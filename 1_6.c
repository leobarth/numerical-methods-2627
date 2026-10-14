// deliberately not using #include <math.h> for practice purposes

#include <stdio.h>
#include <stdlib.h>

// power function implementation for exponents n and bases x
double power(double x, int n) {
    // catches trivial inputs in the beginning, and multiplies x with itself n times to get the result (n < 0 path ensures correct reciprocal handling)
    
    // absolute value of n for loop end condition
    if (n == 0) {
        // especially returns 1 for 0⁰ to correctly evaluate exp(0, n)
        return 1;
    }
    if (x == 0) {
        return 0;
    }
    int abs_n = n;
    if (n < 0) {
        abs_n = -n;
    }
    double output = 1.0;
    for (int i = 1; i <= abs_n; i++) {
        output *= x;
    }
    if (n < 0) {
        return 1 / output;
    }
    return output;
}

// factorial function implementation with integer input k
// double to prevent integer overflow
double factorial(int k) {
    // catches trivial inputs in the beginning and iterates k times to get the factorial

    if (k == 0) {
        return 1;
    }
    if (k < 0) {
        fprintf(stderr, "factorial input may not be negative, got: %d", k);
        exit(1);
    }
    double output = 1.0;
    for (int i = 1; i <= k; i++){
        output *= i;
    }
    return output;
}

// required implementation of the exponential function
double my_exp(double x, int n) {
    // catches n < 0, correctly evaluates for n = 0 (see
    // power function implementation) and loops over outer
    // sum to get the taylor-expression
    if (n < 0) {
        fprintf(stderr, "Taylor-series cutoff may not be negative, got: %d", n);
    }
    double output = 0;
    for (int k = 0; k <= n; k++) {
        output += (power(x, k) / factorial(k));
    }
    return output;
}

int main() {
    FILE *f = fopen("results_1_6.txt", "w");
    if (f == NULL) {
        perror("Error when creating file.");
        return 1;
    }
    
    // M1
    fprintf(f, "M1 results:\n");
    for (int n = 3; n <= 30; n += 3) {
        fprintf(f, "n = %d: %.10f\n", n, my_exp(-5.5, n));
    }

    //M2
    fprintf(f, "\nM2 results:\n");
    for (int n = 3; n <= 30; n += 3) {
        fprintf(f, "n = %d: %.10f\n", n, 1 / my_exp(5.5, n));
    }

    //M3
    fprintf(f, "\nM3 results:\n");
    for (int n = 3; n <= 30; n += 3) {
        fprintf(f, "n = %d: %.10f\n", n, power(my_exp(0.5, n), -11));
    }
    fclose(f);
}