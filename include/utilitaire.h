/*!
 * \file utilitaire.h
 * \brief Fichier de déclaration des fonctions utiles à la manipulation de la mémoire.
 * \author Salma BENCHELKHA - Mouncif LEKMITI - Farah MANOUBI
 * \version 1.0
 * \date 2 avril 2021
 *  
 * Ce fichier contient la déclaration des fonctions d'initialisation, d'allocation, 
 * de désallocation et de libération de la mémoire. Elle contient également la 
 * déclaration d'une fonction permettant la défragmentation de l'espace mémoire.
 */

/*!
 * \brief Fonction permettant l'initialisation de la mémoire de la zone de travail.
 *        Elle permet d'allouer de la mémoire à l'aide du nombre de bytes passé en paramètre.
 * 		  Elle initialise la liste de mémoire libre avec le nombre de bytes passé en paramètre et
 * 		  l'adresse de la mémoire initilisée. Elle initialise également la liste de mémoire allouée à NULL.
 * \param [in,out] nbBytes Nombre de byte à initialiser. Type int.  
 * \return Le nombre de byte alloué.
 */
int initMemory(int nbBytes);

/*!
 * \brief Fonction permettant la récupération de la mémoire de la zone initialement réservée.
 * \return Le nombre de byte récupéré ou -1 en cas d'echec.
 */
int freeMemory();

/*!
 * \brief Fonction permettant l'allocation dynamique d'espace dans la zone de travail.
 * \param [in] nbBytes Nombre de byte à alloué. Type int.  
 * \return L'adresse allouée ou NULL en cas d'erreur.
 */
void* myalloc(int nbBytes);

/*!
 * \brief Fonction permettant la désallocation dynamique d'espace dans une zone adressée par un pointeur.
 * \param [in] p pointeur vers l'adresse mémoire recherchée. Type void*.
 * \return Le nombre de bytes récupéré ou -1 en cas d'erreur.
 */
int myfree(void *p);

/*!
 * \brief Fonction permettant l'affichage des messages concernant l'initialisation de la mémoire.
 * \param [in] nbBytesAlloue Nombre de byte alloué du bloc mémoire. Type int. 
 * \param [in] nbBytes Nombre de byte du bloc mémoire. Type int.   
 */
void initMemoryMessage(int nbBytesAlloue,int nbBytes);

/*!
 * \brief Fonction permettant l'affichage des messages concernant la récuperation de la mémoire.
 * \param [in] nbBytesRecupere Nombre de byte récupéré du bloc mémoire. Type int. 
 */
void freeMemoryMessage(int nbBytesRecupere);

/*!
 * \brief Fonction permettant l'affichage des messages concernant l'allocation de mémoire.
 * \param [in] p pointeur vers l'adresse mémoire allouée. Type void*.
 * \param [in] nbBytes Nombre de byte alloué. Type int. 
 */
void myallocMessage(void* p,int nbBytes);

/*!
 * \brief Fonction permettant l'affichage des messages concernant la désallocation de la mémoire.
 * \param [in] nbBytesRecupere Nombre de byte récupéré. Type int. 
 */
void myfreeMessage(int nbBytesRecupere);

/*!
 * \brief Fonction permettant la défragmentation de la mémoire libre.
 * \param [in, out] liste espace mémoire libre à défragmenter. Type Liste.
 * \return Une liste d'espace mémoire libre défragmentée.
 */
Liste defragmentation(Liste liste);

/*!
 * \brief Fonction permettant de remplir un tableau à partir d'un fichier.
 * \param [in] filename Chemin où se trouve le chemin. Type char*.
 * \param [in] longMaxMot Entier représentant la taille de la longueur maximal d'un mot. Type int.
 * \param [in, out] tailleTableau Entier où sera stocker la taille du tableau. Type int*.
 * \return Un tableau contenant les mots du fichier passé en paramètre.
 */
char** fileToTab(char* filename,int longMaxMot,int* nbMots);