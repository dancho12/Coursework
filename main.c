#include <stdio.h>
#include <stdlib.h>

#if defined(WIN32)
#include <windows.h>
#include <locale.h>
#endif

#define numMenu 9
//#define numMenu2 3

struct robot{
    int x;
    int y;
    int speed;
    int port;
    int sensor1;
    int sensor2;
    int batterry;
    int acceleration;

};

struct Console{
    int width;
    int height;
    HANDLE hOutput;
    HANDLE hInput;
    COORD coord;
    CONSOLE_SCREEN_BUFFER_INFO defaultBufferSize;
    int ch;
};

struct Item {
    char str[50];
    COORD coord;
};



void updi(struct robot *sk);
void updo(struct robot *sk);
int input();
void menuview();
void SysPause();
void Fflush();

//---------------------------------------------------------------------------------------
_Bool console_init(struct Console **c){
    COORD bufferSize = {80,25};
    SMALL_RECT sWin = {0,0,80-1,25-1};
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (c == 0) {
        return FALSE;
    }
    (*c) = calloc(1, sizeof(struct Console));
    (*c)->hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    (*c)->hInput = GetStdHandle(STD_INPUT_HANDLE);
    (*c)->ch = -1;
    GetConsoleScreenBufferInfo((*c)->hOutput, &((*c)->defaultBufferSize));
    SetConsoleWindowInfo((*c)->hOutput, TRUE, &sWin);
    SetConsoleScreenBufferSize((*c)->hOutput, bufferSize);
    GetConsoleScreenBufferInfo((*c)->hOutput, &csbi);
    (*c)->width = csbi.dwSize.X;
    (*c)->height = csbi.dwSize.Y;
    return TRUE;
}

void start_position_cursor(struct Item *m, struct Console **c){
    (*c)->coord.X=(m+1)->coord.X-1;
    (*c)->coord.Y=(m+1)->coord.Y;
    SetConsoleCursorPosition((*c)->hOutput,(*c)->coord);
    printf(">");
}

void menu_page(struct Item **m, struct Console *c){
#if defined(WIN32)
    system("cls");
#else
    system("clear");
#endif
    char str[][70]={
            " |���� ���������� �������| ",
            "��������� ������",
            "��������� �������� ������",
            "��������� ��������� ������",
            "��������� ��������� ������",
            "�������� ������� ������",
            "�������� ��������� ��������",
            "�������� ��� �������������� ������",
            "�����"
    };
    int j;

    if(((*m)= calloc(numMenu, sizeof(struct Item)))==NULL)
        printf("\nERROR_1");

    for ( j = 0; j < numMenu; j++) {
        strcpy((*m + j)->str, str[j]);
        (*m + j)->coord.X = c->width / 2 - strlen(str[j]) / 2;
        (*m + j)->coord.Y = c->height / 2 - (numMenu * 2 - 1) / 2 + (2 * j);
        SetConsoleCursorPosition(c->hOutput, (*m + j)->coord);
        printf("%s", (*m + j)->str);
    }

    start_position_cursor(*m,&c);
}


void set_text(int numMenuyy,int j,struct Item **m, struct Console *c,char *str[])
{
    strcpy((*m + j)->str, str[j]);
    (*m + j)->coord.X = c->width / 2 - strlen(str[j]) / 2;
    (*m + j)->coord.Y = c->height / 2 - (numMenuyy * 2 - 1) / 2 + (2 * j);
    SetConsoleCursorPosition(c->hOutput, (*m + j)->coord);
    printf("%s", (*m + j)->str);

}

void menu_page2(struct Item **m, struct Console *c,char *str[],int numMenu2){


#if defined(WIN32)
        system("cls");
#else
        system("clear");
#endif


    if(((*m)= calloc(numMenu2, sizeof(struct Item)))==NULL)
        printf("\nERROR_1");
    for ( int j = 0; j < numMenu2; j++) {
        set_text(4,j,m,c,str);
    }

        start_position_cursor(*m,&c);

}

