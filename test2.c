#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * @typedef definie toute les structure et ses parametre
 */
typedef struct { int cx, cy, rx, ry; } ellipse_t;
typedef struct { int x, y, width, height; } rectangle_t; 
typedef struct { int x, y, side; } carres_t; 
typedef struct { int x, y, r; } cercle_t; 
typedef struct { int x1, y1, x2, y2; } line_t; 

enum ShapeType {
    TYPE_ELLIPSE = 0,
    TYPE_RECTANGLE = 1,
    TYPE_CIRCLE = 2,
    TYPE_LINE = 3,
    TYPE_SQUARE = 4,
    TYPE_EXIT = 5
};

/**
 * @param color permet de choisir la couleur 20 caractere max
 */

typedef struct list {
    enum ShapeType Typeforme; 
    void* Forme;
    char color[20];           // NOUVEAU: Champ pour stocker la couleur saisie
    struct list *prec; 
} List;


// Vider le buffer (essentiel après scanf)
void clear_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 
}

/**
 * @param color_buffer Lire la couleur et la stocker dans color_buffer %19s pour le nombre de caractere
 */ 
int read_color(char *color_buffer) {
    printf("Entrez la couleur (ex: red, blue, #FF0000): ");
    if (scanf("%19s", color_buffer) != 1) {
        strcpy(color_buffer, "gray"); // Couleur par défaut si échec
        return 0; 
    }
    clear_buffer();
    return 1;
}

/**
 * fonction ellipse
 * @param cx coordonnées x du milieu de l'ellipse
 * @param cy coordonnées y du milieu de l'ellipse
 * @param rx coordonnées x du milieu de l'ellipse
 * @param ry coordonnées y du milieu de l'ellipse
 * @return retourne au pointeur ellipse
 */
ellipse_t* create_ellipse(int cx, int cy, int rx, int ry) {
    ellipse_t *ellipse = malloc(sizeof(ellipse_t)); 
    if (ellipse == NULL) { perror("malloc ellipse"); return NULL; }
    ellipse->cx = cx; 
    ellipse->cy = cy; 
    ellipse->rx = rx; 
    ellipse->ry = ry;
    return ellipse;
}

/**
 * fonction rectangle
 * @param x coordonnées x du coin haut gauche
 * @param y coordonnées y du coin haut gauche
 * @param width largeur du rectangle
 * @param height hauteur du rectangle
 * @return retourne au pointeur rectangle
 */
rectangle_t* create_rectangle(int x, int y, int w, int h) {
    rectangle_t *rectangle = malloc(sizeof(rectangle_t));
    if (rectangle == NULL) { perror("malloc rectangle"); return NULL; }
    rectangle->x = x; 
    rectangle->y = y;
    rectangle->width = w; 
    rectangle->height = h;
    return rectangle;
}

/**
 * fonction carres
 * @param x coordonnées x du coin haut gauche
 * @param y coordonnées y du coin haut gauche
 * @param side coin du carre
 * @return retourne au pointeur carres
 */
carres_t* create_carres(int x, int y, int side) {
    carres_t *carres = malloc(sizeof(carres_t));
    if (carres == NULL) { perror("malloc carres"); return NULL; }
    carres->x = x; 
    carres->y = y;
    carres->side = side;
    return carres;
}
/**
 * fonction rectangle
 * @param x coordonnées x du milieu
 * @param y coordonnées y du milieu
 * @param r rayon du cercle
 * @return retourne au pointeur rectangle
 */
cercle_t* create_cercle(int x, int y, int r) {
    cercle_t *cercle = malloc(sizeof(cercle_t));
    if (cercle == NULL) { perror("malloc cercle"); return NULL; }
    cercle->x = x; 
    cercle->y = y; 
    cercle->r = r;
    return cercle;
}
/**
 * fonction ligne
 * @param x1 coordonnées x d'une extremite de la ligne
 * @param y1 coordonnées y d'une extremite de la ligne
 * @param x2 coordonnées x d'une extremite de la ligne
 * @param y2 coordonnées y d'une extremite de la ligne
 * @return retourne au pointeur ellipse
 */
