#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include <stdint.h>

#include <Archimedes.h>

#include "defines.h"

typedef struct
{
  float x, y;
  float zoom;
  float angle;
  float w, h;
  aRectf_t clip_rect;
} Viewport_t;

typedef struct
{
  float x, y;
  int w, h;
  float offset_x, offset_y;
  float zoom;
  float zoom_speed;
  struct{
    float intensity;
    int duration;
  } shake;
} Camera2D_t;

typedef struct
{
  aImage_t* img;
} ImageArray_t;

typedef struct
{
  ImageArray_t* img_array;
  uint16_t* glyph; //holds the index to the associated glyph
  int tile_count;
  int row, col;
  int tile_w, tile_h;
} Tileset_t;

typedef struct
{
  int id;
  int type;
  uint8_t active;
  
  aRectf_t rect;
  float speed;
  float vx, vy;
  float angle;

  aRectf_t hitbox;
  uint8_t is_gounded;
  float friction;
  float mass;

  aImage_t* img;
  int z_index;

  aAnimation_t* anim;

  int health;
  int max_health;
  int state;

} Entity_t;

typedef struct _tile_t
{
  uint8_t type;
} Tile_t;

typedef struct _world_t
{
  Tile_t grid_a[WORLD_RENDER_WIDTH * WORLD_RENDER_HEIGHT];
  Tile_t grid_b[WORLD_RENDER_WIDTH * WORLD_RENDER_HEIGHT];
  Tile_t *current_gen;
  Tile_t *next_gen;
  int originx, originy;
  int width, height;
} World_t;

#endif

