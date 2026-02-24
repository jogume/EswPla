/*
 * FreeRTOS V202212.00
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

/******************************************************************************
 * FreeRTOS Blinky Demo
 *
 * This demo creates a simple task-based application using FreeRTOS queues,
 * tasks, and timers. Console output is used in place of LED toggling.
 *
 * NOTE: Windows will not be running the FreeRTOS demo threads continuously, so
 * do not expect to get real time behaviour from the FreeRTOS Windows port, or
 * this demo application. Also, the timing information in the FreeRTOS+Trace
 * logs have no meaningful units. See the documentation page for the Windows
 * port for further information:
 * https://www.FreeRTOS.org/FreeRTOS-Windows-Simulator-Emulator-for-Visual-Studio-and-Eclipse-MingW.html
 *
 ******************************************************************************
 */

/*-----------------------------------------------------------*/
/* INCLUDES                                                   */
/*-----------------------------------------------------------*/

#include "yolpiya.h"

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"
#include "queue.h"

#include "hal_spi.h"
#include "hal_init.h"
#include "tle92104.h"

/*-----------------------------------------------------------*/
/* CONFIGURATION CONSTANTS                                    */
/*-----------------------------------------------------------*/

#define mainREGION_1_SIZE                     8201
#define mainREGION_2_SIZE                     40905
#define mainREGION_3_SIZE                     50007

#define mainNO_KEY_PRESS_VALUE                -1
#define mainOUTPUT_TRACE_KEY                  't'
#define mainRESET_TIMER_KEY                   'r'
#define mainINTERRUPT_NUMBER_KEYBOARD         3

#define mainTRACE_FILE_NAME                   "Trace.dump"

/*-----------------------------------------------------------*/
/* TASK CONFIGURATION                                         */
/*-----------------------------------------------------------*/

#define mainQUEUE_RECEIVE_TASK_PRIORITY       ( tskIDLE_PRIORITY + 2 )
#define mainQUEUE_SEND_TASK_PRIORITY          ( tskIDLE_PRIORITY + 1 )

/*-----------------------------------------------------------*/
/* TIMING CONFIGURATION                                       */
/*-----------------------------------------------------------*/

#define mainTASK_SEND_FREQUENCY_MS            pdMS_TO_TICKS( 10000UL )
#define mainTIMER_SEND_FREQUENCY_MS           pdMS_TO_TICKS( 100UL )
#define mainTASK_RECEIVE_FREQUENCY_MS         pdMS_TO_TICKS( 1000UL )

/*-----------------------------------------------------------*/
/* QUEUE CONFIGURATION                                        */
/*-----------------------------------------------------------*/

#define mainQUEUE_LENGTH                      ( 2 )
#define mainVALUE_SENT_FROM_TASK              ( 100UL )
#define mainVALUE_SENT_FROM_TIMER             ( 200UL )

/*-----------------------------------------------------------*/
/* PRIVATE VARIABLES                                          */
/*-----------------------------------------------------------*/

static QueueHandle_t xQueue = NULL;
static TimerHandle_t xTimer = NULL;
static HANDLE xWindowsKeyboardInputThreadHandle = NULL;
static int xKeyPressed = mainNO_KEY_PRESS_VALUE;

StackType_t uxTimerTaskStack[ configTIMER_TASK_STACK_DEPTH ];

/*-----------------------------------------------------------*/
/* PRIVATE FUNCTION PROTOTYPES - APPLICATION TASKS           */
/*-----------------------------------------------------------*/

static void prvQueueSendTask( void * pvParameters );
static void prvQueueReceiveTask( void * pvParameters );
static void prvQueueSendTimerCallback( TimerHandle_t xTimerHandle );

/*-----------------------------------------------------------*/
/* PRIVATE FUNCTION PROTOTYPES - SYSTEM SETUP                */
/*-----------------------------------------------------------*/

