// License       : License.txt
// Specifications: Spec-TMP9A00.pdf
/*-- File Header Comment Start -----------------------------------------------*/
// File Name        : TMP9A00.cpp
// Reason for change: 01.00.00 : 01/11/'22 : New Release
// Nickname         : Blue Dragon
/*-- File Header Comment End -------------------------------------------------*/

#include        "TMP9A00.h"

#if     iTMP9A00_ma == iSMA                             // Simple moving average filter
static float32 TMP9A00_sma_buf[iTMP9A00_SMA_num];
static sma_f32_t TMP9A00_Phy_SMA =
{
        iInitial ,                                      // Initial state
        iTMP9A00_SMA_num ,                              // Simple moving average number & buf size
        0U ,                                            // buffer position
        0.0F ,                                          // sum
        &TMP9A00_sma_buf[0]                             // buffer
};

#elif   iTMP9A00_ma == iEMA                             // Exponential moving average filter
static ema_f32_t TMP9A00_Phy_EMA =
{
        iInitial ,                                      // Initial state
        0.0F ,                                          // Xn-1
        iTMP9A00_EMA_K                                  // Exponential smoothing factor
};

#elif   iTMP9A00_ma == iWMA                             // Weighted moving average filter
static float32 TMP9A00_wma_buf[iTMP9A00_WMA_num];
static wma_f32_t TMP9A00_Phy_WMA =
{
        iInitial ,                                      // Initial state
        iTMP9A00_WMA_num ,                              // Weighted moving average number & buf size
        0U ,                                            // buffer poition
        iTMP9A00_WMA_num * (iTMP9A00_WMA_num + 1)/2 ,   // kn sum
        &TMP9A00_wma_buf[0]                             // Xn buffer
};

#else                                                   // Non-moving average filter
#endif

#define iDummy_adr       0xffffffff                     // Dummy address

const tbl_adc_t tbl_TMP9A00 =
{
        iTMP9A00                ,
        iTMP9A00_pin            ,
        iTMP9A00_xoff           ,
        iTMP9A00_yoff           ,
        iTMP9A00_gain           ,
        iTMP9A00_max            ,
        iTMP9A00_min            ,
        iTMP9A00_ma             ,
        
#if     iTMP9A00_ma == iSMA                             // Simple moving average filter
        &TMP9A00_Phy_SMA        ,
        (ema_f32_t*)iDummy_adr  ,
        (wma_f32_t*)iDummy_adr
#elif   iTMP9A00_ma == iEMA                             // Exponential moving average filter
        (sma_f32_t*)iDummy_adr  ,
        &TMP9A00_Phy_EMA        ,
        (wma_f32_t*)iDummy_adr
#elif   iTMP9A00_ma == iWMA                             // Weighted moving average filter
        (sma_f32_t*)iDummy_adr  ,
        (ema_f32_t*)iDummy_adr  ,
        &TMP9A00_Phy_WMA
#else                                                   // Non-moving average filter
        (sma_f32_t*)iDummy_adr  ,
        (ema_f32_t*)iDummy_adr  ,
        (wma_f32_t*)iDummy_adr
#endif

};
