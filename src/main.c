/* To do list:
 *  - MAYBE make a global table, in which all variables reside
 *  - add booleans, lists, strings, and functions
 *  - finish showTable()
 *  - MAYBE move newVar() to it's own file; could be a waste of space, though
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "type_table.h"

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

	while (1) {
		double *x = malloc(sizeof(double));
		puts("\nTable contents:");
		showTable(table1);
		printf("\nEnter a number (double); Ctrl-C to quit: ");
		scanf("%lf", x);
		addToTable(table1, newVar(TYPE_NUMBER, (void *)x));
	}

	/* EOF Test */

	return 0;
}

var_t *newVar(unsigned char type, void *value)
{
	var_t *varp = malloc(sizeof(var_t));
	varp->type = type;
	varp->value = value;
	return varp;
}