int menu_page_set(struct Item **m, struct Console *c,int ch,char *str[],int numMenu2){


    int x;
    if(((*m)= calloc(numMenu2, sizeof(struct Item)))==NULL)
        printf("\nERROR_1");
    for ( int j = 0; j < numMenu2; j++) {
        set_text(4,j,m,c,str);
    }
    set_text(4,ch,m,c,str);
    x= input();
    start_position_cursor(*m+(ch-1),&c);
    return x;
}

void console_clear(struct Console *c){
#if defined(WIN32)
    system("cls");
#else
    system("clear");
#endif
}

void cursor_down(struct Item *m, struct Console *c,int numMenuu){
    if((c->coord.Y<(m+numMenuu-1)->coord.Y)&&(c->coord.Y>=(m+(numMenuu-(numMenuu-1)))->coord.Y)){
        SetConsoleCursorPosition(c->hOutput,c->coord);
        printf(" ");
        c->coord.Y=c->coord.Y+2;
        int i;
        for(i=1; i<numMenuu; i++){
            if(c->coord.Y==(m+i)->coord.Y){
                c->coord.X=(m+i)->coord.X-1;
                SetConsoleCursorPosition(c->hOutput,c->coord);
                printf(">");
            }
        }
    }
}


void cursor_up(struct Item *m, struct Console *c,int numMenuu){
    if((c->coord.Y<=(m+numMenuu-1)->coord.Y)&&(c->coord.Y>(m+(numMenuu-(numMenuu-1)))->coord.Y)){
        SetConsoleCursorPosition(c->hOutput,c->coord);
        printf(" ");
        c->coord.Y=c->coord.Y-2;
        int i;
        for(i=1; i<numMenu; i++){
            if(c->coord.Y==(m+i)->coord.Y){
                c->coord.X=(m+i)->coord.X-1;
                SetConsoleCursorPosition(c->hOutput,c->coord);
                printf(">");
            }
        }
    }
}

_Bool console_event(struct Console **c){
    INPUT_RECORD eventBuffer;
    DWORD numEventsRead=0;

    if(ReadConsoleInput((*c)->hInput, &eventBuffer, 1, &numEventsRead))
        if(numEventsRead==1)
            if(eventBuffer.EventType==KEY_EVENT)
                if(eventBuffer.Event.KeyEvent.bKeyDown){
                    (*c)->ch=eventBuffer.Event.KeyEvent.wVirtualKeyCode;
                    return TRUE;
                }
                else return FALSE;
}

void imp(int num, struct robot *s);
void control_movement(struct Item *m, struct Console *c, struct robot *s){

    char *str[] [70]={
            " |���� ���������� �������| ","������� x:","������� y:","�����"};
    BOOL isRun = TRUE;
    while (isRun){
        if(console_event(&c))
            switch (c->ch){
                case VK_ESCAPE:
                    isRun=FALSE;
                    break;
                case VK_DOWN:
                    cursor_down(m,c,4);
                    break;
                case VK_UP:
                    cursor_up(m,c,4);
                    break;
                case VK_RETURN:{
                    if(c->coord.Y==m[1].coord.Y) {
                        SetConsoleCursorPosition((*c).hOutput,m[1].coord);
                        (*s).x=menu_page_set(&m,c,1,*str,4);;
                        updo(s);
                    }
                    if(c->coord.Y==m[2].coord.Y){

                        SetConsoleCursorPosition((*c).hOutput,m[2].coord);
                        (*s).y=menu_page_set(&m,c,2,*str,4);;
                        updo(s);
                    }
                    if(c->coord.Y==m[3].coord.Y)
                        isRun=FALSE;
                }
                    break;
            }
    }
}

int control_uni(struct Item *m, struct Console *c,char *str[],int tt){
    int x =0;
    BOOL isRun = TRUE;
    while (isRun){
        if(console_event(&c))
            switch (c->ch){
                case VK_ESCAPE:
                    isRun=FALSE;
                    break;
                case VK_DOWN:
                    cursor_down(m,c,tt);
                    break;
                case VK_UP:
                    cursor_up(m,c,tt);
                    break;
                case VK_RETURN:{
                    if(c->coord.Y==m[1].coord.Y) {
                        SetConsoleCursorPosition((*c).hOutput,m[1].coord);
                        x=menu_page_set(&m,c,1,str,tt);

                    }
                    if((c->coord.Y==m[2].coord.Y)&&tt==4) {
                        SetConsoleCursorPosition((*c).hOutput,m[2].coord);
                        x=menu_page_set(&m,c,2,str,tt);

                    }
                    if((c->coord.Y==m[2].coord.Y)&&tt==3){
                        isRun=FALSE;
                    }
                    if((c->coord.Y==m[3].coord.Y)&&tt==4){
                        isRun=FALSE;
                    }

                }
                    break;
            }
    }
    return x;
}

