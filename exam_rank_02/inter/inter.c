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
	i = 2;
	while (i)
	{
		j = 0;
		while (argv[i][j])
		{
			if (i == 2 && !used[argv[i][j]])
				used[argv[i][j]] = 1;
			if (i == 1 && used[argv[i][j]] == 1)
			{
				write(1, &argv[i][j], 1);
				used[argv[i][j]] = 2;
			}
			j++;
		}
		i--;
	}
	write(1, "\n", 1);
	return 0;
}
