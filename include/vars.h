#ifndef VARS_H
#define VARS_H

void initVars(void);
var_t *newVar(unsigned char type, void *value);
void delVar(var_t *varp);

#endif
