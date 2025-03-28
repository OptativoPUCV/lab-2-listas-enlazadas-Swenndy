#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node
{
    void *data;
    Node *next;
    Node *prev;
};

struct List
{
    Node *head;
    Node *tail;
    Node *current;
};

typedef List List;

Node *createNode(void *data)
{
    Node *new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List *createList()
{
    List *list = (List *)malloc(sizeof(List));
    list->head = NULL;
    list->current = NULL;
    return list;
}

void *firstList(List *list)
{
    if (list->head == NULL || list == NULL)
        return NULL;

    return list->head->data;
}

void *nextList(List *list)
{
    if (list == NULL || list->current == NULL || list->current->next == NULL)
        return NULL;

    list->current = list->current->next;
    return list->current->data;
}

void *lastList(List *list)
{
    if (list == NULL || list->current == NULL)
        return NULL;
    while (list->current->next != NULL)
    {
        list->current = list->current->next;
    }
    return list->current->data;
}

void *prevList(List *list)
{
    if (list == NULL || list->current == NULL || list->current->prev == NULL)
        return NULL;

    list->current = list->current->prev;
    return list->current->data;
}

void pushFront(List *list, void *data)
{
    Node *nuevo = createNode(data);
    nuevo->prev = NULL;
    if (list->head == NULL)
    {
        list->head = nuevo;
        list->tail = nuevo;
        nuevo->next = NULL;
    }
    else
    {
        nuevo->next = list->head;
        list->head->prev = nuevo;
        list->head = nuevo;
    }
}

void pushBack(List *list, void *data)
{
    list->current = list->tail;
    pushCurrent(list, data);
}

void pushCurrent(List *list, void *data)
{
    Node *nuevo = createNode(data);

    if (list->current->next == NULL)
    {
        list->current->next = nuevo;
        nuevo->prev = list->current;
        nuevo->next = NULL;
        list->tail = nuevo;
    }
    else
    {
        nuevo->next = list->current->next;
        list->current->next->prev = nuevo;
        nuevo->prev = list->current;
        list->current->next = nuevo;
    }
}

void *popFront(List *list)
{
    list->current = list->head;
    return popCurrent(list);
}

void *popBack(List *list)
{
    list->current = list->tail;
    return popCurrent(list);
}

void *popCurrent(List *list)
{
    if (list->current == NULL || list == NULL)
        return NULL;

    Node *aux = list->current;
    void *data = aux->data;

    if (aux->prev == NULL)
    {
        list->head = aux->next;
        list->head->prev = NULL;
    }
    else if (aux->next == NULL)
    {
        list->tail = aux->prev;
        aux->prev->next = NULL;
    }
    else
    {
        aux->prev->next = aux->next;
        aux->next->prev = aux->prev;
    }

    free(aux);
    return data;
}

void cleanList(List *list)
{
    while (list->head != NULL)
    {
        popFront(list);
    }
}