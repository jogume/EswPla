/** ***************************************************************************
 * \file            yolpiya.h
 * \brief           Common definitions for all ecu sw
 * \author          gavadvi
 * \compiler        all compilers used in electronic development
 * \controller      all CPUs used in electronic development
 *****************************************************************************/

/**** include guard **********************************************************/
#ifndef YOLPIYA_H
#define YOLPIYA_H

/**
  * \necessity C++ message suppressed for legacy C support
  * \safety Still valid C/C++ code
  */ /* PRQA S 1020,1025,1014,1026,1038,1039,2400 EOF */

/**** includes ****************************************************************/
#if defined(__cplusplus)
#include <climits>
#else
#include <limits.h>
#endif

/* standard true and false definition*/
#define YOLPIYA_FALSE     (0U)            /**< In expressions 0 is considered as false */
#define YOLPIYA_TRUE      (!YOLPIYA_FALSE)  /**< In expressions values not 0 are considered as true */

#ifdef WIN32
/**
 * \brief       PC compile true and false definition
 * \details     If software is compiled as PC application the true and false definition
 *              is overwritten.
 */
  #undef        TRUE
  #undef        FALSE
  #define TRUE  YOLPIYA_TRUE
  #define FALSE YOLPIYA_FALSE
#endif

/**** type declarations ***************************************************************************/
/**
 * \brief       Define standard types only if not yet defined
 * \details     Avoid double declaration for modules that have their one type
 *              definition. E.g. the independently delivered anti trap module.
 */

/** \necessity  Exact definition of size macros in limits.h depends on compiler
 *              implementation
 *  \safety     Pre-processor only and no integer arithmetic is performed. No
 *              influence on implicit type casts.
 */ /* PRQA S 1281 YOLPIYA_QAC_TYPEDEF */

  /* *** 8 bit data type **************************************************************************/

  /* *** 16 bit data type *************************************************************************/

  /* *** 32 bit data type *************************************************************************/

  /* *** 64 bit data type *************************************************************************/
/** \necessity  The 64-bit unsigned data type is needed in project using 32-bit architectures
 *  \safety     long long is a C99 extension and is only activated if available
 */ /* PRQA S 0047,0048,0580,1018,1027 YOLPIYA_QAC_64BIT*/
    /* PRQA L: YOLPIYA_QAC_64BIT */
  /* PRQA L: YOLPIYA_QAC_TYPEDEF */


/***  CPU type dependent defines  *****************************************************************/
#define YOLPIYA_CPU_DFLT              0U        /**< Default or generic CPU      */

#define YOLPIYA_CPU_FS_S08            1U        /**< NXP (Freescale) Star08 CPU  */
#define YOLPIYA_CPU_FS_S12            2U        /**< NXP (Freescale) Star12 CPU  */
#define YOLPIYA_CPU_FS_S12X           3U        /**< NXP (Freescale) Star12X CPU */
#define YOLPIYA_CPU_FS_PPC            4U        /**< NXP (Freescale) PowerPC CPU */
#define YOLPIYA_CPU_FS_S12Z           5U        /**< NXP (Freescale) Star12Z CPU */
#define YOLPIYA_CPU_FS_S32K           6U        /**< NXP (Freescale) S32K CPU    */
#define YOLPIYA_CPU_RN_RL78           7U        /**< Renesas         RL78 CPU    */
#define YOLPIYA_CPU_X86_64            8U        /**< Intel           X86 CPU     */

/*** Architecture dependent defines ***************************************************************/
#define YOLPIYA_ARCH_NO               0U

#define YOLPIYA_ARCH_COSMIC_S08       1U
#define YOLPIYA_ARCH_COSMIC_S12       2U
#define YOLPIYA_ARCH_COSMIC_S12X      3U
#define YOLPIYA_ARCH_COSMIC_S12Z      4U
#define YOLPIYA_ARCH_GCC_S32K         5U
#define YOLPIYA_ARCH_GCC_X86_64       6U
#define YOLPIYA_ARCH_GHS_PPC          7U
#define YOLPIYA_ARCH_IAR_S32K         8U
#define YOLPIYA_ARCH_IAR_RL78         9U
#define YOLPIYA_ARCH_METROW_S12X     10U
#define YOLPIYA_ARCH_MSC_X86_64      11U


/**
 * \brief   Macro value indicating reverse bit order in structs
 * \details Filling of the bits is started with bit0 of the bit field to the MSB of the underlying byte.*/
#define YOLPIYA_REVERSE   0U

