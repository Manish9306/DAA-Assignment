import pandas as pd
import matplotlib.pyplot as plt

# Read experimental data
data = pd.read_csv("special_matrix_data.csv")

print("\nSpecial-Pattern Matrix Multiplication Data")
print("------------------------------------------")
print(data)


# Plot total operations
plt.figure(figsize=(10, 6))

plt.plot(
    data["n"],
    data["total_operations"],
    marker="o",
    label="Actual Total Operations"
)

plt.plot(
    data["n"],
    data["n_squared"],
    marker="s",
    linestyle="--",
    label=r"Theoretical $O(n^2)$"
)

plt.xlabel("Matrix Size (n × n)")
plt.ylabel("Number of Operations")

plt.title(
    "Special-Pattern Matrix Multiplication "
    "using Divide and Conquer"
)

plt.legend()
plt.grid(True)

plt.tight_layout()

# Save graph
plt.savefig(
    "special_matrix_graph.png",
    dpi=300
)

# Display graph
plt.show()