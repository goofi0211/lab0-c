#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* TODO: What if malloc returned NULL? */
    if (q) {
        q->head = NULL;
        q->tail = NULL;
        q->size = 0;
    }
    return q;  // return NULL if can't malloc
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* TODO: How about freeing the list elements and the strings? */
    /* Free queue structure */
    list_ele_t *tmp = NULL;
    if (q) {
        while (q->head) {
            tmp = q->head;
            free(tmp->value);  // free the listnode value
            q->head = q->head->next;
            free(tmp);  // free the listnode
        }
        free(q);  // free the queue
    }
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    /* TODO: What should you do if the q is NULL? */
    if (!q)
        return false;
    newh = malloc(sizeof(list_ele_t));
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    if (!newh)
        return false;
    if (q->size == 0)
        q->tail = newh;
    char *val =
        malloc((strlen(s) + 1) * sizeof(char));  // malloc space for string
    if (!val) {
        free(newh);
        return false;
    }
    memset(val, '\0', (strlen(s) + 1));
    val = strncpy(val, s, strlen(s));
    newh->value = val;
    newh->next = q->head;
    q->head = newh;
    q->size++;
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* TODO: You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q)
        return false;
    list_ele_t *newtail;
    newtail = malloc(sizeof(list_ele_t));
    if (!newtail)
        return false;
    char *val =
        malloc((strlen(s) + 1) * sizeof(char));  // malloc space for string
    if (!val) {
        free(newtail);
        return false;
    }
    memset(val, '\0', (strlen(s) + 1));
    val = strncpy(val, s, strlen(s));
    if (q->size == 0) {
        q->head = newtail;
        newtail->value = val;
        newtail->next = NULL;
        q->tail = newtail;
        q->size++;
        return true;
    }
    newtail->value = val;
    newtail->next = NULL;
    q->tail->next = newtail;
    q->tail = q->tail->next;
    q->size++;
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* TODO: You need to fix up this code. */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q || q->size == 0)
        return false;
    list_ele_t *tmp = q->head;
    if (sp != NULL) {
        memset(sp, '\0', bufsize);
        strncpy(sp, tmp->value, bufsize - 1);
    }
    q->head = q->head->next;
    q->size--;
    free(tmp->value);
    free(tmp);
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q)
        return 0;
    return q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q || q->size == 0)
        return;
    list_ele_t *cur = q->head;
    list_ele_t *pre = NULL;
    list_ele_t *nxt = NULL;
    q->tail = cur;
    while (cur) {
        nxt = cur->next;
        cur->next = pre;
        pre = cur;
        cur = nxt;
    }
    q->head = pre;
    return;
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q || q->size == 1)
        return;
    q->head = sort_list(q->head);
    list_ele_t *cur = q->head;
    while (cur) {  //確保tail也有被改到
        q->tail = cur;
        cur = cur->next;
    }
}
list_ele_t *sort_list(list_ele_t *t)
{
    if (!t || !t->next)
        return t;  //切到剩一個元素或沒有元素時結束
    //繼續切半
    list_ele_t *slow = t;
    list_ele_t *fast = t->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    list_ele_t *mid = slow->next;
    slow->next = NULL;
    slow = t;
    return my_merge_sort(sort_list(slow), sort_list(mid));
}
list_ele_t *my_merge_sort(list_ele_t *l1, list_ele_t *l2)
{
    list_ele_t *dummy;
    if (strcmp(l1->value, l2->value) > 0) {
        dummy = l2;
        l2 = l2->next;
    } else {
        dummy = l1;
        l1 = l1->next;
    }
    list_ele_t *l_tail = dummy;
    while (l1 && l2) {
        if (strcmp(l1->value, l2->value) > 0) {
            l_tail->next = l2;
            l_tail = l_tail->next;
            l2 = l2->next;
        } else {
            l_tail->next = l1;
            l_tail = l_tail->next;
            l1 = l1->next;
        }
    }
    if (l1)
        l_tail->next = l1;
    else
        l_tail->next = l2;

    return dummy;
}
