#include <stdio.h>
#include <stdlib.h>

#if defined(WIN32)
#include <windows.h>
#include <locale.h>
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
void Fflush();
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
#else
        system("clear");
#endif
        updi(&s);
        menuview();
        while ( ( !scanf("%d",&num) ) || num < 0 || num > 7){     //������ �������� �� ���� ����
            printf("error-�� ����� ������ �� �������� � ����\n��� �����: ");
            fflush(stdin);
        }
#if defined(WIN32)
        system("cls");
#else
        system("clear");
#endif
        switch (num){
            case 0:
                break;
            case 1:
                printf("������� ���������� x\n");
                x = input();
                printf("������� ���������� y\n");
                y = input();
                s.x=x;
                s.y=y;
                updo(&s);
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
                s.speed=temp;
                updo(&s);
                printf("�������� ������� ����������\n");
                SysPause();
                break;
            case 3:
                printf("������� ���������, ������� ������ ����������\n");
                temp = input();
                s.acceleration=temp;
                updo(&s);
                printf("�������� ������� ����������\n");
                SysPause();
                break;
            case 4:
                printf("������� ����, �� �������� ����� ����������� � �������\n");
                temp = input();
                s.port=temp;
                updo(&s);
                printf("�������� ������� ����������\n");
                SysPause();
                break;
            case 5:
                printf("������� �������� �� %d ���������\n",s.batterry);
                SysPause();
                break;
            case 6:
                printf("������ ����� 1 �������� � ��������� � %d ���������\n",s.sensor1);
                printf("������ ����� 2 �������� � ����������� � %d ���������\n",s.sensor2);
                SysPause();
                break;
            case 7:
                printf("���������� x =%d\n",s.x);
                printf("���������� y =%d\n",s.y);
                printf("�������� ������ ����� %d\n",s.speed);
                printf("���� �� ������� �������� ����� %d\n",s.port);
                printf("��������� ������� ������� %d\n",s.sensor1);
                printf("��������� ������� ������� %d\n",s.sensor2);
                printf("������� ����������� ����� %d ���������\n",s.batterry);
                printf("��������� ������ ����� \n",s.acceleration);
                SysPause();
                break;
            default:
                printf("������ ������ �� ��������������\n");
                break;
        }

    }while(num!=0);
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