/* Link list node */
typedef struct node {
    int data;
    struct node *next;
} node_t;

node_t *MergeSort(node_t *head);
node_t *SortedMerge(node_t *a, node_t *b);
node_t *findMid(node_t *source);
node_t *insert(node_t *head, int data);
