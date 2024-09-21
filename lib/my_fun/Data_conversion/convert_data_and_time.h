#include "_include.h"
#ifdef _INC_CONVERT_DATA_AND_TIME

#include "stdint.h"

namespace data_time{
//============================================================================= 
typedef struct 
{
    uint16_t hour;
    uint16_t minute;
    uint16_t second;
}mytime_t;
//--------------------
typedef struct 
{
    uint8_t year;
    uint8_t month;
    uint8_t day;
}mydata_t;
//----------------------------------------------
// Conversion from seconds to time structure
mytime_t From_ms_to_time(uint32_t ms);
mytime_t From_sec_to_time(uint32_t sec);

// Conversion from time structure to seconds amount
uint32_t From_time_to_ms(const mytime_t *pTime);
uint32_t From_time_to_sec(const mytime_t *pTime);
//=============================================================================
} // namespace myTime

#endif // _INC_CONVERT_DATA_AND_TIME