#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct charList
{
    char letter;
    int freq;
    struct charList *next;
} *head = NULL;

struct codeList
{
    char letter;
    string code;
    int sizeOfCode;
    struct codeList *next;
} *start = NULL;
// A Huffman tree node 
struct MinHeapNode
{
    char data; // One of the input characters
    int freq; // One of the input characters
    int counter;
    bool internalNode = false;
    struct MinHeapNode *left, *right; // Left and Right Child of this Node
};

// A Min Heap: Collection of 
// min heap (or Hufmman tree) nodes 
struct MinHeap
{
    unsigned size; // Current size of min heap
    unsigned capacity; // Capacity of min heap
    struct MinHeapNode** array; // Array of minheap node pointers
};
//A utility fuction to create a min heap of given capacity
struct MinHeap* createMinHeap(unsigned capacity)
{
    struct MinHeap* minHeap = new (struct MinHeap);
    minHeap -> size = 0;
    minHeap -> capacity = capacity;
    minHeap -> array = new MinHeapNode*[capacity];
    return minHeap;
}
//A utility function to swap two min heap nodes
void swapMinHeapNode(struct MinHeapNode **a, struct MinHeapNode **b)
{
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}
//A standard minHeapify function.
void minHeapify(struct MinHeap* minHeap, int idx)
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if((unsigned)left < minHeap -> size && minHeap->array[left]->
freq < minHeap->array[smallest]->freq) 
        smallest = left; 
  
    if ((unsigned)right < minHeap->size && minHeap->array[right]-> 
freq < minHeap->array[smallest]->freq) 
        smallest = right; 
  
    if (smallest != idx) { 
        swapMinHeapNode(&minHeap->array[smallest], 
                        &minHeap->array[idx]); 
        minHeapify(minHeap, smallest); 
    } 
}
//A standard function to build min heap
void buildMinHeap(struct MinHeap* minHeap)
{
    int n = minHeap -> size -1;
    int i;
    for(i = (n - 1) / 2; i >= 0; --i)
    {
        minHeapify(minHeap,i);
    }
}

//A utility function allocate a new min heap node with given
//character and frequency of the character
struct MinHeapNode* newNode(char data, unsigned freq)
{
    struct MinHeapNode* temp = new (struct MinHeapNode);
    temp -> left = temp -> right = NULL;
    temp -> data = data;
    temp -> freq = freq;
    return temp; 
}
// A utility function to insert 
// a new node to Min Heap 
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode) 
{ 
    ++minHeap->size; 
    int i = minHeap->size - 1; 
  
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) { 
  
        minHeap->array[i] = minHeap->array[(i - 1) / 2]; 
        i = (i - 1) / 2; 
    } 
  
    minHeap->array[i] = minHeapNode; 
} 
// A standard function to extract 
// minimum value node from heap 
struct MinHeapNode* extractMin(struct MinHeap* minHeap) 
{ 
  
    struct MinHeapNode* temp = minHeap->array[0]; 
    minHeap->array[0] 
        = minHeap->array[minHeap->size - 1]; 
  
    --minHeap->size; 
    minHeapify(minHeap, 0); 
  
    return temp; 
} 
//A utility function that finds the size of minheap
int isSizeOne(struct MinHeap* minHeap)
{
    return (minHeap -> size == 1);
}
//Creates a minheap of capacity equal to size
// and inserts all of data[] in min heap.
struct MinHeap* createandbuildMinHeap(char data[], int freq[], int size)
{
    struct MinHeap* minHeap = createMinHeap(size);
    for(int i = 0; i < size; ++i)
    {
        minHeap -> array[i] = newNode(data[i],freq[i]);
    }
    minHeap -> size = size;
    buildMinHeap(minHeap);

    return minHeap;
    
}

// Utility function to check if this node is leaf 
int isLeaf(struct MinHeapNode* root)   
{ 
  
    return !(root->left) && !(root->right); 
} 
  
struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size)
{
    struct MinHeapNode *left, *right, *top;

    //Create a min heap of capacity equal to the size.
    //No. of Nodes equal to size.
    struct MinHeap* minHeap = createandbuildMinHeap(data, freq, size);
    int counter = 0;
    //Iterate while size of heap isnt 1
    while(!isSizeOne(minHeap))
    {
        //Find the two minimum freq items from minheap
        left = extractMin(minHeap);
       // cout << left -> data << " " << left ->freq << endl;
        right = extractMin(minHeap);
        //cout << right -> data << " " << right ->freq << endl;
        //Create a new node with freq
        //equal to the sum of the two node frequencies.
        //Make the two nodes the left and right children
        //of this new node.
        //Add this node to the min heap
        //'$' is the special character for internal nodes, not used
        top = newNode('|', left ->freq + right -> freq);
        top -> left = left;
        top -> right = right;
        top -> internalNode = true;
        top -> counter = counter;
        counter++;

        insertMinHeap(minHeap,top);
    }
    
    //Remaning Node is the root node so return it.
    return extractMin(minHeap);
}
// Prints huffman codes from the root of Huffman Tree. 
// It uses string str  to store codes 
void printCodes(struct MinHeapNode* root, string str) 
{ 
    if(root == NULL)
        return;

    if(root->internalNode == false)
    {
        struct codeList *temp;
        temp = new (struct codeList);

        if(start == NULL)
        {
            temp -> letter = root -> data;
            temp -> code = str;
            temp -> sizeOfCode = str.length();
            temp -> next = NULL;

            start = temp;
        }
        else
        {
            temp -> letter = root -> data;
            temp -> code = str;
            temp -> sizeOfCode = str.length();
            temp -> next = start;
            start = temp;
        }
    }
    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
} 
// Print PreOrder
void printPreorder(ofstream &fp, struct MinHeapNode* node) 
{ 
    if (node == NULL) 
        return; 
  
    /* first print data of node */
    if(node -> internalNode == false)
    {
        fp << "s " << (int)node -> data << endl;
    }
    else
    {
        fp << "i " << node -> counter << endl; 
    }
 
    //cout << node->data << " "; 
  
    /* then recur on left sutree */
    printPreorder(fp,node->left);  
  
    /* now recur on right subtree */
    printPreorder(fp,node->right); 
} 
//Function that prints The tree inorder
void printInorder(ofstream &fp1, struct MinHeapNode* node) 
{ 
    if (node == NULL) 
        return; 
  
    /* first recur on left child */
    printInorder(fp1,node->left); 
  
    /* then print the data of node */
    if(node -> internalNode == false)
    {
        fp1 << "s " << (int)node -> data << endl;
    }
    else
    {
        fp1 << "i " << node -> counter << endl; 
    } 
  
    /* now recur on right child */
    printInorder(fp1,node->right); 
} 
//Main Function that builds and prints codes
void HuffmanCodes(char data[], int freq[], int size)
{
    struct MinHeapNode* root = buildHuffmanTree(data, freq, size);
    //int arr[MAX_TREE_HT], top = 0; 
    printCodes(root, ""); 

    ofstream fp;
    fp.open("preorder1.txt");
    printPreorder(fp,root);
    fp.close();

    ofstream fp1;
    fp1.open("inorder1.txt");
    printInorder(fp1,root);
    fp1.close();
    
}

/* Function to delete the entire linked list */
void deleteList(charList** head_ref)  
{  
      
    /* deref head_ref to get the real head */
    charList* current = *head_ref;  
    charList* next;  
  
    while (current != NULL)  
    {  
        next = current->next;  
        free(current);  
        current = next;  
    }     
      
    /* deref head_ref to affect the real head back  
    in the caller. */
    *head_ref = NULL;  
}  
int main(int argc, char const *argv[])
{
    static const char* fileName = argv[1];
    // Will store the word and count.
    ifstream fileStream(fileName);
    // Check if we've opened the file (as we should have).
    if(!fileStream)
    {
        cout << "File " << argv[1] << " doesn't exist or can't be opened";
        return -1;
    }
    
    char letter;
    unsigned int size = 0;

    // Scan letter by letter 
    while(fileStream>>noskipws>>letter)
    {   
        // Store in Linked List
        struct charList *temp;
        temp = new (struct charList);

        bool freqIncrement = false;

        if(head == NULL)
        {
            temp -> letter = letter;
            temp -> freq = 1;
            temp -> next = NULL;

            head = temp;
            size++;
        }
        else
        {
            // Check if letter is already in linked list, if so increment freq by  1
            for(charList *ptr = head; ptr != NULL; ptr = ptr -> next)
            {
                if(ptr -> letter == letter)
                {
                    ptr ->freq = ptr -> freq + 1;
                    freqIncrement = true;
                    break; 
                }
            }

            // Otherwise insert into linked list
            if(!freqIncrement)
            {
                temp -> letter = letter;
                temp -> freq = 1;                
                temp -> next = head;
                head = temp;
                size++;
            }
        }
    }
    fileStream.close();
    // Create Arrays
    char *data = new char[size];
    int *freq = new int[size];

    //Store data into arrays which will be then passed to function
    int i = 0;
    for(charList *ptr = head; ptr != NULL; ptr = ptr -> next)
    {
        data[i] = ptr -> letter;
        freq[i] = ptr -> freq;
        i++;
    }
    deleteList(&head);
    HuffmanCodes(data,freq,size);
    
    ifstream file(fileName);
    ofstream outputfile("code1.txt");

    int numberOfBits = 0;
    while(file>>noskipws>>letter)
    {
        for(codeList *ptr = start; ptr != NULL; ptr = ptr -> next)
        {
            if(letter == ptr -> letter)
            {
                outputfile << ptr ->code; 
                numberOfBits += ptr -> sizeOfCode;
            }
        }
    }
    file.close();
    outputfile.close();
    cout <<"Phase 1 code length: " << numberOfBits << " bits";
    
   
}