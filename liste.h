#ifndef LISTE_H
#define LISTE_H
#include "shapes.h"
#include "structures.h"

// Linked list node definition
typedef struct list {
    Typeforme_t Typeforme;
    Forme_t Forme;
    struct list *prec;
} List;

// Function prototypes
void init_shape_list(List **list);
List *createNode(Typeforme_t Typeforme, Forme_t Forme);
void pushFront(List **head, Typeforme_t Typeforme, Forme_t Forme);
void pushBack(List **head, Typeforme_t Typeforme, Forme_t Forme);
void insertAt(List **head, int position, Typeforme_t Typeforme, Forme_t Forme);
void popFront(List **head);
void printList(List *head);

#endif // LISTE_H
