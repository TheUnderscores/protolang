#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "testing.h"
#include "types.h"
#include "type_table.h"
#include "vars.h"

static char *trim(char *target);
static int getInput(void);
static int evalInput(void);
static void cleanUp(void);
static int step0(void);
static int step1(void);
static int step2(void);

static const int loopSteps_len = 3;
static int (*loopSteps[3])(void);// = {step1, step2, step3};
static int curStep = 0;
static const int LOOP_REPEAT = 1;
static const int LOOP_NEXT   = 2;
static const int LOOP_RESET  = 3;
static const int LOOP_QUIT   = 4;
static const int LOOP_CONT   = 5;
static table_t *tablep;
static const int input_size = 512;
static char *input;
static char *varName;


/*
 * Global functions
 */

void init_testing(void)
{
	loopSteps[0] = &step0;
	loopSteps[1] = &step1;
	loopSteps[2] = &step2;
	input = (char *) NULL;
	varName = (char *) NULL;
}

void inputLoop(table_t *inTbl)
{
	tablep = inTbl;
	int cont = 1;
	input = malloc(sizeof(char) * input_size);
	while (cont) {
		switch(loopSteps[curStep]()){
		case 1: /*LOOP_REPEAT*/
			break;
		case 2: /*LOOP_NEXT*/
			++curStep;
			if (curStep > 2)
				curStep = 0;
			break;
		case 3: /*LOOP_RESET*/
			curStep = 0;
			cleanUp();
			break;
		case 4: /*LOOP_QUIT*/
			cont = 0;
			cleanUp();
			break;
		default:
			perror("Unexpected loop condition");
		}
		/* a case for LOOP_CONT is purposefully omitted */
	}
}


/*
 * Static functions
 * Returned string must be free()'d
 */

char *trim(char *target)
{
	int bgn, end, sLen;
	
	/* Find beginning of string */
        sLen = strlen(target);
	for (bgn = 0;
	     bgn < sLen && isspace(input[bgn]);
	     bgn++
	     );
		
	if (bgn == sLen)
		return (char *) NULL;
		
	/* Find end of string */
	for (end = sLen - 1;
	     end > bgn && isspace(input[end]);
	     end--
	     );
		
        /* Copy section of string that is trimmed */
	sLen = end - bgn + 1;
	char *newStr = malloc(sizeof(char) * (sLen + 1));
	memcpy(newStr, &target[bgn], sLen);
	newStr[sLen] = '\0';
	
	return newStr;
}

int getInput(void)
{
	if (fgets(input, input_size, stdin) == NULL) {
		perror("Error reading input");
	        return 1;
	}
        
	char *trimmed = trim(input);
	/* Copied so input doesn't need to be free()'d */
	memcpy(input, trimmed, sizeof(char) * (strlen(trimmed) + 1));
	free(trimmed);
	
	return 0;
}

int evalInput(void)
{
	/* If string is only one character long */
	/* Generally more efficient then calling strlen() */
	if (input[1] == '\0') {
		if (input[0] == 'q') { /* Quit signal */
			puts("\nQuitting...\n");
			return LOOP_QUIT;
	
		} else if (input[0] == 'c') { /* Cancel signal */
			puts("\nCanceled...\n");
			return LOOP_RESET;
			
		} else if (input[0] == '\n' || strlen(input) == 0) { /* No input! Just ignore it. */
			return LOOP_REPEAT;
	
		} else {
			return LOOP_CONT;
		}
	} else {
		return LOOP_CONT;
	}
}

/*
 * Should be invoked after the current step is executed.
 */
void cleanUp(void)
{
	if (curStep > 1)
		free(varName);
}

int step0(void)
{
	showTable(tablep);
	return LOOP_NEXT;
}


/*
 * Get variable's name
 */
int step1(void)
{
	printf("\nEnter a variable name: 'q' to quit: ");
	
	if (getInput() == 1)
		return LOOP_QUIT;
	
	int loopState = evalInput();
	if (loopState != LOOP_CONT)
		return loopState;
	
	int sLen = strlen(input);
	varName = malloc(sizeof(char) * sLen);
	memcpy(varName, input, sizeof(char) * sLen);
	return LOOP_NEXT;
}

/*
 * Get variable's value
 */
int step2(void)
{
        printf("\nEnter a number (double); 'c' to cancel; 'q' to quit: ");
	
	if (getInput() == 1)
		return LOOP_QUIT;
	
	int loopState = evalInput();
	if (loopState != LOOP_CONT)
		return loopState;
	
	/* Get number value */
	char *sEnd;
	double val = strtod(input, &sEnd);
	if (sEnd == input) {
		puts("Did not enter a number.");
		return LOOP_REPEAT;
	}
	
	addToTable(tablep, varName, newVar(TYPE_NUMBER, (void *)&val));
	free(varName);
	return LOOP_NEXT;
}
