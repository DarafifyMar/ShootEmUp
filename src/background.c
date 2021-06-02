#include "../header/background.h"

Stars init_stars(int wind_width) {
	Stars back;
	int i;

	for(i = 0; i < MAX_STAR; i++) {
		back.x[i] = rand()%wind_width;
		back.y[i] = 0;
		back.size[i] = rand()%(3-1) + 1;
		back.speed[i] = rand()%(35-5) + 5;
		back.active[i] = 0;
		back.r[i] = 255;
		back.g[i] = 255;
		back.b[i] = 255;
	}
	return back;
}

void draw_stars(Stars back) {
	int i;
	for(i = 0; i < MAX_STAR; i++){
		if(back.active[i] == 1){
			MLV_draw_filled_circle(back.x[i], back.y[i], back.size[i], MLV_rgba(back.r[i], back.g[i], back.b[i], MLV_ALPHA_OPAQUE));
		}
	}
}

Stars moove_stars(Stars back, int wind_height) {
	int i;
	for(i = 0; i < MAX_STAR; i++) {
		if(back.y[i] > wind_height){
			back.y[i] = 0;
			back.active[i] = 0;
		}else{
			back.y[i] += back.speed[i];
		}
	}
	return back;
}

Stars set_active(Stars back) {
	int i;
	int prob;
	for(i = 0; i < MAX_STAR; i++) {
		if((prob = rand()%8) == 0){
			back.active[i] = 1;
		}
	}
	return back;
}