line_t* create_line(int x1, int y1, int x2, int y2) {
    line_t *line = malloc(sizeof(line_t));
    if (line == NULL) { perror("malloc line"); return NULL; }
    line->x1 = x1; 
    line->y1 = y1; 
    line->x2 = x2; 
    line->y2 = y2;
    return line;
}

/**
 * fonction free-liste
 * @param type donne le type de forme 
 * @param shape donne les parametre de la forme
 */ 

void free_shape_data(enum ShapeType type, void *shape) {
    if (shape != NULL) {
        free(shape);
    }
}

/**
 * fonction free-liste
 * @param type donne le type de forme 
 * @param forme donne les parametre de la forme
 * @param mylist nom de la liste cree
 * @param color la couleur dans le nœud
 * @return retourne vers la liste mylist 
 */ 
List *createNode(enum ShapeType type, void* forme, const char *color) {
    List *mylist = malloc(sizeof(List));
    if (mylist == NULL) {
        fprintf(stderr, "ariel na pas fait son node\n");
        return NULL;
    }
    mylist->Typeforme = type;
    mylist->Forme = forme;
    strncpy(mylist->color, color, sizeof(mylist->color) - 1);// strncpy permet de be pas overflow le buffer car la limite de char pour la couleur est de 20
    mylist->color[sizeof(mylist->color) - 1] = '\0';
    mylist->prec = NULL;
    return mylist;
}

/**
 * fonction pushliste
 * @param type donne le type de forme 
 * @param forme donne les parametre de la forme
 * @param head haut de la liste cree
 * @param current emplacement actuelle dans la liste
 * @param color la couleur
 * @return retourne vers la liste mylist 
 */ 
void pushFront(List **head, enum ShapeType type, void* forme, const char *color) {
    List *newNode = createNode(type, forme, color);
    if (!newNode) return;
    newNode->prec = *head;
    *head = newNode;
}
/** fonction free
 * @param head libert la place pour la prochaine forme
 * @param current emplacement actuelle dans la liste
 * @param typeforme type de forme
 * @param forme parametre de la forme
 */
void free_shape_list(List **head) {
    List *current = *head;
    List *next_node;

    while (current != NULL) {
        next_node = current->prec;
        free_shape_data(current->Typeforme, current->Forme);
        free(current);
        current = next_node;
    }
    *head = NULL;
}

/** 
* print ellipse
* @param svg le fichier svg
* @param ellipse les parametre de l'ellipse 
* @param color defini la couleur
*/

void print_ellipse_svg(FILE *svg, ellipse_t *ellipse, const char *color) {
    fprintf(svg, " <ellipse cx=\"%d\" cy=\"%d\" rx=\"%d\" ry=\"%d\" fill=\"%s\" />\n",
            ellipse->cx, ellipse->cy, ellipse->rx, ellipse->ry, color);
}

/** 
* print rectangle
* @param svg le fichier svg
* @param rectangle les parametre du rectangle
* @param color defini la couleur
*/
void print_rectangle_svg(FILE *svg, rectangle_t *rectangle, const char *color) {
    fprintf(svg, " <rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" fill=\"%s\"  />\n",
            rectangle->x, rectangle->y, rectangle->width, rectangle->height, color);
}

/** 
* print carre
* @param svg le fichier svg
* @param carres les parametre du carre
* @param color defini la couleur
*/
void print_carres_svg(FILE *svg, carres_t *carres, const char *color) {
    fprintf(svg, " <rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" fill=\"%s\" />\n",
            carres->x, c->y, carres->side, carres->side, color);
}

/** 
* print cercle
* @param svg le fichier svg
* @param cercle les parametre du cercle
* @param color defini la couleur
*/
void print_cercle_svg(FILE *svg, cercle_t *cercle, const char *color) {
    fprintf(svg, " <circle cx=\"%d\" cy=\"%d\" r=\"%d\" fill=\"%s\" />\n",
            cercle->x, cercle->y, cercle->r, color);
}

