/*1. Dictionary Operations: Consider a dictionary (D) abstract data type that permits access
to data items by content (key). The following are the primary operations that the dictionary
supports.

• Search(D, k) - Given a search key k, return a pointer to the elements in the dictionary
D whose key value is k, if one exists.
• Insert(D, x) - Given a data item x, add it to the Dictionary D.
• Delete(D, x) - Given a pointer x to a data item in the dictionary D, remove it from
D.
• Max(D) or Min(D) - Retrieve the item with the largest (or smallest) key from D.
These two operations help the dictionary to serve as a priority queue.
• Predecessor(D, x) or Successor(D, x) Retrieve the item from D whose key is immediately
before (or after) the item x in sorted order.

What are the asymptotic worst-case running times for all the seven primary operations
(search, insert, delete, maximum, minimum, predecessor, and successor) when the said
data structure is implemented using:
• An unsorted array.
• A sorted array.
• A singly linked unsorted list.
• A singly linked sorted list.
• A doubly linked unsorted list.
• A doubly linked sorted list.

Write a C program to validate your claim by plotting the order of growth of these functions*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 100 // Maximum size for array implementations


// DATA STRUCTURE DEFINITIONS


// Array Structures
typedef struct {
    int data[MAX];
    int size;
} UnsortedArray, SortedArray;

// Node structure for Linked Lists
typedef struct Node {
    int key;
    struct Node* prev;
    struct Node* next;
} Node;

// List Container Structures
typedef struct {
    Node* head;
    Node* tail;
} List;


// 1. UNSORTED ARRAY IMPLEMENTATION


int search_unsorted_array(UnsortedArray* arr, int k) {
    for (int i = 0; i < arr->size; i++) {
        if (arr->data[i] == k) return i; // Return index
    }
    return -1;
}

void insert_unsorted_array(UnsortedArray* arr, int x) {
    if (arr->size < MAX) {
        arr->data[arr->size++] = x; // Place at end: O(1)
    }
}

void delete_unsorted_array(UnsortedArray* arr, int index) {
    if (index >= 0 && index < arr->size) {
        arr->data[index] = arr->data[arr->size - 1]; // Swap with last element: O(1)
        arr->size--;
    }
}



// 2. SORTED ARRAY IMPLEMENTATION


int search_sorted_array(SortedArray* arr, int k) {
    int low = 0, high = arr->size - 1;
    while (low <= high) { // Binary Search: O(log n)
        int mid = low + (high - low) / 2;
        if (arr->data[mid] == k) return mid;
        if (arr->data[mid] < k) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

void insert_sorted_array(SortedArray* arr, int x) {
    if (arr->size >= MAX) return;
    int i = arr->size - 1;
    while (i >= 0 && arr->data[i] > x) { // Shift elements right: O(n)
        arr->data[i + 1] = arr->data[i];
        i--;
    }
    arr->data[i + 1] = x;
    arr->size++;
}

void delete_sorted_array(SortedArray* arr, int index) {
    if (index >= 0 && index < arr->size) {
        for (int i = index; i < arr->size - 1; i++) { // Shift elements left: O(n)
            arr->data[i] = arr->data[i + 1];
        }
        arr->size--;
    }
}


// 3 & 4. SINGLY LINKED LISTS (Unsorted & Sorted)


Node* create_node(int key) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->key = key;
    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;
}

// Singly Linked List Delete: Requires finding predecessor -> O(n)
void delete_singly_linked(List* list, Node* x) {
    if (!list->head || !x) return;

    if (list->head == x) {
        list->head = x->next;
        if (list->tail == x) list->tail = NULL;
        free(x);
        return;
    }

    Node* curr = list->head;
    while (curr && curr->next != x) { // Traverse to find predecessor node
        curr = curr->next;
    }

    if (curr) {
        curr->next = x->next;
        if (list->tail == x) list->tail = curr;
        free(x);
    }
}

// Singly Linked Sorted Predecessor: Must traverse from head -> O(n)
Node* predecessor_singly_sorted(List* list, Node* x) {
    if (list->head == x) return NULL;
    Node* curr = list->head;
    while (curr && curr->next != x) {
        curr = curr->next;
    }
    return curr;
}



// 5 & 6. DOUBLY LINKED LISTS (Unsorted & Sorted)


// Doubly Linked List Delete: Direct pointer update -> O(1)
void delete_doubly_linked(List* list, Node* x) {
    if (!list->head || !x) return;

    if (x->prev) x->prev->next = x->next;
    else list->head = x->next;

    if (x->next) x->next->prev = x->prev;
    else list->tail = x->prev;

    free(x);
}

// Doubly Linked Sorted Insert -> O(n) traversal, O(1) pointer shifts
void insert_doubly_sorted(List* list, int x) {
    Node* new_node = create_node(x);
    if (!list->head || list->head->key >= x) {
        new_node->next = list->head;
        if (list->head) list->head->prev = new_node;
        list->head = new_node;
        if (!list->tail) list->tail = new_node;
        return;
    }

    Node* curr = list->head;
    while (curr->next && curr->next->key < x) {
        curr = curr->next;
    }

    new_node->next = curr->next;
    new_node->prev = curr;
    if (curr->next) curr->next->prev = new_node;
    else list->tail = new_node;
    curr->next = new_node;
}



// HELPER PRINT FUNCTIONS


void print_array(int arr[], int size) {
    printf("[ ");
    for (int i = 0; i < size; i++) printf("%d ", arr[i]);
    printf("]\n");
}

void print_list(List* list) {
    Node* curr = list->head;
    printf("[ ");
    while (curr) {
        printf("%d ", curr->key);
        curr = curr->next;
    }
    printf("]\n");
}



// MAIN DEMO FUNCTION

int main() {
    printf("--- 1. UNSORTED ARRAY DEMO ---\n");
    UnsortedArray u_arr = {.size = 0};
    insert_unsorted_array(&u_arr, 40);
    insert_unsorted_array(&u_arr, 10);
    insert_unsorted_array(&u_arr, 30);
    printf("Unsorted Array: "); print_array(u_arr.data, u_arr.size);
    delete_unsorted_array(&u_arr, 0); // Deletes '40' in O(1) by swapping with '30'
    printf("After deleting index 0 (O(1) swap): "); print_array(u_arr.data, u_arr.size);

    printf("\n--- 2. SORTED ARRAY DEMO ---\n");
    SortedArray s_arr = {.size = 0};
    insert_sorted_array(&s_arr, 40);
    insert_sorted_array(&s_arr, 10);
    insert_sorted_array(&s_arr, 30);
    printf("Sorted Array: "); print_array(s_arr.data, s_arr.size);
    printf("Binary Search for 30: Index %d\n", search_sorted_array(&s_arr, 30));

    printf("\n--- 3. DOUBLY LINKED SORTED LIST DEMO ---\n");
    List dll = {NULL, NULL};
    insert_doubly_sorted(&dll, 50);
    insert_doubly_sorted(&dll, 20);
    insert_doubly_sorted(&dll, 35);
    printf("Doubly Linked Sorted List: "); print_list(&dll);
    
    printf("Min (Head): %d, Max (Tail): %d\n", dll.head->key, dll.tail->key);
    
    Node* target = dll.head->next; // Pointing to node with key 35
    printf("Target Node Key: %d\n", target->key);
    if (target->prev) printf("Predecessor (O(1) via prev): %d\n", target->prev->key);
    if (target->next) printf("Successor (O(1) via next): %d\n", target->next->key);

    delete_doubly_linked(&dll, target); // Delete node '35' in O(1)
    printf("After deleting node 35 (O(1)): "); print_list(&dll);

    return 0;
}
