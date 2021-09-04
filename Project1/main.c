//
// Created by Jude Urban on 9/3/21.
//

#include <stdio.h>
#include <math.h>
#include <time.h>

enum Bool {false, true};

//functions
void Prompt(void);
void Calculation(void);
void Help(void);

//variables
double arg1;
double arg2;
char validOperatorTypes[] = {'+', '-', '*', '/', '&', '%', '^', 's', 'n', 'l'};
char operator;
enum Bool isActive = true;

int main()
{
    printf("ECE4263 CALCULATOR\n");
    printf("When prompted for an operator, enter 'h' for help or 'e' to exit.\n");

    while(isActive)
    {
        Prompt();
        Calculation();
    }
    return 0;
}

void Prompt()
{
    operator = '\0';
    printf("Operator:\n");
    scanf(" %c", &operator);

    switch (operator)
    {
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
        case 'h':
            Help();
            break;
        case 'e':
            isActive = false;
            break;
        default:
            //printf("invalid entry.\n");
            return;
    }
}

void Calculation() 
{
    double result;
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
            return;

    }

    printf("= %lf\n", result);

}

void Help()
{
    printf(" ----------------------------------------\n");
    printf("|                                       |\n");
    printf("|           ECE4263 CALCULATOR          |\n");
    printf("|                                       |\n");
    printf(" ----------------------------------------\n\n");

    printf("Valid Operator Types:\n");
    printf("    '+', '-', '*', '/', '&', modulo, '^', 's', 'n', 'l'\n\n");

    printf("Enter the operator first, then the value(s).\n\n");

    printf("Once the result is computed, enter another operator to \ncontinue computing. Press enter to exit the program");
    // char validOperatorTypes[] = {'+', '-', '*', '/', '&', '%', '^', 's', 'n', 'l'};
}