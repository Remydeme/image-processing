//
//  matrice1DC.c
//  projet7
//
//  Created by remy DEME on 25/03/2016.
//  Copyright © 2016 DEME Rémy. All rights reserved.
//

#include "matrice1DC.h"
#include "matrice1DC.h"
          // image noir et blanc 

infoBMP* read_header1D_IMC ( const char file_name[])
{
          if ( file_name)
                {
                    char cheminAbsolue[CHEMIN_ABSOLUE] = "/Users/remydeme/Documents/programmes/projet7/projet7/database/"; 
                    strcat(cheminAbsolue, file_name);// complete chemin absolue 
                    infoBMP *ptrEntete ;  // définie une var pour enregistrer l'entete 
                     FILE * ptrFile = fopen(cheminAbsolue, "rb"); // ouverture du flot
                    if (!(ptrEntete = calloc(1, sizeof(infoBMP))) ) // test si l'allocation c'est bien passé 
                          {
                              perror("infoBMP Alocation : "); 
                              exit(EXIT_FAILURE); 
                          }
                    
                    if ( ptrFile && ptrEntete)// test ptr
                          {
                              fread(ptrEntete,sizeof(infoBMP), 1, ptrFile); // lecture du flot 
                          }
                    else
                          {
                              perror("Message : ");
                              exit(EXIT_FAILURE); 
                          }// Message d'erreur 
                    fclose(ptrFile); // fermeture du flot 
                    return ptrEntete ; // return l'addresse de l'entete 
                }
          else 
                {
                    perror("MESSAGE : "); 
                    exit( EXIT_FAILURE); 
                }
}



pix  * builtTab1D_IMC ( const infoBMP * infoEntete, const char fileName[] )
{
          if ( infoEntete && fileName)
                {
                    pix * ptrTab = NULL ;// allocation dynamique // ++> définition d'une M1D 
                    if (!( ptrTab = calloc( ((infoEntete->hauteur) * (infoEntete->largeur) ) , sizeof(pix))) )
                          {
                              assert( ptrTab != NULL ); 
                          }
                    char cheminAbsolue[CHEMIN_ABSOLUE] = "/Users/remydeme/Documents/programmes/projet7/projet7/database/"; 
                    const size_t nombrePix =( (infoEntete->hauteur) * (infoEntete->largeur)  ) ; // calcule nombre de pixel M1D 
                    strcat(cheminAbsolue, fileName); // complete le chemin
                    FILE * ptrFile = fopen(cheminAbsolue, "rb"); // ouverture du fichier en mode lecture 
                    if ( ptrFile )// test pointeur 
                          {
                              fseek(ptrFile, infoEntete->offsetDecalage+OFFQET_SET, SEEK_SET);// on se place au début de l'image 
                              while ( fread(ptrTab, PIXEL_COULEUR, nombrePix, ptrFile) ) // lecture et copie dans matrice 
                                    {
                                                  //nombreAffectation++ ; 
                                    }
                                        // for ( i = 0 ; i < nombrePix ; i++)
                                        //  printf("PIXEL B: %d V: %d  R: %d . ", ptrTab[i].b , ptrTab[i].v , ptrTab[i].r);                               fclose(ptrFile); 
                          }
                    else perror("MESSAGE : "); 
                    
                    
                    return ptrTab; 
                    
                }
          else 
                {
                    printf(" ERREUR : Pointeur NULL . \n "); 
                    exit(EXIT_FAILURE); 
                }
}

          // fonctions qui recopie l'image une fois modifié dans un fichier // 
