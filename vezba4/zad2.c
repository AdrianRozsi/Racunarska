#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>

#define KEY0 25
#define KEY1 26
#define LED 28

int main()
{
    int i = 0, taster_pritisnut_0 = 0, taster_pritisnut_1 = 0;
    int key0_value;
    int key1_value;
    if (wiringPiSetup() == -1)
        exit(1);

    pinMode(KEY0, INPUT);
    pinMode(KEY1, INPUT);

    if (softPwmCreate(LED, 0, 100) != 0)
        exit(2);

    i = 0;
    taster_pritisnut_0 = 0;
    taster_pritisnut_1 = 0;

    while (1)
    {
        key0_value = digitalRead(KEY0); // procitaj KEY0
        key1_value = digitalRead(KEY1); // procitaj KEY1

        // cekamo na pritisak tastera
        if (!key0_value && !(taster_pritisnut_0))
        {
            taster_pritisnut_0 = 1;

            i += 20;
            if (i > 100)
                i = 100;
            printf("i = %d\n", i);
            fflush(stdout);
            softPwmWrite(LED, i);
        }
        if (!key1_value && !(taster_pritisnut_1))
        {
            taster_pritisnut_1 = 1;

            i -= 20;
            if (i < 0)
                i = 0;
            printf("i = %d\n", i);
            fflush(stdout);
            softPwmWrite(LED, i);
        }

        // cekamo da se taster otpusti
        if (key0_value)
            taster_pritisnut_0 = 0;

        if (key1_value)
            taster_pritisnut_1 = 0;
    }
    return 0;
}