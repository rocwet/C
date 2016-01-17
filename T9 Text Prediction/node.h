// ################################################################ AUTHOR
/* 
Minhhue H. Khuu
2015.11.11
node.h file: 
*/

// ################################################################ DEFINE
#ifndef NODE_H
#define NODE_H

// ###########  Define structs ##############

/* 
Define a NodeTrie to have two fields.
numKey, An array of 8 NodeTrie's (the sub trees)
words, An array of words.
*/
struct NodeTrie {
  struct NodeTrie* numKey[8];
  struct wordList* words;
};

/* 
Define a wordList to have two fields.
word, The current word.
next, pointer to the wordList that has the next word.
*/
struct wordList {
  char* word;
  struct wordList* next;
};

/* 
Simpler names for NodeTrie and wordList structs.
NodeTrie => Node
wordList => LinkList
*/
typedef struct NodeTrie Node;
typedef struct wordList LinkList;

// ###########  Define function calls to be implemented ##############

/* 
The newNode() function creates a Trie Node, intializes its
children and words stored as NULL, and returns the pointer to it.

@return The pointer to the intialized NULL Trie Node
*/
struct NodeTrie* newNode();

/* 
The newLinkList() function creates a Linked List that has the head
intialized as the string argument, and returns the pointer to it.

@param word The word that will be the head of the linked list.
@return The pointer to the linked list.
*/
struct wordList* newLinkList(char* word);

/* 
The freeNodeTrie() function frees up all memory usage in the heap
of the Node Trie. It uses recursion to free up all sub trees.

param root The Node Trie to be free.
*/
void freeNodeTrie(Node* root);

/* 
The freeLinkList() function frees up all memory usage in the heap
of the Linked List. It uses recursion to free up all nodes within
the Linked List.

@param front The Linked List to be freed (ideally the head node).
 */
void freeLinkList(LinkList* front);


#endif
// ################################################################ END