static void prvSetupKeyboardHandling( void );
static void prvInitialiseTrace( void );
static void prvCreateApplicationQueuesAndTasks( void );
static void prvCreateApplicationTimer( TickType_t xTimerPeriod );
static void prvInitialiseHeap( void );
static void prvExerciseHeapStats( void );
static void prvSaveTraceFile( void );

/*-----------------------------------------------------------*/
/* PRIVATE FUNCTION PROTOTYPES - KEYBOARD HANDLING           */
/*-----------------------------------------------------------*/

static DWORD WINAPI prvWindowsKeyboardInputThread( void * pvParam );
static uint32_t prvKeyboardInterruptHandler( void );
static void prvHandleKeyboardInput( int xKeyPressed );

/*-----------------------------------------------------------*/
/* PRIVATE FUNCTION PROTOTYPES - FREERTOS HOOKS              */
/*-----------------------------------------------------------*/

void vApplicationMallocFailedHook( void );
void vApplicationIdleHook( void );
void vApplicationStackOverflowHook( TaskHandle_t pxTask, char * pcTaskName );
void vApplicationTickHook( void );
void vApplicationDaemonTaskStartupHook( void );
void vApplicationGetIdleTaskMemory( StaticTask_t ** ppxIdleTaskTCBBuffer,
                                    StackType_t ** ppxIdleTaskStackBuffer,
                                    uint32_t * pulIdleTaskStackSize );
void vApplicationGetTimerTaskMemory( StaticTask_t ** ppxTimerTaskTCBBuffer,
                                     StackType_t ** ppxTimerTaskStackBuffer,
                                     uint32_t * pulTimerTaskStackSize );

/*-----------------------------------------------------------*/
/* PRIVATE FUNCTION PROTOTYPES - TRACE TIMING                */
/*-----------------------------------------------------------*/

void vTraceTimerReset( void );
uint32_t uiTraceTimerGetFrequency( void );
uint32_t uiTraceTimerGetValue( void );

/*-----------------------------------------------------------*/
/* MAIN FUNCTION                                              */
/*-----------------------------------------------------------*/

/**
 * @brief Main entry point for the FreeRTOS blinky demo application.
 *
 * This function initializes the system components including keyboard handling,
 * heap memory, trace recording, and creates the application tasks and timers
 * before starting the FreeRTOS scheduler.
 *
 * @return Should never return. Returns 0 if scheduler fails to start.
 */
int main( void )
{
    const TickType_t xTimerPeriod = mainTIMER_SEND_FREQUENCY_MS;

    prvSetupKeyboardHandling();
    prvInitialiseHeap();
    prvInitialiseTrace();

    printf( "\r\nStarting FreeRTOS Blinky Demo. Press \'%c\' to reset the timer.\r\n\r\n", 
            mainRESET_TIMER_KEY );

    prvCreateApplicationQueuesAndTasks();
    prvCreateApplicationTimer( xTimerPeriod );

    vTaskStartScheduler();

    return 0;
}

/*-----------------------------------------------------------*/
/* APPLICATION SETUP FUNCTIONS                                */
/*-----------------------------------------------------------*/

/**
 * @brief Configures keyboard input handling via Windows thread.
 *
 * Sets up the interrupt handler for keyboard input and creates a separate
 * Windows thread to capture keyboard events outside the FreeRTOS simulator.
 */
static void prvSetupKeyboardHandling( void )
{
    vPortSetInterruptHandler( mainINTERRUPT_NUMBER_KEYBOARD, prvKeyboardInterruptHandler );

    xWindowsKeyboardInputThreadHandle = CreateThread(
        NULL,
        0,
        prvWindowsKeyboardInputThread,
        NULL,
        0,
        NULL );

    fflush( stdout );
    SetThreadAffinityMask( xWindowsKeyboardInputThreadHandle, ~0x01u );
}

/**
 * @brief Initializes the FreeRTOS trace recorder.
 *
 * Configures and starts the trace recording system if code coverage testing
 * is not active. The trace data can be saved to a file for analysis.
 */
