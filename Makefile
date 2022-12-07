##### Project #####

PROJECT			?= app
BUILD_DIR		= Build


##### Options #####

# Enable printf float %f support, y:yes, n:no
ENABLE_PRINTF_FLOAT	?= n
# Build with FreeRTOS, y:yes, n:no
USE_FREERTOS	?= n
# Programmer, jlink or pyocd
FLASH_PROGRM	?= pyocd


##### Toolchains #######

#ARM_TOOCHAIN	?= /opt/gcc-arm/gcc-arm-11.2-2022.02-x86_64-arm-none-eabi/bin
#ARM_TOOCHAIN	?= /opt/gcc-arm/arm-gnu-toolchain-11.3.rel1-x86_64-arm-none-eabi/bin
ARM_TOOCHAIN	?= /opt/gcc-arm/arm-gnu-toolchain-12.2.mpacbti-bet1-x86_64-arm-none-eabi/bin

# path to JLinkExe
JLINKEXE		?= /opt/SEGGER/JLink/JLinkExe
JLINK_DEVICE	?= AT32F421C8T7
# path to PyOCD
PYOCD_EXE		?= pyocd
PYOCD_DEVICE	?= _at32f421c8t7


##### Paths ############

# Link descript file for this chip
LDSCRIPT		= Libraries/cmsis/cm4/device_support/startup/gcc/linker/AT32F421x8_FLASH.ld
# Library build flags
LIB_FLAGS		= USE_STDPERIPH_DRIVER AT32F421C8T7

# C source folders
CDIRS	:= User \
		Libraries/cmsis/cm4/device_support \
		Libraries/drivers/src \
		Libraries/bsp/src

# C source files (if there are any single ones)
CFILES := 

# ASM source folders
ADIRS	:= User
# ASM single files
AFILES	:= Libraries/cmsis/cm4/device_support/startup/gcc/startup_at32f421.s

# Include paths
INCLUDES	:= User \
			Libraries/cmsis/cm4/core_support \
			Libraries/cmsis/cm4/device_support \
			Libraries/drivers/inc \
			Libraries/bsp/inc

ifeq ($(USE_FREERTOS),y)
CDIRS		+= Middlewares/FreeRTOS \
			Middlewares/FreeRTOS/portable/GCC/ARM_CM3

CFILES		+= Middlewares/FreeRTOS/portable/MemMang/heap_4.c

INCLUDES	+= Middlewares/FreeRTOS/include \
			Middlewares/FreeRTOS/portable/GCC/ARM_CM3
endif

include ./rules.mk
