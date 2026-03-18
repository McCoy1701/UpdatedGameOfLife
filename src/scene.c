/*
 * scene.c:
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

#include "camera.h"
#include "entity.h"
#include "life.h"
#include "player.h"
#include "world.h"

static void s_Logic( float dt );
static void s_Draw( float dt );

static int debug = 0;
static int simulation = 0;

static float update_timer = 0.0f;
static float time_tick    = 0.1f;

void SceneInit( void )
{
  app.delegate.logic = s_Logic;
  app.delegate.draw  = s_Draw;

  g_map = World_Init( 0, 0 );
  PlayerInit( 2, ENT_PLAYER,
              ARENA_WIDTH/2, ARENA_HEIGHT/2,
              16, 32,
              0.0f, 0.0f,
              0.0f, "resources/assets/CharacterTest.png",
              NULL, 100,
              100, S_IDLE, 16.0f );
  
  g_camera = Camera2DInit(SCREEN_WIDTH, SCREEN_HEIGHT);
}

static void s_Logic( float dt )
{
  a_DoInput();
  
  if ( app.keyboard[A_ESCAPE] == 1 )
  {
    app.keyboard[A_ESCAPE] = 0;
    
    app.running = 0;
  }
  
  if ( app.keyboard[A_L] == 1 )
  {
    app.keyboard[A_L] = 0;
    
    life();
  }
  
  if ( app.keyboard[A_1] == 1 )
  {
    app.keyboard[A_1] = 0;
    CameraShake( &g_camera, 5, 60 );
  }
  
  if ( app.keyboard[A_F3] == 1 )
  {
    app.keyboard[A_F3] = 0;
    debug = !debug;
  }
  
  if ( app.keyboard[A_SPACEBAR] == 1 )
  {
    app.keyboard[A_SPACEBAR] = 0;
    simulation = !simulation;
  }
  
  if ( app.keyboard[A_UP] == 1 )
  {
    app.keyboard[A_UP] = 0;
    time_tick -= 0.01;
  }
  
  if ( app.keyboard[A_DOWN] == 1 )
  {
    app.keyboard[A_DOWN] = 0;
    time_tick += 0.01;
  }

  if ( time_tick < 0.01f ) time_tick = 0.01f;
  if ( time_tick > 1.0f ) time_tick  = 1.0f;

  PlayerInput( &g_player );
  CameraInput( &g_camera );

  CameraUpdate( &g_camera, &g_player.rect );

  float world_x = ( app.mouse.x / g_camera.zoom ) + g_camera.x;
  float world_y = ( app.mouse.y / g_camera.zoom ) + g_camera.y;

  int tile_x = (int)world_x / TILE_WIDTH;
  int tile_y = (int)world_y / TILE_HEIGHT;

  if ( app.mouse.button == 1 )
  {
    if ( tile_x >= 0 && tile_y >= 0 &&
         tile_x < ARENA_WIDTH && tile_y < ARENA_HEIGHT )
    {
      int index = tile_y * (WORLD_RENDER_WIDTH) + tile_x;
      g_map->current_gen[index].type = 1;
    }
  }
  
  if ( app.mouse.button == 3 )
  {
    if ( tile_x >= 0 && tile_y >= 0 &&
         tile_x < ARENA_WIDTH && tile_y < ARENA_HEIGHT )
    {
      int index = tile_y * (WORLD_RENDER_WIDTH) + tile_x;
      g_map->current_gen[index].type = 0;
    }
  }
  
  update_timer += dt;
  
  if ( simulation && update_timer >= time_tick )
  {
    NeighborMap( g_map );
    update_timer = 0.0f;
  }

  a_DoWidget();
}

static void s_Draw( float dt )
{
  char buffer[MAX_LINE_LENGTH];
  snprintf( buffer, MAX_NAME_LENGTH, "FPS:%.01f, ZOOM:%.03f TIME:%.03f",
            app.time.avg_FPS, g_camera.zoom, time_tick );

  aTextStyle_t text_style = {
    .type = FONT_CODE_PAGE_437,
    .fg = white,
    .bg = black,
    .align = TEXT_ALIGN_CENTER,
    .wrap_width = 0,
    .scale = 1.0f,
    .padding = 0
  };

  World_Draw( g_map, &g_camera );
  
  if( debug )
  {
    a_DrawText( buffer, 600, 100, text_style );
  }
  
  a_DrawWidgets();
}

