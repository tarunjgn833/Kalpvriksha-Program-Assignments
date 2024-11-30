#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_EXPR_LEN 100
#define MAX_STACK_SIZE 100

const char operators[] = {'*', '/', '+', '-'};

typedef struct
{
    int items[MAX_STACK_SIZE];
    int top;
} Stack;

typedef enum
{
    NO_ERROR,
    ERROR_DIVISION_BY_ZERO,
    ERROR_INVALID_EXPRESSION,
} ErrorCode;

// stack:
void initStack(Stack *stack)
{
    stack->top = -1;
}

int isEmpty(Stack *stack)
{
    return stack->top == -1;
}

void push(Stack *stack, int value)
{
    if (stack->top < MAX_STACK_SIZE - 1)
    {
        stack->items[++(stack->top)] = value;
    }
    else
    {
        printf("Error: Stack overflow\n");
        exit(EXIT_FAILURE);
    }
}

int pop(Stack *stack)
{
    if (!isEmpty(stack))
    {
        return stack->items[(stack->top)--];
    }
    else
    {
        printf("Error: Stack underflow\n");
        exit(EXIT_FAILURE);
    }
}

// program:

int is_operator(char ch)
{
    for (int i = 0; i < sizeof(operators); i++)
    {
        if (ch == operators[i])
            return 1;
    }
    return 0;
}

int opr_priority(char op)
{
    return (op == '+' || op == '-') ? 1 : (op == '*' || op == '/') ? 2
                                                                   : 0;
}

void handle_error(ErrorCode error)
{
    switch (error)
    {
    case ERROR_DIVISION_BY_ZERO:
        printf("Error: Division by zero.\n");
        break;
    case ERROR_INVALID_EXPRESSION:
        printf("Error: Invalid expression.\n");
        break;
    default:
        printf("Error: Unknown error occurred.\n");
    }
}

int calculate(int a, int b, char op, ErrorCode *error)
{
    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        if (b == 0)
        {
            *error = ERROR_DIVISION_BY_ZERO;
            return 0;
        }
        return a / b;
    default:
        return 0;
    }
}

int evaluate_expr(const char *expr, ErrorCode *error)
{
    Stack values, ops;
    initStack(&values);
    initStack(&ops);

    int i = 0;
    int expr_len = strlen(expr);
    char currentChar;
    int lastWasOperator = 1;

    while (i < expr_len)
    {
        currentChar = expr[i];

        if (currentChar == ' ')
        {
            i++;
            continue;
        }
        else if (isdigit(currentChar) || (currentChar == '-' && lastWasOperator))
        {
            int sign = 1;
            // handles negative integers
            if (currentChar == '-')
            {
                sign = -1;
                i++;
                if (i >= expr_len || !isdigit(expr[i]))
                {
                    *error = ERROR_INVALID_EXPRESSION;
                    return 0;
                }
                currentChar = expr[i];
            }

            int val = 0;
            while (i < expr_len && (isspace(expr[i]) || isdigit(expr[i])))
            {
                if (isdigit(expr[i]))
                    val = (val * 10) + (expr[i] - '0');
                i++;
            }

            push(&values, sign * val);
            lastWasOperator = 0;
        }
        else if (is_operator(currentChar))
        {   
            if (lastWasOperator)
            {
                if (currentChar == '-')
                {
                    lastWasOperator = 1;
                    i++;
                }
                else
                {
                    *error = ERROR_INVALID_EXPRESSION;
                    return 0;
                }
                continue;
            }

            while (!isEmpty(&ops) && opr_priority(ops.items[ops.top]) >= opr_priority(currentChar))
            {
                int val2 = pop(&values);
                int val1 = pop(&values);
                char opr = (char)pop(&ops);
                int res = calculate(val1, val2, opr, error);
                if (*error != NO_ERROR)
                    return 0;
                push(&values, res);
            }
            push(&ops, currentChar);
            lastWasOperator = 1;
            i++;
        }
        else
        {
            *error = ERROR_INVALID_EXPRESSION;
            return 0;
        }
    }

    if (lastWasOperator)
    {
        *error = ERROR_INVALID_EXPRESSION;
        return 0;
    }
    
    while (!isEmpty(&ops))
    {
        if (isEmpty(&values))
        {
            *error = ERROR_INVALID_EXPRESSION;
            return 0;
        }

        int val2 = pop(&values);
        int val1 = pop(&values);
        char opr = (char)pop(&ops);

        push(&values, calculate(val1, val2, opr, error));
        if (*error != NO_ERROR)
            return 0;
    }

    if (values.top != 0)
    {
        *error = ERROR_INVALID_EXPRESSION;
        return 0;
    }

    return pop(&values);
}
int main()
{

    char input_expr[MAX_EXPR_LEN];

    // loop to run the program until user wants to quit
    while (1)
    {
        printf("Enter an expression: (type 'quit'/'exit' to quit): ");
        fgets(input_expr, MAX_EXPR_LEN, stdin);
        input_expr[strcspn(input_expr, "\n")] = '\0'; // to remove the endline character

        if (strcmp(input_expr, "exit") == 0 || strcmp(input_expr, "quit") == 0)
        {
            printf("Goodbye!\n");
            break;
        }

        ErrorCode error = NO_ERROR;
        int result = evaluate_expr(input_expr, &error);

        if (error != NO_ERROR)
        {
            handle_error(error);
        }
        else
        {
            printf("Output: %d\n", result);
        }
    }
}
