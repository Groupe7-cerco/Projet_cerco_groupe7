#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Parc.h"

float init(Voiture *voiture,int *n)
{
    float kilo=0;
    int verImat=0,i=0,j=0,ajout=0,nbAjouter=0,v=1;

      printf("\n...........................................................\n");
      printf("\t\tVOITURE NUMERO %d\n",i+1);
      printf("\n");
      printf("ENTRER SON MODEL: ");
      fgets((voiture+i)->modele,TAILLE_TABLEAU,stdin);
      printf("\n");
      printf("ENTRER SON NUMERO D'IMMATRICULATION: ");
      fgets((voiture+i)->numImatricule,TAILLE_TABLEAU,stdin);
      printf("\n");
      printf("ENTRER SON KILOMETRAGE: ");
      burgkilom(&(voiture+i)->kilometrage);// APPEL DE LA FONCTION POUR EMPECHER QUE L'UTILISATEUR TAPE DES VALEURS NON PRISES EN CHARGE LORS DE LA SAISIE
      kilo=(voiture+i)->kilometrage;//CONSERVE LA PREMIERE VALEUR DU KILOMETRAGE POUR COMPARER PLUS TARD DANS LA BOUCLE
      a:printf("ENTRER SON ETAT \n");
      printf("1:DISPONIBLE\n2:EN COURS DE LOCATION\n\n");
      burg(&(voiture+i)->etatDispo);// APPEL DE LA FONCTION POUR EMPECHER QUE L'UTILISATEUR TAPE DES VALEURS NON PRISE EN CHARGE LORS DE LA SAISIE
      if((voiture+i)->etatDispo!=1 && (voiture+i)->etatDispo!=2)//IMPOSER LA VALEUR 1 OU 2 POUR LE CHOIX DE L'ETAT DE DISPONIBILITE D'UNE VOITURE A LA CREATION
      {
          printf("SAISIE INCOMPATIBLE...\n\n");
          goto a;
      }
      printf("...........................................................\n");
  f:for(i=v;i<*n;i++)//BOUCLE POUR CREER DES VOITURES ET FAIRE SUCCESSIVEMENT LA COMPARAISON ENTRE LES KILOMETRAGES SAISIES AU CLAVIER
  {
      printf("\t\tVOITURE NUMERO %d\n",i+1);
      printf("\n");
      printf("ENTRER SON MODEL: ");
      fgets((voiture+i)->modele,TAILLE_TABLEAU,stdin);
      printf("\n");
      printf("ENTRER SON NUMERO D'IMMATRICULATION: ");
      fgets((voiture+i)->numImatricule,TAILLE_TABLEAU,stdin);
      for(j=0;j<i;j++)//VERIFICATION POUR EMPECHER DEUX VOITURES D'AVOIR LE MEME NUMERO IMMATRICULE
      {
          verImat=strcmp((voiture+i)->numImatricule,(voiture+j)->numImatricule);//COMPARAISON DE TOUS LES NUMERO MATRICULE DEJA SASIE
          if(verImat==0)
          {
              printf("\nLA VOITURE NUMERO %d PORTE DEJA LE NUMERO D'IMMATRICULATION %s\n\n",j+1,(voiture+i)->numImatricule);
              strcpy((voiture+i)->numImatricule,"");
              printf("ENTRER UN NOUVEAU NUMERO D'IMMATRICULATION: ");
              fgets((voiture+i)->numImatricule,TAILLE_TABLEAU,stdin);
              printf("\n");
              j=-1;//PERMET DE RAMENER LA VALEUR DE j A ZERO A LA FIN DE LA STRUCTURE IF POUR RECOMMENCER LA VERIFICATION DU DEBUT AVEC LE NOUVEAU NUMERO IMMATRICULE CHOISIR PAR L'UTILISATEUR
          }
      }//FIN DE LA VERIFICATION IMMATRICULE
      printf("\n");
      printf("ENTRER SON KILOMETRAGE: ");
      burgkilom(&(voiture+i)->kilometrage);
      if((voiture+i)->kilometrage<kilo)//STOCKAGE DE LA PETITE VALEUR DE KILOMETRAGE ENTRER PAR L'UTILISATEUR
       {
           kilo=0;
           kilo=(voiture+i)->kilometrage;
       }//FIN DE STOCKAGE
      b:printf("ENTRER SON ETAT \n");
      printf("1:DISPONIBLE\n2:EN COURS DE LOCATION\n\n");
      burg(&(voiture+i)->etatDispo);
      if((voiture+i)->etatDispo!=1 && (voiture+i)->etatDispo!=2)//IMPOSER LE CHOIX 1 OU 2 A L'UTILISATEUR POUR L'ETAT DE LOCATION DE LA VOITURE A LA CREATION
      {
          printf("SAISIE INCOMPATIBLE...\n\n");
          goto b;
      }//FIN DE LA PARTIE: ETAT DE LOCATION D'UNE VOITURE A SA CREATION
      printf("...........................................................\n");
  }
      printf("\n\t\tPACKING GESTION: CERCO IA/2019\n\n"); // CETTE PARTIE DU CODE PERMET UNE REALLCATION DE MEMOIRE QUAND L'UTILISATEUR AURAIT OUBLIE DES VOITURES
      e:printf("1-AJOUTER ENCORE DE VOITURES A LA COLLECTION   2-FERMER LE PACKING DE COLLECTION: ");
      burg(&ajout);
      if(ajout!=1 && ajout!=2)
      {
          printf("SAISIE INCOMPATIBLE...\n\n");
          goto e;
      }
      switch(ajout)
      {
      case 1:
        printf("ENTRER LE NOMBRE DE VOITURE QUE VOUS VOULEZ AJOUTER A LA COLLECTION: ");
        burg(&nbAjouter);
        printf("\n");
        voiture=realloc(voiture,nbAjouter*sizeof(Voiture));
        v=*n;
        *n+=nbAjouter;
        printf("...........................................................\n");
        goto f;
        break;
        default:
        printf("PARCKING DE COLLECTION FERME AVEC SUCCES.");//FIN DE LA PARTIE DE REALLOCATION
      }
    return kilo;//RETOUR DE LA PLUS PETITE VALEUR DE KILOMETRAGE ENTRER PAR L'UTILISATEUR A LA FONCTION main
}

