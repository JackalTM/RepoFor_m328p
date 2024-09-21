#include "_include.h"
#ifdef _INC_TIME_MODULE

#include "stdint.h"
#include "Data_conversion/convert_data_and_time.h"

class DataAndTime
{
private:
    const uint8_t _F;
    uint8_t hour, minute, second, n;
    uint32_t _n_sec;

    void IncSecond(void);

public:
    DataAndTime(uint8_t in_F): _F(in_F) 
    {   hour = 0; minute = 0; second = 0; n = 1; _n_sec = 0;}
    ~DataAndTime();

    void IRQ_TickEvent(void);
    
    data_time::mytime_t GetTime(void);
};

#endif // _INC_TIME_MODULE