// License       : License.txt
// Specifications: Spec-00000058.pdf
/*-- File Header Comment Start -----------------------------------------------*/
// File Name        : pp_00000058.cpp
// BSL              : 00000058
// Reason for change: 01.00.00 : 15/09/'22 : New Release
// Nickname         : Blue Dragon
/*-- File Header Comment End -------------------------------------------------*/

#include "user_define.h"

static uint32 lib_f32_MaxMin( float32* , float32 , float32 );

#if     iMA == iSMA                             // Simple moving average filter
static float32 lib_f32_SMA( float32 , sma_f32_t* );

#elif   iMA == iEMA                             // Exponential moving average filter
static float32 lib_f32_EMA( float32 , ema_f32_t* );

#elif   iMA == iWMA                             // Weighted moving average filter
static float32 lib_f32_WMA( float32 , wma_f32_t* );

#else                                           // Non-moving average  filter
#endif

// ADC Main Function
pp2ap_adc_t pp_00000058( AnalogIn adc , tbl_adc_t tbl )
{
        pp2ap_adc_t res;
        
        // MP A/D value read
        uint16  ai = adc.read_u16();
        
        // CP A/D value to Voltage value conversion
        float32 vi = ( ai * iADC_vdd ) / ( 1<<iADC_bit );
        
        // SP Voltage value to Physical value : linear conversion
        float32 wk = (( vi - tbl.xoff ) / tbl.gain ) + tbl.yoff;
        
        // range (Min to Max)
        res.sts = lib_f32_MaxMin( &wk , tbl.max , tbl.min );
        
        // Moving average filter select
#if     iMA == iSMA    // Simple moving average filter
        res.phy = lib_f32_SMA( wk , tbl.sma );
        
#elif   iMA == iEMA    //  Exponential moving average filter
        res.phy = lib_f32_EMA( wk , tbl.ema );
        
#elif   iMA == iWMA    // Weighted moving average filter
        res.phy = lib_f32_WMA( wk , tbl.wma );
        
#else                  // Non-moving average filter
        res.phy = wk;
#endif
        
        return( res );
}

// Min to max range function
static uint32 lib_f32_MaxMin( float32* x , float32 max , float32 min )
{
        uint32 res = iNormal;
        
        if( *x > max )
        {
                *x  = max;
                res = iMax_NG;
        }
        else if( *x < min )
        {
                *x  = min;
                res = iMin_NG;
        }
        else
        {
                // Nothing to do
        }
        
        return( res );
}

#if iMA == iSMA

// Simple moving average filter function
static float32 lib_f32_SMA( float32 x , sma_f32_t *x_t )
{
        float32 y = 0.0F;
        
        if( x_t->n > 0U )
        {
                if( x_t->sts == iInitial )
                {
                        x_t->sum = 0.0F;
                        for( x_t->pos = 0U ; x_t->pos < x_t->n ; x_t->pos++ )
                        {
                                x_t->buf[ x_t->pos ] = x;
                                x_t->sum = x_t->sum + x;
                        }
                        x_t->pos = 0U;
                        y = x;
                        x_t->sts = iInitial_Fin;
                }
                else
                {
                        x_t->sum = x_t->sum - x_t->buf[ x_t->pos ] + x;
                        y = (float32)( x_t->sum / x_t->n );
                        
                        x_t->buf[ x_t->pos ] = x;
                        
                        x_t->pos++;
                        if( x_t->pos >= x_t->n )
                        {
                                x_t->pos = 0U;
                        }
                        else
                        {
                                // Nothing to do
                        }
                }
        }
        else
        {
                y = x;
        }
        
        return( y );
}

#elif   iMA == iEMA

// Exponential moving average filter function
static float32 lib_f32_EMA( float32 x , ema_f32_t *x_t )
{
        float32 y;
        
        if( x_t->sts == iInitial )
        {
                y = x;
                x_t->sts = iInitial_Fin;
        }
        else if( ( x_t->k > 0.0F ) && ( x_t->k < 1.0F ) )
        {
                y = (float32)( ( x_t->k * x ) + ( ( 1.0F - x_t->k ) * x_t->xn_1 ) );
        }
        else
        {
                y = x;
        }
        x_t->xn_1 = y;
        return( y );
}

#elif   iMA == iWMA

// Weighted moving average filter function
static float32 lib_f32_WMA( float32 x , wma_f32_t *x_t )
{
        float32 y   = 0.0F;
        float64 sum = 0.0F;
        uint8   i   = 0U;
        uint8   j   = 0U;
        
        if( x_t->n > 0U )
        {
                if( x_t->sts == iInitial )
                {
                        for( i = 0 ; i < x_t->n ; i++ )
                        {
                                x_t->buf[i] = x;
                        }
                        y = x;
                        x_t->pos = 0U;
                        x_t->sts = iInitial_Fin;
                }
                else
                {
                        x_t->buf[x_t->pos] = x;
                        
                        sum = 0.0F;
                        j   = x_t->pos;
                        
                        for( i = 0 ; i < x_t->n ; i++ )
                        {
                                sum = sum + x_t->buf[j] * ( x_t->n - i );
                                if( j > 0 )
                                {
                                        j--;
                                }
                                else
                                {
                                        j = x_t->n - 1;
                                }
                        }
                        
                        y = (float32)( sum / x_t->n_sum );
                        
                        x_t->pos++;
                        if( x_t->pos >= x_t->n )
                        {
                                x_t->pos = 0U;
                        }
                        else
                        {
                                // Nothing to do
                        }
                        
                }
        }
        else
        {
                y = x;
        }
        
        return( y );
}

#else
#endif
