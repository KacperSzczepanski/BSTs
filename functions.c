#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "input.h"

void writeln(char *word) {
	
	if (word != NULL) {
		printf ("%s\n", word);
	}
}

bool lastWordNotAsterisk(char *str1, char *str2, char *str3) {
	
	if (str2 == NULL) {
		if (!strcmp (str1, "*")) {
			return 0;
		}
		else {
			return 1;
		}
	}
	
	if (str3 == NULL) {
		if (!strcmp (str2, "*")) {
			return 0;
		}
		else {
			return 1;
		}
	}
	
	if (!strcmp (str3, "*")) {
			return 0;
		}
		else {
			return 1;
		}
}

char *returnWord(char *str1, char *str2, char *str3, int number) {
	
	if (number == 1) {
		return str1;
	}
	else if (number == 2) {
		return str2;
	}
	else {
		return str3;
	}
}

//adds new value as a leaf to existing bst, depth means which being we add
//(or how deep in bsts we are)
void addNewValue(Tree *bst, char *forest, char *tree, char *animal, int depth) {
	
	char *word = returnWord(forest, tree, animal, depth);
	
	if (*bst == NULL) {
		Tree newNode = malloc(sizeof(struct Node));
		newNode->value = calloc(sizeof(char), strlen(word) + 1);
		newNode->left = newNode->right = newNode->center = NULL;
		
		memcpy(newNode->value, word, strlen(word));
		
		*bst = newNode;
	}
	
	int cmp = strcmp(word, (*bst)->value);
	
	if (cmp < 0) {
		addNewValue(&(*bst)->left, forest, tree, animal, depth);
	}
	else if (cmp > 0) {
		addNewValue(&(*bst)->right, forest, tree, animal, depth);
	}
	else {
		if (depth == 3) {
			return;
		}
		else if (depth == 2) {
			if (animal == NULL) {
				return;
			}
			else {
				addNewValue(&(*bst)->center, forest, tree, animal, 3);
			}
		}
		else {
			if (tree == NULL) {
				return;
			}
			else {
				addNewValue(&(*bst)->center, forest, tree, animal, 2);
			}
		}
		
	}
}

Tree findMinimumValue(Tree bst) {
	
	if (bst->left == NULL) {
		return bst;
	}
	else {
		return findMinimumValue(bst->left);
	}
}

void freeNode(Tree bst) {
	
	if (bst != NULL) {
		if (bst->left != NULL) {
			free(bst->left);
			bst->left = NULL;
		}
		
		if (bst->right != NULL) {
			free(bst->right);
			bst->right = NULL;
		}
		
		if (bst->center != NULL) {
			free(bst->center);
			bst->center = NULL;
		}
		
		if (bst->value != NULL) {
			free(bst->value);
			bst->value = NULL;
		}
		
		free(bst);
		bst = NULL;
	}
}

void deleteTree(Tree bst) {
	
	if (bst == NULL) {
		return;
	}
	
	deleteTree(bst->left);
	deleteTree(bst->right);
	deleteTree(bst->center);
	bst->left = NULL;
	bst->right = NULL;
	bst->center = NULL;
	
	freeNode(bst);
}

//deletes root and joins left subtree to leaf of right subtree
Tree deleteRoot(Tree bst) {
	
	if (bst->left == NULL) {
		if (bst->right == NULL) {
			freeNode(bst);
			return NULL;
		}
		else {
			Tree tmp = bst->right;
			
			bst->right = NULL;
			freeNode(bst);
			
			return tmp;
		}
	}
	else {
		if (bst->right == NULL) {
			Tree tmp = bst->left;
			
			bst->left = NULL;
			freeNode(bst);
			
			return tmp;
		}
		else {
			Tree tmp = findMinimumValue(bst->right);
			tmp->left = bst->left;
			bst->left = NULL;
			
			Tree tmp2 = bst->right;
			bst->right = NULL;
			
			freeNode(bst);
			return tmp2;
		}
	}
}

