#include "./main.h"
#include <unistd.h>

void	func(t_mlx *mlx)
{
	char *str = "hello";
	t_map map;

	map.row = ft_strdup(str);
	ft_lstadd_back(&mlx->map, map);
}

int main(int argc, char const *argv[])
{
	t_mlx mlx;

	func(&mlx);
	return 0;
}
