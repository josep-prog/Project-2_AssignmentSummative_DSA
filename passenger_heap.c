#include <stdio.h>
#include <string.h>

#define MAX 20

typedef struct {
    char name[20];
    int risk;
} Passenger;

Passenger heap[MAX];
int size = 0;

// Swap two passengers
void swap(Passenger *a, Passenger *b) {
    Passenger temp = *a;
    *a = *b;
    *b = temp;
}

// Fix heap downward
void fixHeap(int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && heap[left].risk > heap[largest].risk)
        largest = left;

    if (right < size && heap[right].risk > heap[largest].risk)
        largest = right;

    if (largest != i) {
        swap(&heap[i], &heap[largest]);
        fixHeap(largest);
    }
}

// Build Max Heap
void buildHeap() {
    for (int i = size / 2 - 1; i >= 0; i--) {
        fixHeap(i);
    }
}

// Insert passenger
void addPassenger(char name[], int risk) {
    strcpy(heap[size].name, name);
    heap[size].risk = risk;

    int i = size;
    size++;

    while (i > 0) {
        int parent = (i - 1) / 2;

        if (heap[parent].risk < heap[i].risk) {
            swap(&heap[parent], &heap[i]);
            i = parent;
        } else {
            break;
        }
    }
}

// Extract highest-risk passenger
Passenger getTop() {
    Passenger top = heap[0];

    heap[0] = heap[size - 1];
    size--;

    fixHeap(0);

    return top;
}

// Remove passenger by risk score
void removePassenger(int risk) {
    int index = -1;

    for (int i = 0; i < size; i++) {
        if (heap[i].risk == risk) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Passenger not found.\n");
        return;
    }

    heap[index] = heap[size - 1];
    size--;

    buildHeap();
}

// Display heap
void showHeap() {
    for (int i = 0; i < size; i++) {
        printf("%s(%d) ", heap[i].name, heap[i].risk);
    }
    printf("\n");
}

int main() {

    // Initial passengers
    addPassenger("Alice", 85);
    addPassenger("Brian", 60);
    addPassenger("Adeline", 92);
    addPassenger("Emanual", 70);
    addPassenger("Joseph", 55);
    addPassenger("Rerwa", 80);

    printf("Max Heap:\n");
    showHeap();

    // Extract priority queue
    printf("\nScreening Order (Highest Risk First):\n");

    Passenger temp[MAX];
    int tempSize = size;

    for (int i = 0; i < tempSize; i++) {
        temp[i] = getTop();
        printf("%s (%d)\n", temp[i].name, temp[i].risk);
    }

    // Restore heap
    size = 0;
    for (int i = 0; i < tempSize; i++) {
        addPassenger(temp[i].name, temp[i].risk);
    }

    // Insert new passenger
    printf("\nAdding passenger with risk 98:\n");
    addPassenger("NewPassenger", 98);
    showHeap();

    // Remove passenger with risk 98
    printf("\nRemoving passenger with risk 98:\n");
    removePassenger(98);
    showHeap();

    return 0;
}
