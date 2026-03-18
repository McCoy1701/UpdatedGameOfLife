#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "structs.h"

extern Camera2D_t g_camera;

Camera2D_t Camera2DInit( int screen_width, int screen_height );
void CameraUpdate( Camera2D_t* cam, aRectf_t* rect );
void CameraInput( Camera2D_t* cam );
void CameraShake( Camera2D_t* cam, int intensity, int duration );

uint8_t IsOnCamera( Camera2D_t* cam, aRectf_t* obj );
void WorldToCamera( Camera2D_t* cam, int Wx, int Wy, int* Sx, int* Sy );

#endif

