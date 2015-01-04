#include <stdlib.h>
#include "types.h"
#include "type_table.h"
#include "vars.h"

var_t *newVar(unsigned char type, void *value)
{
	var_t *varp = malloc(sizeof(var_t));
	varp->type = type;
	varp->value = value;
	return varp;
}
