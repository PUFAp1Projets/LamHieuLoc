#include <iostream>
#include <cstdlib>
#include <SDL/SDL.h>
#include <string>
using namespace std;

/***********************************************************************************/


const int SCREEN_WIDTH = 1100;
const int SCREEN_HEIGHT = 650;
const int SCREEN_BPP = 24;
const int SIZE_BUTTON_H = 75;
const int SIZE_BUTTON_W = 75;
const int NBR_BUTTON = 4; // les touches de la page introduction: level, help, play, quit

/***********************************************************************************/

SDL_Surface *screen=NULL;
SDL_Surface *background=NULL;
SDL_Surface *image2=NULL;
SDL_Surface *button_img=NULL;
SDL_Rect button[NBR_BUTTON];
SDL_Event event;
//TTF_Font *font = NULL;

/***********************************************************************************/

bool check_SDL(); // Verifier la fonction SDL

/***********************************************************************************/

SDL_Surface *verify_image (string filename); // Prendre les images de la source bmp

void blit_image (int x, int y, 
		  SDL_Surface* source, 
		  SDL_Surface* destination, 
		  SDL_Rect* clip = NULL) // Preparer l'affichage des images 
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( source, clip, destination, &offset );
}
/***********************************************************************************/

void intro_page( bool & intro, 
		bool & main_quit); // Afficher la page Introduction

void value_button();

void intro_page_main(); //Charger les images pour les afficher dans la page Introduction


/***********************************************************************************/
/******************************  MAIN   ********************************************/

int main ( int argc, char* args[] )
{
  bool main_quit =false, intro = true;
  
  if (check_SDL() == false)
    return 1;

  while (main_quit == false)
  {
    intro_page (intro, main_quit); // Afficher la page Introduction
   
  }
  return 0;
  
}
  
/***********************************************************************************/
/**************************  Les fonctions  *****************************************/

bool check_SDL()
{
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) return false;
    
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_DOUBLEBUF );
   
    if( screen == NULL ) return false;
    
    SDL_WM_SetCaption( "Pong Metal", NULL );

    return true;
}


/***********************************************************************************/

SDL_Surface *verify_image (string filename)
{
  SDL_Surface* hinh = NULL;
  SDL_Surface* ep_hinh = NULL;
  hinh = SDL_LoadBMP (filename.c_str()); //Charger l'image 
  if (hinh != NULL) //Si le chargement est reussi
  {
    ep_hinh = SDL_DisplayFormat( hinh ); //Modifier le format de l'image
    SDL_FreeSurface (hinh); // liberer l'ecran
    if (ep_hinh != NULL) //filtrer les couleurs inutiles
      SDL_SetColorKey (ep_hinh, SDL_SRCCOLORKEY, SDL_MapRGB (ep_hinh->format, 0, 0xFF, 0xFF ));
  }
  return ep_hinh;
}


/***********************************************************************************/

void intro_page( bool & intro,
		bool & main_quit)
{
  value_button();
  intro_page_main();
  
  while (intro)
  {
     while (SDL_PollEvent(&event) != 0) 
      {
	switch (event.type)
	{
	  case SDL_QUIT:
	    intro = false;
	    main_quit = true;
	}
      }
  }
  SDL_FreeSurface ( button_img );
  SDL_FreeSurface ( background );
}
void value_button()
{
  for (int i =0; i < NBR_BUTTON; i++)
  {
     button[i].x = 0;
     button[i].y = i*SIZE_BUTTON_H;
     button[i].w = SIZE_BUTTON_W;
     button[i].h = SIZE_BUTTON_H;
  }
 
}


void intro_page_main()
{
  background = verify_image ( "images/intro_page.bmp" );
  button_img = verify_image ("images/button.bmp");
  blit_image (0, 0, background, screen);

  for (int i=0; i< NBR_BUTTON; i++)
    blit_image (350+ i*100, 525, button_img, screen, &button[i]);

  SDL_Flip (screen);
}

