#include "../header/graph.h"

void draw_window(Stars background, Ship ship, ListEnemy enemy, ListeShot lst_shot, ListeShot lst_enemy_shot, int score) {
	draw_stars(background);
	draw_ship(ship);
	draw_pv(ship);
	draw_enemy(enemy);
	draw_shot(lst_shot, "img/shot.png", SHOT_SIZE, 0);
	draw_shot(lst_enemy_shot, "img/enemy_shot.png", 20, 25);
	draw_score(score, WINDOWWIDTH);
	MLV_actualise_window();
}
