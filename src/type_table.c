#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "type_table.h"
#include "vars.h"

static char *varValStr(var_t *varp);
static char *boolToStr(void *value);
static char *funcToStr(void *value); /* TODO */
static char *listToStr(void *value); /* TODO */
static char *numToStr(void *value);
static char *strToStr(void *value);
static char *tableToStr(void *value);

static const char *typenames[6];
static char *(*valStrFuncs[6]) (void *value);

/* Global functions */

void initType_table(void)
{
	typenames[TYPE_BOOLEAN] = "boolean";
	typenames[TYPE_LIST] = "list";
	typenames[TYPE_FUNCTION] = "function";
	typenames[TYPE_NUMBER] = "number";
	typenames[TYPE_STRING] = "string";
	typenames[TYPE_TABLE] = "table";
	valStrFuncs[TYPE_BOOLEAN] = boolToStr;
	valStrFuncs[TYPE_LIST] = listToStr;
	valStrFuncs[TYPE_FUNCTION] = funcToStr;
	valStrFuncs[TYPE_NUMBER] = numToStr;
	valStrFuncs[TYPE_STRING] = strToStr;
	valStrFuncs[TYPE_TABLE] = tableToStr;
}

table_t *newTable(void)
{
	table_t *tablep = malloc(sizeof(table_t));

	if (tablep == NULL)
		return NULL;

	tablep->size = 0;
	tablep->first = NULL;
	return tablep;
}

void addToTable(table_t *tablep, var_t *varp)
{
	// Add to beginning of stack.
	struct tableseg *newseg = malloc(sizeof(struct tableseg));

	if (newseg == NULL) {
		perror("Could not add to table");
		return;
	}

	memset(newseg, 0, sizeof(struct tableseg));
	newseg->varp = varp;
	newseg->next = tablep->first;
	tablep->first = newseg;
	tablep->size += 1;
}

void rmvFromTable(table_t *tablep, unsigned int i)
{
	if (tablep->size == 0)
		return;

	if (i + 1 > tablep->size)
		return;

	struct tableseg *prev, *cur;

	/* Get to one before */
	int cnt;
	for (cnt = 0, prev = NULL, cur = tablep->first; cnt < i;
	     cnt++, prev = cur, cur = cur->next);

	if (prev == NULL)
		tablep->first = cur->next;
	else
		prev->next = cur->next;

	delVar(cur->varp);
	free(cur);

	tablep->size--;
}

void showTable(table_t *tablep)
{
	if (!tablep->first) {
		puts("nothing in table");
		return;
	}

	printf("%d elements in table\n", tablep->size);

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
	        int i;
		int init_size = tablep->size;
		for (i = 0; i < init_size; i++)
			/* Yes, really, delete first element each time */
			rmvFromTable(tablep, 0);
	}
	/* Delete table */
	free(tablep);
}

/* Static functions */

char *varValStr(var_t *varp)
{
	return valStrFuncs[varp->type](varp->value);
}

char *boolToStr(void *value)
{
	if ((char *)value == 0)
		return (char *)"FALSE";
	else
		return (char *)"TRUE";
}

char *funcToStr(void *value)
{
	/* Change later */
	UNUSED(value);
	return (char *)"[placeholder]";
}

char *listToStr(void *value)
{
	/* Change later */
	UNUSED(value);
	return (char *)"[placeholder]";
}

char *numToStr(void *value)
{
	static char str[50];
	snprintf(str, 50, "%f", *(double *)value);
	return str;
}

char *strToStr(void *value)
{
	return (char *)value;
}

char *tableToStr(void *value)
{
	/* Change later */
	UNUSED(value);
	return (char *)"DOIT";
}
