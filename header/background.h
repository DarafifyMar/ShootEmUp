#ifndef __BACKGROUND__
#define __BACKGROUND__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <MLV/MLV_all.h>
#include <time.h>

#define MAX_STAR 200

typedef struct stars{
	int x[MAX_STAR];
	int y[MAX_STAR];
	int size[MAX_STAR];
	int speed[MAX_STAR];
	int active[MAX_STAR];
	int r[MAX_STAR];
	int g[MAX_STAR];
	int b[MAX_STAR];
}Stars;

/*fonction qui va initialiser les etoiles*/
Stars init_stars(int wind_width);

/*fonction qui dessine les etoiles à l'ecran*/
void draw_stars(Stars back);

/*fonction qui deplace les etoiles*/
Stars moove_stars(Stars back, int wind_height);

/*fonction qui va activer les etoiles selon un rand*/
Stars set_active(Stars back);

#endif