/**
 * \brief   Macro value indicating identical bit order in structs
 * \details Filling of the bits starts with bit0 of the bit field to the LSB of the underlying byte.*/
#define YOLPIYA_IDENTICAL 1U

/**
 * \brief   Macro value indicating Little-Endian byte order
 * \details Little-Endian is known as the Intel byte order. Start with the least significant
 *          byte in the lowest address.*/
#define YOLPIYA_LITTLE_ENDIAN 0U

/**
 * \brief   Macro value indicating Big-Endian byte order
 * \details Big-Endian is known as the Motorola byte order. Start with the most significant
 *          byte in the lowest address.*/
#define YOLPIYA_BIG_ENDIAN 1U


/*** Type modifiers with name space ***************************************************************/
/**
 * \brief       Type modifier for private variables and functions
 * \details     Variables and functions are then visible only at file scope.
 * \note        If used in headers the compile will perhaps silently fail.
 */
#define YOLPIYA_PRIVATE static

/** \necessity  Compiler extension for embedded systems programming
 *  \safety     Extensions dedicated for every compiler are done and tested.
 */  /* PRQA S 289, 0628, 3453 YOLPIYA_COMP_EX */
/** \necessity  One to one textual replacement is required and not further macro evaluation
 *  \safety     Only one # operator is used and it performs the intended functionality.
 */ /* PRQA S 341 YOLPIYA_COMP_EX */

/**
 * \brief       Concatenate two macros and evaluate it
 * \details     Needed if a \#define is assembled out of two parts and evaluated then.
 */
#define YOLPIYA_STRINGIFY(string)   #string

#if defined(__CSMC__)
  /* COSMIC compiler for different cpus */
  #if !defined(TESSY)
    #define YOLPIYA_ADDRESS(ap_address)   @(ap_address)
    #define YOLPIYA_CONST                 const
  #endif
  #define YOLPIYA_ASM(as_Command)         _asm( #as_Command )
  #define YOLPIYA_FUNC_INLINE             @inline

  #if defined (__CPU_S08__)
    #define YOLPIYA_CPU_TYPE              YOLPIYA_CPU_FS_S08
    #define YOLPIYA_ARCH_TYPE             YOLPIYA_ARCH_COSMIC_S08
    #if !defined(TESSY)
      #define YOLPIYA_FUNC_ISR            @interrupt @svlreg
    #endif
    #define YOLPIYA_FUNC_NEAR             @near
    #define YOLPIYA_FUNC_FAR              @far
    #define YOLPIYA_VAR_BIT               @tiny
    #define YOLPIYA_VAR_DIRECT            @tiny
    #define YOLPIYA_VAR_NEAR
    #define YOLPIYA_VAR_FAR
    #include <stdbool.h>
    #include "yolpiya_stdint.h"

  #elif defined (__CPU_S12__) || defined(__CPU_S12X__)
    #if defined (__CPU_S12__)
      #define YOLPIYA_CPU_TYPE            YOLPIYA_CPU_FS_S12
      #define YOLPIYA_ARCH_TYPE           YOLPIYA_ARCH_COSMIC_S12
    #else
      #define YOLPIYA_CPU_TYPE            YOLPIYA_CPU_FS_S12X
      #define YOLPIYA_ARCH_TYPE           YOLPIYA_ARCH_COSMIC_S12X
    #endif
    #if !defined(TESSY)
      #define YOLPIYA_FUNC_ISR            @near @interrupt
    #endif
    #define YOLPIYA_FUNC_NEAR             @near
    #define YOLPIYA_FUNC_FAR              @far
    #define YOLPIYA_VAR_BIT               @dir
    #define YOLPIYA_VAR_DIRECT            @dir
    #define YOLPIYA_VAR_NEAR
    #define YOLPIYA_VAR_FAR               @far

    #include "yolpiya_stdint.h"
  #elif defined (__CPU_S12Z__)
    #define YOLPIYA_CPU_TYPE              YOLPIYA_CPU_FS_S12Z
    #define YOLPIYA_ARCH_TYPE             YOLPIYA_ARCH_COSMIC_S12Z
    #if !defined(TESSY)
      #define YOLPIYA_FUNC_ISR            @interrupt
    #endif
    #define YOLPIYA_FUNC_NEAR
    #define YOLPIYA_FUNC_FAR
    #define YOLPIYA_VAR_BIT
    #define YOLPIYA_VAR_DIRECT
    #define YOLPIYA_VAR_NEAR
    #define YOLPIYA_VAR_FAR
    #define YOLPIYA_VECTOR                @vector
    #include <stdint.h>
    #include <stdbool.h>

  #else
    #error "CPU_TYPE not valid"
  #endif

  #define YOLPIYA_BYTE_ORDER YOLPIYA_BIG_ENDIAN

  #if (__CSMC__ & 0x10)
    #define YOLPIYA_BIT_ORDER             YOLPIYA_REVERSE
  #else
    #define YOLPIYA_BIT_ORDER             YOLPIYA_IDENTICAL
  #endif

