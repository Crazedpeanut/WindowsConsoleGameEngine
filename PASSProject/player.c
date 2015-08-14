#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "player.h"
#include "vector2.h"
#include "main.h"
#include "event.h"

void remove_player_from_player_list(void *data);

int DEFAULT_X_DIRECTION = 1;
int DEFAULT_Y_DIRECTION = 1;

static int player_count = 0;

char DEFAULT_PLAYER_NAME[] = "Unknown";

player* init_player(void)
{
    player *plyr;

    #ifdef DEBUG
        printf("Init player\n");
    #endif

    plyr = (player*)malloc(sizeof(player));

	plyr->player_id = player_count++;

    plyr->coordinates = init_vector2();
    plyr->player_name = DEFAULT_PLAYER_NAME;
    plyr->player_settings = 0;

    plyr->direction = init_vector2();
    plyr->direction->x = DEFAULT_X_DIRECTION;
    plyr->direction->y = DEFAULT_Y_DIRECTION;
    plyr->move_distance = GLOBAL_DEFAULT_PLAYER_MOVE_DISTANCE;

	plyr->collider = init_collider(COLLIDER_BOX, 
		plyr->coordinates->x, 
		plyr->coordinates->y, 
		DEFAULT_PLAYER_COLLIDER_HEIGHT, 
		DEFAULT_PLAYER_COLLIDER_WIDTH);

    #ifdef DEBUG
        printf("done Init player with coords: (%d, %d) and direction:(%d, %d)\n", plyr->coordinates->x, plyr->coordinates->y, plyr->direction->x, plyr->direction->y);
    #endif

    return plyr;
}

void set_player_location(player *plyr, vector2 *coordinates)
{
    plyr->coordinates = coordinates;
}

vector2* get_player_location(player *plyr)
{
    return plyr->coordinates;
}

void move_player(game_state *game_state, player *player)
{
    char u_input;

    if(is_human(player))
    {
        u_input = check_for_user_input(game_state->global_event_list);

        perform_human_move(game_state, player, u_input);
    }

    if(is_default_bot(player))
    {
        perform_default_bot_move(game_state, player);
    }
}

void add_player_setting(player *plyr, int setting)
{
    plyr->player_settings = plyr->player_settings | setting;
}

void remove_player_setting(player *plyr, int setting)
{
    plyr->player_settings = !(plyr->player_settings ^ setting);
}

int get_player_settings(player *plyr)
{
    return plyr->player_settings;
}

bool get_player_setting(player *plyr, int setting)
{
    int result;

    result = plyr->player_settings & setting;

    if(result)
    {
        return true;
    }
    else
    {
        return false;
    }
}

char check_for_user_input(linked_list *ll)
{
    node *current, *first;
    event *evnt;
    int i;

    #ifdef DEBUG
        i = 0;
        printf("Checking for use input\n");
    #endif

    if(isEmpty(ll))
    {
        return '\0';
    }

    first = ll->root_node;
    current = first;

    do
    {
        evnt = (event*)current->data;

        if(evnt->evnt_cat == USER_INPUT)
        {
            return evnt->data;
        }

        current = current->next;
    }while(current != first);

    #ifdef DEBUG
        i++;
        printf("Done checking for user input");
    #endif

    return '\0';
}

void perform_default_bot_move(game_state *game_state, player *plyr)
{
   int next_x, next_y;

    #ifdef DEBUG
        printf("Moving player: %s\n", plyr->player_name);
    #endif

    next_x = plyr->coordinates->x + (plyr->direction->x * plyr->move_distance);
    next_y = plyr->coordinates->y + (plyr->direction->y * plyr->move_distance);

    #ifdef DEBUG
        printf("Attempting to move player from (x, y)(%d, %d)\n", plyr->coordinates->x, plyr->coordinates->y);
        printf("with direction (x, y)(%d, %d)\n", plyr->direction->x, plyr->direction->y);
    #endif


    #ifdef DEBUG
        printf("Attempting to move player to (x, y)(%d, %d)\n", next_x, next_y);
    #endif

    if(next_x >= game_state->max_x || next_x <= 0)
    {
        plyr->direction->x *= -1;

        #ifdef DEBUG
            printf("Attempted move hit wall x\n");
        #endif
    }
    else
    {
        plyr->coordinates->x = next_x;

        #ifdef DEBUG
            printf("Player has moved x\n");
        #endif
    }

    if(next_y >= game_state->max_y || next_y <= 0)
    {
        plyr->direction->y *= -1;

        #ifdef DEBUG
            printf("Attempted move hit wall y\n");
        #endif
    }
    else
    {
        plyr->coordinates->y = next_y;

        #ifdef DEBUG
            printf("Player has moved y\n");
        #endif
    }

    #ifdef DEBUG
        printf("Done moving player\n");
    #endif
}

void perform_human_move(game_state *game_state, player *plyr, char u_input)
{
   int next_x, next_y;

   next_x = plyr->coordinates->x;
   next_y = plyr->coordinates->y;

    switch(u_input)
    {
        case 'w':
            next_y = plyr->coordinates->y - plyr->move_distance;
            break;
        case 's':
            next_y = plyr->coordinates->y + plyr->move_distance;
            break;
        case 'a':
            next_x = plyr->coordinates->x - plyr->move_distance;
            break;
        case 'd':
            next_x = plyr->coordinates->x + plyr->move_distance;
            break;
        default:
            next_x = plyr->coordinates->x;
            next_y = plyr->coordinates->y;
            break;
    }

    if(next_x > game_state->max_x)
    {
        next_x = game_state->max_x - 1;
    }

    if(next_x < 0)
    {
        next_x = 1;
    }

    if(next_y > game_state->max_y)
    {
        next_y = game_state->max_y - 1;
    }

    if(next_y < 0)
    {
        next_y = 1;
    }

    plyr->coordinates->x = next_x;
    plyr->coordinates->y = next_y;
}

bool is_default_bot(player *plyr)
{
    return get_player_setting(plyr, GLOBAL_DEFAULT_BOT);
}

bool is_human(player *plyr)
{
    return get_player_setting(plyr, GLOBAL_HUMAN_PLAYER);
}

void destroy_player(game_state *gamestate, player *player)
{
	traverse_comparison(gamestate->player_list, remove_player_from_player_list, player);
	free(player->collider);
	free(player->coordinates);
	free(player->direction);
	free(player);
}

void remove_player_from_player_list(linked_list *ll, node *node, void *comparison_data)
{
	player *current_player, *player_to_remove;

	current_player = node->data;
	player_to_remove = comparison_data;

	if (current_player->player_id == player_to_remove->player_id)
	{
		remove_node(ll, node);
	}

}