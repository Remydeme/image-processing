//
//  main.c
//  projet7
//
//  Created by remy DEME on 25/03/2016.
//  Copyright © 2016 DEME Rémy. All rights reserved.
//


/*  remarque : Lena_NB à un comportement étange la taille de son header est de 40 alors que l'oofset de décalage est de 1073 ??????? */


/* Notre projet ce limite à l'algorithme des K-means et la phase 1 tous les autres fichier sont des fichiers bonus */


#include "bmplib.h"
int main(int argc, const char * argv[])
{
          argc = 3 ; 
          argv[1] = "lena_NB.bmp";// nom image 
          argv[2] = "new_image2.bmp";// nom new Pic 
          
          
          if ( argc >= 2)
                {
                    int choix = 0 ;
                    char couleur = 0 ; 
                              // debut menu // 
                              // BIENVENU // message de beinvenu 
                              //printf ( " Date : %s \n",__DATE__);  
                              //PRESENTATION_APP// message 
                    if(strcmp(argv[1],NOM_IMAGE_COULEUR) == 0 )// si l'image est en couleur 
                          {
                              infoBMP * ptrEntete = NULL ; // récupère le pointeur 
                              pix**ptrTableau_2D = NULL;// initialisation pointeur 
                              pix *ptrTableau_1D = NULL ;// initialisation pointeur 
                              pix couleur_pixel = {100,100,100} ; 
                              QUESTION_WDW// question de choix 
                              printf ( "1- Charger et modifier dans une matrice 1D.\t\n"); 
                              printf ( "2- Charger et modifier dans une matrice 2D.\t\n"); 
                              printf ( "3- Affiche  Header \n");
                              printf ( "4- Segmenter l'image avec l'algorithme des K-means.\n "); 
                              printf ( "5 - Dessiner l'histogramme de l'image.\t\n"); 
                              printf ( "6 - Appliquer un filtre negatif sur l'image.\n");
                              printf ( "7- Appliquer les K-means avec option fausses couleurs. "); 
                              scanf( "%d",&choix); // lecture du choix utilisateur 
                              viderBuff(); // vider le buffer 
                              switch (choix) {//
                                        case DIMENSION_1:// si la dimension est de 1 
                                                  
                                                  ptrEntete = read_header1D_IMC(argv[1]);// récpère un pointeur sur la structure contenant 
                                                  
                                                  printf ( "a - Rouge.\n");
                                                  printf ( "b - bleu.\n"); 
                                                  printf ( "c - Vert.\n"); 
                                                  printf(  "d _ Blanc.\n"); 
                                                  printf ( "e - BBR .\n"); 
                                                  scanf ( "%c",&couleur);
                                                  viderBuff(); 
                                                  ptrTableau_1D = builtTab1D_IMC(ptrEntete, argv[1]); 
                                                  if ( couleur == 'e')
                                                        {
                                                            retouch1D_IMC_2(ptrTableau_1D, ptrEntete, couleur_pixel);        
                                                        }
                                                  
                                                  else 
                                                        {
                                                            SWITCH_COULEUR(couleur,(couleur_pixel.r),(couleur_pixel.v),(couleur_pixel.b))
                                                            ptrTableau_1D = retouch1D_IMC(ptrTableau_1D,ptrEntete,couleur_pixel);
                                                            
                                                        }
                                                  
                                                  restore_picture_retouch1D_IMC(ptrTableau_1D,argv[2], ptrEntete); 
                                                  
                                                  break;
                                                  
                                        case DIMENSION_2:
                                                  ptrEntete = read_header2D_C(argv[1]);
                                                  printf ( "a - Rouge.\n");
                                                  printf ( "b - bleu.\n"); 
                                                  printf ( "c - Vert.\n"); 
                                                  printf(  "d _ Blanc.\n"); 
                                                  printf ( "e - BBR .\n"); 
                                                  printf ( "g- grayscale.\n"); 
                                                  scanf ( "%c",&couleur); 
                                                  ptrTableau_2D = builtTab2D_C(ptrEntete, argv[1]); 
                                                  if ( couleur == 'e')
                                                        {
                                                            retouch2D_IMC_2(ptrTableau_2D, ptrEntete, couleur_pixel);        
                                                        }
                                                  else 
                                                        {
                                                            SWITCH_COULEUR(couleur,(couleur_pixel.r),(couleur_pixel.v),(couleur_pixel.b))
                                                            ptrTableau_2D = retouch2D_IMC(ptrTableau_2D,ptrEntete,couleur_pixel);
                                                            
                                                        }
                                                  
                                                  restore_picture_retouch2D_C(ptrTableau_2D,argv[2],ptrEntete); 
                                                  
                                                  
                                                  
                                                  break; 
                                                  
                                        case AFFICHE_HEADER : 
                                                  ptrEntete  = read_header2D_C(argv[1]);
                                                  affiche_header(ptrEntete); 
                                                  break ;
                                                  
                                        case K_MEANS: 
                                                  ptrEntete = read_header2D_C(argv[1]); 
                                                  ptrTableau_2D = builtTab2D_C(ptrEntete, argv[1]);
                                                  retouch2D_IMC_2_K_means(ptrTableau_2D, ptrEntete);
                                                  restore_picture_retouch2D_C(ptrTableau_2D,argv[2], ptrEntete); 
                                                  break;
                                                  
                                        case HISTOGRAMME : 
                                                  ptrEntete = read_header2D_C(argv[1]); 
                                                  ptrTableau_2D = builtTab2D_C(ptrEntete, argv[1]);
                                                  dessinner_histogramme_IMC2D(ptrTableau_2D, ptrEntete); 
                                                  restore_picture_retouch2D_C(ptrTableau_2D,argv[2], ptrEntete); 
                                                  break;
                                                  
                                        case EFFET_NEGATIF:
                                                  ptrEntete = read_header2D_C(argv[1]);
                                                  ptrTableau_2D = builtTab2D_C(ptrEntete, argv[1]); 
                                                  retouch2D_IMC_2_greyscale(ptrTableau_2D, ptrEntete); 
                                                  restore_picture_retouch2D_C(ptrTableau_2D, argv[2], ptrEntete);
                                                  break; 
                                                  
                                        case K_MEANS_FC_OPTION: 
                                                  ptrEntete = read_header2D_C(argv[1]); 
                                                  ptrTableau_2D = builtTab2D_C(ptrEntete, argv[1]);
                                                   retouch2D_IMC_2_K_means_option(ptrTableau_2D, ptrEntete); 
                                                  restore_picture_retouch2D_C(ptrTableau_2D, argv[2], ptrEntete); 
                                                  break; 
                                                  
                                        default:
                                                  ptrEntete  = read_header2D_C(argv[1]);
                                                  affiche_header(ptrEntete); 
                                                  break;
                              }
                              
                          }
                    else if( strcmp(argv[1],NOM_IMAGE_NB) == 0 )// a travailler 
                          {
                              
                              infoBMP * ptrEntete = NULL ; // declaration des variables 
                              unsigned char**ptrTableau_2D = NULL;
                              unsigned char *ptrTableau_1D = NULL ;
                              
                              QUESTION_WDW// message question 
                                          printf ( "1- Charger et modifier dans une matrice 1D.\n"); 
                                            printf ( "2- Charger et modifier dans une matrice 2D \t\n "); 
                              printf ( "1 - Appliquez le filtre de Sobel sur l'image.\t\n");
                                         printf ( "4- Appliquer seuillage damier sur photo.\t\n"); 
                                        printf ( " 5- Dessiner l'histogramme.\t\n ");
                                          printf( " 6- Appliquer l'algorithme des K-means à l'image \t\n"); 
                              printf ( " 8- Appliquer l'echange de pix .\n");
                              scanf( "%1d",&choix); // lecture du choix utilisateur 
                              viderBuff(); 
                              switch (choix) {
                                                  
                                        case DIMENSION_1  :
                                                  
                                                  ptrEntete = read_header2D_NB(argv[1]);
                                                  printf ( "n - noire.\n");
                                                  printf(  "b - Blanc.\n"); 
                                                  printf ( "c - BN .\n"); 
                                                  scanf ( "%c",&couleur); 
                                                  SWITCH_COULEUR_NB(couleur,couleur)
                                                  ptrTableau_1D = builtTab1D_NB(ptrEntete,argv[1]);
                                                  ptrTableau_1D = retouche1D_NB(ptrTableau_1D,ptrEntete,couleur); 
                                                  restore_picture_retouch1D_NB(ptrTableau_1D,argv[2], ptrEntete); 
                                                  break;
                                                  
                                        case DIMENSION_2:
                                                  ptrEntete = read_header2D_NB(argv[1]);
                                                  printf ( " Choisissez la couleur de votre bordure entrez une lettre : \n"); 
                                                  printf ( "n - noir.\n");
                                                  printf(  "b - Blanc.\n"); 
                                                  printf ( "c - BN .\n"); 
                                                  scanf ( "%1c",&couleur); 
                                                  SWITCH_COULEUR_NB(couleur,couleur) 
                                                  ptrTableau_2D = builtTab2D_NB(ptrEntete,argv[1]);
                                                  ptrTableau_2D = retouchIM2D_NB(ptrTableau_2D, ptrEntete, couleur); 
                                                  restore_picture_retouch2D_NB(ptrTableau_2D,argv[2],ptrEntete); 
                                                  
                                                  break; 
                                                  
                                        case FILTRE_PREWIT_SOBEL :
                                                  
                                                  ptrEntete = read_header2D_C(argv[1]);
                                                  ptrTableau_2D = builtTab2D_NB(ptrEntete, argv[1]); 
                                                  filtre_prewitt(ptrTableau_2D, ptrEntete); 
                                                            //restore_picture_retouch2D_NB(ptrTableau_2D,argv[2], ptrEntete); 

                                                  break;
                                        case SEUILLAGE_DAMIER :
                                                  ptrEntete = read_header2D_C(argv[1]);
                                                  ptrTableau_2D = builtTab2D_NB(ptrEntete, argv[1]); 
                                                  seuillage_damier(ptrTableau_2D, ptrEntete, 0); 
                                                  restore_picture_retouch2D_NB(ptrTableau_2D,argv[2], ptrEntete); 
                                                  break; 
                                        case HISTOGRAMME : 
                                                  ptrEntete = read_header2D_C(argv[1]);
                                                  ptrTableau_2D = builtTab2D_NB(ptrEntete, argv[1]); 
                                                  dessinner_histogramme_1(ptrTableau_2D,ptrEntete, 0);
                                                  restore_picture_retouch2D_NB(ptrTableau_2D,argv[2], ptrEntete); 
                                                  break; 
                                        case 6 : 
                                                  ptrEntete = read_header2D_C(argv[1]);
                                                  ptrTableau_2D = builtTab2D_NB(ptrEntete, argv[1]); 
                                                  retouch2D_IMC_2_K_means_NG(ptrTableau_2D, ptrEntete); 
                                                  restore_picture_retouch2D_NB(ptrTableau_2D,argv[2], ptrEntete);
                                                  break; 
                                        case 7 : 
                                                  ptrEntete = read_header2D_C(argv[1]);
                                                  ptrTableau_2D = builtTab2D_NB(ptrEntete, argv[1]); 
                                                  difference_gauss(ptrEntete, ptrTableau_2D); 
                                                  restore_picture_retouch2D_NB(ptrTableau_2D,argv[2], ptrEntete);
                                                  break; 
                                        case 8 : 
                                                  ptrEntete = read_header2D_C(argv[1]);
                                                  ptrTableau_2D = builtTab2D_NB(ptrEntete, argv[1]); 
                                                  change_pix(ptrTableau_2D, ptrEntete); 
                                                  break ; 
                                                  
                                                  
                                        default:
                                                  ptrEntete = read_header2D_NB(argv[1]);
                                                  printf ( " Choisissez la couleur de votre bordure entrez une lettre : \n"); 
                                                  printf ( "n - noir.\n");
                                                  printf(  "b - Blanc.\n"); 
                                                  printf ( "c - BN .\n"); 
                                                  scanf ( "%1c",&couleur); 
                                                  SWITCH_COULEUR_NB(couleur,couleur) 
                                                  ptrTableau_2D = builtTab2D_NB(ptrEntete,argv[1]);
                                                  ptrTableau_2D = retouchIM2D_NB(ptrTableau_2D, ptrEntete, couleur); 
                                                  restore_picture_retouch2D_NB(ptrTableau_2D,argv[2],ptrEntete); 
                                                  

                                                  break;
                              }
                              free(ptrEntete);
                              free(ptrTableau_2D);
                              
                          }
                    else 
                          {
                              printf ( " Veuillez donnez le bon argument d'entré . "); // a modifié dans ce cas lire l'entete et déterminer si elle est en couleur etc... 
                          }
                    
                    
                    
                    
                 }
          else 
                {
                  perror("Message : ");   
                }
                    
          
          return 0;
}


