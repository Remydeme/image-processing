//
//  matrice2DC.c
//  projet7
//
//  Created by remy DEME on 25/03/2016.
//  Copyright © 2016 DEME Rémy. All rights reserved.
//

#include "matrice2DC.h"


infoBMP* read_header2D_C ( const char file_name[])
{
          if ( file_name)// si le pointeur vers le nom du fichier est NULL 
                {
                    char cheminAbsolue[CHEMIN_ABSOLUE] = "/Users/remydeme/Documents/programmes/projet7/projet7/database/"; 
                    strcat(cheminAbsolue, file_name);// complete le chemin absolue 
                    infoBMP *ptrEntete = calloc(1, sizeof(infoBMP) ); // definie un pointeur de type entete 
                    FILE * ptrFile = fopen(cheminAbsolue, "rb"); // ouverture du flot est  initialisation d'un pointeur 
                    if ( ptrFile && ptrEntete)// test pointeurs 
                          {
                              fread(ptrEntete,sizeof(infoBMP), 1, ptrFile); // on récupère l'entete 
                          }
                    else
                          {
                              perror("Message "); 
                          }
                    fclose(ptrFile); 
                    return ptrEntete ; 
                }
          else 
                {
                    perror("MESSAGE : "); 
                    exit( EXIT_FAILURE); 
                }
           
}



pix **builtTab2D_C ( const infoBMP * infoEntete, const char fileName[] )
{
          if( infoEntete && fileName)
                {
                    int i = 0 ; // variable de boucle for
                    char cheminAbsolue[CHEMIN_ABSOLUE] = "/Users/remydeme/Documents/programmes/projet7/projet7/database/"; 
                    strcat(cheminAbsolue, fileName);// complete le chemin absolue nAbsolue, fileName); 
                    FILE * ptrFile = fopen(cheminAbsolue,"rb"); 
                    pix **ptrTableau = allocation_tableau(infoEntete); 
                    if ( ptrFile)
                          {
                              fseek(ptrFile, infoEntete->offsetDecalage+OFFSET_SET, SEEK_SET);
                              for ( i = 0 ; i < infoEntete->largeur ; i++)
                                    {
                                       (void) fread(ptrTableau[i],sizeof(pix), infoEntete->largeur, ptrFile);
                                    }
                               fclose(ptrFile); 
                           }
                    else 
                          {
                              perror("ERREUR ouverture fichier : "); 
                          }
                    return ptrTableau; 
                    
                }
          else  exit(EXIT_FAILURE); 
}


          /* restore la photo */
void restore_picture_retouch2D_C (pix **ptrTableau,const char fileName[],const infoBMP *infoEntete )
{
          if ( ptrTableau && fileName)// test la nullité des pointeurs 
                {
                    
                    int i = 0 ;  // variable de boucle 
                    char cheminAbsolue[CHEMIN_ABSOLUE] = "/Users/remydeme/Documents/programmes/projet7/projet7/database/"; 
                    strcat(cheminAbsolue,fileName);// complète le chemin absolue
                    FILE* file = fopen(cheminAbsolue, "wb+"); 
                    if ( file )
                          {
                              
                              fwrite(infoEntete ,sizeof(infoBMP) ,1, file); // copie d'abord l'entete du fichier
                              for ( i = 0 ;  i < infoEntete->hauteur; i++)
                                    {
                                        fwrite(ptrTableau[i],sizeof(pix),(infoEntete->largeur), file); 
                                    }
                              
                          }
                    printf ( " Les Modifications ont été faites ! "); 
                    fclose(file); 
                }
          else 
                {
                    printf ( " Pointeur de tableau ou de nom de fichier NULL. \n  "); 
                    exit(EXIT_FAILURE);
                }
}



          // traite image matrice 2D couleur // 


pix **retouch2D_IMC( pix**ptrTab , const infoBMP*infoEntete ,const pix pixel)
{
          if ( ptrTab && infoEntete)
                {
                    int i , j ; // variables boucles for 
                    for ( i = 0 ; i < infoEntete->hauteur ; i++)
                          {
                              for ( j = 0 ; j < infoEntete->largeur ; j++ )
                                    {
                                        if ( (j <= infoEntete->largeur && j >= infoEntete->largeur-DECALAGE)  || ( j >= 0 && j<= DECALAGE ) || ( i >= 0 && i<= DECALAGE ) || (i <= infoEntete->hauteur && i >= infoEntete->hauteur-DECALAGE))
                                              {
                                                  ptrTab[i][j].b = pixel.b; 
                                                  ptrTab[i][j].v = pixel.v; 
                                                  ptrTab[i][j].r = pixel.r; 
                                              }
                                    }
                          }
                    return ptrTab; 
                }
          else 
                {
                    printf ( " Pointeur NULL . \n ");
                    exit(EXIT_FAILURE); 
                }
          
}


