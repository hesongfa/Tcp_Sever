/****************************************************************************/
/*                                                                          */
/* ���ݴ������ӿƼ����޹�˾                                                 */
/*                                                                          */
/* Copyright (C) 2014-2016 Guangzhou Tronlong Electronic Technology Co.,Ltd */
/*                                                                          */
/****************************************************************************/
/****************************************************************************/
/*                                                                          */
/*              NDK_TCP ͨ��                                                */
/*                                                                          */
/*              2016��07��11��                                              */
/*                                                                          */
/****************************************************************************/

// ȫ�ֶ���
#include "General.h"

/****************************************************************************/
/*                                                                          */
/*              ȫ�ֱ���                                                    */
/*                                                                          */
/****************************************************************************/
// ����
char *HostName    = "Tronlong-DSP_C6678";
char *LocalIPAddr = "0.0.0.0";          // DHCP ģʽ������Ϊ "0.0.0.0"
char *LocalIPMask = "255.255.255.0";    // ʹ�� DHCP ʱ������
char *GatewayIP   = "192.168.2.101";    // ʹ�� DHCP ʱ������
char *DomainName  = "x.51dsp.net";         // ʹ�� DHCP ʱ������
char *DNSServer   = "0.0.0.0";          // ������0ʱ�����õ�

// ���
static HANDLE hHello=0;

/****************************************************************************/
/*                                                                          */
/*              ��������                                                    */
/*                                                                          */
/****************************************************************************/
extern int TcpTest();
// ������ƻص�����
static void   NetworkOpen();
static void   NetworkClose();
static void   NetworkIPAddr( IPN IPAddr, uint IfIdx, uint fAdd );

// ���񱨸溯��
static void   ServiceReport( uint Item, uint Status, uint Report, HANDLE hCfgEntry );

/****************************************************************************/
/*                                                                          */
/*              NDK ��                                                    */
/*                                                                          */
/****************************************************************************/
static void NetworkOpen()
{
	// ����һ�������� �˿� 1025
    hHello = DaemonNew( SOCK_STREAMNC, 0, 1025, TcpTest,
                       OS_TASKPRINORM, OS_TASKSTKNORM, 0, 3 );
}

/****************************************************************************/
/*                                                                          */
/*              NDK �ر�                                                    */
/*                                                                          */
/****************************************************************************/
static void NetworkClose()
{
    DaemonFree( hHello );
}

/****************************************************************************/
/*                                                                          */
/*              IP ��ַ                                                     */
/*                                                                          */
/****************************************************************************/
static void NetworkIPAddr( IPN IPAddr, uint IfIdx, uint fAdd )
{
    IPN IPTmp;

    if( fAdd )
    	platform_write("Network Added: ");
    else
    	platform_write("Network Removed: ");

    IPTmp = ntohl( IPAddr );
    platform_write("If-%d:%d.%d.%d.%d\n", IfIdx,
            (UINT8)(IPTmp>>24)&0xFF, (UINT8)(IPTmp>>16)&0xFF,
            (UINT8)(IPTmp>>8)&0xFF, (UINT8)IPTmp&0xFF );
}

/****************************************************************************/
/*                                                                          */
/*              ����״̬                                                    */
/*                                                                          */
/****************************************************************************/
static char *TaskName[]  = { "Telnet","HTTP","NAT","DHCPS","DHCPC","DNS" };
static char *ReportStr[] = { "","Running","Updated","Complete","Fault" };
static char *StatusStr[] = { "Disabled","Waiting","IPTerm","Failed","Enabled" };

