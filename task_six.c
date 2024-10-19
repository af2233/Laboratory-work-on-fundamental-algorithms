#include <stdio.h>
#include <math.h>
#include "mylibrary.h"

int GetOpts(int argc, char** argv, double *epsilon) {
    if (argc != 2) return INCORRECT_NUMBER_OF_ARGUMENTS;

    for (int i = 1; i <= argc - 1; ++i) {
        const char* proceeding_option = argv[i];
        if(!overflow_check(proceeding_option)) return OVER_FLOW;
    
        double divisor = 1.0;
        int decimal_point_found = 0;

        for (int j = 0; proceeding_option[j]; ++j) {
            if (proceeding_option[j] >= '0' && proceeding_option[j] <= '9') {
                if (decimal_point_found) {
                    divisor *= 10.0;
                    *epsilon += (proceeding_option[j] - '0') / divisor;
                } else {
                    *epsilon *= 10;
                    *epsilon += proceeding_option[j] - '0';
                }
            } else if (proceeding_option[j] == '.') {
                if (decimal_point_found) {
                    // ошибка, если уже встречена десятичная точка
                    return PARCING_ERROR;
                }
                decimal_point_found = 1;
            } else {
                return PARCING_ERROR;
            }
        }
    }
    if (*epsilon <= 0.0) return INCORRECT_ARGUMENT;
    return 0;
}

double func_a(double x) {
    if (x == 0) {
        return 1.0;
    }
    return x / exp(x);
}  // ln(1 + x) / x

// упрощение: x / e^x

double func_b(double x) {
    return 1 / sqrt(exp(pow(x, 2)));
}  // e^(-(x^2 / 2))

// упрощение: 1 / sqrt(e^(pow(x, 2))

double func_c(double x) {
    if (x == 0) {
        return 1.0;
    }
    return log(x);
}  // ln(1 / (1 - x)

// упрощение: lnx

double func_d(double x) {
    return pow(x, x);
}  // x^x

double rectangle_method(double (*f)(double), double epsilon) {
    double a = 0;
    double b = 1;
    double n = 1;

    double step = (b - a) / n;
    double sum = f(a) * step;
    double prev_sum = 0.0;

    while ((sum - prev_sum) > epsilon) {
        prev_sum = sum;
        n *= 2;
        step = (b - a) / n;
        sum = 0.0;

        for(int i = 0; i < n; i++) {
            double x = a + i * step;
            sum += f(x) * step;
        }
    }
    return sum;
}


int main (int argc, char** argv) {
    puts("\n____________________ TASK SIX ____________________\n");

    double epsilon = 0.0;

    int error = GetOpts(argc, argv, &epsilon);

    if (error) {
        switch(error) {

            case 1:
                puts("Incorrect number of arguments");
                break;

            case 2:
                puts("Incorrect argument");
                break;

            case 3:
                puts("Overflow");
                break;

            case 4:
                puts("Unknown command");
                break;

            case 5:
                puts("Parsing error");
                break;

            case 6:
                puts("Incorrect option");
                break;

            case 7:
                puts("Opening file error");
                break;

            case 8:
                puts("Incorrect file name");
                break;

            default:
                puts("Error occured");
                break;
        }
        return 1;
    }

    puts("Limits of integration a = 0, b = 1");
    printf("Integral of a function log(1 + x) / x\t\t~ %.12f\n", rectangle_method(func_a, epsilon));
    printf("Integral of a function exp(-(pow(x, 2) / 2))\t~ %.12f\n", rectangle_method(func_b, epsilon));
    printf("Integral of a function log(1 / (1 - x))\t\t~ %.12f\n", rectangle_method(func_c, epsilon));
    printf("Integral of a function pow(x, x)\t\t~ %.12f\n", rectangle_method(func_d, epsilon));
    return 0;
}
