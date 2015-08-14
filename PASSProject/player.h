#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "vector2.h"
#include "game_state.h"
#include <stdbool.h>
#include "collider.h"

#define GLOBAL_DEFAULT_BOT 1
#define GLOBAL_HUMAN_PLAYER 2
#define SHOW_PLAYER_NAMES 1
#define GLOBAL_DEFAULT_PLAYER_MOVE_DISTANCE 1
#define DEFAULT_PLAYER_COLLIDER_HEIGHT 1
#define DEFAULT_PLAYER_COLLIDER_WIDTH 1

typedef struct
{
	int player_id;
    char* player_name;
    vector2 *coordinates;
    vector2 *direction;
    int player_settings;
    int move_distance;
	collider *collider;
}player;

player* init_player(void);
void set_player_location(player *plyr, vector2 *coordinates);
vector2* get_player_location(player *plyr);
void move_player(game_state *game_state, player *player);
void add_player_setting(player *plyr, int setting);
void remove_player_setting(player *plyr, int setting);
int get_player_settings(player *plyr);
bool get_player_setting(player *plyr, int setting);
void perform_default_bot_move(game_state *game_state, player *plyr);
void perform_human_move(game_state *game_state, player *plyr, char u_input);
bool is_default_bot(player *plyr);
bool is_human(player *plyr);
char check_for_user_input(linked_list *ll);
void destroy_player(player *player);

#endif // PLAYER_H_INCLUDED
