#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define E_ARG "Error: argument\n"
#define E_OP "Error: Operation file corrupted\n"

int ft_strlen(char *s)
{
	int len = 0;

	while (s[len])
		len++;
	return len;
}
//에러메세지를 출력하고 에러인 경우에는 항상 1 리턴
int str_error(char *s)
{
	write(1, s, ft_strlen(s));
	return 1;
}

int main(int argc, char *argv[])
{
	FILE *file;
	char *image;
	int read;

	//배경 높이, 넓이, 배경문자, 반복문 안에서 돌아가는 x,y좌표
	int b_width;
	int b_height;
	char b_char;
	int x;
	int y;
	
	//원 관련 정보
	char type;
	float center_x;
	float center_y;
	float r;	//반지름
	char c_char;
	float distance;	//현재좌표와 원의 중심과의 거리

	// 인자 2개가 아닌 경우 에러
	if (argc != 2)
		return (str_error(E_ARG));
	// fopen 실패시 에러
	if (!(file = fopen(argv[1], "r")))
		return (str_error(E_OP));
	// 배경정보가 3개가 아니면 에러
	if (fscanf(file, "%d %d %c\n", &b_width, &b_height, &b_char) != 3)
		return (str_error(E_OP));
	// 0 초과 300 이하가 아니면 에러처리
	if (!(b_width > 0 && b_width <= 300 && b_height > 0 && b_height <= 300))
		return (str_error(E_OP));
	image = (char *)malloc(sizeof(char) * (b_width * b_height));
	memset(image, b_char, b_width * b_height);	//일단 배경색으로 다 칠함
	read = fscanf(file, "%c %f %f %f %c\n", &type, &center_x, &center_y, &r, &c_char);
	while (read == 5)
	{
		//반지름이 0 미만이거나 아 여기서 0 인 경우에 처리를 못해줬네....
		if (r <= 0 || !(type == 'c' || type == 'C'))
		{
			free(image);
			fclose(file);
			return (str_error(E_OP));
		}
		y = 0;
		while (y < b_height)
		{
			x = 0;
			while (x < b_width)
			{
				distance = sqrtf(powf(x - center_x, 2.) + powf(y - center_y, 2.));
				if (distance <= r)
				{
					if (type == 'c')
					{
						if (r - distance < 1.0000000)
							image[y * b_width + x] = c_char;
					}
					else if (type == 'C')
						image[y * b_width + x] = c_char;
				}
				x++;
			}
			y++;
		}
		read = fscanf(file, "%c %f %f %f %c\n", &type, &center_x, &center_y, &r, &c_char);
	}
	// eof를 만나기 전에 다른 값이 들어오면 에러처리
	if (read != -1)
	{
		free(image);
		fclose(file);
		return (str_error(E_OP));
	}
	y = 0;
	while (y < b_height)
	{
		write(1, image + y * b_width, b_width);
		write(1, "\n", 1);
		y++;
	}
	free(image);
	fclose(file);
	return 0;
}

