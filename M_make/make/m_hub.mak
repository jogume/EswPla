#** ***************************************************************************
# \copyright       EswPla FreeRTOS Project
# \file            m_hub.mak
# \brief           Central hub for project configuration
# \Make            GNU Make
#******************************************************************************

include m_project_cfg.mak

#-----------------------------------------------------------------------------#
# Include module makefile
#-----------------------------------------------------------------------------#
-include m_module.mak

#-----------------------------------------------------------------------------#
# List of general variables used in Makefile
#-----------------------------------------------------------------------------#
comma                        := ,
blank                        :=
space                        := $(blank) $(blank)

#-----------------------------------------------------------------------------#
# Module path processing (backward compatibility)
#-----------------------------------------------------------------------------#
MODULE_PATH           := $(strip $(subst ./,,\
                         $(subst :,$(space),$(MODULE_PATH))))

MODULE_HEADER_PATH    := $(strip $(subst ./,,\
                         $(subst :,$(space),$(MODULE_HEADER_PATH))))

#-----------------------------------------------------------------------------#
# Compiler and toolchain paths
#-----------------------------------------------------------------------------#
S_DIR_PROC              := M_make
S_DIR_PROC_MAKE         := $(S_DIR_PROC)/make

#-----------------------------------------------------------------------------#
# Compiler executable paths
#-----------------------------------------------------------------------------#
T_PTH_BUILD_COMPILER    = $(COMPILER_PREFIX)gcc
T_PTH_BUILD_ASM         = $(COMPILER_PREFIX)gcc
T_PTH_BUILD_LIB         = $(COMPILER_PREFIX)ar
T_PTH_BUILD_LINK        = $(COMPILER_PREFIX)gcc

#-----------------------------------------------------------------------------#
# Module output directories
#-----------------------------------------------------------------------------#
S_DIR_LIB               = library
S_DIR_OBJ               = object

S_DPH_MOD_OUT           = $(MODULE_NAME)/output/$(PROJECT_NAME)
S_DPH_MOD_LIB           = $(S_DPH_MOD_OUT)/$(S_DIR_LIB)
S_DPH_MOD_OBJ           = $(S_DPH_MOD_OUT)/$(S_DIR_OBJ)

#-----------------------------------------------------------------------------#
# Project output directories
#-----------------------------------------------------------------------------#
S_DPH_PRJ_OUT           = $(PROJECT_NAME)/output/$(PROJECT_NAME)
S_DPH_PRJ_OBJ           = $(S_DPH_PRJ_OUT)/$(S_DIR_OBJ)

S_PPH_PRJ_EXE           = $(S_DPH_PRJ_OUT)/$(PROJECT_NAME).exe
S_PPH_PRJ_MAP           = $(S_DPH_PRJ_OUT)/$(PROJECT_NAME).map

#-----------------------------------------------------------------------------#
# Source and include paths
#-----------------------------------------------------------------------------#
MODULE_SOURCE_PATHS     = $(addprefix $(MODULE_NAME)/,$(MODULE_PATH))
MODULE_INCLUDE_PATHS    = $(addprefix $(MODULE_NAME)/,$(MODULE_HEADER_PATH))

#-----------------------------------------------------------------------------#
# Compiler defines and includes
#-----------------------------------------------------------------------------#
COMPILER_DEFINE         = $(COMPILER_DEFINE_PROJECT) $(COMPILER_DEFINE_MODULE)
COMPILER_INCLUDE        = $(addprefix -I ,$(MODULE_INCLUDE_PATHS)) $(HEADER_PATH)

#-----------------------------------------------------------------------------#
# Object files
#-----------------------------------------------------------------------------#
OBJ_LIST                = $(OBJ_QAC) $(OBJ_NOQAC) $(OBJ_ASM)
OBJECTS                 = $(addprefix $(S_DPH_MOD_OBJ)/,$(OBJ_LIST))

#-----------------------------------------------------------------------------#
# Module library
#-----------------------------------------------------------------------------#
S_PPH_MOD_LIB           = $(S_DPH_MOD_LIB)/$(MODULE_NAME)_$(LINKING_VARIANT).lib