static void ServiceReport( uint Item, uint Status, uint Report, HANDLE h )
{
	platform_write("Service Status: %-9s: %-9s: %-9s: %03d\n",
            TaskName[Item-1], StatusStr[Status],
            ReportStr[Report/256], Report&0xFF);

    // ���� DHCP
    if( Item == CFGITEM_SERVICE_DHCPCLIENT &&
        Status == CIS_SRV_STATUS_ENABLED &&
        (Report == (NETTOOLS_STAT_RUNNING|DHCPCODE_IPADD) ||
         Report == (NETTOOLS_STAT_RUNNING|DHCPCODE_IPRENEW)) )
    {
        IPN IPTmp;

        // ���� DNS
        IPTmp = inet_addr(DNSServer);
        if( IPTmp )
            CfgAddEntry( 0, CFGTAG_SYSINFO, CFGITEM_DHCP_DOMAINNAMESERVER,
                         0, sizeof(IPTmp), (UINT8 *)&IPTmp, 0 );
    }
}

/****************************************************************************/
/*                                                                          */
/*              ����Task���߳�                                            */
/*                                                                          */
/****************************************************************************/
Void NDKTask(UArg a0, UArg a1)
{
    int             rc;
    HANDLE          hCfg;
    QMSS_CFG_T      qmss_cfg;
    CPPI_CFG_T      cppi_cfg;

    /* ��ʼ����Ҫ�������
     *  (1) QMSS
     *  (2) CPPI
     *  (3) Packet Accelerator
     */
    // ��ʼ�� QMSS
    if (platform_get_coreid() == 0)
    {
        qmss_cfg.master_core        = 1;
    }
    else
    {
        qmss_cfg.master_core        = 0;
    }
    qmss_cfg.max_num_desc       = MAX_NUM_DESC;
    qmss_cfg.desc_size          = MAX_DESC_SIZE;
    qmss_cfg.mem_region         = Qmss_MemRegion_MEMORY_REGION0;
    if (res_mgr_init_qmss (&qmss_cfg) != 0)
    {
        platform_write ("Failed to initialize the QMSS subsystem \n");
        goto main_exit;
    }
    else
    {
     platform_write ("QMSS successfully initialized \n");
    }

    // ��ʼ�� CPPI
    if (platform_get_coreid() == 0)
    {
        cppi_cfg.master_core        = 1;
    }
    else
    {
        cppi_cfg.master_core        = 0;
    }
    cppi_cfg.dma_num            = Cppi_CpDma_PASS_CPDMA;
    cppi_cfg.num_tx_queues      = NUM_PA_TX_QUEUES;
    cppi_cfg.num_rx_channels    = NUM_PA_RX_CHANNELS;
    if (res_mgr_init_cppi (&cppi_cfg) != 0)
    {
        platform_write ("Failed to initialize CPPI subsystem \n");
        goto main_exit;
    }
    else
    {
     platform_write ("CPPI successfully initialized \n");
    }

    // ��ʼ�� PA
    if (res_mgr_init_pass()!= 0) {
        platform_write ("Failed to initialize the Packet Accelerator \n");
        goto main_exit;
    }
    else
    {
     platform_write ("PA successfully initialized \n");
    }

    // ʹ�� NDK Э��ջ�ı������ȵ��ô˺���
    rc = NC_SystemOpen( NC_PRIORITY_LOW, NC_OPMODE_INTERRUPT );
    if( rc )
    {
        platform_write("NC_SystemOpen Failed (%d)\n",rc);
        for(;;);
    }

    // �����µ�ϵͳ����
    hCfg = CfgNew();
    if( !hCfg )
    {
        platform_write("Unable to create configuration\n");
        goto main_exit;
    }

    // ��֤֧�ֵ���������
    if( strlen( DomainName ) >= CFG_DOMAIN_MAX ||
        strlen( HostName ) >= CFG_HOSTNAME_MAX )
    {
    	platform_write("Names too long\n");
        goto main_exit;
    }

    // ���ȫ���������� hCfg
    CfgAddEntry( hCfg, CFGTAG_SYSINFO, CFGITEM_DHCP_HOSTNAME, 0,
                 strlen(HostName), (UINT8 *)HostName, 0 );

    // ���ָ�� IP ��ַ���ֶ����� IP �� ����
    if (0)
    {
        CI_IPNET NA;
        CI_ROUTE RT;
        IPN      IPTmp;

        // ����IP ��ַ
        bzero( &NA, sizeof(NA) );
        NA.IPAddr  = inet_addr(LocalIPAddr);
        NA.IPMask  = inet_addr(LocalIPMask);
        strcpy( NA.Domain, DomainName );
        NA.NetType = 0;

        // ��ӵ�ַ���ӿ�
        CfgAddEntry( hCfg, CFGTAG_IPNET, 1, 0,
                           sizeof(CI_IPNET), (UINT8 *)&NA, 0 );

        // ���Ĭ������
        bzero( &RT, sizeof(RT) );
        RT.IPDestAddr = 0;
        RT.IPDestMask = 0;
        RT.IPGateAddr = inet_addr(GatewayIP);

        // �������·��
        CfgAddEntry( hCfg, CFGTAG_ROUTE, 0, 0,
                           sizeof(CI_ROUTE), (UINT8 *)&RT, 0 );

        // ���ָ�� DNS,���ֶ���� DNS ����
        IPTmp = inet_addr(DNSServer);
        if( IPTmp )
            CfgAddEntry( hCfg, CFGTAG_SYSINFO, CFGITEM_DHCP_DOMAINNAMESERVER,
                         0, sizeof(IPTmp), (UINT8 *)&IPTmp, 0 );
    }
    // ͨ�� DHCP �Զ����� IP �� ����
    else
    {
        CI_SERVICE_DHCPC dhcpc;

        // ���� DHCP ����
        bzero( &dhcpc, sizeof(dhcpc) );
        dhcpc.cisargs.Mode   = CIS_FLG_IFIDXVALID;
        dhcpc.cisargs.IfIdx  = 1;
        dhcpc.cisargs.pCbSrv = &ServiceReport;
        CfgAddEntry( hCfg, CFGTAG_SERVICE, CFGITEM_SERVICE_DHCPCLIENT, 0,
                     sizeof(dhcpc), (UINT8 *)&dhcpc, 0 );
    }

    // ���鿴���ھ��漶��ĵ�����Ϣ
    rc = DBG_WARN;
    CfgAddEntry( hCfg, CFGTAG_OS, CFGITEM_OS_DBGPRINTLEVEL,
                 CFG_ADDMODE_UNIQUE, sizeof(uint), (UINT8 *)&rc, 0 );

    // TCP ���� buffer ��С
	rc = 8192;
	CfgAddEntry( hCfg, CFGTAG_IP, CFGITEM_IP_SOCKTCPTXBUF,
				 CFG_ADDMODE_UNIQUE, sizeof(uint), (UINT8 *)&rc, 0 );

	// TCP ���� buffer ��С������ģʽ��
	rc = 8192;
	CfgAddEntry( hCfg, CFGTAG_IP, CFGITEM_IP_SOCKTCPRXBUF,
				 CFG_ADDMODE_UNIQUE, sizeof(uint), (UINT8 *)&rc, 0 );

	// TCP �������ƣ��Ǹ���ģʽ��
	rc = 8192;
	CfgAddEntry( hCfg, CFGTAG_IP, CFGITEM_IP_SOCKTCPRXLIMIT,
				 CFG_ADDMODE_UNIQUE, sizeof(uint), (UINT8 *)&rc, 0 );

    // UDP ��������
    rc = 8192;
    CfgAddEntry( hCfg, CFGTAG_IP, CFGITEM_IP_SOCKUDPRXLIMIT,
                 CFG_ADDMODE_UNIQUE, sizeof(uint), (UINT8 *)&rc, 0 );

    // ʹ����Щ��������ϵͳ
    do
    {
        rc = NC_NetStart( hCfg, NetworkOpen, NetworkClose, NetworkIPAddr );
    } while( rc > 0 );

    // �ͷ����þ��
    CfgFree( hCfg );

main_exit:
    NC_SystemClose();
}

