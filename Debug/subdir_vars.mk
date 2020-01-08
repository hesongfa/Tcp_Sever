################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CFG_SRCS += \
../app.cfg 

C_SRCS += \
../Net.c \
../TCP.c \
../main.c \
../platform_osal.c \
../resourcemgr.c 

OBJS += \
./Net.obj \
./TCP.obj \
./main.obj \
./platform_osal.obj \
./resourcemgr.obj 

C_DEPS += \
./Net.pp \
./TCP.pp \
./main.pp \
./platform_osal.pp \
./resourcemgr.pp 

GEN_MISC_DIRS += \
./configPkg/ 

GEN_CMDS += \
./configPkg/linker.cmd 

GEN_OPTS += \
./configPkg/compiler.opt 

GEN_FILES += \
./configPkg/linker.cmd \
./configPkg/compiler.opt 

GEN_FILES__QUOTED += \
"configPkg\linker.cmd" \
"configPkg\compiler.opt" 

GEN_MISC_DIRS__QUOTED += \
"configPkg\" 

C_DEPS__QUOTED += \
"Net.pp" \
"TCP.pp" \
"main.pp" \
"platform_osal.pp" \
"resourcemgr.pp" 

OBJS__QUOTED += \
"Net.obj" \
"TCP.obj" \
"main.obj" \
"platform_osal.obj" \
"resourcemgr.obj" 

C_SRCS__QUOTED += \
"../Net.c" \
"../TCP.c" \
"../main.c" \
"../platform_osal.c" \
"../resourcemgr.c" 

GEN_CMDS__FLAG += \
-l"./configPkg/linker.cmd" 

GEN_OPTS__FLAG += \
--cmd_file="./configPkg/compiler.opt" 


