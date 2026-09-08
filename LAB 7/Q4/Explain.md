**Question 4: Security Switches**

**Algorithm**:
* Number the switches 1 to n from right to left[cite: 4].
* Manipulate the rightmost switch (Switch 1) freely[cite: 4].
* Toggle any other switch 'k' only if switch k-1 is ON and all switches 1 to k-2 are OFF[cite: 4].
* Use mutual recursion where turning off switch 'k' involves turning off k-2, toggling k, turning on k-2, and turning off k-1[cite: 4].

**Time Complexity**: 
* Theta(2^n)[cite: 4].
