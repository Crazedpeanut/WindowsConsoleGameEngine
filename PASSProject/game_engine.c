#include <Windows.h>
#include <stdlib.h>
#include "main.h"
#include <stdbool.h>
#include "game_engine.h"
#include "linked_list.h"
#include "player.h"
#include "event.h"
#include "Display.h"
#include <string.h>

int SECOND = 1000;
float DEFAULT_FPS = 30;

game_state* init_game_engine(void)
{
    game_state *new_game_state;

    #ifdef DEBUG
        printf("Init game state\n");
    #endif

    new_game_state = (game_state*)malloc(sizeof(game_state));
    new_game_state->player_list = init_linked_list();
    new_game_state->isRunning = true;
    new_game_state->fps = DEFAULT_FPS;
    new_game_state->global_event_list = init_linked_list();

	init_display();

	new_game_state->max_x = WINDOW_WIDTH;
	new_game_state->max_y = WINDOW_HEIGHT;

    #ifdef DEBUG
        printf("Done Init game state\n");
    #endif

    return new_game_state;
}

void start_game_loop(game_state *game_state)
{
    while(game_state->isRunning)
    {

        process_input(game_state);
		move_players(game_state);
		display_players(game_state);

        reset_events(game_state);
        Sleep(SECOND / game_state->fps);
		undisplay_players(game_state);
    }
}

void move_players(game_state *game_state)
{
    node *current, *first;
    int i;

    #ifdef DEBUG
        i = 0;
        printf("Moving players\n");
    #endif

    if(isEmpty(game_state->player_list))
    {
        return;
    }

    first = game_state->player_list->root_node;
    current = first;

    do
    {
        #ifdef DEBUG
            i++;
            player *plyr = (player*)current->data;
            printf("Moving player: %d %s\n", i, plyr->player_name);
        #endif

        move_player(game_state, (player*)current->data);
        current = current->next;

    }while(current != first);

    #ifdef DEBUG
        printf("Finshed moving all players\n");
    #endif
}

void display_players(game_state *game_state)
{
    node *current, *first;
    int i;

    #ifdef DEBUG
        i = 0;
        printf("Displaying players\n");
    #endif

    if(isEmpty(game_state->player_list))
    {
        return;
    }

    first = game_state->player_list->root_node;
    current = first;

    do
    {
        #ifdef DEBUG
            i++;
            printf("Displaying player: %d\n", i);
        #endif
        display_player((player*)current->data);
        current = current->next;
    }while(current != first);

    #ifdef DEBUG
        i++;
        printf("Done displaying players");
    #endif
}

void undisplay_players(game_state *game_state)
{
	node *current, *first;
	int i;

#ifdef DEBUG
	i = 0;
	printf("Displaying players\n");
#endif

	if (isEmpty(game_state->player_list))
	{
		return;
	}

	first = game_state->player_list->root_node;
	current = first;

	do
	{
#ifdef DEBUG
		i++;
		printf("Displaying player: %d\n", i);
#endif
		undisplay_player((player*)current->data);
		current = current->next;
	} while (current != first);

#ifdef DEBUG
	i++;
	printf("Done displaying players");
#endif
}

void reset_events(game_state *game_state)
{
    #ifdef DEBUG
        printf("Resetting event list\n");
    #endif // DEBUG

    destroy_list(game_state->global_event_list);
    game_state->global_event_list = init_linked_list();
}

void display_player(player *player)
{
	draw_char(player->coordinates->x, player->coordinates->y, 'o');

	if (SHOW_PLAYER_NAMES)
	{
		draw_string(player->coordinates->x - (strlen(player->player_name)/2), player->coordinates->y+1, player->player_name);
	}

}

void undisplay_player(player *player)
{
	int i;

	draw_char(player->coordinates->x, player->coordinates->y, ' ');

	if (SHOW_PLAYER_NAMES)
	{
		for (i = 0; i < strlen(player->player_name); i++)
		{
			draw_char(player->coordinates->x + i - (strlen(player->player_name)/2), player->coordinates->y + 1, ' ');
		}
	}
}

void process_input(game_state *game_state)
{
	char input;

	input = get_user_input();

    switch(input)
    {
        case 'q':
            game_state->isRunning = false;
            break;
        case 'w':
            add_input_to_event_list(game_state, input);
            break;
        case 'a':
            add_input_to_event_list(game_state, input);
            break;
        case 's':
            add_input_to_event_list(game_state, input);
            break;
        case 'd':
            add_input_to_event_list(game_state, input);
            break;
        default:
            break;
    }
}

void add_player(player *plyr, game_state *game_state)
{
    #ifdef DEBUG
        printf("Adding player %s to player list\n", plyr->player_name);
    #endif
	
	plyr->coordinates->x = WINDOW_WIDTH/2;
	plyr->coordinates->y = WINDOW_HEIGHT / 2;

    add_node(game_state->player_list, plyr);
}

player* new_player(game_state *game_state, char* name, int player_settings)
{
	player *player;


#ifdef DEBUG
	printf("Adding player %s to player list\n", plyr->player_name);
#endif

	player = init_player();
	player->player_name = name;
	add_player_setting(player, player_settings);

	player->coordinates->x = WINDOW_WIDTH / 2;
	player->coordinates->y = WINDOW_HEIGHT / 2;

	add_node(game_state->player_list, player);

	return player;
}

linked_list* get_players(game_state *game_state)
{
    return game_state->player_list;
}

void add_input_to_event_list(game_state *game_state, char input)
{
    event *evnt;

    evnt = (event*)malloc(sizeof(event));
	evnt->evnt_cat = USER_INPUT;
    evnt->data = input;

    add_node(game_state->global_event_list, evnt);
}
