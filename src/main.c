/* To do list:
 *  - MAYBE make a global table, in which all variables reside
 *  - add booleans, lists, strings, and functions
 *  - finish showTable()
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "type_table.h"
#include "vars.h"

int main(void)
{
	initType_table();

	/* Test */
	/* Feel free to edit this section as you please. */
	/* If in doubt, just comment out code you don't want to use. */
	/* Just make sure it's functional before making a pull request. */

	table_t *table1 = newTable();
	puts("");
	puts("-------------------------------------------------------------------");
	puts(" This interface is purely for testing purposes.                    ");
	puts(" Input isn't checked, so invalid input will probably cause issues. ");
	puts("-------------------------------------------------------------------");
	puts("");
        
	double x1 = 3.1415926535;
	double x2 = 13.37;
	double x3 = 777.666;
	var_t *var1 = newVar(TYPE_NUMBER, (void *)&x1);
	var_t *var2 = newVar(TYPE_NUMBER, (void *)&x2);
	var_t *var3 = newVar(TYPE_NUMBER, (void *)&x3);
	char *name1 = (char *)"first";
	char *name2 = (char *)"bubbles";
	char *name3 = (char *)"aName";
	puts("\nTable contents:");
	showTable(table1);
	
	addToTable(table1, name1, var1);
	puts("\nTable contents:");
	showTable(table1);
	
	addToTable(table1, name2, var2);
	puts("\nTable contents:");
	showTable(table1);
	
	addToTable(table1, name3, var3);
	puts("\nTable contents:");
	showTable(table1);
	
	var_t *gotvar = getFromTable(table1, name2);
	printf("\ntest: %s\t%f\n", name2, *(double *)(gotvar->value));
	gotvar = getFromTable(table1, name1);
	printf("\ntest: %s\t%f\n", name1, *(double *)(gotvar->value));
	gotvar = getFromTable(table1, name3);
	printf("\ntest: %s\t%f\n", name3, *(double *)(gotvar->value));
	
	const int input_size = 512; /* 512 should be enough for anyone :P */
	char *input = malloc(sizeof(char) * input_size);
	unsigned char cont = 1;
	while (1) {
		if (!cont) {
			free(input);
			break;
		}
		
		/*
		 * TODO: the input bits should likely go into
		 * it's own function(s)...
		 */
		
		char *varName;
		double *x = malloc(sizeof(double));
		char *strend;
		int sLen;
		
		puts("\nTable contents:");
		showTable(table1);
		/* Get variable name */
		/* Thing's will probably look wierd if whitespace is given */
		/* But... just a testing block. */
		printf("\nEnter a variable name; 'q' to quit: ");
		
		if (fgets(input, input_size, stdin) == NULL) {
			perror("Error reading input");
			continue;
		}

		if (input[0] == 'q') { /* Quit signal */
			cont = 0;
			continue;
		}
		
		/* Trim whitespace */
		
		sLen = strlen(input);
		/* Find beginning of string */
		int bgn;
		for (bgn = 0;
		     bgn <= sLen &&
			     (input[bgn] == ' ' ||
			     input[bgn] == '\t' ||
			      input[bgn] == '\n');
		     bgn++
		     );
		
		if (bgn == sLen)
			continue; /* All whitespace; ignore */
		
		/* Find end of string */
		int end;
		for (end = sLen-1;
		     end >= bgn&&
			     (input[end] == ' ' ||
			     input[end] == '\t' ||
			      input[end] == '\n');
		     end--
		     );
		
		/* Modify start and end of string */
		input[end+1] = '\0';
		input = &input[bgn];
		
		/* Copy trimmed string */
		sLen = strlen(input);
		varName = malloc(sizeof(char)*sLen+1);
		memcpy(varName, input, sLen+1);
		
		/* Get number */
		while (1) {
			printf("\nEnter a number (double); 'c' to cancel; 'q' to quit: ");

			if (fgets(input, input_size, stdin) == NULL) {
				perror("Error reading input");
				continue;
			}

			if (input[0] == 'q') { /* Quit signal */
				cont = 0;
				break;
			}
			
			if (input[0] == 'c') { /* Cancel signal */
				break;
			}
			
			if (input[0] == '\n') /* No input! Just ignore it. */
				continue;
		
			*x = strtod(input, &strend);

			/*
			 * Inequality means that strtod() actually
			 * did something. Add x to table.
			 */

			if (input != strend) {
				addToTable(table1, varName, newVar(TYPE_NUMBER, (void *)x));
				break;
			} else {
				puts("Did not enter a number.");
			}
		}
		free(varName);
		free(x);
	}
	delTable(table1);
	return 0;
}
