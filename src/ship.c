#include "../header/ship.h"

Ship initShip(int wind_width, int wind_height, int sizeShip) {
  Ship ship;
  ship.posShip.x = (wind_width/2) - (sizeShip/2);
  ship.posShip.y = wind_height - sizeShip;
  ship.size = sizeShip;
  ship.pv = 10;
  ship.shipSpeed = 10;
  return ship;
}

void draw_ship(Ship ship) {
  MLV_Image *imgShip;
  imgShip = MLV_load_image( "img/ship2.png" );
  MLV_resize_image_with_proportions(imgShip, ship.size, ship.size);
  MLV_draw_image(imgShip, ship.posShip.x, ship.posShip.y);
  MLV_free_image(imgShip);
}

void moove_ship(Ship * ship, int wind_width, int wind_height) {

  if( MLV_get_keyboard_state(MLV_KEYBOARD_z) == MLV_PRESSED && (ship->posShip.y > 0) ){/* HAUT */
    ship->posShip.y -= ship->shipSpeed;
  }
  if( MLV_get_keyboard_state(MLV_KEYBOARD_q) == MLV_PRESSED && (ship->posShip.x > 0) ){/* GAUCHE */
    ship->posShip.x -= ship->shipSpeed;
  }
  if( MLV_get_keyboard_state(MLV_KEYBOARD_s) == MLV_PRESSED && (ship->posShip.y <= (wind_height - ship->size - 5) ) ){/* BAS */
    ship->posShip.y += ship->shipSpeed;
  }
  if( MLV_get_keyboard_state(MLV_KEYBOARD_d) == MLV_PRESSED && (ship->posShip.x <= (wind_width - ship->size - 5) ) ){/* DROITE */
    ship->posShip.x += ship->shipSpeed;
  }
}

ListEnemy alloueEnemy(int x, int wind_width, int taille) {
  ListEnemy new_enemy;
  new_enemy = (ListEnemy) malloc(sizeof(Enemy) );

  if(new_enemy != NULL){
    new_enemy->enemy_ship.posEnemy.x = x;
    new_enemy->enemy_ship.posEnemy.y = 0;
    new_enemy->enemy_ship.enemySpeed = 10;
    new_enemy->enemy_ship.enemyHealthPoint = 1;
    new_enemy->enemy_ship.enemySize = taille;

    new_enemy->suivant = NULL;
  }else{
    free(new_enemy);
    printf("BUG ALLOCATION\n");
  }
  return new_enemy;
}

void add_new_enemy(ListEnemy * lst_enemy,int x, int wind_width, int taille){
  ListEnemy tmp = NULL;
  ListEnemy new_enemy = NULL;

  tmp = (*lst_enemy);
  new_enemy = alloueEnemy(x, wind_width, taille);

  if( (*lst_enemy) == NULL) {
    (*lst_enemy) = new_enemy;
    return;
  }
  while( tmp->suivant != NULL ){
    tmp = tmp->suivant;
  }
  tmp->suivant = new_enemy;
}

void draw_enemy(ListEnemy lst_enemy) {
  MLV_Image *imgEnemy;
  if(lst_enemy == NULL){
    return;
  }else{

    imgEnemy = MLV_load_image( "img/enemy_ship.png" );
    int taille = lst_enemy->enemy_ship.enemySize;
    MLV_resize_image_with_proportions(imgEnemy, taille, taille);

    while(lst_enemy != NULL){
      if(lst_enemy->enemy_ship.enemyHealthPoint != 0){
        MLV_draw_image(imgEnemy, lst_enemy->enemy_ship.posEnemy.x, lst_enemy->enemy_ship.posEnemy.y);
      }
      lst_enemy = lst_enemy->suivant;
    }
    MLV_free_image(imgEnemy);
  }
}

void enemy_linear_moove(ListEnemy * lst_enemy, int wind_height) {
  ListEnemy tmp = *lst_enemy;
  if(*lst_enemy == NULL){
    return;
  }else{

  while(tmp != NULL) {
    if(tmp->enemy_ship.posEnemy.y > wind_height){
      tmp->enemy_ship.enemyHealthPoint = 0;
    }
      tmp->enemy_ship.posEnemy.y += tmp->enemy_ship.enemySpeed;
      tmp = tmp->suivant;
    }
  }
}

