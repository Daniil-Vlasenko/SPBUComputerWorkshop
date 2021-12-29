#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct node
{
    int n;
    struct node *next;
};

typedef struct stack
{
    struct node *head;
} stack;

int stack_init (stack *s)
{
    s->head = NULL;
    return 0;
}

int stack_is_empty (const stack *s)
{
return !s->head;
}

int stack_push(stack *s, int e)
{
    struct node *n = malloc (sizeof(struct node));
    if (!n) return -1;

    n->next = s->head;
    n->n = e;
    s->head = n;

    return 0;
}

int stack_pop (stack *s, int *e)
{
    struct node *t = s->head;
    if (!t) return -1;

    if (e) *e = t->n;
    s->head = s->head->next;

    free (t);
    return 0;
}

int stack_free (stack *s)
{
    while (!stack_pop(s, NULL));
    return 0;
}



int main()
{
    int i, a, b, d;
    char c;
    stack s;
    stack_init (&s);
        while (c != '=') {
         c = getchar();         /*тоже самое что и getc(stdin). ѕосимвольно считывает строку*/
         int x;
         switch (c) {
             case '\n':
             case ' ' : break;
             case '=' : stack_pop(&s, &a); printf("%d\n", a); break;        /*осталось одно число, т.е. ответ*/
             case '+' : if (stack_pop(&s, &a) + stack_pop(&s, &b) == 0)
                            {
                                stack_push(&s, a+b); break;
                            }
                        else return -1;
             case '-' : if (stack_pop(&s, &a) + stack_pop(&s, &b) == 0)
                            {
                                stack_push(&s, b-a); break;
                            }
                        else return -1;
             case '*' : if (stack_pop(&s, &a) + stack_pop(&s, &b) == 0)
                            {
                                stack_push(&s, a*b); break;
                            }
                        else return -1;
             case '^' : if (stack_pop(&s, &a) + stack_pop(&s, &b) == 0)
                            {
                                d=pow(b,a);
                                stack_push(&s, d); break;
                            }
                        else return -1;
             default:
                 ungetc(c, stdin);
                 if (scanf("%d", &x) != 1)
                     {
                         return -1;
                     }
                 else
                     {
                         stack_push(&s, x);
                     }
                 break;
          }
    }
    return 0;
}
