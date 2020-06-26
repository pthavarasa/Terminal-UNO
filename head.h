#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NB_CARD 108
#define NB_COLOR 4
#define NB_NUM 10
#define NB_TYPE_SPE 3
#define NB_TYPE_JOKER 2
#define NB_CARD_START 7


typedef struct Carte Carte;

/** 
	\brief Type, couleur et nombre d'une carte
*/
struct Carte{
    int type; 
    int color;
    int number;
};

typedef struct Joueur Joueur;

/**	
	\brief Nom, statut, nombre de cartes et cartes d'un joueur
*/
struct Joueur{
    char name[100];
    int status;
    int nbrCarte;
    Carte card[NB_CARD];
};

// void printGameLogo(); Affiche un logo
void printGameLogo();
// void fullPacket(Carte * packet); Rempli le packet
void fullPacket(Carte * packet);
// void shuffle(Carte * packet, int nbCard); Melange le paquet
void shuffle(Carte * packet, int nbCard);
// void distribute(Carte * packet, Joueur * joueurs, int nbPlayer, int * nbCard); distribue les cartes
void distribute(Carte * packet, Joueur * joueurs, int nbPlayer, int * nbCard);
// Carte draw(Carte * packet, int * nbCard); Retourne la derniere carte du paquet et la supprime
Carte draw(Carte * packet, int * nbCard);
// void printCard(Carte card); Affiche une carte
void printCard(Carte card);
// void printNumber(int id); Affiche la valeur de id si la valeur de id est different de -1
void printNumber(int id);
// int stringToInt(char * c); Transforme une chaine de caractere en int (renvoi un int)
int stringToInt(char * c);
// int fetchInput(int max); Recupere les entrées
int fetchInput(int max);
// void printColor(int id); Affiche la couleur d'une carte en fonction de la valeur du parametre
void printColor(int id);
// void printType(int id); Affiche un type de carte en fonction d'un id
void printType(int id);
// void addCard(Carte card, Carte * packet, int *nbCard); Ajoute une carte a la fin du paquet
void addCard(Carte card, Carte * packet, int *nbCard);
// void printCardPlayer(Joueur j); Affiche les carte d'un joueur
void printCardPlayer(Joueur j);
// void deleteCard(Carte * packet, int *nbCard, int index); Supprime la carte a l'index indiquer
void deleteCard(Carte * packet, int *nbCard, int index);
// void chooseColor(int * color); Permet de changer la couleur actuel du jeu
void chooseColor(int * color);
// void numberPlayer(Joueur * joueurs, int * nbPlayer); Demande le nombre de joueurs
void numberPlayer(Joueur * joueurs, int * nbPlayer);
// void validCard(Joueur * joueurs, int currentPlayer, int input, int * color, int * pioche, int * jump, int * sens, Carte * cimetery, int * sizeCimetery, int * done); Effectue les changement dans les parametre de la partie apres qu'une carte soit posé
void validCard(Joueur * joueurs, int currentPlayer, int input, int * color, int * pioche, int * jump, int * sens, Carte * cimetery, int * sizeCimetery, int * done);
// void changePlayer(int sens, int nbPlayer, int * currentPlayer, int jump); Change le joueur courant
void changePlayer(int sens, int nbPlayer, int * currentPlayer, int jump);
//void reverseSens(int * sens); Inverse la valeur de sens
void reverseSens(int * sens);
// void game(Carte * packet, Joueur * joueurs, int nbCard, int nbPlayer); Fonction principal du jeux qui utilise toute les fonctions
void game(Carte * packet, Joueur * joueurs, int nbCard, int nbPlayer);

static char * colorDefault = "\033[0m";
static char * colorRed = "\033[1;31m";
static char * colorGreen = "\033[1;32m";
static char * colorBlue = "\033[1;34m";
static char * colorYellow = "\033[1;33m";

static char * msgFullPacket = "\n - L paquet est remplit avec %d cartes!\n";
static char * msgNbCard = " - Il y a %d cartes dans le packet!\n";
static char * msgSuffle = " - Le paquet est bien mélangé!\n\n";
static char * msgCardDistribute = " - Les cartes sont distribuées !\n";
static char * msgNbPlayer = "Entrer le nombre de joueur : ";
static char * msgNbPlayerErr = "/!\\ Wrong input : Entrer le nombre de joueur (2 - 10): ";
static char * msgInputPlayerName = "Nom du joueur %d : ";
static char * msgInputCardErr = "/!\\ Wrong input : Entrer Possible : -2 - %d\n ->";
static char * msgGameStart = "Le jeu commence !\n";
static char * msgPlayerTrun = "C'est le tour du joueur : %s\n";
static char * msgPickaxe = "Carte potentiel a piocher : %d\n";
static char * msgPlayingColor = "Couleur de jeux : ";
static char * msgCurentCard = "La carte courante est : ";
static char * msgPayingPlayer = "\nLa main du joueur de %s :\n\n";
static char * msgPlayerAction = "\nQuel action effectuer ?\n";
static char * msgPickaxeCard = "Choisir une carte à poser : 0 - %d\n";
static char * msgPickaxeNotif = "Piocher : -1\n";
static char * msgEndTurn = "Fin du tour : -2\n -> ";
static char * msgGameEnd = "Fin de partie\n";
static char * msgWinner = "Gagnant : %s\n";