int louer(char *matricule, Voiture *voitures, int n)
{
    int verif=0;
    for(int i=0;i<n;i++)
    {
        verif=strcmp(matricule,(voitures+i)->numImatricule);//COMPARAISON DU NUMERO IMMATRICULE AVEC CEUX QUI EXISTENT
        if(verif==0 && (voitures+i)->etatDispo==1)//SI VOITURE EXISTE ET DISPONIBLE
        {
            printf("\nLOCATION DE LA VOITURE EFFECTUEE AVEC SUCCES\n\n");
            (voitures+i)->etatDispo=2;
            return 0;
        }
        else if(verif==0 && (voitures+i)->etatDispo==2)//SI VOITURE EXISTE ET INDISPONIBLE
        {
            printf("\nCETTE VOITURE EST EN LOCATION, VEUILLEZ CONSULTER LA LISTE DES VOITURES DISPONIBLE CI-DESSUS ET REESSAYER.\n\n");
            return 0;
        }
    }
    printf("\nVOITURE INTROUVABLE! VERIFIEZ ET REESSAYEZ.\n\n");
    return 0;
}

int retour(char *matricule, Voiture *voitures,int n,float *kilom)
{
    int verif=0;
    float kilo=0;
    for(int i=0;i<n;i++)
    {
        verif=strcmp(matricule,(voitures+i)->numImatricule);
        if(verif==0 && (voitures+i)->etatDispo==2)//SI VOITURE EXISTE ET INDISPONIBLE
        {
            printf("\nENTRER LE NOMBRE DE KILOMETRES EFFECTUES AVEC LA VOITURE: ");
            burgkilom(&kilo);
            (voitures+i)->kilometrage+=kilo;//AJOUT DE KILOMETRAGE
            *kilom=(voitures+i)->kilometrage;//REMPLACE LA PLUS PETITE VALEUR DE KILOMETRAGE PAR CETTE NOUVELLE VALEUR POUR FAIRE LA COMPARAISON PLUS TARD
            (voitures+i)->etatDispo=1;//RENDRE LA VOITURE DISPONIBLE
            for(int j=0;j<n;j++)//PERMET DE REDEFINIR LA PLUS PETITE VALEUR DE KILOMETRAGE PAR ADRESSE CAR APRES AVOIR RETOUNER UNE VOITURE, LE KILOMETRAGE CHANGE
            {
                if((voitures+j)->kilometrage<*kilom)
                {
                    *kilom=(voitures+j)->kilometrage;
                }
            }
            printf("VOITURE RETOUNEE AVEC SUCCES.\n\n");
            return 0;
        }
        else if(verif==0 && (voitures+i)->etatDispo==1)//SI VOITURE EXISTE ET DISPONIBLE
        {
            printf("\nCETTE VOITURE N'EST PAS LOUEE, VEUILLEZ CONSULTER LA LISTE DES VOITURES EN LOCATION CI-DESSUS ET REESSAYEZ.\n\n");
            return 0;
        }
    }
    printf("\nVOITURE INTROUVABLE! VERIFIER ET REESSAYEZ\n\n");
   return 0;
}

