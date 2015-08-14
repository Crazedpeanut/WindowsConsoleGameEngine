#include "collider.h"
#include <stdlib.h>

collider* init_collider(collider_type col_type, int bx, int by,int h,int w)
{
	collider *c;

	c = (collider*)malloc(sizeof(collider));

	c->base_x = bx;
	c->base_y = by;
	c->height = h;
	c->width = w;

	c->col_type = col_type;

	return c;
}

void destroy_collider(collider* col)
{
	free(col);
}