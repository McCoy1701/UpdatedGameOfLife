#ifndef __WORLD_H__
#define __WORLD_H__

#include "structs.h"

extern World_t* g_map;

World_t* World_Init( int originx, int originy );
void World_Free( World_t* world );
void World_Draw( World_t* world, Camera2D_t* cam );

#endif

