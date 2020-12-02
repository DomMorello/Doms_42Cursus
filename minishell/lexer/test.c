#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	char *s;

	s = malloc(6);
	s[0] = 'h';
	s[1] = 'e';
	s[2] = 'l';
	s[3] = 'l';
	s[4] = 'o';
	s[5] = 0;

	char *new = malloc(3);
	new[0] = 'h';
	new[1] = 'i';
	new[2] = 0;
	free(s);
	s = new;
	printf("%s\n", s);
	return 0;
}
