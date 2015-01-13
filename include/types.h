#ifndef TYPE_H
#define TYPE_H

#define TYPE_BOOLEAN	0
#define TYPE_FUNCTION   1
#define TYPE_LIST	2
#define TYPE_NUMBER	3
#define TYPE_STRING	4
#define TYPE_TABLE	5
#define VAL_FALSE	0
#define VAL_TRUE	!(FALSE)
#define UNUSED(x) (void)(x)

typedef struct {
	unsigned char type;
	void *value;
} var_t;

struct tableseg {
	char* varName;
	var_t *varp;
	struct tableseg *next;
};

typedef struct {
	unsigned int size;
	struct tableseg *first;
} table_t;

#endif /* #ifndef TYPE_H */
