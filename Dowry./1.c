#include <stdio.h>

int main() {
    float monthly_salary, age, net_worth;
    float min_dowry, max_dowry;
    int choice;

    printf("Enter your monthly salary: ");
    scanf("%f", &monthly_salary);

    printf("Enter your age: ");
    scanf("%f", &age);

    printf("Enter your net worth: ");
    scanf("%f", &net_worth);

    // Simple calculation (you can customize this)
    min_dowry = (monthly_salary * 12) + (age * 1000) + (net_worth * 0.1);
    max_dowry = (monthly_salary * 24) + (age * 2000) + (net_worth * 0.2);

    printf("Choose an option:\n1. Calculate Minimum Dowry\n2. Calculate Maximum Dowry\n3. Exit\n");
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            printf("Minimum Dowry: %.2f\n", min_dowry);
            break;
        case 2:
            printf("Maximum Dowry: %.2f\n", max_dowry);
            break;
        default:
            printf("Exiting.\n");
            break;
    }

    return 0;
}
