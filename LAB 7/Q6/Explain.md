**Question 6: The Best Time to be Alive**

**Algorithm**:
* Convert each scientist's lifespan into two discrete events: a BIRTH event at their birth year and a DEATH event at their death year[cite: 6].
* Apply a tie-breaking rule for equal years where DEATH events must precede BIRTH events[cite: 6].
* Sort all 2N events by year in ascending order using a sweep-line approach[cite: 6].
* Traverse the sorted events to track the concurrently alive count and record the peak count and year[cite: 6].

**Time Complexity**: 
* O(N log N)[cite: 6].
