#include <stdio.h>
#include <ctype.h>

int lengthfile() {
    int c, l;
    l = 0;

    while((c=getchar())!=EOF) ++l;
    rewind(stdin);

    return l;
}

int *read(int arr[]) {
    int c, cn;
    cn = 0;

    while((c=getchar())!=EOF) {
        if(isalpha(c)) c=tolower(c);
        arr[cn]=c;
        ++cn;
    }
    return arr;
}

int count(int *p, int l) {
    int x;
    for(x=0; x<l; ++x) putchar(*(p+x)); // kontrolle
    return 0;
}

void main() {
    int lf;
    lf = lengthfile();
    int base[lf];
    count(read(base), lf);
}