#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <dirent.h>

#include "json.h"
#include <topologie.h>


/*
* Fonction qui transforme une chaine FEN en position
**/
T_Position convFEN(char*);

/*
* Fonction qui permet de savoir si un dossier existe
**/
int existDir(char*);

int main(int argc, char** argv){

	char rep = 'a';
	char nom[MAXCHAR/4];
	char buffer[MAXCHAR];
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
			fprintf(stderr, "Il y a un problème avec vos arguments : 2 arguments passés mais aucun numérique.\n");
			return 1;
		}
	}
	// On a passé trop d'arguments
	else{
		fprintf(stderr, "Vous avez passé trop d'arguments. Assurez vous de passer votre chaine FEN sous la forme \"uUuU... j/r\"\n");
		return 1;
	}

	while(tolower(rep) != 'o' && tolower(rep) != 'n'){
		printf("Voulez-vous entrer une description pour ce diagramme ? (o/n)\n> ");
		scanf("%c", &rep);
		getchar();
	}

	if(tolower(rep) == 'o'){
		printf("Entrez votre description (%i caractères MAX) :\n", MAXCHAR);

		diag.desc[0] = '\0';
		while(fgets(buffer, sizeof(buffer), stdin) != NULL){
			strtok(buffer, "\n"); // On supprime le caractère de fin de ligne
			if(buffer[0] == '\n') buffer[0] = ' ';

			strcat(diag.desc, " ");

			strcat(diag.desc, buffer);
		}
	}
	else{
		strcpy(diag.desc, "nodesc");
	}

	printf("Entrez le nom du fichier à produire (%i caractères MAX, l'extention .json sera ajoutée automatiquement)\n> ", MAXCHAR/4);
	fgets(nom, sizeof(nom), stdin);
	strtok(nom, "\n"); // On supprime le caractère de fin de ligne
	if(nom[0] == '\n') strcpy(nom, "noname");

	if(!existDir(nom)){
		fprintf(stderr, "%s : fichier introuvable, ou permissions non accordées.\n", nom);
		return 1;
	}

	strcat(nom, ".json");

	if(ecrireDiag(&diag, nom))
		printf("Création du fichier terminé !\n");
	else{
		fprintf(stderr, "Erreur lors de la création de votre fichier...\n");
		return 1;
	}

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

int existDir(char* p){
	char path[MAXCHAR/4];

	strcpy(path, p);

	int i = sizeof(path)-1;

	while(i >= 0 && path[i] != '/' && path[i] != '\\'){
		path[i] = '\0';
		i--;
	}

	printf("%s ", path);

	// On a passé un simple fichier, donc on peut le créer
	if(path[0] == '\0')
		return 1;

	// On a passé un dossier

	DIR* dir = opendir(path);

	if(dir)
		return 1; // Le dossier existe
	else
		return 0; // Le dossier n'existe pas/on a pas les perms
}