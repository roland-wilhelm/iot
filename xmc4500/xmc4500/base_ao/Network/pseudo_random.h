
#ifndef PSEUDO_RANDOM_H
#define PSEUDO_RANDOM_H
 

#include "md5.h"

void rnd_init(char*);

char rnd_nextChar(void);

int rnd_nextInt(void);

void rnd_fillArray(char*, unsigned int);

#endif /* PSEUDO_RANDOM_H */
