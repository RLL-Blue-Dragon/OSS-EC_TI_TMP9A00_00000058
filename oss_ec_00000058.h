// License       : License.txt
// Specifications: Spec-00000058.pdf
/*-- File Header Comment Start -----------------------------------------------*/
// File Name        : oss_ec_00000058.h
// BSL              : 00000058
// Reason for change: 01.00.00 : 15/09/'22 : New Release
// Nickname         : Blue Dragon
/*-- File Header Comment End -------------------------------------------------*/

#ifndef __OSS_EC_H__
#define __OSS_EC_H__

#include "mbed.h"

typedef unsigned char           uint8;
typedef unsigned short          uint16;
typedef unsigned long           uint32;
typedef unsigned long long      uint64;
typedef signed char             sint8;
typedef signed short            sint16;
typedef signed long             sint32;
typedef signed long long        sint64;
typedef float                   float32;
typedef double                  float64;

typedef struct
{
        uint32                  sts;
        float32                 phy;
}pp2ap_adc_t;

typedef struct
{
        uint32                  sts;                            // CAUTION: initial value = iInitial
        uint8                   n;                              // CAUTION: n != 0 , buf size == n
        uint8                   pos;
        float64                 sum;
        float32*                buf;
}sma_f32_t;

typedef struct
{
        uint32                  sts;                            // CAUTION: initial value = iInitial
        float32                 xn_1;
        float32                 k;                              // CAUTION: range of 0 to 1.0
}ema_f32_t;

typedef struct
{
        uint32                  sts;                            // CAUTION: initial value = iInitial
        uint8                   n;                              // CAUTION: n != 0 , buf size == n
        uint8                   pos;
        uint16                  n_sum;
        float32*                buf;
}wma_f32_t;

typedef struct
{
        uint32                  cmp;
        uint8                   pin;
        float32                 xoff;
        float32                 yoff;
        float32                 gain;
        float32                 max;
        float32                 min;
        uint32                  ma;
        sma_f32_t*              sma;
        ema_f32_t*              ema;
        wma_f32_t*              wma;
}tbl_adc_t;


// 2000 - 2999 : Process state/command/response status codes
#define iInitial                2000U                           // Initial
#define iInitial_Fin            2001U                           // Initialization finished

// 3000 - 3999 : Function call codes
#define iNonMA                  3000U                           // Non-moving average filter
#define iSMA                    3001U                           // Simple Moving Average
#define iEMA                    3002U                           // Exponential Moving Average
#define iWMA                    3003U                           // Weighted Moving Average

// 4000 - 4999 : Diagnosis result codes
#define iNormal                 4000U                           // Normal
#define iMax_NG                 4001U                           // Max Limiter NG
#define iMin_NG                 4002U                           // Min Limiter NG

// PP Function
pp2ap_adc_t pp_00000058( AnalogIn , tbl_adc_t );

#endif /*__OSS_EC_H__*/
