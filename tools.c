//
//  tools.c
//  projet7
//
//  Created by remy DEME on 25/03/2016.
//  Copyright © 2016 remy DEME. All rights reserved.
//

#include "tools.h"

          // _________________________________PHASE 1 _______________________________//
           //____________________________________________________________________//
void viderBuff ( )
{
          int c ; 
          while ((c = getchar())!='\n')
                {
                    
                }
}


void affiche_header ( infoBMP*infoEntete )
{
          AFFICHE_VALEUR("largeur : ",( infoEntete->largeur)); 
          AFFICHE_VALEUR("hauteur : ", (infoEntete->hauteur)); 
          AFFICHE_VALEUR("Nombre de pixel :", infoEntete->tailleTot); 
          AFFICHE_VALEUR("Offset : ", infoEntete->offsetDecalage); 
          AFFICHE_VALEUR("Profondeur de codage : ", infoEntete->profCodage); 
}

          /* fonctions  qui permettront l'enregistrement des points idéaux pour un certain k  nombre de clusters */


char * center_name ( const int nombre_centre , char * name  )
{
          if ( name )// test de pointeur 
                {
                    char *chiffre = convert_int_to_char(nombre_centre); 
                    strcat(name, chiffre); 
                    strcat(name, ".txt"); 
                }
          else 
                {
                    assert(name != NULL ); 
                    exit(EXIT_FAILURE); 
                }
          return name ; 
}


char * convert_int_to_char ( const int valeur )
{
          char *chiffre = calloc(4, sizeof(char)); 
          int centaine ; 
          int dizaine ; 
          int unite ; 
          if (chiffre )
                {
                    centaine = valeur/ 100 ; // détermine le nombre de centaine 
                    dizaine = (valeur%100)/10;// le nombre de dizaine 
                    unite = valeur - centaine*100 - dizaine * 10 ; // le nombre d'unité 
                    change_to_char(&chiffre[0],&chiffre[1],&chiffre[2], centaine, dizaine, unite); 
                    chiffre[3] = '\0'; // ajoute le charactère NULL  à la fin du 
                }
          else
                {
                    perror("bad allocation"); 
                    printf ( " Ligne : %d ",__LINE__); 
                    printf ( " fichier : %s ",__FILE__); 
                    chiffre = NULL ;
                }
          
          return chiffre; 
}

void change_to_char ( char *centaine , char *dizaine , char *unite  ,const int centaine_int , const int dizaine_int, const int unite_int  )
{
          *centaine = 48+centaine_int;// 0 + la valeur de centaine ==> valeur ASCCI du nombre 
          *dizaine = 48 + dizaine_int; 
          *unite = 48 + unite_int; 
}


int temp_exec ( const float new_temps_exec , const int nombre_couleur )
{
          FILE * file = NULL ;
          float temps_exec = 0.0 ; 
          char chemin_absolue_temp[TAILLE_BUFF] = CHEMIN_FICHIER_TEMPS_EXEC ;    
          center_name(nombre_couleur,chemin_absolue_temp);  // fonction qui permet crée le nom du fichier // 
          file = fopen(chemin_absolue_temp, "r+");
          if ( errno == ENOENT )// si le fichier n'existe pas 
            {
                printf ( " Fichier inexistant ERRNO : %d \n \n => Création du fichier et sauvegarde des données . \n ",errno);
                file = fopen(chemin_absolue_temp, "w+") ;
                if (file)
                      {
                           fprintf (file,"%f",new_temps_exec); 
                      }
                else 
                      {
                          assert(file != NULL ); 
                      }
                temps_exec = INT_MAX ; // Afin d'etre sur de quitter le fichié // 
          }
          else if (file)// sinon 
                {
                    fscanf (file ,"%f",&temps_exec); 
                    if ( temps_exec > new_temps_exec )/*on compare le temps obtenu avec celui stocké dans le fichier */
                          {
                              fseek(file,0, SEEK_SET); // si le temps 
                              fprintf (file,"%f",new_temps_exec); 
                          }
                }
          else // si l'ouverture échoue 
                {
                    assert(file !=NULL) ; /* si le pointeur sur fichier est NULL => arrêt du code et affichage de l'erreur */
                }
          fclose(file); 
          return temps_exec > new_temps_exec ; 
}




