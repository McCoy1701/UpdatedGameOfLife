#ifndef __TILESET_H__
#define __TILESET_H__

#include "structs.h"

enum
{
  TILESET_MAIN = 0,
  TILESET_MAX
};

extern Tileset_t* g_tileset[TILESET_MAX];

Tileset_t* TilesetInit( const char* filename,
                        const int tile_w, const int tile_h );
void TilesetDestroy( Tileset_t* t_set );

void RenderTiles( Camera2D_t* cam, World_t* world );

#endif

