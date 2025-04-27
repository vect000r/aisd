class HashedSet:
    def __init__(self, bucket_count=10):
        self.bucket_count = bucket_count
        self.buckets = [[] for _ in range(bucket_count)]

    def hash(self, element):
        """Hash function to map elements to bucket indices."""
        return hash(element) % self.bucket_count
    
    def add(self, element):
        """Add an element to the set. Time Complexity: O(1) on average."""
        bucket_index = self.hash(element)
        if element not in self.buckets[bucket_index]:
            self.buckets[bucket_index].append(element)
        
    def remove(self, element):
        """Remove an element from the set. Time Complexity: O(1) on average."""
        bucket_index = self.hash(element)
        if element in self.buckets[bucket_index]:
            self.buckets[bucket_index].remove(element)
    
    def contains(self, element):
        """Check if an element is in the set. Time Complexity: O(1) on average."""
        bucket_index = self.hash(element)
        return element in self.buckets[bucket_index]
    
    def display(self):
        """Display the contents of the set."""
        for i, bucket in enumerate(self.buckets):
            print(f"Bucket {i}: {bucket}")
    
# Example usage

hashed = HashedSet()
hashed.add(1)
hashed.add(2)
hashed.add(3)
hashed.add(11)  # This will go to the same bucket as 1 if bucket_count is 10
hashed.add(12)  # This will go to the same bucket as 2 if bucket_count is 10
hashed.add(13)  # This will go to the same bucket as 3 if bucket_count is 10
hashed.display()  # Should show the contents of each bucket
print(f"Contains 2: {hashed.contains(2)}")  # Should be True
print(f"Contains 5: {hashed.contains(5)}")  # Should be False
hashed.remove(2)
print(f"After removing 2: {hashed.contains(2)}")  # Should be False
hashed.display()  # Should show the contents of each bucket without 2