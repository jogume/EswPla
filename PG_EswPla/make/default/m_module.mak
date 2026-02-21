###############################################################################
#                                                                             #
#     Module Description:  PG_EswPla Application module makefile             #
#     Module Name:         PG_EswPla                                          #
#                                                                             #
###############################################################################

#------------------------- Module information --------------------------------#
MODULE_NAME            = PG_EswPla
MODULE_PATH            = source:source/framework:source/freertos_app:source/pack_unpack
MODULE_HEADER_PATH     = source:source/framework:source/freertos_app:source/pack_unpack:Trace_Recorder_Configuration
MODULE_STATUS          = public
PRE_COMPILE_VARIANT    = default

#---------------------------------------------------------------------------------------------------------------------------#
# Objects - Main application files
#---------------------------------------------------------------------------------------------------------------------------#
OBJ_QAC   	 = main.o \
               Run-time-stats-utils.o \
               can_dbc_generated.o \
               system_signals.o \
               can_driver.o \
               can_scheduler.o \
               dbc_pack_unpack.o
OBJ_ASM      =

OBJ_NOQAC 	 =