int etat(char *matricule, Voiture *voitures,int n)
{
    int verif=0;
    for(int i=0;i<n;i++)
    {
        verif=strcmp(matricule,(voitures+i)->numImatricule);
        if(verif==0 && (voitures+i)->etatDispo==1)//VOITURE EXISTE ET DISPONIBLE
        {
            printf("\n*************************************************\n");
            printf("\n NUMERO D'IMMATRICULATION: %s \n",(voitures+i)->numImatricule);
            printf("\n ETAT DE LOCATION: DISPONIBLE\n");
            printf("\n KILOMETRAGE: %f Km\n",(voitures+i)->kilometrage);
            printf("\n MODELE: %s\n",(voitures+i)->modele);
            printf("\n*************************************************\n");
            return 0;
        }
        else if(verif==0 && (voitures+i)->etatDispo==2)//VOITURE EXISTE ET INDISPONIBLE
        {
            printf("\n*************************************************\n");
            printf("\n NUMERO D'IMMATRICULATION: %s \n",(voitures+i)->numImatricule);
            printf("\n ETAT DE LOCATION: EN COURS DE LOCATION\n");
            printf("\n KILOMETRAGE: %f Km\n",(voitures+i)->kilometrage);
            printf("\n MODELE: %s\n",(voitures+i)->modele);
            printf("\n*************************************************\n");
            return 0;
        }
    }
    printf("\nVOITURE INTROUVABLE! VERIFIER ET REESSAYEZ.\n\n");
    return 0;
}

void etatParc(Voiture *voitures, int n,float kiloMetre)
{
    int i=0,cmpt1=0,cmpt2=0;
   printf("\t\tETAT RESUME DU PARC\n");
   printf("\n********************************************************\n");
   printf("IL Y A AU TOTAL %d VOITURE(S) DANS NOTRE PARC \n\n",n);
    for(i=0;i<n;i++)//STOCKAGE DU NOMBRE DE VOITURE DISPONIBLE ET AFFICHAGE DE LEUR NUMERO IMMATRICULE
    {
        if((voitures+i)->etatDispo==1)
        {
          printf("DISPONIBLE: %s",(voitures+i)->numImatricule);
          cmpt1++;
        }
    }
  printf("IL Y A AU TOTAL %d VOITURE(S) DISPONIBLE \n\n",cmpt1);
    for(i=0;i<n;i++)
    {
        if((voitures+i)->etatDispo==2)//STOCKAGE DU NOMBRE DE VOITURE INDISPONIBLE ET AFFICHAGE DE LEUR NUMERO IMMATRICULE
        {
          printf("EN COURS DE LOCATION: %s",(voitures+i)->numImatricule);
          cmpt2++;
        }
    }
    printf("IL Y A AU TOTAL %d VOITURE(S) EN COURS DE LOCATION \n\n",cmpt2);
    printf("KILOMETRAGE MOYEN DE L'ENSEMBLE DES VOITURES: %f Km\n",kiloMetre);//AFFICHAGE DE LA PLUS PETITE VALEUR DE KILOMETRAGE FOUNIR PAR LA FONCTION init
    printf("\n********************************************************\n");
}

