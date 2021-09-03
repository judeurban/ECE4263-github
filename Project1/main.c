//
// Created by Jude Urban on 9/3/21.
//

#include <stdio.h>
#include <math.h>

double Prompt(void);

double arg1;
double arg2;

char validOperatorTypes[] = {'+', '-', '*', '/', '&', '%', '^', 's', 'n', 'l'};
char operator;

void main() {
    printf("\n= %lf", Prompt());
}

double Prompt() {
    printf("Enter first operator\n");
    scanf("%lf",&arg1);
    printf("Enter operand\n");
    scanf("%c", &operator);
    scanf("%c", &operator);
    printf("Enter second operator\n");
    scanf("%lf",&arg2);

    printf("%lf %c %lf", arg1, operator, arg2);

    switch (operator) {
        case '+':
            return arg1 + arg2;
        case '-':
            return arg1 - arg2;
        case '*':
            return arg1 * arg2;
        case '/':
            if(arg2 == 0)
            {
                printf("You cannot divide by zero.\n");
                return 0;
            }
            return arg1 / arg2;
        case '^':
            return powl(arg1, arg2);
        case 's'
            return sqrt()
    }

}