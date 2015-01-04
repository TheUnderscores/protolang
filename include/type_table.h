#ifndef TYPE_TABLE_H
#define TYPE_TABLE_H

void initType_table(void);
table_t *newTable(void);
void addToTable(table_t *tablep, var_t *varp);
void rmvFromTable(table_t *tablep, unsigned int i);
void showTable(table_t *tablep);

#endif
