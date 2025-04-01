class BinaryHeap:
    def __init__(self):
        self.items = [0]
    
    def __len__(self):
        return len(self.items) - 1
    
    def insert(self, k):
        self.items.append(k)
        self.percolate_up()
    
    def percolate_up(self):
        i = len(self)
        while i // 2 > 0:
            if self.items[i] < self.items[i // 2]:
                self.items[i // 2], self.items[i] = self.items[i], self.items[i // 2]
            i = i // 2

    def addElements(self):
        self.insert(5)
        self.insert(7)
        self.insert(11)
        self.insert(14)
        self.insert(9)
    
    def min_child(self, i):
        if i * 2 + 1 > len(self):
            return i * 2 

        if self.items[i * 2] < self.items[i * 2 + 1]:
            return i * 2
        
        return i * 2 + 1


    def percolate_down(self, i):
        while i * 2 <= len(self):
            mc = self.min_child(i)
            if self.items[i]> self.items[mc]:
                self.items[i], self.items[mc] = self.items[mc], self.items[i]
            i = mc

    def del_min(self):
        return_value = self.items[1]
        self.items[1] = self.items[len(self)]
        self.items.pop()
        self.percolate_down(1)
        return return_value

bh = BinaryHeap()
bh.addElements()
print(bh.items)