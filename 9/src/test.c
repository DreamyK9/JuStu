#include <stdio.h>

struct data {
    int array[5];
};

struct wrapper {
    struct data *data;
    int error_level;
};

void struct_passing()
{
    struct data data = {{1, 4, 6, 3, 19}};
    struct wrapper test = {&data, 0};
    data.array[2] = 20;
    
    printf("original: array[2] = %d\ntest: arrray[2] = %d", data.array[2], test.data);
}

void plusplus()
{
    int a = 0;
    while (a < 5)
        printf("a = %d\n", a+=1);
    
    putchar('\n');
    
    a = 0;
    while (a < 5)
        printf("a = %d\n", a++);
}

void comma()
{
    int a = 2, b = 8;
    printf("Before: a = %d, b = %d\n", a, b);

    for(int i = 0; i < 10; i+=2)
        a++, b=i, printf("a = %d, b = %d\n", a, b);
}

void array_assign()
{
    int arr[10][5], next=0;

    for(int i = 0; i < 10; i++)
    {
        arr[(int)next/2][next%2] = i;
        printf("arr[%d][%d]\n", (int)next/5, next%5);
        next++;
    }
}


int main()
{
    array_assign();
}
