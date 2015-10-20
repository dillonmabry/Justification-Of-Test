## Justification-Of-Test

### Program to justify paragraph text based on using Linked Lists in C

- Program reads in a text file
- Tokenizes each word in each line adding them to the Linked List
- Linked List is used by reading in a Node header 
- Linked List is analyzed and justified accordingly by calculating spaces and string lengths
- List is then printed out in the form of a justified paragraph

#### Known Issues
- Program has a tendency to segfault on the "Presidential" sample text file
- Program might be one or two characters off from actual justification in some files
- Multiple paragraphs result in odd spacing displacement in the first lines of each only

