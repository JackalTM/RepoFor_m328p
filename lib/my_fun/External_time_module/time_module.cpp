#include "time_module.h"
#ifdef _INC_TIME_MODULE

/***************************************************************
 * @name    IncSecond
 * @brief   Add one second time data
 */
void DataAndTime::IncSecond(void)
{
    if(second < 60)
    {   second++;}
    else
    {   second=0;
        if(minute < 60)
        {   minute++;}
        else
        {   minute=0;
            if(hour < 24)
            {   hour++;}
            else
            {   hour=0;}
        }
    }
    _n_sec++;
}
//==============================================================

/***************************************************************
 * @name    IncSecond
 * @brief   Add one second time data
 */
inline void DataAndTime::IRQ_TickEvent(void)
{
    if(n < _F)
    {   n++;}
    else
    {   IncSecond();
        n=1;}
}
//==============================================================

/***************************************************************
 * @name    GetTime
 * @brief   Return current time value
 * @return  Time format "data_time::mytime_t"
 */
data_time::mytime_t DataAndTime::GetTime(void)
{
    data_time::mytime_t tTime;
    tTime.hour = hour;
    tTime.minute = minute;
    tTime.second = second;
    return tTime;
}
//==============================================================
#endif // _INC_TIME_MODULE
//==============================================================