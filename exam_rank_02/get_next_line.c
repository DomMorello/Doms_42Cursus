#include "./get_next_line.h"


int main()
{
	char *line = NULL;
	int ret = 0;

	while ((ret = get_next_line(&line)) > 0)
	{
		printf("line:%s\n", line);
		free(line);
		line = NULL;
	}
	printf("line:%s\n", line);
	free(line);
	line = NULL;
	return 0;
}