static void prvInitialiseTrace( void )
{
    #if ( projCOVERAGE_TEST != 1 )
    {
        configASSERT( xTraceInitialize() == TRC_SUCCESS );

        printf(
            "Trace started.\r\n"
            "The trace uses ring buffer mode. Data will be written to \"%s\"\r\n"
            "whenever configASSERT() is called or the \'%c\' key is pressed.\r\n\r\n",
            mainTRACE_FILE_NAME, mainOUTPUT_TRACE_KEY );
        fflush( stdout );

        configASSERT( xTraceEnable( TRC_START ) == TRC_SUCCESS );
    }
    #endif
}

/**
 * @brief Creates the application queues and tasks.
 *
 * Creates the message queue for inter-task communication and spawns the
 * queue send and receive tasks with their configured priorities.
 */
static void prvCreateApplicationQueuesAndTasks( void )
{
    xQueue = xQueueCreate( mainQUEUE_LENGTH, sizeof( uint32_t ) );
    configASSERT( xQueue != NULL );

    xTaskCreate( prvQueueReceiveTask,
                 "Rx",
                 configMINIMAL_STACK_SIZE,
                 NULL,
                 mainQUEUE_RECEIVE_TASK_PRIORITY,
                 NULL );

    xTaskCreate( prvQueueSendTask,
                 "TX",
                 configMINIMAL_STACK_SIZE,
                 NULL,
                 mainQUEUE_SEND_TASK_PRIORITY,
                 NULL );
}

/**
 * @brief Creates and starts the application software timer.
 *
 * @param xTimerPeriod The period of the timer in ticks.
 */
static void prvCreateApplicationTimer( TickType_t xTimerPeriod )
{
    xTimer = xTimerCreate( "Timer",
                           xTimerPeriod,
                           pdTRUE,
                           NULL,
                           prvQueueSendTimerCallback );

    configASSERT( xTimer != NULL );
    xTimerStart( xTimer, 0 );
}

/*-----------------------------------------------------------*/
/* APPLICATION TASKS                                          */
/*-----------------------------------------------------------*/

/**
 * @brief Task that periodically sends messages to the queue.
 *
 * This task wakes up at regular intervals and sends a message to the queue.
 * It demonstrates periodic task execution using vTaskDelayUntil().
 *
 * @param pvParameters Unused task parameters (required by FreeRTOS).
 */
static void prvQueueSendTask( void * pvParameters )
{
    TickType_t xNextWakeTime;
    const TickType_t xBlockTime = mainTASK_SEND_FREQUENCY_MS;
    const uint32_t ulValueToSend = mainVALUE_SENT_FROM_TASK;
    uint32_t current_time_ms = 0;

    ( void ) pvParameters;

    xNextWakeTime = xTaskGetTickCount();

    for( ; ; )
    {
        current_time_ms = xTaskGetTickCount() * portTICK_PERIOD_MS;
        vTaskDelayUntil( &xNextWakeTime, xBlockTime );

        printf( "[%u] Message sent from task\r\n", current_time_ms );
        xQueueSend( xQueue, &ulValueToSend, 0U );
    }
}

/**
 * @brief Task that receives and processes messages from the queue.
 *
 * This task blocks on the queue waiting for messages. When a message is
 * received, it checks the value and responds accordingly.
 *
 * @param pvParameters Unused task parameters (required by FreeRTOS).
 */
