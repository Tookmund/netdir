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
	if (ret < 0) perror("Could not make create fifo: ");

	int ctfd = open("create",O_RDONLY);
	if (ctfd < 0) perror("Could not open create: ");

	char create;
	char* cte = &create;
	
	//socket counter
	int count = 0;

	for(;;ret = read(ctfd,cte,1)) {
		if (ret < 0) {
			perror("Failed to read from create: ");
			continue;
		}
		char crdir[ ] = { (char)count,'\0' };
		ret = mkdir(crdir,0777);
		if (ret < 0) {
			printf("Failed to create dir ");
			perror("");
			continue;
		}
		count++;
		printf("%d",count);
		switch(fork()) {
		case -1:
			perror("Failed to fork: ");
			break;
		case 0:
			break;
		default:
			//char* argv[ ] = {"netclient",cte};
			exit(0);
		}
	}
	//execvp()
	return 0;
}
