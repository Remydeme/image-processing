//
//  matrice2DNB.c
//  projet7
//
//  Created by remy DEME on 25/03/2016.
//  Copyright © 2016 DEME Rémy. All rights reserved.
//

#include "matrice2DNB.h"


infoBMP* read_header2D_NB ( const char file_name[] )
{
          if ( file_name)
                {
                    char cheminAbsolue[CHEMIN_ABSOLUE] = "/Users/remydeme/Documents/programmes/projet7/projet7/database/"; 
                    strcat(cheminAbsolue, file_name);// complete chemin absolue 
                    infoBMP *ptrEntete = calloc(1, sizeof(infoBMP) ); // définie une var pour enregistrer l'entete 
                    
                    FILE * ptrFile = fopen(cheminAbsolue, "rb"); // ouverture du flot 
                    if ( ptrFile && ptrEntete)// test ptr
                          {
                              fread(ptrEntete,sizeof(infoBMP), 1, ptrFile); // lecture du flot 
                          }
                    else perror("Message "); // Message d'erreur 
                    fclose(ptrFile); // fermeture du flot 
                    return ptrEntete ; // return l'addresse de l'entete 
                }
          else 
                {
                    perror("MESSAGE : "); 
                    exit( EXIT_FAILURE); 
                }
}


unsigned char  **builtTab2D_NB ( const infoBMP * infoEntete, const char fileName[] )
{         
          if ( infoEntete && fileName)// test pointeurs
                {
                    int i ; 
                    unsigned char  ** ptrTab = calloc( infoEntete->largeur , sizeof(char*));
                    char cheminAbsolue[CHEMIN_ABSOLUE] = "/Users/remydeme/Documents/programmes/projet7/projet7/database/"; 
                    size_t NombrePixelleLigne =  (infoEntete->largeur)*(infoEntete->profCodage) ; 
                    strcat(cheminAbsolue, fileName); // complète le chemin absolue 
                    FILE * ptrFile = fopen(cheminAbsolue, "rb"); 
                    for ( i = 0 ; i < infoEntete->hauteur ; i++ )
                          {
                              ptrTab[i] = calloc(NombrePixelleLigne, sizeof( unsigned char)); 
                          }
                    if ( ptrFile)
                          {
                              fseek(ptrFile, infoEntete->offsetDecalage, SEEK_SET);
                              for ( i = 0 ; i < infoEntete->hauteur ; i++)// remplie notre matrice à partir du flot 
                                    {
                                        fread(ptrTab[i],PIXEL_NB,infoEntete->largeur, ptrFile) ;
                                    }
                              fclose(ptrFile); 
                          }
                    else perror("MESSAGE : "); // affiche message d'erreur 
                    
                    
                    return ptrTab; 
                }
          else 
                {
                    printf ( " Pointeur sur cahine ou structure NULL \n");
                    exit(EXIT_FAILURE);
                }
          
}

          // fonctions qui recopie l'image une fois modifié dans un fichier // 
void restore_picture_retouch2D_NB ( unsigned char **ptrTab , const char fileName[] ,const infoBMP *infoEntete )
{
          if ( ptrTab && fileName)// test la nullité des pointeurs 
                {
                    int i ;
                    unsigned char * src = calloc(infoEntete->offsetDecalage, sizeof(char));  
                    char cheminAbsolue[CHEMIN_ABSOLUE] = "/Users/remydeme/Documents/programmes/projet7/projet7/database/"; 
                              // strcat(cheminAbsolue, fileName);// complète le chemin absolue
                    FILE * file_lena = fopen("/Users/remydeme/Documents/programmes/projet7/projet7/database/lena_NB.bmp", "rb");
                    FILE* file = fopen(fileName, "wb+"); 
                    if ( file && file_lena)
                          {
                              fread(src, 1, infoEntete->offsetDecalage, file_lena); 
                              fwrite(src ,infoEntete->offsetDecalage,1, file); // copie d'abord l'entete du fichier 
                                                                               // fwrite(file_lena, 1, portionImagTaille, file);
                              for ( i = 0 ; i < infoEntete->hauteur ; i++ )
                                        fwrite(ptrTab[i],1,infoEntete->largeur,file); 
                              
                          }
                    fclose(file); fclose(file_lena);  
                }
          else 
                {
                    printf ( " Pointeur de tableau ou de nom de fichier NULL. \n  "); 
                    exit(EXIT_FAILURE);
                }
}



