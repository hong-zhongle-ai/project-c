#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "shapes.h"
#include "structures.h"

Ellipse* create_ellipse(int cx, int cy, int rx, int ry) {
    Ellipse* el = malloc(sizeof(Ellipse));
    if(!el) return NULL;

    el->cx = cx;
    el->cy = cy;
    el->rx = rx;
    el->ry = ry;

    return el;
}



void free_ellipse(Ellipse *ellipse) {
    if (ellipse != NULL) {
        free(ellipse); // Libère le bloc de mémoire alloué par malloc.
    }
}

//rectangle
Rectangle* create_rectangle(int x, int y, int width, int height) {

    Rectangle *rectangle = malloc(sizeof(Rectangle));
    rectangle->x = x;
    rectangle->y = y;
    rectangle->width = width;
    rectangle->height = height;
    return rectangle;
}

void free_rectangle(Rectangle *rectangle) {
    if (rectangle != NULL) {
        free(rectangle);
    }
}

//circle
Circle* create_circle(int cx, int cy, int r) {

    Circle *circle = malloc(sizeof(Circle));
    circle->cx = cx;
    circle->cy = cy;
    circle->r = r;
    return circle;
}

void free_circle(Circle *circle) {
    if (circle != NULL) {
        free(circle);
    }
}

//line
Line* create_line(int x1, int y1, int x2, int y2) {

    Line *line = malloc(sizeof(Line));
    line->x1 = x1;
    line->y1 = y1;
    line->x2 = x2;
    line->y2 = y2;
    return line;
}

void free_Line(Line *Line) {
    if (Line != NULL) {
        free(Line);
    }
}

//carres
Square* create_square(int x, int y, int side) {

    Square *Square = malloc(sizeof(Square));
    Square->x = x;
    Square->y = y;
    Square->side = side;
    return Square;
}

void free_Square(Square *Square) {
    if (Square != NULL) {
        free(Square);
    }
}





