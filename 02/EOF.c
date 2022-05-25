#include <stdio.h>

int main() {
	// EOF als Zahl ausgeben
	printf("%d", EOF);
	// EOF als String bzw als Zeichen ausgegeben
	printf("%s", EOF);
	// Ausgabe nach EOF, die nicht mehr angezeigt wird
	printf("Test");

	return 0;
}

// EOF gibt, wenn als String ausgegeben einen leeren character
// und wenn als Zahl ausgegeben -1 aus
// Außerdem lässt sich nichts nach EOF ausgeben