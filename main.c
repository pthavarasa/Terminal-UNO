#include "head.h"

/**
	\mainpage Documentation de notre projet
*/

/**
	\brief Fonction principale du jeu qui fait appel à toutes les fonctions créer précédemment.
*/
int main(){

    Carte packet[NB_CARD];
    Joueur joueurs[10];
    int nbCard = NB_CARD, nbPlayer = 0;

    printGameLogo();
    fullPacket(packet);
    shuffle(packet,nbCard);
    numberPlayer(joueurs,&nbPlayer);
    distribute(packet,joueurs,nbPlayer,&nbCard);
    game(packet,joueurs,nbCard,nbPlayer); 
}
