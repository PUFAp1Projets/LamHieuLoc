#include <iostream>
#include <math.h>
#include <cstdlib>
//#include <terminos.h>
#include <unistd.h>
#include <stdio.h>
//#include <ncurses.h>
using namespace std;

/*****************************************************************************************/

#define N 30 // le nombre de lignes du cadre
#define M 79 // ____________ colonnes du cadre
#define nbr_gallet 20 // le nombre du caractere "=" constitue le gallet
#define hang 5 //le nombre de lignes de brique
#define cot 12 //____________ colonnes de brique

#define speedx 1
#define speedy 1
#define level 2

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
void aider ();
void annonce ();
bool touche_appuyee();
int code_touche();
void arranger_brique (brique d[][cot]);

void init_sprite(Sprite & s, double x, double y, double dx, double dy);
void clavier (Sprite q[]);

void paysage ();
void affiche_screen();
void mise_a_jour_sprite(Sprite & s, Sprite q[], brique d[][cot]);// declarer Sprite q[] pour l'interaction entre le gallet et la balle

/*********************************** MAIN ************************************************/

int main () {
  annonce ();
  Sprite goutte,gallet[nbr_gallet];
  brique gach[hang][cot];
  arranger_brique (gach);
  init_sprite(goutte, 8, 1, 1,1);
  
  for ( int g=0; g<nbr_gallet; g++)
    {
      init_sprite(gallet[g],N-5,g+1,0,0);//pour chaque boucle for, chaque gallet de la ligne N-5 sera augmente une unite en y pour former une chaine de caractere "========"
    }
  for (int t=0;; t++)
    {
      system ("stty raw");
      usleep(10 * 10000);   
      clavier (gallet);   
      system ("stty cooked");
      paysage(); //afficher le cadre de caractere "X"
      for ( int g=0; g<nbr_gallet; g++)
	{
	  screen[(int) gallet[g].x][(int) gallet[g].y] = '='; //afficher le gallet
	}
      for (int row=0; row<hang; row++)
	for (int column=0; column<cot; column++)
	  if (gach[row][column].check == 1)
	    for (int characters=0; characters<5; characters++)
	      screen[gach[row][column].x][gach[row][column].y[characters]] = 'W';
      screen[(int) goutte.x][(int) goutte.y] = '0'; //afficher la balle
      
      affiche_screen();
      mise_a_jour_sprite(goutte, gallet, gach); //mettre en mouvement la balle et le gallet
      cout << "\n\tPress  'h' for help\n";
    }
}

/********************************** Les fonctions ****************************************/

void annonce (){
  system ("clear");
  string line[6];
  line[0] = "\t\t\t\tFBI WARNING\n";
  line[1] = "\t\tThis game copyright by group LamHieuLoc,all rights reserved.\n";
  line[2] = "\t\tThe unauthorized reproduction or distribution of this\n";
  line[3] = "\t\tcopyrighted work is illegal. Criminal copyright infringement\n";
  line[4] = "\t\tis investigated by federal law enforcement agencies and is\n";
  line[5] = "\t\tpunishable by up to 100 years in prison and a fine of $1,000,000.\n";
 
  for (int i=0; i<25; i++)
    {
      system ("clear");
      for (int f=0; f<25-i; f++)
	cout << endl;
      for (int m=0; m<i && m<6; m++)
	cout << line[m];
      usleep (100000);
    }
  sleep (3);
  cout << endl << endl << endl <<"\t\t\tPress ENTER to continue";
  char c = getchar ();
}

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
  if (code_touche() == 'h')
    {
      aider();
    }
  if (code_touche() == 27)
    {
      system ("stty cooked");
      exit(0);
    }
}

void aider () {
  system ("clear");
  cout << "\n\n\n\n";
  cout << "\t\t*****************************************************************\n";
  cout << "\t\t*                                                               *\n";
  cout << "\t\t*     Vous avez en main 3 balles et 3 niveaux de difficulte     *\n";
  cout << "\t\t*    Lorsque vous passez un niveau,le nombre de balle augmente  *\n";
  cout << "\t\t*            tandis que la taille du gallet raccourcit          *\n";
  cout << "\t\t*    Pour deplacer le gallet, utilisez les touches suivantes    *\n";
  cout << "\t\t*          'z': a gauche           'm' : a droite               *\n";
  cout << "\t\t*           ESC: quitter le jeu    Enter: commencer             *\n";
  cout << "\t\t*        Enfin, a vous de trouver une touche secrete            *\n";
  cout << "\t\t*                   pour tricher sur le jeu                     *\n";
  cout << "\t\t*****************************************************************\n";
  cout << "\t\t\t Appuyer sur Enter pour revenir au jeu";
  char c = getchar ();
}

void check_button (char c, Sprite q[])
{
  switch (c) {
  case 'm':
    system ("stty cooked");
    if (q[nbr_gallet-1].y<M-4) //si le gallet ne touche pas encore le cote droite, on peut le deplacer a droite
      for ( int g=0; g<nbr_gallet; g++)
	q[g].y += 4;
    break;
  case 'z':
    system ("stty cooked");
    if (q[0].y > 4)//si le gallet ne touche pas encore le cote gauche, on peut le deplacer a gauche    
      for ( int g=0; g<nbr_gallet; g++)
	q[g].y -= 4;
    break;
  case 27:
    system ("stty cooked");
    exit(0);
  }
}

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
  if ( s.x < 2 || (s.x == N-6 && s.y >= q[0].y && s.y <= q[nbr_gallet-1].y )) s.dx *= -speedx; //cette fonction verifie la collision entre la balle et le gallet
  if ( s.y < 2 || s.y > M-3) s.dy *= -speedy;
  if ( s.x == N) s.dx *= -speedx;
}
exit(0); //si le joueur est perdu, on quitte automatiquement le jeu
  
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