#elif defined(__MWERKS__)
  /* METROWERKS compiler for S12/X cpu*/
  #define YOLPIYA_CPU_TYPE                YOLPIYA_CPU_FS_S12X
  #define YOLPIYA_ARCH_TYPE               YOLPIYA_ARCH_METROW_S12X
  #if !defined(TESSY)
    #define YOLPIYA_FUNC_ISR              interrupt
    #define YOLPIYA_CONST                 const
  #endif
  #define YOLPIYA_FUNC_NEAR
  #define YOLPIYA_FUNC_FAR                far
  #define YOLPIYA_FUNC_INLINE
  #define YOLPIYA_VAR_BIT
  #define YOLPIYA_VAR_DIRECT
  #define YOLPIYA_VAR_NEAR
  #define YOLPIYA_VAR_FAR                 far
  #define YOLPIYA_ASM(as_Command)         {asm as_Command;}
  #define YOLPIYA_ADDRESS(ap_address)     @ap_address

  #include "yolpiya_stdint.h"

  #if defined(__BIG_ENDIAN__)
    #define YOLPIYA_BYTE_ORDER            YOLPIYA_BIG_ENDIAN
  #else
    #error "No correct endianess definition!!!"
  #endif

  #if defined(__BITFIELD_LSBIT_FIRST__)
    #define YOLPIYA_BIT_ORDER             YOLPIYA_IDENTICAL
  #elif defined(__BITFIELD_MSBIT_FIRST__)
    #define YOLPIYA_BIT_ORDER             YOLPIYA_REVERSE
  #else
    #error "No correct bit order definition!!!"
  #endif

#elif defined(__ghs__)
  /* Greehills compiler for the ppc cpu*/
  #if !defined(TESSY)
    #define YOLPIYA_CONST                 const
  #endif
   #define YOLPIYA_ASM(as_Command)         asm( #as_Command )
   #define YOLPIYA_BEGIN_PACK(n)           _Pragma(YOLPIYA_STRINGIFY(pack(n)))
   #define YOLPIYA_END_PACK()              _Pragma(YOLPIYA_STRINGIFY(pack()))
  #if defined(__PowerPC__)
    #define YOLPIYA_CPU_TYPE                YOLPIYA_CPU_FS_PPC
    #define YOLPIYA_ARCH_TYPE               YOLPIYA_ARCH_GHS_PPC
    #define YOLPIYA_FUNC_ISR
    #define YOLPIYA_FUNC_NEAR
    #define YOLPIYA_FUNC_FAR
    #define YOLPIYA_FUNC_INLINE             inline
    #define YOLPIYA_VAR_BIT
    #define YOLPIYA_VAR_DIRECT
    #define YOLPIYA_VAR_NEAR
    #define YOLPIYA_VAR_FAR
    #include <stdbool.h>
    #if defined(__BIG_ENDIAN__)
      #define YOLPIYA_BYTE_ORDER            YOLPIYA_BIG_ENDIAN
    #else
      #error "No correct endianess definition!!!"
    #endif
    #define YOLPIYA_BIT_ORDER YOLPIYA_REVERSE

  #elif defined(__V850__)
    #define YOLPIYA_CPU_TYPE                YOLPIYA_CPU_FS_V850
    #define YOLPIYA_ARCH_TYPE               YOLPIYA_ARCH_GHS_V850
    #define YOLPIYA_FUNC_ISR
    #define YOLPIYA_FUNC_NEAR
    #define YOLPIYA_FUNC_FAR
    #define YOLPIYA_FUNC_INLINE             inline
    #define YOLPIYA_VAR_BIT
    #define YOLPIYA_VAR_DIRECT
    #define YOLPIYA_VAR_NEAR
    #define YOLPIYA_VAR_FAR
    #include <stdbool.h>

    #if (__LITTLE_ENDIAN__ == 1)
      #define YOLPIYA_BYTE_ORDER          YOLPIYA_LITTLE_ENDIAN
    #else
      #error "No correct endianess definition!!!"
    #endif
    #define YOLPIYA_BIT_ORDER             YOLPIYA_IDENTICAL

  #else
    #error "CPU_TYPE not valid"
  #endif

  #include "stdint.h"

