#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
	PHYSICS,
	CHEMISTRY,
	MATH,
	ENGLISH,
	HISTORY
}SUBJECT_T;

typedef enum {
	FIRST_CLASS,
	SECOND_CLASS,
	THIRD_CLASS,
	FOURTH_CLASS,
	FIFTH_CLASS
}CLASS_T;

typedef enum {
	TEACHER_1,
	TEACHER_2,
	TEACHER_3,
	TEACHER_4,
	TEACHER_5
}TEACHER_T;

typedef struct StudentBuilder_t StudentBuilder_t;
typedef struct Student_t Student_t;

typedef StudentBuilder_t *(*setOtherParam)(StudentBuilder_t *, SUBJECT_T, CLASS_T, TEACHER_T, const char *, int, int);
typedef Student_t *(*build)(StudentBuilder_t *);

typedef const char *(*getString)(int );

typedef struct Student_t {
	char name[20];
	SUBJECT_T subject;
	CLASS_T class;
	int age;
	int Id;
	TEACHER_T teacher;
	Student_t *next;
}Student_t;

typedef struct StudentList {
	Student_t *student;
	Student_t *head;
}StudentList;

typedef struct StudentDataBehavior {
	setOtherParam paramSetting;
	build Build;
	getString getSub;
	getString getClass;
	getString getTeacher;
}StudentDataBehavior;

typedef struct StudentBuilder_t {
	StudentList slist;
	StudentDataBehavior behaviors;

} StudentBuilder_t;

static StudentBuilder_t *assignParams(StudentBuilder_t *sb, SUBJECT_T sub, CLASS_T class, TEACHER_T teacher, const char *name, int age, int Id )
{
	Student_t *st = (Student_t *)malloc(sizeof(Student_t));
	if(!st){
		printf("Heap/dynamic memory allocation failed\n");
		return NULL;
	}
	strncpy(st->name, name, sizeof(name));
	st->subject = sub;
	st->class = class;
	st->teacher = teacher;
	st->age = age;
	st->Id = Id;
	st->next = NULL;
	sb->slist.student->next = st;
	sb->slist.student = st;
	if(!sb->slist.head)
		sb->slist.head = st;

	return sb;
}
static Student_t *Build(StudentBuilder_t *sb)
{
	return sb->slist.student;
}

static const char *getSubString(int sub)
{
	switch(sub)
	{
		case PHYSICS:
			return "Physics";
		case CHEMISTRY:
			return "Chemistry";
		case MATH:
			return "Math";
		case ENGLISH:
			return "English";
		case HISTORY:
			return "History";
		default:
			return NULL;
	}
}
static const char *getClassString(int class)
{
	switch(class)
	{
		case FIRST_CLASS:
			return "FirstClass";
		case SECOND_CLASS:
			return "SecondClass";
		case THIRD_CLASS:
			return "ThirdClass";
		case FOURTH_CLASS:
			return "FourthClass";
		case FIFTH_CLASS:
			return "FifthClass";
		default:
			return NULL;
	}
}
static const char *getTeacherString(int teacher)
{
	switch(teacher)
	{
		case TEACHER_1:
			return "Teacher_1";
		case TEACHER_2:
			return "Teacher_2";
		case TEACHER_3:
			return "Teacher_3";
		case TEACHER_4:
			return "Teacher_4";
		case TEACHER_5:
			return "Teacher_5";
		default:
			return NULL;
	}
}
StudentBuilder_t createStudentBuilder(void) 
{
	StudentBuilder_t sb;
	memset(&sb, 0, sizeof(sb));
	sb.slist.student = (Student_t *)malloc(sizeof(Student_t));
	if(!sb.slist.student)
		printf("Memory allocation failed\n");
	
	if(!sb.slist.head)
		sb.slist.head = NULL;

	sb.behaviors.paramSetting = assignParams;
	sb.behaviors.Build = Build;
	sb.behaviors.getSub = getSubString;
	sb.behaviors.getClass = getClassString;
	sb.behaviors.getTeacher = getTeacherString;


	return sb;
}

void display(StudentBuilder_t sb)
{
	Student_t *st = sb.slist.head;
	if(!st) {
		printf("No data available\n");
		return;
	}
	while(st) {
		printf("student name: %s\n",st->name);
		printf("subject: %s\n", sb.behaviors.getSub(st->subject));
		printf("class: %s\n", sb.behaviors.getClass(st->class));
		printf("teacher: %s\n", sb.behaviors.getTeacher(st->teacher));
		printf("age: %d\n",st->age);
		printf("Id: %d\n", st->Id);
		st = st->next;
	}
}
void deallocateMem(StudentBuilder_t sb)
{
	Student_t *st = sb.slist.head;
	Student_t *tmp = sb.slist.head;
	if(st == NULL)
		return;
	while(st) {
		tmp = st;
		free(tmp);
		st = st->next;
	}
}
int main()
{

	StudentBuilder_t sb = createStudentBuilder(); /*Public interface*/
	sb.behaviors.paramSetting(&sb, PHYSICS, FIRST_CLASS, TEACHER_1, (const char *)"George", 34, 1234 );
	sb.behaviors.paramSetting(&sb, CHEMISTRY, SECOND_CLASS, TEACHER_2, (const char *)"John", 36, 5678 );
	sb.behaviors.paramSetting(&sb, MATH, THIRD_CLASS, TEACHER_3, (const char *)"Vasco", 38, 9101 );
	sb.behaviors.paramSetting(&sb, ENGLISH, FOURTH_CLASS, TEACHER_4, (const char *)"Benjamin", 40, 1213 );
	sb.behaviors.paramSetting(&sb, HISTORY, FIFTH_CLASS, TEACHER_5, (const char *)"David", 50, 1415 );

	display(sb); /*Public Interface*/
	deallocateMem(sb);


	return 0;
}
