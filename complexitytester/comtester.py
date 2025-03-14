import matplotlib

n = []
t = []

with open("DATASL.txt", "r") as data:
    for line in data:
        numbers = line.split()
        n.append(int(numbers[0]))
        t.append(int(numbers[1]))

print(n)