#elif defined(__IAR_SYSTEMS_ICC__)
    #if !defined(TESSY)
      #define YOLPIYA_CONST               const
      #define YOLPIYA_ADDRESS(ap_address) @ap_address
    #endif
    #define YOLPIYA_BEGIN_PACK(n)         _Pragma(YOLPIYA_STRINGIFY(pack(n)))
    #define YOLPIYA_END_PACK()            _Pragma(YOLPIYA_STRINGIFY(pack()))
    #define YOLPIYA_ALIGNED(BITS)         _Pragma(YOLPIYA_STRINGIFY(data_alignment=BITS))
    #define YOLPIYA_FORCED_INLINE         _Pragma("inline=forced") inline
    #if defined(__ICCARM__)
      /* IAR compiler for the arm s32k cpu*/
      #define YOLPIYA_CPU_TYPE            YOLPIYA_CPU_FS_S32K
      #define YOLPIYA_ARCH_TYPE           YOLPIYA_ARCH_IAR_S32K
      #define YOLPIYA_FUNC_ISR            __irq
      #define YOLPIYA_FUNC_NEAR
      #define YOLPIYA_FUNC_FAR
      #define YOLPIYA_FUNC_INLINE         inline
      #define YOLPIYA_VAR_BIT
      #define YOLPIYA_VAR_DIRECT
      #define YOLPIYA_VAR_NEAR
      #define YOLPIYA_VAR_FAR
      #define YOLPIYA_ASM(as_Command)     asm( #as_Command )
    #elif defined(__ICCRL78__)
      /* IAR compiler for the rl78 cpu*/
      #define YOLPIYA_CPU_TYPE            YOLPIYA_CPU_RN_RL78
      #define YOLPIYA_ARCH_TYPE           YOLPIYA_ARCH_IAR_RL78
      #define YOLPIYA_FUNC_ISR            __interrupt
      #define YOLPIYA_FUNC_NEAR           __near_func
      #define YOLPIYA_FUNC_FAR            __far_func
      #define YOLPIYA_FUNC_INLINE         inline
      #define YOLPIYA_VAR_BIT
      #define YOLPIYA_VAR_DIRECT          __saddr
      #define YOLPIYA_VAR_NEAR            __near
      #define YOLPIYA_VAR_FAR             __far
      #define YOLPIYA_ASM(as_Command)     asm( #as_Command )
    #else
      #error "CPU_TYPE not valid"
    #endif

    #if (__LITTLE_ENDIAN__ == 1)
      #define YOLPIYA_BYTE_ORDER          YOLPIYA_LITTLE_ENDIAN
    #else
      #error "No correct endianess definition!!!"
    #endif

    #define YOLPIYA_BIT_ORDER             YOLPIYA_IDENTICAL
    #include <stdbool.h>
    #include <stdint.h>
#elif defined(__GNUC__)
  /* GNU C Compiler */

  #if !defined(TESSY)
    #define YOLPIYA_CONST                 const
  #endif
  #define YOLPIYA_FUNC_ISR
  #define YOLPIYA_FUNC_NEAR
  #define YOLPIYA_FUNC_FAR
  #define YOLPIYA_FUNC_INLINE             inline
  #define YOLPIYA_VAR_BIT
  #define YOLPIYA_VAR_DIRECT
  #define YOLPIYA_VAR_NEAR
  #define YOLPIYA_VAR_FAR
  #define YOLPIYA_VECTOR
  #define YOLPIYA_ASM(as_Command)
  #define YOLPIYA_ADDRESS(ap_address)
  #define YOLPIYA_BEGIN_PACK(n)           _Pragma(YOLPIYA_STRINGIFY(pack(n)))
  #define YOLPIYA_END_PACK()              _Pragma(YOLPIYA_STRINGIFY(pack()))
  #define YOLPIYA_ALIGNED(BITS)           __attribute__((aligned(BITS)))
  #define YOLPIYA_FORCED_INLINE           __attribute__((always_inline)) inline

  #if defined(DERIV_S32K)
    #define YOLPIYA_CPU_TYPE              YOLPIYA_CPU_FS_S32K
    #define YOLPIYA_ARCH_TYPE             YOLPIYA_ARCH_GCC_S32K
    #if (__BYTE_ORDER__==__ORDER_LITTLE_ENDIAN__)
      #define YOLPIYA_BYTE_ORDER          YOLPIYA_LITTLE_ENDIAN
      #define YOLPIYA_BIT_ORDER           YOLPIYA_IDENTICAL
    #else
      #error "No correct endianess definition!!!"
    #endif
  #else
    #define YOLPIYA_CPU_TYPE              YOLPIYA_CPU_X86_64
    #define YOLPIYA_ARCH_TYPE             YOLPIYA_ARCH_GCC_X86_64
  #endif

  #if defined(__cplusplus)
    #include <cstdint>
  #else
    #include <stdint.h>
  #endif


  #include <stdbool.h>