static void prvQueueReceiveTask( void * pvParameters )
{
    uint32_t ulReceivedValue;
    static bool bHsInitialized = false;
    tle92104_status_t tle_status;
    uint8_t ucDeviceId = 0u;

    ( void ) pvParameters;

    /* One-time HAL and TLE92104 initialization */
    if( !bHsInitialized )
    {
        taskENTER_CRITICAL();
        {
            printf( "[RX Task] Initializing HAL...\r\n" );
            fflush( stdout );
        }
        taskEXIT_CRITICAL();

        (void)hal_init();

        tle_status = hs_init();

        taskENTER_CRITICAL();
        {
            if( tle_status == TLE92104_OK )
            {
                printf( "[RX Task] TLE92104 initialized OK\r\n" );
            }
            else
            {
                printf( "[RX Task] TLE92104 init failed (%d)\r\n", (int)tle_status );
            }
            fflush( stdout );
        }
        taskEXIT_CRITICAL();

        bHsInitialized = true;
    }

    for( ; ; )
    {
        xQueueReceive( xQueue, &ulReceivedValue, mainTASK_RECEIVE_FREQUENCY_MS );

        taskENTER_CRITICAL();
        {
            if( ulReceivedValue == mainVALUE_SENT_FROM_TIMER )
            {
                /* Service TLE92104 watchdog every 100 ms */
                tle_status = hs_service_watchdog();
                if( tle_status != TLE92104_OK )
                {
                    printf( "[RX Task] Watchdog service failed\r\n" );
                }

                /* Read device ID periodically */
                tle_status = hs_get_device_id( &ucDeviceId );
                if( tle_status == TLE92104_OK )
                {
                    printf( "[RX Task] TLE92104 DevID=0x%02X\r\n", (unsigned)ucDeviceId );
                }
            }

            ulReceivedValue = 0;
            fflush( stdout );
        }
        taskEXIT_CRITICAL();
    }
}

/*-----------------------------------------------------------*/
/* TIMER CALLBACKS                                            */
/*-----------------------------------------------------------*/

/**
 * @brief Software timer callback function.
 *
 * This callback is executed when the software timer expires. It sends a
 * message to the queue with a distinct value to identify timer-sourced messages.
 *
 * @param xTimerHandle Handle to the timer that expired (unused).
 */
static void prvQueueSendTimerCallback( TimerHandle_t xTimerHandle )
{
    const uint32_t ulValueToSend = mainVALUE_SENT_FROM_TIMER;

    ( void ) xTimerHandle;

    xQueueSend( xQueue, &ulValueToSend, 0U );
}

/*-----------------------------------------------------------*/
/* KEYBOARD HANDLING                                          */
/*-----------------------------------------------------------*/

/**
 * @brief Handles special keyboard input commands.
 *
 * Processes keyboard input for application-specific commands such as
 * resetting the software timer.
 *
 * @param xKeyPressed The key code that was pressed.
 */
static void prvHandleKeyboardInput( int xKeyPressed )
{
    switch( xKeyPressed )
    {
        case mainRESET_TIMER_KEY:
            if( xTimer != NULL )
            {
                portENTER_CRITICAL();
                {
                    printf( "\r\nResetting software timer.\r\n\r\n" );
                }
                portEXIT_CRITICAL();

                xTimerReset( xTimer, portMAX_DELAY );
            }
            break;

        default:
            break;
    }
}

/**
 * @brief Interrupt handler for keyboard input events.
 *
 * This handler is called when a keyboard interrupt is generated. It processes
 * special keys like trace output and delegates other keys to the application
 * keyboard handler.
 *
 * @return pdFALSE as this interrupt does not require a context switch.
 */
static uint32_t prvKeyboardInterruptHandler( void )
{
    switch( xKeyPressed )
    {
        case mainNO_KEY_PRESS_VALUE:
            break;

        case mainOUTPUT_TRACE_KEY:
            #if ( projCOVERAGE_TEST != 1 )
                portENTER_CRITICAL();
                {
                    ( void ) xTraceDisable();
                    prvSaveTraceFile();
                    ( void ) xTraceEnable( TRC_START );
                }
                portEXIT_CRITICAL();
            #endif
            break;

        default:
            prvHandleKeyboardInput( xKeyPressed );
            break;
    }

    return pdFALSE;
}

/**
 * @brief Windows thread function for capturing keyboard input.
 *
 * This thread runs outside the FreeRTOS simulator and blocks waiting for
 * keyboard input. When a key is pressed, it generates a simulated interrupt
 * to notify the FreeRTOS tasks.
 *
 * @param pvParam Unused thread parameter.
 * @return Should never return. Returns -1 on error.
 */