pix **retouch2D_IMC_2( pix**ptrTab , const infoBMP*infoEntete ,const pix pixel)
{
          if ( ptrTab && infoEntete)
                {
                    int i , j ; // variables boucles for 
                    for ( i = 0 ; i < infoEntete->hauteur ; i++)
                          {
                              for ( j = 0 ; j < infoEntete->largeur ; j++ )
                                    {
                                        
                                        if ( (j <= infoEntete->largeur && j >= infoEntete->largeur-DECALAGE)  || ( j >= 0 && j<= DECALAGE )) 
                                              {
                                                  ptrTab[i][j].b = 0; 
                                                  ptrTab[i][j].v = 0; 
                                                  ptrTab[i][j].r = 250; 
                                                  
                                              }
                                        if ( ( i >= 0 && i<= DECALAGE ) || (i <= infoEntete->hauteur&& i >= infoEntete->hauteur-DECALAGE) )
                                              {
                                                  ptrTab[i][j].b = 250; 
                                                  ptrTab[i][j].v = 0; 
                                                  ptrTab[i][j].r = 0; 
                                              }
                                        if( (( i >= 0 && i<= DECALAGE ) || (i <= infoEntete->largeur && i >= infoEntete->largeur-DECALAGE)) && (( j>= 0 && j<= DECALAGE) || (j <= infoEntete->largeur && j>= infoEntete->largeur-DECALAGE)) )
                                              {
                                                  ptrTab[i][j].b = 250; 
                                                  ptrTab[i][j].v = 250; 
                                                  ptrTab[i][j].r = 250; 
                                              }
                                        
                                    }
                          }
                    return ptrTab; 
                }
          else 
                {
                    printf ( " Pointeur NULL . \n ");
                    exit(EXIT_FAILURE); 
                }
          
          
          
}

pix **retouch2D_IMC_2_greyscale( pix**ptrTab , const infoBMP*infoEntete )
{
           int moyenne = 0 ;  
     
          if ( ptrTab && infoEntete)
                {
                    int i , j ; // variables boucles for 
                    for ( i = 0 ; i < infoEntete->hauteur ; i++)
                          {
                              for ( j = 0 ; j < infoEntete->largeur ; j++ )
                                    {
                                        moyenne = ( ptrTab[i][j].r +ptrTab[i][j].b +ptrTab[i][j].v )*0.8; 
                                        ptrTab[i][j].r =  moyenne;
                                        ptrTab[i][j].b = moyenne;
                                        ptrTab[i][j].v = moyenne; 
                                        
                                    }
                          }
                    return ptrTab; 
                }
          else 
                {
                    printf ( " Pointeur NULL . \n ");
                    exit(EXIT_FAILURE); 
                }
          
          
          
}

/* Valeur didéal de K est 5 et 4 par nombre de cluster */
void retouch2D_IMC_2_K_means( pix**matrice , const infoBMP*infoEntete )
{
          int k  = 0;
          int compteur = 0 ; 
          float temps_dexecution = 0.0 ; 
          int nombre_cluster = 0 ;
          centre_PNS centres = {NULL}; 
          time_t start , end; /*variables servant à contenir la valeur retourné par la fonction clock */ 
          sommes sigma = {0}; // structures de pointeurs sur tableau. 
          printf ( " Combien de cluster ? : \t"); 
          scanf("%d",&nombre_cluster); 
          int *nombre_element_cluster = alloc_memoir(nombre_cluster); 
          initialiser_centre_memoir(nombre_cluster,&centres); 
          srandom((int)time(NULL)); 
          initialise_center(centres.centre_n, nombre_cluster,infoEntete); 
          centres.centre_s = centres.centre_n ; // copie dans pour save ; 
          initialisation_sigma(&sigma, nombre_cluster); 
          cluster** groupe = create_groupe(infoEntete); 
          start = clock();
          do 
                {
                    if(egalite_centre(centres.centre_n, centres.centre_p, nombre_cluster) == 1) break; /*Si les centres précédents ont les mêmes cood que le new cent */
                    for ( k = 0 ; k < nombre_cluster; k++ ) centres.centre_p[k] = centres.centre_n[k];    /*si faux on recopie les new cood dans centre_p */ 
                    k_means( centres.centre_n, nombre_cluster, infoEntete, matrice, nombre_element_cluster, groupe);                   
                    calcul_centre(centres.centre_n ,groupe, nombre_element_cluster , nombre_cluster,&sigma,infoEntete);
                    remise_zero_sigma(&sigma, nombre_cluster); 
                    remise_zero(nombre_element_cluster, k); 
                    compteur++;    
                }while ( compteur < LIMITE_NOMBRE_TOURS);// a retirer
          end = clock(); 
          temps_dexecution = ( (float)(end-start)/(CLOCKS_PER_SEC)  ); 
          modifier_image(centres.centre_n,matrice,k,infoEntete,groupe);
          printf ( "\n temps d 'execution : %f \n\n",temps_dexecution); 
          affiche_centre(centres.centre_n, nombre_cluster); // affiche les centres finaux // 
          save_center(nombre_cluster,centres.centre_s, temps_dexecution); 
           free(centres.centre_p); free(centres.centre_s); free(nombre_element_cluster);// libération de la mémoire
          free_memory(&sigma); 
}


          /*Algorithme des k-means qui modifie */ 
