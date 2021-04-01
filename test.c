/*!
 * \file test.c
 * \brief Fichier qui comporte les programmes de test des différentes fonctions créees.
 * \author Salma BENCHELKHA - Mouncif LEKMITI - Farah MANOUBI
 * \version 1.0
 * \date 2 avril 2021
 * 
 * Ce fichier contient les programmes permettant de tester les fonctions suivant différents modes:
 * le mode intéractif, le mode batch et le mode "ligne de commande"
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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


/*!
 * \brief Fonction qui affiche les différentes options disponibles pour le mode intéractif.
 */
void afficherOptions(){
    printf("\nQue souhaitez-vous faire ?\n");
    printf("1 : %s.\n",CHOIX_INIT_MEMORY);
    printf("2 : %s.\n",CHOIX_FREE_MEMORY);
    printf("3 : %s.\n",CHOIX_MYALLOC);
    printf("4 : %s.\n",CHOIX_MYFREE);
    printf("5 : %s.\n\n",CHOIX_QUITTER);
}

/*!
 * \brief Fonction qui récupère le choix de l'utilisateur pour le mode intéractif.
 */
void recupererChoix(int* choix){
    printf("Votre choix : ");
    scanf("%d",choix);
    if(*choix <= 5)
        printf("\nVous avez choisis : %s.\n",choixString[*choix-1]);
}

/*!
 * \brief Fonction qui gère les intéractions avec l'utilisateur en fonction des options choisiespar ce dernier.
 */
void gestionModeInteractif(){
    printf("\nBienvenue dans le mode interactif du programme\n");
        int choix = -1;
        int nbBytes = 0;
        int allocAdesalloc = 0;
        do{
            //Affiche les options et récupère le choix de l'utilisateur.
            afficherOptions();
            recupererChoix(&choix);

            //Différents cas sont réalisés selon l'option choisie.
            switch (choix){
                //Initialisation de la mémoire
                case 1:
                    printf("Combien de bytes ?\t");
                    scanf("%d",&nbBytes);
                    initMemoryMessage(initMemory(nbBytes),nbBytes);
                    break;

                //Recupere la zone de travail initialement reserve au programme freeMemory.
                case 2:
                    freeMemoryMessage(freeMemory());
                    break;

                //Allocation de la mémoire .
                case 3:
                    printf("Combien de bytes ?\t");
                    scanf("%d",&nbBytes);
                    myallocMessage(myalloc(nbBytes),nbBytes);
                    break;

                //Désalloue de la mémoire
                case 4:
                    printf("Quelle allocation souhaitez-vous desallouer ?\t");
                    scanf("%d",&allocAdesalloc);
                    int listeSize = tailleListe(memoireAllouee);
                    if(listeSize >= allocAdesalloc){
                        Liste listeAdesalloue = rechercheParIndice(memoireAllouee,listeSize-allocAdesalloc); 
                        myfreeMessage(myfree(listeAdesalloue->blocMemoire.adresse));
                    }
                    else
                        printf("Erreur l'indice %d est superieur au nombre d'element alloue.\n",allocAdesalloc);
                    break;

                //Permet de quitter le programme
                case 5:
                    printf("Arret du programme.\n");
                    choix = 5;
                    break;

                default:
                    printf("Votre choix n'a pas ete reconnue, veuillez choisir un nombre entre 1 et 5.\n");
                    break;
            }
            sleep(2);
        }while(choix != 5);
}

/*!
 * \brief Fonction qui gère le mode batch permettant de lire des opérations définies dans un fichier de configuration.
 */
void gestionModeBatch(char* filename){
    printf("\nBienvenue dans le mode batch du programme.\n\n");
    int nbMots ;
    char** mots = fileToTab(filename,MAX,&nbMots); 
    
    //Effectue le traitement en fonction de ce qui a été lue
    for(int i=0;i<nbMots;i++){

        //Si le mot lu est InitMemory on initialise la mémoire.
        if(strcmp(mots[i],"InitMemory") == 0){
            i++;
            int nbBytes = atoi(mots[i]);
            int longueurInt = log10(nbBytes) + 1;

            //Si l'entier contient des lettres, le programme sera interrompu.
            if(longueurInt != strlen(mots[i])){
                printf("Erreur dans la syntaxe du fichier sur le mot : %s, attendu : entier.\n",mots[i]);
                printf("Interruption du programme.\n");
                exit(EXIT_FAILURE);
            }

            //Récupère le nombre de bits afin d'initialiser la mémoire.
            else{
                int status = initMemory(nbBytes);
                initMemoryMessage(status,nbBytes);
                if(status == 0){
                    printf("Interruption du programme.\n");
                    exit(EXIT_FAILURE);
                } 
                printf("\n");
            }
        }
        
        //Si le mot lu est FreeMemory,on récupère de la mémoire au niveau de la zone initialement réservée.
        else if(strcmp(mots[i],"FreeMemory") == 0){
            int nbBytesRecupere = freeMemory();
            freeMemoryMessage(nbBytesRecupere);
            if(nbBytesRecupere == -1) {
                printf("Interruption du programme.\n");
                exit(EXIT_FAILURE);
            } 
            printf("\n");
        }

        //Si le mot lu est Allocation, on alloue de la mémoire.
        else if(strcmp(mots[i],"Allocation") == 0){
            i++;
            int nbBytes = atoi(mots[i]);
            int longueurInt = log10(nbBytes) + 1;

            //Si l'entier contient des lettres, le programme sera interrompu.
            if(longueurInt != strlen(mots[i])){
                printf("Erreur dans la syntaxe du fichier sur le mot : %s, attendu : entier.\n",mots[i]);
                printf("Interruption du programme.\n");
                exit(EXIT_FAILURE);
            }

            //Récupère le nombre de bits afin d'allouer de la mémoire.
            else{
                void* p = myalloc(nbBytes);
                myallocMessage(p,nbBytes);
                if(p == NULL){
                    printf("Interruption du programme.\n");
                    exit(EXIT_FAILURE);
                } 
                printf("\n");
            }
        }
        
        //Si le mot lu est Desallocation, on désalloue de la mémoire.
        else if(strcmp(mots[i],"Desallocation") == 0){
            i++;
            int indice = atoi(mots[i]);
            int longueurInt = log10(indice) + 1;

            //Si l'entier contient des lettres, le programme sera interrompu.
            if(longueurInt != strlen(mots[i])){
                printf("Erreur dans la syntaxe du fichier sur le mot : %s, attendu : entier.\n",mots[i]);
                printf("Interruption du programme.\n");
                exit(EXIT_FAILURE);
            }

            //On récupère la taille de la liste afin de la parcourir et de désallouer en fonction des allocations faîtes précédemment.
            //La recherche de l'indice se fait dans le sens inverse de la liste.
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
                    printf("Erreur l'indice %d de l'element a desallouer est superieur au nombre d'element alloue.\n",indice);
                    printf("Interruption du programme.\n");
                    exit(EXIT_FAILURE);
                }
            }
        }

        else{
            printf("Erreur dans la syntaxe du fichier sur le mot : %s.\n",mots[i]);
            printf("Interruption du programme.\n");
            exit(EXIT_FAILURE);
        }
    }
}

 /*!
 * \brief Fonction permettant la désallocation dynamique d'espace dans une zone adressée par un pointeur.
 * \param [in] argc entier permettant la récupération du nombre d'arguments passé en paramètre. Type int.
 * \param [in] argv[] tableau de chaînes de caractères contenant les arguments. Type char*.
 */
