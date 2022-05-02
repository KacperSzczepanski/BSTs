//Male zadanie
//autor: Kacper Szczepanski 418474
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
#include "functions.h"

int main()
{
	
	Tree bst = NULL;
	char *line;
	bool pause = 0;
    
    while (!pause)
    {
		
		bool error = 0, empty = 0, is_endl = 1, not_in_range = 0;
		
		line = getLine();
		int length = strlen(line);
		
		if (length > 0 && line[length - 1] == -1) {
			pause = 1;
		}
		
		if (line == NULL) {
			continue;
		}
		
		if (length <= 1) {
			free(line);
			continue;
		}
		
		if (whitespace(line[0])) {
			empty = 1;
		}
		
		for (int i = 0; i <= length; ++i) {
			if (0 < line[i] && line[i] < 33 && !whitespace(line[i]) && line[i] != 10) {
				not_in_range = 1;
			}
		}

		if (line[length - 1] != 10) is_endl = 0;
		line[length - 1] = 0;
		
		char *action, *forest, *tree, *animal, *trash, *words;
		action = forest = tree = animal = trash = words = NULL;
		
		words = strtok(line, " ");
		while (words != NULL) {
			if (action == NULL) action = words;
			else if (forest == NULL) forest = words;
			else if (tree == NULL) tree = words;
			else if (animal == NULL) animal = words;
			else if (trash == NULL) trash = words;
			words = strtok (NULL, " ");
		}
		
		if (action == NULL || (action[0] == '#' && empty == 0)) {
			free(line);
			continue;
		}
		else if (not_in_range || !is_endl || trash != NULL) {
			error = 1;	
		}
		else if (!strcmp(action, "ADD") && forest != NULL) {
			addNewValue(&bst, forest, tree, animal, 1);
			printf("OK\n");
		}
		else if (!strcmp(action, "DEL")) {
			if (forest == NULL) {
				deleteTree(bst);
				bst = NULL;
			}
			else {
				if (tree == NULL && bst != NULL && !strcmp(forest, bst->value)) {
					deleteTree(bst->center);
					bst->center = NULL;
					bst = deleteRoot(bst);
				}
				else {
					deleteValue(&bst, forest, tree, animal, 1, NULL, 0);
				}
			}
			printf ("OK\n");
		}
		else if (!strcmp(action, "PRINT") && animal == NULL) {
			if (forest == NULL) {
				printTree(bst);
			}
			else {
				printValues(&bst, forest, tree, 1);
			}
		}
		else if (!strcmp(action, "CHECK") && forest != NULL && lastWordNotAsterisk(forest, tree, animal)) {
			bool res = checkValue(&bst, forest, tree, animal, 1);
			printf ("%s\n", res ? "YES" : "NO");
		}
		else {
			error = 1;
		}
		
		if (error == 1) {
			fprintf (stderr, "ERROR\n");
		}
		
		free(line);
		
	}

	deleteTree(bst);
	
    return(0);
}
