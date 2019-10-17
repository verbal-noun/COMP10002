#include <stdio.h>

int main(int argc, char const *argv[])
{
    int row = 0, col = 0;
    
    char **arr;
    

    while(scanf("[%d,%d]\n", &row, &col) == 2){
        printf("%d %d\n", row, col);
    }
    return 0;
}
