#include <stdbool.h>
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct Node* Tree;

struct Node {
	char *value;
	Tree left, right, center;
};

extern void writeln(char *word);

//checks if last word is '*' (supposing every next is NULL)
extern bool lastWordNotAsterisk(char *str1, char *str2, char *str3);

//returns 1st, 2nd or 3rd of given words
extern char *returnWord(char *str1, char *str2, char *str3, int number);

//adds new forest, tree and animal to bst
extern void addNewValue(Tree *bst, char *forest, char *tree, char *animal, int depth);

//finds minimum value in bst
extern Tree findMinimumValue(Tree bst);

//frees memory pointed by root of bst
extern void freeNode(Tree bst);

//deletes entire bst and frees every pointer
extern void deleteTree(Tree bst);

//deletes root of bst and returns merged sons
extern Tree deleteRoot(Tree bst);

//deletes value and all of it's subvalues from bst
extern void deleteValue(Tree *bst, char *forest, char *tree, char *animal, int depth, Tree *father, int son);

//prints every value of bst to stdout
extern void printTree(Tree bst);

//prints all values from given bst
extern void printValues(Tree *bst, char *forest, char *tree, int depth);

//checks if given value is in bst
extern bool checkValue(Tree *bst, char *forest, char *tree, char *animal, int depth);

#endif