void menu_movement(struct Item *m, struct Console *c, struct robot *s){
    BOOL isRun = TRUE;
    while (isRun){
        if(console_event(&c))
            switch (c->ch){
                case VK_ESCAPE:
                    isRun=FALSE;
                    break;
                case VK_DOWN:
                    cursor_down(m,c,9);
                    break;
                case VK_UP:
                    cursor_up(m,c,9);
                    break;
                case VK_RETURN:{
                    if(c->coord.Y==m[1].coord.Y) {
                        char *str[] [70]={
                                " |���� ���������� �������| ","������� x:","������� y:","�����"};
                        menu_page2(&m,c,*str,4);

//                        (*s).x=control_uni(m,c,*str,4);
//                        (*s).y=control_uni(m,c,*str,4);
//                        updo(s);
                        control_movement(m,c,s);
                        SetConsoleCursorPosition((*c).hOutput,m[1].coord);
                        menu_page(&m,c);
                    }
                    if(c->coord.Y==m[2].coord.Y){
                        char *str[] [70]={
                                " |���� ���������� �������| ","������� ��������, ������� ������ ����������:","�����"};
                        menu_page2(&m,c,*str,3);
                        (*s).speed=control_uni(m,c,*str,3);
                        updo(s);
                        SetConsoleCursorPosition((*c).hOutput,m[2].coord);
                        menu_page(&m,c);
                    }
                    if(c->coord.Y==m[3].coord.Y){
                        console_clear(c);
                        imp(3,s);
                        menu_page(&m,c);
                    }
                    if(c->coord.Y==m[4].coord.Y){
                        console_clear(c);
                        imp(3,s);
                        menu_page(&m,c);
                    }
                    if(c->coord.Y==m[5].coord.Y){
                        console_clear(c);
                        imp(5,s);
                        menu_page(&m,c);
                    }
                    if(c->coord.Y==m[6].coord.Y){
                        console_clear(c);
                        imp(6,s);
                        menu_page(&m,c);
                    }
                    if(c->coord.Y==m[7].coord.Y){
                        console_clear(c);
                        imp(7,s);
                        menu_page(&m,c);
                    }
                    if(c->coord.Y==m[8].coord.Y)
                        isRun=FALSE;
                }
                    break;
            }
    }
}