#elif defined(_MSC_VER)
  #define YOLPIYA_CPU_TYPE                YOLPIYA_CPU_X86_VS
  #define YOLPIYA_ARCH_TYPE               YOLPIYA_ARCH_MSC_X86_64
  #if !defined(TESSY)
    #define YOLPIYA_CONST                 const
  #endif
  #define YOLPIYA_FUNC_ISR
  #define YOLPIYA_FUNC_NEAR
  #define YOLPIYA_FUNC_FAR
  #define YOLPIYA_FUNC_INLINE              _inline
  #define YOLPIYA_VAR_BIT
  #define YOLPIYA_VAR_DIRECT
  #define YOLPIYA_VAR_NEAR
  #define YOLPIYA_VAR_FAR
  #define YOLPIYA_VECTOR
  #define YOLPIYA_ASM(as_Command)
  #define YOLPIYA_ADDRESS(ap_address)

  #include <stdint.h>
  #include <stdbool.h>

#else
  #define YOLPIYA_CPU_TYPE                YOLPIYA_DFLT_CPU
  #if !defined(TESSY)
    #define YOLPIYA_CONST                 const
  #endif
  #define YOLPIYA_FUNC_ISR
  #define YOLPIYA_FUNC_NEAR
  #define YOLPIYA_FUNC_FAR
  #define YOLPIYA_FUNC_INLINE             inline
  #define YOLPIYA_VAR_BIT
  #define YOLPIYA_VAR_DIRECT
  #define YOLPIYA_VAR_NEAR
  #define YOLPIYA_VAR_FAR
  #define YOLPIYA_VECTOR
  #define YOLPIYA_ASM(as_Command)
  #define YOLPIYA_ADDRESS(ap_address)

  #include <stdint.h>
  #include <stdbool.h>

#endif

/* PRQA L: YOLPIYA_COMP_EX */

/**** type declarations ***************************************************************************/
#ifndef YOLPIYA_TYPES
/**
 * \brief       Define standard types only if not yet defined
 * \details     Avoid double declaration for modules that have their one type
 *              definition. E.g. the independently delivered anti trap module.
 */
  #define YOLPIYA_TYPES

  typedef unsigned char UNUM1;          /**< Single bit data type for bit field declaration */

/* *** 8 bit data type **************************************************************************/
  typedef uint8_t UNUM8;               /**< Unsigned type with fixed 8 bit length   */
  typedef  int8_t SNUM8;               /**< Signed type with fixed 8 bit length     */
  #define YOLPIYA_UNUM8_MIN 0U           /**< Minimum size of the unsigned 8 bit type */
  #define YOLPIYA_UNUM8_MAX 255U         /**< Maximum size of the unsigned 8 bit type */
  #define YOLPIYA_SNUM8_MIN (-1-127)     /**< Minimum size of the signed 8 bit type   */
  #define YOLPIYA_SNUM8_MAX 127          /**< Maximum size of the signed 8 bit type   */

/* *** 16 bit data type *************************************************************************/
  typedef uint16_t UNUM16;             /**< Unsigned type with fixed 16 bit length   */
  typedef  int16_t SNUM16;             /**< Signed type with fixed 16 bit length     */
  #define YOLPIYA_UNUM16_MIN 0U          /**< Minimum size of the unsigned 16 bit type */
  #define YOLPIYA_UNUM16_MAX 65535U      /**< Maximum size of the unsigned 16 bit type */
  #define YOLPIYA_SNUM16_MIN (-1-32767)  /**< Minimum size of the signed 16 bit type   */
  #define YOLPIYA_SNUM16_MAX 32767       /**< Maximum size of the signed 16 bit type   */

