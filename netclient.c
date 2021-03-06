#include "netdir.h"
#include "netsock.h"

//maximum url size plus max port size
#define MAX_URL (2000+65535)

void test(int ret,char* mess) {
	if (ret < 0) {
		perror(mess);
	}
}
int main (int argc, char* argv[]) {
	printf("Starting NetClient\n");
	int ret = chdir(argv[1]);
	test(ret,"Unable to chdir");

	ret = mkfifo("url",0666);
	test(ret,"Unable to make url FIFO");
	int url = open("url",O_RDWR);
	test(url,"Unable to open url FIFO");

	ret = mkfifo("in",0666);
	test(ret,"Unable to make input FIFO");
	int in = open("in",O_RDWR);
	test(in,"Unable to open input FIFO");

	ret = mkfifo("out",0666);
	test(ret,"Unable to make output FIFO");
	int out = open("out",O_RDWR);
	test(out,"Unable to open output FIFO");

	char urlbuf[MAX_URL];
	long separator = 0;
	char urlread[2];
	int fail = 1;
	long urlsize;
	while (fail) {
		int rb = read(url,urlread,2);
		test(rb,"Unable to read from URL FIFO");
		printf("(%s)\n",urlread);
		if (rb < 2) fail = 0;
		else strcat(urlbuf,urlread);
	}
	long i;
	for(i = 0; i<= MAX_URL; i++) {
		if(urlbuf[i] == ':') {
			separator = i;
		}
		else if (urlbuf[i] == '\n' || urlbuf[i] == '\0') {
			i = MAX_URL+1;
			urlsize = i;
		}
	}
	printf("\n\n(%s)\n\n",urlbuf);
	char* host = (char*)malloc(separator+1);
	strncat(host,urlbuf,separator);
	printf("\n(%s)\n",host);
	char* port = (char*)malloc((MAX_URL-separator)+1);
	long j = 0;
	long g = 0;
	for (g = separator+1; g <= urlsize; g++) {
		port[j] = urlbuf[g];
		j++;
	}
	printf("(%s)\n",port);
	int sfd = makesock(host,port,0);
	char*  localbuf = NULL;
	size_t blank = 0;
	FILE* socketfile = fdopen(sfd,"r");
	FILE* infile = fdopen(in,"r");
	while(1) {
		getline(&localbuf,&blank,socketfile);
		printf("(%s)\n",localbuf);
		ret = write(out,localbuf,sizeof(localbuf));
		test(ret,"Unable to write to output");

		free(localbuf);
		getline(&localbuf,&blank,infile);
		printf("(%s)\n",localbuf);
		ret = write(sfd,localbuf,sizeof(localbuf));
		free(localbuf);
	}
	return 0;
}
