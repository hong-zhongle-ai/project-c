#ifndef STRUCTURES_H
#define STRUCTURES_H
#include "shapes.h"
#include "structures.h"

typedef struct ShapeNode ShapeNode;
typedef struct ShapeList ShapeList;

typedef struct {
    unsigned x; // Coordonnée X du coin supérieur gauche
    unsigned y; // Coordonnée Y du coin supérieur gauche
    unsigned side; // Longueur du côté du carré
} Square;

Square* create_square(int x, int y, int side);    

void free_carres(Square *square);

typedef struct {
    unsigned x1; // Coordonnée X du point de départ (Starting Point X)
    unsigned y1; // Coordonnée Y du point de départ (Starting Point Y)
    unsigned x2; // Coordonnée X du point d'arrivée (Ending Point X)
    unsigned y2; // Coordonnée Y du point d'arrivée (Ending Point Y)
} Line;

Line* create_line(int x1, int y1, int x2, int y2);
    
void free_line(Line *line);

typedef struct {
    unsigned cx; // Coordonnée X du centre (Center X)
    unsigned cy; // Coordonnée Y du centre (Center Y)
    unsigned r;  // Rayon (Radius)
} Circle;

Circle* create_circle(int cx, int cy, int r);
    
void free_circle(Circle *circle);

typedef struct {
    unsigned x; // Coordonnée X du coin supérieur gauche
    unsigned y; // Coordonnée Y du coin supérieur gauche
    unsigned width; // Largeur du rectangle
    unsigned height; // Hauteur du rectangle
} Rectangle;

Rectangle* create_rectangle(int x, int y, int width, int height);
    
void free_rectangle(Rectangle *rectangle);
    

typedef struct {
    unsigned cx; // Coordonnée X du centre (Center X)
    unsigned cy; // Coordonnée Y du centre (Center Y)
    unsigned rx; // Rayon horizontal (Radius X)
    unsigned ry; // Rayon vertical (Radius Y)
} Ellipse;

Ellipse* create_ellipse(int cx, int cy, int rx, int ry);
    
void free_ellipse(Ellipse *ellipse);
    

typedef enum {
    SQUARE,
    ELLIPSE,
    RECTANGLE,
    CIRCLE,
    LINE
} Typeforme_t;

typedef union {
    Square* square;
    Ellipse* ellipse;
    Rectangle* rectangle;
    Circle* circle;
    Line* line;
} Forme_t;

struct ShapeNode {
    Typeforme_t type; // Type de la forme (ellipse, rectangle, cercle, ligne)
    Forme_t data; // Détails spécifiques de la forme
    struct ShapeNode* next;
    struct ShapeNode* prev;
};

struct ShapeList {
    ShapeNode* head;
    ShapeNode* tail;
    int size;
};

#endif