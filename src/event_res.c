#include "../header/event_res.h"

int event_resolution(MLV_Keyboard_button userChoice) {
  if(userChoice == MLV_KEYBOARD_SPACE){
    return 1;
  }else{
    return 0;
  }
}
