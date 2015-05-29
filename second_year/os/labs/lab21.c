#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


#define BEL '\07'


int beep_cntr;


void beep()
{
	// printf("%c\n", BEL);
	system("pacmd play-file /usr/share/sounds/KDE-Sys-App-Message.ogg alsa_output.pci-0000_00_1b.0.analog-stereo");
	++beep_cntr;
}


void finish()
{
	printf("\nTOTAL BEEPS: %d\n", beep_cntr);
	exit(1);
}


int main(int argc, char **argv)
{
	beep_cntr = 0;

	signal(SIGINT, finish);
	signal(SIGQUIT, beep);

	while (1);
	// scan_symbols();

	return 0;
}
