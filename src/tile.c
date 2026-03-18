/*
 * tile.c:
 *
 * Copyright (c) 2026 Jacob Kellum <jkellum819@gmail.com>
 *                    Mathew Storm <smattymat@gmail.com>
 ************************************************************************
 */

#include <SDL2/SDL_render.h>
#include <stdio.h>
#include <stdlib.h>
#include <Archimedes.h>
#include <Daedalus.h>

#include "defines.h"
#include "structs.h"

#include "camera.h"
#include "tile.h"

Tileset_t* g_tileset[TILESET_MAX] = {0};

Tileset_t* TilesetInit( const char* filename,
                        const int tile_w, const int tile_h )
{
  aSpriteSheet_t* temp_sheet = a_SpriteSheetCreate( filename, tile_w, tile_h );
  
  Tileset_t* new_set = malloc( sizeof( Tileset_t ) );
  if ( new_set == NULL ) return NULL;

  new_set->img_array = malloc( sizeof( ImageArray_t ) * temp_sheet->img_count );
  if ( new_set->img_array == NULL ) return NULL;
  
  new_set->glyph = malloc( sizeof( uint16_t ) * temp_sheet->img_count );
  if ( new_set->glyph == NULL )
  {
    free( new_set->img_array );
    free( new_set );
    return NULL;
  }

  new_set->tile_count = temp_sheet->img_count;
  new_set->row = temp_sheet->h_count;
  new_set->col = temp_sheet->v_count;
  new_set->tile_w = tile_w;
  new_set->tile_h = tile_h;

  for ( int i = 0; i < temp_sheet->img_count; i++ )
  {
    int row = i % temp_sheet->v_count;
    int col = i / temp_sheet->v_count;
    new_set->img_array[i].img = a_ImageFromSpriteSheet( temp_sheet, row, col );
    new_set->glyph[i] = 0;
  }

  a_SpriteSheetDestroy( temp_sheet );

  return new_set;
}

void e_TilesetDestroy( Tileset_t* t_set )
{
  if ( t_set == NULL ) return;

  free( t_set->glyph );
  free( t_set->img_array );
  free( t_set );
}

void RenderTiles( Camera2D_t* cam, World_t* world )
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
          .w = (TILE_WIDTH  * cam->zoom),
          .h = (TILE_HEIGHT * cam->zoom)
        };

        int index = y * ( ARENA_WIDTH / TILE_WIDTH ) + x;
        aImage_t* img = g_tileset[TILESET_MAIN]->img_array[world->tiles[index].type].img;
        a_BlitRect( img, NULL, &dest, 1 );
      }
    }
  }
}