//-----------------------------
int main() {
#if defined(WIN32)
    setlocale(LC_ALL,"Rus");
#endif

    struct robot s;
    struct Console *c;
    struct Item *m;
    struct Item *set;

    int num;
    int x,y,temp;
    //do{
#if defined(WIN32)
        system("cls");
#else
        system("clear");
#endif
        updi(&s);

        console_init(&c);
        menu_page(&m,c);
        menu_movement(m,c,&s);

        //menuview();
//        while ( ( !scanf("%d",&num) ) || num < 0 || num > 7){     //������ �������� �� ���� ����
//            printf("error-�� ����� ������ �� �������� � ����\n��� �����: ");
//            fflush(stdin);
//        }
//#if defined(WIN32)
//        system("cls");
//#else
//        system("clear");
//#endif
//        switch (num){
//            case 0:
//                break;
//            case 1:
//                printf("������� ���������� x\n");
//                x = input();
//                printf("������� ���������� y\n");
//                y = input();
//                s.x=x;
//                s.y=y;
//                updo(&s);
//                printf("�������� ������� ����������\n");
//                SysPause();
//                break;
//            case 2:
//                printf("������� ��������, ������� ������ ����������\n");
//                temp = input();
//                while (  temp < 0 ){     //������ �������� �� ������������� ��������
//                    printf("error-������ �����\n��������� ����: ");
//                    Fflush();
//                    temp = input();
//                }
//                s.speed=temp;
//                updo(&s);
//                printf("�������� ������� ����������\n");
//                SysPause();
//                break;
//            case 3:
//                printf("������� ���������, ������� ������ ����������\n");
//                temp = input();
//                s.acceleration=temp;
//                updo(&s);
//                printf("�������� ������� ����������\n");
//                SysPause();
//                break;
//            case 4:
//                printf("������� ����, �� �������� ����� ����������� � �������\n");
//                temp = input();
//                s.port=temp;
//                updo(&s);
//                printf("�������� ������� ����������\n");
//                SysPause();
//                break;
//            case 5:
//                printf("������� �������� �� %d ���������\n",s.batterry);
//                SysPause();
//                break;
//            case 6:
//                printf("������ ����� 1 �������� � ��������� � %d ���������\n",s.sensor1);
//                printf("������ ����� 2 �������� � ����������� � %d ���������\n",s.sensor2);
//                SysPause();
//                break;
//            case 7:
//                printf("���������� x =%d\n",s.x);
//                printf("���������� y =%d\n",s.y);
//                printf("�������� ������ ����� %d\n",s.speed);
//                printf("���� �� ������� �������� ����� %d\n",s.port);
//                printf("��������� ������� ������� %d\n",s.sensor1);
//                printf("��������� ������� ������� %d\n",s.sensor2);
//                printf("������� ����������� ����� %d ���������\n",s.batterry);
//                printf("��������� ������ ����� \n",s.acceleration);
//                SysPause();
//                break;
//            default:
//                printf("������ ������ �� ��������������\n");
//                break;
//        }
//
//    }while(num!=0);
}

void imp(int num, struct robot *s)
{
    int x,y,temp;
    switch (num){
            case 0:
                break;
            case 1:
                printf("������� ���������� x\n");
                x = input();
                printf("������� ���������� y\n");
                y = input();
                (*s).x=x;
                (*s).y=y;
                updo(s);
                printf("�������� ������� ����������\n");
                SysPause();
                break;
            case 2:
                printf("������� ��������, ������� ������ ����������\n");
                temp = input();
                while (  temp < 0 ){     //������ �������� �� ������������� ��������
                    printf("error-������ �����\n��������� ����: ");
                    Fflush();
                    temp = input();
                }
                (*s).speed=temp;
                updo(s);
                printf("�������� ������� ����������\n");
                SysPause();
                break;
            case 3:
                printf("������� ���������, ������� ������ ����������\n");
                temp = input();
                (*s).acceleration=temp;
                updo(s);
                printf("�������� ������� ����������\n");
                SysPause();
                break;
            case 4:
                printf("������� ����, �� �������� ����� ����������� � �������\n");
                temp = input();
                (*s).port=temp;
                updo(s);
                printf("�������� ������� ����������\n");
                SysPause();
                break;
            case 5:
                printf("������� �������� �� %d ���������\n",(*s).batterry);
                SysPause();
                break;
            case 6:
                printf("������ ����� 1 �������� � ��������� � %d ���������\n",(*s).sensor1);
                printf("������ ����� 2 �������� � ����������� � %d ���������\n",(*s).sensor2);
                SysPause();
                break;
            case 7:
                printf("���������� x =%d\n",(*s).x);
                printf("���������� y =%d\n",(*s).y);
                printf("�������� ������ ����� %d\n",(*s).speed);
                printf("���� �� ������� �������� ����� %d\n",(*s).port);
                printf("��������� ������� ������� %d\n",(*s).sensor1);
                printf("��������� ������� ������� %d\n",(*s).sensor2);
                printf("������� ����������� ����� %d ���������\n",(*s).batterry);
                printf("��������� ������ ����� \n",(*s).acceleration);
                SysPause();
                break;
            default:
                //printf("������ ������ �� ��������������\n");
                break;
        }
}

void SysPause(){
#if defined(WIN32)
    system("Pause");
#else
    printf("��� ����������� ������� Enter\n");
    getchar();
    getchar();
#endif
}
void Fflush(){
#if defined(WIN32)
    fflush(stdin);
#endif
    char ch;
    while (((ch = getchar()) != '\n') && (ch != EOF)) {}
}

