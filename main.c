#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>


#define numMenu 4
//#define numSettings 10
struct Console{
    int width;
    int height;
    HANDLE hOutput;
    HANDLE hInput;
    COORD coord;
    CONSOLE_SCREEN_BUFFER_INFO defaultBufferSize;
    int ch;
    int numSettings;
};
struct Item {
    char str[20];
    COORD coord;
};

struct Settings{
    char ip[16];
    char port[5];
    char speed[4];
    char speed_up[4];
    char coord_x[3];
    char coord_y[3];
    char coord_z[3];
    char coord_u[3];
    char coord_k[3];
};

/*int file_opening (struct Settings *st, char ** file_name) {
    FILE *fd;

    fd = fopen(*file_name, "r+t");
    if (fd == 0){
        int i;

        fprintf(stderr,"Can't open file \"%s\". Programm will work with default settings.\n",*file_name);
        for (i = 1; i<=6;i++){
            switch (i){
                case 1:
                    memset(st -> IP, '0', 16);
                case 2:
                    memset(st -> Port, '0', 5);
                case 3:
                    memset(st -> Speed, '0', 4);
                case 4:
                    memset(st -> SpeedUp, '0', 4);
                case 5:
                    memset(st -> CoordX, '0', 3);
                case 6:
                    memset(st -> CoordY, '0', 3);
            }
        }
    }
}*/

