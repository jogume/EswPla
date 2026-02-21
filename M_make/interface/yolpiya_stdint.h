/**
 * \brief           Definition of standard integers type for compilers without stdint.h
 * \compiler        all compilers used in electronic development
 * \controller      all CPUs used in electronic development
 * \file            yolpiya_stdint.h
 */
#ifndef YOLPIYA_STDINT_H
#define YOLPIYA_STDINT_H


/**** includes ************************************************************************************/
#include "limits.h"


/**** type declarations ***************************************************************************/
/** \necessity  Exact definition of size macros in limits.h depends on compiler
*              implementation
*  \safety     Pre-processor only and no integer arithmetic is performed. No
*              influence on implicit type casts.
*/ /* PRQA S 1281 YOLPIYA_QAC_TYPEDEF */

#if (UCHAR_MAX==255U)
  typedef unsigned char uint8_t;         /**< Unsigned type with fixed 8 bit length   */
  typedef   signed char  int8_t;         /**< Signed type with fixed 8 bit length     */
#else
  #error "No correct typedef for 8 bit data types!!!"
#endif

/* *** 16 bit data type *************************************************************************/
#if (USHRT_MAX==65535U)
  typedef unsigned short uint16_t;       /**< Unsigned type with fixed 16 bit length   */
  typedef   signed short  int16_t;       /**< Signed type with fixed 16 bit length     */
#else
  #error "No correct typedef for 16 bit data types!!!"
#endif

/* *** 32 bit data type *************************************************************************/
#if (ULONG_MAX==4294967295UL)
  typedef unsigned long uint32_t;       /**< Unsigned type with fixed 32 bit length   */
  typedef   signed long  int32_t;       /**< Signed type with fixed 32 bit length     */
#else
  #error "No correct typedef for 32 bit data types!!!"
#endif

/* *** 64 bit data type *************************************************************************/
#if defined(ULLONG_MAX)
/** \necessity  The 64-bit unsigned data type is needed in project using 32-bit architectures
 *  \safety     long long is a C99 extension and is only activated if available
 */ /* PRQA S 0047,0048,0580,1018,1027 YOLPIYA_QAC_64BIT*/
    #if (ULLONG_MAX==18446744073709551615U)
      typedef unsigned long long uint64_t;                              /**< Unsigned type with fixed 64 bit length   */
      typedef   signed long long  int64_t;                              /**< Signed type with fixed 64 bit length     */
    #else
      #error "No correct typedef for 64 bit data types!!!"
    #endif
    /* PRQA L: YOLPIYA_QAC_64BIT */
#endif
  /* PRQA L: YOLPIYA_QAC_TYPEDEF */





#endif

/**** end of file *********************************************************************************/





