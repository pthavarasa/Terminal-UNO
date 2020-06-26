#include "head.h"

/**
	\brief Affiche un message de confirmaation que le paquet à été rempli
	\details 3 boucles : \n
		1/ Boucle qui ajoute les cartes "normal" (6 rouge / 8 vert / ...) \n
		2/ Boucle qui ajoute les cartes "Inversement" et "+2" et "Passage de tour" \n
		3/ Boucle qui ajoute les cartes "+4" et "Joker"
	\param *packet Paquet qui va être rempli
	
*/
void fullPacket(Carte * packet){
    int i, j, t, cpt=0;
    for (i=0; i < NB_COLOR; i++){
        for (t=0; t < 2; t++) {
            if (t==0){j=0;}
            else {j=1;}
            for (; j < NB_NUM; j++, cpt++){
                packet[cpt].color = i;
                packet[cpt].type = 0;         // Ajoute les cartes normal
                packet[cpt].number = j;
            }
        }
    }
    for (t=1; t < NB_TYPE_SPE+1; t++){
        for (i=0; i < NB_COLOR; i++){
            for (j=0; j < 2; j++, cpt++){
                packet[cpt].color = i;          // Ajoute les "Inversement de sens" 
                packet[cpt].type = t;           // Ajoute les +2
                packet[cpt].number = -1;        // Ajoute les "Passage de tour"
            }
        }  
    }
    for (t=4; t < NB_TYPE_JOKER+4; t++){
        for (i=0; i < 4; i++, cpt++){
            packet[cpt].color = -1;        // Ajoute les jokers (changement de couleur)
            packet[cpt].type = t;          // Ajoute les +4
            packet[cpt].number = -1;
        }
    }
    printf(msgFullPacket, cpt);
}

/**
	\brief Affiche une couleur
	\param id Entier variant de 0 à 3 représentant des couleurs
*/

void printColor(int id){
    if (!id) {
        printf("%s", colorRed);
        printf ("Rouge ");
        printf("%s", colorDefault);
    }else if (id==1) {
        printf("%s", colorGreen);
        printf ("Vert ");
        printf("%s", colorDefault);
    }else if (id==2) {
        printf("%s", colorYellow);
        printf ("Jaune ");
        printf("%s", colorDefault);
    }else if (id==3) {
        printf("%s", colorBlue);
        printf ("Bleu ");
        printf("%s", colorDefault);
    }
}
 
/**
	\brief Affiche le type de carte
	\param id Entier variant de 0 à 5 représentant des types de cartes
*/

void printType(int id){
    if (!id) {printf ("Normal ");}
    else if (id==1) {printf ("Inverse ");}
    else if (id==2) {printf ("Passage de tour ");}
    else if (id==3) {printf ("+2 ");}
    else if (id==4) {printf ("+4 ");}
    else if (id==5) {printf ("Changement de couleur ");}
}

/** 
	\brief Affiche le numéro de la carte 
	\param id Numéro de la carte
*/

void printNumber(int id){if (id != -1)printf("%d ",id);}

/** 
	\brief Affiche une carte
	\param card Carte à afficher
*/

void printCard(Carte card){
    printColor(card.color);
    printType(card.type);
    printNumber(card.number); 
    printf("\n");
}

/** 
	\brief Affiche toutes les cartes d'un paquet
	\param *paquet Paquet à afficher
	\param nbCard Nombre de cartes dans le paquet
*/


void printPacket(Carte * packet, int nbCard){
    int i;
    for(i=0; i < nbCard; i++){
        printCard(packet[i]);
    }
    printf(msgNbCard, nbCard);
}
 
/**
	\brief Mélange les cartes d'un paquet
	\param *packet Paquet à mélanger
	\param nbCard Nombre de cartes du paquet
*/

void shuffle(Carte * packet, int nbCard){
    time_t t;
    int i, val;
    Carte cpy;
    srand((unsigned) time(&t));
    for(i=0; i < nbCard; i++){
        val = rand()%50;
        cpy = packet[i];
        packet[i] = packet[val];
        packet[val] = cpy;
    }
    printf("%s", msgSuffle);
}
 
/** 
	\brief Distribue les cartes du paquet aux joueurs
	\param *packet Paquet à distribuer
	\param *joueurs Joueurs qui vont jouer
	\param nbPlayer Nombre de joueurs
	\param *nbCard Nombre de cartes
*/

