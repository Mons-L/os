/*!
 * \file liste.h
 * \brief Fichier de déclaration des fonctions sur les listes.
 * \author Salma BENCHELKHA - Mouncif LEKMITI - Farah MANOUBI
 * \version 1.0
 * \date 2 avril 2021
 *  
 * Ce fichier contient la déclaration des fonction sur les listes.
 */


/*!
 * \brief Fonction permettant l'initialisation d'une liste.
 * \return Renvoie NULL.
 */
Liste initListe();

/*!
 * \brief Fonction permettant l'allocation de la mémoire d'une liste.
 *        Celle-ci initialise ensuite ses variables avec les valeurs passées en paramètre.
 * \param [in, out] liste Liste à initialiser. Type Liste.
 * \param [in] nbBytes Nombre de byte du bloc mémoire. Type int.  
 * \param [in] adresse Pointeur vers une adresse mémoire. Type void*.
 * \param [in] suivant Liste suivante. Type Liste. 
 * \return Une liste.
 */
Liste initVariableListe(Liste liste, int nbBytes, void *adresse, Liste suivant);

/*!
 * \brief Fonction permettant l'insertion d'une liste en tête d'une liste chainée.
 * \param [in] liste Liste où sera inserée une liste en tête. Type Liste
 * \param [in] nbBytes Nombre de byte du bloc mémoire pour la liste à inserer. Type int.  
 * \param [in] adresse pointeur vers une adresse mémoire pour la liste à inserer. Type void*. 
 * \return Une liste.
 */
Liste inserTete(Liste liste, int nbBytes, void* adresseMemoire);

/*!
 * \brief Fonction permettant la suppression de la liste en tête d'une liste chainée.
 * \param [in, out] liste Liste à supprimer. Type Liste
 * \return Une liste.
 */
Liste suppTete(Liste liste);

/*!
 * \brief Fonction permettant la suppression d'une liste contenu dans une liste chainée.
 * \param [in, out] liste Liste chaînée où sera supprimée la liste passé en paramètre. Type Liste.
 * \param [in] listeAsupp Liste à supprimer. Type Liste.
 * \return Une liste.
 */
Liste suppListe(Liste liste, Liste listeAsupp);

/*!
 * \brief Fonction permettant la recherche d'une liste contenant un bloc mémoire avec un nombre
 *        de bytes supérieur ou égal au nombre passé en paramètre.
 * \param [in, out] liste Liste où effectuer la recherche. Type Liste.
 * \param [in] nbBytes Nombre de byte du bloc mémoire recherché. Type int.  
 * \return Une liste avec un bloc mémoire contenant un nombre de byte supérieur ou égal ou NULL.
 */
Liste rechercheElement(Liste liste, int element);

/*!
 * \brief Fonction permettant la recherche d'une liste contenant un bloc mémoire avec une adresse
 *        égal à l'adresse passée en paramètre.
 * \param [in, out] liste Liste où effectuer la recherche. Type Liste.
 * \param [in] p pointeur vers l'adresse mémoire recherchée. Type void*.
 * \return Une liste avec un bloc mémoire contenant une adresse mémoire égal à celle passée en paramètre ou NULL.
 */
Liste rechercheBlocMemoire(Liste liste, void* p);

int tailleListe(Liste liste);

Liste rechercheParIndice(Liste liste, int i);