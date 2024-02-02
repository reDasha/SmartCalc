#include "smart_calc.h"

int parse_input(char *input_string, double x, double *result) {
  int error = 0;
  char parse_string[255] = {0};
  for (int k = 0; input_string[k] != '\0'; ++k) {
    if (isalpha(input_string[k]) && !strchr("cstalm", input_string[k]) &&
        input_string[k] != 'x') {
      error = 1;
      break;
    }
    if (input_string[k] != ' ') {
      if (input_string[k] == 'm' && input_string[k + 1] == 'o' &&
          input_string[k + 2] == 'd') {
        strcat(parse_string, "m");
        k += 2;
        continue;
      }
      if (isalpha(input_string[k]) && strchr("cstal", input_string[k])) {
        char string_func[8] = {0};
        while (isalpha(input_string[k]) && input_string[k] != '(') {
          strncat(string_func, &input_string[k], 1);
          ++k;
        }
        if (!strcmp(string_func, "cos"))
          strcat(parse_string, "c");
        else if (!strcmp(string_func, "sin"))
          strcat(parse_string, "s");
        else if (!strcmp(string_func, "tan"))
          strcat(parse_string, "t");
        else if (!strcmp(string_func, "acos"))
          strcat(parse_string, "C");
        else if (!strcmp(string_func, "asin"))
          strcat(parse_string, "S");
        else if (!strcmp(string_func, "atan"))
          strcat(parse_string, "T");
        else if (!strcmp(string_func, "sqrt"))
          strcat(parse_string, "q");
        else if (!strcmp(string_func, "ln"))
          strcat(parse_string, "l");
        else if (!strcmp(string_func, "log"))
          strcat(parse_string, "L");
      }
      if (input_string[k] == '-' &&
          (strlen(parse_string) == 0 || strchr("(/+", parse_string[strlen(parse_string) - 1]))) {
        strcat(parse_string, "0");
      }
      if(input_string[k] == '-' && parse_string[strlen(parse_string) - 1] == '*') error = 1;
      strncat(parse_string, &input_string[k], 1);
    }
  }
  char postfix_string[255] = {0};
  if (input_to_postfix(parse_string, postfix_string) ||
      calculation(postfix_string, x, result) || check_braces(input_string)) {
    error = 1;
  }
  return error;
}

int get_prioritet(char oper) {
  int res = 0;
  switch (oper) {
    case '(':
      res = 1;
      break;
    case ')':
      res = 1;
      break;
    case 's':
      res = 2;
      break;
    case 'c':
      res = 2;
      break;
    case 't':
      res = 2;
      break;
    case 'C':
      res = 2;
      break;
    case 'S':
      res = 2;
      break;
    case 'T':
      res = 2;
      break;
    case 'l':
      res = 2;
      break;
    case 'L':
      res = 2;
      break;
    case 'q':
      res = 5;
      break;
    case '+':
      res = 3;
      break;
    case '-':
      res = 3;
      break;
    case '*':
      res = 4;
      break;
    case '/':
      res = 4;
      break;
    case 'm':
      res = 4;
      break;
    case '^':
      res = 5;
      break;
  }
  return res;
}

