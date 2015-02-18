#include "netdir.h"

int main (int argc, char* argv[]) {
	if (argc != 2) {
		printf("Usage: %s <directory>\n",argv[0]);
		exit(0);
	}
	int ret = chdir(argv[1]);
	if (ret < 0) {
		printf("Could not chdir to %s\n",argv[1]);
		perror("");
		exit(0);
	}

	ret = mkfifo("create",0666);
	if (ret < 0) {
		perror("Could not make create fifo");
		return 0;
	}
	int ctfd = open("create",O_RDWR);
	if (ctfd < 0) {
		perror("Could not open create");
		return 0;
	}
	char create[1];
	//socket counter
	int count = 0;
	char crdir[15];

	while(1) {
		ret = read(ctfd,create,1);
		//printf("%s %d\n",create,count);
		if (ret < 0) {
			perror("Failed to read from create");
			continue;
		}
		else if (ret < 1 || create[0] == '\n') {
			continue;
		}

		sprintf(crdir,"%d",count);
		ret = mkdir(crdir,0777);
		if (ret < 0) {
			printf("Failed to create dir");
			perror("");
			continue;
		}
		count++;

		char* args[ ] = { "netclient", crdir };
		switch(fork()) {
			case -1:
				perror("Failed to fork");
				break;
			case 0:
				printf("NetClient\n");
				execv("../netclient", args);
				break;
			default:
				break;
		}
	}
	return 0;
}
