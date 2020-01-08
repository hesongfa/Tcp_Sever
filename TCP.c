/****************************************************************************/
/*                                                                          */
/* 广州创龙电子科技有限公司                                                 */
/*                                                                          */
/* Copyright (C) 2014-2016 Guangzhou Tronlong Electronic Technology Co.,Ltd */
/*                                                                          */
/****************************************************************************/
/****************************************************************************/
/*                                                                          */
/*              NDK TCP 通信                                                */
/*                                                                          */
/*              2014年09月22日                                              */
/*                                                                          */
/****************************************************************************/

#include <ti/ndk/inc/netmain.h>
#include <stdio.h>
#include <socket.h>
#include <usertype.h>
#include "General.h"
#include <cstdio>
/****************************************************************************/
/*                                                                          */
/*              回调函数 TCP Server Daemon                                  */
/*                                                                          */
/****************************************************************************/
struct Data //鏁版嵁鍖�
{
 int number;
 int length;
 char receivemessage[1026]; //鍐呭淇℃伅
 int fin;
}data;

#define FAR far
#define WSADESCRIPTION_LEN 256
#define WSASYS_STATUS_LEN  128
typedef unsigned short WORD;

/*typedef struct WSAData
{
	WORD  wVersion;
	WORD  wHighVersion;

	char    szDescription[WSADESCRIPTION_LEN+1];
	char    szSystemStatus[WSASYS_STATUS_LEN+1];
	unsigned short     iMaxSockets;
	unsigned short     iMaxUdpDg;
	 char FAR * lpVendorInfo;

}WSADATA,FAR_LPWSADATA;*/


/*
BMP鍥�
浣嶅浘鏂囦欢澶寸粨鏋勪綋鎻愪緵鍥惧儚鐨勬牸寮忋�澶у皬绛変俊鎭�       		  	  hsf
14涓瓧鑺�
*/
typedef struct
{
	//WORD bfType;				//鏍煎紡鍥哄畾涓�x424D 2瀛楄妭
	unsigned long bfSize;   	//鏂囦欢澶у皬 	           4瀛楄妭
	unsigned short bfReserved1;	//淇濈暀瀛楋紝涓嶈�铏�    	   2瀛楄妭
	unsigned short bfReserved2; //淇濈暀瀛楋紝鍚屼笂		   2瀛楄妭
	unsigned long bfOffBits;	//瀹為檯浣嶅浘鏁版嵁鐨勫亸绉诲瓧鑺傛暟锛屽嵆鍓嶄笁涓儴鍒嗛暱搴︿箣鍜�                  		4瀛楄妭
}ClBitMapFileHeader;     


