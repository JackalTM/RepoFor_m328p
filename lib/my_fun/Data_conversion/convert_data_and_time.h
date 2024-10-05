#include "_include.h"
#ifdef _INC_CONVERT_DATA_AND_TIME

#ifndef CONVERT_DATA_AND_TIME_H
#define CONVERT_DATA_AND_TIME_H

#include "stdint.h"

namespace data_time{

    #define data_time_TIME_LEN (uint8_t)8U
    #define data_time_DATA_LEN (uint8_t)10U
//============================================================================= 
typedef struct
{
    uint16_t hour;
    uint16_t minute;
    uint16_t second;
}time_t;
//--------------------

//----------------------------------------------
// Conversion from seconds to time structure
time_t From_ms_to_time(uint32_t ms);
time_t From_sec_to_time(uint32_t sec);

// Conversion from time structure to seconds amount
uint32_t From_time_to_ms(const time_t *pTime);
uint32_t From_time_to_sec(const time_t *pTime);
//=============================================================================
} // namespace myTime

#endif // ifndef CONVERT_DATA_AND_TIME_H
#endif // _INC_CONVERT_DATA_AND_TIME