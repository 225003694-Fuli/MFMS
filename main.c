#include <stdio.h>
void employeeMenu();
int main()
{

    int choice;

    do
 {
    printf("\nMUNICIPAL FINANCIAL MANAGEMENT SYSTEM\n");
    printf("1. Employee Management\n");
    printf("2. Budget Management\n");
    printf("3. Supplier Management\n");
    printf("4. Asset Management\n");
    printf("5. Reports\n");
    printf("6. Exit\n");

    printf("Enter your choice:");
    scanf("%d", &choice);
    if (choice == 1)
    {
       employeeMenu();
    }
    else if (choice == 2)
    {
        printf("Budget Management selected.\n");
    }
    else if (choice == 3)
    {
        printf("Supplier Management selected.\n");
    }
    else if (choice == 4)
    {
        printf("Asset Management selected.\n");
    }
    else if (choice == 5)
    {
        printf("Reports selected.\n");
    }
    else if (choice == 6)
    {
        printf("Exiting the system.\n");
    }
    else 
    {
        printf("Invalid choice. Please enter a number from 1 to 6.\n");
    }
    } while (choice != 6);
    return 0;
}