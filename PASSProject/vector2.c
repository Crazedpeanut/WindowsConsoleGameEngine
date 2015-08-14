#include "vector2.h"
#include <stdlib.h>

int DEFAULT_VECTOR2_X = 0;
int DEFAULT_VECTOR2_Y = 0;

vector2* init_vector2()
{
    vector2 *new_vector2;

    new_vector2 = (vector2*)malloc(sizeof(vector2));
    new_vector2->x = DEFAULT_VECTOR2_X;
    new_vector2->y = DEFAULT_VECTOR2_Y;

    return new_vector2;
}