void distribute(Carte * packet, Joueur * joueurs, int nbPlayer, int * nbCard){
    int i, j, nb = *nbCard;
    for(i=0; i < nbPlayer; i++){
        joueurs[i].nbrCarte = NB_CARD_START;
        for(j=0; j < NB_CARD_START; j++){
            joueurs[i].card[j] = packet[nb-1];
            nb--;
        }
    }
    *nbCard = nb;
    printf("%s", msgCardDistribute);
}

/** 
	\brief Demande le nombre de joueurs qui vont jouer la partie
	\param *joueurs Joueurs qui vont jouer
	\param *nbPlayer Nombre de joueurs
*/

void numberPlayer(Joueur * joueurs, int * nbPlayer){
    int i=0;
    char s[100];
    do{
        if(i==0){
            printf("%s", msgNbPlayer);
            i=1;
        }else{
            printf("%s", msgNbPlayerErr);
        }
        scanf("%s", s);
    } while(atoi(s) < 2 || atoi(s) > 10);
    *nbPlayer = atoi(s);
    for(i = 0; i < *nbPlayer;i++){
        printf(msgInputPlayerName, i+1);
        scanf("%s", joueurs[i].name);
    }
}

/** 
	\brief Transforme une chaîne de caractères en int (renvoie un int)
	\param *c Chaîne de caractères à transformer
*/

int stringToInt(char * c){
    int sign = 1, som = 0;
    if(*c == '-'){
        sign = -1;
        c++;
    }
    while (*c) {
        if ( '0' <= *c && '9' >= *c){
            som = som * 10 + (*c - '0');
            c++;
        }
        else {
            return -5;
        }
    }
    return som * sign;
    
}

/** 
	\brief Récupère les entrées
	\param max Nombre de cartes d'un joueur
*/

int fetchInput(int max){
    int i=0, input;
    char s[100];
    do{
        if(i==0){
            i=1;
        }else{
            printf(msgInputCardErr,max);
        }
        scanf ("%s",s);
        input = stringToInt(s);
    } while(input < -2 || input > max);
    return input;
}
 
/**
	\brief Affcihe les cartes d'un joueur
	\param j Joueur concerné
*/

void printCardPlayer(Joueur j){
    for(int i=0; i < j.nbrCarte; i++){
        printf ("%d ",i);
        printCard(j.card[i]);
    }
}
 
/**
	\brief Retourne la dernière carte du paquet et la supprime
	\param *packet Paquet concerné
	\param *nbCard Nombre de cartes du paquet
*/

Carte draw(Carte * packet, int * nbCard){
    *nbCard-=1;
    return packet[*nbCard];   
}

/**
	\brief Ajoute une carte à la fin du paquet
	\param card Carte à ajouter
	\param *packet Paquet qui reçoit la carte
	\param *nbCard Nombre de cartes du paquet
*/

void addCard(Carte card, Carte * packet, int *nbCard){
    packet[*nbCard] = card;
    *nbCard+=1;                                   
}

/**
	\brief Supprime la carte à l'index indiqué dans le paquet
	\param *packet Paquet d'où l'on supprime la carte
	\param *nbCard Nombre de cartes du paquet
	\param index Index de la carte à supprimer
*/

void deleteCard(Carte * packet, int *nbCard, int index){
    int nb = *nbCard;
    packet[index] = packet[nb-1];
    *nbCard-=1;
}

/**
	\brief Permet de choisir une couleur avec un scanf
	\param *color Entier variant de 0 à 3 représentant les couleurs
*/

void chooseColor(int * color) {
    int c;
    do {
        printf ("[0 : Rouge] / [1 : Vert] / [2 : Jaune] / [3 : Bleu]\n");
        printf ("Choisir une couleur : ");
        scanf ("%d",&c);
    } while (c > 3 && c < 0);
    *color = c;
}

/**
	\brief Inverse le sens de 1 vers 0 ou de 0 vers 1
	\param sens Entier variant de 0 à 1 représentant les sens
*/

void reverseSens(int * sens){
    if (*sens==-1) {*sens=1;}
    else {*sens=-1;}
} 

