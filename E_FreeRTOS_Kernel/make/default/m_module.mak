###############################################################################
#                                                                             #
#     Module Description:  FreeRTOS Kernel module makefile                   #
#     Module Name:         E_FreeRTOS_Kernel                                  #
#                                                                             #
###############################################################################

#------------------------- Module information --------------------------------#
MODULE_NAME            = E_FreeRTOS_Kernel
MODULE_PATH            = .:portable/MemMang:portable/MSVC-MingW
MODULE_HEADER_PATH     = include:portable/MSVC-MingW
MODULE_STATUS          = public
PRE_COMPILE_VARIANT    = default

#---------------------------------------------------------------------------------------------------------------------------#
# Objects - FreeRTOS Kernel core files
#---------------------------------------------------------------------------------------------------------------------------#
OBJ_QAC   	 = croutine.o \
               event_groups.o \
               list.o \
               queue.o \
               stream_buffer.o \
               tasks.o \
               timers.o \
               heap_5.o \
               port.o

OBJ_ASM      =

OBJ_NOQAC 	 =
