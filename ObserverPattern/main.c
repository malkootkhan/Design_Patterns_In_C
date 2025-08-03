#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE (10)

typedef void (*callback)(void* context, void* data);

typedef struct Observer {
    callback observerCallBack;
    void *context;
}Observer, *pObserver;

typedef struct Subject {
    Observer observer[MAX_SIZE];
    int count;
}Subject, *pSubject;

pSubject subjectConstructor(void)
{
    int i;
    static Subject sub;
    sub.count = 0;
    for(i = 0; i < MAX_SIZE; i++) {
        sub.observer[i].observerCallBack = NULL;
        sub.observer[i].context = NULL;
    }
    return &sub;
}

void subjectAttached(pSubject self, callback observerFunction, void *ctx )
{
    if(self->count >= MAX_SIZE) {
        printf("Valid observer count reached!\n");
        return ;
    }
    self->observer[self->count].observerCallBack = observerFunction;
    self->observer[self->count].context = ctx;
    self->count++;
}
void subjectNotifyAll(pSubject self, void *data)
{
    int i;
    for(i = 0; i < self->count; i++){
        if(self->observer[i].observerCallBack != NULL)
            self->observer[i].observerCallBack(self->observer[i].context, data);
    }
}
void notifyImplementation(void *ctx, void *data)
{
    printf("name: %s\n", (char*)ctx);
    printf("ID: %d\n", *(int*)data);
}
void subjectDettach(pSubject self, callback cb, void *ctx)
{
    int i,j;
    for(i = 0; i < self->count; i++)
    {
        if(self->observer[i].observerCallBack == cb && self->observer[i].context == ctx) {
            for(j = i; j < self->count -1; j++){
                self->observer[j].observerCallBack = self->observer[j+1].observerCallBack;
                self->observer[j].context = self->observer[j+1].context;
            }
        self->count--;
        break;
        }
    }
}
#include <string.h>
int main()
{

    char ctex[] = "context-name!";
    int id = 32;
    pSubject subject = subjectConstructor();
    subjectAttached(subject, notifyImplementation, (void*)ctex);
    subjectNotifyAll(subject, (void*)&id);
    return 0;
}



