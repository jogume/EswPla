###############################################################################
#                                                                             #
#     Module Description:  FreeRTOS Plus Trace module makefile               #
#     Module Name:         E_FreeRTOS_Plus_Trace                              #
#                                                                             #
###############################################################################

#------------------------- Module information --------------------------------#
MODULE_NAME            = E_FreeRTOS_Plus_Trace
MODULE_PATH            = .:kernelports/FreeRTOS
MODULE_HEADER_PATH     = include:kernelports/FreeRTOS/include
MODULE_STATUS          = public
PRE_COMPILE_VARIANT    = default

#---------------------------------------------------------------------------------------------------------------------------#
# Objects - Trace Recorder files
#---------------------------------------------------------------------------------------------------------------------------#
OBJ_QAC   	 = trcAssert.o \
               trcCounter.o \
               trcDependency.o \
               trcDiagnostics.o \
               trcEntryTable.o \
               trcError.o \
               trcEvent.o \
               trcEventBuffer.o \
               trcExtension.o \
               trcHardwarePort.o \
               trcHeap.o \
               trcInternalEventBuffer.o \
               trcInterval.o \
               trcISR.o \
               trcMultiCoreEventBuffer.o \
               trcObject.o \
               trcPrint.o \
               trcRunnable.o \
               trcSnapshotRecorder.o \
               trcStackMonitor.o \
               trcStateMachine.o \
               trcStaticBuffer.o \
               trcStreamingRecorder.o \
               trcString.o \
               trcTask.o \
               trcTimestamp.o \
               trcKernelPort.o

OBJ_ASM      =

OBJ_NOQAC 	 =
