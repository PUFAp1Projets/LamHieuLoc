#include <iostream>
#include <math.h>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <ncurses.h>
using namespace std;

/*****************************************************************************************/

#define N 30 // le nombre de lignes du cadre
#define M 79 // ____________ colonnes du cadre
#define nbr_gallet 25 // le nombre du caractere "=" constitue le gallet
#define hang 5 //le nombre de lignes de brique
#define cot 12 //____________ colonnes de brique
#define speedx 1
#define speedy 1
#define maxscore 6000

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

void verifier_condition(int & ball,long int & score, int & level);
void avant_jouer(Sprite & goutte,
		 Sprite gallet[], 
		 brique gach[][cot], 
		 int & ball, 
		 long int & score, 
		 int & level, 
		 int & gallet_neveau);
void aider ();
void annonce ();
bool touche_appuyee();
int code_touche();
void arranger_brique (brique gach[][cot]);
void init_sprite(Sprite & s, double x, double y, double dx, double dy);
void clavier (Sprite & goutte, 
	      Sprite gallet[], 
	      int & gallet_neveau, 
	      bool & cheat);
void paysage (bool & cheat);
void affiche_screen();
void mise_a_jour_sprite(Sprite & s, 
			Sprite gallet[], 
			brique gach[][cot], 
			long int & score, 
			int & ball, 
			bool & cheat, 
			int &level,
			int & gallet_neveau);


/*********************************** MAIN ************************************************/

int main () {
  
  annonce ();
  Sprite goutte;
  brique gach[hang][cot];
  arranger_brique (gach);
  int ball = 3;
  long int score = 0;
  bool cheat = false;
  int level = 1;
  int gallet_neveau = nbr_gallet-5*level;
  Sprite gallet [gallet_neveau];
  for ( int g=0; g<gallet_neveau; g++)
  {
    init_sprite(gallet[g], N-5, g+1, 0, 0);//pour chaque boucle for, chaque gallet de la ligne N-5 sera augmente une unite en y pour former une chaine de caractere "========"
  }
  
  start_here:
  
  gallet_neveau = nbr_gallet-5*level;
  avant_jouer (goutte, gallet, gach, ball, score, level, gallet_neveau);
  verifier_condition (ball, score, level);
  
  while (1) 
  {
    system ("stty raw");
    usleep(10 * 10000);    
    clavier (goutte, gallet, gallet_neveau, cheat);    
    system ("stty cooked");    
    paysage (cheat); //afficher le cadre de caractere "X"
       for ( int g=0; g<gallet_neveau; g++)    
	  	screen[(int) gallet[g].x][(int) gallet[g].y] = '='; //afficher le gallet    
       
       for (int row = 0; row < hang; row++)
	 for (int column = 0; column < cot; column++)
	   if (gach [row] [column].check == 1) 
	   for (int characters  = 0; characters < 5; characters++)
	      screen [gach[row][column].x] [gach[row][column].y[characters]] = 'W';    
	   
       screen[(int) goutte.x][(int) goutte.y] = '0'; //afficher la balle
 
    system ("stty cooked");
    affiche_screen ();
    mise_a_jour_sprite(goutte,
		       gallet,
		       gach, 
		       score, 
		       ball, 
		       cheat, 
		       level, 
		       gallet_neveau);
    cout << "\nLevel: "<< level << "\t\tBall: "<< ball <<"\t\t\t\tScore:  " <<score;
    cout << "\n\tPress  'h' for help\t\tPress Spacebar to start\n";
    system ("stty cooked");
    if (goutte.dy == 0) break;
  }
  goto start_here;
}

/********************************** Les fonctions ****************************************/
void verifier_condition (int & ball, long int & score, int & level)
{
  if (ball < 0)
  { system ("clear");
    cout << "\n\n\tMung qua!!! Da co nguoi choi te hon tui. Tui iu ban!!";
    cout << "\nNhan phim Enter de thoat\n";
    char c = getchar();
    exit (0);    
  }
  if (level >3)
    { system ("clear");
    cout << "\n\n\tChuc mung ban da chien thang voi so diem " << score <<endl;
    cout << "\nBan nhan duoc 1 phan thuong, xin vui long lien he voi";
    cout << "\nvan phong dieu hanh Puf de lanh qua.";
    cout << "\nNhan phim Enter de thoat\n";
    char c=getchar();
    exit (0);    
  }
    
}

