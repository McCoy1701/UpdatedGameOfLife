#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "structs.h"

extern Entity_t g_player;

void PlayerInit( const int id, const int type,
                 const float x, const float y,
                 const float w, const float h,
                 const float angle, const float friction,
                 const float mass, const char* filename,
                 const char* anim_filename, int health, 
                 int max_health, int state, float speed );

void PlayerInput( Entity_t* player );

#endif

