#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "type_table.h"
#include "vars.h"

static char *varValStr(var_t *varp);
static char *listToStr(void *value);
static char *boolToStr(void *value);
static char *tableToStr(void *value);
static char *numToStr(void *value);
static char *strToStr(void *value);

static const char *typenames[5];
static char *(*valStrFuncs[5]) (void *value);

/* Global functions */

void initType_table(void)
{
	typenames[TYPE_BOOLEAN] = "boolean";
	typenames[TYPE_LIST] = "list";
	typenames[TYPE_NUMBER] = "number";
	typenames[TYPE_STRING] = "string";
	typenames[TYPE_TABLE] = "table";
	valStrFuncs[TYPE_BOOLEAN] = boolToStr;
	valStrFuncs[TYPE_LIST] = listToStr;
	valStrFuncs[TYPE_NUMBER] = numToStr;
	valStrFuncs[TYPE_STRING] = strToStr;
	valStrFuncs[TYPE_TABLE] = tableToStr;
}

table_t *newTable(void)
{
	table_t *tablep = malloc(sizeof(table_t));
	tablep->size = 0;
	return tablep;
}

void addToTable(table_t *tablep, var_t *varp)
{
	// Add to beginning of stack.
	struct tableseg *newseg = malloc(sizeof(struct tableseg));
	newseg->varp = varp;
	newseg->next = tablep->first;
	tablep->first = newseg;
	tablep->size += 1;
}

void rmvFromTable(table_t *tablep, unsigned int i)
{
	if (i > tablep->size) {
		return;
	}
	struct tableseg *before;
	struct tableseg *after;
	before = tablep->first;
	int cnt;
	for (cnt = 1; cnt < i - 1; cnt++)
		before = before->next;
	after = before->next;
	if (after) {
		after = after->next;
		free((void *)before->next);
	}
	before->next = after;
	tablep->size -= 1;
}

void showTable(table_t *tablep)
{
	if (!tablep->first) {
		puts("nothing in table");
		return;
	}
	struct tableseg *cur;
	var_t *varp;
	for (cur = tablep->first; cur; cur = cur->next) {
		varp = cur->varp;
		char str[60];
		strcpy(str, typenames[varp->type]);
		strcat(str, "\t");
		strcat(str, varValStr(varp));
		puts(str);
	}
}

void delTable(table_t *tablep)
{
	if (tablep->first) {
		/* Delete all variables in table. */
		struct tableseg *cur, *nxt;
		for (cur = tablep->first, nxt = cur->next;
		     nxt;
		     cur = nxt, nxt = cur->next
		) {
			delVar(cur->varp);
			free(cur);
		}
	}
	/* Delete table */
	free(tablep);
}

/* Static functions */

char *varValStr(var_t *varp)
{
	return valStrFuncs[varp->type] (varp->value);
}

char *listToStr(void *value)
{
	/* Change later */
	UNUSED(value);
	return (char *)"DOIT";
}

char *boolToStr(void *value)
{
	if ((char *)value == 0) {
		return (char *)"FALSE";
	} else {
		return (char *)"TRUE";
	}
}

char *tableToStr(void *value)
{
	/* Change later */
	UNUSED(value);
	return (char *)"DOIT";
}

char *numToStr(void *value)
{
	char *str = malloc(sizeof(char) * 50);
	snprintf(str, 50, "%f", *(double *)value);
	return str;
}

char *strToStr(void *value)
{
	return (char *)value;
}
