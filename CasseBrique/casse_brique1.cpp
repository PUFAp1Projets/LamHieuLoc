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

bool touche_appuyee();
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
void mise_a_jour_sprite(Sprite & s);

int main () {
  Sprite goutte;
  init_sprite(goutte, 1, 1, 1,1);
  for (int t=0;; t++) 
    {
      system ("stty raw"); 
      usleep(10 * 10000);
      if (touche_appuyee()) {  // OL: utilise plutot la fonction code_touche de goutte.cpp
	char c = getchar();
      system ("stty cooked");
      switch (c) {
      case 13:
        system ("stty cooked");
        exit(0);
      }
      }
      system ("stty cooked");
      
      paysage();
      screen[(int) goutte.x][(int) goutte.y] = 'O';
      affiche_screen();
      mise_a_jour_sprite(goutte);
      
    }
}

void mise_a_jour_sprite(Sprite & s) {
  s.x += s.dx;
  s.y += s.dy;
  if ( s.x < 2 ) s.dx =1; // OL: Utilise un #define pour la vitesse du sprite
  if ( s.x > N-3 ) s.dx =-1;
  if ( s.y < 2 ) s.dy =1;
  if ( s.y > M-3 ) s.dy =-1;
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
