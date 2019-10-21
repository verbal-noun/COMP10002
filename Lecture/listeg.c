#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int data_t;
#include "listops.c"

int main(int argc, char const *argv[])
{
    list_t *list;
    int i;
    list = make_list_empty();
    
    while (scanf("%d", &i) == 1) 
    {
        /* code */
        list = insert_at_head(list, i);
        list = insert_at_head(list, i+1);
        list = insertFoot(list, i+2);
    }
    while (!is_list_empty(list))
    {
        /* code */
        i = get_head(list);
        printf("%d ", i);
        list = get_tail(list);
    }
    
    printf("\n");
    free_list(list);
    list = NULL;

    return 0;
}
