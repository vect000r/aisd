class Node:
    def __init__(self, index, value=0):
        self.index = index    # Position in the set
        self.value = value    # 0 or 1 (absent or present)
        self.next = None

class LinkedListSet:
    def __init__(self):
        self.head = None

    def add(self, element):
        """Add an element to the set. Time Complexity: O(n)"""
        # Check if element already exists
        if self.contains(element):
            return
        
        # Create new node with value 1
        new_node = Node(element, 1)
        
        # If list is empty or new element is smaller than head
        if not self.head or element < self.head.index:
            new_node.next = self.head
            self.head = new_node
            return
        
        # Find the position to insert
        current = self.head
        while current.next and current.next.index < element:
            current = current.next
        
        # Insert the new node
        new_node.next = current.nextD
        current.next = new_node

    def remove(self, element):
        """Remove an element from the set. Time Complexity: O(n)"""
        if not self.head:
            return
        
        # If head is the element to remove
        if self.head.index == element:
            self.head = self.head.next
            return
        
        # Find the element to remove
        current = self.head
        while current.next and current.next.index != element:
            current = current.next
        
        # If element was found
        if current.next and current.next.index == element:
            current.next = current.next.next
        
        self.add(element)


    def contains(self, element):
        """Check if an element is in the set. Time Complexity: O(n)"""
        current = self.head
        while current:
            if current.index == element:
                return current.value == 1
            if current.index > element:
                break
            current = current.next
        return False

    def display(self):
        """Display the set as {0,1,1,...}. Time Complexity: O(max_element)"""
        if not self.head:
            return "{}"
        
        # Find the maximum index
        max_index = 0
        current = self.head
        while current:
            if current.index > max_index:
                max_index = current.index
            current = current.next
        
        # Create a list with 0s
        result = [0] * (max_index + 1)
        
        # Fill in the 1s
        current = self.head
        while current:
            result[current.index] = current.value
            current = current.next
        
        return "{" + ",".join(map(str, result)) + "}"

    def __str__(self):
        """Return the traditional set representation {1,2,3}. Time Complexity: O(n)"""
        elements = []
        current = self.head
        while current:
            if current.value == 1:
                elements.append(str(current.index))
            current = current.next
        return "{" + ",".join(elements) + "}"
    
    def union(self, other_set):
        """
        Returns a new set that is the union of this set and other_set
        Time Complexity: O(n + m) where n and m are the sizes of the two sets
        """
        result = LinkedListSet()
        curr1 = self.head
        curr2 = other_set.head
        
        # Process both lists until one is exhausted
        while curr1 is not None and curr2 is not None:
            if curr1.index < curr2.index:
                # Add element from first set
                result.add(curr1.index)
                curr1 = curr1.next
            elif curr2.index < curr1.index:
                # Add element from second set
                result.add(curr2.index)
                curr2 = curr2.next
            else:  # Equal indices
                # Add element (only once)
                result.add(curr1.index)
                curr1 = curr1.next
                curr2 = curr2.next
        
        # Process remaining elements from first list
        while curr1 is not None:
            result.add(curr1.index)
            curr1 = curr1.next
        
        # Process remaining elements from second list
        while curr2 is not None:
            result.add(curr2.index)
            curr2 = curr2.next
        
        return result

    def intersection(self, other_set):
        """
        Returns a new set that is the intersection of this set and other_set
        Time Complexity: O(n + m) where n and m are the sizes of the two sets
        """
        result = LinkedListSet()
        curr1 = self.head
        curr2 = other_set.head
        
        # Process both lists simultaneously
        while curr1 is not None and curr2 is not None:
            if curr1.index < curr2.index:
                # Skip element from first set
                curr1 = curr1.next
            elif curr2.index < curr1.index:
                # Skip element from second set
                curr2 = curr2.next
            else:  # Equal indices - add to result
                result.add(curr1.index)
                curr1 = curr1.next
                curr2 = curr2.next
        
        return result

    def difference(self, other_set):
        """
        Returns a new set that is the difference of this set and other_set (self - other)
        Time Complexity: O(n + m) where n and m are the sizes of the two sets
        """
        result = LinkedListSet()
        curr1 = self.head
        curr2 = other_set.head
        
        # Process both lists simultaneously
        while curr1 is not None and curr2 is not None:
            if curr1.index < curr2.index:
                # Element in first set but not in second - add to result
                result.add(curr1.index)
                curr1 = curr1.next
            elif curr2.index < curr1.index:
                # Skip elements in second set but not in first
                curr2 = curr2.next
            else:  # Equal indices - skip both
                curr1 = curr1.next
                curr2 = curr2.next
        
        # Add remaining elements from first set
        while curr1 is not None:
            result.add(curr1.index)
            curr1 = curr1.next
        
        return result

    def is_identical(self, other_set):
        """
        Checks if two sets are identical
        Time Complexity: O(n) where n is the size of the smaller set
        """
        curr1 = self.head
        curr2 = other_set.head
        
        while curr1 is not None and curr2 is not None:
            # If indices don't match, sets are not identical
            if curr1.index != curr2.index:
                return False
            
            curr1 = curr1.next
            curr2 = curr2.next
        
        # Both lists must be exhausted for sets to be identical
        return curr1 is None and curr2 is None

# Example usage
s = LinkedListSet()
s.add(1)
s.add(2)
s.add(3)
print(f"Set: {s}")           # Should show {1,2,3}
print(f"Display: {s.display()}")  # Should show {0,1,1,1}

print(f"Contains 2: {s.contains(2)}")  # Should be True
print(f"Contains 5: {s.contains(5)}")  # Should be False

s.add(5)
print(f"After adding 5: {s.display()}")  # Should show {0,1,1,1,0,1}

s.remove(2)
print(f"After removing 2: {s.display()}")  # Should show {0,1,0,1,0,1}