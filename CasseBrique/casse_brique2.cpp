#include <iostream>
#include <math.h>
#include <cstdlib>
//#include <terminos.h>
#include <unistd.h>
#include <stdio.h>
//#include <ncurses.h>
using namespace std;

#define N 30
#define M 80
#define nbr_gallet 20

bool touche_appuyee();
int code_touche();

typedef struct {
  double x;
  double y;
  double dx;
  double dy;
} Sprite;

char screen [N][M];
void init_sprite(Sprite & s, double x, double y, double dx, double dy);
void paysage ();
void affiche_screen();
void mise_a_jour_sprite(Sprite & s, Sprite q[]);
void clavier (char c, Sprite q[]);

int main () {
  Sprite goutte,gallet[nbr_gallet];
  init_sprite(goutte, 1, 1, 1,1);
  for ( int g=0; g<nbr_gallet; g++)
    {
      init_sprite(gallet[g],N-5,g+1,0,0);
    }
  
  
  for (int t=0;; t++) 
    {
      system ("stty raw");
      usleep(10 * 10000);
      int c = code_touche();
      if (code_touche()) {
	system ("stty cooked");
	clavier (c,gallet);
	
      }
      system ("stty cooked");
      
      paysage();
      for ( int g=0; g<nbr_gallet; g++)
	{
	  screen[(int) gallet[g].x][(int) gallet[g].y] = '=';
	}
      screen[(int) goutte.x][(int) goutte.y] = '0';
      affiche_screen();
      mise_a_jour_sprite(goutte,gallet);
      cout << "\n\tPress ESC to exit the game \n\tPress 'z' to move left end press 'm' to move right\n";
      
      
      
    }
}
void clavier (char c, Sprite q[])
{
  switch (c) {
  case 'm':
    system ("stty cooked");
    if (q[nbr_gallet-1].y<M-4)
      for ( int g=0; g<nbr_gallet; g++)
	q[g].y += 10;
    break;
  case 'z':
    system ("stty cooked");
    if (q[0].y > 4)
      for ( int g=0; g<nbr_gallet; g++)
	q[g].y -= 10;
    break;
  case 27:
    system ("stty cooked");
    exit(0);
  }
  
}

int code_touche() {
  int result = -1;
  system ("stty raw");
  if (touche_appuyee())
    result = (int) getchar();
  system ("stty cooked");
  return result;
}

void mise_a_jour_sprite(Sprite & s,Sprite  q[]) {
  s.x += s.dx;
  s.y += s.dy;
  if ( s.x < 2 ) s.dx =1;
  if ( s.x == N-6 && s.y >= q[0].y && s.y <= q[nbr_gallet-1].y ) s.dx =-1;
  if ( s.y < 2 ) s.dy =1;
  if ( s.y > M-3 ) s.dy =-1;
  if ( s.x == N) ;
}

void paysage() {
  for (int i=0; i<N; i++)
    for (int j=0; j<M; j++)
      if (i==0 || i==N-1 || j==0 || j==M-1)
        screen[i][j] = 'X';
      else
        screen[i][j] = ' ';
}

void affiche_screen() {
  system("clear");
  for (int i=0; i<N; i++) {
    for (int j=0; j<M; j++)
      cout << screen[i][j];
    cout << endl;
  }
}


void init_sprite(Sprite & s,
                 double x, 
                 double y, 
                 double dx, 
                 double dy) {
  s.x = x;
  s.y = y;
  s.dx = dx;
  s.dy = dy;
}

bool touche_appuyee()  
{
  struct timeval tv;
  fd_set fds;
  tv.tv_sec = 0;
  tv.tv_usec = 0;
  FD_ZERO(&fds);
  FD_SET(STDIN_FILENO, &fds);
  select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
  return (FD_ISSET(0, &fds));
}
