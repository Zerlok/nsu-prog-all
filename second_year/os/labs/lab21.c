#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


int beep_cntr;


void beep()
{
	printf("beep\n");

	system("pacmd play-file /usr/share/sounds/KDE-Sys-App-Message.ogg alsa_output.pci-0000_00_1b.0.analog-stereo");
	++beep_cntr;
}


void finish()
{
	printf("\nTOTAL BEEPS: %d\n", beep_cntr);
	exit(1);
}



void scan_symbols()
{
	int c;
	for (;;)
	{
		c = getchar();
		
		if (c == EOF)
			break;
		
		printf("%d ", c);
	}
}


int main(int argc, char **argv)
{
	beep_cntr = 0;

	signal(SIGINT, finish);
	signal(SIGQUIT, beep);

	scan_symbols();

	return 0;
}
