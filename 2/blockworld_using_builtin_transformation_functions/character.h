#include <blockworld.h>

#define SIZELEGh     2.0d
#define SIZELEGb     0.7d
#define SIZELEGl     SIZELEGb

#define SIZEBODYl    4.2d
#define SIZEBODYb    2.4d
#define SIZEBODYh    SIZEBODYb

#define SIZETAILl    0.31d
#define SIZETAILb    0.8d
#define SIZETAILh    0.8d

#define SIZEHEADl1   (4 * SIZEBODYl / 7)
#define SIZEHEADb1   SIZEBODYb
#define SIZEHEADh1   (1 * SIZEBODYh / 2)

#define SIZEHEADl2   (SIZEHEADl1 / 2)
#define SIZEHEADb2   SIZEHEADb1
#define SIZEHEADh2   SIZEHEADh1

#define SIZEEARh     0.9d
#define SIZEEARl     0.3d
#define SIZEEARb     (2 * SIZEEARl)

#define SIZEEYE      (1.4 * SIZEHEADb2 / 5)

#define SIZENOSE     (1.1 * SIZEHEADb2 / 5)

void bwTail();
void bwBody();
void bwHead();
void bwDog();

