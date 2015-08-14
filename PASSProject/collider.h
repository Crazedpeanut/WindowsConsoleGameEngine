#ifndef COLLIDER_H_INCLUDED
#define COLLIDER_H_INCLUDED

typedef enum
{
	COLLIDER_BOX
} collider_type;

typedef struct{
	collider_type col_type;
	int base_x;
	int base_y;
	int width;
	int height;
} collider;

collider* init_collider(collider_type col_type, int bx, int by, int h, int w);

#endif //COLLIDER_H_INCLUDED