void retouch2D_IMC_2_K_means_option( pix**matrice , const infoBMP*infoEntete )
{
          int k  = 0;
          int compteur = 0 ; 
          float temps_dexecution = 0.0 ; 
          int nombre_cluster = 0;
          int choix  = 0 ; 
          centre_PNS centres = {NULL,NULL}; 
          time_t start , end; /*variables servant à contenir la valeur retourné par la fonction clock */ 
          sommes sigma = {0}; // structures de pointeurs sur tableau. 
          printf ( " Combien de cluster ? : \t"); 
          scanf("%d",&nombre_cluster); 
          int *nombre_element_cluster = alloc_memoir(nombre_cluster);  
          initialiser_centre_memoir(nombre_cluster,&centres); 
          srandom((int)time(NULL)); 
          printf ( " 1- utilisez des centres aléatoires .    ");
          printf ( " 2- Utilisez coordonnées enregistrés . \n"); 
          (void)scanf ( "%d",&choix); 
          switch (choix) {
                    case 1 :
                              printf ( " \n Initialisation aléatoire .\n"); 
                               initialise_center(centres.centre_n, nombre_cluster,infoEntete); 
                              break;
                    case 2 : 
                              printf( " \n Chargement des centres .  \n"); 
                             if ( ENOENT != initialiser_centre_s(nombre_cluster, centres.centre_n) )
                                   {
                                       break; 
                                   }
                              
                    default:
                              printf ( " \n Initialisation aléatoire . \n "); 
                              initialise_center(centres.centre_n, nombre_cluster,infoEntete); 
                              break;
          }
          affiche_centre(centres.centre_n, nombre_cluster); 
          centres.centre_s = centres.centre_n ; // copie dans pour save ; 
          initialisation_sigma(&sigma, nombre_cluster); 
          cluster** groupe = create_groupe(infoEntete); 
          start = clock();
          do 
                {
                    if(egalite_centre(centres.centre_n, centres.centre_p, nombre_cluster) == 1) break; /*Si les centres précédents ont les mêmes cood que le new cent */
                    for ( k = 0 ; k < nombre_cluster; k++ ) centres.centre_p[k] = centres.centre_n[k];    /*si faux on recopie les new cood dans centre_p */ 
                    k_means( centres.centre_n, nombre_cluster, infoEntete, matrice, nombre_element_cluster, groupe);                   
                    calcul_centre(centres.centre_n ,groupe, nombre_element_cluster , nombre_cluster,&sigma,infoEntete);
                    remise_zero_sigma(&sigma, nombre_cluster); 
                    remise_zero(nombre_element_cluster, k); 
                    compteur++;    
                }while ( compteur < LIMITE_NOMBRE_TOURS);// a retirer
          fausse_couleur_centre(centres.centre_n, nombre_cluster); 
          modifier_image(centres.centre_n,matrice,k,infoEntete,groupe); 
          end = clock(); 
          temps_dexecution = ( (float)(end-start)/(CLOCKS_PER_SEC)  ); 
          printf ( "temps d 'execution : %f",temps_dexecution); 
          save_center(nombre_cluster,centres.centre_s, temps_dexecution); 
         free(centres.centre_p); free(centres.centre_s); free(nombre_element_cluster);// libération de la mémoire
          free_memory(&sigma); 

}


void  dessinner_histogramme_IMC2D ( pix** ptrTab , const infoBMP *infoEntete)
{
          if ( ptrTab && infoEntete)
                {
                    effec_pix effectif = {0,0,0}; 
                    determination_effectif_IMC(ptrTab, infoEntete, &effectif);
                    tapis_blanc_IMC(ptrTab, infoEntete); 
                    dessiner_histogramme_IMC(ptrTab, infoEntete, &effectif); 
                }
        else 
              {
                  assert(ptrTab != NULL ); 
                  assert(infoEntete != NULL ); 
              }
                   
}









