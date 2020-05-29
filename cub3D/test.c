#include <stdio.h>
#include "./main.h"

int functDraw(int key, t_mlx *mola)
{
    int i = 0;

    mlx_destroy_image(mola->mlx_ptr, mola->img.img_ptr);
    mola->img.img_ptr = mlx_new_image(mola->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
    mola->img.data = (int *)mlx_get_data_addr(mola->img.img_ptr, &mola->img.bpp, &mola->img.size_l, &mola->img.endian);
    printf("key: %d\n", key);
    for (i = 0; i < 50; i++)
    {
        mola->img.data[200 + WIN_WIDTH * i] = 0xFFFFFF;
    }
    mlx_put_image_to_window(mola->mlx_ptr, mola->win_ptr, mola->img.img_ptr, 0, 0);
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
    mlx_hook(mlx.win_ptr,2, 1L<<0, func_ptr, &mlx);
    mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.img.img_ptr, 0, 0);
    mlx_loop(mlx.mlx_ptr);

    return 0;
}
