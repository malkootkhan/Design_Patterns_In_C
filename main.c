#include <stdio.h>
#include <string.h>

struct circle;
struct triangle;
struct shape_operations;
struct shape;

enum shapeType_t {SHAPE_CIRCLE, SHAPE_TRIANGLE};

struct shape_operations {
	int (*area)(void *);
	void (*print)(struct shape *);
};

struct triangle {
	int h;
	int b;
	char name[10];
};

struct circle {
	int radius;
	char name[10];
};

struct shape {
	void *shape; 				//data onject 
	struct shape_operations operation;	//operations object
	enum shapeType_t sType;
};

static struct shape s;
static struct triangle t;
static struct circle c;


int circleArea(void* sha)
{
	struct circle *c = (struct circle *)sha;
	return (c->radius * c->radius * 3);
}
int triangleArea(void* sha)
{
	struct triangle *t = (struct triangle *)sha;
	return (t->b * t->h/2);
}

void printShape(struct shape *ss)
{
	if(ss->sType == SHAPE_CIRCLE){
		struct circle *cr = (struct circle *)ss->shape;
		printf("area of %s : %d\n", cr->name, ss->operation.area(cr));
	}else {
		struct triangle *tr = (struct triangle *)ss->shape;
		printf("area of %s : %d\n", tr->name,ss->operation.area(tr));
	}
	

}

struct shape *create_shape(enum shapeType_t type)
{
	switch(type) 
	{
		case SHAPE_CIRCLE:
			c.radius = 5;
			strcpy(c.name, "CIRCLE");
			s.shape = (struct circle *)&c;
			s.operation.area = circleArea;
			s.operation.print = printShape;
			s.sType = SHAPE_CIRCLE;
			
			return &s;
		case SHAPE_TRIANGLE:
			t.h = 10;
			t.b = 20;
			strcpy(t.name, "TRIANGLE");
			s.shape = (struct triangle *)&t;
			s.operation.area = triangleArea;
			s.operation.print = printShape;
			s.sType = SHAPE_TRIANGLE;
			return &s;
		default:
			return NULL;

	}
}

int main()
{	
	int shape_type;
	int result;

	printf("Enter shape type: \n");
	scanf("%d", &shape_type);

	struct shape *curr_shape = create_shape(shape_type);
	if(!curr_shape) {
		printf("shape pointer is NULL\n");
		return 0;
	}
	curr_shape->operation.print(curr_shape);



	return 0;
}
