
#ifndef _STEPPER_H_
#define _STEPPER_H_

#ifdef __cplusplus
extern "C" {
#endif

#define DIR_GPIO GPIO_NUM_12    // Direction 2
#define STEP_GPIO GPIO_NUM_14   // Step 4

// Motor steps per rotation
#define STEPS_PER_REVI   200

void Setup_stepper(void);
void Control_stepper(void);


#ifdef __cplusplus
}
#endif



#endif /*_STEPPER_H_*/