static DWORD WINAPI prvWindowsKeyboardInputThread( void * pvParam )
{
    ( void ) pvParam;

    for( ; ; )
    {
        xKeyPressed = _getch();
        vPortGenerateSimulatedInterrupt( mainINTERRUPT_NUMBER_KEYBOARD );
    }

    return -1;
}

/*-----------------------------------------------------------*/
/* FREERTOS HOOK FUNCTIONS                                    */
/*-----------------------------------------------------------*/

/**
 * @brief Hook function called when memory allocation fails.
 *
 * This hook is called if configUSE_MALLOC_FAILED_HOOK is set to 1 and
 * a call to pvPortMalloc() fails.
 */
void vApplicationMallocFailedHook( void )
{
    vAssertCalled( __LINE__, __FILE__ );
}

/**
 * @brief Idle task hook function.
 *
 * This hook is called on each iteration of the idle task if
 * configUSE_IDLE_HOOK is set to 1. Currently unused in this demo.
 */
void vApplicationIdleHook( void )
{
    /* Idle hook intentionally left empty for this demo. */
}

/**
 * @brief Stack overflow detection hook.
 *
 * This hook is called if a stack overflow is detected and
 * configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.
 *
 * @param pxTask Handle to the task that overflowed its stack.
 * @param pcTaskName Name of the task (for debugging).
 */
void vApplicationStackOverflowHook( TaskHandle_t pxTask, char * pcTaskName )
{
    ( void ) pcTaskName;
    ( void ) pxTask;

    vAssertCalled( __LINE__, __FILE__ );
}

/**
 * @brief Tick hook function called on each tick interrupt.
 *
 * This hook is called by each tick interrupt if configUSE_TICK_HOOK is
 * set to 1. Currently unused in this demo.
 */
void vApplicationTickHook( void )
{
    /* Tick hook intentionally left empty for this demo. */
}

/**
 * @brief Daemon (timer) task startup hook.
 *
 * This hook is called once when the daemon task starts executing.
 * Useful for initialization that must occur after the scheduler starts.
 */
void vApplicationDaemonTaskStartupHook( void )
{
    /* Daemon task startup hook intentionally left empty for this demo. */
}

/**
 * @brief Provides static memory for the idle task.
 *
 * This function is required when configSUPPORT_STATIC_ALLOCATION is set to 1.
 * It provides the memory buffers used by the idle task.
 *
 * @param[out] ppxIdleTaskTCBBuffer Pointer to idle task TCB buffer.
 * @param[out] ppxIdleTaskStackBuffer Pointer to idle task stack buffer.
 * @param[out] pulIdleTaskStackSize Pointer to idle task stack size.
 */