unsigned char ** retouchIM2D_NB ( unsigned char ** ptrTab , const infoBMP *infoEntete,const unsigned char couleurPix)
{
          int i ; 
          int j ; 
          
          for  ( i = 0 ; i < infoEntete->hauteur ; i++)
                {
                    for ( j = 0 ;  j < infoEntete->largeur ; j++)
                          {
                              if( (i >= 0 && i<= DECALAGE ) || ( i >= infoEntete->hauteur - DECALAGE && i <= infoEntete->hauteur ) || ( j >= 0 && j <= DECALAGE ) || ( j >= infoEntete->largeur -DECALAGE && j <= infoEntete->largeur ) )
                                        ptrTab[i][j] = couleurPix ; 
                          }
                }
          return ptrTab; 
}




void seuillage_damier ( unsigned char ** ptrTab , const infoBMP *infoEntete,const unsigned char couleurPix ) 
{
          int i ; 
          int j ; 
          int ligne ; // correspondent au ligne et colonne à partir desquelle 
          int colonne ; 
          int seuille ; 
          printf ( " Veuillez entrez la valeur de la ligne puis la colonne à partir de laquelle vous souhaitez appliquer le filtre : \t"); 
          scanf ("%d %d",&ligne,&colonne); 
          printf ( "\n"); 
          if ( ligne > infoEntete->hauteur)
                {
                    ligne = infoEntete->hauteur -1  ; 
                }
          if ( colonne > infoEntete->largeur)
                {
                    colonne = infoEntete->largeur - 1 ; 
                }
          printf ( " Veuillez entrez le seuille : ");
          scanf( "%d",&seuille); 
          printf (" \n"); 
          for ( i = 0 ; i < infoEntete->hauteur ; i++ )
                {
                    for ( j = 0 ; j < infoEntete->largeur ; j++ )
                          {
                              if (( i > ligne && j > colonne) && ( ptrTab[i][j] > seuille )  )
                                    {
                                        ptrTab[i][j] = 255 ;
                                    }
                              else if ( ( i > ligne && j > colonne) && ( ptrTab[i][j] < seuille ) )
                                    {
                                        ptrTab[i][j] = 0 ; 
                                    }
                          }
                }
}


void  dessinner_histogramme_1 ( unsigned char ** ptrTab , const infoBMP *infoEntete,const unsigned char couleurPix )
{
          int tableau_effectif [NBR_COULEUR] = {0} ; 
          int *tableau_classe = calloc((sqrt(NBR_COULEUR)), sizeof(int)); 
          if ( tableau_classe )
                {
                    determination_effectif(ptrTab, infoEntete, tableau_effectif);
                    creation_classe(tableau_classe, tableau_effectif);
                    tapis_blanc(ptrTab, infoEntete); 
                    afficher_taff(tableau_classe); 
                    dessiner_histogramme(ptrTab, tableau_classe, infoEntete); 
                }
          else 
                {
                    assert (tableau_classe != NULL); 
                }
          
}


