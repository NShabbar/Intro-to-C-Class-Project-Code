// Standard libraries
#include <stdio.h>
#include <math.h>


//User libraries:
#include "BOARD.h"

#ifdef PIC32
// Microchip libraries
#include <xc.h>
#endif


// **** Declare function prototypes ****
double Add(double operand1, double operand2);
double Subtract(double operand1, double operand2);
double Multiply(double operand1, double operand2);
double Divide(double operand1, double operand2);
double AbsoluteValue(double operand);
double FahrenheitToCelsius(double operand);
double Tangent(double operand);
double CelsiusToFahrenheit(double operand);
double Average(double operand1, double operand2);
double Tangent(double operand);
double Round(double operand);
//add more prototypes here

void CalculatorRun(void) {
    double operand;
    double operand1;
    double operand2;
    char sel;
    while (1) {
        printf("\n\nWelcome to NAME's calculator program! Compiled at %s %s\n", __DATE__, __TIME__);
        printf("Enter a mathematical operation to perform (*,/,+,-,m,a,c,f,t,q,r): ");
        scanf(" %s", &sel);
        if (sel == '*') {
            printf("Enter the first operand: ");
            scanf(" %lf", &operand1);
            printf("Enter the second operand: ");
            scanf(" %lf", &operand2);
            double answer = Multiply(operand1, operand2);
            printf("Result of %lf * %lf: %lf", operand1, operand2, answer);
        } else if (sel == '/') {
            printf("Enter the first operand: ");
            scanf(" %lf", &operand1);
            printf("Enter the second operand: ");
            scanf(" %lf", &operand2);
            double answer = Divide(operand1, operand2);
            printf("Result of %lf / %lf: %lf", operand1, operand2, answer);
        } else if (sel == '+') {
            printf("Enter the first operand: ");
            scanf(" %lf", &operand1);
            printf("Enter the second operand: ");
            scanf(" %lf", &operand2);
            double answer = Add(operand1, operand2);
            printf("Result of %lf + %lf: %lf", operand1, operand2, answer);
        } else if (sel == '-') {
            printf("Enter the first operand: ");
            scanf(" %lf", &operand1);
            printf("Enter the second operand: ");
            scanf(" %lf", &operand2);
            double answer = Subtract(operand1, operand2);
            printf("Result of %lf - %lf: %lf", operand1, operand2, answer);
        } else if (sel == 'm') {
            printf("Enter the first operand: ");
            scanf(" %lf", &operand1);
            printf("Enter the second operand: ");
            scanf(" %lf", &operand2);
            double answer = Average(operand1, operand2);
            printf("Result of (%lf + %lf)/2: %lf", operand1, operand2, answer);
        } else if (sel == 'a') {
            printf("Enter an operand: ");
            scanf(" %lf", &operand);
            double answer = AbsoluteValue(operand);
            printf("Result of |%lf|: %lf", operand, answer);
        } else if (sel == 'c') {
            printf("Enter an operand: ");
            scanf(" %lf", &operand);
            double answer = FahrenheitToCelsius(operand);
            printf("Result of (%lf - 32)*0.5556: %lf", operand, answer);
        } else if (sel == 'f') {
            printf("Enter an operand: ");
            scanf(" %lf", &operand);
            double answer = CelsiusToFahrenheit(operand);
            printf("Result of (%lf * 1.8) + 32: %lf", operand, answer);
        } else if (sel == 't') {
            printf("Enter an operand: ");
            scanf(" %lf", &operand);
            double answer = Tangent(operand);
            printf("Result of Tan(%lf): %lf", operand, answer);
        } else if (sel == 'q') {
            return;
        } else if (sel == 'r') {
            printf("Enter an operand: ");
            scanf(" %lf", &operand);
            double answer = Round(operand);
            printf("Result of ~%lf: %lf", operand, answer);
        } else {
            printf("The input was not valid. Please try another input");
        }
        // Your code here
        BOARD_End();
        while (1);
    }
}

/********************************************************************************
 * Define the Add function here.
 ********************************************************************************/
double Add(double operand1, double operand2) {
    double result = operand1 + operand2;
    return result;
}

/********************************************************************************
 * Define the Subtract function here.
 ********************************************************************************/
double Subtract(double operand1, double operand2) {
    double result = operand1 - operand2;
    return result;
}

/********************************************************************************
 * Define the Multiply function here.
 ********************************************************************************/
double Multiply(double operand1, double operand2) {
    double result = operand1*operand2;
    return result;
}

/********************************************************************************
 * Define the Divide function here.
 ********************************************************************************/
double Divide(double operand1, double operand2) {
    double result = operand1 / operand2;
    return result;
}

/********************************************************************************
 * Define the Absolute Value function here.
 ********************************************************************************/
double AbsoluteValue(double operand) {
    if (operand < 0) {
        double result = operand*-1;
        return result;
    } else {
        return operand;
    }
}

/*********************************************************************************
 * Define the Fahrenheit to Celsius function here.
 ********************************************************************************/
double FahrenheitToCelsius(double operand) {
    double result = (operand - 32)*0.5556;
    return result;
}

/*********************************************************************************
 * Define the Celsius to Fahrenheit function here.
 ********************************************************************************/
double CelsiusToFahrenheit(double operand) {
    double result = (operand * 1.8) + 32;
    return result;
}

/********************************************************************************
 * Define the Average function here.
 *******************************************************************************/
double Average(double operand1, double operand2) {
    double result = (operand1 + operand2) / 2;
    return result;
}

/*********************************************************************************
 * Define the Tangent function that takes input in degrees.
 ********************************************************************************/
double Tangent(double operand) {
    double degree = operand * (180 / M_PI);
    double result = tan(degree);
    return result;
}

/*********************************************************************************
 * Define the Round function here.
 * In order to receive the extra credit your calculator MUST ALSO CORRECTLY utilize
 * this function.
 ********************************************************************************/
double Round(double operand) {
    double doub_op = operand;
    int integer_op = operand;
    if (doub_op - integer_op > 0.5) {
        double result = integer_op + 1;
        return result;
    } else {
        return integer_op;
    }
}


