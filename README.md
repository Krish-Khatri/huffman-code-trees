# huffman-code-trees
A program that reads a plain text file, computes a Huffman code tree for that text file, and writes out the encoded version of the text.
The program will:

   • Read the text from the file given as a command-line
     argument. No more than 100,000 characters are in the
     file.
     
   • Compute the number of occurrences of each character in the file,
     and each character (and its frequency)will be placed a new tree node.
     
   • Build the Huffman Code Tree using the heap. 
   
   • Write the pre-order traversal of the Huffman code tree to the file
     “preorder1.txt” and the in-order traversal to the file “inorder1.txt”. As it
     writes out the nodes in the traversal, it will write each node on a line. If the node is
     an internal node, then write an ‘i’ followed by the integer for that node. If the
     node is a leaf, write an ‘s’ followed be the ascii values of the letter(s)
     represented by that node. 
     
     
   • Construct a table containing the encoding for each character, storing the
     encoding as a string.
     
   • Encode the original text, writing the encoded version to “code1.txt”. This file
     contains ASCII ‘0’ and ‘1’ characters (much easier to debug)
     
   • Lastly, compute and write out the number of bits (0s and 1s) in the file above 
     to the standard output
    
    
The Huffman Tree was created using a binary heap data structure that uses an array and implements
insert and extract-min that run in O(lg N) time.



Example: 
Suppose that the file “foo.txt” contains the following text:
ALLALABAMAFOOTBALL
Then executing:
encode foo.txt
should produce output files such as the following. 

Standard Output (to the screen):
Phase 1 code length: 45 bits

preorder1.txt:
i 133
i 132
s 76
s 65
i 131
i 130
s 66
s 79
i 129
i 128
s 84
s 70
s 77

inorder1.txt:
s 76
i 132
s 65
i 133
s 66
i 130
s 79
i 131
s 84
i 128
s 70
i 129
s 77

code1.txt:
010000010001100011110111011011011100100010000
