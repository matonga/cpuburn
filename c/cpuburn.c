#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (int argc, char *argv[]) {
	int cores = 0;
	int i;
	for (i=1; i<argc; i++) {
		if (argv[i][0] == '-' && argv[i][1] == 'n') {
			cores = atoi (argv[i+1]);
		}
	}
	if (!cores) {
		FILE *fp = fopen ("/proc/cpuinfo", "r");
		while (!feof (fp)) {
			char buffer[4096];
			if (!fgets (buffer, sizeof (buffer), fp)) {
				break;
			}
			if (strncmp (buffer, "processor\t:", 11) == 0) {
				cores++;
			}
		}
	}
	printf ("Burning %u cores...\n", cores);
	for (i=0; i<cores; i++) {
		if (fork () == 0) {
			while (1) ;
		}
	}
	for (i=0; i<cores; i++) {
		wait (NULL);
	}
	return 0;
}
