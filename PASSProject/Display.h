#ifndef DISPLAY_H

#define DISPLAY_H
#define WINDOW_HEIGHT 25
#define WINDOW_WIDTH 80

void init_display();
void refresh();
void clear_window();
void draw_char(int x, int y, char c);
void draw_string(int x, int y, char *s);
char get_user_input();

#endif