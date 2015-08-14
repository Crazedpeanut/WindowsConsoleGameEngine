#include "event.h"
#include <stdlib.h>

event* init_event(void *d)
{
    event *evnt;

    evnt = (event*)malloc(sizeof(event));
    //evnt->data = d;

    return evnt;
}

void destroy_event(event *evnt)
{
    //free(evnt->data);
    free(evnt);
}
