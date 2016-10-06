#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<assert.h>

#ifdef BUBBLE
#include "bubble.h"
#else
#include "merge.h"
#endif


static double diff_in_second(struct timespec t1, struct timespec t2)
{
    struct timespec diff;
    if (t2.tv_nsec-t1.tv_nsec < 0) {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
    } else {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
    return (diff.tv_sec + diff.tv_nsec / 1000000000.0);
}

int check(node_t *head)
{
    node_t *current = head;
    int min = current->data;
    current = current->next;
    while(current) {
        if(min > current->data) return 0;
        min = current->data;
        current = current->next;
    }
    return 1;
}

int main()
{
    struct timespec start, end;
    double cpu_time;
    FILE *fp;
    srand(time(NULL));
    node_t *head;
#ifdef BUBBLE
    fp = fopen("bubble.txt", "w");
#else
    fp = fopen("merge.txt", "w");
#endif
    for(int j=1; j<=10; j++) {
        head = NULL;
        for(int i=0; i<=1000*j; i++)
            head = insert(head, rand()%1000);
#ifdef BUBBLE
        clock_gettime(CLOCK_REALTIME, &start);
        head = sort(head);
        clock_gettime(CLOCK_REALTIME, &end);
        cpu_time = diff_in_second(start,end);
        assert(check(head) && "Linked list is not sorted!!\n");
        fprintf(fp, "%d %.4lf\n", j*1000, cpu_time);
#else
        clock_gettime(CLOCK_REALTIME, &start);
        head = MergeSort(head);
        clock_gettime(CLOCK_REALTIME, &end);
        cpu_time = diff_in_second(start, end);
        assert(check(head) && "Linked list is not sorted!!\n");
        fprintf(fp, "%d %.4lf\n", j*1000, cpu_time);
#endif
    }
    fclose(fp);
    return 0;
}
