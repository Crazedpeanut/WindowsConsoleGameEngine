#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED

typedef enum
{
    USER_INPUT
} event_category;

typedef struct
{
    event_category evnt_cat;
    char data;
} event;

event* init_event(void *d);

#endif // EVENT_H_INCLUDED
