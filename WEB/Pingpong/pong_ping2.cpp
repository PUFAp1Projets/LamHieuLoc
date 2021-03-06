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
const int NBR_BUTTON = 4; // button cua trang intro: level, help, play, quit

/***********************************************************************************/

SDL_Surface *screen=NULL;
SDL_Surface *background=NULL;
SDL_Surface *image2=NULL;
SDL_Surface *button_img=NULL;
SDL_Rect button[NBR_BUTTON];
SDL_Rect button_press[NBR_BUTTON];
SDL_Event event;
//TTF_Font *font = NULL;

/***********************************************************************************/
/***********************************************************************************/

bool check_SDL(); // kiem tra va thiet lap cua so

/***********************************************************************************/

SDL_Surface *verify_image (string filename); // lay hinh tu nguon hinh bmp

void blit_image (int x, int y, 
		  SDL_Surface* source, 
		  SDL_Surface* destination, 
		  SDL_Rect* clip = NULL) // nap hinh vao de chua bi hien thi
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( source, clip, destination, &offset );
}
/***********************************************************************************/

void intro_page( bool & intro, 
		bool & main_quit); // hien thi man hinh intro

void value_button();

void intro_page_main(); // nap cac hinh de duoc hien thi trong Intro

void help_main(); // hien thi phan giup do

/***********************************************************************************/
/******************************  MAIN   ********************************************/

int main ( int argc, char* args[] )
{
  bool main_quit =false, intro = true;
  
  if (check_SDL() == false)
    return 1;

  while (main_quit == false)
  {
    intro_page (intro, main_quit); // hien thi intro
   
  }
  return 0;
  
}
  
/***********************************************************************************/
/**************************  Cac function  *****************************************/

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
  hinh = SDL_LoadBMP (filename.c_str()); //load anh bmp vao hinh
  if (hinh != NULL) // neu load thanh cong
  {
    ep_hinh = SDL_DisplayFormat( hinh ); // ep chuan hinh lai cho phu hop, dua vao ephinh
    SDL_FreeSurface (hinh); // giai toa hinh
    if (ep_hinh != NULL) // loc nhung mau khong can thiet - transparent
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
	case SDL_MOUSEBUTTONDOWN:
	{
	  int x = event.button.x;
	  int y = event.button.y;
	  
	  //bam nut LEVEL
	  if (x> 350 && x < 425 && y >525 && y <600 && 
	    event.button.button == SDL_BUTTON_LEFT)
	  {
	    blit_image (350+ 0*100, 525, button_img, screen, &button_press[0]);
	    SDL_Flip (screen);
	    break;
	  }
	  
	  //help
	  if (x> 450 && x < 525 && y >525 && y <600 && 
	    event.button.button == SDL_BUTTON_LEFT)
	  {
	    blit_image (350+ 1*100, 525, button_img, screen, &button_press[1]);
	    image2 = verify_image ("images/help.bmp");
	    SDL_Flip (screen);
	    SDL_Delay (1000);
	    help_main ();
	    break;
	    
	  }
	  
	  //play
	  if (x> 550 && x < 625 && y >525 && y <600 && 
	    event.button.button == SDL_BUTTON_LEFT)
	  {
	    blit_image (350+ 2*100, 525, button_img, screen, &button_press[2]);
	    SDL_Flip (screen);
	    SDL_Delay (1500);
	    break;
	  }
	  
	  //quit
	  if (x> 650 && x < 725 && y >525 && y <600 && 
	    event.button.button == SDL_BUTTON_LEFT)
	  {
	    blit_image (350+ 3*100, 525, button_img, screen, &button_press[3]);
	    SDL_Flip (screen);
	    intro = false;
	    main_quit = true;
	    SDL_Delay (1000);
	    break;
	  } 
	}
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
     
     button_press[i].x = SIZE_BUTTON_W;
     button_press[i].y = i*SIZE_BUTTON_H;
     button_press[i].w = SIZE_BUTTON_W;
     button_press[i].h = SIZE_BUTTON_H;  
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

void help_main ()
{
  bool quit= false;
  blit_image (150, 150, image2, screen);
  SDL_Flip (screen);
  
  while (quit == false)
  {
    if (SDL_PollEvent( &event ))
    {
      if (event.type == SDL_MOUSEBUTTONDOWN)
      {
	int a = event.button.x;
	int b = event.button.y;
	if (a> 450 && a < 525 && b >525 && b <600 && 
	  event.button.button == SDL_BUTTON_LEFT)
	{
	  SDL_Delay (1000);
	  intro_page_main ();
	  quit = true;
	  
	}
      }
    }
  }
  
}



