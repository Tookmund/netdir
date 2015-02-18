#include "netdir.h"
#include "netsock.h"

int main (int argc, char* argv[]) {
	if (argc < 2) return 0;

	int ret = chdir(argv[1]);
	if (ret < 1) return 0;

	ret = mkfifo("url",666);
	if (ret < 1) return 0;

	ret = mkfifo("in",666);
	if (ret < 0) return 0;

	ret = mkfifo("out",666);
	if ret < 0) return 0;
	
	int urlsize = 10;
	char* url;
	while (1) {
		url  = (char*)malloc(urlsize);
		read 
	}
}
