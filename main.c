#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "curses.h"
#include <inttypes.h>
#include <string.h>
#include <wchar.h>
#include <unistd.h>
#include "droid.h"

enum { STOP_GAME = 'q'};
double DELAY = 0.05;
enum { MAX_DROIDS = 1};

void printHelp(char *s) {
    mvprintw(0, 0, s);
}

void changeDirection(droid_t* droid, const int32_t key)
{
    if (key == droid->controls.down)
        droid->direction = DOWN;
    else if (key == droid->controls.up)
        droid->direction = UP;
    else if (key == droid->controls.right)
        droid->direction = RIGHT;
    else if (key == droid->controls.left)
        droid->direction = LEFT;
}

int checkDirection(droid_t* droid, int32_t key)
{
    if(droid->controls.down  == key&&droid->direction==UP ||
       droid->controls.up    == key&&droid->direction==DOWN ||
       droid->controls.left  == key&&droid->direction==RIGHT ||
       droid->controls.right == key&&droid->direction==LEFT)
        return 0;
    else
        return 1;
}

void initLevel()
{
    char ch[] = "$";
    int max_x = 0, max_y = 0;
    getmaxyx(stdscr, max_y, max_x); // macro - размер терминала
    for(int x=1;x<max_x;x++)
        for(int y=1;y<max_y;y++)
            mvprintw(y, x, ch);

}

int main()
{
    int x = 0, y = 0, key_pressed = 0;


    droid_t droid[MAX_DROIDS];

    initscr();// Старт curses mod
    keypad(stdscr, TRUE);// Включаем F1, F2, стрелки и т.д.
    raw(); // Откдючаем line buffering
    noecho();// Отключаем echo() режим при вызове getch
    curs_set(FALSE);//Отключаем курсор
    timeout(0);    //Отключаем таймаут после нажатия клавиши в цикле
    char str[255];
    int max_x = 0, max_y = 0;
    getmaxyx(stdscr, max_y, max_x); // macro - размер терминала
    sprintf(str,"  Use arrows for control. Press 'q' for EXIT max_y=%d, max_x=%d",max_y, max_x);
    printHelp(str);

    initHead(droid,2,2);
    initControls(droid);
    initLevel();

    while (key_pressed != STOP_GAME)
    {
        clock_t begin = clock();
        key_pressed = getch(); // Считываем клавишу
        go(droid); // Рисуем дроида
        if(checkDirection(droid, key_pressed))
        {
            changeDirection(droid, key_pressed);
        }
        if(key_pressed==KEY_F(2))
        {
            doupdate();
            refresh();
            scr_dump("save");
            mvprintw(0, 90, "scr_dump");
        }
        if(key_pressed==KEY_F(3))
        {
            //clear();
            mvprintw(0, 90, "scr_restore");
            scr_restore("save");
            doupdate();
            refresh();
        }
//        timeout(5); // Задержка при отрисовке
        while((double)(clock() - begin)/CLOCKS_PER_SEC<DELAY)
        {}

//        goTail(snakes[snake_id]); //?????? ?????
    }
    endwin();
    return 0;
}
