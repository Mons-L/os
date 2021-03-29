#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <unistd.h>
#include "include/structure.h"
#include "include/liste.h"
#include "include/espaceMemoire.h"
#include "include/utilitaire.h"

#define MAX 20
#define CHOIX_INIT_MEMORY "Initialiser la zone de travail pour le programme [initMemory()]"
#define CHOIX_FREE_MEMORY "Recuperer la zone de travail initialement reserve au programme [freeMemory()]"
#define CHOIX_MYALLOC "Allouer de la memoire dans la zone de travail [myalloc(int nbBytes)]"
#define CHOIX_MYFREE "Desallouer une zone adressee par un pointeur dans la zone de travail [myfree(void* p)]"
#define CHOIX_QUITTER "Quitter le programme"
char* choixString[5] = {CHOIX_INIT_MEMORY,CHOIX_FREE_MEMORY,CHOIX_MYALLOC,CHOIX_MYFREE,CHOIX_QUITTER};

extern char *optarg;
Liste memoireLibre, memoireAllouee;

void afficherOptions(){
    printf("\nQue souhaitez-vous faire ?\n");
    printf("1 : %s\n",CHOIX_INIT_MEMORY);
    printf("2 : %s\n",CHOIX_FREE_MEMORY);
    printf("3 : %s\n",CHOIX_MYALLOC);
    printf("4 : %s\n",CHOIX_MYFREE);
    printf("5 : %s\n\n",CHOIX_QUITTER);
}

void recupererChoix(int* choix){
    printf("Votre choix : ");
    scanf("%d",choix);
    printf("\nVous avez choisis : %s\n",choixString[*choix]);
}

void gestionModeInteractif(){
    printf("\nBienvenue dans le mode interactif du programme\n");
        int choix = -1;
        int nbBytes = 0;
        void* adresse = NULL;
        do{
            afficherOptions();
            recupererChoix(&choix);
            switch (choix){
                case 1:
                    printf("Combien de bytes ?\t");
                    scanf("%d",&nbBytes);
                    initMemoryMessage(initMemory(nbBytes),nbBytes);
                    break;

                case 2:
                    freeMemoryMessage(freeMemory());
                    break;

                case 3:
                    printf("Combien de bytes ?\t");
                    scanf("%d",&nbBytes);
                    myallocMessage(myalloc(nbBytes),nbBytes);
                    break;

                case 4:
                    printf("Quel est l'adresse memoire ?\t");
                    scanf("%p",&adresse);
                    myfreeMessage(myfree(adresse));
                    break;

                case 5:
                    printf("arret du programme\n");
                    choix = 5;
                    break;

                default:
                    printf("Votre choix n'a pas ete reconnue, veuillez choisir un nombre entre 1 et 5");
                    break;
            }
            sleep(2);
        }while(choix != 5);
}