/* *** 32 bit data type *************************************************************************/
  typedef uint32_t UNUM32;                                /**< Unsigned type with fixed 32 bit length   */
  typedef  int32_t SNUM32;                                /**< Signed type with fixed 32 bit length     */
  #define YOLPIYA_UNUM32_MIN  0u                            /**< Minimum size of the unsigned 32 bit type */
  #define YOLPIYA_UNUM32_MAX  4294967295U                   /**< Maximum size of the unsigned 32 bit type */
  #define YOLPIYA_SNUM32_MIN (-1L-2147483647L)              /**< Minimum size of the signed 32 bit type   */
  #define YOLPIYA_SNUM32_MAX  2147483647L                   /**< Maximum size of the signed 32 bit type   */

/* *** 64 bit data type *************************************************************************/
  #if defined(ULLONG_MAX)
/** \necessity  The 64-bit unsigned data type is needed in project using 32-bit architectures
 *  \safety     long long is a C99 extension and is only activated if available
 */ /* PRQA S 0047,0048,0580,1018,1027 YOLPIYA_QAC_64BIT*/
    typedef uint64_t UNUM64;                              /**< Unsigned type with fixed 64 bit length   */
    typedef  int64_t SNUM64;                              /**< Signed type with fixed 64 bit length     */
    #define YOLPIYA_UNUM64_MIN 0ULL                         /**< Minimum size of the unsigned 64 bit type */
    #define YOLPIYA_UNUM64_MAX 0xffffffffffffffffU          /**< Maximum size of the unsigned 64 bit type */
    #define YOLPIYA_SNUM64_MIN (-1L-9223372036854775807LL)  /**< Minimum size of the signed 64 bit type   */
    #define YOLPIYA_SNUM64_MAX  9223372036854775807LL       /**< Maximum size of the signed 64 bit type   */
    /* PRQA L: YOLPIYA_QAC_64BIT */
  #endif
  /* PRQA L: YOLPIYA_QAC_TYPEDEF */

#endif


/*** Public definition for constants **************************************************************/
/**
 * \brief       Extern declaration of YOLPIYA_CONST type modifier
 * \details     Used for declaration of linking and post build calibration parameters. In Tessy mode
 *              the they are generated as normal variables.
 */
#define YOLPIYA_PUBLIC_CONST              extern YOLPIYA_CONST

/* Options common to both TESSY_GCC and TESSY_TARGET */
#if defined(TESSY) || defined (DOXYGEN)
  /**
   * \brief	    Return type for YOLPIYA_TsModifyFunc()
   * \details   Container to return data of different type but using only one generic YOLPIYA_TsModifyFunc() stub function.
   */
  typedef struct
  {
    UNUM8   u8_Type;                    /**< Container for any 8 bit unsigned data type */
    UNUM16 u16_Type;                    /**< Container for any 16 bit unsigned data type */
    UNUM32 u32_Type;                    /**< Container for any 32 bit unsigned data type */
  #if defined(YOLPIYA_UNUM64_MAX)
    UNUM64 u64_Type;                    /**< Container for any 64 bit unsigned data type */
  #endif
    SNUM8   s8_Type;                    /**< Container for any 8 bit signed data type */
    SNUM16 s16_Type;                    /**< Container for any 16 bit signed data type */
    SNUM32 s32_Type;                    /**< Container for any 32 bit signed data type */
  #if defined(YOLPIYA_UNUM64_MAX)
    SNUM64 s64_Type;                    /**< Container for any 64 bit signed data type */
  #endif
  } YOLPIYA_TsModifyFuncReturnT;

  /**
   * \brief     Control variable for endless loop unrolling
   * \details   The variable controls the execution cycle of endless loops in Tessy mode
   *            as part of the test vector.
   */
  extern UNUM8 YOLPIYA_gu8_TsLoopCount;

  /**
   * \brief     Generic stub function for in test step variable access
   * \details   For e.g. test of register polling with timeout it is necessary to modify a variable or register
   *            within one test step of different loop executions. The YOLPIYA_TsModifyFunc is added as a stub
   *            and can be implemented in Tessy with user code.
   */
  extern YOLPIYA_TsModifyFuncReturnT YOLPIYA_TsModifyFunc(void);

  /**
   * \brief     Tessy controlled endless loop unrolling
   * \details   Endless loops are not executable in Tessy. The test case processing is completely
   *            blocked. Therefore it is replaced by a for loop in Tessy mode.
   */
  #define YOLPIYA_ELOOP() for(;YOLPIYA_gu8_TsLoopCount > 0;YOLPIYA_gu8_TsLoopCount--)

  /** \brief    Tessy stub function to modify code variables */
  #define YOLPIYA_TSMODIFYFUNC(var,type) var=(YOLPIYA_TsModifyFunc()).type

  /**
   * \brief     No fixed addresses in Tessy mode
   * \details   Fix mapped variables might lead to problems in Tessy tests. E.g. if read write operations to SFRs
   *            are used test behavior depends on hardware. If address operator is removed SRFs become global
   *            and can be tested without problems.
   */
  #define YOLPIYA_ADDRESS(ap_address)

  /**
   * \brief     Converted ISR to normal routines in Tessy mode
   * \details   The return from interrupt added to ISR is disturbing the Tessy test execution.
   */
  #define YOLPIYA_FUNC_ISR

  /**
   * \brief     Make global variables none writable accessible to Tessy
   * \details   If the const qualifier is removed in Tessy mode the variable will become
   *            global variable in RAM. It is then possible to configured them as part
   *            of the test vectors.
   */
  #define YOLPIYA_CONST