/* fonction qui  permet d'initialiser des pointeur de types centre avec des addresse mémoires alloué dynamiquement */

void initialiser_centre_memoir ( const int nombre_de_cluster , centre_PNS *centres )
{
          if ( centres )
                {
                    centres->centre_n = calloc(nombre_de_cluster, sizeof(centre));
                    centres->centre_p = calloc(nombre_de_cluster, sizeof(centre)); 
                    centres->centre_s = calloc(nombre_de_cluster, sizeof(centre)); 
                    assert((centres->centre_n && centres->centre_p && centres->centre_s) != 0 ); 
                }
          else
                {
                    assert(centres != NULL ); 
                }
}

void initialiser_centre_memoir_NG ( const int nombre_de_cluster , centre_PNS_NG *centres )
{
          if ( centres )
                {
                    centres->centre_n = calloc(nombre_de_cluster, sizeof(centre));
                    centres->centre_p = calloc(nombre_de_cluster, sizeof(centre)); 
                    centres->centre_s = calloc(nombre_de_cluster, sizeof(centre)); 
                    assert((centres->centre_n && centres->centre_p && centres->centre_s) != 0 ); 
                }
          else
                {
                    assert(centres != NULL ); 
                }
}

void save_center ( const int nombre_cluster , centre * c  , const float temps_exec )
{
          int i ; 
          int save = 0 ; 
          char chemin_absolue_centre[TAILLE_BUFF] = CHEMIN_CENTRE ; 
          center_name(nombre_cluster, chemin_absolue_centre); // fonction qui permet l'ecriture du nom du ficier // 
          FILE * fichier_coord_centre = NULL ; 
          save = temp_exec(temps_exec, nombre_cluster); 
          if (save)
                {
                    fichier_coord_centre = fopen(chemin_absolue_centre, "w+");
                    if ( fichier_coord_centre)
                          {
                              for ( i = 0 ; i < nombre_cluster ; i++ )
                                    {
                                        fprintf (fichier_coord_centre,  "%d %d %d %d %d %c",c[i].x,c[i].y,c[i].r,c[i].v,c[i].b,'\n'); 
                                    }
                          }
                    else 
                          {
                              assert(fichier_coord_centre != NULL); 
                          }
                    }
          else 
                {
                    printf( "\n Le temps d'exécution était supérieur au record . Les points n'ont pas été sauvegardés .\n ");
                }
          fclose(fichier_coord_centre);
}



int * alloc_memoir ( const int size )
{
          int * temp = NULL ; 
          if ( size > 0)
                {
                   temp =  calloc(size, sizeof(int));
                    if ( !temp )
                          {
                              assert( temp == NULL ) ;    
                          }
                }
          else 
                {
                    assert(size > 0); 
                }
          return temp ; 
}


pix **allocation_tableau (const infoBMP*infoEntete  )
{
          pix**ptrTab = NULL ; 
          int i ; 
          ptrTab = calloc(infoEntete->hauteur, sizeof(pix*)); 
          if ( ptrTab)
                {
                    for ( i = 0 ; i < infoEntete->hauteur ; i++ ) ptrTab[i] = calloc( infoEntete->largeur , sizeof(pix)) ; 
                    for ( i = 0 ; i < infoEntete->hauteur ; i++ )
                          {
                              if ( !ptrTab[i]){ assert(ptrTab[i] != NULL); }
                          }               
                }
          else 
                {
                    assert( ptrTab != NULL );
                }
          return ptrTab ; 
}

