class Node:
    def __init__(self, index, value=0):
        self.index = index
        self.value = value
        self.next = None


class LinkedList:
    def __init__(self):
        self.head = None
    
    def contains(self, element):
        if self.head == None:
            return False

        current = self.head
        while current:
            if current.index == element:
                return current.value == 1 # if an element is in the set then this will return true, otherwise false
            if current.index > element:
                break   # if we moved to the index past the one we are looking for, stop
            current = current.next

        return False # if we jump out of the loop, then we moved past the indexes where the element should have been, so return false 
    
    def add(self, element):
        if self.contains(element):
            return # if an element is already in the set, then return nothing, jump out of the function
        
        new_node = Node(element, 1) # we create a new node with value of 1 

        # if list is empty or the element should be before the head, then we make the element the new head
        if not self.head or element < self.head.index:
            new_node.next = self.head
            self.head = new_node
            return
        
        current = self.head
        while current.next and current.next.index < element:
            current = current.next
        
        new_node.next = current.next
        current.next = new_node

    def remove(self, element):
        if not self.contains(element):
            return # nothing to remove 

        if self.head.index == element and self.head.value == 1:
            # the element we need to remove is the head
            self.head = self.head.next
            return        
        
        # search for the right index and disconnect the node that has the index of the element
        current = self.head
        while current.next and current.next.index < element:
            current = current.next
        
        if current.next and current.next.index == element:
            current.next = current.next.next

    