#include <stdio.h>

int fibonacci(int n){
    printf("Calling fibonacci(%d)\n", n);

    if(n == 0){
        printf("Returning 0 (base case for %d)\n", n);
        return 0;
    }
    if(n == 1){
        printf("Returning 1 (base case for %d)\n", n);
        return 1;
    }

    int result = fibonacci(n - 1) + fibonacci(n - 2);
    printf("Returning %d for fibonacci(%d)\n", result, n);
    return result;
}

int main(void){
    int num;

    printf("Enter n: ");
    scanf("%d", &num);

    int result = fibonacci(num);
    printf("Fibonacci(%d) = %d\n", num, result);

    return 0;
}