void save(char *fichier, Voiture *voitures, int n,float kiloMetre)
{
    int i=0,cmpt1=0,cmpt2=0;
    FILE *fic=fopen(fichier,"wb");//CREATION DU FICHIER EN MODE BINAIRE ECRITURE SEUL
    if(fic==NULL)//VERIFICATION DE LA CREATION DU FICHIER
       {
           printf("\nCREATION DE FICHIER ECHOUEE!!, ERREUR FATALE\n");
           free(voitures);
           exit(1);
       }
   fprintf(fic,"%s%d%c  ","NOMBRE TOTAL DE VOITURES DANS LE PARC: \n",n,'.');//ECRITURE DANS LE FICHIER AVEC LA FONCTION FPRINTF
    for(i=0;i<n;i++)
    {
        if((voitures+i)->etatDispo==1)
        {
            fputs("",fic);//SERT A METTRE DE L'ESPACE ENTRE LES ECRITS DANS LE FICHIER
           fprintf(fic,"%s %s %s  ","IMMATRICULEE ",(voitures+i)->numImatricule,"DISPONIBLE.\n");
          cmpt1++;//STOCKAGE POUR CONNAITRE LE NOMBRE DE VOITURE INDISPONIBLE
        }
    }
    fprintf(fic,"%s %d %s  ","IL Y A AU TOTAL",cmpt1,"VOITURE(S) DISPONIBLE.\n");
    for(i=0;i<n;i++)
    {
        if((voitures+i)->etatDispo==2)
        {
          fputs("",fic);
          fprintf(fic,"%s %s %s  ","IMMATRICULEE ",(voitures+i)->numImatricule,"EN LOCATION.\n");
          cmpt2++;
        }
    }
    fprintf(fic,"%s %d %s  ","IL Y A AU TOTAL",cmpt2,"VOITURE(S) EN COURS DE LOCATION.\n");
    fputs("",fic);
    fprintf(fic,"%s %f %s  ","KILOMETRAGE MOYEN DE L'ENSEMBLE DES VOITURES: ",kiloMetre," Km.");
    printf("\nSTOCKAGE DE L'ETAT DU PARC EFFECTUE AVEC SUCCES.. RETROUVEZ CE FICHIER DANS VOTRE DOSSIER 'Parc'\n\n");
    fclose(fic);//FERMETURE DU FICHIER
}
void burg(int *l)
{
    char chaine[TAILLE_TABLEAU]="";
    int lon=0,i=0,n=0;
    fgets(chaine,TAILLE_TABLEAU,stdin);
    printf("\n");
    n=strlen(chaine);
    for(i=0;i<n-1;i++)
    {
      lon=isdigit(chaine[i]);// STOCKAGE DU RETOUR DE LA FONCTION ISDIGIT, ISDIGIT VERIFIE SI UN CARACTERE EST UN CHIFFRE(DE 0 A 9)
      if(lon==0)
      {
          printf("ERREUR, ENTRER UNE VALEUR VALIDE: ");
          fgets(chaine,TAILLE_TABLEAU,stdin);
          printf("\n");
          n=strlen(chaine);
          i=-1;
      }
    }
   *l=atoi(chaine);// CONVERSION DE LA CHAINE DE CARACTERE EN ENTIER.
}
void burgkilom(float *l)
{
    float verifi;
    char chaine[TAILLE_TABLEAU];
    int lon=0,cmpt=0,i=0;
    fgets(chaine,TAILLE_TABLEAU,stdin);
    printf("\n");
    lon=strlen(chaine);
    f:for(i=0;i<lon-1;i++)
    {
        if(isdigit(chaine[i])==0 && chaine[i]!= '.')
        {
            printf("ERREUR, ENTRER UNE VALEUR VALIDE: ");
            fgets(chaine,TAILLE_TABLEAU,stdin);
            lon=strlen(chaine);
            printf("\n");
            i=-1;
        }
    }
    for(i=0;i<lon;i++)
    {
        if(chaine[i]=='.')
            cmpt++;
    }
    if(cmpt>1)
    {
        s:printf("ERREUR, ENTRER UNE VALEUR VALIDE: ");
        fgets(chaine,TAILLE_TABLEAU,stdin);
        lon=strlen(chaine);
        printf("\n");
        cmpt=0;
        goto f;
    }
    verifi=strtod(chaine,NULL);// CONVERSION DE LA CHAINE DE CHARACTERE EN DOUBLE.
    if(verifi<0 || verifi>150000)
        goto s;
    *l=verifi;
}
