/* To do list:
 *  - MAYBE make a global table, in which all variables reside
 *  - add booleans, lists, strings, and functions
 *  - finish showTable()
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "testing.h"
#include "types.h"
#include "type_table.h"
#include "vars.h"

int main(void)
{
	init_testing();
	init_type_table();
	
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

	if (var1 == NULL) {
		perror("Could not create variable");
		return 1;
	}

	var_t *var2 = newVar(TYPE_NUMBER, (void *)&x2);
	
	if (var2 == NULL) {
		perror("Could not create variable");
		return 1;
	}
	
	var_t *var3 = newVar(TYPE_NUMBER, (void *)&x3);
	
	if (var3 == NULL) {
		perror("Could not create variable");
		return 1;
	}
	
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
	
	var_t *var4 = getFromTable(table1, name2);
	printf("\n%s->value:\t%lf\n", name2, *(double *)var4->value);
	
	printf("\nRemoving %s...\n\n", name3);
	rmvFromTable(table1, name3);
	showTable(table1);
	
	puts("");
	
	inputLoop(table1);
	
	delTable(table1);
	
	return 0;
}



