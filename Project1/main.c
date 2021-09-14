//
// Created by Jude Urban on 9/3/21.
//

#include <stdio.h>
#include <math.h>

//variables
char operator;
double arg1;
double arg2;

//enumerators
typedef enum Bool {false, true} Bool;   //compiles as       0,      1
Bool isActive = true;

//functions
void InputPrompt(void);
void Calculation(void);
void Help(void);
void Imaginary(void);
Bool isInteger(double);

int main()
{
    printf("\n\nECE4263 CALCULATOR\n");
    printf("When prompted for an operator, enter 'h' for help or 'e' to exit.\n");

    while(isActive)
    {
        InputPrompt();
        Calculation();
    }
    printf("goodbye.\n");
    return 0;
}

//gets arg1 (and sometimes arg2) from user
void InputPrompt()
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
        case '%':
        case '^':
        case '&':
        case '|':
            printf("First number: ");
            scanf("%lf",&arg1);

            printf("Second number: ");
            scanf("%lf",&arg2);

            if (isInteger(arg1) && isInteger(arg2))
                printf("%i %c %i", (int)arg1, operator, (int)arg2);
            else
                printf("%lf %c %lf", arg1, operator, arg2);

            break;
        case 'R':
        case 'r':
        case 'N':
        case 'n':
        case 'L':
        case 'l':
        case 'S':
        case 's':
        case 'C':
        case 'c':
            printf("Argument: ");
            scanf("%lf",&arg1);
            printf("%c(%.2lf)", operator, arg1);
            break;
        case 'I':
        case 'i':
            break;
        case 'H':
        case 'h':
            Help();
            break;
        case 'E':
        case 'e':
            isActive = false;
            break;
        default:
            printf("invalid entry.\n");
            return;
    }
}

//calculates. would you believe it?
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
            break;
        case '/':
            if (arg2 == 0) {
                printf(" = ∞\n\n");
                return;
            }
            result = arg1 / arg2;
            break;
        case '%':
            if(!isInteger(arg1) || !isInteger(arg2))
                printf("\nNote: this function only works with integers!\n");
            result = (int)arg1 % (int)arg2;
            break;
        case '^':
            result = powl(arg1, arg2);
            break;
        case '&':
            //special code just for integer operations
            if(!isInteger(arg1) || !isInteger(arg2))
            {
                printf("\nOnly integer operations allowed for this function\n");
                return;
            }
            result = (int)arg1 & (int)arg2;
            printf(" = %i\n\n", (int)result);
            return;
        case '|':
            //special code just for integer operations
            if(!isInteger(arg1) || !isInteger(arg2))
            {
                printf("\nOnly integer operations allowed for this function\n");
                return;
            }
            result = (int)arg1 | (int)arg2;
            printf(" = %i\n\n", (int)result);
            return;
        case 'R':
        case 'r':
            result = sqrt(arg1);
            break;
        case 'N':
        case 'n':
            result = log(arg1);
            break;
        case 'L':
        case 'l':
            result = log10(arg1);
            break;
        case 'S':
        case 's':
            result = sin(arg1 * M_PI / 180);
            break;
        case 'C':
        case 'c':
            result = cos(arg1 * M_PI / 180);
            break;
        case 'i':
        case 'I':
            Imaginary();
            return;
        default:
            return;

    }

    if (isInteger(result))
        printf(" = %i\n\n", (int)result);
    else
        printf(" = %lf\n\n", result);

}

//my special imaginary function converting polar <---> rectangular
void Imaginary()
{
    char inputstring[15];
    double realaxis;
    double imagaxis;
    double magnitude;
    double phase;

    printf("Convert to PHASOR or RECTANGULAR?\n");
    scanf(" %s", inputstring);

    //sine inputs as radians

    switch (inputstring[0])
    {
    case 'P':
    case 'p':
        printf("Real: ");
        scanf("%lf", &realaxis);
        printf("Imaginary: ");
        scanf("%lf", &imagaxis);

        magnitude = sqrt(pow(realaxis, 2) + pow(imagaxis, 2));
        phase = atan(imagaxis / realaxis) * 180 / M_PI;

        if(realaxis < 0 && imagaxis < 0)
            phase += 180;
        else if (realaxis < 0)
            phase += 180;

        printf("\nmagnitude: %fl \nphase: %iº\n\n", magnitude, (int)phase);

        break;
    case 'R':
    case 'r':
        printf("Magnitude: ");
        scanf("%lf", &magnitude);
        printf("Phase (in degrees, please): ");
        scanf("%lf", &phase);

        realaxis = magnitude * cos(M_PI * phase / 180);
        imagaxis = magnitude * sin(M_PI * phase / 180);

        if(imagaxis > 0)
            printf("\n%lf + j%lf\n\n", realaxis, imagaxis);
        else
            printf("\n%lf + j(%lf)\n\n", realaxis, imagaxis);
        break;
    
    default:
        return;
    }
}

//returns true for integer, false for float/double
Bool isInteger(double floatvalue)
{
    int intvalue;

    intvalue = floatvalue;

    if((floatvalue - intvalue) == 0)
        return true;
    else
        return false;

}

//i need help
void Help()
{
    printf(" ----------------------------------------\n");
    printf("|                                       |\n");
    printf("|           ECE4263 CALCULATOR          |\n");
    printf("|                                       |\n");
    printf(" ----------------------------------------\n\n");

    printf("Valid Operator Types:\n");
    printf("    addition: -------------- '+'\n");
    printf("    subtraction: ----------- '-'\n");
    printf("    multiplication: -------- '*'\n");
    printf("    division: -------------- '/'\n");
    printf("    modulo: ---------------- '%c'\n", 37);
    printf("    logical AND: ----------- '&'\n");
    printf("    logical OR: ------------ '|'\n");
    printf("    exponential: ----------- '^'\n");
    printf("    square-root: ----------- 'r'\n");
    printf("    natural-logarithm: ----- 'n'\n");
    printf("    logarithm (base 10): --- 'l'\n");
    printf("    sine (degrees): -------- 's'\n");
    printf("    cosine (degrees): ------ 'c'\n");
    printf("    imaginary: ------------- 'i'\n");
    printf("    exit: ------------------ 'e'\n\n");

    printf("Enter the operator first, then the value(s).\n\n");
}