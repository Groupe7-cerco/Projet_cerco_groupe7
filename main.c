#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Parc.h"

int main()
{


    Voiture *voitures=NULL;
    int nbVoitures=0,c=0,cmpt=0,i;
    float kilom=0;
    char newline;
    char matricule[TAILLE_TABLEAU]="",nomFichier[TAILLE_TABLEAU]="";
    printf("\n\n");
    //............................................................................
    printf("\t\tPACKING GESTION: CERCO IA/2019 GROUPE7.\n\n");
    b:printf("ENTRER LE NOMBRE DE VOITURE QUE VOUS DESIREZ CREER DANS VOTRE PARC: ");
    burg(&nbVoitures);
    if(nbVoitures==0)//EMPECHER QUE LE NOMBRE DE VOITURE SOIT INFERIEUR A ZERO OU NUL
    {
        printf("VALEUR INVALIDE. CREER AU MOINS UNE (1) VOITURE...\n\n");
        goto b;
    }//FIN DE LA PARTIE: EMPECHER LE NOMBRE DE VOITURE NEGATIF OU NUL
    printf("\n");
    voitures=malloc(sizeof(Voiture)*nbVoitures);//ALLOCATION DYNAMIQUE DE N ESPACE DANS LA MEMOIRE
    if(voitures==NULL)
    {
        printf("ALLOCATION DE MEMOIRE ECHOUEE!\n");
        exit(1);
    }
    kilom=init(voitures,&nbVoitures);//APPEL DE LA FONCTION POUR CREER LE PARC DES N VOITURES
    printf("\n\n");
    //..............................................................................

    a:printf("-----------MENU--------------\n\n");
    printf(" 1:LOUER UNE VOITURE\n\n 2:RETOUR D'UNE VOITURE\n\n 3:ETAT D'UNE VOITURE\n\n 4:ETAT DU PARC DE VOITURES\n\n 5:SAUVEGARDER L'ETAT DU PARC\n\n 0:FIN DU PROGRAMME\n");
    burg(&c);
    if(c!=1 && c!=2 && c!=3 && c!=4 && c!=5 && c!=0)//OBLIGER L'UTILISATEUR A CHOISIR LES VALEURS INDIQUEES POUR LE MENU
    {
        printf("\n SAISIE INCOMPATIBLE, VEUILLEZ RESSAYER VOTRE CHOIX\n\n");
        goto a;
    }
    switch(c)
    {
    case 1:
        for(i=0;i<nbVoitures;i++)
        {
            if((voitures+i)->etatDispo==1)
            {
                printf("VOITURE DISPONIBLE: %s\n",(voitures+i)->numImatricule);
                cmpt++;
            }
        }
        if(cmpt==0)
        {
            printf(" (0) VOITURE DISPONIBLE ACTUELLEMENT, VEUILLEZ REESSAYEZ PLUS TARD\n\n");
            goto a;
        }
        cmpt=0;
        printf("ENTRER LE NUMERO D'IMMATRICULATION D'UNE VOITURE DISPONIBLE DE VOTRE CHOIX: ");
        fgets(matricule,TAILLE_TABLEAU,stdin);
        louer(matricule,voitures,nbVoitures);//APPEL DE FONCTION POUR LOUER UNE VOITURE
        goto a;
        break;
    case 2:
        for(i=0;i<nbVoitures;i++)
        {
            if((voitures+i)->etatDispo==2)
            {
                printf("EN LOCATION: %s\n",(voitures+i)->numImatricule);
                cmpt++;
            }
        }
        if(cmpt==0)
        {
            printf(" (0) VOITURE EN COURS DE LOCATION ACTUELLEMENT, VEUILLEZ CHOISIR UNE AUTRE OPTION\n\n");
            goto a;
        }
        cmpt=0;
        printf("ENTRER LE NUMERO D'IMMATRICULATION CORRESPONDANT A LA VOITURE QUE VOUS RETOURNEZ: ");
        fgets(matricule,TAILLE_TABLEAU,stdin);
        retour(matricule,voitures,nbVoitures,&kilom);//APPEL DE FONCTION POUR RETOURNER UNE VOITURE
        goto a;
        break;
    case 3:
        printf("IMMATRICULATION(S):\n");
        for(i=0;i<nbVoitures;i++)
        {
            printf("%s",(voitures+i)->numImatricule);
        }
        printf("ENTRER LE NUMERO D'IMMATRICULATION DE LA VOITURE DONT VOUS VOULEZ CONNAITRE L'ETAT: ");
        fgets(matricule,TAILLE_TABLEAU,stdin);
        etat(matricule,voitures,nbVoitures);//APPEL DE FONCTION POUR AFFICHER L'ETAT D'UNE VOITURE
        goto a;
        break;
    case 4:
        etatParc(voitures,nbVoitures,kilom);//APPEL DE FONCTION POUR AFFICHER L'ETAT GLOBAL DU PARC
        goto a;
        break;
    case 5:
        printf("ENTRER JUSTE LE NOM DE VOTRE FICHIER: ");
       scanf("%s",nomFichier);
       strcat(nomFichier,".txt");
       save(nomFichier,voitures,nbVoitures,kilom);//APPEL DE FONCTION POUR SAUVEGARDER L'ETAT GLOBAL DU PARC DANS UN FICHIER
      scanf("%c",&newline);
       goto a;
       break;
        default:
            printf("\nPROGRAMME FERME AVEC SUCCES.\n\n\n");
            printf("\t\tPACKING GESTION: CERCO IA/2019 GROUPE7.\n\n");
            free(voitures);//LIBERATION DE LA MEMOIRE
            exit(1);
        break;
    }

    return 0;
}

