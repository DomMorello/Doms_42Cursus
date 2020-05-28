#include <stdio.h>
#include "./main.h"

int functDraw(int key, t_mlx *mola)
{
    static int i = 0;

    printf("key: %d\n", key);
    i++;
    mola->img.data[200 + WIN_WIDTH * i] = 0xFFFFFF;
    printf("i: %d\n", i);
    return 1;
}

int main(int argc, char const *argv[])
{
    t_mlx mlx;
    int (*func_ptr)(int, t_mlx *) = functDraw;

    mlx.mlx_ptr = mlx_init();
    mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "DomMorello");
    mlx.img.img_ptr = mlx_new_image(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
    mlx.img.data = (int *)mlx_get_data_addr(mlx.img.img_ptr, &mlx.img.bpp, &mlx.img.size_l, &mlx.img.endian);

    for (int i = 0; i < 100; i++)
    {
        mlx.img.data[100 + WIN_WIDTH * i] = 0xFFFFFF;
    }

    // mlx_destroy_image(mlx.mlx_ptr, mlx.img.img_ptr);
    // mlx.img.img_ptr = mlx_new_image(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
    // for (int i = 0; i < 100; i++)
    // {
    //     mlx.img.data[200 + WIN_WIDTH * i] = 0xFFFFFF;
    // }
    mlx_key_hook(mlx.win_ptr, func_ptr, &mlx);
    mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.img.img_ptr, 0, 0);
    mlx_loop(mlx.mlx_ptr);

    return 0;
}
