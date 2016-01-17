// ################################################################ AUTHOR
/*
Minhhue H. Khuu
2015.11.11
node.c file
 */

// ################################################################ LIBRARIES
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "node.h"

// ################################################################ FUNCTIONS
/* 
The newNode() function creates a Trie Node, intializes its
children and words stored as NULL, and returns the pointer to it.
 
@return The pointer to the intialized NULL Trie Node
*/
struct NodeTrie* newNode() {
  struct NodeTrie* nt = (struct NodeTrie*)malloc(sizeof(struct NodeTrie));
  for (int i = 0; i < 8; i++) {
    nt->numKey[i] = NULL;
  }
  nt->words = NULL;
  return nt;
}

/* 
The newLinkList() function creates a Linked List that has the head
intialized as the string argument, and returns the pointer to it.

@param word The word that will be the head of the linked list.
@return The pointer to the linked list.
*/
struct wordList* newLinkList(char* word) {
  struct wordList* l = (struct wordList*)malloc(sizeof(struct wordList));
  l->word = (char*)malloc(strlen(word)+1);
  strncpy(l->word, word, strlen(word)+1);
  l->word[strlen(word) - 1] = '\0';
  l->next = NULL;
  return l;
}

/* 
The freeNodeTrie() function frees up all memory usage in the heap
of the Node Trie. It uses recursion to free up all sub trees.

@param root The Node Trie to be free.
*/
void freeNodeTrie(Node* root) {
  for (int i = 0; i < 8; i++) {
    if (root->numKey[i]) {
      freeNodeTrie(root->numKey[i]);
    }
  }
  if (root->words) {
    freeLinkList(root->words);
  }
  free(root);
}

/* 
The freeLinkList() function frees up all memory usage in the heap
of the Linked List. It uses recursion to free up all nodes within
the Linked List.

@param front The Linked List to be freed (ideally the head node).
*/
void freeLinkList(LinkList* head) {
  if (head->next) {
    freeLinkList(head->next);
  }
  free(head->word);
  free(head);
}

// ################################################################ END




