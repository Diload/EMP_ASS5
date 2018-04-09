#ifndef RTC_H_
#define RTC_H_


INT8U get_hour();
INT8U get_min();
INT8U get_sec();
void set_hour( INT8U );
void set_min( INT8U );
void set_sec( INT8U );

void rtc_task(INT8U, INT8U, INT8U, INT8U );
void display_rtc_task(INT8U, INT8U, INT8U, INT8U );
void ajust_rtc_task(INT8U task_no);

#endif /*RTC_H_*/
