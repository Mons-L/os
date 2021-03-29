int initMemory(int nbBytes);
int freeMemory();
void* myalloc(int nbBytes);
int myfree(void *p);
void myallocMessage(void* p,int nbBytes);
void initMemoryMessage(int nbBytesAlloue,int nbBytes);

