#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MAX 1000000 // size for stack and input buffer

typedef struct {
    int items[MAX];
    int top;
} Stack;


void push(Stack *s, int value) {
    s->items[++s->top] = value;
}


int pop(Stack *s) {
    return s->items[s->top--];
}


void printOut(Stack *s) {

    char b4='[';
    for(int i=0; i <= s->top; i+=1) { 
        printf("%c %d", b4, s->items[i]); 
        b4=','; 
    }
    puts(" ]");

}


int main() {

    Stack stack;
    stack.top = -1;
    char buffer[MAX];

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        char *b = strtok(buffer, " \t\n");

        while (b != NULL) {

            if (isdigit(b[0]) || (b[0] == '-' && isdigit(b[1]))) {
                push(&stack, atoi(b));
            }
            
            else if (b[0] == '+' || b[0] == '-' || b[0] == '*' || b[0] == '%') {
                
                if (stack.top < 1) {
                    printOut(&stack);
                    return 1; // error because operation is used on 1 number
                }

                int num1 = pop(&stack);  //number on the first layer of stack
                int num2 = pop(&stack);  //number on the second layer of stack

                switch (b[0]) {

                    case '+':
                        push(&stack, (num1 + num2));
                        break;
                    case '-':
                        push(&stack, (num2 - num1));
                        break;
                    case '*':
                        push(&stack, (num1 * num2));
                        break;
                    case '%':
                        push(&stack, (num2 % num1));
                        break;
                }
            }
            
            else {
                printOut(&stack);
                return 1; //unknown symbol detected
            }

            //printOut(&stack); //intermediate
            b = strtok(NULL, " \t\n");
        }
    }

    printOut(&stack);
    return 0;
}