void gestionModeCli(int argc, char*argv[]){
    printf("Bienvenue dans le mode CLI.\n");
    // int getopt();
    int test;
    // Tant que A REVOIR
    while ((test = getopt(argc, argv, "m:a:d:l"))!= -1){
        int nbBytes,status,longueurInt,selectionne, listeSize;
        void* p = NULL;
        switch(test){
            // Si l'utilisateur entre le charactère 'm', une initialisation de la mémoire sera effectuée.
            case 'm':
                nbBytes = 0;
                nbBytes = atoi(optarg);
                longueurInt = log10(nbBytes) + 1;
                if(nbBytes == 0 || longueurInt != strlen(optarg)){
                    printf("Initialisation de la memoire: impossible, argument '%s' incorrect\n",optarg); 
                    exit(EXIT_FAILURE);
                }
                status = initMemory(nbBytes);
                initMemoryMessage(status,nbBytes);
                if(status == 0) exit(EXIT_FAILURE);
                printf("\n");
                break;

            // Si l'utilisateur entre le charactère 'a', une allocation de la mémoire sera effectuée.
            case 'a':
                nbBytes = 0;
                nbBytes = atoi(optarg);
                longueurInt = log10(nbBytes) + 1;
                if(nbBytes == 0 || longueurInt != strlen(optarg)){
                    printf("Allocation memoire : impossible, argument '%s' incorrect\n",optarg); 
                    exit(EXIT_FAILURE);
                }
                p = myalloc(nbBytes);
                myallocMessage(p,nbBytes);
                if(p == NULL) exit(EXIT_FAILURE);
                printf("\n");;
                break;

            // Si l'utilisateur entre le charactère 'd', une désallocation de la mémoire sera effectuée.
            case 'd':
                selectionne = 0;
                selectionne = atoi(optarg);
                longueurInt = log10(selectionne) + 1;
                listeSize = tailleListe(memoireAllouee);
                if(selectionne == 0 || longueurInt != strlen(optarg)){
                    printf("Desallocation memoire : impossible, argument '%s' incorrect.\n",optarg); 
                    exit(EXIT_FAILURE);
                }
                else if(listeSize < selectionne){
                    printf("Desallocation memoire : impossible, indice '%d' superieur au nombre d'element alloue.\n",selectionne); 
                    exit(EXIT_FAILURE);
                }
                Liste listeAdesalloue = rechercheParIndice(memoireAllouee,listeSize-selectionne);
                nbBytes = myfree(listeAdesalloue->blocMemoire.adresse);
                myfreeMessage(nbBytes);
                if(nbBytes == -1) exit(EXIT_FAILURE);
                printf("\n");;
                break;

            // Si l'utilisateur entre le charactère 'l', une libération de la mémoire sera effectuée.
            case 'l':
                nbBytes = freeMemory();
                freeMemoryMessage(nbBytes);
                if(nbBytes == -1) exit(EXIT_FAILURE);
                break;
        }
    }
}

/*!
 * \brief Fonction principale permettante la gestion des différents mode proposé à l'utilisateur.
 * \param [in] argc entier permettant la récupération du nombre d'arguments passé en paramètre. Type int.
 * \param [in] argv[] tableau de chaînes de caractères contenant les arguments. Type char*.
 * \return 0
 */
int main(int argc, char *argv[]){

    // Si l'argument entré par l'utilisateur est '-i', le mode intéractif est lancée.
    if(argv[1][0] == '-' && argv[1][1] == 'i'){
        gestionModeInteractif();
    }
    // Si l'argument entré par l'utilisateur est '-f', le mode batch est lancée.
    else if(argv[1][0] == '-' && argv[1][1] == 'f'){
        getopt(argc,argv,":if:lrx");
        char* filename = optarg;
        gestionModeBatch(filename);
    }  
    // Si l'argument entré par l'utilisateur n'est ni '-i', ni '-f', le mode ligne de commande est lancée.  
    else{
        gestionModeCli(argc,argv);
    }
    
    return 0;
}
