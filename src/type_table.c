#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "type_table.h"
#include "vars.h"

static void rmvSeg(table_t *tablep, struct tableseg *prev, struct tableseg *seg);
static void rmvFromTable_i(table_t *tablep, unsigned int i);
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
	tablep->size = 0;
	tablep->first = NULL;
	return tablep;
}

void addToTable(table_t *tablep, char *varName, var_t *varp)
{
	// Add to beginning of stack.
	struct tableseg *newseg = malloc(sizeof(struct tableseg));
	int sLen = strlen(varName);
	memset(newseg, 0, sizeof(struct tableseg));
	newseg->varName = malloc(sizeof(char)*sLen);
        memcpy(newseg->varName, varName, sLen);
	newseg->varp = varp;
	newseg->next = tablep->first;
	tablep->first = newseg;
	tablep->size += 1;
}

var_t *getFromTable(table_t *tablep, char *varName)
{
	struct tableseg *cur;
	
	for(cur = tablep->first;
	    cur != NULL;
	    cur = cur->next
	    ) {
		if (strcmp(varName, cur->varName) == 0)
			return cur->varp;
	}
	
	/* If function gets to this point, then no match was found for the
	   given variable name in the given table. */
	return (var_t *)NULL;
}

int rmvFromTable(table_t *tablep, char *varName)
{
	struct tableseg *prev, *cur;
	
	for(prev = NULL, cur = tablep->first;
	    cur != NULL;
	    prev = cur, cur = cur->next
	    ) {
		if (strcmp(varName, cur->varName) == 0) {
			rmvSeg(tablep, prev, cur);
			return 0;
		}
	}
	
	/* If function gets to this point, then no match was found for the
	   given variable name in the given table. */
	return -1;
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
		char *varName = cur->varName;
		char *typeName = (char *)typenames[varp->type];
		char *varStr = varValStr(varp);
		/* Explicitly malloc size of string to avoid memory leaks */
		/* Simply allocating a large portion of memory could be */
		/* wasteful for small variable names, and still doesn't */
		/* insure that memory leaks won't occur */
		/* This function will probably be redone when a */
		/* string variable type is created */
		char *str = malloc(sizeof(char) *
				   (strlen(varName) + strlen(typeName) +
				    strlen(varStr) + 3)
				   );
		strcpy(str, varName);
		strcat(str, "\t");
		strcat(str, typeName);
		strcat(str, "\t");
		strcat(str, varStr);
		puts(str);
		
		free(str);
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
			rmvFromTable_i(tablep, 0);
	}
	/* Delete table */
	free(tablep);
}


/* Static functions */

void rmvSeg(table_t *tablep, struct tableseg *prev, struct tableseg *seg)
{
	if (prev == NULL)
		tablep->first = seg->next;
	else
		prev->next = seg->next;
        
	free(seg->varName);
	delVar(seg->varp);
	free(seg);
	tablep->size--;
}

void rmvFromTable_i(table_t *tablep, unsigned int i)
{
	if (tablep->size == 0)
		return;

	if (i + 1 > tablep->size)
		return;
        
	struct tableseg *prev, *cur;

	/* Get to one before  */
	int cnt;
	for (cnt = 0, prev = NULL, cur = tablep->first;
	     cnt < i;
	     cnt++, prev = cur, cur = cur->next);
	
        rmvSeg(tablep, prev, cur);
}

char *varValStr(var_t *varp)
{
	return valStrFuncs[varp->type] (varp->value);
}

char *boolToStr(void *value)
{
	if ((char *)value == 0) {
		return (char *)"FALSE";
	} else {
		return (char *)"TRUE";
	}
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
