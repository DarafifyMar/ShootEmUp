#include "../header/graph.h"
#include "../header/menu.h"
#include "../header/event_res.h"

/*int clock_gettime(clockid_t clock_id, struct timespec *tp);*/

int main(int argc, char const *argv[]) {

	struct timespec start, stop;
	double accum;
	Stars background;
	Ship ship;
	ListeShot lst_shot = NULL;
	ListeShot enemy_shot = NULL;
	ListEnemy lst_enemy = NULL;
	int shooting_rate = 0;
	int ips = 0;
	int score = 0;
	srand( time(NULL) );

	background = init_stars(WINDOWWIDTH);
	ship = initShip(WINDOWWIDTH, WINDOWHEIGHT, SHIP_SIZE);
	
	MLV_Music* music;
	MLV_Music* music2;
	
	
	MLV_init_audio();
       	
	music =  MLV_load_music( "img/Song.mp3" );
	music2 =  MLV_load_music( "img/Dofus.mp3" );
	

	/* Main loop over the frames...*/
	MLV_create_window("SHOOT'EM UP", "SEU", WINDOWWIDTH, WINDOWHEIGHT);
	MLV_play_music( music2, 1.0, -1 );
	
	while(draw_menu(WINDOWWIDTH, WINDOWHEIGHT) == 1){
	MLV_play_music( music, 1.0, -1 );

		while(dead(ship, WINDOWWIDTH, WINDOWHEIGHT) != 1) {
			shooting_rate++;
			ips++;
			srand(time(NULL));
			if(ips >= 32 ){
					srand(time(NULL));
					add_new_enemy(&lst_enemy, rand()%(WINDOWWIDTH - SHIP_SIZE), WINDOWWIDTH, SHIP_SIZE);
					ips = 0;
			}
			/* Get the time in nanosecond at the frame begining */
			clock_gettime(CLOCK_REALTIME, &start);
			/* Display of the current frame */
			/* THIS FUNCTION CALL A SINGLE TIME MLV_actualize_window */
			free_shot(&lst_shot);
			free_shot(&enemy_shot);
			free_enemy(&lst_enemy);
			check_hit(&lst_enemy, &lst_shot, &score);
			enemy_hit_ship(&enemy_shot, &ship);
			background = set_active(background);
			draw_window(background, ship, lst_enemy, lst_shot, enemy_shot, score);
			background = moove_stars(background, WINDOWHEIGHT);

			/* We get here at most one keyboard event each frame */
			if(MLV_get_keyboard_state(MLV_KEYBOARD_SPACE) == MLV_PRESSED && shooting_rate >= 5) {
				add_new_shot(&lst_shot, ship, 15);
				shooting_rate = 0;
			}
			/* Moves of the entities on the board */
			moove_ship(&ship, WINDOWWIDTH, WINDOWHEIGHT);
			enemy_linear_moove(&lst_enemy, WINDOWHEIGHT);
			moove_shot(&lst_shot);
			move_enemy_shot(&enemy_shot, WINDOWHEIGHT);
			if(ips % 12 == 0){
				full_shot(&enemy_shot, lst_enemy, 15);
			}

			/* Get the time in nanosecond at the frame ending */
			clock_gettime(CLOCK_REALTIME, &stop);
			/* We compute here the time spent for the current frame */
			accum = (stop.tv_sec-start.tv_sec) + ((stop.tv_nsec-start.tv_sec)/BILLION);
			/* We force here to wait if the frame was too short */
			if(accum < (1.0/45.0)) {
				MLV_wait_milliseconds((int)(((1.0/48.0) - accum) * 1000));
			}
			MLV_clear_window(MLV_COLOR_BLACK);
		}
	}
	return 0;
}
