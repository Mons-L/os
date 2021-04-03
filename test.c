/*!
 * \file test.c
 * \brief Fichier permettant d'utiliser les modes : "intéractif", "batch" et "ligne de commande" du programme.
 * \author Salma BENCHELKHA - Mouncif LEKMITI - Farah MANOUBI
 * \version 1.0
 * \date 2 avril 2021
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

void afficherOptions();
void recupererChoix(int* choix);
void gestionModeInteractif();
void gestionModeBatch(char* filename);
void gestionModeCli(int argc, char*argv[], int option);
void affichageAide();


/*!
 * \brief Fonction principale permettant la gestion des différents mode proposé à l'utilisateur.
 * \param [in] argc entier permettant la récupération du nombre d'arguments passé en paramètre. Type int.
 * \param [in] argv[] tableau de chaînes de caractères contenant les arguments. Type char*.
 * \return Retourne 0 en cas de réussite.
 */
int main(int argc, char *argv[]){
    if(argc > 1){
        int option = getopt(argc, argv, "m:a:d:lhif");
        // Si l'argument entré par l'utilisateur est '-i', le mode "intéractif" est lancé.
        if(option == 'i'){
            gestionModeInteractif();
        }
        // Si l'argument entré par l'utilisateur est '-f', le mode "batch" est lancé.
        else if(option == 'f'){
            getopt(argc,argv,":if:lrx");
            char* filename = optarg;
            gestionModeBatch(filename);
        }
        // Si l'argument entré par l'utilisateur est '-h', les commandes disponible sont affichées.
        else if(option =='h'){
            affichageAide();
        }
        // Sinon, le mode "ligne de commande" est lancé.  
        else{
            gestionModeCli(argc,argv,option);
        }
    }
    else{
        affichageAide(); 
    }

    return 0;
}

/*!
 * \brief Fonction affichant les différentes options disponibles pour le mode intéractif.
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
 * \brief Fonction récupérant le choix de l'utilisateur pour le mode intéractif.
 */
void recupererChoix(int* choix){
    printf("Votre choix : ");
    scanf("%d",choix);
    if(*choix <= 5)
        printf("\nVous avez choisis : %s.\n",choixString[*choix-1]);
}

/*!
 * \brief Fonction gérant les intéractions avec l'utilisateur en fonction des options choisies par ce dernier.
 */
