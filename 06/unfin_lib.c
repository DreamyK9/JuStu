/* ISNUM FUNCTION */
int isnum_base(char str[], int len) {
	if (!str) return 0;

	if (len >= 0) {
		for (int i=0; i<len; i++) {
			if (!isdigit(str[i])) return 0;
		}
	} else {
		for (int i=0; str[i]; i++) {
			if (!isdigit(str[i])) return 0;
		}
	}
	return 1;
}

typedef struct
{
	int len;
	char str[];
} isnum_args;

int var_isnum(isnum_args in) {
	char *str_out = in.str;
	int len_out = in.len ? in.len : -1;
	return isnum_base(str_out, len_out);
}
/* ISNUM END*/

#define isnum(str, len) var_isnum((isnum_args){str, len});
