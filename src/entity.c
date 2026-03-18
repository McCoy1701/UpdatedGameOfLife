/*
 * entity.c:
 *
 * Copyright (c) 2026 Jacob Kellum <jkellum819@gmail.com>
 *                    Mathew Storm <smattymat@gmail.com>
 ************************************************************************
 */

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <stdio.h>
#include <stdlib.h>

#include <Archimedes.h>
#include <Daedalus.h>

#include "defines.h"
#include "structs.h"

Entity_t EntityInit( const int id, const int type,
                     const float x, const float y,
                     const float w, const float h,
                     const float angle, const float friction,
                     const float mass, const char* filename,
                     const char* anim_filename, int health, 
                     int max_health, int state, float speed )
{
  Entity_t new_entity;
  new_entity.id = id;
  new_entity.type = type;
  new_entity.rect = (aRectf_t){
    .x = x,
    .y = y,
    .w = w,
    .h = h
  };
  new_entity.vx = 0;
  new_entity.vy = 0;
  new_entity.speed = speed;
  new_entity.angle = angle;
  new_entity.friction = friction;
  new_entity.mass = mass;
  new_entity.img = a_ImageLoad( filename );
  /*new_entity.anim = a_AnimationCreate( anim_filename,
                                       new_entity.img->rect.w,
                                       new_entity.img->rect.h,
                                       10,
                                       150 );*/
  new_entity.health = health;
  new_entity.max_health = max_health;
  new_entity.state = state;

  return new_entity;
}

