#include <stdio.h>
#include <math.h>

int main() {
    double factorial = 1;
    int n = 25;
    int sym_factor = 2880;  

   
    for (int i = 1; i <= n; ++i) {
        factorial *= i;
    }

 
    double log2_factorial = log2(factorial);

  
    double unique_keys = factorial / sym_factor;
    double log2_unique_keys = log2(unique_keys);

 
    printf("Total number of possible keys (approx.) is 2^%.0f\n", ceil(log2_factorial));
    printf("Number of effectively unique keys (approx.) is 2^%.0f\n", ceil(log2_unique_keys));

    return 0;
}