_Bool console_init(struct Console **c){
    COORD bufferSize = {90,25};
    SMALL_RECT sWin = {0,0,90-1,25-1};
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
    char str[][10]={
            " |MENU| ",
            "SETTINGS",
            "CONTROL",
            "EXIT"
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

void console_clear(struct Console *c){
    system("cls");
}

void cursor_down(struct Item *m, struct Console *c){
    if((c->coord.Y<(m+numMenu-1)->coord.Y)&&(c->coord.Y>=(m+(numMenu-3))->coord.Y)){
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
    if((c->coord.Y<=(m+numMenu-1)->coord.Y)&&(c->coord.Y>(m+(numMenu-3))->coord.Y)){
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

void cursor_set_down(struct Item *m, struct Console *c){
    if((c->coord.Y<(m+c->numSettings-1)->coord.Y)&&(c->coord.Y>=(m+(c->numSettings-(c->numSettings-1)))->coord.Y)){//как работает?
        SetConsoleCursorPosition(c->hOutput,c->coord);
        printf(" ");
        c->coord.Y=c->coord.Y+2;
        int i;
        for(i=1; i<(c->numSettings); i++){
            if(c->coord.Y==(m+i)->coord.Y){
                c->coord.X=(m+i)->coord.X-1;
                SetConsoleCursorPosition(c->hOutput,c->coord);
                printf(">");
            }
        }
    }
}


void cursor_set_up(struct Item *m, struct Console *c){//спросить как работает
    if((c->coord.Y<=(m+c->numSettings-1)->coord.Y)&&(c->coord.Y>(m+(c->numSettings-(c->numSettings-1)))->coord.Y)){
        SetConsoleCursorPosition(c->hOutput,c->coord);
        printf(" ");
        c->coord.Y=c->coord.Y-2;
        int i;
        for(i=1; i<(c->numSettings); i++){
            if(c->coord.Y==(m+i)->coord.Y){
                c->coord.X=(m+i)->coord.X-1;
                SetConsoleCursorPosition(c->hOutput,c->coord);
                printf(">");
            }
        }
    }
}

void ip_input(struct Settings *st, struct Console **c, struct Item *set){
    char BUFF[15];

    (*c)->coord.X = (*c)->coord.X + strlen(set[1].str)+((*c)->numSettings-1);
    SetConsoleCursorPosition((*c)->hOutput,(*c)->coord);
    scanf("%s",BUFF);
    strcpy(st->ip, BUFF);
    (*c)->coord.X = (*c)->coord.X - strlen(set[1].str)-((*c)->numSettings-1);
    SetConsoleCursorPosition((*c)->hOutput,(*c)->coord);
}

void port_input(struct Settings *st, struct Console **c, struct Item *set){
    char BUFF[5];

    (*c)->coord.X = (*c)->coord.X + strlen(set[2].str)+((*c)->numSettings-1);
    SetConsoleCursorPosition((*c)->hOutput,(*c)->coord);
    scanf("%s",BUFF);
    strcpy(st->port, BUFF);
    (*c)->coord.X = (*c)->coord.X - strlen(set[2].str)-((*c)->numSettings-1);
    SetConsoleCursorPosition((*c)->hOutput,(*c)->coord);
}

void speed_input(struct Settings *st, struct Console **c, struct Item *set){
    char BUFF[4];

    (*c)->coord.X = (*c)->coord.X + strlen(set[2].str)+((*c)->numSettings-1);
    SetConsoleCursorPosition((*c)->hOutput,(*c)->coord);
    scanf("%s",BUFF);
    strcpy(st->speed, BUFF);
    (*c)->coord.X = (*c)->coord.X - strlen(set[2].str)-((*c)->numSettings-1);
    SetConsoleCursorPosition((*c)->hOutput,(*c)->coord);
}

void speed_up_input(struct Settings *st, struct Console **c, struct Item *set){
    char BUFF[4];

    (*c)->coord.X = (*c)->coord.X + strlen(set[2].str)+((*c)->numSettings-1);
    SetConsoleCursorPosition((*c)->hOutput,(*c)->coord);
    scanf("%s",BUFF);
    strcpy(st->speed_up, BUFF);
    (*c)->coord.X = (*c)->coord.X - strlen(set[2].str)-((*c)->numSettings-1);
    SetConsoleCursorPosition((*c)->hOutput,(*c)->coord);
}

void coord_x_input(struct Settings *st, struct Console **c, struct Item *set){
    char BUFF[3];

    (*c)->coord.X = (*c)->coord.X + strlen(set[2].str)+((*c)->numSettings-1);
    SetConsoleCursorPosition((*c)->hOutput,(*c)->coord);
    scanf("%s",BUFF);
    strcpy(st->coord_x, BUFF);
    (*c)->coord.X = (*c)->coord.X - strlen(set[2].str)-((*c)->numSettings-1);
    SetConsoleCursorPosition((*c)->hOutput,(*c)->coord);
}

void coord_y_input(struct Settings *st, struct Console **c, struct Item *set){
    char BUFF[3];

    (*c)->coord.X = (*c)->coord.X + strlen(set[2].str)+((*c)->numSettings-1);
    SetConsoleCursorPosition((*c)->hOutput,(*c)->coord);
    scanf("%s",BUFF);
    strcpy(st->coord_y, BUFF);
    (*c)->coord.X = (*c)->coord.X - strlen(set[2].str)-((*c)->numSettings-1);
    SetConsoleCursorPosition((*c)->hOutput,(*c)->coord);
}
void coord_z_input(struct Settings *st, struct Console **c, struct Item *set){
    char BUFF[3];

    (*c)->coord.X = (*c)->coord.X + strlen(set[2].str)+((*c)->numSettings-1);
    SetConsoleCursorPosition((*c)->hOutput,(*c)->coord);
    scanf("%s",BUFF);
    strcpy(st->coord_z, BUFF);
    (*c)->coord.X = (*c)->coord.X - strlen(set[2].str)-((*c)->numSettings-1);
    SetConsoleCursorPosition((*c)->hOutput,(*c)->coord);
}
void coord_u_input(struct Settings *st, struct Console **c, struct Item *set){
    char BUFF[3];

    (*c)->coord.X = (*c)->coord.X + strlen(set[2].str)+((*c)->numSettings-1);
    SetConsoleCursorPosition((*c)->hOutput,(*c)->coord);
    scanf("%s",BUFF);
    strcpy(st->coord_u, BUFF);
    (*c)->coord.X = (*c)->coord.X - strlen(set[2].str)-((*c)->numSettings-1);
    SetConsoleCursorPosition((*c)->hOutput,(*c)->coord);
}
void coord_k_input(struct Settings *st, struct Console **c, struct Item *set){
    char BUFF[3];

    (*c)->coord.X = (*c)->coord.X + strlen(set[2].str)+((*c)->numSettings-1);
    SetConsoleCursorPosition((*c)->hOutput,(*c)->coord);
    scanf("%s",BUFF);
    strcpy(st->coord_k, BUFF);
    (*c)->coord.X = (*c)->coord.X - strlen(set[2].str)-((*c)->numSettings-1);
    SetConsoleCursorPosition((*c)->hOutput,(*c)->coord);
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

void settings_movement(struct Item *set, struct Console **c, struct Settings *st){
    BOOL isRun = TRUE;

    while (isRun){
        if(console_event(c))
            switch ((*c)->ch) {
                case VK_ESCAPE:
                    system("cls");
                    isRun = FALSE;
                    break;
                case VK_DOWN:
                    cursor_set_down(set, *c);
                    break;
                case VK_UP:
                    cursor_set_up(set, *c);
                    break;
                case VK_RETURN: {
                    if ((*c)->coord.Y == set[1].coord.Y) {
                        ip_input(st,c,set);
                    }
                    if ((*c)->coord.Y == set[2].coord.Y) {
                        port_input(st,c,set);
                    }
                    if ((*c)->coord.Y == set[3].coord.Y){
                        speed_input(st,c,set);
                    }
                    if ((*c)->coord.Y == set[4].coord.Y){
                        speed_up_input(st,c,set);
                    }
                    if ((*c)->coord.Y == set[5].coord.Y){
                        coord_x_input(st,c,set);
                    }
                    if ((*c)->coord.Y == set[6].coord.Y){
                        coord_y_input(st,c,set);
                    }
                    if ((*c)->coord.Y == set[7].coord.Y){
                        coord_z_input(st,c,set);
                    }
                    if ((*c)->coord.Y == set[8].coord.Y){
                        coord_u_input(st,c,set);
                    }
                    if ((*c)->coord.Y == set[9].coord.Y){
                        coord_k_input(st,c,set);
                    }
                    if ((*c)->coord.Y == set[10].coord.Y) {
                        system("cls");
                        isRun = FALSE;
                    }
                    break;
                }
            }
    }
}


//void settings_page(struct Item **set, struct Console **c, struct Settings **st){
//    int sn=0;
//    char buf[10];
//    char str[100];
//    FILE *fp;
//    char name[] = "my.txt";
//    fp = fopen(name, "r+t");
//
//    while(!feof (fp)) {
//        if (fgets(buf, 126, fp))
//        {
//            fscanf(buf, "%f", &str[0][sn]);
//            sn++;
//        }
//
//    }
//    fclose(fp);
//  char str[][30]={
//            "Settings",
//            "IP",
//            "Port",
//            "Speed",
//           "SpeedUp",
//            "CoordX",
//            "CoordY",
//            "CoordZ",
//            "Back"
//    };
//  char str2[][30] ={"Settings",
//                    "Settings"};
//  *strcat(*str2,*str);
//    int j;
//    int r=1;
//    (*c)->numSettings = 10;
//    if(((*set)= calloc((*c)->numSettings, sizeof(struct Item)))==NULL)
//        printf("\nERROR_1");
//
//    for ( j = 0; j < (*c)->numSettings; j++) {
//        strcpy((*set + j)->str, str[j]);
//        if(j == 1) {
//            (*set + j)->coord.X = (*c)->width / 4 - strlen(str[j]) / 4-1;
//        }else{
//            (*set + j)->coord.X = (*c)->width / 4 - strlen(str[j]) / 4;
//        }
//
//        if((*c)->numSettings>10)
//        {
//            r=2;
//        }
//        (*set + j)->coord.Y = (*c)->height / 4 - ((numMenu*r) * 2 - 1) / 4 + (2 * j);//используется numMenu потому что выглядит красиво
//        SetConsoleCursorPosition((*c)->hOutput, (*set + j)->coord);
//        printf("%s", (*set + j)->str);
//    }
//
//
//    start_position_cursor(*set,c);
//    settings_movement(*set,c,*st);
//}

void settings_page(struct Item **set, struct Console **c, struct Settings **st){
    int sn=1;
    char buf[10];
    FILE *fp;
    char name[] = "my.txt";
    fp = fopen(name, "r+t");

    while(!feof (fp)) {
        if (fgets(buf, 126, fp))
        {
            sn++;
        }

    }
    fclose(fp);

    char str[100];

    int j;
    int r=1;
    (*c)->numSettings = sn;
    if(((*set)= calloc((*c)->numSettings, sizeof(struct Item)))==NULL)
        printf("\nERROR_1");

    fp = fopen(name, "r+t");


    for ( j = 0; j < (*c)->numSettings; j++) {
        fgets(str, 126, fp);
        strcpy((*set + j)->str, str);

        if(j == 1) {
            (*set + j)->coord.X = (*c)->width / 4 - strlen(str) / 4-1;
        }else{
            (*set + j)->coord.X = (*c)->width / 4 - strlen(str) / 4;
        }

        if((*c)->numSettings>10)
        {
            r=2;
        }
        (*set + j)->coord.Y = (*c)->height / 4 - ((numMenu*r) * 2 - 1) / 4 + (2 * j);//используется numMenu потому что выглядит красиво
        SetConsoleCursorPosition((*c)->hOutput, (*set + j)->coord);
        printf("%s", (*set + j)->str);
    }
    fclose(fp);

    start_position_cursor(*set,c);
    settings_movement(*set,c,*st);
}


void menu_movement(struct Item *m, struct Console *c, struct Item *set, struct Settings *st){
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
                        settings_page(&set,&c,&st);
                        SetConsoleCursorPosition((*c).hOutput,m[1].coord);
                        menu_page(&m,c);
                    }
                    if(c->coord.Y==m[2].coord.Y){
                        //control_page();
                    }
                    if(c->coord.Y==m[3].coord.Y)
                        isRun=FALSE;
                }
                    break;
            }
    }
}



int main () {
    struct Console *c;
    struct Item *m;
    struct Settings **st;
    struct Item *set;
    char * file_name = "settings.txt";

    /* file_opening(st, &file_name);*/
    console_init(&c);
    menu_page(&m,c);
    menu_movement(m,c,set,*st);

    return 0;
}