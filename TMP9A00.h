// License       : License.txt
// Specifications: Spec-TMP9A00.pdf
/*-- File Header Comment Start -----------------------------------------------*/
// File Name        : TMP9A00.h
// Reason for change: 01.00.00 : 01/11/'22 : New Release
// Nickname         : Blue Dragon
/*-- File Header Comment End -------------------------------------------------*/

#ifndef __TMP9A00_H__
#define __TMP9A00_H__

#include "user_define.h"

// Components number
#define iTMP9A00                132U                    // Texas Instruments TMP9A00-EP

// TMP9A00-EP System Parts definitions
#define iTMP9A00_xoff           1.8639F                 // X offset [V]
#define iTMP9A00_yoff           0.0F                    // Y offset [degree celsius]
#define iTMP9A00_gain           -0.01177F               // Gain [V/degree celsius]
#define iTMP9A00_max            150.0F                  // Temperature Max [degree celsius]
#define iTMP9A00_min            -55.0F                  // Temperature Min [degree celsius]

extern const tbl_adc_t tbl_TMP9A00;

#endif /*__TMP9A00_H__*/
