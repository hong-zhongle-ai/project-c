#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "shapes.h"


//void init_shape_list(ShapeList* list)
//List *createNode(Typeforme_t Typeforme, Forme_t Forme) 
//{ 

//    struct list *mylist = malloc(sizeof(struct list));
    
//    if (mylist == NULL) {
//        fprintf(stderr, "Erreur d'allocation mémoire\n");
//        return NULL;
//    }
//    mylist->Typeforme = Typeforme;
//    mylist->Forme = Forme;
//    mylist->prec = NULL; // La list est initialement vide   
//    return mylist;     

//}
    // Ajouter une nouvelle forme au sommet de la list
//void pushFront(struct list **head, Typeforme_t, Forme_t)

//{ 
   // struct list *newNode = createNode(Typeforme_t, Forme_t); 
   // newNode->prec = *head; 
    //*head = newNode; 
//}

//void printlist(struct list *head){
    //struct list *current = head;

    //while (current != NULL)
    //{
    ///    printf("Typeforme", "Forme" , current->Typeforme, current->Forme);
        //current = current->prec;
    //}
    
//}
//void pushback(struct list **head, char Typeforme_t, char Forme_t){
    //struct list *newNode = createNode(Typeforme_t forme, Forme_t shapes);
    //if (*head == NULL) {
        //*head = newNode;
    //} else {
        //struct list *current = *head;
        //while (current->prec != NULL) {
            //current = current->prec;
        //}
        //current->prec = newNode;
    //}
//}

//void popFront(struct list **head){
    //if (*head == NULL) {
     //   printf("La list est vide, impossible de supprimer un élément.\n");
       // return;
   // }
    //struct list *temp = *head;
    //*head = (*head)->prec;
    //free(temp);
//}

//void insertAt(struct list **head,int position,Typeforme_t,Forme_t)
//{
//    struct list *newNode = createNode(Typeforme_t, Forme_t);
//    if (position == 0) {
//        newNode->prec = *head;
//        *head = newNode;
//        return;
//    }
//    struct list *current = *head;
//    for (int i = 0; current != NULL && i < position - 1; i++) {
//        current = current->prec;
//    }
//    if (current == NULL) {
//        printf("La position est en dehors des limites de la list.\n");
//        free(newNode);
//        return;
//    }
//    newNode->prec = current->prec;
//    current->prec = newNode;
//};

//int test() {
//    list *mylist = NULL;
    

    //pushFront(&mylist, forme, shapes);//erreur avec mylist
    //pushback(&mylist, forme, shapes);//erreur avec mylist
    //popFront(&mylist);
    //puts(mylist->forme);
//    printlist(mylist);
//    return 0;
//}


// Assuming these types are defined in your headers
// typedef enum { CERCLE, RECTANGLE, TRIANGLE } Typeforme_t;
// typedef struct { ... } Forme_t;

typedef struct list {
    Typeforme_t Typeforme;
    Forme_t Forme;
    struct list *prec;
} List;

// Initialize a shape list
void init_shape_list(List **list) {
    *list = NULL;
}

// Create a new node
List *createNode(Typeforme_t Typeforme, Forme_t Forme) {
    List *mylist = malloc(sizeof(List));
    if (mylist == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return NULL;
    }
    mylist->Typeforme = Typeforme;
    mylist->Forme = Forme;
    mylist->prec = NULL;
    return mylist;
}

// Add a new node at the front
void pushFront(List **head, Typeforme_t Typeforme, Forme_t Forme) {
    List *newNode = createNode(Typeforme, Forme);
    if (!newNode) return;
    newNode->prec = *head;
    *head = newNode;
}

// Print the list
void printList(List *head) {
    List *current = head;
    int index = 0;
    while (current != NULL) {
        printf("Node %d → Type: %d | Forme: [data here]\n", index, current->Typeforme);
        current = current->prec;
        index++;
    }
}

// Add a new node at the back
void pushBack(List **head, Typeforme_t Typeforme, Forme_t Forme) {
    List *newNode = createNode(Typeforme, Forme);
    if (!newNode) return;

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    List *current = *head;
    while (current->prec != NULL) {
        current = current->prec;
    }
    current->prec = newNode;
}

// Remove the first node
void popFront(List **head) {
    if (*head == NULL) {
        printf("La liste est vide, impossible de supprimer un élément.\n");
        return;
    }
    List *temp = *head;
    *head = (*head)->prec;
    free(temp);
}

// Insert at a given position
void insertAt(List **head, int position, Typeforme_t Typeforme, Forme_t Forme) {
    List *newNode = createNode(Typeforme, Forme);
    if (!newNode) return;

    if (position == 0) {
        newNode->prec = *head;
        *head = newNode;
        return;
    }

    List *current = *head;
    for (int i = 0; current != NULL && i < position - 1; i++) {
        current = current->prec;
    }

    if (current == NULL) {
        printf("Position hors limites.\n");
        free(newNode);
        return;
    }

    newNode->prec = current->prec;
    current->prec = newNode;
}


void removeAt(List **head, int position) {
    if (*head == NULL) {
        printf("La liste est vide, rien à supprimer.\n");
        return;
    }

    List *node_to_delete = NULL;

    if (position == 0) {
        node_to_delete = *head;
        *head = (*head)->prec; // Move head to the next node
        free(node_to_delete);
        return;
    }

    List *current = *head;
    for (int i = 0; current != NULL && i < position - 1; i++) {
        current = current->prec;
    }

    if (current == NULL || current->prec == NULL) {
        printf("Position hors limites. La suppression a échoué.\n");
        return;
    }

    node_to_delete = current->prec;        // The node to delete is the 'next' one
    current->prec = node_to_delete->prec;  // Link the preceding node to the one AFTER the deleted node

    free(node_to_delete);
}

// Test function
int test() {
    List *mylist = NULL;
    init_shape_list(&mylist);

    // Example fake shape data
    Forme_t forme1, forme2, forme3;

    popFront(&mylist);
    pushBack(&mylist, 2, forme2);
    insertAt(&mylist, 1, 3, forme3);
    removeAt(&mylist, 1 );

    printList(mylist);

    popFront(&mylist);
    printList(mylist);

    return 0;
}
