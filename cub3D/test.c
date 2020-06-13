#include "./main.h"
#include <unistd.h>

int main(int argc, char const *argv[])
{
	char *str = " 324 234 \n";
	char **ret = ft_split(str, ' ');

	int i = 0;
	while (ret[i])
	{
		printf("%s\n", ret[i]);
		i++;
	}
	printf("ret[2]:%p\n", ret[2]);
	
	return 0;
}
