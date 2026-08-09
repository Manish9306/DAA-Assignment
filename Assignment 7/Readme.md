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
