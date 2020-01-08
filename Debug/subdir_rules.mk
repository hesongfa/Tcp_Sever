################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
Net.obj: ../Net.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6600 --abi=eabi -g --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="C:/ti/bios_6_37_05_35/packages/ti/bios/include" --include_path="C:/ti/ndk_2_21_02_43/packages/ti/ndk/inc" --include_path="C:/ti/ndk_2_21_02_43/packages/ti/ndk/inc/tools" --include_path="../../../Include/ti/csl" --include_path="../../../Include/ti/platform" --include_path="../../../Include/ti/nimu" --include_path="../../../Include/ti/qmss" --include_path="../../../Include/ti/cppi" --include_path="../../../Include/ti/pa" --include_path="../../../Include" --include_path="../../../Include/Board" --include_path="../../../Include/Driver" --include_path="../../../Include/Driver/hw" --gcc --define=_INCLUDE_NIMU_CODE --define=C66_PLATFORMS --define=_NDK_EXTERN_CONFIG --display_error_number --diag_warning=225 --preproc_with_compile --preproc_dependency="Net.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

TCP.obj: ../TCP.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6600 --abi=eabi -g --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="C:/ti/bios_6_37_05_35/packages/ti/bios/include" --include_path="C:/ti/ndk_2_21_02_43/packages/ti/ndk/inc" --include_path="C:/ti/ndk_2_21_02_43/packages/ti/ndk/inc/tools" --include_path="../../../Include/ti/csl" --include_path="../../../Include/ti/platform" --include_path="../../../Include/ti/nimu" --include_path="../../../Include/ti/qmss" --include_path="../../../Include/ti/cppi" --include_path="../../../Include/ti/pa" --include_path="../../../Include" --include_path="../../../Include/Board" --include_path="../../../Include/Driver" --include_path="../../../Include/Driver/hw" --gcc --define=_INCLUDE_NIMU_CODE --define=C66_PLATFORMS --define=_NDK_EXTERN_CONFIG --display_error_number --diag_warning=225 --preproc_with_compile --preproc_dependency="TCP.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/linker.cmd: ../app.cfg
	@echo 'Building file: $<'
	@echo 'Invoking: XDCtools'
	"C:/ti/xdctools_3_25_03_72/xs" --xdcpath="F:/SYSBIOS/Platform;C:/ti/bios_6_37_05_35/packages;C:/ti/ndk_2_21_02_43/packages;C:/ti/ccsv5/ccs_base;C:/ti/uia_1_03_01_08/packages;" xdc.tools.configuro -o "configPkg" -t ti.targets.elf.C66 -p Tronlong.DSP.C6000.C6678_L2 -r release -c "C:/ti/ccsv5/tools/compiler/c6000_7.4.4" "$<"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/compiler.opt: | configPkg/linker.cmd
configPkg/: | configPkg/linker.cmd

main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6600 --abi=eabi -g --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="C:/ti/bios_6_37_05_35/packages/ti/bios/include" --include_path="C:/ti/ndk_2_21_02_43/packages/ti/ndk/inc" --include_path="C:/ti/ndk_2_21_02_43/packages/ti/ndk/inc/tools" --include_path="../../../Include/ti/csl" --include_path="../../../Include/ti/platform" --include_path="../../../Include/ti/nimu" --include_path="../../../Include/ti/qmss" --include_path="../../../Include/ti/cppi" --include_path="../../../Include/ti/pa" --include_path="../../../Include" --include_path="../../../Include/Board" --include_path="../../../Include/Driver" --include_path="../../../Include/Driver/hw" --gcc --define=_INCLUDE_NIMU_CODE --define=C66_PLATFORMS --define=_NDK_EXTERN_CONFIG --display_error_number --diag_warning=225 --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

platform_osal.obj: ../platform_osal.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6600 --abi=eabi -g --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="C:/ti/bios_6_37_05_35/packages/ti/bios/include" --include_path="C:/ti/ndk_2_21_02_43/packages/ti/ndk/inc" --include_path="C:/ti/ndk_2_21_02_43/packages/ti/ndk/inc/tools" --include_path="../../../Include/ti/csl" --include_path="../../../Include/ti/platform" --include_path="../../../Include/ti/nimu" --include_path="../../../Include/ti/qmss" --include_path="../../../Include/ti/cppi" --include_path="../../../Include/ti/pa" --include_path="../../../Include" --include_path="../../../Include/Board" --include_path="../../../Include/Driver" --include_path="../../../Include/Driver/hw" --gcc --define=_INCLUDE_NIMU_CODE --define=C66_PLATFORMS --define=_NDK_EXTERN_CONFIG --display_error_number --diag_warning=225 --preproc_with_compile --preproc_dependency="platform_osal.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

resourcemgr.obj: ../resourcemgr.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6600 --abi=eabi -g --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="C:/ti/bios_6_37_05_35/packages/ti/bios/include" --include_path="C:/ti/ndk_2_21_02_43/packages/ti/ndk/inc" --include_path="C:/ti/ndk_2_21_02_43/packages/ti/ndk/inc/tools" --include_path="../../../Include/ti/csl" --include_path="../../../Include/ti/platform" --include_path="../../../Include/ti/nimu" --include_path="../../../Include/ti/qmss" --include_path="../../../Include/ti/cppi" --include_path="../../../Include/ti/pa" --include_path="../../../Include" --include_path="../../../Include/Board" --include_path="../../../Include/Driver" --include_path="../../../Include/Driver/hw" --gcc --define=_INCLUDE_NIMU_CODE --define=C66_PLATFORMS --define=_NDK_EXTERN_CONFIG --display_error_number --diag_warning=225 --preproc_with_compile --preproc_dependency="resourcemgr.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


