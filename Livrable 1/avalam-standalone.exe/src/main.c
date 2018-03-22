#include <stdio.h>
#include <string.h>

#include "json.h"
#include <topologie.h>


// Pour l'instant c'est un programme de test pour dev la lib JSON
int main(int argc, char ** argv){
	JSON data;
	data.pos = getPositionInitiale();
	data.scores = evaluerScore(data.pos);

	ecrireData(&data, "testData");

	JSON diag;
	diag.pos = getPositionInitiale();
	diag.numDiag = 0;
	
	strcpy(diag.desc, "La position initiale du jeu.");

	ecrireDiag(&diag, "testDiag");
}