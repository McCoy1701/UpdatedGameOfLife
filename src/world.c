/*
 * world.c:
 *
 * Copyright (c) 2026 Jacob Kellum <jkellum819@gmail.com>
 *                    Mathew Storm <smattymat@gmail.com>
 ************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>

#include <Archimedes.h>
#include <Daedalus.h>

#include "defines.h"
#include "structs.h"

World_t* g_map;

World_t* World_Init( int originx, int originy )
{
  World_t* new_world = malloc( sizeof( World_t ) );
  if ( new_world == NULL ) return NULL;
  
  new_world->width  = WORLD_RENDER_WIDTH;
  new_world->height = WORLD_RENDER_HEIGHT;

  new_world->originx = originx;
  new_world->originy = originy;

  new_world->current_gen = new_world->grid_a;
  new_world->next_gen    = new_world->grid_b;

  for ( int y = 0; y < WORLD_RENDER_HEIGHT; y++ )
  {
    for ( int x = 0; x < WORLD_RENDER_WIDTH; x++ )
    {
      int index = y * WORLD_RENDER_WIDTH + x;
      Tile_t tile = (Tile_t){ .type = 0 };
      
      new_world->current_gen[index] = tile;
      new_world->next_gen[index]    = tile;
    }
  }

  return new_world;
}

void World_Free( World_t* world )
{
  if ( world == NULL ) return;
  
  free( world );
}

void World_Draw( World_t* world, Camera2D_t* cam )
{
  int start_col = cam->x / TILE_WIDTH;
  int start_row = cam->y / TILE_HEIGHT;
  
  int num_cols = (WORLD_RENDER_WIDTH)+1;
  int num_rows = (WORLD_RENDER_HEIGHT)+1;

  for( int c = 0; c < num_cols; c++ )
  {
    for( int r = 0; r < num_rows; r++ )
    {
      int x = start_col + c;
      int y = start_row + r;

      if ( x >= 0 && y >= 0 &&
           x < ( ARENA_WIDTH  / TILE_WIDTH ) &&
           y < ( ARENA_HEIGHT / TILE_HEIGHT) )
      {
        aRectf_t dest = {
          .x = ( x * TILE_WIDTH  - cam->x ) * cam->zoom,
          .y = ( y * TILE_HEIGHT - cam->y ) * cam->zoom,
          .w = (TILE_WIDTH  * cam->zoom-1),
          .h = (TILE_HEIGHT * cam->zoom-1)
        };

        int index = y * ( ARENA_WIDTH / TILE_WIDTH ) + x;
        uint8_t tile_type = world->current_gen[index].type;
        a_DrawFilledRect( dest, tile_type ? white : black );
      }
    }
  }
}

