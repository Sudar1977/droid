#ifndef DROID_H_INCLUDED
#define DROID_H_INCLUDED
#include <stdio.h>

enum {LEFT=0, UP, RIGHT, DOWN};
enum {MAX_TAIL_SIZE=100, START_TAIL_SIZE=5};

struct CONTROL_BUTTONS
{
    int down;
    int up;
    int left;
    int right;
} ;
typedef struct CONTROL_BUTTONS control_buttons_t;

typedef struct TAIL
{
    int x;
    int y;
};
typedef struct TAIL tail_t;


typedef struct DROID
{
    int x;
    int y;
    int direction;
    size_t tsize;
    tail_t *tail;
    char head_symbol;
    control_buttons_t controls;
};
typedef struct DROID droid_t;



#endif // DROID_H_INCLUDED