#else
/**
 * \brief       No endless loop unrolling outside Tessy
 * \necessity   Unrolling of endless loop is required for Tessy
 * \safety      Very limited and constraint use only
 */ /* PRQA S 3412 1*/
  #define YOLPIYA_ELOOP()  while(1)

  /** \brief Remove Tessy stub function for variable modification */
  #define YOLPIYA_TSMODIFYFUNC(var,type)
#endif


/*** C++ extensions *******************************************************************************/
#if defined(__cplusplus)
  /**
   * \brief     C to C++ interface declaration
   * \details   If C functions are called from C++ they must be declared as extern "C". This is activated
   *            the header is compiled the C++ compiler and predefined macro __cplusplus exists.
   */
  #define YOLPIYA_BEGIN_CDECLS  extern "C" {
  #define YOLPIYA_END_CDECLS    }         /**< End compound statement of C to C++ interface */
#else
  /**
   * \brief     C to C++ interface declaration
   * \details   If C functions are called from C++ they must be declared as extern "C". This is deactivated
   *            the header is compiled the C compiler and predefined macro __cplusplus is not existing.
   */
  #define YOLPIYA_BEGIN_CDECLS
  #define YOLPIYA_END_CDECLS              /**< No end compound statement of C to C++ interface */
#endif

/*** Old version without namespace for compatibility **********************************************/
#ifdef __YOLPIYA_BACK_COMPAT__

  /*** check if TRUE and FALSE is already defined for backward compatibility **********************/
  #ifndef FALSE
    #define FALSE    YOLPIYA_FALSE       /**< FALSE definition redefined to standard definition */
  #endif

  #ifndef TRUE
    #define TRUE      YOLPIYA_TRUE        /**< TRUE definition redefined to standard definition */
  #endif

  #ifndef VECTOR
    #define VECTOR    YOLPIYA_VECTOR      /**< Redefine deprecated reset vector type modifier */
  #endif

  #ifndef DIRECT
    #define DIRECT    YOLPIYA_VAR_DIRECT  /**< Redefine deprecated direct addressing type modifier */
  #endif

  #ifndef NEAR
    #define NEAR      YOLPIYA_FUNC_NEAR   /**< Redefine deprecated near addressing type modifier */
  #endif

  #ifndef FAR
    #define FAR       YOLPIYA_FUNC_FAR    /**< Redefine deprecated far addressing type modifier */
  #endif

  #ifndef PRIVATE
    #define PRIVATE   YOLPIYA_PRIVATE     /**<  Redefine deprecated private fucntion and variable type modifier */
  #endif

  #ifndef INTERRUPT
    #define INTERRUPT YOLPIYA_FUNC_ISR    /**< Redefine deprecated interrupt service function type modifier */
  #endif

  #ifndef INLINE
    #define INLINE    YOLPIYA_FUNC_INLINE /**< Redefine deprecated inline function type modifier */
  #endif

#endif


/*** Defines for model based development tools  ***************************************************/
#if defined(__LCC__)
  #define __MATLAB2007__                /**< Use matlab2007 instead of matlab2009 */
#endif

