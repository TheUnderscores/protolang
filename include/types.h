#ifndef TYPE_H
#define TYPE_H

#define TYPE_BOOLEAN	0
#define TYPE_LIST	1
#define TYPE_NUMBER	2
#define TYPE_STRING	3
#define TYPE_TABLE	4
#define VAL_FALSE	0
#define VAL_TRUE	!(FALSE)
#define UNUSED(x) (void)(x)

typedef struct var {
	unsigned char type;
	void *value;
} var;

typedef struct table {
	unsigned int size;
	struct tableseg *first;
} table;

var *newVar (unsigned char type, void *value);

#endif /* #ifndef TYPE_H */