int input_to_postfix(char *input_string, char *postfix_string) {
  int error = 0;
  int check_br = 0;
  Stack *top = NULL;
  for (int i = 0; input_string[i] != '\0'; ++i) {
    if (input_string[i] == 'x') {
      strcat(postfix_string, "x");
      strcat(postfix_string, "|");
    }
    if (isdigit(input_string[i])) {
      char string_number[256] = {0};
      for (int k = i; isdigit(input_string[k]) || (input_string[k] == '.');
           ++k, ++i) {
        strncat(string_number, &input_string[k], 1);
      }
      strcat(postfix_string, string_number);
      strcat(postfix_string, "|");
    }
    if (strchr("(cstCSTqlL", input_string[i])) {
      push(&top, input_string[i]);
      if (input_string[i] == '(') check_br = 1;
    }
    if (strchr("+-*/^m", input_string[i])) {
      while (top &&
             get_prioritet(top->lexeme) >= get_prioritet(input_string[i])) {
        if (top->lexeme != ',') {
          postfix_string[strlen(postfix_string)] = pop(&top);
          strcat(postfix_string, "|");
        }
      }
      push(&top, input_string[i]);
    }
    if (input_string[i] == ')') {
      if (check_br == 0) {
        error = 1;
        break;
      }
      while (top && top->lexeme != '(') {
        postfix_string[strlen(postfix_string)] = pop(&top);
        strcat(postfix_string, "|");
      }
      pop(&top);
      if (top && strchr("cstCSTqlL", top->lexeme)) {
        postfix_string[strlen(postfix_string)] = pop(&top);
        strcat(postfix_string, "|");
      }
    }
  }
  if (!error) {
    while (top) {
      if (top->lexeme == '(' || top->lexeme == ')') {
        error = 1;
        break;
      }
      postfix_string[strlen(postfix_string)] = pop(&top);
      strcat(postfix_string, "|");
    }
  }
  if (top) free(top);
  return error;
}

int check_braces(char *input_string) {
  int count_l = 0;
  int count_r = 0;
  for (int i = 0; input_string[i] != '\0'; ++i) {
    if (input_string[i] == '(') ++count_l;
    if (input_string[i] == ')') ++count_r;
  }
  return abs(count_l - count_r);
}

void push(Stack **top, char lexeme) {
  Stack *new_top = malloc(sizeof(Stack));
  new_top->next = *top;
  new_top->lexeme = lexeme;
  *top = new_top;
}

char pop(Stack **top) {
  char lexeme = {0};
  if (*top) {
    Stack *out;
    out = *top;
    *top = (*top)->next;
    lexeme = out->lexeme;
    free(out);
  }
  return lexeme;
}

void push2(Result **top, double token) {
  Result *new_top = malloc(sizeof(Result));
  new_top->next = *top;
  new_top->token = token;
  *top = new_top;
}

double pop2(Result **top) {
  double token = 0.0;
  if (*top) {
    Result *out;
    out = *top;
    *top = (*top)->next;
    token = out->token;
    free(out);
  }
  return token;
}

int calculation(char *postfix_string, double x, double *result) {
  int error = 0;
  Result *top = NULL;
  char sep[2] = "|";
  char *token = {0};
  token = strtok(postfix_string, sep);
  while (token) {
    if (!strcmp(token, "x")) {
      push2(&top, x);
    }
    if (isdigit(token[0])) {
      push2(&top, atof(token));
    }
    if (strchr("+-*/^m", token[0])) {
      double one = pop2(&top);
      double two = pop2(&top);
      switch (token[0]) {
        case '+':
          push2(&top, one + two);
          break;
        case '-':
          push2(&top, two - one);
          break;
        case '*':
          push2(&top, one * two);
          break;
        case '/':
          if (one != 0) {
            push2(&top, two / one);
          } else {
              error = 1;
              break;
          }
          break;
        case '^':
          push2(&top, pow(two, one));
          break;
        case 'm':
          push2(&top, fmod(two, one));
          break;
      }
    }
    if (strchr("cstCSTlLq", token[0])) {
      double num = pop2(&top);
      switch (token[0]) {
        case 'c':
          push2(&top, cos(num));
          break;
        case 's':
          push2(&top, sin(num));
          break;
        case 't':
          push2(&top, tan(num));
          break;
        case 'C':
          push2(&top, acos(num));
          break;
        case 'S':
          push2(&top, asin(num));
          break;
        case 'T':
          push2(&top, atan(num));
          break;
        case 'l':
          push2(&top, log(num));
          break;
        case 'L':
          push2(&top, log10(num));
          break;
        case 'q':
          push2(&top, sqrt(num));
          break;
      }
    }
    token = strtok(NULL, sep);
  }
  if (top) {
    *result = pop2(&top);
  }
  if (top) {
    error = 1;
    free(top);
  }
  return error;
}
