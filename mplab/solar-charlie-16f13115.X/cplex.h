#ifndef CPLEX_H
#define CPLEX_H

#define PWM1OUTPPS (0x2C)

enum leds
{
    LED1,
    LED2,
    LED3,
    LED4,
    LED5,
    LED6,
    NUM_LEDS,
};

void CP_reset(void);
void CP_setLed(int8_t led_num, uint16_t duty);

#endif
