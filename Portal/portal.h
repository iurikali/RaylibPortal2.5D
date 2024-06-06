#ifndef PORTAL_H_INCLUDED
#define PORTAL_H_INCLUDED

#include "defines.h"
#include "structs.h"

Portal NewPortal(Color color);

void PortalUpdate(Portal *portals, Player *player, int *turn, int *lanched, char map[ROWS][COLS], int *used, float *theta, Camera3D *cam);

void RenderPortal(Portal *portals);

#endif // PORTAL_H_INCLUDED