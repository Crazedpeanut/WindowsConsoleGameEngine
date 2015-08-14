#ifndef GAME_ENGINE_H_INCLUDED
#define GAME_ENGINE_H_INCLUDED

#include "game_state.h"
#include "player.h"
#include "linked_list.h"
#include <stdbool.h>

game_state* init_game_engine(void);
void start_game_loop(game_state *game_state);
void process_input(game_state *);
void add_player(player *plyr, game_state *game_state);
player* new_player(game_state *game_state, char* name, int player_settings);
linked_list* get_players(game_state *game_state);
void move_players(game_state *game_state);
void display_players(game_state *game_state);
void display_player(player *player);
void undisplay_players(game_state *game_state);
void undisplay_player(player *player);
void reset_events(game_state *game_state);
void add_input_to_event_list(game_state *game_state, char input);

#endif // GAME_ENGINE_H_INCLUDED
