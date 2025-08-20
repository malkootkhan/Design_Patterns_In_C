#include <stdio.h>
#include <stdlib.h>


typedef struct shape_t {
	void (*draw) (void);
}shape_t;


void draw_circle(void)
{
	printf("Circle\n");
}
void draw_square(void)
{
	printf("Square\n");
}

int main()
{
	shape_t circle = {draw_circle};
	shape_t square = {draw_square};

	circle.draw();
	square.draw();




	return 0;
}
