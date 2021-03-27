typedef struct{
	void* adresse;
	int nbBytes;
}BlocMemoire;

typedef struct cellule{
	BlocMemoire blocMemoire;
	struct cellule *suivant;
}*Liste;