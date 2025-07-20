#include "cgic.h"

int cgiMain() {
	cgiHeaderContentType("text/html");
	for(long i=0;i<1000000;i++) {
		fprintf(cgiOut,"%ld<br>\n",i);
	}
	return 0;
}
