#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = F:/SYSBIOS/Platform;C:/ti/bios_6_37_05_35/packages;C:/ti/ndk_2_21_02_43/packages;C:/ti/ccsv5/ccs_base;C:/ti/uia_1_03_01_08/packages
override XDCROOT = C:/ti/xdctools_3_25_03_72
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = F:/SYSBIOS/Platform;C:/ti/bios_6_37_05_35/packages;C:/ti/ndk_2_21_02_43/packages;C:/ti/ccsv5/ccs_base;C:/ti/uia_1_03_01_08/packages;C:/ti/xdctools_3_25_03_72/packages;..
HOSTOS = Windows
endif
