#include <stdio.h>
#include <ctype.h>

int isletter(char c);
int isnum(char c);

int main() {
	// b for boolean
	int blast=0;
	// c for count
	int cchar=0, clchar=0, cnl=0, cA=0, c1=0, cword=0, cnum=0, cmix=0, calnum=0;

	for (char c=getchar(); ; c=getchar(), cchar++, clchar++) {
		
		if (isalpha(c)) {cA++; calnum++;
		} else if (isdigit(c)) {c1++; calnum++;
		} else {
			cmix += (cA && c1);
			cword += (cA && !c1);
			cnum += (c1 && !cA);
			cA = c1 = 0;

			if (c=='\n') {
				clchar = 0;
				cnl++;
			} else if (c==EOF) {
				if (clchar>1) blast=1;
				break;
			}
		}
	}


	printf("%d Zeichen\n", cchar);
	printf("davon %d sichtbar\n", cchar-cnl);
	printf("%d Worte\n", cword);
	printf("%d Zahlen\n", cnum);
	printf("%d gemischte Sequenzen\n", cmix);
	printf("%d sonstige Zeichen\n", cchar-calnum);
	if (blast==1) printf("letzte Zeichenfolge unvollstaendig\n");

	return 0;
}
