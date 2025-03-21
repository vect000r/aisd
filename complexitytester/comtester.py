import matplotlib.pyplot as plt
import numpy as np

n = []
t = []

path_to_file = input("Provide the tester with the path to the .txt file, eg. ../lab13/complexitytests/setSimpleResults/add_results.txt")



with open(f"{path_to_file}", "r") as data:
    for line in data:
        numbers = line.split()
        n.append(int(numbers[0]))
        t.append(int(numbers[1]))

print(n)
print(t)

x = np.array(n)
y = np.array(t)

plt.plot(x, y)
plt.savefig("plots/1")