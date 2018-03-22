#include "json.h"

void ajouterEnt(JSON* json, char* nom, octet val){
	fprintf(json->fichier, "\"%s\":%i", nom, val);
}

void ecrirePos(JSON* json){
	// On ouvre notre tableau
	fprintf(json->fichier, "\"cols\":[\n");

		for(int i = 0; i < NBCASES; i++){
			fprintf(json->fichier, "\t{");
				ajouterEnt(json, "nb", json->pos.cols[i].nb); fprintf(json->fichier, ",");
				ajouterEnt(json, "couleur", json->pos.cols[i].couleur);
			fprintf(json->fichier, "}");
			if(i < NBCASES - 1)
				fprintf(json->fichier, ",\n");
			}
	fprintf(json->fichier, "\n]");
	// On ferme notre tableau
}

int ecrireData(JSON* json, char* nom){
	json->fichier = NULL;
	json->fichier = fopen(nom, "w");

	if(json->fichier != NULL){
		// On ouvre notre objet JSON
		fprintf(json->fichier, "{\n");

			ajouterEnt(json, "trait", json->pos.trait); fprintf(json->fichier, ",\n");
			ajouterEnt(json, "scoreJ", json->scores.nbJ); fprintf(json->fichier, ",\n");
			ajouterEnt(json, "scoreJ5", json->scores.nbJ5); fprintf(json->fichier, ",\n");
			ajouterEnt(json, "scoreR", json->scores.nbR); fprintf(json->fichier, ",\n");
			ajouterEnt(json, "scoreR5", json->scores.nbR5); fprintf(json->fichier, ",\n");

			ecrirePos(json);

		fprintf(json->fichier, "\n}");
		// On ferme notre objet JSON

		fclose(json->fichier);
		return 1;
	}

	fclose(json->fichier);

	return 0;
}

int ecrireDiag(JSON* json, char* nom){
	json->fichier = NULL;
	json->fichier = fopen(nom, "w");

	if(json->fichier != NULL){

		// On ouvre notre objet JSON
		fprintf(json->fichier, "{\n");

			ajouterEnt(json, "trait", json->pos.trait); fprintf(json->fichier, ",\n");
			ajouterEnt(json, "numDiag", json->numDiag); fprintf(json->fichier, ",\n");
			fprintf(json->fichier, "\"notes\":\"%s\",\n", json->desc);

			ecrirePos(json);

		fprintf(json->fichier, "\n}");
		// On ferme notre objet JSON

		fclose(json->fichier);
		return 1;
	}

	fclose(json->fichier);
	return 0;
}