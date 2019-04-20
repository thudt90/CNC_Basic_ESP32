/* Timer group-hardware timer example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <stdio.h>
#include "esp_types.h"
#include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "freertos/queue.h"
#include "soc/timer_group_struct.h"
#include "driver/periph_ctrl.h"
#include "driver/timer.h"

#include "timer_group_0.h"
// #include "driver/gpio.h"

/*
* global volatile variable
*/
volatile uint8_t int_timer_flag;

/*
 * Timer group0 ISR handler
 *
 * Note:
 * We don't call the timer API here because they are not declared with IRAM_ATTR.
 * If we're okay with the timer irq not being serviced while SPI flash cache is disabled,
 * we can allocate this interrupt without the ESP_INTR_FLAG_IRAM flag and use the normal API.
 */
void IRAM_ATTR timer_group0_isr(void *para)
{
    int timer_idx = (int) para;

    /* Retrieve the interrupt status and the counter value
       from the timer that reported the interrupt */
    TIMERG0.hw_timer[timer_idx].update = 1;

    /* Clear the interrupt */
    TIMERG0.int_clr_timers.t1 = 1;
    /* After the alarm has been triggered
      we need enable it again, so it is triggered the next time */
    //TIMERG0.hw_timer[timer_idx].config.alarm_en = TIMER_ALARM_EN;

    /* Now just send the event data back*/
    int_timer_flag = 1;
}

/*
 * Initialize selected timer of the timer group 0
 *
 * the TIMER_1 to initialize
 * auto_reload - should the timer auto reload on alarm? No
 * timer_interval - the interval of alarm to set
 */
static void tg0_timer_init(enum delay_type dtype, double timer_interval)
{
    /* Select and initialize basic parameters of the timer */
    timer_config_t config;
    config.divider = TIMER_DIVIDER;
    config.counter_dir = TIMER_COUNT_UP;
    config.counter_en = TIMER_PAUSE;
    config.alarm_en = TIMER_ALARM_EN;
    config.intr_type = TIMER_INTR_LEVEL;
    config.auto_reload = TEST_WITHOUT_RELOAD;
    timer_init(TIMER_GROUP_0, TIMER_1, &config);

    /* Timer's counter will initially start from value below.
       Also, if auto_reload is set, this value will be automatically reload on alarm */
    timer_set_counter_value(TIMER_GROUP_0, TIMER_1, 0x00000000ULL);

    /* Configure the alarm value and the interrupt on alarm. */
    if (MILISECOND == dtype)
    {
        timer_set_alarm_value(TIMER_GROUP_0, TIMER_1, timer_interval * TIMER_SCALE_MILI_SEC);
    }
    else if (MICROSECOND == dtype)
    {
        timer_set_alarm_value(TIMER_GROUP_0, TIMER_1, timer_interval * TIMER_SCALE_MICRO_SEC);
    }
    else
    {
        // Maybe is delay a second
    }

    timer_enable_intr(TIMER_GROUP_0, TIMER_1);
    timer_isr_register(TIMER_GROUP_0, TIMER_1, timer_group0_isr,
        (void *) TIMER_1, ESP_INTR_FLAG_IRAM, NULL);

    timer_start(TIMER_GROUP_0, TIMER_1);
}

/*
 * In this example, we will test hardware timer1 of timer group0.
 * Delay milisecond
 */
void timer_delay_Ms(double ms)
{
    //timer_queue = xQueueCreate(10, sizeof(timer_event_t));
    //tg0_timer_init(TIMER_0, TEST_WITHOUT_RELOAD, TIMER_INTERVAL0_SEC);
    tg0_timer_init(MILISECOND, ms);

    while(0 == int_timer_flag);
    int_timer_flag = 0;
}

/*
* Delay microsecond
*/
void timer_delay_microseconds(double us)
{
    tg0_timer_init(MICROSECOND, us);

    while(0 == int_timer_flag);
    int_timer_flag = 0;
}