/** 
* print ligne
* @param svg le fichier svg
* @param e les parametre de la ligne
* @param color defini la couleur de la ligne
*/
void print_line_svg(FILE *svg, line_t *line, const char *color) {
    fprintf(svg, " <line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"%s\" stroke-width=\"3\" />\n",
            line->x1, line->y1, line->x2, line->y2, color);
}
/** 
* @param filename indique ou les parametre du svg seront marque
* @param head les forme stocker dans le liste
*/
void export_shapes_to_svg(const char *filename, List *head) {
    FILE *svg = fopen(filename, "w");
    if (!svg) {
        perror("Error opening SVG file");
        return;
    }
 /** 
    *SVG viewbox
    * @param current l'emplacement actuelle de la liste 
    * @param typeforme l'emplacement actu va etre un typeforme exemple ellipse
    * @param forme designe quelle forme sera pris en fonction de la forme pris par l'utilisateur
    * @param color ajoute la couleur choisie a la forme
    */
    fprintf(svg, "<svg width=\"800\" height=\"600\" xmlns=\"http://www.w3.org/2000/svg\">\n");
    fprintf(svg, " <desc>Generated shapes</desc>\n");

    List *current = head;
    while (current != NULL) {
        // NOUVEAU: On passe la couleur stockée dans current->color
        switch (current->Typeforme) {
            case TYPE_ELLIPSE:
                print_ellipse_svg(svg, (ellipse_t*)current->Forme, current->color);
                break;
            case TYPE_RECTANGLE:
                print_rectangle_svg(svg, (rectangle_t*)current->Forme, current->color);
                break;
            case TYPE_CIRCLE:
                print_cercle_svg(svg, (cercle_t*)current->Forme, current->color);
                break;
            case TYPE_LINE:
                print_line_svg(svg, (line_t*)current->Forme, current->color);
                break;
            case TYPE_SQUARE:
                print_carres_svg(svg, (carres_t*)current->Forme, current->color);
                break;
            default:
                fprintf(stderr, "tanjiro te dit que (%d) n'existe pas .\n", current->Typeforme);
                break;
        }
        current = current->prec;
    }
    /**
    * fermeture du svg
    */ 
    fprintf(svg, "</svg>\n");
    fclose(svg);
    printf("\n export_shapes_to_svg: %s \n", filename);
}

/**
 * le coordonnees des forme 
*/
void* handle_ellipse_input(char *color_out) {
    int cx, cy, rx, ry;
    printf("Ellipse - Center X (cx): "); 
    if (scanf("%d", &cx) != 1) { clear_buffer(); return NULL; }
    printf("Ellipse - Center Y (cy): "); 
    if (scanf("%d", &cy) != 1) { clear_buffer(); return NULL; }
    printf("Ellipse - Radius X (rx): "); 
    if (scanf("%d", &rx) != 1) { clear_buffer(); return NULL; }
    printf("Ellipse - Radius Y (ry): "); 
    if (scanf("%d", &ry) != 1) { clear_buffer(); return NULL; }
    
    read_color(color_out);
    return create_ellipse(cx, cy, rx, ry);
}

void* handle_rectangle_input(char *color_out) {
    int x, y, w, h;
    printf("Rectangle - Top-left X (x): "); 
    if (scanf("%d", &x) != 1) { clear_buffer(); return NULL; }
    printf("Rectangle - Top-left Y (y): "); 
    if (scanf("%d", &y) != 1) { clear_buffer(); return NULL; }
    printf("Rectangle - Largeur (width): "); 
    if (scanf("%d", &w) != 1) { clear_buffer(); return NULL; }
    printf("Rectangle - Hauteur (height): "); 
    if (scanf("%d", &h) != 1) { clear_buffer(); return NULL; }

    read_color(color_out);
    return create_rectangle(x, y, w, h);
}

