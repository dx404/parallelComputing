#include <stdio.h>
#include <time.h>

int main(){
	time_t x = time(NULL);
	printf("%d\n", x);
	return 0;
}
