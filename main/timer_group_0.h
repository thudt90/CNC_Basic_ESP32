
#ifndef _TIMER_GROUP_0_H_
#define _TIMER_GROUP_0_H_

#ifdef __cplusplus
extern "C" {
#endif

#define TIMER_DIVIDER         16  //  Hardware timer clock divider
#define TIMER_SCALE_SEC       (TIMER_BASE_CLK / TIMER_DIVIDER)  // convert counter value to seconds = 5MHz
#define TIMER_SCALE_MILI_SEC  (TIMER_BASE_CLK / (TIMER_DIVIDER * 1000))
#define TIMER_SCALE_MICRO_SEC       (TIMER_BASE_CLK / (TIMER_DIVIDER * 1000 * 1000) )

#define TEST_WITHOUT_RELOAD   0        // testing will be done without auto reload
#define TEST_WITH_RELOAD      1        // testing will be done with auto reload

/* Define type of delay */
enum delay_type
{
  MILISECOND = 0,
  MICROSECOND,
};


// Extern function
void timer_delay_Ms(double ms);
void timer_delay_microseconds(double us);

#ifdef __cplusplus
}
#endif

#endif /*_TIMER_GROUP_0_H_*/