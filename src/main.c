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
	var_t *var1 = newVar(TYPE_NUMBER, (void *)&x1);
	var_t *var2 = newVar(TYPE_NUMBER, (void *)&x2);
	addToTable(table1, var1);
	puts("\nTable contents:");
	showTable(table1);
	addToTable(table1, var2);

	const int input_size = 512; /* 512 should be enough for anyone :P */
	char *input = malloc(sizeof(char) * input_size);

	while (1) {
		puts("\nTable contents:");
		showTable(table1);
		printf("\nEnter a number (double); 'q' to quit: ");

		/*
		 * TODO: the input bits should likely go into
		 * it's own function(s)...
		 */

		if (fgets(input, input_size, stdin) == NULL) {
			perror("Error reading input");
			continue;
		}

		if (input[0] == 'q') /* Quit signal */
			break;

		if (input[0] == '\n') /* No input! Just ignore it. */
			continue;

		/* FIXME: This method causes memory leaks! */
		double *x = malloc(sizeof(double));
		char *strend;
		*x = strtod(input, &strend);

		/*
		 * Inequality means that strtod() actually
		 * did something. Add x to table.
		 */

		if (input != strend)
			addToTable(table1, newVar(TYPE_NUMBER, (void *)x));
		else
			puts("Did not enter a number.");
		
		free(x);
	}
	
	delTable(table1);
	free(input);

	return 0;
}
