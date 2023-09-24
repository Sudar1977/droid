#include "droid.h"
#include "curses.h"

char* heads="@XOG";
char* tail ="*0PO";

void initDroid(droid_t *head, tail_t *tail, size_t size, int x, int y) {
    initTail(tail, MAX_TAIL_SIZE);
    initHead(head, x, y);
    head->tail  = tail;
    head->tsize = size+1;
}

void initTail(tail_t t[], size_t size)
{
    tail_t init_t={0,0};
    for(size_t i=0; i<size; i++)
    {
        t[i]=init_t;
    }
}

void init(droid_t *head, struct tail_t *tail, size_t size, int x, int y) {
    //clear(); // ??????? ???? ?????
    initTail(tail, MAX_TAIL_SIZE);
    initHead(head, x, y);
    head->tail = tail; // ??????????? ? ?????? ?????
    head->tsize = size+1;
}

void initControls(droid_t *head)
{
    head->controls.down  = KEY_DOWN;
    head->controls.up    = KEY_UP;
    head->controls.left  = KEY_LEFT;
    head->controls.right = KEY_RIGHT;
}
void initHead(droid_t *head, int x, int y)
{
    head->x = x;
    head->y = y;
    head->direction = RIGHT;
}

int Collision(droid_t *head)
{
    static int score = 0;
    char ch[100];
    mvinnstr(head->y, head->x, ch,1);
    mvprintw(0, 110, ch);
    if(ch[0]=='$')
        score++;
    char str[100];
    sprintf(str,"%d",score);
    mvprintw(0, 110, str);
    return 0;
}


/*
 Движение головного дроида с учетом текущего направления движения
 */
void go(droid_t *head) {
//    setColor(head->number);
    char ch[] = "@";
    int max_x = 0, max_y = 0;
    getmaxyx(stdscr, max_y, max_x); // macro - размер терминала
    //clear(); // очищаем весь экран
    max_x--,max_y--;
    mvprintw(head->y, head->x, " "); // очищаем один символ
    switch (head->direction) {
        case LEFT:
            if (--(head->x) <= 1) // Циклическое движение, что бы не
                // уходить за пределы экрана
                head->x = max_x;
            break;
        case RIGHT:
            if (++(head->x) >= max_x)
                head->x = 1;
            break;
        case UP:
            if (--(head->y) <= 1)
                head->y = max_y;
            break;
        case DOWN:
            if (++(head->y) >= max_y)
                head->y = 1;
            break;
        default:
            break;

    }
    Collision(head);
    mvprintw(head->y, head->x, ch);
//    mvprintw(max_y, max_x, ch);

    refresh();
}

void goTail(droid_t *head) {
    char ch = '*';
    mvprintw(head->tail[head->tsize-1].y, head->tail[head->tsize-1].x, " ");
    for(size_t i = head->tsize-1; i>0; i--) {
        head->tail[i] = head->tail[i-1];
        if( head->tail[i].y || head->tail[i].x)
            mvprintw(head->tail[i].y, head->tail[i].x, "%c", ch);
    }
    head->tail[0].x = head->x;
    head->tail[0].y = head->y;
}
