#ifndef PARC_H_INCLUDED
#define PARC_H_INCLUDED
#define TAILLE_TABLEAU 250
typedef struct Voiture
{
   char modele[TAILLE_TABLEAU];
   char numImatricule[TAILLE_TABLEAU];
   float kilometrage;
   int etatDispo;
}Voiture;

float init(Voiture *voiture,int *n);
int louer(char *matricule, Voiture *voitures, int n);
int retour(char *matricule, Voiture *voitures,int n,float *kilom);
int etat(char *matricule, Voiture *voitures,int n);
void etatParc(Voiture *voitures, int n,float kiloMetre);
void save(char *fichier, Voiture *voitures, int n,float kiloMetre);
void burgkilom(float *l);// FONCTION QUI PERMET D'EVITER LE BURG DU PROGRAMME LORS DE LA SAISIE D'UN FLOAT
void burg(int *l);// FONCTION QUI PERMET D'EVITER LE BURG DU PROGRAMME LORS DE LA SAISIE D'UN ENTIER

#endif // PARC_H_INCLUDED