/**
	\brief Change le tour du joueur en fonction de sens et de jump. Dans le tableau des joueurs : avance (si sens = 1) de 1 ou plus, en fonction de jump et inversement.
	\param sens Sens du jeu
	\param nbPlayer Nombre de joueurs jouant
	\param *currentPlayer Joueur courant
	\param jump Nombre de sauts à effectuer (pour passer au joueur suivant)
*/

void changePlayer(int sens, int nbPlayer, int * currentPlayer, int jump){
	int i, c = * currentPlayer;
	for (i=0; i<jump; i++){
		c+=sens;
		if (c==-1){c = nbPlayer-1;}
		else if (c==nbPlayer){c = 0;}
		//c=(c==-1)?nbPlayer-1:c;
		//c=(c=nbPlayer)?0:c;
	}
	*currentPlayer = c;
} 

/** 
	\brief Si la carte choisit est jouable, la fonction va changer les paramètres de jeu en fonction de la carte posée
	\param *joueurs Joueurs jouant au jeu
	\param currentPlayer Joueur courant
	\param input Valeur de la carte à jouer
	\param *color Couleur courante (ou à choisir, si nécessaire)
	\param *pioche Pioche courante (d'où le joueur suivant va piocher, si nécessaire)
	\param *jump Nombre de sauts à effectuer pour passer au joueur suivant
	\param *sens Sens courant du jeu
	\param *cimetery Paquet de cartes déjà jouées
	\param *sizeCimetery Nombre de cartes du paquet de cartes déjà jouées
	\param *done Entier représentant si le joueur a joué (done  1) ou non (done = 0)
*/

void validCard(Joueur * joueurs, int currentPlayer, int input, int * color, int * pioche, int * jump, int * sens, Carte * cimetery, int * sizeCimetery, int * done){
    if (joueurs[currentPlayer].card[input].type==5){
	    chooseColor(color);
	}
	else if (joueurs[currentPlayer].card[input].type==4){
	    *pioche+=4;
	    chooseColor(color);
	}
	else if (joueurs[currentPlayer].card[input].type==3) {
		*pioche+=2;
	}
	else if (joueurs[currentPlayer].card[input].type==2) {
		*jump+=1;
	}
	if (joueurs[currentPlayer].card[input].type==1) {
		reverseSens(sens);
	}
	addCard(joueurs[currentPlayer].card[input],cimetery,sizeCimetery);
	deleteCard(joueurs[currentPlayer].card,&joueurs[currentPlayer].nbrCarte,input);
	*done=1;	
}

/**
	\brief Règle du jeu
	\param *packet Paquet du jeu
	\param *joueurs Joueurs qui vont jouer
	\param nbCard Nombre de cartes du paquet de jeu
	\param nbPlayer Nombre de joueurs qui vont jouer
*/

