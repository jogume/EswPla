#** *************************************************************************** 
# \copyright       EswPla FreeRTOS Project
# \file            Makefile
# \brief           Top-level Makefile for PG_Yolpiya project
# \Make            GNU Make
#******************************************************************************

#------------------------------------------------------------------------------
# Do not modify this line used to get the path of current Makefile
#------------------------------------------------------------------------------
mfd := $(dir $(realpath $(lastword ${MAKEFILE_LIST})))

#------------------------------------------------------------------------------
# Default goal for makefile if no goal is defined at command line
#------------------------------------------------------------------------------
MAKECMDGOALS ?= all

#------------------------------------------------------------------------------
# Makefile call - triggers the main build system
# $(mfd) gives path to "PG_Yolpiya/" add subdirectory path of m_project_cfg.mak
#------------------------------------------------------------------------------
$(MAKECMDGOALS):
	$(MAKE) -C ../ -f M_make/make/makefile.mak -I $(mfd)make $(MAKECMDGOALS) ${MAKEOPTION}
