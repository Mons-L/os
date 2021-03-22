#include<stdlib.h>

typedef struct cellule{
    int nbBytes ;
    void* adressMemory;
    struct cellule *precedent ;
    struct cellule *suivant ;
 }*Liste ;

typedef struct _BlockHeader {
    int Size;
} BlockHeader;

 Liste findEqualOrGreater(Liste l, int nbBytes){
    if(l==NULL){
        return NULL;
    }    
    else{
        if(l->nbBytes >= nbBytes){
            return l;
        }
        else{
            return find(l->suivant, nbBytes);
        }
    }    
 }

 void insertElt(Liste l, int nbBytes){
     while(l->suivant != NULL && l->nbBytes <= nbBytes){
         l = l->suivant;
     }
     Liste ll;
    ll->nbBytes = nbBytes;
     if(l->nbBytes <= nbBytes){
        ll->suivant = l;
        ll->precedent = l->precedent;
        l->precedent->suivant = ll;
        l->precedent = ll;
     }
     else{
        ll->suivant = l->suivant;
        l->suivant = ll;
        ll->precedent = l;
     }
 }

 void suppElt(Liste l, Liste ltoDelete){
     while(l!=NULL && l != ltoDelete){
         l = l->suivant;
     }
     if(l != NULL){
         Liste temp;
         l->precedent->suivant = l->suivant;
         l->suivant->precedent = l->precedent;
         free(l);
         l = NULL;
     }
 }

void* myAlloc(int nbBytes){
    Liste memoireLibre;
    void* allocatedAddress = NULL;
    Liste l = findEqualOrGreater(memoireLibre, nbBytes);
    if(l != NULL){
        if(l->nbBytes == nbBytes){
            allocatedAddress = l->adressMemory;
        }
        else if(l->nbBytes > nbBytes){
            //Couper la liste en 2
            Liste lp1;
            lp1->nbBytes = nbBytes;
            lp1->adressMemory = l->adressMemory;
            
            Liste lp2;
            lp2->nbBytes = l->nbBytes - nbBytes;
            lp2->adressMemory = l->adressMemory+nbBytes;

            suppElt(memoireLibre, l);
            insertElt(lp2,lp2->nbBytes);
            allocatedAddress = lp1->adressMemory;
        }
    }
    return allocatedAddress;
}

int myFree(void *p){
    if(p == NULL){
        return -1;
    }
    else{
        Liste memoireLibre;
        Liste l;
        l->nbBytes = p - sizeof(int);
        l->adressMemory = p;
        insertElt(memoireLibre, l);
        return l->nbBytes;
    }
}