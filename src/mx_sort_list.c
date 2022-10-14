#include "libmx.h"

static void swap_consec(t_list *prev, t_list *a, t_list *b) {
    if (prev != 0) {
        prev->next = b;
    }
    a->next = b->next;
    b->next = a;
} 

t_list *mx_sort_list(t_list *list, bool (*cmp)(void *a, void *b)) {
    t_list *first = list;
    bool sorted = false;

    if (list == 0) {
        return 0;
    }

    while (!sorted) {
        t_list *prev = 0;
        
        sorted = true;
        for (t_list *current = first; current->next != 0;) {
            t_list *next = current->next;

            if (cmp(current->data, next->data)) {
                swap_consec(prev, current, next);
                if (prev == 0) {
                    first = next;
                }
                prev = next;
                sorted = false;
            }
            else {
                if (prev == 0) {
                    first = current;
                }
                prev = current;
                current = next;
            }
        }
    }

    return first;
}
