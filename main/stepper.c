
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "stepper.h"

#include "timer_group_0.h"


void Setup_stepper(void)
{
    gpio_pad_select_gpio(DIR_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(DIR_GPIO, GPIO_MODE_OUTPUT);

    gpio_pad_select_gpio(STEP_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(STEP_GPIO, GPIO_MODE_OUTPUT);
}

void Control_stepper(void)
{
    int x;

    // Set motor direction clockwise
    gpio_set_level(DIR_GPIO, 1);

    // Spin motor one rotation slowly
    for(x = 0; x < STEPS_PER_REVI*3; x++) {
        gpio_set_level(STEP_GPIO,1);
        timer_delay_Ms(1);
        gpio_set_level(STEP_GPIO,0);
        timer_delay_Ms(1);
    }
    // Pause for one second
    timer_delay_Ms(5);

    // Set motor direction counterclockwise
    gpio_set_level(DIR_GPIO,0);
    // timer_delay_Ms(1);

    // Spin motor two rotations quickly
    for(x = 0; x < (STEPS_PER_REVI * 2); x++) {
        gpio_set_level(STEP_GPIO,1);
        timer_delay_Ms(1);
        gpio_set_level(STEP_GPIO,0);
        timer_delay_Ms(1);
    }

    timer_delay_Ms(5);
}





