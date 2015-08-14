#ifndef GAME_STATE_H_INCLUDED
#define GAME_STATE_H_INCLUDED

#include "linked_list.h"

typedef struct
{
    int max_x;
    int max_y;
    linked_list *player_list;
    float fps;
    bool isRunning;
    linked_list *global_event_list;
} game_state;

#endif // GAME_STATE_H_INCLUDED
