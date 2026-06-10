#include <stdio.h>
#include <string.h>

typedef struct {
    char id;
    int pr;
} Job;

Job heap[100];
int size =0;

/* swap two jobs */
void  swap(int a, int b) {
    Job temp = heap[a];
    heap[a] = heap[b];
    heap[b] = temp;
}

/* move node up (heapify up) */
void moveUp(int i) {
    int par = (i - 1) / 2;

    while (i > 0 && heap[i].pr > heap[par].pr) {
        swap(i, par);
        i = par;
        par = (i - 1) / 2;
    }
}

/* move node down (heapify down) */
void moveDown(int i) {
    int left, right, big;

    while (1) {
        left = 2 * i + 1;
        right = 2 * i + 2;
        big = i;

        if (left < size && heap[left].pr > heap[big].pr)
            big = left;

        if (right < size && heap[right].pr > heap[big].pr)
            big = right;

        if (big == i) break;

        swap(i, big);
        i = big;
    }
}

/* build heap from array */
void buildHeap() {
    for (int i = (size / 2) - 1; i >= 0; i--) {
        moveDown(i);
    }
}

/* insert job */
void addJob(char id, int pr) {
    heap[size].id = id;
    heap[size].pr = pr;
    size++;
    moveUp(size - 1);
}

/* remove top (max priority) */
void removeTop() {
    if (size == 0) return;

    heap[0] = heap[size - 1];
    size--;
    moveDown(0);
}

/* print heap as a normal top-down tree with branches */
void showHeapTree() {
    if (size == 0) return;

    /* how many levels does the tree have? */
    int height = 0;
    int n = size;
    while (n > 0) {
        height++;
        n /= 2;
    }

    /* number of leaf slots on the bottom level */
    int leaves = 1;
    for (int i = 0; i < height - 1; i++)
        leaves *= 2;

    int nodeWidth = 6;              /* space reserved for one node, e.g. "U(100)" */
    int width = leaves * nodeWidth;

    for (int level = 0; level < height; level++) {

        int nodesInLevel = 1;
        for (int i = 0; i < level; i++)
            nodesInLevel *= 2;

        int slot = width / nodesInLevel;

        /* line with the node values */
        char line[100];
        for (int i = 0; i < width; i++)
            line[i] = ' ';
        line[width] = '\0';

        for (int p = 0; p < nodesInLevel; p++) {
            int idx = nodesInLevel - 1 + p;
            if (idx >= size) continue;

            char text[10];
            sprintf(text, "%c(%d)", heap[idx].id, heap[idx].pr);

            int center = p * slot + slot / 2;
            int start = center - strlen(text) / 2;

            for (int k = 0; text[k] != '\0'; k++)
                line[start + k] = text[k];
        }
        printf("%s\n", line);

        /* line with the / and \ branches to the children */
        if (level < height - 1) {
            char branch[100];
            for (int i = 0; i < width; i++)
                branch[i] = ' ';
            branch[width] = '\0';

            int childSlot = slot / 2;

            for (int p = 0; p < nodesInLevel; p++) {
                int idx = nodesInLevel - 1 + p;
                int center = p * slot + slot / 2;

                int left = 2 * idx + 1;
                int right = 2 * idx + 2;

                if (left < size) {
                    int leftCenter = (2 * p) * childSlot + childSlot / 2;
                    branch[(center + leftCenter) / 2] = '/';
                }
                if (right < size) {
                    int rightCenter = (2 * p + 1) * childSlot + childSlot / 2;
                    branch[(center + rightCenter) / 2] = '\\';
                }
            }
            printf("%s\n", branch);
        }
    }
    printf("\n");
}

int main() {

    int P[] = {42, 17, 93, 28, 65, 81, 54, 60, 99, 73, 88};
    int n = 11;

    /* Step 1: build initial heap with IDs A-K */
    for (int i = 0; i < n; i++) {
        heap[i].id = 'A' + i;
        heap[i].pr = P[i];
    }

    size = n;

    buildHeap();
    printf("\nAfter building Max-Heap:\n");
    showHeapTree();

    /* Step 2: insert urgent job (priority 100) */
    addJob('U', 100);
    printf("\nAfter inserting 100:\n");
    showHeapTree();

    /* Step 3: remove urgent job (100) */
    removeTop();
    printf("\nAfter removing 100:\n");
    showHeapTree();

    return 0;
}