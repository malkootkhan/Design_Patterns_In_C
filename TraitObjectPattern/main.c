#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct shapeVTable shapeVTable,*pShapeVTable;
typedef struct shape shape,*pShape;
typedef struct circle circle, *pCircle;
typedef struct rectangle rectangle, *pRectangle;

struct shapeVTable {
	void (*draw)(void *);
	void (*area)(void *);
};

struct shape {
	void *self;
	pShapeVTable vTable; 
};

struct rectangle {
	int h;
	int l;
};

void rec_draw(void *self)
{
	pRectangle rec = (pRectangle)self;
	printf("rectangle draw: %d\n", (rec->h + rec->l)*2);
}
void rec_area(void *self)
{
	pRectangle rec = (pRectangle)self;
	printf("rectangle area: %d\n", (rec->h * rec->l));
}

shapeVTable rec_vTable = {.draw = rec_draw, .area = rec_area};

pShape rectangle_new(int h, int l)
{
	pShape s = (pShape)malloc(sizeof(shape));
	pRectangle rec = (pRectangle)malloc(sizeof(rectangle));
	rec->h = h;
	rec->l = l;
	s->self = (pRectangle)rec;
	s->vTable = &rec_vTable;
	return s;
}
struct circle {
	int radius;
};

#define PI (3)
void cir_draw(void *self)
{
	pCircle cir = (pCircle)self;
	printf("circle draw: %d\n", ((cir->radius)*PI));
}
void cir_area(void *self)
{
	pCircle cir = (pCircle)self;
	printf("Circle area: %d\n", PI*(cir->radius * cir->radius));
}
shapeVTable cir_vTable = {.draw = cir_draw, .area = cir_area};
pShape circle_new(int radius)
{
	pShape s = (pShape)malloc(sizeof(shape));
	pCircle cir = (pCircle)malloc(sizeof(circle));
	cir->radius = radius;
	s->self = cir;
	s->vTable = &cir_vTable;
	return s;
}

int main()
{
	pShape s = rectangle_new(10,5);
	s->vTable->area(s->self);
	s->vTable->draw(s->self);

	s = circle_new(5);
	s->vTable->area(s->self);
	s->vTable->draw(s->self);

	return 0;
}
