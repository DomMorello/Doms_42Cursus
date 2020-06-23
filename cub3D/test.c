#include "./main.h"
#include <unistd.h>

int main(int argc, char const *argv[])
{
	// int r = 255;
	// int g = 32;
	// int b = 91;

	// printf("%x\n", r);
	// int ret;
	// ret = 0;

	// ret = r << 16;
	// ret = ret + (g << 8);
	// ret = ret + b;
	

	int input = 0xc8ff;
	int mask;
	for (int i = 31; i >= 0; i--)
	{
		mask = 1 << i;
		printf("%d", input & mask ? 1 : 0);
		if (i % 8 == 0)
			printf(" ");
	}
	printf("\n");
	// mask = 1 << 2;
	// printf("%d\n", mask);
	return 0;
}
