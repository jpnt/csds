#ifndef CSDS_GDE_H
#define CSDS_GDE_H

// Generic Data Example
// Used to test the generic aspect of the data structures

typedef struct {
	int a;
	short b;
	char c;
	char d;
} Gde;

Gde* gde_create();
void gde_destroy(Gde* gde);

#endif // !CSDS_GDE_H
