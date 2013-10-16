#include <iostream>
#include <math.h>
#include <cstdlib>
//#include <terminos.h>
#include <unistd.h>
#include <stdio.h>
//#include <ncurses.h>
using namespace std;

#define N 30
#define nb_balle 1
typedef struct {
  double x;
  double y;
  double dx;
  double dy;
} Sprite;

char screen [N][N];
void init_sprite(Sprite & s, double x, double y, double dx, double dy);
void paysage ();
void affiche_screen();
void mise_a_jour_sprite(Sprite & s);

int main () {
  Sprite balle[nb_balle];
  init_sprite(balle[0], 4, 5, 0.5, 0.8);
 
  for (int t=0; t<1000; t++) {
 paysage();
  for (int b=0; b<nb_balle; b++)
    screen[(int) balle[b].x][(int) balle[b].y] = 'O';
  mise_a_jour_sprite(balle[0]);
  affiche_screen();
  usleep (70*1000);
  system ("clear");
}
}

void mise_a_jour_sprite(Sprite & s) {
  s.x += s.dx;
  s.y += s.dy;
  if ( s.x < 2 ) s.dx =0.5;
  if ( s.x > N-2 ) s.dx =-0.5;
  if ( s.y < 2 ) s.dy =0.8;
  if ( s.y > N-2 ) s.dy =-0.8;
}

void paysage() {
  for (int i=0; i<N; i++)
    for (int j=0; j<N; j++)
      if (i==0 || i==N-1 || j==0 || j==N-1)
        screen[i][j] = '#';
      else
        screen[i][j] = ' ';
}

void affiche_screen() {
  system("clear");
  for (int i=0; i<N; i++) {
    for (int j=0; j<N; j++)
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
