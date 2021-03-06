#include <blockworld.h>

#define SIZELEAF           0.3d
#define SIZEBRANCH         5.0d

#define SIZEBARK           0.1d
#define SIZESTUB           14 * SIZEBARK * 6
#define NSTUBSINTRUNK      5

#define MAINBRANCHLEVELS   2
#define NMAINBRANCHESONLEVEL        5
#define SEPARATIONBWMAINBRANCHES    (360 / (NMAINBRANCHESONLEVEL + 1))

void bwLeaf();
void bwBranch();
void bwMainBranch();
void bwStub();
void bwTrunk();
void bwTree();

