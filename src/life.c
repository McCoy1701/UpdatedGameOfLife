/*
 * life.c:
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

int life( void )
{
  printf("Hello, World!\n");
  return 0;
}

void NeighborMap( World_t* world )
{
  uint8_t counts[WORLD_RENDER_WIDTH*WORLD_RENDER_HEIGHT] = {0};
  for ( int y = 0; y < WORLD_RENDER_HEIGHT; y++ )
  {
    for ( int x = 0; x < WORLD_RENDER_WIDTH; x++ )
    {
      int current_index = y * (WORLD_RENDER_WIDTH) + x;
      if( world->current_gen[current_index].type )
      {
        for ( int ny = -1; ny <= 1; ny++ )
        {
          for ( int nx = -1; nx <= 1; nx++ )
          {
            if( ny == 0 && nx == 0 ) continue;
            int target_x = x + nx;
            int target_y = y + ny;
            if ( target_x >= 0 && target_x < WORLD_RENDER_WIDTH &&
                 target_y >= 0 && target_y < WORLD_RENDER_HEIGHT )
            {
              int counts_index = target_y * (WORLD_RENDER_WIDTH) + target_x;
              counts[counts_index]++;
            }
          }
        }
      }
    }
  }

  for ( int i = 0; i < WORLD_RENDER_WIDTH * WORLD_RENDER_HEIGHT; i++ )
  {
    int count = counts[i];
    int alive = world->current_gen[i].type;

    if ( alive && ( count == 2 || count == 3 ) )
    {
      world->next_gen[i].type = 1;
    }
    
    else if ( !alive && count == 3 )
    {
      world->next_gen[i].type = 1;
    }
    
    else
    {
      world->next_gen[i].type = 0;
    }
  }
  
  Tile_t* temp = world->current_gen;
  world->current_gen = world->next_gen;
  world->next_gen = temp;
}

