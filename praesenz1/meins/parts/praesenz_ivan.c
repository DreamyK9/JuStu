float funktion_3(int *absolute_anzahl, int a) {
	int zusammen, b;
	zusammen = 0;
	
	for(b = 0; b < 26; ++b) {
		zusammen += absolute_anzahl[b];
	}
	
	printf("zusammen = %d \n", zusammen);
	
	return (float)absolute_anzahl[a] / zusammen * 100;
}

int main() {
	int a;
	float prozent[26];
	
	for(a = 0; a < 26; ++a) {
		prozent[a] = funktion_3(absolute_anzahl, a);
	}
	
	for(a = 0; a < 26; ++a) {
		printf("%f %% \n", prozent[a]);
	}
	
	return 0 ;
}