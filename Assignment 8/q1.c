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

/*

ALGORITHMS FOR DICTIONARY ADT OPERATIONS


1. UNSORTED ARRAY
• Search(D, k): Perform a linear scan from index 0 to n-1. Return index if key matches, else NULL.
• Insert(D, x): Append item x at index n. Increment size n.
• Delete(D, x): Swap item x with element at index n-1. Decrement size n.
• Min(D) / Max(D): Iterate through the array tracking the minimum/maximum element seen so far.
• Predecessor(D, x) / Successor(D, x): Scan full array to find the item with largest key < x.key (or smallest key > x.key).

2. SORTED ARRAY
• Search(D, k): Perform Binary Search on array bounds [0, n-1]. Return index if found, else NULL.
• Insert(D, x): Find sorted insertion point via binary search, shift elements right by 1, insert x.
• Delete(D, x): Shift all elements to the right of index x left by 1 position. Decrement size n.
• Min(D) / Max(D): Return element at D[0] for Min, or D[n-1] for Max.
• Predecessor(D, x) / Successor(D, x): Return D[index(x) - 1] for Predecessor, or D[index(x) + 1] for Successor.

3. SINGLY LINKED UNSORTED LIST
• Search(D, k): Traverse list from head to tail. Return node matching key k.
• Insert(D, x): Set x.next = head, then set head = x.
• Delete(D, x): Traverse from head to find predecessor node p where p.next == x. Set p.next = x.next, free(x).
• Min(D) / Max(D): Traverse list from head to tail while keeping track of min/max key node.
• Predecessor(D, x) / Successor(D, x): Traverse list to find node with largest key < x.key (or smallest key > x.key).

4. SINGLY LINKED SORTED LIST
• Search(D, k): Traverse list until node key >= k. Return node if key == k, else NULL.
• Insert(D, x): Traverse list to find position where curr.key < x.key < curr.next.key. Insert node x between them.
• Delete(D, x): Traverse from head to find node p where p.next == x. Set p.next = x.next, free(x).
• Min(D) / Max(D): Return head for Min, and tail for Max.
• Predecessor(D, x): Traverse from head to locate node p whose next pointer points to x (p.next == x).
• Successor(D, x): Return x.next.

5. DOUBLY LINKED UNSORTED LIST
• Search(D, k): Traverse nodes from head to tail to locate key k.
• Insert(D, x): Insert node x at the head. Update x.next and head.prev pointers.
• Delete(D, x): Update pointers directly: x.prev.next = x.next and x.next.prev = x.prev, free(x).
• Min(D) / Max(D): Traverse full list from head to tail tracking min/max key node.
• Predecessor(D, x) / Successor(D, x): Traverse full list to find node with largest key < x.key (or smallest key > x.key).

6. DOUBLY LINKED SORTED LIST
• Search(D, k): Traverse list stopping when node key >= k. Return node if key matches.
• Insert(D, x): Traverse list to find correct sorted spot, adjust 4 pointers (prev and next for adjacent nodes).
• Delete(D, x): Update pointers directly: x.prev.next = x.next and x.next.prev = x.prev, free(x).
• Min(D) / Max(D): Return head for Min, and tail for Max.
• Predecessor(D, x): Return x.prev.
• Successor(D, x): Return x.next.*/

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

/*

WORST-CASE TIME COMPLEXITIES (BIG-O) FOR DICTIONARY ADT


1. UNSORTED ARRAY
• Search(D, k):             O(n)   - Requires linear search through the array.
• Insert(D, x):             O(1)   - Placed at the end (index n) in constant time.
• Delete(D, x):             O(1)   - Overwrite element at x with last element and decrement size.
• Min(D) / Max(D):          O(n)   - Must scan all n elements to find min/max.
• Predecessor / Successor:   O(n)   - Must scan all n elements to find immediate neighbor value.

2. SORTED ARRAY
• Search(D, k):             O(log n) - Binary Search on sorted range.
• Insert(D, x):             O(n)   - Binary search + shifting up to n elements to maintain order.
• Delete(D, x):             O(n)   - Shifting up to n elements left to close the gap.
• Min(D) / Max(D):          O(1)   - Direct access to D[0] for Min, D[n-1] for Max.
• Predecessor / Successor:   O(1)   - Direct access to D[idx-1] for Pred, D[idx+1] for Succ.

3. SINGLY LINKED UNSORTED LIST
• Search(D, k):             O(n)   - Linear traversal from head to tail.
• Insert(D, x):             O(1)   - Prepended at head in constant time.
• Delete(D, x):             O(n)   - Must traverse from head to find x's predecessor node.
• Min(D) / Max(D):          O(n)   - Must scan all n nodes.
• Predecessor / Successor:   O(n)   - Must scan all n nodes to find relative neighbor key.

4. SINGLY LINKED SORTED LIST
• Search(D, k):             O(n)   - Linear search (can stop early, but still O(n) worst-case).
• Insert(D, x):             O(n)   - Linear traversal to find insertion spot + O(1) pointer updates.
• Delete(D, x):             O(n)   - Must traverse from head to find predecessor node.
• Min(D) / Max(D):          O(1)   - Head is Min; Tail (if tracked) is Max.
• Predecessor(D, x):        O(n)   - Cannot traverse backward; must find node p where p.next == x.
• Successor(D, x):          O(1)   - Direct access via x.next pointer.

5. DOUBLY LINKED UNSORTED LIST
• Search(D, k):             O(n)   - Linear traversal from head to tail.
• Insert(D, x):             O(1)   - Inserted at head in constant time.
• Delete(D, x):             O(1)   - Direct pointer updates using x.prev and x.next.
• Min(D) / Max(D):          O(n)   - Must scan all n nodes.
• Predecessor / Successor:   O(n)   - Must scan all n nodes to find relative neighbor key.

6. DOUBLY LINKED SORTED LIST
• Search(D, k):             O(n)   - Linear search through sorted nodes.
• Insert(D, x):             O(n)   - Traversal to find correct spot + O(1) 4-pointer adjustments.
• Delete(D, x):             O(1)   - Direct pointer updates using x.prev and x.next.
• Min(D) / Max(D):          O(1)   - Head is Min; Tail is Max.
• Predecessor(D, x):        O(1)   - Direct access via x.prev pointer.
• Successor(D, x):          O(1)   - Direct access via x.next pointer.*/