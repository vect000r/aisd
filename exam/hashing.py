class SetHashed:
    def __init__(self, max_element=100):
        # Inicjalizujemy pustą tablicę z zerami
        # max_element określa maksymalny indeks w zbiorze
        self.elements = [0] * (max_element + 1)
    
    def add(self, x):
        # Dodajemy element x do zbioru
        if 0 <= x < len(self.elements):
            self.elements[x] = 1
        else:
            raise ValueError(f"Element {x} poza zakresem zbioru")
    
    def remove(self, x):
        # Usuwamy element x ze zbioru
        if 0 <= x < len(self.elements):
            self.elements[x] = 0
        else:
            raise ValueError(f"Element {x} poza zakresem zbioru")
    
    def contains(self, x):
        # Sprawdzamy czy element x należy do zbioru
        if 0 <= x < len(self.elements):
            return self.elements[x] == 1
        return False
    
    def union(self, other):
        # Suma zbiorów A ∪ B
        result = SetHashed(max(len(self.elements), len(other.elements)) - 1)
        
        for i in range(len(result.elements)):
            # Element należy do sumy zbiorów, jeśli należy do A lub B
            if (i < len(self.elements) and self.elements[i] == 1) or \
               (i < len(other.elements) and other.elements[i] == 1):
                result.elements[i] = 1
                
        return result
    
    def intersection(self, other):
        # Część wspólna zbiorów A ∩ B
        result = SetHashed(max(len(self.elements), len(other.elements)) - 1)
        
        for i in range(min(len(self.elements), len(other.elements))):
            # Element należy do części wspólnej, jeśli należy do A i B
            if self.elements[i] == 1 and other.elements[i] == 1:
                result.elements[i] = 1
                
        return result
    
    def difference(self, other):
        # Różnica zbiorów A - B
        result = SetHashed(len(self.elements) - 1)
        
        for i in range(len(self.elements)):
            # Element należy do różnicy, jeśli należy do A i nie należy do B
            if self.elements[i] == 1 and (i >= len(other.elements) or other.elements[i] == 0):
                result.elements[i] = 1
                
        return result
    
    def equals(self, other):
        # Sprawdzanie identyczności zbiorów A = B
        max_len = max(len(self.elements), len(other.elements))
        
        for i in range(max_len):
            a_has = i < len(self.elements) and self.elements[i] == 1
            b_has = i < len(other.elements) and other.elements[i] == 1
            
            if a_has != b_has:
                return False
                
        return True
    
    def __str__(self):
        # Reprezentacja tekstowa zbioru
        elements = [i for i, value in enumerate(self.elements) if value == 1]
        return f"{elements}"