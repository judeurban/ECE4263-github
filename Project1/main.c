//
// Created by Jude Urban on 9/3/21.
//

#include <stdio.h>
#include <math.h>

//functions
void Prompt(void);
void Calculation(void);
void Help(void);

//variables
double arg1;
double arg2;
double result;
char validOperatorTypes[] = {'+', '-', '*', '/', '&', '%', '^', 's', 'n', 'l'};
char operator;

void main() {
    Prompt();
    Calculation();
}

void Prompt() {

    printf("Operand:\n");
    scanf("%c", &operator);

    switch (operator) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '&':
        case '%':
        case '^':
            printf("First number:\n");
            scanf("%lf",&arg1);

            printf("Second number:\n");
            scanf("%lf",&arg2);
            printf("%lf %c %lf\n", arg1, operator, arg2);
            break;
        case 's':
        case 'n':
        case 'l':
            printf("Number:\n");
            scanf("%lf",&arg1);
            printf("%c(%lf)", operator, arg1);
            break;
        default:
            printf("invalid entry");
            return;
    }
    }

void Help(){
    printf("helpppp");
}

void Calculation() {
    switch (operator) {
        case '+':
            result = arg1 + arg2;
            break;
        case '-':
            result = arg1 - arg2;
            break;
        case '*':
            result = arg1 * arg2;
        case '/':
            if (arg2 == 0) {
                printf("= ∞ \n");
                return;
            }
            result = arg1 / arg2;
            break;
        case '&':
            result = 0;
        case '%':
            printf("\nNote: values must be integers.\n");
            result = (int)arg1 % (int)arg2;
            break;
        case '^':
            result = powl(arg1, arg2);
            break;
        case 's':
            result = sqrt(arg1);
            break;
        case 'n':
            result = log(arg1);
            break;
        case 'l':
            result = log10(arg1);
            break;
        default:
            result = 0;
            break;

            print("= %lf", result);

    }
}