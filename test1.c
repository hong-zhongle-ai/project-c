#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/**
 * javadoc
 */
typedef struct { int cx, cy, rx, ry; } ellipse_t;
typedef struct { int x, y; } rectangle_t;
typedef struct { int x, y; } carres_t; 
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

typedef struct list {
    enum ShapeType Typeforme; 
    void* Forme;              
    struct list *prec;        
} List;

/**
 * alocation de la memoire
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

rectangle_t* create_rectangle(int x, int y) {
    rectangle_t *rectangle = malloc(sizeof(rectangle_t));
    if (rectangle == NULL) { perror("malloc rectangle"); return NULL; }
    rectangle->x = x;
    rectangle->y = y;
    return rectangle;
}

carres_t* create_carres(int x, int y) {
    carres_t *carres = malloc(sizeof(carres_t));
    if (carres == NULL) { perror("malloc carres"); return NULL; }
    carres->x = x;
    carres->y = y;
    return carres;
}

cercle_t* create_cercle(int x, int y, int r) {
    cercle_t *cercle = malloc(sizeof(cercle_t));
    if (cercle == NULL) { perror("malloc cercle"); return NULL; }
    cercle->x = x;
    cercle->y = y;
    cercle->r = r;
    return cercle;
}

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
 * la liste
 */ 

void free_shape_data(enum ShapeType type, void *shape) {
    if (shape != NULL) {
        free(shape);
    }
}

List *createNode(enum ShapeType type, void* forme) {
    List *mylist = malloc(sizeof(List));
    if (mylist == NULL) {
        fprintf(stderr, "ariel na pas fait son node\n");
        return NULL;
    }
    mylist->Typeforme = type;
    mylist->Forme = forme;
    mylist->prec = NULL;
    return mylist;
}

void pushFront(List **head, enum ShapeType type, void* forme) {
    List *newNode = createNode(type, forme);
    if (!newNode) return;
    newNode->prec = *head;
    *head = newNode;
}

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
*la ou on ecrire le svg
*/

void print_ellipse_svg(FILE *svg, ellipse_t *e) {
    fprintf(svg, " <ellipse cx=\"%d\" cy=\"%d\" rx=\"%d\" ry=\"%d\" fill=\"purple\" />\n",
            e->cx, e->cy, e->rx, e->ry);
}

void print_rectangle_svg(FILE *svg, rectangle_t *r) {
    fprintf(svg, " <rect x=\"%d\" y=\"%d\" width=\"80\" height=\"50\" fill=\"blue\"  />\n",
            r->x, r->y);
}

void print_carres_svg(FILE *svg, carres_t *c) {
    fprintf(svg, " <rect x=\"%d\" y=\"%d\" width=\"40\" height=\"40\" fill=\"green\" />\n",
            c->x, c->y);
}

void print_cercle_svg(FILE *svg, cercle_t *c) {
    fprintf(svg, " <circle cx=\"%d\" cy=\"%d\" r=\"%d\" fill=\"red\" />\n",
            c->x, c->y, c->r);
}

void print_line_svg(FILE *svg, line_t *l) {
    fprintf(svg, " <line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"black\" stroke-width=\"3\" />\n",
            l->x1, l->y1, l->x2, l->y2);
}

