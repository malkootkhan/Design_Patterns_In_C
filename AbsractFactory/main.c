#include <stdio.h>
#include <stdlib.h> 

typedef enum {WINDOWS, LINUX, MAC}Type_t;
typedef struct Button {
    void (*click) (void);
}Button, *pButton;

typedef struct Dialog {
    void (*dialogOpen)(void);
}Dialog, *pDialog;

typedef struct GUIFactory {
    Button button;
    Dialog dialog;
}GUIFactory, *pGUIFactory;

void click_implementationWin(void) {
    printf("absract factory(windows): click method\n");
}
void dialog_implementationWin(void)
{
    printf("abstract factory(windows): dialog method\n");
}
void click_implementationLin(void) {
    printf("absract factory(linux): click method\n");
}
void dialog_implementationLin(void)
{
    printf("abstract factory(linux): dialog method\n");
}
void click_implementationMac(void) {
    printf("absract factory(mac): click method\n");
}
void dialog_implementationMac(void)
{
    printf("abstract factory(mac): dialog method\n");
}


pGUIFactory createFactory(Type_t type)
{
    switch(type)
    {
        case WINDOWS:
            pGUIFactory gFactWin = (pGUIFactory)malloc(sizeof(GUIFactory));
            gFactWin->button.click = click_implementationWin;
            gFactWin->dialog.dialogOpen = dialog_implementationWin;
            return gFactWin;
        case LINUX:
            pGUIFactory gFactLin = (pGUIFactory)malloc(sizeof(GUIFactory));
            gFactLin->button.click = click_implementationLin;
            gFactLin->dialog.dialogOpen = dialog_implementationLin;
            return gFactLin;
        case MAC:
            pGUIFactory gFactMac = (pGUIFactory)malloc(sizeof(GUIFactory));
            gFactMac->button.click = click_implementationMac;
            gFactMac->dialog.dialogOpen = dialog_implementationMac;
            return gFactMac;
        default:
            return NULL;
    }

}

int main()
{
    pGUIFactory factory = createFactory(MAC);
    factory->button.click();
    factory->dialog.dialogOpen();

    factory = createFactory(WINDOWS);
    factory->button.click();
    factory->dialog.dialogOpen();

    factory = createFactory(LINUX);
    factory->button.click();
    factory->dialog.dialogOpen();


    return 0;
}