void restore_picture_retouch1D_IMC ( pix ptrTab[] , const char fileName[] ,const infoBMP *infoEntete )
{
          if ( ptrTab && fileName)// test la nullité des pointeurs 
                {
                    int i = 0 ; // variable de boucle 
                    size_t tailleI =( infoEntete->hauteur)*(infoEntete->largeur ); // calcul taille ligne image 
                    char cheminAbsolue[CHEMIN_ABSOLUE] = "/Users/remydeme/Documents/programmes/projet7/projet7/database/"; 
                    strcat(cheminAbsolue, fileName);// complète le chemin absolue
                    FILE* file = fopen(cheminAbsolue, "wb+"); // ouverture fichier en mode ecriture 
                    if ( file )// test 
                          {
                              
                              fwrite(infoEntete ,sizeof(infoBMP) , 1, file); // copie d'abord l'entete du fichier //
                              while (  i < tailleI  )
                                    {
                                        
                                        fwrite(&ptrTab[i],1,PIXEL_COULEUR, file); // recopie de la matrice dans le fichier 
                                        i++; // incrémente ntre i 
                                    }
                          }
                    fclose(file); // fermeture du flot 
                }
          else // si le fichier n'a pas été ouvert ++> 
                {
                    printf ( " Pointeur de tableau ou de nom de fichier NULL. \n  "); 
                    exit(EXIT_FAILURE);
                }
}




/* grace à deux boucle for et une variable on s'arrange afin d'avoir une représentation en 2D de la matrice colonne (^_^) */


pix * retouch1D_IMC ( pix *ptrTab , const infoBMP * infoEntete, const pix pixel)
{
          int i , j= 0; // variable de boucle 
          int folow = 1 ; // definie foloww // permet d'augmenter a chaque fin de bouble de " largeur " la valeur de la condition de la boucle for n°2 
          for ( i = 0 ; i < infoEntete->hauteur ; i++)// 
                {
                    for ( j = j ; j < (folow*infoEntete->largeur) ; j++ )
                          {
                              if ( (j >= (i*infoEntete->largeur) && (j <= i*infoEntete->largeur+DECALAGE))  || ( j <= (i+1)*(infoEntete->largeur) && (j >=  (i+1)*infoEntete->largeur - DECALAGE))|| ( i >= 0 && i<= DECALAGE ) || ( i <= infoEntete->hauteur && i>= infoEntete->hauteur -DECALAGE) )
                                    {
                                        ptrTab[j].b = pixel.b; 
                                        ptrTab[j].v = pixel.v; 
                                        ptrTab[j].r = pixel.r; 
                                        
                                    }
                              
                              
                          }
                    folow++; 
                }
          
          return ptrTab ; 
}
pix * retouch1D_IMC_2 ( pix *ptrTab , const infoBMP * infoEntete, const pix pixel)
{
          int i , j= 0; // variable de boucle 
          int folow = 1 ; // definie foloww // permet d'augmenter a chaque fin de bouble de " largeur " la valeur de la condition de la boucle for n°2 
          for ( i = 0 ; i < infoEntete->hauteur ; i++)// 
                {
                    for ( j = j ; j < (folow*infoEntete->largeur) ; j++ )
                          {
                              if ( (j >= 0 && j <= 10 ) || (j <= infoEntete->largeur && j >= infoEntete->largeur - 10 )) 
                                    {
                                        ptrTab[j].b = 200; 
                                        ptrTab[j].v = 200; 
                                        ptrTab[j].r = 200; 
                                        
                                    }
                              if ( (j >= (i*infoEntete->largeur) && (j <= i*infoEntete->largeur+DECALAGE))  || (  j <= (i+1)*infoEntete->largeur && (j >=  (i+1)*infoEntete->largeur - DECALAGE)  ) )
                                    {
                                        ptrTab[j].b = 200; 
                                        ptrTab[j].v = 0; 
                                        ptrTab[j].r = 0; 
                                    }
                              if( (i >= 0 && i<= DECALAGE ) || ( i <= infoEntete->hauteur && i>= infoEntete->hauteur -DECALAGE) )
                                    {
                                        ptrTab[j].b = 0; 
                                        ptrTab[j].v = 0; 
                                        ptrTab[j].r = 250; 
                                        
                                        
                                    }
                              
                              
                          }
                    folow++; 
                }
          
          return ptrTab ; 
}

