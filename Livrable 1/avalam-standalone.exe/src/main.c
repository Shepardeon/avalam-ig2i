#include <stdio.h>
#include <string.h>
#include <dirent.h>

#include "json.h"
#include <topologie.h>

/*
* Fonction qui permet de savoir si un dossier existe
**/
int existDir(char*);

// Pour l'instant c'est un programme de test pour dev la lib JSON
int main(int argc, char** argv){
	octet trait = 1; // joueur jaune = 1, joueur rouge = 0
	int numCase, numCaseD;
	char nomFichier[MAXCHAR/4];
	JSON data;

	/* On traite le nombre d'arguments passés */
	switch(argc){
		case 1: // Aucun argument passé
			strcpy(nomFichier, "data.json");
			break;
		case 2: // Un argument passé
			if(!existDir(argv[1])){
				fprintf(stderr, "%s : fichier introuvable, ou permissions non accordées.\n", argv[1]);
				return 1;
			}
			strcpy(nomFichier, argv[1]);
			break;
		default:
			fprintf(stderr, "Nombre trop important d'arguments !\n");
			return 1;
	}

	/* On initialise les différentes variables du jeu */
	data.pos = getPositionInitiale();
	data.scores = evaluerScore(data.pos);
	T_ListeCoups l = getCoupsLegaux(data.pos);

	ecrireData(&data, nomFichier);

	printf("\t\t+------+\n\t\t|AVALAM|\n\t\t+------+\n\n");

	/* La boucle de jeu : tant qu'il y a des coups légaux, on joue */
	while(l.nb > 0){
		//if(trait) printf("C'est au tours du joueur jaune !\n");
		//else printf("C'est au tour du joueur rouge !\n");		Afficher le trait est intéressant mais impossible !

		printf("Entrez la case de départ\n> ");
		scanf("%i", &numCase);

		printf("Entrez la case d'arrivée\n> ");
		scanf("%i", &numCaseD);

		data.pos = jouerCoup(data.pos, numCase, numCaseD);
		data.scores = evaluerScore(data.pos);
		l = getCoupsLegaux(data.pos);

		ecrireData(&data, nomFichier);

		//trait = (trait+1)%2;
	}

	printf("\nFin de la partie !\n");
	afficherScore(data.scores);

	return 0;
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