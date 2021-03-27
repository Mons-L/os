Liste initListe();
Liste inserTete(Liste liste, int nbBytes, void* adresseMemoire);
Liste suppTete(Liste liste);
void suppListe(Liste liste, Liste listeAsupp);
Liste rechercheElement(Liste liste, int element);
Liste rechercheBlocMemoire(Liste liste, void* p);