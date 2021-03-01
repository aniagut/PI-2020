#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct stack {
    int* elements;
    int top;
    int max_size;
} stack;

void push(stack* s, int n)
{
    s -> top++;
    s -> elements[s->top] = n;
}

int pop(stack* s)
{
    s -> top--;
    return s -> elements[s->top+1];
}

bool is_empty(stack* s)
{
    if(s -> top == -1)
        return true;
    else return false;
}

stack* new_stack(int size)
{
    stack* stos = malloc(sizeof(int*)+2*sizeof(int));
    stos -> max_size = size;
    stos -> elements = malloc(size*sizeof(int));
    stos -> top = -1;
    return stos;
}

void delete_stack(stack* s)
{
    free(s -> elements);
    free(s);
}

typedef enum entry_type {number, add, subtract, multiply, divide} entry_type;

entry_type parse(char* raw)
{
    if (raw[0] == '+') return add;
    if (raw[0] == '-') return subtract;
    if (raw[0] == '*') return multiply;
    if (raw[0] == '/') return divide;
    return number;
}

int ConvToInt(char* entry, int max_entry_size)
{
    int t;
    int result = 0;
    int mnoznik = 1;
    for(t = 0; t < max_entry_size && entry[t] != '\0'; t++) mnoznik *= 10;

    mnoznik /= 10;
    for(t = 0; t < max_entry_size && entry[t] != '\0'; t++)
    {
        result += (entry[t] - 48)*mnoznik;
        mnoznik /= 10;
    }
    return result;
}

void do_add(stack* s)
{
    int a = pop(s);
    int b = pop(s);
    push(s, b+a);
}

void do_subtract(stack* s)
{
    int a = pop(s);
    int b = pop(s);
    push(s, b-a);
}

void do_multiply(stack* s)
{
    int a = pop(s);
    int b = pop(s);
    push(s, b*a);
}

void do_divide(stack* s)
{
    int a = pop(s);
    int b = pop(s);
    push(s, b/a);
}

int read_and_calculate(int operands_count, int max_entry_size)
{
    stack* operands = new_stack(operands_count);
    char* entry = malloc((max_entry_size+1)*sizeof(char));

    while(operands_count > 0 || operands -> top > 0)
    {
        for(int i=0; i<max_entry_size; i++) entry[i] = '\0';
        scanf("%s", entry);

        if(parse(entry) == add) do_add(operands);
        else if(parse(entry) == subtract) do_subtract(operands);
        else if(parse(entry) == multiply) do_multiply(operands);
        else if(parse(entry) == divide) do_divide(operands);
        else
        {
            push(operands, ConvToInt(entry, max_entry_size));
            operands_count --;
        }
    }
    int result = pop(operands);
    delete_stack(operands);
    free(entry);
    return result;
}

int main()
{
    int operands_count, max_entry_size;
    scanf("%d", &operands_count);
    scanf("%d", &max_entry_size);
    printf("%d\n", read_and_calculate(operands_count, max_entry_size));
}

