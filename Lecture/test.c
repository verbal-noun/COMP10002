#include <stdio.h>

int main(int argc, char const *argv[])
{
	/* code */
	int sid[10], score[10], i = 0;
	while(scanf("%d %d", &sid[i], &score[i])) {
		i++;
	}

	for(i=0;i<10;i++) {
		printf("%d ", sid[i]);
	}
	return 0;
}