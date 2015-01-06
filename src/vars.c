#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "type_table.h"
#include "vars.h"

static int typeSizes[5];

void initVars(void)
{
	typeSizes[TYPE_BOOLEAN] = sizeof(char);
	typeSizes[TYPE_LIST] = 0; /* TODO: change when there is a struct/typedef for lists */
	typeSizes[TYPE_NUMBER] = sizeof(double);
	/* String size is determined with strlen() */
	typeSizes[TYPE_STRING] = 0;
	typeSizes[TYPE_TABLE] = sizeof(table_t);
}

var_t *newVar(unsigned char type, void *value)
{
	var_t *varp = malloc(sizeof(var_t));
	varp->type = type;
	/* Make copy of value so it can for sure me free()'d */
	/* and also so the end-user can not interfere with it */
	/* through the given pointer argument */
	int size;
	if (type == TYPE_STRING)
		size = strlen(value);
	else
		size = typeSizes[type];
	/* TODO: add an else for lists */
	varp->value = malloc(size);
	memcpy(varp->value, value, size);
	return varp;
}

void delVar(var_t *varp)
{
	free(varp->value);
	free(varp);
}
