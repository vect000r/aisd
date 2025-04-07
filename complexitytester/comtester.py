import matplotlib.pyplot as plt
import numpy as np

n = []
t = []

filename = input("Provide the tester with the name of the .txt file")
path_to_file = "../lab14/complexitytests/setHashedResults/" + filename

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
plt.savefig("plots/2/setHashedUnion.png")