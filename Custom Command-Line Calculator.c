/*
UserId=Moinul
Password=Moinul909
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#define MAX_LEN 256

typedef struct {
    double *data; //moinul909
    int top;
    int capacity;
} Stack;

Stack* create_stack(int capacity) {
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity; //moinul909
    stack->top = -1;
    stack->data = (double*)malloc(capacity * sizeof(double));
    return stack;
}

void push(Stack *stack, double value) {
    stack->data[++stack->top] = value;
}

double pop(Stack *stack) {
    return stack->data[stack->top--];
}

int is_empty(Stack *stack) { //moinul909
    return stack->top == -1;
}

int precedence(char op) {
    switch (op) {
        case '+':  //moinul909
        case '-': return 1;
        case '*':
        case '/': return 2;
        case '^': return 3; // Exponentiation if added later
        default: return 0;
    }
}

void handle_error(const char *message) {
    fprintf(stderr, "Error: %s\n", message);
    exit(EXIT_FAILURE);
}

// Function to evaluate the expression
double evaluate_expression(const char *expression) {
    Stack *values = create_stack(MAX_LEN);
    Stack *ops = create_stack(MAX_LEN);
    const char *ptr = expression;

    while (*ptr) {
        if (isspace(*ptr)) {
            ptr++;  //moinul909
            continue;
        }

        if (isdigit(*ptr) || *ptr == '.') {
            double value = strtod(ptr, (char **)&ptr);
            push(values, value);
        } else if (*ptr == '(') {
            push(ops, *ptr);
            ptr++;
        } else if (*ptr == ')') {
            while (!is_empty(ops) && (char)pop(ops) != '(') {
                double b = pop(values);
                double a = pop(values);
                char op = (char)pop(ops);
                double result = 0.0;

                switch (op) {
                    case '+': result = a + b; break;
                    case '-': result = a - b; break;
                    case '*': result = a * b; break;
                    case '/': result = a / b; break;
                }
                push(values, result);
            }
            ptr++;
        } else if (strchr("+-*/", *ptr)) { //moinul909
            while (!is_empty(ops) && precedence(ops->data[ops->top]) >= precedence(*ptr)) {
                double b = pop(values);
                double a = pop(values);
                char op = (char)pop(ops);
                double result = 0.0;

                switch (op) {
                    case '+': result = a + b; break;
                    case '-': result = a - b; break;
                    case '*': result = a * b; break;
                    case '/':
                        if (b == 0) handle_error("Division by zero.");
                        result = a / b; break;
                }
                push(values, result);
            }
            push(ops, *ptr);
            ptr++;
        } else {
            handle_error("Invalid character in expression.");
            return 0; // Not reached
        }
    }

    while (!is_empty(ops)) {
        double b = pop(values);
        double a = pop(values);
        char op = (char)pop(ops);
        double result = 0.0;

        switch (op) {
            case '+': result = a + b; break;
            case '-': result = a - b; break;
            case '*': result = a * b; break;
            case '/':
                if (b == 0) handle_error("Division by zero.");
                result = a / b; break;
        }
        push(values, result);
    }

    double final_result = pop(values);
    free(values->data);
    free(values);
    free(ops->data);//moinul909
    free(ops);
    return final_result;
}

int main() {
    char expression[MAX_LEN];
    printf("Custom Command-Line Calculator (moinul909)\n");
    printf("Enter an expression {without using any brackets}(or 'exit' to quit): ");

    while (fgets(expression, sizeof(expression), stdin)) {
        if (strncmp(expression, "exit", 4) == 0) {
            break;
        }
        double result = evaluate_expression(expression);
        printf("Result: %.2f\n", result);
        printf("Enter an expression (or 'exit' to quit): ");
    }

    return 0;
}
