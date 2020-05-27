#include <stdio.h>
#include "./main.h"

int test(int a, char b)
{
    printf("in the test\n");
    return 0;
}

int main(int argc, char const *argv[])
{

    int (*ptr)(int, char) = test;
    ptr(3, 'a');


    // double posX = 22, posY = 12;      //x and y start position
    // double dirX = -1, dirY = 0;       //initial direction vector
    // double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

    // double time = 0;    //time of current frame
    // double oldTime = 0; //time of previous frame

    // for (int x = 0; x <= WIN_WIDTH; x++)
    // {
    //     double cameraX = 2 * x / (double)WIN_WIDTH - 1;
    //     double rayDirX = dirX + planeX * cameraX; 
    //     double rayDirY = dirY + planeY * cameraX; 

    //     printf("cameraX: %f rayDirX %f rayDirY %f\n", cameraX, rayDirX, rayDirY);
    // }

    return 0;
}
