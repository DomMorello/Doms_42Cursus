#include <unistd.h>

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		write(1, "\n", 1);
		return 0;
	}
	int used[255] = {0, };
	int i, j = 0;
	
	i = 1;
	while (i < 3)
	{
		j = 0;
		while (argv[i][j])
		{
			if (used[argv[i][j]] == 0)
			{
				write(1, &argv[i][j], 1);
				used[argv[i][j]] = 1;
			}	
			j++;
		}
		i++;
	}
	write(1, "\n", 1);
	return 0;
}
