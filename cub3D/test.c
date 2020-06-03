#include <stdio.h>
#include "./main.h"

int main(int argc, char const *argv[])
{
    t_mlx mlx;
    t_tex tex;

    mlx.mlx_ptr = mlx_init();
    mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "fuck");
    mlx.img.img_ptr = mlx_new_image(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
    mlx.img.data = (int *)mlx_get_data_addr(mlx.img.img_ptr, &mlx.img.bpp, &mlx.img.size_l, &mlx.img.endian);
    // for (size_t i = 0; i < 100; i++)
    // {
    //     mlx.img.data[100 + i * WIN_WIDTH] = 0xFFFFFF;
    // }
    
    tex.img_ptr = mlx_xpm_file_to_image(mlx.mlx_ptr, "./textures/mossy.xpm", &tex.width, &tex.height);
    tex.data = (int *)mlx_get_data_addr(tex.img_ptr, &tex.bpp, &tex.size_l, &tex.endian);
    
    // mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, tex.img_ptr, 0, 0);
    
    mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.img.img_ptr, 0, 0);
    mlx_loop(mlx.mlx_ptr);
    return 0;
}