ListeShot alloueShot(Ship ship, int speed) {
  ListeShot newShot;
  newShot = (ListeShot) malloc( sizeof(Shot) );
  if( newShot != NULL) {
    newShot->posShot.x = ship.posShip.x + (ship.size / 3 - 5);
    newShot->posShot.y = ship.posShip.y - (ship.size / 2 - 4);
    newShot->shotSpeed = speed;
    newShot->activity = 1;

    newShot->suivant = NULL;
  }else{
    free(newShot);
    printf("BUG ALLOCATION\n" );
  }
  return newShot;
}

void add_new_shot(ListeShot * lst, Ship ship, int speed) {
  ListeShot tmp = NULL;
  ListeShot newShot = NULL;

  tmp = (*lst);
  newShot = alloueShot(ship, speed);

  if( (*lst) == NULL) {
    (*lst) = newShot;
    return;
  }
  while( tmp->suivant != NULL ){
    tmp = tmp->suivant;
  }
  tmp->suivant = newShot;
}

void draw_shot( ListeShot lst, char * imgName, int size, int decalage) {
  MLV_Image *shotImg;

  if(lst == NULL) {
    return;
  }else{
    shotImg = MLV_load_image( imgName );
    MLV_resize_image_with_proportions( shotImg, size, size );

    while(lst != NULL) {
      if(lst->activity == 1){
        MLV_draw_image( shotImg , lst->posShot.x + decalage, lst->posShot.y  );
      }
      lst = lst->suivant;
    }
    MLV_free_image(shotImg);
  }
}

void moove_shot( ListeShot * lst ) {
  ListeShot index = *lst;
  if(*lst == NULL) {
    return;
  }else{
    while( index != NULL) {
      if(index->posShot.y < 0) {
        index->activity = 0;
      }
      index->posShot.y -= index->shotSpeed;
      index = index->suivant;
    }
  }
}

void free_shot(ListeShot * lst){
  ListeShot prev = *lst;
  if(prev == NULL){
    return;
  }
  ListeShot index = prev->suivant;
  if(prev->activity == 0){
    *lst = prev->suivant;
    free(prev);
  }else{
    while(index != NULL){
      if(index->activity == 0){
        prev->suivant = index->suivant;
        free(index);
        index = prev->suivant;
      }else{
        prev = index;
        index = index->suivant;
      }
    }
  }
}

void free_enemy(ListEnemy * lst){
  ListEnemy prev = *lst;
  if(prev == NULL){
    return;
  }
  ListEnemy index = prev->suivant;
  if(prev->enemy_ship.enemyHealthPoint == 0){
    *lst = prev->suivant;
    free(prev);
  }else{
    while(index != NULL){
      if(index->enemy_ship.enemyHealthPoint == 0){
        prev->suivant = index->suivant;
        free(index);
        index = prev->suivant;
      }else{
        prev = index;
        index = index->suivant;
      }
    }
  }
}

int count_enemy(ListEnemy lst_enemy){
  int count = 0;
  while(lst_enemy != NULL){
    if(lst_enemy->enemy_ship.enemyHealthPoint != 0){
      count++;
    }
    lst_enemy = lst_enemy->suivant;
  }
  return count;
}

int colision(EnemyShip enemy, Pos p){
  Pos e = enemy.posEnemy;
  int t = enemy.enemySize;
  int subsize = SHOT_SIZE/2;

  if( ( (p.x + subsize) >= e.x && (p.x + subsize) <= e.x + t) && (p.y >= e.y && p.y <= e.y + t)){
    return 1;
  }else{
    return 0;
  }
}

void draw_explosion(Pos p){
    MLV_Image * explosion;
    explosion = MLV_load_image( "img/explo.png" );
    MLV_resize_image_with_proportions( explosion, SHIP_SIZE, SHIP_SIZE);
    MLV_draw_image( explosion , p.x, p.y );
    MLV_free_image(explosion);
}

