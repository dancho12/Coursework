#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <unistd.h>
#if defined(WIN32)
#include <windows.h>
#endif

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
void updi(struct robot *sk);
void updo(struct robot *sk);
int input();
void menuview();
void SysPause();
int main() {
#if defined(WIN32)
    setlocale(LC_ALL,"Rus");
#endif

    struct robot s;

    int num;
    int x,y,temp;
    do{
#if defined(WIN32)
        system("cls");
#elif defined(_WIN64)
        system("cls");
#else
        system("clear");
#endif
        updi(&s);
        menuview();
        while ( ( !scanf("%d",&num) ) || num < 0 || num > 7){     //делаем проверку на ввод букв
            printf("error-Вы ввели символ не входящий в меню\nВаш выбор: ");
            fflush(stdin);
        }
#if defined(WIN32)
        system("cls");
#elif defined(_WIN64)
        system("cls");
#else
        system("clear");
#endif
        switch (num){
            case 0:
                break;
            case 1:
                printf("Введите координату x\n");
                x = input();
                printf("Введите координату y\n");
                y = input();
                s.x=x;
                s.y=y;
                updo(&s);
                printf("Операция успешно выполненна\n");
                SysPause();
                break;
            case 2:
                printf("Введите скорость, которую хотите установить\n");
                temp = input();
                while (  temp < 0 ){     //делаем проверку на отрицателньую скорость
                    printf("error-Ошибка ввода\nПовторите ввод: ");
                    fflush(stdin);
                    temp = input();
                }
                s.speed=temp;
                updo(&s);
                printf("Операция успешно выполненна\n");
                SysPause();
                break;
            case 3:
                printf("Введите ускорение, которую хотите установить\n");
                temp = input();
                s.acceleration=temp;
                updo(&s);
                printf("Операция успешно выполненна\n");
                SysPause();
                break;
            case 4:
                printf("Введите порт, по которому нужно связываться с роботом\n");
                temp = input();
                s.port=temp;
                updo(&s);
                printf("Операция успешно выполненна\n");
                SysPause();
                break;
            case 5:
                printf("Батерея заряжена на %d процентов\n",s.batterry);
                SysPause();
                break;
            case 6:
                printf("Датчик номер 1 сообщает о влажности в %d процентов\n",s.sensor1);
                printf("Датчик номер 2 сообщает о температуре в %d процентов\n",s.sensor2);
                SysPause();
                break;
            case 7:
                printf("Координтата x =%d\n",s.x);
                printf("Координтата y =%d\n",s.y);
                printf("Скорость робота равна %d\n",s.speed);
                printf("Порт на котором работает робот %d\n",s.port);
                printf("Показание первого датчика %d\n",s.sensor1);
                printf("Показание второго датчика%d\n",s.sensor2);
                printf("Зарядка аккумлятора равна %d процентов\n",s.batterry);
                printf("Ускорение робота равно \n",s.acceleration);
                SysPause();
                break;
            default:
                printf("Такого пункта не предусмотренно\n");
                break;
        }





    }while(num!=0);
}

void SysPause(){
#if defined(WIN32)
    system("Pause");
#elif defined(_WIN64)
    system("Pause");
#else
    printf("Для продолжения нажмите Enter\n");
    getchar();
    getchar();
#endif
}

int input(){
    int a = 0;
    while (!scanf("%d", &a) ) {     //делаем проверку на ввод букв
        printf("error-Ошибка ввода\nПовторите ввод: ");
#if defined(WIN32)
        fflush(stdin);
#endif
        char ch;
        while (((ch = getchar()) != '\n') && (ch != EOF)) {}
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