void avant_jouer (Sprite & goutte,
		 Sprite gallet[],
		 brique gach[][cot],
		 int & ball,
		 long int & score,
		 int & level, 
		 int & gallet_neveau) {
  double goutte_y;
  goutte_y= ( gallet [0].y + gallet [gallet_neveau-1].y ) / 2;
  init_sprite(goutte, N-6, goutte_y, 0,0);
  if (score % maxscore == 0 && gach[0][0].check == 0)
	  {
	    level += 1;
	    ball +=1;
	    arranger_brique (gach);
	    for ( int g=0; g<gallet_neveau; g++)	      
	      init_sprite(gallet[g], N-5,g+1, 0, 0);	      
	    init_sprite(goutte, N-6, goutte_y, 0, 0);
	  }
}

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
void arranger_brique (brique gach[][cot])
{
  for (int row=0; row<hang; row++)
    for (int column=0; column<cot; column++)
      {
	gach[row][column].x = row+3;
	gach[row][column].check = true;
	for (int h=0; h<5; h++)
	{
	  gach[row][column].y[h] = 3 + column*6 + (h+1);
	}
	  
	
      }
}

void clavier (Sprite & goutte, Sprite gallet[], int  & gallet_neveau, bool & cheat)
{
    if (code_touche() == 'm') 
    {
      system ("stty cooked");
      if (gallet[gallet_neveau-1].y<M-3)
	for ( int g=0; g<gallet_neveau; g++)
	  gallet[g].y += 3;
      return;
    }
    if (code_touche() == 'z')
    {
      system ("stty raw");
      system ("stty cooked");
      if (gallet[0].y > 2)
      for ( int g=0; g<gallet_neveau; g++)
	gallet[g].y -= 3;
      return;
    }    
    if (code_touche() == 'h') 
      {aider();
      system ("stty cooked");}
    if (code_touche() == 92) 
      {system ("stty cooked");
      cheat = !cheat;}
    if (code_touche() == 32) {system ("stty cooked");goutte.dx = -1; goutte.dy = 1;}
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
  cout << "\t\t*      Vous avez en main 3 balles et 3 niveaux de difficulte    *\n";
  cout << "\t\t*    Lorsque vous passez un niveau,le nombre de balle augmente  *\n";
  cout << "\t\t*    tandis que la taille du gallet raccourcit                  *\n";
  cout << "\t\t*          'z': a gauche        'm' : a droite                  *\n";
  cout << "\t\t*       ESC: quitter le jeu      Space bar: lanceer la balle    *\n";
  cout << "\t\t*      Enfin, a vous de trouver une touche secrete pour tricher *\n";
  cout << "\t\t*                                               sur le jeu      *\n";
  cout << "\t\t*                                                               *\n";
  cout << "\t\t*****************************************************************\n";
  cout << "\t\t\tAppuyer sur Enter pour revenir au jeu";
  char c = getchar ();
}


void mise_a_jour_sprite(Sprite & s,
			Sprite  gallet[], 
			brique gach[][cot], 
			long int & score, 
			int & ball, 
			bool & cheat, 
			int & level,
			int & gallet_neveau) {
  s.x += s.dx;
  s.y += s.dy;
  for (int row=0; row<hang; row++)
    for (int column=0; column<cot; column++)
      {
	if ( s.x == gach[row][column].x 
	    && s.y >= gach[row][column].y[0] 
	    && s.y <= gach[row][column].y[4] 
	    && gach[row][column].check != 0 )
	{
	  s.dx *= -speedx;
	  gach[row][column].check = false;
	  score += 100;
	  if (score%maxscore ==0) s.dx = s.dy =0;	  
	}
      }
  if ( s.x < 2 || (s.x == N-5 
		  && s.y >= gallet[0].y 
		  && s.y <= gallet[gallet_neveau-1].y )) s.dx *= -speedx; //verifie la collision entre la balle et le gallet
  if ( s.y < 2 || s.y > M-3) s.dy *= -speedy;
  if ( s.x == N) 
  { 
    if (cheat == 1) s.dx *= -speedx;
    else
    {
      ball -=1;
      s.dx = s.dy =0;
    }
  }
   
}

void paysage(bool & cheat) {
  for (int i=0; i<N; i++)
    for (int j=0; j<M; j++)
      if (cheat==0 && (i==0 || j==0 || j==M-1))
        screen[i][j] = 'X';
      else if (cheat==1 && (i==0 || i==N-1 || j==0 || j==M-1))
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
