#Generated by VisualGDB (http://visualgdb.com)
#DO NOT EDIT THIS FILE MANUALLY UNLESS YOU ABSOLUTELY NEED TO
#USE VISUALGDB PROJECT PROPERTIES DIALOG INSTEAD

BINARYDIR := Debug

#Additional flags
PREPROCESSOR_MACROS := DEBUG=1 STM32F10X_MD
INCLUDE_DIRS := ./Core ./HAL
LIBRARY_DIRS := 
LIBRARY_NAMES := 
ADDITIONAL_LINKER_INPUTS := 
MACOS_FRAMEWORKS := 
LINUX_PACKAGES := 

CFLAGS := -ggdb -ffunction-sections -Os -fdata-sections
CXXFLAGS := -ggdb -ffunction-sections -fno-exceptions -fno-rtti -Os -fdata-sections
ASFLAGS := 
LDFLAGS := -Wl,-gc-sections
COMMONFLAGS := 
LINKER_SCRIPT := 

START_GROUP := -Wl,--start-group
END_GROUP := -Wl,--end-group

#Additional options detected from testing the toolchain
USE_DEL_TO_CLEAN := 1
CP_NOT_AVAILABLE := 1

ADDITIONAL_MAKE_FILES := stm32.mak
GENERATE_BIN_FILE := 1
GENERATE_IHEX_FILE := 1