int input(){
    int a = 0;
    while (!scanf("%d", &a)||a<0 ) {     //������ �������� �� ���� ����
        printf("������ �����\n��������� ����: ");
        Fflush();
    }
    return a;
}

void updi(struct robot *sk){
    FILE *fileptr;
    fileptr = fopen("robot.txt","r");
    if (fileptr == NULL) {
        printf ("������ - ���� �� ������ \n");
    }
    else{
        fscanf(fileptr,"%d",&sk->x);
        fscanf(fileptr,"%d",&sk->y);
        fscanf(fileptr,"%d",&sk->speed);
        fscanf(fileptr,"%d",&sk->port);
        fscanf(fileptr,"%d",&sk->sensor1);
        fscanf(fileptr,"%d",&sk->sensor2);
        fscanf(fileptr,"%d",&sk->batterry);
        fscanf(fileptr,"%d",&sk->acceleration);
        fclose(fileptr);
    }

}
void updo(struct robot *sk){
    FILE *fileptr;
    fileptr = fopen("robot.txt","w");
    if (fileptr == NULL) {
        printf ("������ - ���� �� ������\n");
    }
    else {
        fprintf(fileptr, "%d\n", (*sk).x);
        fprintf(fileptr, "%d\n", (*sk).y);
        fprintf(fileptr, "%d\n", (*sk).speed);
        fprintf(fileptr, "%d\n", (*sk).port);
        fprintf(fileptr, "%d\n", (*sk).sensor1);
        fprintf(fileptr, "%d\n", (*sk).sensor2);
        fprintf(fileptr, "%d\n", (*sk).batterry);
        fprintf(fileptr, "%d\n", (*sk).acceleration);
        fclose(fileptr);
    }
}
void menuview(){
    printf("\t���� ���������� �������\n");
    printf("1.��������� ������\n");
    printf("2.��������� �������� ������\n");
    printf("3.��������� ��������� ������\n");
    printf("4.��������� ����� � �������\n");
    printf("5.�������� ������� ������\n");
    printf("6.�������� ��������� ��������\n");
    printf("7.�������� ��� �������������� ������\n");
    printf("0.�����\n");
    printf("������� ����� ������, ������� ������ �������\n");

}



