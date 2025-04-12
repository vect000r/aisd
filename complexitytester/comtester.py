import matplotlib.pyplot as plt
import numpy as np
import os
from collections import defaultdict
from scipy.ndimage import uniform_filter1d

plt.style.use("seaborn-v0_8-muted")

# --- Helper functions ---

def remove_outliers(x, y, z_thresh=2.5):
    x = np.array(x)
    y = np.array(y)
    z_scores = np.abs((y - np.mean(y)) / np.std(y))
    mask = z_scores < z_thresh
    return x[mask], y[mask]

def average_by_x(x, y):
    grouped = defaultdict(list)
    for xi, yi in zip(x, y):
        grouped[xi].append(yi)
    x_avg = []
    y_avg = []
    for xi in sorted(grouped.keys()):
        x_avg.append(xi)
        y_avg.append(np.mean(grouped[xi]))
    return np.array(x_avg), np.array(y_avg)

def smooth(y, window_size=5):
    return uniform_filter1d(y, size=window_size)

def get_expected_curve(x, complexity_type):
    x_safe = np.where(x == 0, 1, x)
    if complexity_type == "O(1)":
        return np.ones_like(x)
    elif complexity_type == "O(log n)":
        return np.log2(x_safe)
    elif complexity_type == "O(n)":
        return x
    elif complexity_type == "O(n log n)":
        return x * np.log2(x_safe)
    elif complexity_type == "O(n^2)":
        return x**2
    elif complexity_type == "O(n^3)":
        return x**3
    else:
        return None

# --- User input ---

lab_dir = input("Choose lab directory (lab13, lab14, lab15): ").strip()
while lab_dir not in ["lab13", "lab14", "lab15"]:
    print("Invalid input. Please enter: lab13, lab14, or lab15.")
    lab_dir = input("Choose lab directory (lab13, lab14, lab15): ").strip()

test_dir = input("Enter the specific directory inside 'complexitytests' (e.g. setHashedResults): ").strip()
filename = input("Enter the name of the .txt file (e.g. data.txt): ").strip()
path_to_file = os.path.join("..", lab_dir, "complexitytests", test_dir, filename)

output_plot = input("Enter the name of the output plot (e.g. plot.png): ").strip()
output_path = os.path.join("plots", "2", output_plot)

complexity = input("Enter expected complexity (O(1), O(log n), O(n), O(n log n), O(n^2), O(n^3)): ").strip()

# --- Load data ---

n = []
t = []

with open(path_to_file, "r") as data:
    for line in data:
        numbers = line.split()
        n.append(int(numbers[0]))
        t.append(int(numbers[1]))

x_raw = np.array(n)
y_raw = np.array(t)

# --- Clean and process ---

x_clean, y_clean = remove_outliers(x_raw, y_raw)
x_avg, y_avg = average_by_x(x_clean, y_clean)
y_smooth = smooth(y_avg)

# Expected curve
expected_y = get_expected_curve(x_avg, complexity)
if expected_y is not None:
    expected_y = expected_y / np.max(expected_y) * np.max(y_smooth)

# --- Plot ---

fig, ax = plt.subplots(figsize=(10, 6))

ax.plot(x_avg, y_smooth, label="Actual (Averaged + Smoothed)", color="#1f77b4", linewidth=2)
if expected_y is not None:
    ax.plot(x_avg, expected_y, label=f"Expected {complexity}", linestyle='--', color='orange', linewidth=2)

ax.set_xlabel("Input Size (n)", fontsize=12)
ax.set_ylabel("Time", fontsize=12)
ax.set_title(f"Complexity Comparison for {filename}", fontsize=14)
ax.grid(True, linestyle='--', alpha=0.5)
ax.legend(frameon=True)
fig.tight_layout()

plt.savefig(output_path)

