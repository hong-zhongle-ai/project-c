#include <stdlib.h>
#include <stdio.h>
#include "shapes.h"
#include <string.h>
#include "structures.h"



//int main(int argc, char * argv[]){
  //  FILE *svg;

//    svg = fopen("mon_dessin.svg", "w");

//if (svg == NULL) {
//        perror("Erreur lors de l'ouverture du fichier");
 //       return EXIT_FAILURE,printf("ya rien");
 //   }
    
//int x, y; 

//printf("Entrez la largeur (x) : ");
 //       scanf("%d", &x); 
 //       printf("Entrez la hauteur (y) : ");
 //       scanf("%d", &y);
 //       fprintf(svg, "<svg width=\"&x\" height=\"&y\" viewBox=\"0 0 &x &y\" xmlns=\"http://www.w3.org/2000/svg\">\n");
 //   
  //  char forme[15];
 //       printf("choisir une forme\ncercles\nellipse\ncarres\nrectangles\nlignes\nenchainements de lignes\npolygones\ntrajectoires,\ngroupes\n");
 //       scanf("%s", forme);    
        


//}



// Définition des constantes pour les choix du menu
#define RECTANGLE 1
#define CARRE 2
#define LIGNE 3
#define CERCLE 4
#define ELLIPSE 5
#define QUITTER 0

// Structure pour stocker les quatre valeurs de la ViewBox
typedef struct {
    double min_x, min_y;
    double width, height;
} ViewBox;

// Fonction pour afficher le menu
void afficher_menu() {
    printf("\n============================================\n");
    printf("        CHOIX DE LA FORME GÉOMÉTRIQUE\n");
    printf("============================================\n");
    printf("%d. Rectangle\n", RECTANGLE);
    printf("%d. Carré\n", CARRE);
    printf("%d. Ligne\n", LIGNE);
    printf("%d. Cercle\n", CERCLE);
    printf("%d. Ellipse\n", ELLIPSE);
    printf("%d. Quitter\n", QUITTER);
    printf("--------------------------------------------\n");
    printf("Entrez votre choix (0-5) : ");
}

// Fonction pour saisir les dimensions de la ViewBox
int saisir_viewbox(ViewBox *vb) {
    printf("\n--- SAISIE DE LA VIEWBBOX (min-x min-y width height) ---\n");
    printf("Entrez min-x (ex: 0) : ");
    if (scanf("%lf", &vb->min_x) != 1) return 0;
    
    printf("Entrez min-y (ex: 0) : ");
    if (scanf("%lf", &vb->min_y) != 1) return 0;

    printf("Entrez width (largeur, ex: 100) : ");
    if (scanf("%lf", &vb->width) != 1) return 0;

    printf("Entrez height (hauteur, ex: 100) : ");
    if (scanf("%lf", &vb->height) != 1) return 0;

    return 1;
}

// Fonction pour afficher les coordonnées et la viewBox
void afficher_resultats(ViewBox vb, const char *forme_type, const char *attributs) {
    printf("\n--- RESULTATS SVG GÉNÉRÉS ---\n");
    
    // 1. Affichage de la balise <svg> avec la ViewBox définie par l'utilisateur
    printf("➡️ Balise <svg> :\n");
    printf("   <svg viewBox=\"%.2f %.2f %.2f %.2f\" width=\"100%%\" height=\"100%%\">\n", 
           vb.min_x, vb.min_y, vb.width, vb.height);
           
    // 2. Affichage des coordonnées de la forme
    printf("➡️ Balise de la Forme :\n");
    printf("   <%s %s />\n", forme_type, attributs);
    
    printf("   </svg>\n");
    printf("---------------------------------------\n");
}


