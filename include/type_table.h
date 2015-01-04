#ifndef TYPE_TABLE_H
#define TYPE_TABLE_H

void initType_table(void);
table *newTable(void);
void addToTable(table *tablep, var *varp);
void rmvFromTable(table *tablep, unsigned int i);
void showTable(table *tablep);

#endif
