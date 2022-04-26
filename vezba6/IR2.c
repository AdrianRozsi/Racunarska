#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bcm2835.h>
#include <lirc/lirc_client.h>
#include <softPwm.h>



#define PIN 20
#define LED 28

int main(int argc, char **argv)
{
    int i = 0;
    struct lirc_config *config;
    char *code;
    if (softPwmCreate(LED, 0, 100) != 0)
        exit(2);
    // startuj lirc
    if (lirc_init("lirc", 1) == -1)
        return 1;
    if (!bcm2835_init())
        return 2;
    // Setuj PIN kao izlazni
    bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP);
    // procitaj /etc/lirc/lircrc/lircd.conf
    if (lirc_readconfig(NULL, &config, NULL) == 0)
    {
        // radimo dok je LIRC soket otvoren 0=otvoren -1=zatvoren
        while (lirc_nextcode(&code) == 0)
        {
            // if code=NULL ništa nije primljeno-preskoči
            if (code == NULL)
                continue;
            {
                bcm2835_delay(400);
                if (strstr(code, "KEY_0"))
                {
                    i += 20;
                    if (i > 100)
                        i = 100;
                    printf("Jacina leda: %d%%", i);
                    softPwmWrite(LED, i);
                }
                else if (strstr(code, "KEY_1"))
                {
                    printf("KEY1\n");
                    i -= 20;
                    if (i < 0)
                        i = 100;
                    printf("Jacina leda: %d%%", i);
                    softPwmWrite(LED, i);
                }
            }
            free(code);
        }
        lirc_freeconfig(config);
    }
    lirc_deinit();
    bcm2835_close();
    return 0;
}