// Fonction principale pour gérer les dimensions et coordonnées de la forme
void saisir_dimensions(int choix, ViewBox vb) {
        FILE *svg;

    svg = fopen("mon_dessin.svg", "w");

    double x, y, dim1, dim2; // Variables pour les coordonnées et les dimensions
    char attributs[256] = ""; // Chaîne pour stocker les attributs SVG
    const char *forme_type;

    switch (choix) {
        case RECTANGLE:
            forme_type = "rect";
            printf("\n--- Forme: Rectangle ---\n");
            
            // Saisie des coordonnées de position
            printf("Entrez la coordonnée X (coin supérieur gauche) : ");
            if (scanf("%lf", &x) != 1) return;
            printf("Entrez la coordonnée Y (coin supérieur gauche) : ");
            if (scanf("%lf", &y) != 1) return;
            
            // Saisie des dimensions de taille
            printf("Entrez la Longueur (Width) : ");
            if (scanf("%lf", &dim1) != 1) return;
            printf("Entrez la Largeur (Height) : ");
            if (scanf("%lf", &dim2) != 1) return;
            fprintf(svg, "  <rect x=\"&x\" y=\"&y\" width=\"&dim1\" height=\"&dim2\"/>\n");
            snprintf(attributs, sizeof(attributs), "x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" height=\"%.2f\"",
                     x, y, dim1, dim2);
            break;

        case CARRE:
            forme_type = "rect"; // Un carré utilise la balise rect
            printf("\n--- Forme: Carré ---\n");
            
            // Saisie des coordonnées de position
            printf("Entrez la coordonnée X (coin supérieur gauche) : ");
            if (scanf("%lf", &x) != 1) return;
            printf("Entrez la coordonnée Y (coin supérieur gauche) : ");
            if (scanf("%lf", &y) != 1) return;
            
            // Saisie de la dimension (le côté)
            printf("Entrez la longueur du Côté (Width/Height) : ");
            if (scanf("%lf", &dim1) != 1) return;
            dim2 = dim1; // Largeur = Longueur
            
            snprintf(attributs, sizeof(attributs), "x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" height=\"%.2f\"",
                     x, y, dim1, dim2);
            break;

        case LIGNE:
            forme_type = "line";
            printf("\n--- Forme: Ligne ---\n");
            
            // Saisie des coordonnées de départ (x1, y1)
            printf("Entrez la coordonnée X1 (point de départ) : ");
            if (scanf("%lf", &x) != 1) return; // x1
            printf("Entrez la coordonnée Y1 (point de départ) : ");
            if (scanf("%lf", &y) != 1) return; // y1
            
            // Saisie des coordonnées d'arrivée (x2, y2)
            printf("Entrez la coordonnée X2 (point d'arrivée) : ");
            if (scanf("%lf", &dim1) != 1) return; // x2
            printf("Entrez la coordonnée Y2 (point d'arrivée) : ");
            if (scanf("%lf", &dim2) != 1) return; // y2
            
            snprintf(attributs, sizeof(attributs), "x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\"",
                     x, y, dim1, dim2);
            break;

        case CERCLE:
            forme_type = "circle";
            printf("\n--- Forme: Cercle ---\n");
            
            // Saisie des coordonnées du centre (cx, cy)
            printf("Entrez la coordonnée CX (centre horizontal) : ");
            if (scanf("%lf", &x) != 1) return; // cx
            printf("Entrez la coordonnée CY (centre vertical) : ");
            if (scanf("%lf", &y) != 1) return; // cy
            
            // Saisie de la dimension (rayon)
            printf("Entrez le Rayon (r) : ");
            if (scanf("%lf", &dim1) != 1) return; // r
            
            snprintf(attributs, sizeof(attributs), "cx=\"%.2f\" cy=\"%.2f\" r=\"%.2f\"",
                     x, y, dim1);
            break;

        case ELLIPSE:
            forme_type = "ellipse";
            printf("\n--- Forme: Ellipse ---\n");
            
            // Saisie des coordonnées du centre (cx, cy)
            printf("Entrez la coordonnée CX (centre horizontal) : ");
            if (scanf("%lf", &x) != 1) return; // cx
            printf("Entrez la coordonnée CY (centre vertical) : ");
            if (scanf("%lf", &y) != 1) return; // cy
            
            // Saisie des dimensions (rayons)
            printf("Entrez le Rayon horizontal (rx) : ");
            if (scanf("%lf", &dim1) != 1) return; // rx
            printf("Entrez le Rayon vertical (ry) : ");
            if (scanf("%lf", &dim2) != 1) return; // ry
            
            snprintf(attributs, sizeof(attributs), "cx=\"%.2f\" cy=\"%.2f\" rx=\"%.2f\" ry=\"%.2f\"",
                     x, y, dim1, dim2);
            break;

        default:
            return;
    }

    // Affiche la ViewBox et les attributs SVG de la forme
    afficher_resultats(vb, forme_type, attributs);
}

int main() {
    int choix;
    ViewBox vue_globale;
    
    // Initialisation de la ViewBox par défaut
    vue_globale.min_x = 0;
    vue_globale.min_y = 0;
    vue_globale.width = 100;
    vue_globale.height = 100;
    
    printf("Bienvenue dans le générateur d'attributs SVG.\n");
    
    // Saisie initiale de la ViewBox
    if (!saisir_viewbox(&vue_globale)) {
        printf("\n Saisie invalide pour la ViewBox. Le programme quitte.\n");
        return 1;
    }
    printf(" ViewBox définie : %.2f %.2f %.2f %.2f\n", 
           vue_globale.min_x, vue_globale.min_y, vue_globale.width, vue_globale.height);


    do {
        // Nettoie le buffer restant de la saisie précédente
        int c;
        while ((c = getchar()) != '\n' && c != EOF); 
        
        afficher_menu();
        
        // Saisie du choix de l'utilisateur
        if (scanf("%d", &choix) != 1) {
            printf("\n Saisie invalide. Veuillez entrer un nombre.\n");
            continue;
        }

        // Exécute l'action demandée
        if (choix >= RECTANGLE && choix <= ELLIPSE) {
            saisir_dimensions(choix, vue_globale);
        } else if (choix == QUITTER) {
            printf("\n Programme terminé. ciao !\n");
        } else {
            printf("\n Choix non valide. Veuillez sélectionner un numéro entre 0 et 5.\n");
        }

    } while (choix != QUITTER);

    return 0;
}