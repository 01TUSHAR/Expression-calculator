/// Calculator

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SIZE 100

int stack[SIZE];
char infix[SIZE], postfix[SIZE];
int top = -1;
// double result = 0;

void push(int s)
{
    if (top == SIZE - 1)
    {
        printf("\nOverflow!!");
        exit(1);
    }
    top++;
    stack[top] = s;
}

int pop()
{
    int num;
    if (top == -1)
    {
        printf("Wrong Expression\n");
        exit(1);
    }
    num = stack[top];
    top--;
    return num;
}

int isEmpty()
{
    if (top == -1)
        return 1;
    else
        return 0;
}

int space(char c)
{
    if (c == ' ' || c == '\t')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int isDigit(char c)
{
    return (c >= '0' && c <= '9');
}

int isNegativeSign(char c)
{
    return (c == '-');
}

int precedence(char symbol)
{
    switch (symbol)
    {
    case '/':
    case '*':
        return 2;
    case '+':
    case '-':
        return 1;
    default:
        return 0;
    }
}

void display()
{
    printf("The equivalent postfix expression is: %s\n", postfix);
}

void inToPost()
{
    int i, j = 0;
    char next, symbol;
    for (i = 0; i < strlen(infix); i++)
    {
        symbol = infix[i];
        next = infix[i + 1];

        if (!space(symbol))
        {
            if (isDigit(symbol) || (isNegativeSign(symbol) && infix[i + 1] != ' '))
            {
                // If it's a digit or a negative sign, append it to the postfix expression
                while (isDigit(infix[i]) || (isNegativeSign(infix[i])))
                {
                    postfix[j++] = infix[i++];
                }
                i--;                // Adjust the index
                postfix[j++] = ' '; // Add a space to separate multi-digit numbers
            }
            else
            {
                switch (symbol)
                {
                case '(':
                    push(symbol);
                    break;

                case ')':
                    while ((next = pop()) != '(')
                    {
                        postfix[j++] = next;
                        postfix[j++] = ' ';
                    }
                    break;

                case '+':
                case '-':
                case '*':
                case '/':
                    while (!isEmpty() && precedence(stack[top]) >= precedence(symbol))
                    {
                        postfix[j++] = pop();
                        postfix[j++] = ' ';
                    }
                    push(symbol);
                    break;

                default:
                    postfix[j++] = symbol;
                    postfix[j++] = ' ';

                    break;
                }
            }
        }
    }
    while (!isEmpty())
    {
        postfix[j++] = pop();
        postfix[j++] = ' ';
    }
    postfix[j++] = '\0';
}

int post_eval()
{
    int i, num, a, b;
    char strNum[10];
    for (i = 0; i < strlen(postfix); i++)
    {
        if (isDigit(postfix[i]) || (isNegativeSign(postfix[i]) && isDigit(postfix[i + 1])))
        {
            int k = 0;
            while (postfix[i] != ' ' && postfix[i] != '\0')
            {
                strNum[k++] = postfix[i++];
            }
            strNum[k] = '\0';
            num = atoi(strNum);
            push(num);
        }
        else if (postfix[i] != ' ')
        {
            a = pop();
            b = pop();

            switch (postfix[i])
            {
            case '+':
                push(b + a);
                break;

            case '-':
                push(b - a);
                break;

            case '*':
                push(b * a);
                break;

            case '/':
                push(b / a);
                break;
            }
        }
    }
    return pop();
}

FILE *historyFile;
void openHistoryFile()
{
    historyFile = fopen("history.txt", "a");
    if (historyFile == NULL)
    {
        printf("Error opening history file!\n");
        exit(1);
    }
}

void closeHistoryFile()
{
    fclose(historyFile);
}

void recordHistory(char *expression, double result)
{
    fprintf(historyFile, "Expression: %s\nResult: %f\n\n", expression, result);

}

void displayHistory()
{
    printf("***************************************************************\n");
    printf("                      CALCULATION HISTORY                      \n");
    printf("***************************************************************\n\n");
    FILE *historyFile = fopen("history.txt", "r");
    if (historyFile == NULL)
    {
        printf("Error opening history file!\n");
        exit(1);
    }

    printf("Calculation History:\n");
    char c;
    while ((c = fgetc(historyFile)) != EOF)
    {
        printf("%c", c);
    }

    fclose(historyFile);
    printf("***************************************************************\n");
    printf("                         MAIN MENU                             \n");
    printf("***************************************************************\n\n");
}


void clearHistory()
{
    FILE *historyFile = fopen("history.txt", "w");
    if (historyFile == NULL)
    {
        printf("Error opening history file!\n");
        exit(1);
    }

    printf("***************************************************************\n");
    printf("                         CLEAR HISTORY                         \n");
    printf("***************************************************************\n\n");

    fclose(historyFile);
}

void arithmeticFunction()
{
    printf("***************************************************************\n");
    printf("                    ARITHMETIC OPERATION                       \n");
    printf("***************************************************************\n\n");
    double num1, num2, result = 0;
    int choice;
    while (1)
    {
        printf("\n1. Addition\n2. Substraction\n3. Multiplication\n4. Division\n5. Clear Result\n6. Main Menu\n\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            if (result == 0)
            {
                printf("Enter 1st number: ");
                scanf("%lf", &num1);
                printf("Enter 2nd number: ");
                scanf("%lf", &num2);
                result = num1 + num2;
                printf("Result: %f\n", result);
            }
            else
            {
                printf("Enter a number to Add: ");
                scanf("%lf", &num1);
                result = result + num1;
                printf("Result: %f\n", result);
            }
            break;

        case 2:
            if (result == 0)
            {
                printf("Enter 1st number: ");
                scanf("%lf", &num1);
                printf("Enter 2nd number: ");
                scanf("%lf", &num2);
                result = num1 - num2;
                printf("Result: %f\n", result);
            }
            else
            {
                printf("Enter a number to Subtract: ");
                scanf("%lf", &num1);
                result = result - num1;
                printf("Result: %f\n", result);
            }
            break;

        case 3:
            if (result == 0)
            {
                printf("Enter 1st number: ");
                scanf("%lf", &num1);
                printf("Enter 2nd number: ");
                scanf("%lf", &num2);
                result = num1 * num2;
                printf("Result: %f\n", result);
            }
            else
            {
                printf("Enter a number to Multiply: ");
                scanf("%lf", &num1);
                result = result * num1;
                printf("Result: %f\n", result);
            }
            break;
        case 4:
            if (result == 0)
            {
                printf("Enter 1st number: ");
                scanf("%lf", &num1);
                printf("Enter 2nd number(Not Zero): ");
                scanf("%lf", &num2);
                if (num2 == 0)
                {
                    printf("Error!! Cannot Divivde by Zero\n");
                }
                else
                {
                    result = num1 / num2;
                }
                printf("Result: %f\n", result);
            }
            else
            {
                printf("Enter a number to Divide(Not Zero): ");
                scanf("%lf", &num1);
                if (num1 == 0)
                {
                    printf("Error!! Cannot Divivde by Zero\n");
                }
                else
                {
                    result = num1 / num2;
                }
                printf("Result: %f\n", result);
            }
            break;

        case 5:
            result = 0;
            break;
        case 6:
            printf("***************************************************************\n");
            printf("                         MAIN MENU                             \n");
            printf("***************************************************************\n\n");
            return;

        default:
            break;
        }
    }
}

double isDegree()
{
    double angle;
    int option;
    printf("1. In Degress\n2. In Radian\n");
    printf("Enter choice:\n");
    scanf("%d", &option);
    if (option == 1)
    {
        printf("Enter angle: ");
        scanf("%lf", &angle);
        angle = angle * (3.141592653589793 / 180);
    }
    else if (option == 2)
    {
        printf("Enter angle: ");
        scanf("%lf", &angle);
    }
    return angle;
}

void trigonometricOperation()
{
    double angle;
    // int isDegree;
    double result;
    int choice;
    printf("***************************************************************\n");
    printf("                  TRIGONOMETRIC OPERATION                      \n");
    printf("***************************************************************\n\n");
    while (1)
    {

        printf("\n1. Sin\n2. Cos\n3. Tan\n4. Cot\n5. Sec\n6. Cosec\n7. Asin\n8. Acos\n9. Atan\n10. Main Menu\n\n");
        scanf("%d", &choice);
        switch (choice)
        {

        case 1:
            // Sine function
            angle = isDegree();
            result = sin(angle);
            printf("Result Sin(%f) = %f\n\n", angle, result);
            break;
        case 2:
            // Cosine function
            angle = isDegree();
            result = cos(angle);
            printf("Result Cos10(%.2f) = %f\n\n", angle, result);
            break;
        case 3:
            // Tangent function
            angle = isDegree();
            result = tan(angle);
            printf("Result Tan(%.2f) = %f\n\n", angle, result);

            break;
        case 4:
            // Cotangent function
            angle = isDegree();
            result = 1.0 / tan(angle);
            printf("Result Cot(%.2f) = %f\n\n", angle, result);
            break;
        case 5:
            // Secant function
            angle = isDegree();
            result = 1.0 / cos(angle);
            printf("Result Sec(%.2f) = %f\n\n", angle, result);

            break;
        case 6:
            // Cosecant function
            angle = isDegree();
            result = 1.0 / sin(angle);
            printf("Result Cosec(%.2f) = %f\n\n", angle, result);

            break;

        case 7:
            // Arcsine function
            angle = isDegree();
            result = asin(angle);
            printf("Result Asin(%.2f) = %f\n\n", angle, result);
            break;

        case 8:
            // Arccosine function
            angle = isDegree();
            result = acos(angle);
            printf("Result Acos(%.2f) = %f\n\n", angle, result);
            break;

        case 9:
            // Arctangent function
            angle = isDegree();
            result = atan(angle);
            printf("Result Atan(%.2f) = %f\n\n", angle, result);
            break;

        case 10:
            printf("***************************************************************\n");
            printf("                         MAIN MENU                             \n");
            printf("***************************************************************\n\n");
            return;

        default:
            // Handle invalid operation
            printf("Invalid trigonometric operation.\n");
            printf("Result = 0.0"); // You can choose an appropriate default value
            break;
        }
    }
}

void expression()
{
    openHistoryFile();
    printf("***************************************************************\n");
    printf("                    EXPRESSION CALCULATION                     \n");
    printf("***************************************************************\n\n");
    double result = 0;
    int choice;
    while (1)
    {
        printf("1. Contiune and Calculate Expression\n2. Clear Result and Start New Calculation\n3. Main Menu\n\n");
        scanf("%d", &choice);
        while (getchar() != '\n')
            ;

        switch (choice)
        {
        case 1:
            printf("Enter Expression to Calculate: ");
            gets(infix);
            inToPost();
            if(result == 0){
            result = result + post_eval();
            printf("Total Result: %f\n\n", result);
            recordHistory(infix, result);
            }
            else{
            printf("Current Result: %f\n", post_eval());
            result = result + post_eval();
            printf("Total Result: %f\n\n", result);
            recordHistory(infix, result);
            }
            break;

        case 2:
            printf("Enter Expression to Calculate: ");
            gets(infix);
            result = 0;
            inToPost();
            result = post_eval();
            printf("Result: %f\n\n", result);
            recordHistory(infix, result);
            break;

        case 3:
            printf("***************************************************************\n");
            printf("                         MAIN MENU                             \n");
            printf("***************************************************************\n\n");
            closeHistoryFile();
            return;

        default:
            printf("Invalid choice");
            break;
        }
    }
}

int main()
{
    openHistoryFile();
    printf("***************************************************************\n");
    printf("                         CALCULATOR                            \n");
    printf("***************************************************************\n\n");
    int choice;
    // int choice2;
    double num1, num2, result = 0;
    while (1)
    {
        printf("1. Expression Calculation\n2. Arithmetic Calculations\n3. Trigonometric Operations\n4. History\n5. Clear History\n6. Exit\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            expression();
            break;

        case 2:
            arithmeticFunction();
            break;

        case 3:
            trigonometricOperation();
            break;

        case 4:
            displayHistory();
            printf("\n");
            break;

        case 5:
            clearHistory();
            break;

        case 6:
            closeHistoryFile();
            exit(0);
            break;

        default:
            printf("Invalid Choice!!\nChose Again\n");
            break;
        }
    }

    return 0;
}