void* handle_carres_input(char *color_out) {
    int x, y, side;
    printf("Square - Top-left X (x): "); 
    if (scanf("%d", &x) != 1) { clear_buffer(); return NULL; }
    printf("Square - Top-left Y (y): "); 
    if (scanf("%d", &y) != 1) { clear_buffer(); return NULL; }
    printf("Square - Côté (side): "); 
    if (scanf("%d", &side) != 1) { clear_buffer(); return NULL; }

    read_color(color_out);
    return create_carres(x, y, side);
}

void* handle_cercle_input(char *color_out) {
    int x, y, r;
    printf("Circle - Center X (cx): "); 
    if (scanf("%d", &x) != 1) { clear_buffer(); return NULL; }
    printf("Circle - Center Y (cy): "); 
    if (scanf("%d", &y) != 1) { clear_buffer(); return NULL; }
    printf("Circle - Radius (r): "); 
    if (scanf("%d", &r) != 1) { clear_buffer(); return NULL; }
    
    read_color(color_out);
    return create_cercle(x, y, r);
}

void* handle_line_input(char *color_out) {
    int x1, y1, x2, y2;
    printf("Line - Start X (x1): ");  
    if (scanf("%d", &x1) != 1) { clear_buffer(); return NULL; }
    printf("Line - Start Y (y1): "); 
    if (scanf("%d", &y1) != 1) { clear_buffer(); return NULL; }
    printf("Line - End X (x2): "); 
    if (scanf("%d", &x2) != 1) { clear_buffer(); return NULL; }
    printf("Line - End Y (y2): "); 
    if (scanf("%d", &y2) != 1) { clear_buffer(); return NULL; }

    read_color(color_out);
    return create_line(x1, y1, x2, y2);
}

/**
 * menu
 */

int afficher_et_choisir_forme() {
    int choix = -1;

    printf("\n==========================================================\n");
    printf("  CHOIX DE LA FORME GÉOMÉTRIQUE;taille du svg 800x600\n");
    printf("==========================================================\n");
    printf("%d. Ellipse\n", TYPE_ELLIPSE);
    printf("%d. Rectangle\n", TYPE_RECTANGLE);
    printf("%d. Cercle\n", TYPE_CIRCLE);
    printf("%d. Ligne\n", TYPE_LINE);
    printf("%d. Carré\n", TYPE_SQUARE);
    printf("%d. Quitter et Exporter SVG\n", TYPE_EXIT);
    printf("====================================\n");
    printf("Entrez votre choix (%d-%d) : ", TYPE_ELLIPSE, TYPE_EXIT);

    if (scanf("%d", &choix) != 1) {
        choix = -1;
    }
    clear_buffer(); // Utilisation de la fonction pour vider le buffer

    return choix;
}

int main() {
    List *shape_list = NULL;
    int selection;
    
    do {
        selection = afficher_et_choisir_forme();

        if (selection == TYPE_EXIT) {
            break;
        }
        
        void *new_shape = NULL;
        char temp_color[20] = ""; // Tampon pour stocker la couleur temporairement

        switch (selection) {
            case TYPE_ELLIPSE:
                new_shape = handle_ellipse_input(temp_color); 
                break;
            case TYPE_RECTANGLE:
                new_shape = handle_rectangle_input(temp_color);
                break;
            case TYPE_CIRCLE:
                new_shape = handle_cercle_input(temp_color);
                break;
            case TYPE_LINE:
                new_shape = handle_line_input(temp_color);
                break;
            case TYPE_SQUARE:
                new_shape = handle_carres_input(temp_color);
                break;
            default:
                printf("yare yare kono baka (Choix invalide) \n");
                continue;
        }

        if (new_shape != NULL) {
            pushFront(&shape_list, (enum ShapeType)selection, new_shape, temp_color); 
            printf("nezuko a ajouter la forme a la liste\n");
        } else if (selection != -1) {
            printf("bruh ca marche pas (Erreur de saisie ou de création)\n");
        }

    } while (1);

    if (shape_list != NULL) {
        export_shapes_to_svg("output.svg", shape_list);
    } else {
        printf("il y a rien\n");
    }

    free_shape_list(&shape_list); 
    printf("ryoiki tenkai expulsion de la memoire \n");

    return EXIT_SUCCESS;
}
