typedef struct{
	void* adresse;
	int nbBytes;
}BlocMemoire;

typedef struct cellule{
	BlocMemoire blocMemoire;
	struct cellule *suivant;
}*Liste;

Liste initListe();
Liste inserTete(Liste liste, int nbBytes, void* adresseMemoire);
Liste suppTete(Liste liste);
void suppListe(Liste liste, Liste listeAsupp);
Liste rechercheElement(Liste liste, int element);
