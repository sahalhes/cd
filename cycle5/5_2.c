/* Simple TAC: single-character operands, binary operators and parentheses. */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char input[100], operators[100], values[100][12];
char code[100][80];
int top = -1, count = 0, lines = 0, temporary = 0;
int precedence(char c) { return (c == '*' || c == '/') ? 2 : 1; }

void reduce(void) {
    char left[12], right[12], dest[12];
    strcpy(right, values[--count]);
    strcpy(left, values[--count]);
    sprintf(dest, "t%d", ++temporary);
    char op = operators[top--];
    snprintf(code[lines++], 80, "%c\t%s\t%s\t%s\t\t%s = %s %c %s",
             op, dest, left, right, dest, left, op, right);
    strcpy(values[count++], dest);
}

int main(void) {
    int operand = 1;
    printf("Enter expression (e.g. a=b+c*d): ");
    if (scanf("%99s", input) != 1) return 1;
    if (!isalpha((unsigned char)input[0]) || input[1] != '=' || !input[2]) goto invalid;
    for (int i = 2; input[i]; i++) {
        char c = input[i];
        if (isalnum((unsigned char)c)) {
            if (!operand) goto invalid;
            values[count][0] = c; values[count++][1] = '\0'; operand = 0;
        } else if (c == '(') {
            if (!operand) goto invalid;
            operators[++top] = c;
        } else if (c == ')') {
            if (operand) goto invalid;
            while (top >= 0 && operators[top] != '(') reduce();
            if (top < 0) goto invalid;
            top--;
        } else if (strchr("+-*/", c)) {
            if (operand) goto invalid;
            while (top >= 0 && operators[top] != '(' &&
                   precedence(operators[top]) >= precedence(c)) reduce();
            operators[++top] = c; operand = 1;
        } else goto invalid;
    }
    if (operand) goto invalid;
    while (top >= 0) {
        if (operators[top] == '(') goto invalid;
        reduce();
    }
    if (count != 1) goto invalid;
    printf("\nOp\tDest\tArg1\tArg2\t\tThree Address Code\n");
    for (int i = 0; i < lines; i++) puts(code[i]);
    printf("=\t%c\t%s\t-\t\t%c = %s\n", input[0], values[0], input[0], values[0]);
    return 0;
invalid:
    printf("Invalid expression: use single-character operands and binary + - * /\n");
    return 1;
}