void check_hit(ListEnemy * lst_enemy, ListeShot * lst_shot, int * score){
  ListEnemy tmpE = *lst_enemy;
  ListeShot tmpS = *lst_shot;

  while(tmpS != NULL){
    while(tmpE != NULL){
      if(colision(tmpE->enemy_ship, tmpS->posShot) == 1){
        draw_explosion(tmpE->enemy_ship.posEnemy);
        tmpE->enemy_ship.enemyHealthPoint = 0;
        tmpS->activity = 0;
        (*score)++;
      }
      tmpE = tmpE->suivant;
    }
    tmpE = *lst_enemy;
    tmpS = tmpS->suivant;
  }
}

ListeShot alloueEnemyShot(EnemyShip ship, int speed){
  ListeShot newShot;
  newShot = (ListeShot) malloc( sizeof(Shot) );
  if( newShot != NULL) {
    newShot->posShot.x = ship.posEnemy.x;
    newShot->posShot.y = ship.posEnemy.y + (ship.enemySize);
    newShot->shotSpeed = speed;
    newShot->activity = 1;

    newShot->suivant = NULL;
  }else{
    free(newShot);
    printf("BUG ALLOCATION\n" );
  }
  return newShot;
}

void add_enemy_shot(ListeShot * lst, EnemyShip ship, int speed){
  ListeShot tmp = NULL;
  ListeShot newShot = NULL;

  tmp = (*lst);
  newShot = alloueEnemyShot(ship, speed);

  if( (*lst) == NULL) {
    (*lst) = newShot;
    return;
  }
  while( tmp->suivant != NULL ){
    tmp = tmp->suivant;
  }
  tmp->suivant = newShot;
}

void full_shot(ListeShot * lst, ListEnemy lst_enemy, int speed){
  if(lst_enemy != NULL){
    while(lst_enemy != NULL){
      add_enemy_shot(lst, lst_enemy->enemy_ship, speed);
      lst_enemy = lst_enemy->suivant;
    }
  }
}

void move_enemy_shot(ListeShot * lst, int wind_height){
  ListeShot index = *lst;
  if(*lst == NULL) {
    return;
  }else{
    while( index != NULL) {
      if(index->posShot.y > wind_height) {
        index->activity = 0;
      }
      index->posShot.y += index->shotSpeed;
      index = index->suivant;
    }
  }
}

void draw_pv(Ship ship){
  MLV_Image *pv;
  int i;
  pv = MLV_load_image( "img/hp.png" );
  MLV_resize_image_with_proportions( pv, 50, 50 );

  for(i = 0; i < ship.pv; i++) {
      MLV_draw_image( pv , i * 20, 0 );
  }
  MLV_free_image(pv);
}

int enemy_hit(Pos shot, Ship ship){
  int subsize = 20/2;

  if( ( (shot.x + subsize) >= ship.posShip.x && (shot.x + subsize) <= (ship.posShip.x + ship.size) ) && ( (shot.y >= ship.posShip.y) && shot.y <= (ship.posShip.y + ship.size) ) ){
    return 1;
  }else{
    return 0;
  }
}

void enemy_hit_ship(ListeShot * lst_enemy_shot, Ship * ship){
  assert(ship != NULL);
  ListeShot tmp = *lst_enemy_shot;
  while(tmp != NULL){
    if(enemy_hit(tmp->posShot, (*ship) ) == 1 && tmp->activity != 0){
      ship->pv -= 1;
      tmp->activity = 0;
    }
    tmp = tmp->suivant;
  }
}

int dead(Ship ship, int wind_width, int wind_height){
  if(ship.pv <= 0){
    game_over(wind_width, wind_height);
    return 1;
  }else{
    return 0;
  }
}

void game_over(int wind_width, int wind_height){
  MLV_Image *over;
  over = MLV_load_image( "img/game_over.png" );
  MLV_resize_image_with_proportions( over, wind_width, wind_height );
  MLV_clear_window(MLV_COLOR_BLACK);
  MLV_draw_image( over , 0, 0 );
  MLV_actualise_window();
  MLV_wait_milliseconds(10000);
  MLV_free_image(over);
  exit(EXIT_SUCCESS);
}

void draw_score(int score, int wind_width){
  char str[64];
  char str2[8];
  strcpy(str2, "Score :");
  sprintf(str, "%d", score);
  strcat(str2, str);
  MLV_draw_adapted_text_box(wind_width - 100, 0, str2, 2, MLV_COLOR_GREY, MLV_COLOR_BLACK,  MLV_COLOR_LIGHT_GREY ,MLV_TEXT_CENTER);
}
