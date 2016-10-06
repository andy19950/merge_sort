#include"merge.h"
#include<stdlib.h>

node_t *findMid(node_t *source)
{
    node_t *fast, *slow;
    if (source==NULL || source->next==NULL)
        return NULL;
    slow = source;
    fast = source->next;

    while (fast && fast->next) {
        fast = fast->next->next;
        slow = slow->next;
    }
    fast = slow->next;
    slow->next = NULL;
    return fast;
}

node_t *SortedMerge(node_t *a, node_t *b)
{
    node_t *result = NULL;

    /* Base cases */
    if (a == NULL)
        return b;
    else if (b == NULL)
        return a;

    /* Pick either a or b, and recur */
    if (a->data <= b->data) {
        result = a;
        result->next = SortedMerge(a->next, b);
    } else {
        result = b;
        result->next = SortedMerge(a, b->next);
    }
    return result;
}

node_t *MergeSort(node_t *head)
{
    node_t *a;
    node_t *b;

    /* length 0 or 1 */
    if ((head == NULL) || (head->next ==NULL))
        return head;

    a = head;
    b = findMid(head);

    a = MergeSort(a);
    b = MergeSort(b);

    head = SortedMerge(a, b);
    return head;
}

node_t *insert(node_t *head, int data)
{
    node_t *new_node = (node_t *) malloc (sizeof(node_t));
    new_node->data = data;
    new_node->next = head;
    head = new_node;

    return head;
}
