#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "json.h"
#include <topologie.h>


/*
* Fonction qui transforme une chaine FEN en position
**/
T_Position convFEN(char*);

int main(int argc, char** argv){

	char rep = 'a';
	char nom[MAXCHAR/4];
	JSON diag;

	// On a passé aucun argument
	if(argc == 1){
		diag.numDiag = 0;
		diag.pos = getPositionInitiale();
	}
	// On a passé un argument
	else if(argc == 2){
		if(atoi(argv[1]))
			diag.numDiag = atoi(argv[1]);
		else
			diag.pos = convFEN(argv[1]);
	}
	// On a passé deux arguments
	else if(argc == 3){
		if(atoi(argv[1])){
			diag.numDiag = atoi(argv[1]);
			diag.pos = convFEN(argv[2]);
		}
		else if(atoi(argv[2])){
			diag.numDiag = atoi(argv[2]);
			diag.pos = convFEN(argv[1]);
		}
		else{
			diag.numDiag = 0;
			diag.pos = getPositionInitiale();
			printf("Il y a un problème avec vos arguments : 2 arguments passés mais aucun numérique.\n");
		}
	}
	// On a passé trop d'arguments
	else{
		diag.numDiag = 0;
		diag.pos = getPositionInitiale();
		printf("Vous avez passé trop d'arguments. Assurez vous de passer votre chaine FEN sous la forme \"uUuU... j/r\"\n");
	}

	while(tolower(rep) != 'o' && tolower(rep) != 'n'){
		printf("Voulez-vous entrer une description pour ce diagramme ? (o/n)\n> ");
		scanf("%c", &rep);
		getchar();
	}

	if(tolower(rep) == 'o'){
		printf("Entrez votre description (%i caractères MAX) :\n", MAXCHAR);
		fgets(diag.desc, sizeof(diag.desc), stdin);

		strtok(diag.desc, "\n"); // On supprime le caractère de fin de ligne
		if(diag.desc[0] == '\n') diag.desc[0] = ' ';
	}
	else{
		strcpy(diag.desc, "nodesc");
	}

	printf("Entrez le nom du fichier à produire (%i caractères MAX, l'extention .json sera ajoutée automatiquement)\n> ", MAXCHAR/4);
	fgets(nom, sizeof(nom), stdin);
	strtok(nom, "\n"); // On supprime le caractère de fin de ligne
	if(nom[0] == '\n') strcpy(nom, "noname");

	strcat(nom, ".json");

	if(ecrireDiag(&diag, nom))
		printf("Création du fichier terminé !\n");
	else
		printf("Erreur lors de la création de votre fichier...\n");


	return 0;
}

T_Position convFEN(char* str){
	int j = 0;

	T_Position pos;


	for(int i = 0; i < NBCASES; i++){
		pos.cols[i].nb = VIDE;
		pos.cols[i].couleur= VIDE;
	}

	for(int i = 0; i < strlen(str); i++){

		char c = str[i];
		if(isdigit(c)){
			char num[5];
			int a = 0;

			while(i+a < strlen(str) && a < 5 && isdigit(str[i+a]) && str[i+a] != '\0'){
				num[a] = str[i+a];
				a++;
			}

			j += atoi(num) - 1;
		}
		else{

			if(c >= 'a' && c <= 'z' && (c != 'j' || c != 'r'))
				pos.cols[j].couleur = JAU;
			else if(c >= 'A' && c <= 'Z' && (c != 'J' || c != 'R'))
				pos.cols[j].couleur = ROU;

			if(j < NBCASES){
				switch(tolower(c)){
					case 'u':
						pos.cols[j].nb = 1;
						break;
					case 'd':
						pos.cols[j].nb = 2;
						break;
					case 't':
						pos.cols[j].nb = 3;
						break;
					case 'q':
						pos.cols[j].nb = 4;
						break;
					case 'c':
						pos.cols[j].nb = 5;
						break;
					case ' ': 
						j--;
						break;
					case '/': 
						j--;
						break;
					case 'j':
						pos.trait = JAU;
						pos.cols[j].couleur = VIDE;
						j--;
						break;
					case 'r':
						pos.trait = ROU;
						pos.cols[j].couleur = VIDE;
						j--;
						break;
					default:
						pos.cols[j].nb = VIDE;
						pos.cols[j].couleur = VIDE;
						break;
				}
			}
		}
		j++;
	}

	if(pos.trait != JAU && pos.trait != ROU)
		pos.trait = JAU;

	return pos;
}