PUF-HCM
Classe: LINF13
Professeur: Olivier Ly


Projet AP1
Ping Pong


I. Les membres participés
_ NGUYEN Thanh Son Lam
_ TRUONG Ba Loc
_ MAI Trung Hieu

II. Le contenu
1. Nom du projet: Le jeu Ping Pong, écrit en langage C++
2. Présentation générale: Deux joueurs, face à face, contrôlent deux gallets et une balle. 
Le but de ce jeu est d'éviter la balle à se déplacer en dehors de la table. Le premier à laisser la balle hors de la table est vaincu.

III. Notre Plan détaillé
1. Délai: 15/12/2013
2. Les étapes principales
_ Le mois d'Octobre et de Novembre:
     	  + Préparer les documents nécessaires (la bibliothèque SDL)
	  + Construire la règle, les caractéristiques rendant le jeu amusant et intéressant.
	  + Réfléchir aux algorithmes pour écrire ce jeu.
_ Le mois de Decembre:
     	  + Commencer à écrire les codes.
	  + Vérifier les fautes et terminer le travail.

IV. La règle du jeu
Nous proposons ici 3 niveaux de difficulté (EASY, NORMAL, HARD), correspondant au nombre de balle de 1 à 3. 
Après chaque 10 secondes, la vitesse de la balle augmente. Chaque joueur aura 3 tours à jouer. 
Le premier à laisser tous ses 3 balles hors de la table est vaincu. 
Pour être équitable, la balle se déplace aléatoirement et n'apparait qu'au centre de la table. 
Quant au niveau NORMAL et HARD, un écart de temps de 2 secondes est nécessaire pour que les balles n'apparaissent pas en même temps.

V. Développement possible
_ Créer les effets sonores pour rendre le jeu intéressant
_ Laisser les joueurs à modifier les paramètres selon leur gout pour augmenter la difficulté du jeu.

VI. Compilation et Exécution du jeu
_ Le jeu fonctionne sous linux donc, il faut avoir le bibliothèque SDL. (à installer par la commande: apt-get install libsdl1.2-dev libsdl1.2debian )
_ Compilez par cette commande: (exemple)
g++ -o game pingpong.cpp  -lSDL
_ Executez : ./game

VII. Références
1. “Programming Linux Games” - Loki Software de John R. Hall
2. Brian Kernighan, Dennis Ritchie - The C Programming Language (2nd Edition)
3. Site: http://lazyfoo.net/
