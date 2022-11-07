// License       : License.txt
// Specifications: Spec-00000058.pdf
/*-- File Header Comment Start -----------------------------------------------*/
// File Name        : TMP9A00_00000058.cpp
// BSL              : 00000058
// Model number     : Texas Instruments TMP9A00-EP
// Spec               Component type       : ADC
//                    OS                   : Mbed
//                    Calculation          : Floating-point
//                    Conversion type      : Linear
//                    Moving average filter: Moving average filter select
//                    Diagnosis            : Range (Min to Max)
// Reason for change: 01.00.00 : 01/11/'22 : New Release
// Nickname         : Blue Dragon
/*-- File Header Comment End -------------------------------------------------*/

#include "TMP9A00.h"

AnalogIn TMP9A00_adc( iTMP9A00_pin , iVref );   // AnalogIn object

// Main Function
pp2ap_adc_t TMP9A00_00000058( void )
{
        pp2ap_adc_t res = pp_00000058( TMP9A00_adc , tbl_TMP9A00 );
        return( res );
}
