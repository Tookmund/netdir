#include "netdir.h"

int main (int argc, char* argv[]) {
	if (argc != 1) {
		printf("Usage: %s <directory>\n",argv[0]);
		exit(0);
	}
	int ret = chdir(argv[1]);
	if (ret < 0) {
		perror("Could not chdir to %s",argv[1];);
	}
	
	return 0;
}