void export_shapes_to_svg(const char *filename, List *head) {
    FILE *svg = fopen(filename, "w");
    if (!svg) {
        perror("Error opening SVG file");
        return;
    }

    /** 
    *SVG viewbox
    */
    fprintf(svg, "<svg width=\"800\" height=\"600\" xmlns=\"http://www.w3.org/2000/svg\">\n");
    fprintf(svg, " <desc>Generated shapes</desc>\n");

    List *current = head;
    while (current != NULL) {
        switch (current->Typeforme) {
            case TYPE_ELLIPSE:
                print_ellipse_svg(svg, (ellipse_t*)current->Forme);
                break;
            case TYPE_RECTANGLE:
                print_rectangle_svg(svg, (rectangle_t*)current->Forme);
                break;
            case TYPE_CIRCLE:
                print_cercle_svg(svg, (cercle_t*)current->Forme);
                break;
            case TYPE_LINE:
                print_line_svg(svg, (line_t*)current->Forme);
                break;
            case TYPE_SQUARE:
                print_carres_svg(svg, (carres_t*)current->Forme);
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
void* handle_ellipse_input() {
    int cx, cy, rx, ry;
    printf("Ellipse - Center X (cx): ");
    if (scanf("%d", &cx) != 1) return NULL;
    printf("Ellipse - Center Y (cy): ");
    if (scanf("%d", &cy) != 1) return NULL;
    printf("Ellipse - Radius X (rx): ");
    if (scanf("%d", &rx) != 1) return NULL;
    printf("Ellipse - Radius Y (ry): ");
    if (scanf("%d", &ry) != 1) return NULL;
    return create_ellipse(cx, cy, rx, ry);
}

void* handle_rectangle_input() {
    int x, y;
    printf("Rectangle - Top-left X (x): ");
    if (scanf("%d", &x) != 1) return NULL;
    printf("Rectangle - Top-left Y (y): ");
    if (scanf("%d", &y) != 1) return NULL;
    return create_rectangle(x, y);
}

void* handle_carres_input() {
    int x, y;
    printf("Square - Top-left X (x): ");
    if (scanf("%d", &x) != 1) return NULL;
    printf("Square - Top-left Y (y): ");
    if (scanf("%d", &y) != 1) return NULL;
    return create_carres(x, y);
}

void* handle_cercle_input() {
    int x, y, r;
    printf("Circle - Center X (cx): ");
    if (scanf("%d", &x) != 1) return NULL;
    printf("Circle - Center Y (cy): ");
    if (scanf("%d", &y) != 1) return NULL;
    printf("Circle - Radius (r): ");
    if (scanf("%d", &r) != 1) return NULL;
    return create_cercle(x, y, r);
}

void* handle_line_input() {
    int x1, y1, x2, y2;
    printf("Line - Start X (x1): ");
    if (scanf("%d", &x1) != 1) return NULL;
    printf("Line - Start Y (y1): ");
    if (scanf("%d", &y1) != 1) return NULL;
    printf("Line - End X (x2): ");
    if (scanf("%d", &x2) != 1) return NULL;
    printf("Line - End Y (y2): ");
    if (scanf("%d", &y2) != 1) return NULL;
    return create_line(x1, y1, x2, y2);
}

/**
 * menu
 */

int afficher_et_choisir_forme() {
    int choix = -1;

    printf("\n====================================\n");
    printf("      CHOIX DE LA FORME GÉOMÉTRIQUE\n");
    printf("====================================\n");
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

    //note a moi de ne pas oublier ca si c'est pas la mon code peux lire 2 fois la meme chose
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 

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

        switch (selection) {
            case TYPE_ELLIPSE:
                new_shape = handle_ellipse_input(); 
                break;
            case TYPE_RECTANGLE:
                new_shape = handle_rectangle_input();
                break;
            case TYPE_CIRCLE:
                new_shape = handle_cercle_input();
                break;
            case TYPE_LINE:
                new_shape = handle_line_input();
                break;
            case TYPE_SQUARE:
                new_shape = handle_carres_input();
                break;
            default:
                printf("yare yare kono bake \n");
                continue;
        }

        if (new_shape != NULL) {
            pushFront(&shape_list, (enum ShapeType)selection, new_shape); 
            printf("ajout a la liste\n");
        } else if (selection != -1) {
            printf("bruh ca marche pas\n");
        }

    } while (1);

    if (shape_list != NULL) {
        export_shapes_to_svg("output.svg", shape_list);
    } else {
        printf("il y a rien\n");
    }

    free_shape_list(&shape_list); 
    printf("free la memoire\n");

    return EXIT_SUCCESS;
}