int initialiser_centre_s ( const int nombre_cluster , centre * c  )
{
          int i ;
          int existe = 0 ; 
          char *chemin_fichier_centre = NULL  ; 
          char *chemin_fichier = NULL ;
          chemin_fichier = calloc(TAILLE_BUFF, sizeof(char)); 
          memmove(chemin_fichier,CHEMIN_CENTRE, strlen(CHEMIN_CENTRE));
          FILE * fichier_coord_centre = NULL ; 
          chemin_fichier_centre = center_name(nombre_cluster, chemin_fichier); 
          fichier_coord_centre = fopen(chemin_fichier, "r"); 
          if ( errno != ENOENT)
                {
                    if ( fichier_coord_centre && chemin_fichier_centre)
                          {
                              for ( i = 0 ;  i < nombre_cluster ; i++  )
                                    {
                                        (void)fscanf(fichier_coord_centre,  "%d %d %d %d %d \n",&c[i].x,&c[i].y,&c[i].r,&c[i].v,&c[i].b);
                                    }
                          }
                    else 
                          {
                              assert(fichier_coord_centre != NULL );
                              assert(chemin_fichier_centre != NULL); 
                          }
                    fclose(fichier_coord_centre); 

                }
          else 
                {
                    existe = ENOENT ; 
                }
          return existe; 
}

void free_memory( sommes * sigma  )
{
          free(sigma->moyenne_b); 
          free(sigma->moyenne_r); 
          free(sigma->moyenne_v); 
           free(sigma->moyenne_x);
           free(sigma->moyenne_y);
          free(sigma->somme_b); 
          free(sigma->somme_r); 
          free(sigma->somme_v); 
          free(sigma->somme_x); 
          free(sigma->somme_y); 
          sigma->moyenne_r = NULL ; 
          sigma->moyenne_b = NULL ; 
          sigma->moyenne_v = NULL ; 
          sigma->moyenne_x = NULL ; 
          sigma->moyenne_y = NULL ; 
          sigma->somme_b    = NULL ; 
          sigma->somme_r    = NULL;
          sigma->somme_v    = NULL; 
          sigma->somme_x = NULL ; 
          sigma->somme_y = NULL ; 
}


void free_memory_NG( sommes_NG * sigma  )
{
          free(sigma->moyenne_g); 
          free(sigma->moyenne_x);
          free(sigma->somme_x); 
          free(sigma->somme_y); 
          free(sigma->moyenne_y);
          sigma->moyenne_x = NULL ; 
          sigma->moyenne_y = NULL ; 
          sigma->somme_x = NULL ; 
          sigma->somme_y = NULL ; 
          sigma->moyenne_g = NULL ; 
          sigma->somme_g = NULL ; 
}



int means_matrice ( const  infoBMP * infoEntete , const unsigned char  ** matrice )
{
          int i , j ; 
          int  moyenne = 0 ; 
          const int taille = infoEntete->largeur * infoEntete->hauteur ; 
          for ( i = 0 ; i <  infoEntete->hauteur ; i++  )
                {
                    for ( j = 0 ; j < infoEntete->largeur  ; j++ )
                          {
                              moyenne += matrice[i][j] ;  
                          }
                }
          moyenne =(double)moyenne / taille ; 
          return moyenne ; 
}


int new_x (  const int means , const unsigned char valeur_pix , const int ecart_type_1 , const int ecart_type_2  )
{
          const double facteur_1 = 1.0 / (float)ecart_type_1*(sqrtf(2*M_PI)) ; 
          const double  facteur_2 = 1.0 / ecart_type_2*(sqrtf(2*M_PI)) ; 
          const double A = -((pow((double)(valeur_pix-means),2)  ) / (  2*pow((float)ecart_type_1, 2) ) ); 
          const double  B =  -((pow((double)(valeur_pix-means),2)  ) / (  2*pow((float)ecart_type_2, 2) ) ) ; 
          const int valeur =  (facteur_1 * exp((double)A)) -  (facteur_2 * exp((double)B));
          return  valeur ; 
}





