#include <stdio.h>

#ifndef MAX
#define MAX 10
#endif

int main(int argc, char const *argv[]){
    char *row1[] = {"num", "name", "sum"};
    int col1[] = { 1, 2, 3 };
    char* col2[] = { "one", "two", "three" };
    int col3[] = { 1243, 14234, 3324 };


    printf("%*s | %*s | %*s\n", -3, row1[0], -MAX, row1[1], MAX, row1[2]);
    printf("%*c | %*c | %*c\n", -3, '-', -MAX, '-', MAX, '-');
    size_t len = sizeof col1 / sizeof col1[0];
    for (int i = 0; i < len; ++i) {
        printf("%-3d | %-10s | %10d\n", col1[i], col2[i], col3[i]);
}
    return 0;
}

 