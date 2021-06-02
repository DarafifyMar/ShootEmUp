#include "../header/menu.h"
#include <MLV/MLV_all.h>
#define SIZE_INTERLIGNE 20
#define X 450
#define Y 150


//dessine un fond d'écran
void draw_wallPaper(int width, int height){
    int image_width, image_height;
    MLV_Image *image;

    image = MLV_load_image("img/menuprincipal.png");

    MLV_resize_image_with_proportions(image, width, height);
    MLV_get_image_size(image, &image_width, &image_height);
    MLV_draw_image(image, 0, 0);
    MLV_free_image( image );

}
//dessine l'aide du jeu
void draw_how_to_play(int width, int height){
    MLV_Image *image;
    image = MLV_load_image("img/menu.png");

    MLV_resize_image_with_proportions(image, width, height);
    MLV_draw_image(image, 0, 0);
    MLV_free_image( image );


}
int retour_menuPrincipal(int width, int height){
	const char* text = "Retour au menu principal";
   	int width_box = 0,  height_box = 0 ;
    	int xclic, yclic;

	draw_how_to_play(width, height);

    MLV_draw_adapted_text_box(20, 600, text, SIZE_INTERLIGNE, MLV_COLOR_GREY, MLV_COLOR_BLACK,  MLV_COLOR_LIGHT_GREY ,MLV_TEXT_CENTER);
    MLV_get_size_of_adapted_text_box(text,SIZE_INTERLIGNE, &width_box, &height_box);

	  while(1){

		MLV_actualise_window();
		MLV_wait_mouse(&xclic, &yclic);

        	if(((xclic >= 20) && (xclic <= (20 + width_box)))){
        		if((yclic >= 600) && (yclic <= (600 + height_box))){
        		MLV_actualise_window();
   			draw_menu(width, height);
        return 1;
   			 }
  		}
	}
}


//dessine le menu principal
int draw_menu(int width, int height)
{

    draw_wallPaper(width, height);

    int xclic, yclic;
    int width_box = 0 , height_box = 0;

    const char *text_box = "         HELP       ";
    const char *text_box2 = "        EXIT       ";
    const char *text_box3 = "        PLAY       ";

 //dessine les boites
 MLV_draw_adapted_text_box(X, 3 * Y, text_box, SIZE_INTERLIGNE, MLV_COLOR_GREY, MLV_COLOR_BLACK,  MLV_COLOR_GREY , MLV_TEXT_CENTER);
 MLV_draw_adapted_text_box(X, 4 * Y, text_box2,SIZE_INTERLIGNE, MLV_COLOR_GREY, MLV_COLOR_BLACK,  MLV_COLOR_GREY , MLV_TEXT_CENTER);
 MLV_draw_adapted_text_box(X, 2 * Y, text_box3, SIZE_INTERLIGNE, MLV_COLOR_GREY , MLV_COLOR_BLACK, MLV_COLOR_GREY , MLV_TEXT_CENTER);

//récupère la taille des boites
 MLV_get_size_of_adapted_text_box(text_box, SIZE_INTERLIGNE, &width_box, &height_box);
	while(1)
	{
		MLV_actualise_window();
		MLV_wait_mouse(&xclic, &yclic);

        	if(((xclic >= X) && (xclic <= (X + width_box)))){

        		if((yclic >= 2 * Y) && (yclic <= (2 * Y + height_box))){
        				printf("PLAY ");
					return 1;


			}
        		else if((yclic >= 3 * Y) && (yclic <= (3 * Y + height_box))){
        				printf(" HELP");
					MLV_actualise_window();
					retour_menuPrincipal(width, height);

			}

			else if((yclic >= 4 * Y) && (yclic <= (4 * Y + height_box))){
					printf("  EXIT");

					MLV_actualise_window();
					exit(EXIT_SUCCESS);



			}

		}

	}
 }