void gestionModeInteractif(){
    printf("\nBienvenue dans le mode interactif du programme\n");
        int choix = -1;
        int nbBytes = 0;
        int allocAdesalloc = 0;
        do{
            // Affiche les options et récupère le choix de l'utilisateur.
            afficherOptions();
            recupererChoix(&choix);

            switch (choix){
                case 1:
                    // Récuperation du nombre de bytes à initialiser.
                    printf("Combien de bytes ?\t");
                    scanf("%d",&nbBytes);
                    // Initialisation de la mémoire et affichage d'un message sur l'état de l'initialisation.
                    initMemoryMessage(initMemory(nbBytes),nbBytes);
                    break;

                case 2:
                    // Libération de la mémoire et affichage d'un message sur l'état de la libération.
                    freeMemoryMessage(freeMemory());
                    break;

                case 3:
                    // Récuperation du nombre de bytes à allouer.
                    printf("Combien de bytes ?\t");
                    scanf("%d",&nbBytes);
                    // Allocation de la mémoire et affichage d'un message sur l'état de l'allocation.
                    myallocMessage(myalloc(nbBytes),nbBytes);
                    break;

                case 4:
                    // Récuperation de l'indice de l'allocation à désallouer.
                    printf("Quelle allocation souhaitez-vous desallouer ?\t");
                    scanf("%d",&allocAdesalloc);
                    int listeSize = tailleListe(memoireAllouee);
                    if(listeSize >= allocAdesalloc){
                        // Recherche du bloc mémoire à désallouer en fonction de l'indice.
                        Liste listeAdesalloue = rechercheParIndice(memoireAllouee,listeSize-allocAdesalloc); 
                        // Désallocation de la mémoire et affichage d'un message sur l'état de la désallocation.
                        myfreeMessage(myfree(listeAdesalloue->blocMemoire.adresse));
                    }
                    else
                        printf("Erreur l'indice %d est superieur au nombre d'element alloue.\n",allocAdesalloc);
                    break;

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
 * \brief Fonction gérant le mode batch permettant de lire des opérations définies dans un fichier de configuration.
 * \param [in] filename Chemin du fichier. Type char*.
 */
void gestionModeBatch(char* filename){
    printf("\nBienvenue dans le mode batch du programme.\n\n");
    int nbMots ;
    char** mots = fileToTab(filename,MAX,&nbMots); 
    
    // Effectue le traitement en fonction de ce qui a été lu.
    for(int i=0;i<nbMots;i++){

        // Si le mot lu est "InitMemory" on initialise la mémoire.
        if(strcmp(mots[i],"InitMemory") == 0){
            i++;
            int nbBytes = atoi(mots[i]);
            int longueurInt = log10(nbBytes) + 1;

            // Si le mot suivant contient des lettres, le programme sera interrompu.
            if(longueurInt != strlen(mots[i])){
                printf("Erreur dans la syntaxe du fichier sur le mot : %s, attendu : entier.\n",mots[i]);
                printf("Interruption du programme.\n");
                exit(EXIT_FAILURE);
            }

            // Sinon, on récupère le nombre de bytes afin d'initialiser la mémoire.
            else{
                int status = initMemory(nbBytes);
                initMemoryMessage(status,nbBytes);
                // S'il y a une erreur, on interrompt le programme.
                if(status == 0){
                    printf("Interruption du programme.\n");
                    exit(EXIT_FAILURE);
                } 
                printf("\n");
            }
        }
        
        // Si le mot lu est "FreeMemory", on récupère la mémoire de la zone initialement réservée.
        else if(strcmp(mots[i],"FreeMemory") == 0){
            int nbBytesRecupere = freeMemory();
            freeMemoryMessage(nbBytesRecupere);
            // S'il y a une erreur, on interrompt le programme.
            if(nbBytesRecupere == -1) {
                printf("Interruption du programme.\n");
                exit(EXIT_FAILURE);
            } 
            printf("\n");
        }

        // Si le mot lu est "Allocation", on alloue de la mémoire.
        else if(strcmp(mots[i],"Allocation") == 0){
            i++;
            int nbBytes = atoi(mots[i]);
            int longueurInt = log10(nbBytes) + 1;

            // Si le mot suivant contient des lettres, le programme sera interrompu.
            if(longueurInt != strlen(mots[i])){
                printf("Erreur dans la syntaxe du fichier sur le mot : %s, attendu : entier.\n",mots[i]);
                printf("Interruption du programme.\n");
                exit(EXIT_FAILURE);
            }

            // Sinon, on récupère le nombre de bytes afin d'allouer la mémoire.
            else{
                void* p = myalloc(nbBytes);
                myallocMessage(p,nbBytes);
                // S'il y a une erreur, on interrompt le programme.
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

            // Si le mot suivant contient des lettres, le programme sera interrompu.
            if(longueurInt != strlen(mots[i])){
                printf("Erreur dans la syntaxe du fichier sur le mot : %s, attendu : entier.\n",mots[i]);
                printf("Interruption du programme.\n");
                exit(EXIT_FAILURE);
            }

            // Sinon, on récupère l'indice de l'allocation à désallouer.
            else{
                /* On récupère la taille de la liste afin de la parcourir et de désallouer
                   en fonction des allocations faîtes précédemment.*/
                int listeSize = tailleListe(memoireAllouee);

                // Si l'indice à désallouer est inférieur ou égal à la liste, on effectue la désallocation.
                if(listeSize >= indice){
                    Liste listeAdesalloue = rechercheParIndice(memoireAllouee,listeSize-indice); 
                    int nbBytesRecupere = myfree(listeAdesalloue->blocMemoire.adresse);
                    myfreeMessage(nbBytesRecupere);
                    if(nbBytesRecupere == -1) exit(EXIT_FAILURE);
                    printf("\n");
                }
                // Sinon on interrompt le programme.
                else{
                    printf("Erreur l'indice %d de l'element a desallouer est superieur au nombre d'element alloue.\n",indice);
                    printf("Interruption du programme.\n");
                    exit(EXIT_FAILURE);
                }
            }
        }
        // Si aucun mot n'est reconnu, on interrompt le programme.
        else{
            printf("Erreur dans la syntaxe du fichier sur le mot : %s.\n",mots[i]);
            printf("Interruption du programme.\n");
            exit(EXIT_FAILURE);
        }
    }
}

 /*!
 * \brief Fonction gérant le mode "ligne de commande".
 * \param [in] argc entier permettant la récupération du nombre d'arguments passé en paramètre. Type int.
 * \param [in] argv[] tableau de chaînes de caractères contenant les arguments. Type char*.
 */
void gestionModeCli(int argc, char*argv[], int option){
    printf("Bienvenue dans le mode CLI.\n\n");

    // Tant que toutes les options n'ont pas été lues.
    do{
        int nbBytes,status,longueurInt,selectionne, listeSize;
        void* p = NULL;
        switch(option){

            case 'm':
                nbBytes = 0;
                nbBytes = atoi(optarg);
                longueurInt = log10(nbBytes) + 1;
                // Si le paramètre de l'option contient des lettres, le programme sera interrompu.
                if(nbBytes == 0 || longueurInt != strlen(optarg)){
                    printf("Initialisation de la memoire: impossible, argument '%s' incorrect\n",optarg); 
                    printf("Interruption du programme.\n");
                    exit(EXIT_FAILURE);
                }
                // Initialisation de la mémoire avec le paramètre de l'option.
                status = initMemory(nbBytes);
                // Affichage d'un message sur l'état de l'initialisation.
                initMemoryMessage(status,nbBytes);
                // S'il y a une erreur, on interrompt le programme.
                if(status == 0) exit(EXIT_FAILURE);
                printf("\n");
                break;

            case 'a':
                nbBytes = 0;
                nbBytes = atoi(optarg);
                longueurInt = log10(nbBytes) + 1;
                // Si le paramètre de l'option contient des lettres, le programme sera interrompu.
                if(nbBytes == 0 || longueurInt != strlen(optarg)){
                    printf("Allocation memoire : impossible, argument '%s' incorrect\n",optarg); 
                    printf("Interruption du programme.\n");
                    exit(EXIT_FAILURE);
                }
                // Allocation de la mémoire avec le paramètre de l'option.
                p = myalloc(nbBytes);
                // Affichage d'un message sur l'état de l'allocation.
                myallocMessage(p,nbBytes);
                // S'il y a une erreur, on interrompt le programme.
                if(p == NULL) exit(EXIT_FAILURE);
                printf("\n");;
                break;

            case 'd':
                selectionne = 0;
                selectionne = atoi(optarg);
                longueurInt = log10(selectionne) + 1;
                listeSize = tailleListe(memoireAllouee);
                // Si le paramètre de l'option contient des lettres, le programme sera interrompu.
                if(selectionne == 0 || longueurInt != strlen(optarg)){
                    printf("Desallocation memoire : impossible, argument '%s' incorrect.\n",optarg); 
                    printf("Interruption du programme.\n");
                    exit(EXIT_FAILURE);
                }
                // Si le paramètre de l'option est supérieur au nombre d'allocation effectuée, le programme sera interrompu.
                else if(listeSize < selectionne){
                    printf("Desallocation memoire : impossible, indice '%d' superieur au nombre d'element alloue.\n",selectionne); 
                    printf("Interruption du programme.\n");
                    exit(EXIT_FAILURE);
                }
                Liste listeAdesalloue = rechercheParIndice(memoireAllouee,listeSize-selectionne);
                // Désallocation de la mémoire avec le paramètre de l'option.
                nbBytes = myfree(listeAdesalloue->blocMemoire.adresse);
                // Affichage d'un message sur l'état de la désallocation.
                myfreeMessage(nbBytes);
                // S'il y a une erreur, on interrompt le programme.
                if(nbBytes == -1) exit(EXIT_FAILURE);
                printf("\n");;
                break;

            case 'l':
                // Libération de la mémoire initialement allouée.
                nbBytes = freeMemory();
                // Affichage d'un message sur l'état de la libération de mémoire.
                freeMemoryMessage(nbBytes);
                // S'il y a une erreur, on interrompt le programme.
                if(nbBytes == -1) exit(EXIT_FAILURE);
                break;
        }
    }while ((option = getopt(argc, argv, "m:a:d:l"))!= -1);
}


//Affichage des options disponible pour le programme.
void affichageAide(){
    printf("Voici toutes les commandes disponibles pour ce programme : \n");
    printf("\n-i\t\tUtilisation du programme en mode interactif.\n");
    printf("-f path\t\tUtilisation du programme en mode batch avec le fichier 'path'.\n");
    printf("\nUtilisation du programme en mode ligne de commande : \n");
    printf("\t\t-m nbBytes\tInitialisation de 'nbBytes' bytes pour la zone de travail.\n");
    printf("\t\t-a nbBytes\tAllocation de 'nbBytes' bytes dans la memoire.\n"); 
    printf("\t\t-d indice\tDesallocation de l'allocation memoire numero 'indice'.\n"); 
    printf("\t\t-l \t\tLiberation de la memoire initialement allouee.\n");
}