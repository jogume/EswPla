###############################################################################
#                                                                             #
#           EswPla FreeRTOS Project Configuration                             #
#                                                                             #
#     Module Description:  Project Configuration Makefile                     #
#     Module Name:         PG_Yolpiya                                         #
#                                                                             #
###############################################################################

#------------------------- Project name and linking variant ------------------#
PROJECT_NAME   ?= PG_Yolpiya
PROJECT_TYPE    = program
PROJECT_PATH    = PG_Yolpiya/make
LINKING_VARIANT = default

#------------------------- Compiler settings ---------------------------------#
COMPILER_NAME    = T_gcc
COMPILER_VARIANT = mingw
COMPILER_VERSION = 8.1.0
COMPILER_PREFIX  =

# Compiler defines during compilation
COMPILER_DEFINE_PROJECT = -D_WIN32_WINNT=0x0601 -DprojCOVERAGE_TEST=0

#------------------------- List of all the modules source files path ---------#
# Header paths for all modules
HEADER_PATH  = -I PG_Yolpiya/source
HEADER_PATH += -I PG_Yolpiya/source/framework
HEADER_PATH += -I PG_Yolpiya/source/freertos_app
HEADER_PATH += -I PG_Yolpiya/source/pack_unpack
HEADER_PATH += -I PG_Yolpiya/Trace_Recorder_Configuration
HEADER_PATH += -I PG_Yolpiya
HEADER_PATH += -I E_FreeRTOS_Kernel/include
HEADER_PATH += -I E_FreeRTOS_Kernel/portable/MSVC-MingW
HEADER_PATH += -I E_FreeRTOS_Plus_Trace/include
HEADER_PATH += -I E_FreeRTOS_Plus_Trace/kernelports/FreeRTOS/include
HEADER_PATH += -I M_make/interface
HEADER_PATH += -I M_hal/interface
HEADER_PATH += -I M_hs/interface

#------ List all the module libs to be linked --------------------------------#
LIBRARY_QAC      = E_FreeRTOS_Kernel/output/$(PROJECT_NAME)/library/E_FreeRTOS_Kernel_default.lib
LIBRARY_QAC     += E_FreeRTOS_Plus_Trace/output/$(PROJECT_NAME)/library/E_FreeRTOS_Plus_Trace_default.lib
LIBRARY_QAC     += M_hal/output/$(PROJECT_NAME)/library/M_hal_default.lib
LIBRARY_QAC     += M_hs/output/$(PROJECT_NAME)/library/M_hs_default.lib
LIBRARY_QAC     += PG_Yolpiya/output/$(PROJECT_NAME)/library/PG_Yolpiya_default.lib

# List of modules to compile (with QAC support - though we're not using QAC)
MAKE_QAC         = E_FreeRTOS_Kernel/make/default
MAKE_QAC        += E_FreeRTOS_Plus_Trace/make/default
MAKE_QAC        += M_hal/make/default
MAKE_QAC        += M_hs/make/default
MAKE_QAC        += PG_Yolpiya/make/default

# Modules without QAC (none in this case)
MAKE_NOQAC       =

#------------------------- Linker options ------------------------------------#
LINKER_ADDITIONAL_OPTIONS = -lwinmm -lws2_32

#------------------------- Build options -------------------------------------#
# Custom compiler options (if needed)
# COMPILER_CUSTOM_OPTIONS = -O0 -g3 -Wall

# Project status for debug info
PROJECT_STATUS = public
