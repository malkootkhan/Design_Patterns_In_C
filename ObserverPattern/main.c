#include <stdio.h>
#include <stdlib.h>


typedef void (*callback)(void* context, void* data);

typedef struct ObserverNode {
    callback observerCallBack;
    void *context;
    struct ObserverNode *next;
}ObserverNode, *pObserverNode;

typedef struct Subject {
    ObserverNode *head;
}Subject, *pSubject;
void subjectCreate(Subject **self);
pSubject subjectConstructor(void)
{
    pSubject sub = (pSubject)malloc(sizeof(Subject));
    if(!sub) {
        printf("subject object memory allocation failed\n");
        return NULL;
    }
    sub->head = NULL;
    return sub;
}


void subjectAttached(pSubject self, callback observerFunction, void *ctx )
{
    pObserverNode newNode = (pObserverNode)malloc(sizeof(ObserverNode));
    if(!newNode) {
        printf("memory allocation for observer node failed\n");
        return;
    }
    newNode->observerCallBack = observerFunction;
    newNode->context = ctx;
    newNode->next = self->head;
    self->head = newNode;

}
void subjectNotifyAll(pSubject self, void *data)
{
    ObserverNode *tmp = self->head;
    if(!tmp){
        printf("There is no node\n");
        return;
    } 

    while(tmp)
    {
        if(!tmp->observerCallBack){
            printf("No Observer \n");
            return;
        }
        tmp->observerCallBack(tmp->context, data);
        tmp = tmp->next;
    }
}
void notifyImplementation(void *ctx, void *data)
{
    printf("name: %s\n", (char*)ctx);
    printf("ID: %d\n", *(int*)data);
}
void subjectDettach(pSubject self, callback cb, void *ctx)
{
    ObserverNode **tmp = &self->head;
    if(!(*tmp)) return;

    while(*tmp){
        if((*tmp)->observerCallBack == cb && (*tmp)->context == ctx){
            pObserverNode del = (*tmp);
            (*tmp) = (*tmp)->next;
            free(del);
            return;        
        }
        (*tmp) = (*tmp)->next;
    }
}
#include <string.h>
int main()
{

    char ctex1[] = "context1-name!";
    int id1 = 32;
    pSubject subject1 = subjectConstructor();
    subjectAttached(subject1, notifyImplementation, (void*)ctex1);
    subjectNotifyAll(subject1, (void*)&id1);

    subjectDettach(subject1, notifyImplementation, ctex1);

    char ctex2[] = "context2_name!";
    int id2 = 499;
    pSubject subject2 = subjectConstructor();
    subjectAttached(subject2, notifyImplementation, (void*)ctex2);
    subjectNotifyAll(subject2, (void*)&id2);

    subjectDettach(subject2, notifyImplementation, ctex2);

    return 0;
}



