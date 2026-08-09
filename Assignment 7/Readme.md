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
