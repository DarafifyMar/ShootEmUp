#ifndef __SHIP__
#define __SHIP__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <MLV/MLV_all.h>

#define SHOT_SIZE 50
#define SHIP_SIZE 75

typedef struct {
	int x;
	int y;
}Pos;

typedef struct {
	Pos posShip;
	int shipSpeed;
	int pv;
	int size;
}Ship;

typedef struct {
	Pos posEnemy;
	int enemySpeed;
	int enemyHealthPoint;
	int enemySize;
}EnemyShip;

typedef struct enemy{
		EnemyShip enemy_ship;
		struct enemy * suivant;
}Enemy, *ListEnemy;

typedef struct shot {
	Pos posShot;
	int shotSpeed;
	int activity;
	struct shot * suivant;
}Shot, *ListeShot;
/*------------------------------------------------------------------------------*/
Ship initShip(int wind_width, int wind_height, int sizeShip);

void draw_ship(Ship ship);

void moove_ship(Ship *ship, int wind_width, int wind_height);
/*------------------------------------------------------------------------------*/
ListEnemy alloueEnemy(int x, int wind_width, int taille);

void add_new_enemy(ListEnemy * lst_enemy, int x,int wind_width, int taille);

void draw_enemy(ListEnemy lst_enemy);

void enemy_linear_moove(ListEnemy * lst_enemy, int wind_height);

void free_enemy(ListEnemy * lst);

int count_enemy(ListEnemy lst_enemy);

/*------------------------------------------------------------------------------*/
ListeShot alloueShot(Ship ship, int speed);

void add_new_shot(ListeShot * lst, Ship ship, int speed);

void draw_shot( ListeShot lst, char * imgName, int size, int decalage);

void moove_shot( ListeShot * lst);

void free_shot(ListeShot * lst);

void check_hit(ListEnemy * lst_enemy, ListeShot * lst_shot, int * score);

int colision(EnemyShip enemy, Pos p);

void draw_explosion(Pos p);

ListeShot alloueEnemyShot(EnemyShip ship, int speed);

void add_enemy_shot(ListeShot * lst, EnemyShip ship, int speed);

void full_shot(ListeShot * lst, ListEnemy lst_enemy, int speed);

void move_enemy_shot(ListeShot * lst, int wind_height);

void draw_pv(Ship ship);

int enemy_hit(Pos shot, Ship ship);

void enemy_hit_ship(ListeShot * lst_enemy_shot, Ship * ship);

int dead(Ship ship, int wind_width, int wind_height);

void game_over(int wind_width, int wind_height);

void draw_score(int score, int wind_width);
#endif