//searches for main value to delete, then calls deleteTree to delete all subvalues
void deleteValue(Tree *bst, char *forest, char *tree, char *animal, int depth, Tree *father, int son) {
	
	if (*bst == NULL) {
		return;
	}
	
	char *word = returnWord(forest, tree, animal, depth);
	
	int cmp = strcmp(word, (*bst)->value);
	
	if (cmp < 0) {
		deleteValue(&(*bst)->left, forest, tree, animal, depth, bst, 0);
	}
	else if (cmp > 0) {
		deleteValue(&(*bst)->right, forest, tree, animal, depth, bst, 1);
	}
	else {
		if (depth == 3) {
			deleteTree((*bst)->center);
			(*bst)->center = NULL;
			
			Tree tmp = deleteRoot(*bst);
			
			if (!son) {
				(*father)->left = tmp;
			}
			else if (son == 1) {
				(*father)->right = tmp;
			}
			else {
				(*father)->center = tmp;
			}
		}
		else if (depth == 2) {
			if (animal == NULL) {
				deleteTree((*bst)->center);
				(*bst)->center = NULL;
				
				Tree tmp = deleteRoot(*bst);
				
				if (!son) {
					(*father)->left = tmp;
				}
				else if (son == 1) {
					(*father)->right = tmp;
				}
				else {
					(*father)->center = tmp;
				}
			}
			else {
				deleteValue(&(*bst)->center, forest, tree, animal, 3, bst, 2);
			}
		}
		else {
			if (tree == NULL) {
				deleteTree((*bst)->center);
				(*bst)->center = NULL;
				
				Tree tmp = deleteRoot(*bst);
				
				if (!son) {
					(*father)->left = tmp;
				}
				else if (son == 1) {
					(*father)->right = tmp;
				}
				else {
					(*father)->center = tmp;
				}
			}
			else {
				deleteValue(&(*bst)->center, forest, tree, animal, 2, bst, 2);
			}
		}
	}
}

void printTree(Tree bst)
{
    if (bst == NULL) return;
    
    printTree(bst->left);
    writeln(bst->value);
    printTree(bst->right);
}

//searches for value, which subvalues are supposed to be printed
void printValues(Tree *bst, char *forest, char *tree, int depth) {
	
	if (*bst == NULL) {
		return;
	}
	
	char *word = returnWord(forest, tree, NULL, depth);
	
	int cmp = strcmp(word, (*bst)->value); 
	
	if (cmp < 0) {
		printValues(&(*bst)->left, forest, tree, depth);
	}
	else if (cmp > 0) {
		printValues(&(*bst)->right, forest, tree, depth);
	}
	else {
		if (depth == 2) {
			printTree((*bst)->center);
		}
		else {
			if (tree == NULL) {
				printTree((*bst)->center);
			}
			else {
				printValues(&(*bst)->center, forest, tree, 2);
			}
		}
	}
}
//checks if value is in bst
_Bool checkValue(Tree *bst, char *forest, char *tree, char *animal, int depth) {
	
	if (*bst == NULL) {
		return 0;
	}
	
	char *word = returnWord(forest, tree, animal, depth);
	
	if (!strcmp(word, "*")) {
		
		bool res = 0;
		
		res |= checkValue(&(*bst)->left, forest, tree, animal, depth);
		if (res) {
			return res;
		}
		
		res |= checkValue(&(*bst)->right, forest, tree, animal, depth);
		if (res) {
			return res;
		}
		
		res |= checkValue(&(*bst)->center, forest, tree, animal, depth + 1);
		return res;
	}
	else {
		int cmp = strcmp(word, (*bst)->value);
		
		if (cmp < 0) {
			return checkValue(&(*bst)->left, forest, tree, animal, depth);
		}
		else if (cmp > 0) {
			return checkValue(&(*bst)->right, forest, tree, animal, depth);
		}
		else {
			if (depth == 3) {
				return 1;
			}
			else if (depth == 2) {
				if (animal == NULL) {
					return 1;
				}
				else {
					return checkValue(&(*bst)->center, forest, tree, animal, depth + 1);
				}
			}
			else {
				if (tree == NULL) {
					return 1;
				}
				else {
					return checkValue(&(*bst)->center, forest, tree, animal, depth + 1);
				}
			}
		}
	}
}
