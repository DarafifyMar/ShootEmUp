#ifndef __GRAPH__
#define __GRAPH__

#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include <assert.h>
#include "../header/ship.h"
#include "../header/background.h"

#define WINDOWHEIGHT 800
#define WINDOWWIDTH 1000
#define BILLION 1000000000000

void draw_window(Stars background, Ship ship, ListEnemy enemy, ListeShot lst_shot, ListeShot lst_enemy_shot, int score);
#endif
