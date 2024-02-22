#include "../include/csds/gde.h"
#include <stdio.h>
#include <stdlib.h>

Gde* gde_create() {
	Gde* gde = (Gde*) malloc(sizeof(Gde));
	if (gde == NULL) {
		perror("Error allocating memory for generic data example");
		exit(EXIT_FAILURE);
	}
	gde->a = 0;
	gde->b = 1;
	gde->c = 2;
	gde->d = 3;

	return gde;
}

void gde_destroy(Gde* gde) {
	free(gde);
}
