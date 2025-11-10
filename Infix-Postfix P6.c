#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STACK_SIZE 100

// Stack structure for Infix to Postfix conversion
char operatorStack[MAX_STACK_SIZE];
int operatorTop = -1;

// Stack structure for Postfix evaluation
int operandStack[MAX_STACK_SIZE];
int operandTop = -1;

// Stack operations for operatorStack
void pushOperator(char op) 
{
    if (operatorTop == MAX_STACK_SIZE - 1) 
    {
        printf("Operator stack overflow!\n");
        exit(1);
    }
    operatorStack[++operatorTop] = op;
}

char popOperator() 
{
    if (operatorTop == -1) 
    {
        return '\0'; // Indicates empty stack
    }
    return operatorStack[operatorTop--];
}

char peekOperator() 
{
    if (operatorTop == -1) 
    {
        return '\0';
    }
    return operatorStack[operatorTop];
}

int isOperatorEmpty() 
{
    return operatorTop == -1;
}

// Stack operations for operandStack
void pushOperand(int val) 
{
    if (operandTop == MAX_STACK_SIZE - 1) 
    {
        printf("Operand stack overflow!\n");
        exit(1);
    }
    operandStack[++operandTop] = val;
}

int popOperand() 
{
    if (operandTop == -1) 
    {
        printf("Operand stack underflow!\n");
        exit(1);
    }
    return operandStack[operandTop--];
}

// Function to get precedence of operators
int getPrecedence(char op) 
{
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0; // For '(' and other characters
}

// Function to convert Infix to Postfix
void infixToPostfix(char infix[], char postfix[]) 
{
    int i, j;
    char symbol, poppedChar;

    for (i = 0, j = 0; infix[i] != '\0'; i++) 
    {
        symbol = infix[i];

        if (isalnum(symbol)) 
        { // Operand
            postfix[j++] = symbol;
        } else if (symbol == '(')
         {
            pushOperator(symbol);
        } else if (symbol == ')') 
        {
            while (!isOperatorEmpty() && peekOperator() != '(') 
            {
                postfix[j++] = popOperator();
            }
            if (!isOperatorEmpty() && peekOperator() == '(') 
            {
                popOperator(); // Pop '('
            }
        } else if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/') 
        {
            while (!isOperatorEmpty() && getPrecedence(peekOperator()) >= getPrecedence(symbol)) 
            {
                postfix[j++] = popOperator();
            }
            pushOperator(symbol);
        }
    }

    while (!isOperatorEmpty()) {
        postfix[j++] = popOperator();
    }
    postfix[j] = '\0'; // Null-terminate the postfix string
}

// Function to evaluate Postfix expression
int evaluatePostfix(char postfix[]) {
    int i;
    char symbol;
    int op1, op2, result;

    for (i = 0; postfix[i] != '\0'; i++) {
        symbol = postfix[i];

        if (isdigit(symbol)) { // Operand (assuming single digit for simplicity)
            pushOperand(symbol - '0'); // Convert char to int
        } else if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/') {
            op2 = popOperand();
            op1 = popOperand();

            switch (symbol) {
                case '+': result = op1 + op2; break;
                case '-': result = op1 - op2; break;
                case '*': result = op1 * op2; break;
                case '/': result = op1 / op2; break;
            }
            pushOperand(result);
        }
    }
    return popOperand(); // Final result
}

int main() 
{
    char infix[MAX_STACK_SIZE];
    char postfix[MAX_STACK_SIZE];

    printf("Enter infix expression (single char operands/operators, +,-,*,/ only): ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);

    // For evaluation, assume operands are single-digit numbers for simplicity
    // If operands can be variables, a mapping from char to value would be needed.
    printf("Result of evaluation: %d\n", evaluatePostfix(postfix));

    return 0;
}
