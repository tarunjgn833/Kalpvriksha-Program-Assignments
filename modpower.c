#include <stdio.h>

//used recursive eponent calculation algorithm
long long modpower(long long base, long long  exponent, long long modulus) {
    if (exponent == 0) 
        return 1%modulus; 
        
    long long result = modpower(base, exponent/2, modulus);  
    result = (result*result) % modulus;

    if (exponent % 2 == 1) 
        result = (result * base) % modulus;
    return result;
}

int main() {
    long long base, exponent, modulus;
    
    printf("Base : ");
    scanf("%lld", &base);
    
    printf("Exponent : ");
    scanf("%lld", &exponent);
    
    printf("Modulus : ");
    scanf("%lld", &modulus);
    
    if (modulus <= 1 || base <= 0 || exponent < 0) {
        printf("Invalid input: Modulus must be > 1, Base > 0, and Exponent >= 0\n");
        return 1;
    }
    
    printf("Result: %lld\n", modpower(base, exponent, modulus));
    return 0;
}
