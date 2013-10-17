#include <iostream>
#include <math.h>
#include <cstdlib>
//#include <terminos.h>
#include <unistd.h>
#include <stdio.h>
//#include <ncurses.h>

using namespace std;

/*****************************************************************************************/

#define N 30
#define M 80
#define speedx 1
#define speedy 1
#define nbr_gallet 20


/*****************************************************************************************/

typedef struct {
  double x;
  double y;
  double dx;
  double dy;
} Sprite;

char screen [N][M];

/**************************** Declarer les fonctions ************************************/

bool touche_appuyee();
int code_touche();
void init_sprite(Sprite & s, double x, double y, double dx, double dy);
void paysage ();
void affiche_screen();
void mise_a_jour_sprite(Sprite & s, Sprite q[]);
void clavier (Sprite q[]);


/*********************************** MAIN ************************************************/

int main () {
  Sprite goutte,gallet[nbr_gallet];
  init_sprite(goutte, 1, 1, speedx, speedy);
  for ( int g=0; g<nbr_gallet; g++)
    {
      init_sprite(gallet[g],N-5,g+1,0,0);
    }
  for (int t=0;; t++) 
    {
      system ("stty raw");
      //clavier (gallet);
      usleep(10 * 10000);
      //clavier (gallet);
      /*
	if (code_touche() == 'm') 
	{
	system ("stty cooked");
	if (gallet[nbr_gallet-1].y<M-3)
	for ( int g=0; g<nbr_gallet; g++)
	gallet[g].y += 3;
	
	}
	if (code_touche() == 'z')
	
	{
	system ("stty cooked");
	if (gallet[0].y > 2)
	for ( int g=0; g<nbr_gallet; g++)
	gallet[g].y -= 3;
	
	}
	if (code_touche() == 27)
	
	{
	system ("stty cooked");
	exit(0);
	}*/
      
      system ("stty cooked");
      
      paysage();
      for ( int g=0; g<nbr_gallet; g++)
	{
	  screen[(int) gallet[g].x][(int) gallet[g].y] = '=';
	}
      screen [(int) goutte.x] [(int) goutte.y] = '0';
      affiche_screen();
      mise_a_jour_sprite(goutte,gallet);
      cout << "\n\tPress ESC to exit the game \n\tPress 'z' to move left end press 'm' to move right\n";
    }
}

/********************************** Les fonctions ****************************************/

void clavier (Sprite q[])
{
    if (code_touche() == 'm') 
      {
	system ("stty cooked");
	if (q[nbr_gallet-1].y<M-3)
	  for ( int g=0; g<nbr_gallet; g++)
	    q[g].y += 3;
	return;
      }
    if (code_touche() == 'z')
      
      {
	system ("stty cooked");
	if (q[0].y > 2)
	  for ( int g=0; g<nbr_gallet; g++)
	    q[g].y -= 3;
	return;
      }
    if (code_touche() == 27)
      
      {
	system ("stty cooked");
	exit(0);
      }
}

void mise_a_jour_sprite(Sprite & s,Sprite  q[]) {
  
  s.x += s.dx;
  s.y += s.dy;
  if ( s.x < 2 ) s.dx = speedx;
  if ( s.x == N-6 && s.y >= q[0].y && s.y <= q[nbr_gallet-1].y ) s.dx = -speedx;
  
  if ( s.y < 2 ) s.dy = speedy;
  if ( s.y > M-3 ) s.dy = -speedy;
  if ( s.x == N) exit(0);
}