void vApplicationGetIdleTaskMemory( StaticTask_t ** ppxIdleTaskTCBBuffer,
                                    StackType_t ** ppxIdleTaskStackBuffer,
                                    uint32_t * pulIdleTaskStackSize )
{
    static StaticTask_t xIdleTaskTCB;
    static StackType_t uxIdleTaskStack[ configMINIMAL_STACK_SIZE ];

    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

/**
 * @brief Provides static memory for the timer service task.
 *
 * This function is required when both configSUPPORT_STATIC_ALLOCATION and
 * configUSE_TIMERS are set to 1. It provides the memory buffers used by
 * the timer service task.
 *
 * @param[out] ppxTimerTaskTCBBuffer Pointer to timer task TCB buffer.
 * @param[out] ppxTimerTaskStackBuffer Pointer to timer task stack buffer.
 * @param[out] pulTimerTaskStackSize Pointer to timer task stack size.
 */
void vApplicationGetTimerTaskMemory( StaticTask_t ** ppxTimerTaskTCBBuffer,
                                     StackType_t ** ppxTimerTaskStackBuffer,
                                     uint32_t * pulTimerTaskStackSize )
{
    static StaticTask_t xTimerTaskTCB;

    *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;
    *ppxTimerTaskStackBuffer = uxTimerTaskStack;
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}

/*-----------------------------------------------------------*/
/* ERROR HANDLING                                             */
/*-----------------------------------------------------------*/

/**
 * @brief Assertion failure handler.
 *
 * This function is called when a configASSERT() fails. It saves the trace
 * file and enters an infinite loop that can be exited via debugger.
 *
 * @param ulLine Line number where the assertion failed.
 * @param pcFileName Name of the file where the assertion failed.
 */
void vAssertCalled( unsigned long ulLine, const char * const pcFileName )
{
    volatile uint32_t ulSetToNonZeroInDebuggerToContinue = 0;

    ( void ) ulLine;
    ( void ) pcFileName;

    taskENTER_CRITICAL();
    {
        printf( "ASSERT! Line %ld, file %s, GetLastError() %ld\r\n", 
                ulLine, pcFileName, GetLastError() );
        fflush( stdout );

        #if ( projCOVERAGE_TEST != 1 )
        {
            ( void ) xTraceDisable();
            prvSaveTraceFile();
        }
        #endif

        while( ulSetToNonZeroInDebuggerToContinue == 0 )
        {
            __asm volatile ( "NOP" );
            __asm volatile ( "NOP" );
        }

        #if ( projCOVERAGE_TEST != 1 )
        {
            ( void ) xTraceEnable( TRC_START );
        }
        #endif
    }
    taskEXIT_CRITICAL();
}

/*-----------------------------------------------------------*/
/* TRACE FILE HANDLING                                        */
/*-----------------------------------------------------------*/

/**
 * @brief Saves trace data to a file.
 *
 * Writes the trace recorder data to a binary file for later analysis.
 * This function will overwrite any existing trace file.
 */
static void prvSaveTraceFile( void )
{
    #if ( projCOVERAGE_TEST != 1 )
    {
        FILE * pxOutputFile;

        pxOutputFile = fopen( mainTRACE_FILE_NAME, "wb" );

        if( pxOutputFile != NULL )
        {
            fwrite( RecorderDataPtr, sizeof( RecorderDataType ), 1, pxOutputFile );
            fclose( pxOutputFile );
            printf( "\r\nTrace output saved to %s\r\n", mainTRACE_FILE_NAME );
            fflush( stdout );
        }
        else
        {
            printf( "\r\nFailed to create trace dump file\r\n" );
            fflush( stdout );
        }
    }
    #endif
}

/*-----------------------------------------------------------*/
/* HEAP MANAGEMENT                                            */
/*-----------------------------------------------------------*/

/**
 * @brief Initializes the FreeRTOS heap using heap_5.
 *
 * Configures multiple heap regions for demonstration purposes. In production,
 * heap_4 with a single region would be more appropriate.
 */
static void prvInitialiseHeap( void )
{
    static uint8_t ucHeap[ configTOTAL_HEAP_SIZE ];
    volatile uint32_t ulAdditionalOffset = 19;
    HeapStats_t xHeapStats;
    const HeapRegion_t xHeapRegions[] =
    {
        { ucHeap + 1,                                          mainREGION_1_SIZE },
        { ucHeap + 15 + mainREGION_1_SIZE,                     mainREGION_2_SIZE },
        { ucHeap + 19 + mainREGION_1_SIZE + mainREGION_2_SIZE, mainREGION_3_SIZE },
        { NULL,                                                0                 }
    };

    configASSERT( ( ulAdditionalOffset + mainREGION_1_SIZE + mainREGION_2_SIZE + mainREGION_3_SIZE ) < configTOTAL_HEAP_SIZE );

    ( void ) ulAdditionalOffset;

    vPortGetHeapStats( &xHeapStats );
    vPortDefineHeapRegions( xHeapRegions );

    prvExerciseHeapStats();
}

/**
 * @brief Tests heap allocation and deallocation statistics.
 *
 * Performs several heap allocations and deallocations to verify that
 * heap statistics tracking is working correctly.
 */
static void prvExerciseHeapStats( void )
{
    HeapStats_t xHeapStats;
    size_t xInitialFreeSpace = xPortGetFreeHeapSize(), xMinimumFreeBytes;
    size_t xMetaDataOverhead, i;
    void * pvAllocatedBlock;
    const size_t xArraySize = 5, xBlockSize = 1000UL;
    void * pvAllocatedBlocks[ xArraySize ];

    vPortGetHeapStats( &xHeapStats );

    configASSERT( xHeapStats.xMinimumEverFreeBytesRemaining == xHeapStats.xAvailableHeapSpaceInBytes );
    configASSERT( xHeapStats.xMinimumEverFreeBytesRemaining == xInitialFreeSpace );
    configASSERT( xHeapStats.xNumberOfSuccessfulAllocations == 0 );
    configASSERT( xHeapStats.xNumberOfSuccessfulFrees == 0 );

    pvAllocatedBlock = pvPortMalloc( xBlockSize );
    configASSERT( pvAllocatedBlock );
    xMetaDataOverhead = ( xInitialFreeSpace - xPortGetFreeHeapSize() ) - xBlockSize;

    vPortFree( pvAllocatedBlock );
    vPortGetHeapStats( &xHeapStats );
    configASSERT( xHeapStats.xAvailableHeapSpaceInBytes == xInitialFreeSpace );
    configASSERT( xHeapStats.xNumberOfSuccessfulAllocations == 1 );
    configASSERT( xHeapStats.xNumberOfSuccessfulFrees == 1 );

    for( i = 0; i < xArraySize; i++ )
    {
        pvAllocatedBlocks[ i ] = pvPortMalloc( xBlockSize );
        configASSERT( pvAllocatedBlocks[ i ] );
        vPortGetHeapStats( &xHeapStats );
        configASSERT( xHeapStats.xMinimumEverFreeBytesRemaining == ( xInitialFreeSpace - ( ( i + 1 ) * ( xBlockSize + xMetaDataOverhead ) ) ) );
        configASSERT( xHeapStats.xMinimumEverFreeBytesRemaining == xHeapStats.xAvailableHeapSpaceInBytes );
        configASSERT( xHeapStats.xNumberOfSuccessfulAllocations == ( 2Ul + i ) );
        configASSERT( xHeapStats.xNumberOfSuccessfulFrees == 1 );
    }

    configASSERT( xPortGetFreeHeapSize() == xPortGetMinimumEverFreeHeapSize() );
    xMinimumFreeBytes = xPortGetFreeHeapSize();

    for( i = 0; i < xArraySize; i++ )
    {
        vPortFree( pvAllocatedBlocks[ i ] );
        vPortGetHeapStats( &xHeapStats );
        configASSERT( xHeapStats.xAvailableHeapSpaceInBytes == ( xInitialFreeSpace - ( ( ( xArraySize - i - 1 ) * ( xBlockSize + xMetaDataOverhead ) ) ) ) );
        configASSERT( xHeapStats.xNumberOfSuccessfulAllocations == ( xArraySize + 1 ) );
        configASSERT( xHeapStats.xNumberOfSuccessfulFrees == ( 2UL + i ) );
    }

    configASSERT( xMinimumFreeBytes == xPortGetMinimumEverFreeHeapSize() );
}

/*-----------------------------------------------------------*/
/* TRACE TIMING FUNCTIONS                                     */
/*-----------------------------------------------------------*/

static uint32_t ulEntryTime = 0;

/**
 * @brief Resets the trace timer to the current tick count.
 */
void vTraceTimerReset( void )
{
    ulEntryTime = xTaskGetTickCount();
}

/**
 * @brief Returns the trace timer frequency in Hz.
 *
 * @return The configured tick rate.
 */
uint32_t uiTraceTimerGetFrequency( void )
{
    return configTICK_RATE_HZ;
}

/**
 * @brief Returns the elapsed tick count since the timer was reset.
 *
 * @return Number of ticks elapsed since vTraceTimerReset() was called.
 */
uint32_t uiTraceTimerGetValue( void )
{
    return( xTaskGetTickCount() - ulEntryTime );
}