void retouch2D_IMC_2_K_means_NG( unsigned char **matrice , const infoBMP*infoEntete )
{
          int k  = 0;
          int compteur = 0 ; 
          float temps_dexecution = 0.0 ; 
          int nombre_cluster = 0 ;
          centre_PNS_NG centres = {NULL}; 
          time_t start , end; /*variables servant à contenir la valeur retourné par la fonction clock */ 
          sommes_NG sigma = {0}; // structures de pointeurs sur tableau. 
          printf ( " Combien de cluster ? : \t"); 
          scanf("%d",&nombre_cluster); 
          int *nombre_element_cluster = alloc_memoir(nombre_cluster); 
          initialiser_centre_memoir_NG(nombre_cluster,&centres); // a modifier 
          srandom((int)time(NULL)); 
          initialise_center_NG(centres.centre_n, nombre_cluster,infoEntete); // a modifier 
          centres.centre_s = centres.centre_n ; // copie dans pour save ; 
          initialisation_sigma_NG(&sigma, nombre_cluster); // a modifier 
          cluster_NG** groupe = create_groupe_NG(infoEntete); 
          start = clock();
          do 
                {
                    if(egalite_centre_NG(centres.centre_n, centres.centre_p, nombre_cluster) == 1) break; /*Si les centres précédents ont les mêmes cood que le new cent */
                    for ( k = 0 ; k < nombre_cluster; k++ ) centres.centre_p[k] = centres.centre_n[k];    /*si faux on recopie les new cood dans centre_p */ 
                    k_means_NG( centres.centre_n, nombre_cluster, infoEntete, matrice, nombre_element_cluster, groupe);                   
                    calcul_centre_NG(centres.centre_n ,groupe, nombre_element_cluster , nombre_cluster,&sigma,infoEntete);
                    remise_zero_sigma_NG(&sigma, nombre_cluster); 
                    remise_zero_NG(nombre_element_cluster, k); 
                    affiche_centre_NG(centres.centre_n, k); 
                    compteur++;    
                }while ( compteur < LIMITE_NOMBRE_TOURS);// a retirer
          end = clock(); 
          modifier_image_NG(centres.centre_n, matrice, nombre_cluster, infoEntete, groupe); 
          temps_dexecution = ( (float)(end-start)/(CLOCKS_PER_SEC)  ); 
          printf ( "\n temps d 'execution : %f \n\n",temps_dexecution); 
         free(centres.centre_p); free(centres.centre_s); free(nombre_element_cluster);// libération de la mémoire
          free_memory_NG(&sigma); 
}


void difference_gauss ( const infoBMP * infoEntete ,  unsigned char ** matrice  )
{
          int i , j ; 
          int  ecart_type_1 = 0 ; 
          int ecart_type_2 = 0 ; 
          int  moyenne = means_matrice(infoEntete,matrice); 
          printf( " Entrez la valeur de sigma 1 :\t "); 
          scanf ( " %d",&ecart_type_1); 
          printf (" \n"); 
          printf ( " Entrez la valeur de sigma 2 : \t"); 
          scanf ( "%d",&ecart_type_2); 
          for ( i = 0 ; i < infoEntete->hauteur ; i++ )
                {
                    for ( j = 0 ; j < infoEntete->largeur ; j++ )
                          {
                              matrice[i][j] = new_x(moyenne, matrice[i][j], ecart_type_1, ecart_type_2); 
                          }
                }
}


void filtre_prewitt( unsigned  char**matrice , infoBMP*infoEntete )
{
          int largeur = 0 ; 
          int hauteur = 0 ; 
          int temp[3][3] = {0} ;  
          do 
                {
                    for ( largeur = 0 ; largeur < infoEntete->largeur ; largeur += 3 )
                          {
                              copie_vers_mini_matrice(matrice, temp,hauteur,largeur);
                              gradient(temp); 
                                      
                              copie_vers_matrice(matrice, temp,hauteur,largeur); 
                          }
                    
                    hauteur+= 3 ; 
                }while ( hauteur < (infoEntete->hauteur-3)  ); 
          restore_picture_retouch2D_NB(matrice, "/Users/remydeme/Documents/programmes/projet7/projet7/database/lena.bmp", infoEntete); 
}



void change_pix (  unsigned  char**matrice , infoBMP*infoEntete)
{
          int i = 0, j ; 
          pixe tableau[8] = {0}; 
          do{
                    for ( j = 0 ; j < (infoEntete->largeur - 8) ; j+=8 )
                          {
                              remplir_tab(matrice, tableau, i, j);
                              sort_tab(tableau); 
                              echanger_valeur(tableau); 
                              remplir_matrice(matrice, tableau); 
                          }
                    i+=2; 
                }while ( i < (infoEntete->hauteur - 4)); 
          restore_picture_retouch2D_NB(matrice,"/Users/remydeme/Documents/programmes/projet7/projet7/database/lena.bmp",  infoEntete); 
}












