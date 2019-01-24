#include <stdio.h>
#include <stdlib.h>

#if defined(WIN32)
#include <windows.h>
#include <locale.h>
#endif

#define numMenu 9

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
            " |Меню управления роботом| ",
            "Направить робота",
            "Натсроить скорость робота",
            "Натсроить ускорение робота",
            "Натсроить ускорение робота",
            "Показать процент заряда",
            "Показать показания датчиков",
            "Показать все характеристики робота",
            "Выход"
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


void menu_page2(struct Item **m, struct Console *c,int ch,int cr){

    if(cr!=1)
    {
#if defined(WIN32)
        system("cls");
#else
        system("clear");
#endif
    }

    int y;
    char str[70]={
            " |Меню управления роботом| "};
    int j=1;

    if(((*m)= calloc(numMenu, sizeof(struct Item)))==NULL)
        printf("\nERROR_1");

    for ( j = 0; j < numMenu; j++) {
        strcpy((*m + j)->str, str);
        (*m + j)->coord.X = c->width / 2 - strlen(str) / 2;
        (*m + j)->coord.Y = c->height / 2 - (numMenu * 2 - 1) / 2 + (2 * j);
        SetConsoleCursorPosition(c->hOutput, (*m + j)->coord);
        printf("%s", (*m + j)->str);

    }
    if(ch!=0)
    {
        switch (ch){
            case 1:
                strcpy((*m + ch)->str, str);
                (*m + ch)->coord.X = c->width / 2 - strlen(str) / 2;
                (*m + ch)->coord.Y = c->height / 2 - (numMenu * 2 - 1) / 2 + (2 * ch);
                SetConsoleCursorPosition(c->hOutput, (*m + ch)->coord);
                printf("%s", (*m + ch)->str);
                y= input();
                start_position_cursor(*m,&c);
                break;
            case 2:
                strcpy((*m + ch)->str, str);
                (*m + ch)->coord.X = c->width / 2 - strlen(str) / 2;
                (*m + ch)->coord.Y = c->height / 2 - (numMenu * 2 - 1) / 2 + (2 * ch);
                SetConsoleCursorPosition(c->hOutput, (*m + ch)->coord);
                printf("%s", (*m + ch)->str);
                y= input();
                start_position_cursor(*m+1,&c);
                break;
        }

    } else
    {
        start_position_cursor(*m,&c);
    }
    //y= input();

}

void console_clear(struct Console *c){
#if defined(WIN32)
    system("cls");
#else
    system("clear");
#endif
}