int main(int argc, char *argv[]){

    if(argv[1][0] == '-' && argv[1][1] == 'i'){
        //Gerer le mode interactif
        gestionModeInteractif();
    }
    else if(argv[1][0] == '-' && argv[1][1] == 'f'){
        printf("\nBienvenue dans le mode batch du programme\n\n");
        FILE *fichier;
        int nbMots,nbCar = 0;
        char** mots;
        char caractere;
        char* filename;
        getopt(argc,argv,":if:lrx");
        filename = optarg;

        //printf("Voici le contenu du fichier %s : \n",optarg);

        fichier = fopen(filename,"r");
        FILE *f2 = fopen(filename,"r");

        //On compte le nombre de mot pour l'initialisation du tableau de mots
        while((caractere=fgetc(f2)) != EOF){
            nbCar++;
            if (caractere == ' ' || caractere == '\t' || caractere == '\n' || caractere == '\0')
                nbMots++;
        }
        //On incrémente le nombre de mot pour prendre en compte le dernier mot
        if(nbCar>0)
            nbMots++;

        //On initialise le tableau de mots
        mots = (char**)malloc(sizeof(char*)*nbMots);
        for(int i=0;i<nbMots;i++){
            mots[i] = (char*)malloc(sizeof(char)*MAX);
        }

        //On remplit le tableau de mots
        int i = 0;
        int j = 0;
        while((caractere=fgetc(fichier)) != EOF){
            if (caractere == ' ' || caractere == '\t' || caractere == '\n' || caractere == '\0'){
                while(j<20){
                    mots[i][j] = '\0';
                    j++;
                }
                i++;
                j=0;
            }
            else{
                mots[i][j] = caractere;
                j++;
            }
        }
        //Remplir le tableau du dernier mot avec des cases vides
        while(j<20){
            mots[i][j] = '\0';
            j++;
        }

        //On affiche les mots qui ont été lue
        for(int i=0;i<nbMots;i++){
            if(strcmp(mots[i],"InitMemory") == 0){
                i++;
                int nbBytes = atoi(mots[i]);
                int longueurInt = log10(nbBytes) + 1;
                if(longueurInt != strlen(mots[i])){
                    printf("Erreur dans la syntaxe du fichier sur le mot : %s, attendu : entier\n",mots[i]);
                    printf("Interruption du programme\n");
                    exit(EXIT_FAILURE);
                }
                else{
                    int status = initMemory(nbBytes);
                    initMemoryMessage(status,nbBytes);
                    if(status == 0) exit(EXIT_FAILURE);
                    printf("\n");
                }
            }
            
            else if(strcmp(mots[i],"FreeMemory") == 0){
                int nbBytesRecupere = freeMemory();
                freeMemoryMessage(nbBytesRecupere);
                if(nbBytesRecupere == -1)   exit(EXIT_FAILURE);
            }

            else if(strcmp(mots[i],"Allocation") == 0){
                i++;
                int nbBytes = atoi(mots[i]);
                int longueurInt = log10(nbBytes) + 1;
                if(longueurInt != strlen(mots[i])){
                    printf("Erreur dans la syntaxe du fichier sur le mot : %s, attendu : entier\n",mots[i]);
                    printf("Interruption du programme\n");
                    exit(EXIT_FAILURE);
                }
                else{
                    void* p = myalloc(nbBytes);
                    myallocMessage(p,nbBytes);
                    if(p == NULL) exit(EXIT_FAILURE);
                    printf("\n");
                }
            }
            

            else if(strcmp(mots[i],"Desallocation") == 0){
                i++;
                int indice = atoi(mots[i]);
                int longueurInt = log10(indice) + 1;
                if(longueurInt != strlen(mots[i])){
                    printf("Erreur dans la syntaxe du fichier sur le mot : %s, attendu : entier\n",mots[i]);
                    printf("Interruption du programme\n");
                    exit(EXIT_FAILURE);
                }
                else{
                    int listeSize = tailleListe(memoireAllouee);
                    if(listeSize >= indice){
                        Liste listeAdesalloue = rechercheParIndice(memoireAllouee,listeSize-indice); 
                        int nbBytesRecupere = myfree(listeAdesalloue->blocMemoire.adresse);
                        myfreeMessage(nbBytesRecupere);
                        if(nbBytesRecupere == -1) exit(EXIT_FAILURE);
                        printf("\n");
                    }
                    else{
                        printf("Erreur l'indice %d de l'element a desallouer est superieur au nombre d'element alloue\n",indice);
                        printf("Interruption du programme\n");
                        exit(EXIT_FAILURE);
                    }
                }
            }

            else{
                printf("Erreur dans la syntaxe du fichier sur le mot : %s\n",mots[i]);
                printf("Interruption du programme\n");
                exit(EXIT_FAILURE);
            }
        }
        

        
        //On ferme le fichier
        fclose(fichier);
        fclose(f2);
    }    
   /* else{
        printf("Option non reconnue.\n");
        printf("%s\n",argv[1]);
    }*/
    
    else{
        printf("C'est le mode CLI\n");
        //Faire la ligne de commande
        int getopt();
        int test;
        while ((test = getopt(argc, argv, "m:a:f:"))!= -1){
            switch(test){
                case 'm':
                printf("Initialisation de la memoire: %s \n",optarg);
                int init = atoi(optarg);
                if(init==0){
                    printf("allocation impossible. \n", init);
                }
                initMemory(init);
                break;
                
                case 'a':
                printf("Allocation de la memoire: %s \n", optarg);
                int alloc = atoi(optarg);
                myalloc(alloc);
                break;

                case 'f':
                printf("Desallocation de la memoire: %s \n", optarg);
                void* p1 = myalloc(alloc);
                myfree(p1);
                break;


            }
        }
    }
    return 0;
}