/*** Static Assert Macro for Assertion Check during Compilation ****************************/
#ifndef NDEBUG
/**
 * \necessity   The static assert is not of the shelf supported by C. All published applications
 *              utilizing a kind typedef. In addition by the stringify The macro is redefined with
 *              every invocation.
 * \safety      No code is generated out of it and it can be deactivated for production code
 */ /* PRQA S 0341, 0845, 3614, 3453, 3412 YOLPIYA_QAC_SASSERT */
  #define YOLPIYA_STATIC_ASSERT(condition) typedef UNUM8 YOLPIYA_STATIC_ASSERT_CONCAT(YOLPIYA_gu8_AssertFailedInLine,__LINE__)[(condition)?1:-1];
  #define YOLPIYA_STATIC_ASSERT_CONCAT(X,Y) YOLPIYA_STATIC_ASSERT_CONCAT_LINE(X,Y)
  #define YOLPIYA_STATIC_ASSERT_CONCAT_LINE(X,Y) X##Y
  /* PRQA L: YOLPIYA_QAC_SASSERT */
#else
  #define YOLPIYA_STATIC_ASSERT(condition) /**< Remove static assert in case of no debug is set */
#endif

/***  Specific defines for memory mapping  ********************************************************/
#ifdef YOLPIYA_VECTOR
/**
 * \def         YOLPIYA_VECTOR
 * \brief       Used only with the interrupt vector table to create addresses.
 */
#endif

#ifdef YOLPIYA_CONST
/**
 * \def         YOLPIYA_CONST
 * \brief       Make global variables none writable
 * \details     Variables that are used for configuration purpose and have global scope will
 *              be optimized by ROM placement.
 */
#endif

#ifdef YOLPIYA_ADDRESS
/**
 * \def         YOLPIYA_ADDRESS(ap_address)
 * \brief       Type modifier for placement at a dedicated address
 * \details     If variables are used to access hardware registers they have to be placed at
 *              dedicated address.
 */
#endif

#ifdef YOLPIYA_ASM
/**
 * \def         YOLPIYA_ASM(as_Command)
 * \brief       One operation inline assembler
 * \details     Inserts single operation inline assembly C code. E.g.YOLPIYA_ASM(nop).
 * \note        Do not use quotes!
 */
#endif

#ifdef YOLPIYA_FUNC_ISR
/**
 * \def         YOLPIYA_FUNC_ISR
 * \brief       The function is generated as a interrupt service routine (ISR). (i.e. a return from interrupt is
 *              generated instead of a return from sub routine.
 */
#endif

#ifdef YOLPIYA_FUNC_FAR
/**
 * \def         YOLPIYA_FUNC_FAR
 * \brief       Function is placed in area with far or banked addressing mode. (i.e. Star12X with 24 bit addresses)
 */
#endif

#ifdef YOLPIYA_FUNC_NEAR
/**
 * \def         YOLPIYA_FUNC_NEAR
 * \brief       Function is placed in area with near mode addressing (i.e. not with banked mode)
 */
#endif

#ifdef YOLPIYA_FUNC_INLINE
/**
 * \def         YOLPIYA_FUNC_INLINE
 * \brief       Function is realized with code inlining. Argument passing is optimized.
 */
#endif

#ifdef YOLPIYA_VAR_BIT
/**
 * \def         YOLPIYA_VAR_BIT
 * \brief       Variable is placed in bit accessible area
 */
#endif

#ifdef YOLPIYA_VAR_DIRECT
/**
 * \def         YOLPIYA_VAR_DIRECT
 * \brief       Variable is placed in area with short addressing (e.g. zero page RAM)
 */
#endif

#ifdef YOLPIYA_VAR_NEAR
/**
 * \def         YOLPIYA_VAR_NEAR
 * \brief       Variable is placed in area with normal addressing (e.g. internal RAM)
 */
#endif

#ifdef YOLPIYA_VAR_FAR
/**
 * \def         YOLPIYA_VAR_FAR
 * \brief       Variable is placed in area with extended addressing (e.g. bank switch, indirect access) */
#endif

#ifdef YOLPIYA_CPU_TYPE
/**
 * \def         YOLPIYA_CPU_TYPE
 * \brief       Unified predefined macro for CPU
 * \details     The compilers have predefined macros indication the CPU type they compile for. However,
 *              the macros vary from compiler to compilers. The YOLPIYA_CPU_TYPE provides and CPU identifier
 *              in an unique and standardized way. Easy to use in conditional compile.
 */
#endif

#ifdef YOLPIYA_BYTE_ORDER
/**
 * \def         YOLPIYA_BYTE_ORDER
 * \brief       Macro reveals the endiness of the target the code is compile for.*/
#endif

#ifdef YOLPIYA_BIT_ORDER
/**
 * \def         YOLPIYA_BIT_ORDER
 * \brief       Macro reveals the bit order in structures of the target the code is compile for.*/
#endif

#endif

/**** end of file *********************************************************************************/






