int initMemory(int nbBytes);
int freeMemory();
void* myalloc(int nbBytes);
int myfree(void *p);
void initMemoryMessage(int nbBytesAlloue,int nbBytes);
void freeMemoryMessage(int nbBytesRecupere);
void myallocMessage(void* p,int nbBytes);
void myfreeMessage(int nbBytesRecupere);