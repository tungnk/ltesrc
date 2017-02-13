
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stddef.h>

int main(int argc, char* argv[])
{
	/* Get option */
	int ch = 0;
	char *SerialPort = NULL;
	//WORD ttl = 0;

	static struct option long_options[] = {
			{ "serial", required_argument, 0, 's' },
	};

	int long_index;
	/* Process option */
	while (( ch = getopt_long(argc, argv,":s:",
			long_options, &long_index )) != -1) {
		switch (ch) {
		case 's' :
			SerialPort = optarg;
			break;
		default:
			break;
		}
	}
}
