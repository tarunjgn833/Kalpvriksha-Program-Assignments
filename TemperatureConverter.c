#include <stdio.h>

void celsiusToFahrenheit(float celsius)
{
    float fahrenheit = (celsius * 9 / 5) + 32;
    printf("%.2f Celsius = %.2f Fahrenheit\n", celsius, fahrenheit);
}

void celsiusToKelvin(float celsius)
{
    float kelvin = celsius + 273.15;
    printf("%.2f Celsius = %.2f Kelvin\n", celsius, kelvin);
}

void fahrenheitToCelsius(float fahrenheit)
{
    float celsius = (fahrenheit - 32) * 5 / 9;
    printf("%.2f Fahrenheit = %.2f Celsius\n", fahrenheit, celsius);
}

void fahrenheitToKelvin(float fahrenheit)
{
    float kelvin = (fahrenheit - 32) * 5 / 9 + 273.15;
    printf("%.2f Fahrenheit = %.2f Kelvin\n", fahrenheit, kelvin);
}

void kelvinToCelsius(float kelvin)
{
    float celsius = kelvin - 273.15;
    printf("%.2f Kelvin = %.2f Celsius\n", kelvin, celsius);
}

void kelvinToFahrenheit(float kelvin)
{
    float fahrenheit = (kelvin - 273.15) * 9 / 5 + 32;
    printf("%.2f Kelvin = %.2f Fahrenheit\n", kelvin, fahrenheit);
}

int main()
{
    int choice;
    float temp;

    do
    {
        printf("1. Celsius to Fahrenheit\n");
        printf("2. Celsius to Kelvin\n");
        printf("3. Fahrenheit to Celsius\n");
        printf("4. Fahrenheit to Kelvin\n");
        printf("5. Kelvin to Celsius\n");
        printf("6. Kelvin to Fahrenheit\n");
        printf("7. Exit\n");
        printf("Enter your choice (1-7): ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 6)
        {
            printf("Enter temperature: ");
            scanf("%f", &temp);
        }

        switch (choice)
        {
        case 1:
            celsiusToFahrenheit(temp);
            break;
        case 2:
            celsiusToKelvin(temp);
            break;
        case 3:
            fahrenheitToCelsius(temp);
            break;
        case 4:
            fahrenheitToKelvin(temp);
            break;
        case 5:
            kelvinToCelsius(temp);
            break;
        case 6:
            kelvinToFahrenheit(temp);
            break;
        case 7:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice, please try again.\n");
        }
        printf("\n");
    } while (choice != 7);

    return 0;
}
