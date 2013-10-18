#include <iostream>
#include <math.h>
#include <cstdlib>
//#include <terminos.h>
#include <unistd.h>
#include <stdio.h>
#include <ncurses.h>
using namespace std;

/*****************************************************************************************/

#define N 30 // so hang
#define M 80 // so cot
#define nbr_gallet 20 // thanh chan gallet o duoi dai 20 ky tu =
#define hang 5
#define cot 12
#define speedx 1
#define speedy 1
#define level 2
//#define nb_balle 1

/*****************************************************************************************/

typedef struct {
  double x;
  double y;
  double dx;
  double dy;
} Sprite;

typedef struct {
  int x;
  int y[5];
  bool check;
} brique;

char screen [N][M];

/**************************** Declarer les fonctions ************************************/

bool touche_appuyee();
int code_touche();
void arranger_brique (brique d[][cot]);
void init_sprite(Sprite & s, double x, double y, double dx, double dy);
void clavier (Sprite q[]);
void paysage ();
void affiche_screen();
void mise_a_jour_sprite(Sprite & s, Sprite q[], brique d[][cot]);// khai bao them sprite q[] la de cho gallet tuong tac voi trai banh
//void check_button (char c, Sprite q[]); //ham kiem tra nhan ban phim

/*********************************** MAIN ************************************************/

int main () {
  Sprite goutte,gallet[nbr_gallet];
  brique gach[hang][cot];
  arranger_brique (gach);
  init_sprite(goutte, 8, 1, 1,1);
  for ( int g=0; g<nbr_gallet; g++)
  {
    init_sprite(gallet[g],N-5,g+1,0,0);// moi khi dong for chay, cu moi gallet ke tiep nhau o dong thu N-5 se co y tang len 1 de thanh 1 day ====== sat nhau
  }
  

  for (int t=0;; t++) 
  {
    system ("stty raw");
    usleep(10 * 10000);
    
    clavier (gallet);
    
    /*if (touche_appuyee()) {
      char c = getchar();
      system ("stty cooked");
      check_button (c,gallet);
      
    }*/
    system ("stty cooked");

    paysage();// in khung XXX
       for ( int g=0; g<nbr_gallet; g++)
    {
      screen[(int) gallet[g].x][(int) gallet[g].y] = '='; // in ra gallet
    }
       for (int row=0; row<hang; row++)
	 for (int column=0; column<cot; column++)
	   if (gach[row][column].check == 1) 
	   for (int characters=0; characters<5; characters++)
	      screen[gach[row][column].x][gach[row][column].y[characters]] = 'W';
	    
	      
	    
	   
       screen[(int) goutte.x][(int) goutte.y] = '0'; //in ra trai banh
 
    
    affiche_screen();
    mise_a_jour_sprite(goutte, gallet, gach); //de trai banh chuyen dong, va gallet chuyen dong
    cout << "\n\tPress ESC to exit the game \n\tPress 'z' to move left end press 'm' to move right\n";
    
   
    
  }
}

/********************************** Les fonctions ****************************************/

void arranger_brique (brique d[][cot])
{
  for (int row=0; row<hang; row++)
    for (int column=0; column<cot; column++)
      {
	d[row][column].x = row+3;
	d[row][column].check = true;
	for (int h=0; h<5; h++)
	{
	  d[row][column].y[h] = 3 + column*6 + (h+1);
	}
	  
	
      }
}

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

/*
void check_button (char c, Sprite q[])
{
switch (c) {
      case 'm':
	system ("stty cooked");
	if (q[nbr_gallet-1].y<M-4) // neu gallet khong dung canh phai, thi duoc di chuyen sang phai
	  for ( int g=0; g<nbr_gallet; g++)
	    q[g].y += 4;
	break;
      case 'z':
	system ("stty cooked");
	if (q[0].y > 4)// neu gallet chua dung canh trai, thi duoc di chuyen sang trai
	for ( int g=0; g<nbr_gallet; g++)
	  q[g].y -= 4;
	break;
      case 27:
        system ("stty cooked");
        exit(0);
      }
  
}
*/
void mise_a_jour_sprite(Sprite & s,Sprite  q[], brique d[][cot]) {
  s.x += s.dx;
  s.y += s.dy;
  for (int row=0; row<hang; row++)
    for (int column=0; column<cot; column++)
      {
	if ( s.x == d[row][column].x && s.y >= d[row][column].y[0] && s.y <= d[row][column].y[4] && d[row][column].check != 0)
	{
	  s.dx *= -speedx;
	  d[row][column].check = false;
	}
      }
  if ( s.x < 2 || (s.x == N-6 && s.y >= q[0].y && s.y <= q[nbr_gallet-1].y )) s.dx *= -speedx; //ham xet dieu kien cho trai banh dung vao gallet
  if ( s.y < 2 || s.y > M-3) s.dy *= -speedy;
  if ( s.x == N) s.dx *= -speedx;
    //exit(0); // neu trai banh dung vao canh duoi thi chuong trinh tu thoat
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

int code_touche() {
  int result = -1;
  system ("stty raw");
  if (touche_appuyee())
    result = (int) getchar();
  system ("stty cooked");
  return result;
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
