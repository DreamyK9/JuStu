#include <stdio.h>

int main () {
	int nl=0, cnt=0, last=0;

	for (char c=getchar(); ; c=getchar(), cnt++) {

		if (c=='\n') {
			nl++;
			cnt = 0;

		} else if (c==EOF && cnt>0) {
			nl++; cnt--;
			last=1;
			break;
		}
	}

	printf("\n%d lines\n", nl);
	if (last==1) printf("last line unfinished with %d characters\n", cnt);
	
	return 0;
}
