#include <stdio.h>
#include <math.h>
#include "mylibrary.h"

typedef enum kOpts {
    OPT_H,
    OPT_P,
    OPT_S,
    OPT_E,
    OPT_A,
    OPT_F
} kOpts;

int GetOpts(int argc, char** argv, kOpts *option, int *number) {
    if (argc != 3) return 1;

    int flag = 0;

    for (int i = 1; i <= argc - 1; ++i) {
        const char* proceeding_option = argv[i];

        if ((proceeding_option[0] == '/' || proceeding_option[0] == '-') && (!proceeding_option[2]) && (!flag)) {
            flag = 1;

            switch (proceeding_option[1]) {
                case 'h':
                    *option = OPT_H;
                    break;

                case 'p':
                    *option = OPT_P;
                    break;

                case 's':
                    *option = OPT_S;
                    break;

                case 'e':
                    *option = OPT_E;
                    break;

                case 'a':
                    *option = OPT_A;
                    break;

                case 'f':
                    *option = OPT_F;
                    break;

                default:
                    return UNKNOWN_COMMAND;
                    break;
            } 
        } else {
            if (!overflow_check(proceeding_option)) return OVER_FLOW;

            double divisor = 1.0;
            int negative_found = 0;

            for (int j = 0; proceeding_option[j]; ++j) {
                if (proceeding_option[j] >= '0' && proceeding_option[j] <= '9') {
                    *number *= 10;
                    *number += proceeding_option[j] - '0';
                } else if (proceeding_option[j] == '-') {
                    if (negative_found) return PARCING_ERROR;  // ошибка, если уже встречен минус
                    negative_found = 1;
                } else {
                    return PARCING_ERROR;
                }
            }
            if(negative_found == 1) *number = 0 - *number;
            if (((*option == OPT_H) || (*option == OPT_A)) && (*number <= 0)) return INCORRECT_ARGUMENT;  // натуральное число
            if ((*option == OPT_E) && (*number > 10)) return INCORRECT_ARGUMENT;  // 1 <= x <= 10
        }
    }
    return 0;
}

int HandlerOptP(int number) {
    return isPrime(number);
}

int HandlerOptA(int number) {
    return SumToX(number);
}

unsigned long long HandlerOptF(int number) {
    return factorial(number);
}

int main (int argc, char** argv) {
    puts("\n____________________ TASK ONE ____________________\n");

    kOpts opt = 0;
    int proceeded_number = 0;
    int error = GetOpts(argc, argv, &opt, &proceeded_number);

    if (error) {
        switch(error) {
            case 1:
                puts("Incorrect number of arguments.");
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


    switch (opt) {
        case OPT_H:
            int marker = 0;
            for(int i = 1; i <= 100; ++i) {
                if(i % proceeded_number == 0) {
                    marker = 1;
                    printf("%d ", i);
                }
            }
            puts("");
            if(marker == 0) {
                puts("There is no number that is less than 100 and multiple of x");
            }
            break;

        case OPT_P:
            if (HandlerOptP(proceeded_number)) {
                puts("The number is prime.");
            } else {
                puts("The number is composite or unique.");
            }
            break;

        case OPT_S:
            char hex[9];
            int i = 0;

            if (proceeded_number == 0) {
                puts("0");
                break;
            }

            // преобразование числа в шестнадцатеричную систему
            while (proceeded_number != 0) {
                int remainder = proceeded_number % 16;
                if (remainder < 10)
                    hex[i] = remainder + '0';
                else
                    hex[i] = remainder - 10 + 'A';

                proceeded_number /= 16;
                i++;
            }

            // печатаем символы в обратном порядке через пробел
            for (int j = 0; j < i; j++) {
                printf("%c ", hex[i - j - 1]);
            }
            puts("");
            break;

        case OPT_E:
            printf("Base\t");
            for (int i = 1; i <= proceeded_number; i++) {
                printf("Exp %-10d", i);
            }
            puts("");
            for (int base = 1; base <= 10; base++) {
                printf("%d\t", base);
                for (int exp = 1; exp <= proceeded_number; exp++) {
                    printf("%10.0f    ", pow(base, exp));
                }
                puts("");
            }
            break;

        case OPT_A:
            printf("Sum from 1 to x = %d\n", HandlerOptA(proceeded_number));
            break;

        case OPT_F:
            if(proceeded_number > 20) {
                puts("Too big number");
            } else {
                printf("Factorial = %llu\n", HandlerOptF(proceeded_number));
            }
            break;
    }
    return 0;
}
