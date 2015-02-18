#include "netdir.h"
#include "netsock.h"

void test(int ret) {
	if (ret < 0) {
		perror("");
	}
}
int main (int argc, char* argv[]) {
	if (argc < 2) return 0;

	int ret = chdir(argv[1]);
	test(ret);

	ret = mkfifo("url",666);
	test(ret);
	int url = open("url",O_RDWR);
	test(url);

	ret = mkfifo("in",666);
	test(ret);
	int in = open("in",O_RDWR);
	test(in);

	ret = mkfifo("out",666);
	test(ret);
	int out = open("out",O_RDWR);
	test(out);

	int urlsize = 0;
	char* urlbuf;
	int rb;
	int urlread = 1;
	int separator = 0;

	while (urlread) {
		urlsize += 10;
		//Read and process URL in format host:port
		urlbuf  = (char*)malloc(urlsize);
		//sizeof(char) == 1
		rb = read(url,urlbuf,sizeof(urlbuf));
		for (int i = 0;i<= urlsize;i++) {
			if (urlbuf[i] == '\n') {
				if ((i+1) <= urlsize) {
					urlbuf[i+1] = '\0';
					urlread = 0;
				}
			}
			else if (urlbuf[i] == ':') {
				separator = i;
			}
		}
	}
	char* host = (char*)malloc(separator+1);
	strncat(host,urlbuf,separator);

	char* port = (char*)malloc((urlsize-separator)+1);
	int j = 0;
	for (int i = separator; i <= urlsize;i++) {
		port[j] = urlbuf[i];
		j++;
	}

	int sfd = makesock(host,port,0);
	char localbuf[2];

	while(1) {
		memset(localbuf,0,sizeof(localbuf));

		ret = read(sfd,localbuf,1);
		test(ret);

		ret = write(out,localbuf,1);
		test(ret);

		read(in,localbuf,1);
		test(ret);

		write(sfd,localbuf,1);
		test(ret);
	}
	return 0;
}
