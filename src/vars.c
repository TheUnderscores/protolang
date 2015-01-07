#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "type_table.h"
#include "vars.h"

var_t *newVar(unsigned char type, void *value)
{
	var_t *varp = malloc(sizeof(var_t));
	varp->type = type;
	/* Make copy of value so it can for sure me free()'d */
	/* and also so the end-user can not interfere with it */
	/* through the given pointer argument */
	int size;
	switch (type) {
	case TYPE_BOOLEAN:
		size = sizeof(char);
		break;
	case TYPE_FUNCTION:
		size = 0;  /* TODO: add size of function */
		break;
	case TYPE_LIST:
		size = 0;  /* TODO: add size of list */
		break;
	case TYPE_NUMBER:
		size = sizeof(double);
		break;
	case TYPE_STRING:
		size = strlen(value) * sizeof(char);
		break;
	case TYPE_TABLE:
		size = sizeof(table_t);
		break;
	default:
		size = 0;
		break;
	}
	varp->value = malloc(size);
	memcpy(varp->value, value, size);
	return varp;
}

void delVar(var_t *varp)
{
	free(varp->value);
	free(varp);
}

