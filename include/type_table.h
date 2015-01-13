#ifndef TYPE_TABLE_H
#define TYPE_TABLE_H

void initType_table(void);
table_t *newTable(void);
void addToTable(table_t *tablep, char *varName, var_t *varp);
var_t *getFromTable(table_t *tablep, char *varName);
int rmvFromTable(table_t *tablep, char *varName);
void showTable(table_t *tablep);
void delTable(table_t *tablep);

#endif