void game(Carte * packet, Joueur * joueurs, int nbCard, int nbPlayer){
    int i = 0;
    int input;
    int sizeCimetery=0;
    int currentPlayer=0;
    int jouer=0, pioche=0, jump=1, color=-1, sens=1, end=0, done=0;
    Carte cimetery[108];
    do{
        if (sizeCimetery > 0){
            addCard(draw(cimetery,&sizeCimetery),packet,&nbCard);
            shuffle(packet,nbCard);
        }
        addCard(draw(packet,&nbCard-i),cimetery,&sizeCimetery);
    } while (cimetery[0].type != 0);
    system("clear");
    printf("%s", msgGameStart);
    while (!end) {            
        printf (msgPlayerTrun,joueurs[currentPlayer].name);
        while (jouer==0) {
            if (joueurs[currentPlayer].nbrCarte==0) {
                end=1; 
                jouer=1; 
                done=1;
            }
            else{
                if (pioche>0) {printf (msgPickaxe, pioche);}
                if (color!=-1) {
                    printf ("%s", msgPlayingColor); 
                    printColor(color); 
                    printf("\n");
                }
                printf ("%s", msgCurentCard);
                printCard(cimetery[sizeCimetery-1]);              
                printf (msgPayingPlayer, joueurs[currentPlayer].name);  
                printCardPlayer(joueurs[currentPlayer]);   
                printf ("%s", msgPlayerAction);
                printf (msgPickaxeCard, joueurs[currentPlayer].nbrCarte-1);
                printf ("%s", msgPickaxeNotif);
                printf ("%s", msgEndTurn);
                input = fetchInput(joueurs[currentPlayer].nbrCarte);
                system("clear");
                if (input >= 0 && input < joueurs[currentPlayer].nbrCarte){ // Si il choisis de poser une carte et que la valeur inferieur ou égale a la somme des carte du joueur
                	if (done == 0){  // Si il n'a pas encore posé de carte 
                		if (pioche > 0){  // Si il dois piocher des carte
                			if (joueurs[currentPlayer].card[input].type == cimetery[sizeCimetery-1].type){ // Si la carte dans le cimetiere est du meme type que celle choisis
                				validCard(joueurs, currentPlayer, input, &color, &pioche, &jump, &sens, cimetery, &sizeCimetery, &done);
                			}
                		}
                		else { // Si il ne doit pas piocher de carte
                			if (color != -1){ // Si on dois choisir une couleur precise
                				if (joueurs[currentPlayer].card[input].color == color || joueurs[currentPlayer].card[input].type == 4 || joueurs[currentPlayer].card[input].type == 5){ // Si la carte choisis est un +4 ou un changement de couleur [probleme]
                					validCard(joueurs, currentPlayer, input, &color, &pioche, &jump, &sens, cimetery, &sizeCimetery, &done);
                				}
                			} 
                			else { // Si on peux poser la couleur que l'on souhaite 
                				if ((joueurs[currentPlayer].card[input].color == cimetery[sizeCimetery-1].color && joueurs[currentPlayer].card[input].color != -1) || (joueurs[currentPlayer].card[input].number == cimetery[sizeCimetery-1].number && joueurs[currentPlayer].card[input].number != -1) || joueurs[currentPlayer].card[input].type == cimetery[sizeCimetery-1].type || joueurs[currentPlayer].card[input].type == 4 || joueurs[currentPlayer].card[input].type == 5){
    								validCard(joueurs, currentPlayer, input, &color, &pioche, &jump, &sens, cimetery, &sizeCimetery, &done);
                				}
                			}
                		}
                	}
                	else if (done==1){ // Si une carte a deja ete posé
    	            	if (joueurs[currentPlayer].card[input].type == cimetery[sizeCimetery-1].type && joueurs[currentPlayer].card[input].number == cimetery[sizeCimetery-1].number){ // Si les cartes sont du meme type et du meme nombre
    	           			validCard(joueurs, currentPlayer, input, &color, &pioche, &jump, &sens, cimetery, &sizeCimetery, &done);
    	            	} 
    	            }
                }
                else if (input == -1 && done==0) { // Si il a mis -1 et qu'il n'a pas encore jouer
                	if (pioche>0){  // Si la pioche est supérieur a 0
                		while (pioche != 0){  // Fait piocher au joueur toute les carte a pioche
                			addCard(draw(packet,&nbCard),joueurs[currentPlayer].card,&joueurs[currentPlayer].nbrCarte);
                			pioche--;
                		}
                	}
                	else {  // Sinon lui fais piocher une unique carte
                		addCard(draw(packet,&nbCard),joueurs[currentPlayer].card,&joueurs[currentPlayer].nbrCarte);
                	}
                	jouer=1;
                }
                else if (input == -2 && done==1) {jouer=1;}  // Sinon si il choisis -2 et qu'il a deja jouer : le tour est finis
            }
        }
        jouer=0;
        done=0;
        if (joueurs[currentPlayer].nbrCarte==0) {end=1;}
        else {
            changePlayer(sens,nbPlayer,&currentPlayer,jump);
            jump=1;
        }
        system("clear");
    }
    printf ("%s", msgGameEnd);
    printf (msgWinner, joueurs[currentPlayer].name);
}

/**
	\brief Affiche un logo au début du jeu
*/

void printGameLogo(){
    printf("%s", colorYellow);
    printf("\n           )     )   \n\
        ( /(  ( /(   \n\
    (   )\\()) )\\())  \n\
    )\\ ((_)\\ ((_)\\   \n\
 _ ((_) _((_)  ((_)  \n\
| | | || \\| | / _ \\  \n\
| |_| || .` || (_) | \n\
 \\___/ |_|\\_| \\___/  \n\
                     \n");
    printf("%s", colorDefault);
}
