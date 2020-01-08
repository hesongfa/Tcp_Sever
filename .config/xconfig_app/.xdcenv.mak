#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = D:/TI/Demo/SYSBIOS/Platform;D:/TI/bios_6_37_05_35/packages;D:/TI/ndk_2_21_02_43/packages;D:/TI/ccsv5/ccs_base;D:/TI/uia_1_03_01_08/packages;D:/TI/Demo/SYSBIOS/Application/NDK_TCP/.config
override XDCROOT = D:/TI/xdctools_3_25_03_72
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = D:/TI/Demo/SYSBIOS/Platform;D:/TI/bios_6_37_05_35/packages;D:/TI/ndk_2_21_02_43/packages;D:/TI/ccsv5/ccs_base;D:/TI/uia_1_03_01_08/packages;D:/TI/Demo/SYSBIOS/Application/NDK_TCP/.config;D:/TI/xdctools_3_25_03_72/packages;..
HOSTOS = Windows
endif
