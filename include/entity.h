#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "structs.h"

enum
{
  ENT_PLAYER = 0,
  ENT_ENEMY,
  ENT_PROJECTILE,
  ENT_INTERACTABLE,
  ENT_MAX
};

enum
{
  S_IDLE = 0,
  S_RUN,
  S_ATTACK,
  S_STUNNED,
  S_MAX
};

Entity_t EntityInit( const int id, const int type,
                     const float x, const float y,
                     const float w, const float h,
                     const float angle, const float friction,
                     const float mass, const char* filename,
                     const char* anim_filename, int health, 
                     int max_health, int state, float speed );

void EntityUpdate( Entity_t* ents );
void DrawEntity( Camera2D_t* cam, Entity_t* ent );
void RenderEntities( Camera2D_t* cam );

#endif
