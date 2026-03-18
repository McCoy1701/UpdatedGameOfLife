/*
 * main.c:
 *
 * Copyright (c) 2026 Jacob Kellum <jkellum819@gmail.com>
 *                    Mathew Storm <smattymat@gmail.com>
 ************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <Archimedes.h>
#include <Daedalus.h>
#include "scene.h"

void aMainloop( void )
{
  float dt = a_GetDeltaTime();
  a_TimerStart( app.time.FPS_cap_timer );
  a_GetFPS();
  a_PrepareScene();
  
  app.delegate.logic( dt );
  app.delegate.draw( dt );
  
  a_PresentScene();
  app.time.frames++;
  
  if ( app.options.frame_cap )
  {
    int frame_tick = a_TimerGetTicks( app.time.FPS_cap_timer );
    if ( frame_tick < LOGIC_RATE )
    {
      SDL_Delay( LOGIC_RATE - frame_tick );
    }
  }
}

int main( void )
{
  srand( (unsigned)time( NULL ) );
  a_Init( SCREEN_WIDTH, SCREEN_HEIGHT, "Archimedes" );

  dLogConfig_t log_cfg = {
    .default_level    = D_LOG_LEVEL_DEBUG,
    .colorize_output  = true,
    .include_timestamp = true
  };
  dLogger_t* logger = d_CreateLogger( log_cfg );
  d_SetGlobalLogger( logger );

  SceneInit();

  #ifdef __EMSCRIPTEN__
    emscripten_set_main_loop( aMainloop, 0, 1 );
  #endif

  #ifndef __EMSCRIPTEN__
    while( app.running ) {
      aMainloop();
    }
  #endif
  
  a_Quit();

  return 0;
}

