#ifndef SMART_CALC_H
#define SMART_CALC_H

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stacks {
  char lexeme;
  struct Stacks *next;
} Stack;

typedef struct Stacks2 {
  double token;
  struct Stacks2 *next;
} Result;

int get_prioritet(char oper);
void push(Stack **top, char lexeme);
char pop(Stack **top);
void push2(Result **top, double token);
double pop2(Result **top);
int input_to_postfix(char *input_string, char *postfix_string);
int parse_input(char *input_string, double x, double *result);
int calculation(char *postfix_string, double x, double *result);
int check_braces(char *input_string);
#endif
