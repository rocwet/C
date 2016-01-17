// ################################################################ AUTHOR
/* 
Minhhue H. Khuu
2015.11.11
t9.c file
*/

// ################################################################ LIBRARIES
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "node.h"

// ################################################################ CONSTANTS
#define MAX_LINE 100

// ################################################################ INTIALIZE
int getKey(char letter);
void createNodeTrie(Node* head, char* word);
void search(Node* root);

// ################################################################ FUNCTIONS
/* 
The getKey() function returns the corresponding numerical number of
a given character as an integer value.

@param letter The letter to check.
@return The integer value corresponding to the letter.
*/
int getKey(char letter) {
  if (letter == 'a' || letter == 'b' || letter == 'c') {
    return 0;
  } else if (letter == 'd' || letter == 'e' || letter == 'f') {
    return 1;
  } else if (letter == 'g' || letter == 'h' || letter == 'i') {
    return 2;
  } else if (letter == 'j' || letter == 'k' || letter == 'l') {
    return 3;
  } else if (letter == 'm' || letter == 'n' || letter == 'o') {
    return 4;
  } else if (letter == 'p' || letter == 'q' || letter == 'r' || letter == 's') {
    return 5;
  } else if (letter == 't' || letter == 'u' || letter == 'v') {
    return 6;
  } else {
    return 7;
  }
}

/* 
The createNodeTrie() function creates a Node Trie that is intialized
with a head node and words stored in the head node.

@param head The head node of the Node Trie tree.
@param word The word stored in the head node of the Node Trie tree.
*/
void createNodeTrie(Node* head, char* word) {
  LinkList* temp;
  for (int i = 0; i < strlen(word) - 1; i++) {
    int key = getKey(word[i]);
    if (head->numKey[key] != NULL) {
      head = head->numKey[key];
    } else {
      head->numKey[key] = newNode();
      head = head->numKey[key];
    }
    if (i == strlen(word) - 2) {
      if (head->words == NULL) {
        head->words = newLinkList(word);
      } else {
        temp = head->words;
        while (temp->next != NULL) {
          temp = temp->next;
        }
        temp->next = newLinkList(word);
      }
    }
  }
}

/* 
The search() function will take a Node Trie (ideally the root) and
search the the Node Trie, based on the input of the user from stdin.
The search() function will output the word if it matches with the
input or output an error message stating why to the user in stdout.

@param root The root Node of the Node Trie to be examined.
 */
void search(Node* root) {
  
  // intialize
  char input[MAX_LINE];
  Node* current = root;
  LinkList* listPointer;
  int poundCount = 0;
  
  // display information and get input
  printf("Enter \"exit\" to quit.\n");
  printf("Enter Key Sequence (or \"#\" for next word):\n> ");
  
  // interate through the input
  while (fgets(input, MAX_LINE, stdin)) {
    current = root;
    // indicator if a word has been found
    int done = 0;
    if (strstr(input, "exit") != NULL) {
      return;
    }
    
    // # case at start
    if (input[0] == '#') {
      done = 1;
      if (listPointer != NULL && listPointer->next != NULL) {
        listPointer = listPointer->next;
        printf("  \'%s\'\n", listPointer->word);
      } else {
        printf("  There are no more T9onyms\n\n");
      }
      
      // other case
    } else {
      listPointer = current->words;
      for (int i = 0; i < strlen(input) - 1; i++) {
        if (current != NULL) {
          switch (input[i]) {
            case '2':
              current = current->numKey[0];
              break;
            case '3':
              current = current->numKey[1];
              break;
            case '4':
              current = current->numKey[2];
              break;
            case '5':
              current = current->numKey[3];
              break;
            case '6':
              current = current->numKey[4];
              break;
            case '7':
              current = current->numKey[5];
              break;
            case '8':
              current = current->numKey[6];
              break;
            case '9':
              current = current->numKey[7];
              break;
            case '#':
              if (poundCount == 0) {
                listPointer = current->words;
              }
              poundCount++;
              break;
            default:
              done = 1;
              fprintf(stderr, "ERROR: Invalid input. Enter (2-9) or #\n");
          }
        } else {
          if (done == 0) {
            done = 1;
            printf("  Not found in current dictionary.\n");
          }
        }
      }
    }
    
    // display the word, 0 == # case
    if (current != NULL && current->words != NULL && poundCount == 0) {
      listPointer = current->words;
      printf("  \'%s\'\n", current->words->word);
      
      // display the words (multiple) 0 > # case
    } else if (poundCount > 0) {
      while (listPointer != NULL &&
             listPointer->next != NULL && poundCount > 0) {
        listPointer = listPointer->next;
        poundCount--;
      }
      if (poundCount == 0) {
        printf("  %s\n", listPointer->word);
      } else {
        if (done == 0) {
          done = 1;
          printf("  Not found in current dictionary.\n\n");
        }
      }
    } else {
      if (done == 0) {
        printf("  Not found in current dictionary.\n\n");
      }
    }
    
    // redisplay information for user
    printf("Enter Key Sequence (or \"#\" for next word):\n> ");
  }
}

// ################################################################ MAIN
/* 
The main() function runs a T9 word predictor program. It takes a 
single argument that is assumed to be a dictionary text file. Then
loads the words into a Trie Tree, and asks the user for inputs to
retrieve an output that corresponds to the matching t9 numbers.
There is no input validation.

@ param argc The argument count (includes the command call).
@ param argv The command line arguments.
@ return The return status of the program.
         0 = success; 1 = fail;
 */
int main(int argc, char** argv) {
  FILE* dict = fopen(argv[1], "r");
  char word[MAX_LINE];
  Node* root = newNode();
  if (!dict) {
    fprintf(stderr, "ERROR: Dictionary File does not exist!\n");
    return 1;
  }
  while (fgets(word, MAX_LINE, dict) != NULL) {
    createNodeTrie(root, word);
  }
  fclose(dict);
  search(root);
  freeNodeTrie(root);
  return 0;
}
// ################################################################ END