int TcpTest(SOCKET s, UINT32 unused)
{
			/*
			struct timeval tv;  璁剧疆鏃堕棿缁撴瀯浣�
			tv.tv_sec  = 1;		1绉�
	        tv.tv_usec = 0;     1寰
	        鐢ㄤ簬setsockopt锛堬級鍑芥暟閲岀殑鎺ュ彈鎴栧彂閫佽秴鏃跺弬鏁拌瀹�h.s.f
	        鍦═CP杩炴帴涓紝recv绛夊嚱鏁伴粯璁や负闃诲妯″紡(block)锛屽嵆鐩村埌鏈夋暟鎹埌鏉ヤ箣鍓嶅嚱鏁颁笉浼氳繑鍥烇紝
	        鑰屾垜浠湁鏃跺垯闇�涓�瓒呮椂鏈哄埗浣垮叾鍦ㄤ竴瀹氭椂闂村悗杩斿洖鑰屼笉绠℃槸鍚︽湁鏁版嵁鍒版潵锛�
	        杩欓噷鎴戜滑灏变細鐢ㄥ埌setsockopt()鍑芥暟锛屽綋瓒呰繃tv_out璁惧畾鐨勬椂闂磋�娌℃湁鏁版嵁鍒版潵鏃秗ecv()灏变細杩斿洖0鍊笺�
			h.s.f
			*/
	        struct timeval tv;
	        tv.tv_sec  = 1;
	        tv.tv_usec = 0;
	        setsockopt(s,SOL_SOCKET,SO_SNDTIMEO,&tv,sizeof(tv));
	        setsockopt(s,SOL_SOCKET,SO_RCVTIMEO,&tv,sizeof(tv));
			
	        struct sockaddr_in sin1;
	        int sz=sizeof(sin1);  		//缁熻濂楁帴瀛梥ocket淇℃伅闀垮害 9涓瓧鑺�	      	h.s.f
	        //int hlen=strlen(reply);
	        int nr,total=0;				//nr:淇濆瓨鍑芥暟杩斿洖鍊�h.s.f
	        HANDLE hBuffer;    			//绛夊悓浜�void *hBuffer	h.s.f
	        unsigned char* pBuf;
             struct Data data;			//寮�ご瀹氫箟鐨勬暟鎹寘缁撴瀯浣�h.s.f
            int shuchu;

	        unsigned char *pBuf1;
	        unsigned char *pBufn;
			
			unsigned char *pBuf14;
	        pBuf14 = (unsigned char*)malloc(14);  //鍔ㄦ�鍒嗛厤涓�釜瀛樺偍绌洪棿	14涓瓧鑺�瀛樻斁浣嶅浘澶存枃浠跺唴瀹�hsf
	        nr=recvncfrom( s, (void**)&pBuf14, 0, (PSA)&sin1, &sz, &hBuffer );  //鎴愬姛锛氳繑鍥炴帴鏀跺埌鐨勬暟鎹紱澶辫触锛氳繑鍥�/-1
	        unsigned char* pBuf40;				 
	        pBuf40 = (unsigned char*)malloc(40);  //鍔ㄦ�鍒嗛厤涓�釜瀛樺偍绌洪棿 40涓瓧鑺傦紝瀛樻斁浣嶅浘淇℃伅澶村唴瀹筯sf
	        nr=recvncfrom( s, (void**)&pBuf40, 0, (PSA)&sin1, &sz, &hBuffer );
	       /* for(shuchu = 0;shuchu<40;shuchu++)
	        {
	         printf("输出 :%d\n",pBuf40[shuchu]);
	        }*/
            int W1,H1;
            W1 = (int)(pBuf40[4])+(int)(pBuf40[5])*256 +(int)(pBuf40[6]) * 256*256 + (int)(pBuf40[7])* 256*256*256;  //鍥剧墖瀹藉害
            H1 = (int)(pBuf40[8])+(int)(pBuf40[9])*256 +(int)(pBuf40[10]) * 256*256 + (int)(pBuf40[11])* 256*256*256;//鍥剧墖楂樺害hsf

            unsigned char *imagedatatuGUODU;   //杩欓噷寮�緹浜嗕竴鍧楃┖闂达紝瀛樻斁鍥惧儚鍐呭  hsf
            imagedatatuGUODU = (unsigned char*)malloc(W1 * H1 * 3 + 1040);
            pBufn = (unsigned char*)malloc(1024 + 10);
            char*M={"FT"};
            int ifn = 0;
            int II;
            while(1)        //涓嶆柇鎺ユ敹 hsf
  	        {
          	  //nr=recvncfrom( s, (void**)&data, 0, (PSA)&sin1, &sz, &hBuffer );
  	            //nr = recv(s, (unsigned char*)pBufn,1024, 0);
  	            nr = recv(s, (unsigned char*)(imagedatatuGUODU+ifn*1024),1024, 0);  //鎴愬姛锛氳繑鍥炴帴鏀跺埌鐨勫瓧鑺傛暟             澶辫触:-1
                                   //(unsigned char*)(imagedatatuGUODU+ifn*1024) 瀛樻斁鐨勫湴鍧�
          	  //nr = recv(s, (unsigned char*)&data,1040, 0);
          	  if(nr<=0) break;  //褰搉r == -1 鏃惰〃绀烘帴鏀跺凡缁忓畬鎴愶紝鍒欓�鍑篽sf
  
  		      ifn = ifn + 1; //浣垮瓨鏀剧殑鍦板潃鍔犱竴 hsf
  		      total+=nr;    //鎺ユ敹鐨勬�鏁版嵁澶у皬            hsf
  	           //nr = recv(s, (unsigned char*)&pBuf,50, 0);
  	          //  nr = (int)recvnc(s, (void**)&pBuf, 0, &hBuffer);
  	           // recvncfree(hBuffer);
                 // fread(&fileType,sizeof(unsigned short),1,pBuf);
               //memset(pBuf,'0',sizeof(pBuf));
  	            //sendto( s, reply, hlen, 0, (PSA)&sin1, sz );
  	            //send(s, pBuf, nr, 0 );
  	        }
			
           unsigned char *image = (unsigned char*)malloc(W1 * H1 * 3);   //鍙堝紑杈熶簡涓�潡鍥惧儚绌洪棿  hsf
           int K3=0;
           int i,j,k;
           int step = W1*3;
			for (i = 0; i<H1; i++)
			{
				for (j = 0; j<W1; j++)
				{
					for (k = 0; k<3; k++)
					{
						image[(H1 - 1 - i)* step + j * 3 + k] = imagedatatuGUODU[K3];  //琛ㄦ槑浜嗗疄闄呭瓨鏀惧浘鍍忎俊鎭殑绌洪棿hsf
						K3 = K3 +1;
					}
				}
			}


			/*
				杩欎竴娈垫槸鎴戞渶涓嶈兘鐞嗚В鐨勶紝涓轰粈涔堣兘澶熷PC绔殑纾佺洏杩涜鎿嶄綔锛岃�涓斾笂浣嶆満涔熸病鏈変簺浠讳綍鐩稿簲鐨勪唬鐮�hsf
			*/
			step = 0;
			FILE *fpWrite = fopen("F:\\data4.txt","w");
				int ii;
			  	for (ii = 0; ii<W1 * H1 * 3; ii++)
			  	{
			  		fprintf(fpWrite,"%d\n",image[ii]);
			  	}
			step = 0;

			
            return 0;
}
