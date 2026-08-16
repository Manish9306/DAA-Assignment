# Algorithm

1. **Seed Random Number Generator:** Initialize the pseudo-random number generator in `main` using `srand(time(NULL))` to ensure different random sequences on every run.
2. **Define Simulation Function:** Create a `simulate_coin` helper function that accepts `num_tosses` and a floating-point `bias`.
3. **Simulate Coin Tosses:** Inside `simulate_coin`, run a `for` loop for `num_tosses` iterations. In each iteration, generate a random value between `0.0` and `1.0` using `(double)rand() / RAND_MAX`.
4. **Track Outcomes:** Increment `heads_count` whenever the generated random value is strictly less than `bias`.
5. **Calculate Probability:** Divide `heads_count` by `num_tosses` to calculate and return the simulated probability.
6. **Execute Experiments:** In `main`, call `simulate_coin` three times using different bias values (`0.50`, `0.75`, `0.10`) for 1,000,000 trials each, and print the resulting probabilities.

---

# Complexity

* **Time Complexity: O(N)** — Where *N* is the total number of coin tosses performed across all simulation runs (3 × 1,000,000 iterations). Each iteration executes constant-time **O(1)** operations.
* **Space Complexity: O(1)** — Operates in constant auxiliary memory using only primitive scalar variables allocated on the stack.
