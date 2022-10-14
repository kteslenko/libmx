#include "libmx.h"

void mx_pop_back(t_list **list) {
    t_list *current;
    
    if (list == NULL || *list == NULL) {
        return;
    }

    current = *list;

    if ((*list)->next == NULL) {
        free(*list);
        *list = NULL;
    }
    
    while (current->next->next != NULL) {
        current = current->next;
    }
    
    free(current->next);
    current->next = NULL;
}
