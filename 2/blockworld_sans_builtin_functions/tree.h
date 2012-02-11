#include <blockworld.h>

#define LEAFRAND0to0_1      ((rand() % 100) / 1000.0f)
#define LEAFRAND0_3to0_8    ((rand() % 50) / 100.0f + 0.3f)

#define SIZELEAF        0.1d
#define SIZEBRANCH      4.0d

void bwTree();
void bwLeaf();
void bwBranch();
void bwStub();
void bwTrunk();

