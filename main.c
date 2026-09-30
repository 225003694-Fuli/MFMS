
#include <stdio.h>

#include "input.h"     
#include "employees.h" 
#include "budget.h"    
#include "suppliers.h" 
#include "assets.h"     
#include "reports.h"    

#define MENU_MIN 1
#define MENU_EXIT 6

void displayMenu(void)
{
    printf("\n========================================\n");
    printf("   MUNICIPAL FINANCIAL MANAGEMENT SYSTEM\n");
    printf("========================================\n");
    printf("1. Employee Management\n");
    printf("2. Budget Management\n");
    printf("3. Supplier Management\n");
    printf("4. Asset Management\n");
    printf("5. Reports\n");
    printf("6. Exit\n");
}

void handleChoice(int choice)
{
    switch (choice)
    {
        case 1:
            employeeMenu();
            break;
        case 2:
            budgetMenu();
            break;
        case 3:
            supplierMenu();
            break;
        case 4:
            assetMenu();
            break;
        case 5:
            reportsMenu();
            break;
        case 6:
            printf("\nExiting the system. Goodbye.\n");
            break;
        default:
            printf("Invalid choice. Please enter a number from 1 to 6.\n");
            break;
    }
}

int main(void)
{
    int choice;

    do
    {
        displayMenu();
        choice = readInt("Enter your choice: ", MENU_MIN, MENU_EXIT);
        handleChoice(choice);
    } while (choice != MENU_EXIT);

    return 0;
}