//---------------------------------------
//#include <stdio.h>
//#include <stdlib.h>
//
//#if defined(WIN32)
//#include <windows.h>
//#include <locale.h>
//#endif
//
//struct robot{
//    int x;
//    int y;
//    int speed;
//    int port;
//    int sensor1;
//    int sensor2;
//    int batterry;
//    int acceleration;
//
//};
//void updi(struct robot *sk);
//void updo(struct robot *sk);
//int input();
//void menuview();
//void SysPause();
//void Fflush();
//int main() {
//#if defined(WIN32)
//    setlocale(LC_ALL,"Rus");
//#endif
//
//    struct robot s;
//
//    int num;
//    int x,y,temp;
//    do{
//#if defined(WIN32)
//        system("cls");
//#else
//        system("clear");
//#endif
//        updi(&s);
//        menuview();
//        while ( ( !scanf("%d",&num) ) || num < 0 || num > 7){     //������ �������� �� ���� ����
//            printf("error-�� ����� ������ �� �������� � ����\n��� �����: ");
//            fflush(stdin);
//        }
//#if defined(WIN32)
//        system("cls");
//#else
//        system("clear");
//#endif
//        switch (num){
//            case 0:
//                break;
//            case 1:
//                printf("������� ���������� x\n");
//                x = input();
//                printf("������� ���������� y\n");
//                y = input();
//                s.x=x;
//                s.y=y;
//                updo(&s);
//                printf("�������� ������� ����������\n");
//                SysPause();
//                break;
//            case 2:
//                printf("������� ��������, ������� ������ ����������\n");
//                temp = input();
//                while (  temp < 0 ){     //������ �������� �� ������������� ��������
//                    printf("error-������ �����\n��������� ����: ");
//                    Fflush();
//                    temp = input();
//                }
//                s.speed=temp;
//                updo(&s);
//                printf("�������� ������� ����������\n");
//                SysPause();
//                break;
//            case 3:
//                printf("������� ���������, ������� ������ ����������\n");
//                temp = input();
//                s.acceleration=temp;
//                updo(&s);
//                printf("�������� ������� ����������\n");
//                SysPause();
//                break;
//            case 4:
//                printf("������� ����, �� �������� ����� ����������� � �������\n");
//                temp = input();
//                s.port=temp;
//                updo(&s);
//                printf("�������� ������� ����������\n");
//                SysPause();
//                break;
//            case 5:
//                printf("������� �������� �� %d ���������\n",s.batterry);
//                SysPause();
//                break;
//            case 6:
//                printf("������ ����� 1 �������� � ��������� � %d ���������\n",s.sensor1);
//                printf("������ ����� 2 �������� � ����������� � %d ���������\n",s.sensor2);
//                SysPause();
//                break;
//            case 7:
//                printf("���������� x =%d\n",s.x);
//                printf("���������� y =%d\n",s.y);
//                printf("�������� ������ ����� %d\n",s.speed);
//                printf("���� �� ������� �������� ����� %d\n",s.port);
//                printf("��������� ������� ������� %d\n",s.sensor1);
//                printf("��������� ������� ������� %d\n",s.sensor2);
//                printf("������� ����������� ����� %d ���������\n",s.batterry);
//                printf("��������� ������ ����� \n",s.acceleration);
//                SysPause();
//                break;
//            default:
//                printf("������ ������ �� ��������������\n");
//                break;
//        }
//
//    }while(num!=0);
//}
//
//void SysPause(){
//#if defined(WIN32)
//    system("Pause");
//#else
//    printf("��� ����������� ������� Enter\n");
//    getchar();
//    getchar();
//#endif
//}
//void Fflush(){
//#if defined(WIN32)
//    fflush(stdin);
//#endif
//    char ch;
//    while (((ch = getchar()) != '\n') && (ch != EOF)) {}
//}
//
//int input(){
//    int a = 0;
//    while (!scanf("%d", &a)||a<0 ) {     //������ �������� �� ���� ����
//        printf("������ �����\n��������� ����: ");
//        Fflush();
//    }
//    return a;
//}
//
//void updi(struct robot *sk){
//    FILE *fileptr;
//    fileptr = fopen("robot.txt","r");
//    if (fileptr == NULL) {
//        printf ("������ - ���� �� ������ \n");
//    }
//    else{
//        fscanf(fileptr,"%d",&sk->x);
//        fscanf(fileptr,"%d",&sk->y);
//        fscanf(fileptr,"%d",&sk->speed);
//        fscanf(fileptr,"%d",&sk->port);
//        fscanf(fileptr,"%d",&sk->sensor1);
//        fscanf(fileptr,"%d",&sk->sensor2);
//        fscanf(fileptr,"%d",&sk->batterry);
//        fscanf(fileptr,"%d",&sk->acceleration);
//        fclose(fileptr);
//    }
//
//}
//void updo(struct robot *sk){
//    FILE *fileptr;
//    fileptr = fopen("robot.txt","w");
//    if (fileptr == NULL) {
//        printf ("������ - ���� �� ������\n");
//    }
//    else {
//        fprintf(fileptr, "%d\n", (*sk).x);
//        fprintf(fileptr, "%d\n", (*sk).y);
//        fprintf(fileptr, "%d\n", (*sk).speed);
//        fprintf(fileptr, "%d\n", (*sk).port);
//        fprintf(fileptr, "%d\n", (*sk).sensor1);
//        fprintf(fileptr, "%d\n", (*sk).sensor2);
//        fprintf(fileptr, "%d\n", (*sk).batterry);
//        fprintf(fileptr, "%d\n", (*sk).acceleration);
//        fclose(fileptr);
//    }
//}
//void menuview(){
//    printf("\t���� ���������� �������\n");
//    printf("1.��������� ������\n");
//    printf("2.��������� �������� ������\n");
//    printf("3.��������� ��������� ������\n");
//    printf("4.��������� ����� � �������\n");
//    printf("5.�������� ������� ������\n");
//    printf("6.�������� ��������� ��������\n");
//    printf("7.�������� ��� �������������� ������\n");
//    printf("0.�����\n");
//    printf("������� ����� ������, ������� ������ �������\n");
//
//}