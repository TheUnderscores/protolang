#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef TYPE_ARRAY
#define TYPE_ARRAY   0
#endif
#ifndef TYPE_BOOLEAN
#define TYPE_BOOLEAN 1
#endif
#ifndef TYPE_LIST
#define TYPE_LIST    2
#endif
#ifndef TYPE_NUMBER
#define TYPE_NUMBER  3
#endif
#ifndef TYPE_STRING
#define TYPE_STRING  4
#endif
#ifndef TRUE
#define TRUE  1
#endif
#ifndef FALSE
#define FALSE 0
#endif


typedef struct var var;
typedef struct list list;
typedef struct listseg listseg;


list *newList (void);
var *newVar (unsigned short type, void *value);
void addToList (list *listp, var *varp);
void rmvFromList (list *listp, unsigned int i);
char *varValStr (var *varp);
char *arrayToStr (void *value);
char *boolToStr (void *value);
char *listToStr (void *value);
char *numToStr (void *value);
char *strToStr (void *value);
void showList (list *listp);

struct list {
  unsigned int size;
  struct listseg *first;
};

struct listseg {
  struct var *varp;
  struct listseg *next;
};

struct var {
  unsigned short type;
  void *value;
};


char *typenames[5];
char *(*valStrFuncs[5]) (void *value);


int main (void)
{
  typenames[TYPE_ARRAY] = "array";
  typenames[TYPE_BOOLEAN] = "boolean";
  typenames[TYPE_LIST] = "list";
  typenames[TYPE_NUMBER] = "number";
  typenames[TYPE_STRING] = "string";
  valStrFuncs[TYPE_ARRAY] = arrayToStr;
  valStrFuncs[TYPE_BOOLEAN] = boolToStr;
  valStrFuncs[TYPE_LIST] = listToStr;
  valStrFuncs[TYPE_NUMBER] = numToStr;
  valStrFuncs[TYPE_STRING] = strToStr;
  list *list1 = newList();
  showList(list1);
  double x = 7.2422;
  var *var1 = newVar(TYPE_NUMBER, (void*)&x);
  addToList(list1, var1);
  showList(list1);
  return 0;
}


list *newList (void)
{
  list *listp = (list*)malloc(sizeof(list));
  (*listp).size = 0;
  return listp;
}

var *newVar (unsigned short type, void *value)
{
  var *varp = (var*)malloc(sizeof(var));
  (*varp).type = type;
  (*varp).value = value;
  return varp;
}

void addToList (list *listp, var *varp)
{
  // Add to beginning of stack.
  listseg *newseg = (listseg*)malloc(sizeof(listseg));
  (*newseg).varp = varp;
  (*newseg).next = (*listp).first;
  (*listp).first = newseg;
  (*listp).size += 1;
}

void rmvFromList (list *listp, unsigned int i)
{
  if (i > (*listp).size) {
    return;
  }
  listseg *before;
  listseg *after;
  before = (*listp).first;
  int cnt;
  for (cnt=1; cnt<i-1; cnt++)
    before = (*before).next;
  after = (*before).next;
  if (after) {
    after = (*after).next;
    free((void*)(*before).next);
  }
  (*before).next = after;
  (*listp).size -= 1;
}

char *varValStr (var *varp)
{
  valStrFuncs[(*varp).type]((*varp).value);
}

char *arrayToStr (void *value)
{
  return "DOIT";
}

char *boolToStr (void *value)
{
  if ((short*)value == 0) {
    return "FALSE";
  } else {
    return "TRUE";
  }
}

char *listToStr (void *value)
{
  return "DOIT";
}

char *numToStr (void *value)
{
  char *str = malloc(sizeof(char)*50);
  snprintf(str, 50, "%f", *(double*)value);
  return str;
}

char *strToStr (void *value)
{
  return (char*)value;
}

void showList (list *listp)
{
  if ((*listp).first == NULL) {
    puts("nothing in list");
    return;
  }
  listseg *cur;
  var *varp;
  cur = (*listp).first;
  while (cur != NULL) {
    varp = (*cur).varp;
    char str[60];
    strcpy(str, typenames[(*varp).type]);
    strcat(str, "\t");
    strcat(str, varValStr(varp));
    puts(str);
    cur = (*cur).next;
  }
}
