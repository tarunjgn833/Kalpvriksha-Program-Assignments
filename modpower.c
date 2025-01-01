#include <stdio.h>

//used recursive eponent calculation algorithm
long long modpower(long long B, long long  N, long long M) {
    if (N == 0) 
        return 1%M; 
    long long result = modpower(B,N/2,M);  
    result = (result*result)%M;

    if (N%2 == 1) 
        result = (result*B)%M;
    return result;
}

int main() {
    long long B, N, M;
    
    printf("Base (B): ");
    scanf("%lld", &B);
    
    printf("Exponent (N): ");
    scanf("%lld", &N);
    
    printf("Modulus (M): ");
    scanf("%lld", &M);
    
    if (M <= 1 || B <= 0 || N < 0) {
        printf("Invalid input: M must be > 1, B > 0, and N >= 0\n");
        return 1;
    }
    
    printf("Result: %lld\n", modpower(B, N, M));
    return 0;
}
