#include <math.h>
#include <stdlib.h>
#include "mylibrary.h"

unsigned long long factorial(int num) {
    if (num < 0) return 1;
    unsigned long long result = 1;
    for (int i = 1; i <= num; i++) {
        result *= i;
    }
    return result;
}

unsigned long long double_factorial(unsigned long long num) {
    if (num < 0) return 1;
    unsigned long long result = 1;
    for (int i = num; i > 0; i -= 2) {
        result *= i;
    }
    return result;
}

int overflow_check(const char* arg) {
    int MAX_LENGTH = 20;
    int len = 0;
    for(int i = 0; arg[i]; ++i) {
        len++;
    }
    return (len <= MAX_LENGTH);
}

int isPrime(int num) {
    if (num <= 1) {
        return 0;
    }
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return 0;
        }
    }
    return 1;
}

int is_arab_digit(char ch) {
    return !(ch < '0' || ch > '9');
}

int is_latin_letter(char ch) {
    return ((ch > 64) && (ch < 91) || ((ch > 96) && (ch < 123)));
}

int SumToX(int n) {
    return ((n * (n + 1)) / 2);
}
