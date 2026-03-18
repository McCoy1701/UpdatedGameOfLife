/*
 * player.c:
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

#include "entity.h"

Entity_t g_player;

void PlayerInit( const int id, const int type,
                 const float x, const float y,
                 const float w, const float h,
                 const float angle, const float friction,
                 const float mass, const char* filename,
                 const char* anim_filename, int health, 
                 int max_health, int state, float speed )
{
  g_player = EntityInit( id, type, x, y, w, h, angle, friction, mass,
                         filename, anim_filename, health, max_health,
                         state, speed );
}

void PlayerInput( Entity_t* player )
{
  player->vx = 0; player->vy = 0;

  if ( app.keyboard[A_W] == 1 )
  {
    app.keyboard[A_W] = 0;
    player->vy = -player->speed;
  }
  
  if ( app.keyboard[A_A] == 1 )
  {
    app.keyboard[A_A] = 0;
    player->vx = -player->speed;
  }
  
  if ( app.keyboard[A_S] == 1 )
  {
    app.keyboard[A_S] = 0;
    player->vy = player->speed;
  }
  
  if ( app.keyboard[A_D] == 1 )
  {
    app.keyboard[A_D] = 0;
    player->vx = player->speed;
  }

  player->rect.x += player->vx;
  player->rect.y += player->vy;

  if ( player->rect.x < 0 ) player->rect.x = 0;
  if ( player->rect.y < 0 ) player->rect.y = 0;
  if ( player->rect.x > ARENA_WIDTH  - player->rect.w )
  {
    player->rect.x = ARENA_WIDTH  - player->rect.w;
  }
  if ( player->rect.y > ARENA_HEIGHT - player->rect.h )
  {
    player->rect.y = ARENA_HEIGHT - player->rect.h;
  }
}

