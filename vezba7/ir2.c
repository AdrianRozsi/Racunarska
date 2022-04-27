#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bcm2835.h>
#include <lirc/lirc_client.h>
#include <softPwm.h>



#define PIN 20 
#define KEYS 24


int main(int argc, char **argv)
{
    int i = 0;
	int pressed = false;
	int  taster_pritisnut_1 = 0;
	int  taster_pritisnut_0 = 0;
	
	int key_value;
    
	if (wiringPiSetup() == -1)
        exit(1);
	
	pinMode(KEYS,INPUT);
	
    
    struct lirc_config *config;
    char *code;
   
    i = 0;
    taster_pritisnut_1 = 0;
    taster_pritisnut_0 = 0;
	
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
            while(1)
			{
				
				if(!key_value && !(taster_pritisnut_1)){
				taster_pritisnut_1 = 1;
					pressed = true;
                bcm2835_delay(400);
                if (strstr(code, "KEY_VOLUMEUP"))
                {
					
                    i += 20;
                    if (i > 100)
                        i = 100;
                    printf("Jacina leda: %d%% \n", i);
					 bcm2835_gpio_write(PIN,HIGH);
					bcm2835_delay(500);
                  
                }
				}
                else if(!key_value && !(taster_pritisnut_0)) 
				{
						taster_pritisnut_0 = 1;
						pressed = true;
				if (strstr(code, "KEY_VOLUMEDOWN"))
                {
                    printf("KEY1\n");
                    i -= 20;
                    if (i < 0)
                        i = 0;
                    printf("Jacina leda: %d%%", i);
                    bcm2835_gpio_write(PIN,LOW);
					bcm2835_delay(500);
                }
				}
					if(key_value)
						taster_pritisnut_0 = 0;
						taster_pritisnut_1 = 0;
						delay(100);
            }
            free(code);
        }
        lirc_freeconfig(config);
    }
    lirc_deinit();
    bcm2835_close();
    return 0;
}