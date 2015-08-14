#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "game_engine.h"
#include "player.h"

int main()
{
    //TODO: Add Event List Class
    //TODO: Add event subscriptions

    game_state *game_state;
    player *player;

    game_state = init_game_engine();

	player = new_player(game_state, "BOT", GLOBAL_DEFAULT_BOT);

	player = new_player(game_state, "John", GLOBAL_HUMAN_PLAYER);

    start_game_loop(game_state);

    return 0;
}
