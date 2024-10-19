#pragma once

//#define _CRT_SECURE_NO_WARNINGS

typedef enum Errors {
    NO_ERRORS,
    INCORRECT_NUMBER_OF_ARGUMENTS,
    INCORRECT_ARGUMENT,
    OVER_FLOW,
    UNKNOWN_COMMAND,
    PARCING_ERROR,
    INCORRECT_OPTION,
    OPENING_FILE_ERROR,
    INCORRECT_FILE_NAME,
    MEMORY_ALLOCATION_ERROR
} Errors;

unsigned long long factorial(int n);

unsigned long long double_factorial(unsigned long long n);

int overflow_check(const char* arg);

int isPrime(int number);

int is_arab_digit(char ch);

int is_latin_letter(char ch);

int SumToX(int n);
