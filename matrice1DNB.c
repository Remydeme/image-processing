//
//  matrice1DNB.c
//  projet7
//
//  Created by remy DEME on 25/03/2016.
//  Copyright © 2016 DEME Rémy. All rights reserved.
//

#include "matrice1DNB.h"
          // image noir et blanc 

          ///////////////// TESTER LES VALEUR DE RETOUR DES ALLOCATIONS DYNAMIQUE //////////// 

unsigned char  *builtTab1D_NB ( const infoBMP * infoEntete, const char fileName[] )
{
          if (fileName)
                {
                    unsigned char  * ptrTab = calloc(( infoEntete->tailleTot) , sizeof(unsigned char));
                    char cheminAbsolue[CHEMIN_ABSOLUE] = "/Users/remydeme/Documents/programmes/projet7/projet7/database/"; 
                              //int nombreAffectation = 0 ; 
                    const size_t nombrePix =( (infoEntete->hauteur) * (infoEntete->largeur)  ) ; 
                    strcat(cheminAbsolue, fileName); // complète le chemin absolu
                    FILE * ptrFile = fopen(cheminAbsolue, "rb"); // ouverture du fichier en mode lecture binaire 
                    if ( ptrFile)// si non nul
                          {
                              fseek(ptrFile, infoEntete->tailleEntete, SEEK_SET);// Place après l'entête 
                              fread(ptrTab,PIXEL_NB,nombrePix, ptrFile);  // on recopie les données dans la matrice 
                              
                                        //nombreAffectation++ ; 
                              
                                        //    printf(" Nombre Affectation : %d ", nombreAffectation); fflush(stdout);
                              fclose(ptrFile); 
                          }
                    else perror("MESSAGE : "); 
                    
                    
                    return ptrTab; // renvoie le pointeur sur la matrice 
                    
                }
          else 
                {
                    printf ( " Pointeur NULL. \n"); 
                    exit(EXIT_FAILURE);
                }
}


          // restore l'image dans un fichier apres modif //

void restore_picture_retouch1D_NB ( unsigned char ptrTab[] , const char fileName[] ,const infoBMP *infoEntete )
{
          if ( ptrTab && fileName)// test la nullité des pointeurs 
                {
                    char * src = calloc(infoEntete->offsetDecalage, sizeof(char)); 
                    char cheminAbsolue[CHEMIN_ABSOLUE] = "/Users/remydeme/Documents/programmes/projet7/projet7/database/";
                    char chemin_lena[CHEMIN_ABSOLUE] = "/Users/remydeme/Documents/programmes/projet7/projet7/database/lena_NB.bmp"; 
                    strcat(cheminAbsolue, fileName);// complète le chemin absolue
                    FILE * file_lena_NB  = NULL;
                    FILE* file = NULL; 
                    file_lena_NB = fopen(chemin_lena, "rb"); 
                     file = fopen(cheminAbsolue, "wb+"); // ouverture du flot en mode ecriture 
                    if ( file && file_lena_NB )
                          {
                              (void)fread(src,1,infoEntete->offsetDecalage,file_lena_NB); 
                              (void)fwrite(src ,1, infoEntete->offsetDecalage, file); // copie d'abord l'entete du fichier 
                              (void)fwrite(ptrTab,sizeof(char), infoEntete->tailleTot, file); 
                                    
                          }
                    else
                          {
                              perror("Message : ");
                          }
                    fclose(file); // fermeture du flot 
                }
          else // si les pointeurs sont NULL ; 
                {
                    printf ( " Pointeur de tableau ou de nom de fichier NULL. \n  "); 
                    exit(EXIT_FAILURE);
                }
          
}

          // reouvre l'image // 

unsigned char *retouche1D_NB ( unsigned char * ptrTab, const infoBMP*infoEntete,const char couleurPix )
{
          int i, j = 0 ; 
          int folow = 1 ;
          
          for ( i = 0 ; i < infoEntete->hauteur ; i++ )
                {
                    for ( j = j ; j < (folow*infoEntete->largeur) ; j++ ) 
                          {
                              if ( (j >= (i*infoEntete->largeur) && (j <= (i*infoEntete->largeur+DECALAGE)) )  || ( ( j <= (i+1)*(infoEntete->largeur)) && (j >= ( (i+1)*infoEntete->largeur - DECALAGE))) || ( i >= 0 && i<= DECALAGE ) || ( i <= infoEntete->hauteur && i>= infoEntete->hauteur -DECALAGE) )
                                    {
                                        ptrTab[j] = couleurPix ; 
                                    }
                              
                          }
                    folow++; 
                }
          return ptrTab;          
}

