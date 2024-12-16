#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "stack.h"

#define MAX_EXPR_LEN 100

const char operators[] = {'*', '/', '+', '-'}; //valid operators

typedef enum
{
    NO_ERROR,
    ERROR_DIVISION_BY_ZERO,
    ERROR_INVALID_EXPRESSION,
} ErrorCode;

// program:
int is_valid_operator(char ch)
{
    for (int i = 0; i < sizeof(operators); i++)
    {
        if (ch == operators[i])
            return 1;
    }
    return 0;
}

int get_operator_precedence(char op)
{
    switch (op)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        return 0;
    }
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

int perform_operation(int a, int b, char op, ErrorCode *error)
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

int parse_number(const char *expr, int *index, int expr_len, int *sign, ErrorCode *error)
{
    int value = 0;
    *sign = 1;

    if (expr[*index] == '-')
    {
        *sign = -1;
        (*index)++;
        if (*index >= expr_len || !isdigit(expr[*index]))
        {
            *error = ERROR_INVALID_EXPRESSION;
            return 0;
        }
    }
    // parses characters of expression to number
    while (*index < expr_len && (isspace(expr[*index]) || isdigit(expr[*index])))
    {
        if (isdigit(expr[*index]))
            value = (value * 10) + (expr[*index] - '0');
        (*index)++;
    }

    return value;
}

int final_evaluation(Stack *value_stack, Stack *operator_stack, ErrorCode *error)
{
    while (!operator_stack->is_empty(operator_stack))
    {
        if (value_stack->is_empty(value_stack))
        {
            *error = ERROR_INVALID_EXPRESSION;
            return 0;
        }

        int operand2 = value_stack->pop(value_stack);
        int operand1 = value_stack->pop(value_stack);
        char current_operator = (char)operator_stack->pop(operator_stack);

        int result = perform_operation(operand1, operand2, current_operator, error);
        if (*error != NO_ERROR)
            return 0;

        value_stack->push(value_stack, result);
    }

    if (value_stack->top != 1)
    {
        *error = ERROR_INVALID_EXPRESSION;
        return 0;
    }
    return value_stack->pop(value_stack);
}

int evaluate_expression(const char *expr, ErrorCode *error)
{
    Stack *values_stack = create_stack(50);
    Stack *operator_stack = create_stack(50);

    int i = 0;
    int result = 0;
    int expr_len = strlen(expr);
    char current_char;
    int previous_token_was_operator = 1;

    while (i < expr_len)
    {
        current_char = expr[i];

        // skips spaces
        if (current_char == ' ')
        {
            i++;
            continue;
        }
        else if (isdigit(current_char) || (current_char == '-' && previous_token_was_operator))
        {
            int sign;
            int value = parse_number(expr, &i, expr_len, &sign, error);
            if (*error != NO_ERROR)
                return 0;

            values_stack->push(values_stack, sign * value);
            previous_token_was_operator = 0;
        }
        else if (is_valid_operator(current_char))
        {
            if (previous_token_was_operator)
            {
                if (current_char == '-')
                {
                    previous_token_was_operator = 1;
                    i++;
                }
                else
                {
                    *error = ERROR_INVALID_EXPRESSION;
                    return 0;
                }
                continue;
            }

            while (!operator_stack->is_empty(operator_stack) && get_operator_precedence(operator_stack->peek(operator_stack)) >= get_operator_precedence(current_char))
            {
                int second_operand = values_stack->pop(values_stack);
                int first_operand = values_stack->pop(values_stack);
                char opr = (char)operator_stack->pop(operator_stack);
                int res = perform_operation(first_operand, second_operand, opr, error);
                if (*error != NO_ERROR)
                    return 0;
                values_stack->push(values_stack, res);
            }
            operator_stack->push(operator_stack, current_char);
            previous_token_was_operator = 1;
            i++;
        }
        else
        {
            *error = ERROR_INVALID_EXPRESSION;
            return 0;
        }
    }

    if (previous_token_was_operator)
    {
        *error = ERROR_INVALID_EXPRESSION;
        return 0;
    }

    result = final_evaluation(values_stack, operator_stack, error);

    // destroys both stacks, basically frees the arrays inside
    values_stack->destroy(values_stack);
    operator_stack->destroy(operator_stack);

    // frees the stack pointers
    free(values_stack);
    free(operator_stack);

    return result;
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
        int result = evaluate_expression(input_expr, &error);

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
