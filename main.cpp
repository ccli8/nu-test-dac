#include "mbed.h"

#if TARGET_NUMAKER_PFM_NANO130

AnalogIn ain1(A4);
AnalogIn ain2(A5);
AnalogOut aout1(PC_6);
AnalogOut aout2(PC_7);
    
#elif TARGET_NUMAKER_PFM_NUC472

#error("DAC not support")

#elif TARGET_NUMAKER_PFM_M453

AnalogIn ain1(A4);
AnalogIn ain2(A5);
AnalogOut aout1(A0);

#elif TARGET_NUMAKER_PFM_M487 || TARGET_NUMAKER_IOT_M487

AnalogIn ain1(A4);
AnalogIn ain2(A5);
AnalogOut aout1(PB_12);
AnalogOut aout2(PB_13);

#elif TARGET_NUMAKER_PFM_M2351

AnalogIn ain1(A4);
AnalogIn ain2(A5);
AnalogOut aout1(PB_12);
AnalogOut aout2(PB_13);

#endif

#if DEVICE_SERIAL

#define MY_PRINTF(...)   printf(__VA__ARGS__)

#else
    
#define MY_PRINTF(...)

#endif

#define MY_ASSERT_MESSAGE_(cond, file, line, msg, ...)      \
    if (! (cond)) {                                           \
        MY_PRINTF("%s:%d: ", file, line);                   \
        MY_PRINTF(msg, __VA__ARGS__);                       \
        wait_ms(100);                                       \
        MBED_ASSERT(false);                                 \
    }
    
#define MY_ASSERT_MESSAGE(cond, msg, ...)   \
    MY_ASSERT_MESSAGE_(cond, __FILE__, __LINE__, msg, __VA__ARGS__)

int main()
{
    
    float valueOff = 0.0f;
    float valueOn = 0.0f;
    float valueOff_aout = 0.0f;
    float valueOn_aout = 0.0f;

    aout1 = 0;
    valueOff = ain1.read();
    valueOff_aout = aout1.read();
    aout1 = 0.5;
    valueOn = ain1.read();
    valueOn_aout = aout1.read();
    MY_PRINTF("\r\n***** valueOff = %f, valueOn = %f \r\n", valueOff, valueOn);
    MY_PRINTF("\r\n***** valueOff_aout = %f, valueOn_aout = %f \r\n", valueOff_aout, valueOn_aout);
    MY_ASSERT_MESSAGE((0.4f < valueOn) && (0.6f > valueOn), "Value is not in expected range of ~0.5f");
    MY_ASSERT_MESSAGE(valueOn > valueOff,"Value has not increased, expected 0.5");

    valueOff = ain1.read();
    valueOff_aout = aout1.read();
    aout1 = 1.0;
    valueOn = ain1.read();
    valueOn_aout = aout1.read();
    MY_PRINTF("\r\n***** valueOff = %f, valueOn = %f \r\n", valueOff, valueOn);
    MY_PRINTF("\r\n***** valueOff_aout = %f, valueOn_aout = %f \r\n", valueOff_aout, valueOn_aout);
    MY_ASSERT_MESSAGE((0.9f < valueOn) && (1.1f > valueOn), "Value is not in expected range of ~0.5f");
    MY_ASSERT_MESSAGE(valueOn > valueOff,"Value has not increased, expected 1.0");
}