void cursor_down(struct Item *m, struct Console *c){
    if((c->coord.Y<(m+numMenu-1)->coord.Y)&&(c->coord.Y>=(m+(numMenu-8))->coord.Y)){
        SetConsoleCursorPosition(c->hOutput,c->coord);
        printf(" ");
        c->coord.Y=c->coord.Y+2;
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


void cursor_up(struct Item *m, struct Console *c){
    if((c->coord.Y<=(m+numMenu-1)->coord.Y)&&(c->coord.Y>(m+(numMenu-8))->coord.Y)){
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
void menu_movement(struct Item *m, struct Console *c, struct Item *set, struct robot *s){
    int cr =0;
    BOOL isRun = TRUE;
    while (isRun){
        if(console_event(&c))
            switch (c->ch){
                case VK_ESCAPE:
                    isRun=FALSE;
                    break;
                case VK_DOWN:
                    cursor_down(m,c);
                    break;
                case VK_UP:
                    cursor_up(m,c);
                    break;
                case VK_RETURN:{
                    if(c->coord.Y==m[1].coord.Y) {
                        console_clear(c);
                        imp(1,s);
                        SetConsoleCursorPosition((*c).hOutput,m[1].coord);
                        menu_page(&m,c);
//                        menu_page2(&m,c,1,cr);
//                        cr=1;
                    }
                    if(c->coord.Y==m[2].coord.Y){
                        console_clear(c);
                        imp(2,s);
                        SetConsoleCursorPosition((*c).hOutput,m[2].coord);
                        menu_page(&m,c);
//                        menu_page2(&m,c,2,cr);
//                        SetConsoleCursorPosition((*c).hOutput,m[2].coord);
//                        cr=1;
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
        menu_movement(m,c,set,&s);

        //menuview();
//        while ( ( !scanf("%d",&num) ) || num < 0 || num > 7){     //делаем проверку на ввод букв
//            printf("error-Вы ввели символ не входящий в меню\nВаш выбор: ");
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
//                printf("Введите координату x\n");
//                x = input();
//                printf("Введите координату y\n");
//                y = input();
//                s.x=x;
//                s.y=y;
//                updo(&s);
//                printf("Операция успешно выполненна\n");
//                SysPause();
//                break;
//            case 2:
//                printf("Введите скорость, которую хотите установить\n");
//                temp = input();
//                while (  temp < 0 ){     //делаем проверку на отрицателньую скорость
//                    printf("error-Ошибка ввода\nПовторите ввод: ");
//                    Fflush();
//                    temp = input();
//                }
//                s.speed=temp;
//                updo(&s);
//                printf("Операция успешно выполненна\n");
//                SysPause();
//                break;
//            case 3:
//                printf("Введите ускорение, которую хотите установить\n");
//                temp = input();
//                s.acceleration=temp;
//                updo(&s);
//                printf("Операция успешно выполненна\n");
//                SysPause();
//                break;
//            case 4:
//                printf("Введите порт, по которому нужно связываться с роботом\n");
//                temp = input();
//                s.port=temp;
//                updo(&s);
//                printf("Операция успешно выполненна\n");
//                SysPause();
//                break;
//            case 5:
//                printf("Батерея заряжена на %d процентов\n",s.batterry);
//                SysPause();
//                break;
//            case 6:
//                printf("Датчик номер 1 сообщает о влажности в %d процентов\n",s.sensor1);
//                printf("Датчик номер 2 сообщает о температуре в %d процентов\n",s.sensor2);
//                SysPause();
//                break;
//            case 7:
//                printf("Координата x =%d\n",s.x);
//                printf("Координата y =%d\n",s.y);
//                printf("Скорость робота равна %d\n",s.speed);
//                printf("Порт на котором работает робот %d\n",s.port);
//                printf("Показание первого датчика %d\n",s.sensor1);
//                printf("Показание второго датчика %d\n",s.sensor2);
//                printf("Зарядка аккумлятора равна %d процентов\n",s.batterry);
//                printf("Ускорение робота равно \n",s.acceleration);
//                SysPause();
//                break;
//            default:
//                printf("Такого пункта не предусмотренно\n");
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
                printf("Введите координату x\n");
                x = input();
                printf("Введите координату y\n");
                y = input();
                (*s).x=x;
                (*s).y=y;
                updo(s);
                printf("Операция успешно выполненна\n");
                SysPause();
                break;
            case 2:
                printf("Введите скорость, которую хотите установить\n");
                temp = input();
                while (  temp < 0 ){     //делаем проверку на отрицателньую скорость
                    printf("error-Ошибка ввода\nПовторите ввод: ");
                    Fflush();
                    temp = input();
                }
                (*s).speed=temp;
                updo(s);
                printf("Операция успешно выполненна\n");
                SysPause();
                break;
            case 3:
                printf("Введите ускорение, которую хотите установить\n");
                temp = input();
                (*s).acceleration=temp;
                updo(s);
                printf("Операция успешно выполненна\n");
                SysPause();
                break;
            case 4:
                printf("Введите порт, по которому нужно связываться с роботом\n");
                temp = input();
                (*s).port=temp;
                updo(s);
                printf("Операция успешно выполненна\n");
                SysPause();
                break;
            case 5:
                printf("Батерея заряжена на %d процентов\n",(*s).batterry);
                SysPause();
                break;
            case 6:
                printf("Датчик номер 1 сообщает о влажности в %d процентов\n",(*s).sensor1);
                printf("Датчик номер 2 сообщает о температуре в %d процентов\n",(*s).sensor2);
                SysPause();
                break;
            case 7:
                printf("Координата x =%d\n",(*s).x);
                printf("Координата y =%d\n",(*s).y);
                printf("Скорость робота равна %d\n",(*s).speed);
                printf("Порт на котором работает робот %d\n",(*s).port);
                printf("Показание первого датчика %d\n",(*s).sensor1);
                printf("Показание второго датчика %d\n",(*s).sensor2);
                printf("Зарядка аккумлятора равна %d процентов\n",(*s).batterry);
                printf("Ускорение робота равно \n",(*s).acceleration);
                SysPause();
                break;
            default:
                //printf("Такого пункта не предусмотренно\n");
                break;
        }
}

void SysPause(){
#if defined(WIN32)
    system("Pause");
#else
    printf("Для продолжения нажмите Enter\n");
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
    while (!scanf("%d", &a)||a<0 ) {     //делаем проверку на ввод букв
        printf("Ошибка ввода\nПовторите ввод: ");
        Fflush();
    }
    return a;
}

void updi(struct robot *sk){
    FILE *fileptr;
    fileptr = fopen("robot.txt","r");
    if (fileptr == NULL) {
        printf ("Ошибка - файл не открыт \n");
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
        printf ("Ошибка - файл не открыт\n");
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
    printf("\tМеню управления роботом\n");
    printf("1.Направить робота\n");
    printf("2.Натсроить скорость робота\n");
    printf("3.Натсроить ускорение робота\n");
    printf("4.Настроить связь с роботом\n");
    printf("5.Показать процент заряда\n");
    printf("6.Показать показания датчиков\n");
    printf("7.Показать все характеристики робота\n");
    printf("0.Выход\n");
    printf("Введите номер пункта, который хотите выбрать\n");

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
//        while ( ( !scanf("%d",&num) ) || num < 0 || num > 7){     //делаем проверку на ввод букв
//            printf("error-Вы ввели символ не входящий в меню\nВаш выбор: ");
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
//                printf("Введите координату x\n");
//                x = input();
//                printf("Введите координату y\n");
//                y = input();
//                s.x=x;
//                s.y=y;
//                updo(&s);
//                printf("Операция успешно выполненна\n");
//                SysPause();
//                break;
//            case 2:
//                printf("Введите скорость, которую хотите установить\n");
//                temp = input();
//                while (  temp < 0 ){     //делаем проверку на отрицателньую скорость
//                    printf("error-Ошибка ввода\nПовторите ввод: ");
//                    Fflush();
//                    temp = input();
//                }
//                s.speed=temp;
//                updo(&s);
//                printf("Операция успешно выполненна\n");
//                SysPause();
//                break;
//            case 3:
//                printf("Введите ускорение, которую хотите установить\n");
//                temp = input();
//                s.acceleration=temp;
//                updo(&s);
//                printf("Операция успешно выполненна\n");
//                SysPause();
//                break;
//            case 4:
//                printf("Введите порт, по которому нужно связываться с роботом\n");
//                temp = input();
//                s.port=temp;
//                updo(&s);
//                printf("Операция успешно выполненна\n");
//                SysPause();
//                break;
//            case 5:
//                printf("Батерея заряжена на %d процентов\n",s.batterry);
//                SysPause();
//                break;
//            case 6:
//                printf("Датчик номер 1 сообщает о влажности в %d процентов\n",s.sensor1);
//                printf("Датчик номер 2 сообщает о температуре в %d процентов\n",s.sensor2);
//                SysPause();
//                break;
//            case 7:
//                printf("Координата x =%d\n",s.x);
//                printf("Координата y =%d\n",s.y);
//                printf("Скорость робота равна %d\n",s.speed);
//                printf("Порт на котором работает робот %d\n",s.port);
//                printf("Показание первого датчика %d\n",s.sensor1);
//                printf("Показание второго датчика %d\n",s.sensor2);
//                printf("Зарядка аккумлятора равна %d процентов\n",s.batterry);
//                printf("Ускорение робота равно \n",s.acceleration);
//                SysPause();
//                break;
//            default:
//                printf("Такого пункта не предусмотренно\n");
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
//    printf("Для продолжения нажмите Enter\n");
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
//    while (!scanf("%d", &a)||a<0 ) {     //делаем проверку на ввод букв
//        printf("Ошибка ввода\nПовторите ввод: ");
//        Fflush();
//    }
//    return a;
//}
//
//void updi(struct robot *sk){
//    FILE *fileptr;
//    fileptr = fopen("robot.txt","r");
//    if (fileptr == NULL) {
//        printf ("Ошибка - файл не открыт \n");
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
//        printf ("Ошибка - файл не открыт\n");
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
//    printf("\tМеню управления роботом\n");
//    printf("1.Направить робота\n");
//    printf("2.Натсроить скорость робота\n");
//    printf("3.Натсроить ускорение робота\n");
//    printf("4.Настроить связь с роботом\n");
//    printf("5.Показать процент заряда\n");
//    printf("6.Показать показания датчиков\n");
//    printf("7.Показать все характеристики робота\n");
//    printf("0.Выход\n");
//    printf("Введите номер пункта, который хотите выбрать\n");
//
//}