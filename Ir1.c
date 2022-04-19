// LED3 je na DVK512 pločici na P28 što je pin 20 na BCM-u,
// ako se koristi protobord može se
// koristiti isti ovaj pin ili neki drugi
#define PIN 20



int main(int argc, char **argv)
{
	struct lirc_config *config;
	char *code;
	//startuj lirc
		if(lirc_init("lirc",1)==-1)
			return 1;
		if (!bcm2835_init())
			return 2;
	
	
	// Setuj PIN kao izlazni
	bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP);
	//procitaj /etc/lirc/lircrc/lircd.conf
if(lirc_readconfig(NULL, &config,NULL)==0)
	{
	//radimo dok je LIRC soket otvoren 0=otvoren -1=zatvoren
	while (lirc_nextcode(&code)==0)
	{

		// if code=NULL ništa nije primljeno-preskoči
	if(code==NULL) continue; {
		bcm2835_delay(400);

		if (strstr(code,"KEY_0")){
			printf("KEY0\n");

			// ukljuci
			bcm2835_gpio_write(PIN, HIGH);
			bcm2835_delay(500);
		}
		else if (strstr(code,"KEY_1")){
			printf("KEY1\n");
			
			// ukljuci
			bcm2835_gpio_write(PIN, HIGH);
			bcm2835_delay(500);
			}
		else if (strstr(code,"KEY_2")){
			printf("KEY2\n");
			
			// ukljuci
			bcm2835_gpio_write(PIN, HIGH);
			bcm2835_delay(500);
			}
		else if (strstr(code,"KEY_3")){
			printf("KEY3\n");
			
			// ukljuci
			bcm2835_gpio_write(PIN, HIGH);
			bcm2835_delay(500);
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
