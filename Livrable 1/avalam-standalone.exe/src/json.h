#ifndef _JSON_H
#define _JSON_H

#include <stdio.h>
#include <avalam.h>

/*
* On défini ici le nombre de caractères que peut prendre une chaine de caractère en JSON
**/
#define MAXCHAR 1000

/*
* Structure générique l'ensemble des fichiers JSON du projet
**/
typedef struct{
	FILE* fichier; 		// le fichier JSON à utiliser
	octet numDiag;		// numéro de diagramme (pour avalam-diag)
	char desc[MAXCHAR];	// description de diagramme (pour avalam-diag)
	T_Score scores;		// permet d'avoir accès au score (pour avalam-standalone)
	T_Position pos;		// permet de représenter la position du jeu
} JSON;

/*
* Fonction permettant d'écrire un fichier JSON contenant les infos pour avalam-standalone
* renvoie 0 en cas d'erreur
**/
int ecrireData(JSON*, char*);

/*
* Fonction permettant d'écrire un fichier JSON contenant les infos pour avalam-diag
* renvoie 0 en cas d'erreur
**/
int ecrireDiag(JSON*, char*);

/*
* Fonction permettant d'écrire la position dans un fichier JSON déjà ouvert
**/
void ecrirePos(JSON*);

/*
* Fonction qui permet d'ajouter à un fichier JSON déjà ouvert un entier en suivant le schéma "nom":val
**/
void ajouterEnt(JSON*, char*, octet);

#endif