/*!
 * \file structure.h
 * \brief Fichier de déclaration des structures.
 * \author Salma BENCHELKHA - Mouncif LEKMITI - Farah MANOUBI
 * \version 1.0
 * \date 2 avril 2021
 *  
 * Ce fichier contient la déclaration des structures d'un bloc mémoire et d'une liste.
 */

/**
 * \struct BlocMemoire
 * \brief Objet bloc mémoire.
 *
 * BlocMemoire est un petit objet de gestion des blocs mémoires. 
 * Le pointeur adresse pointe vers une adresse mémoire et 
 * le nombre de bytes qui lui a été alloué est contenu dans nbBytes.
 */
typedef struct{
	void* adresse;	/*!< Pointeur vers une adresse mémoire. */
	int nbBytes;	/*!< Nombre de bytes alloué pour cette adresse mémoire. */
}BlocMemoire;

/**
 * \struct Liste
 * \brief Objet liste.
 *
 * Liste est un petit objet de gestion des listes. 
 * Le pointeur suivant pointe vers l'adresse de la cellule suivante et 
 * un blocMemoire est contenu dans chaque liste.
 */
typedef struct cellule{
	BlocMemoire blocMemoire;	/*!< Bloc mémoire. */
	struct cellule *suivant;	/*!< Pointeur vers la cellule suivante. */
}*Liste;