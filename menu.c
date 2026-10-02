#include <stdio.h>

#include "menu.h"
#include "input.h"
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"
#include "reports.h"

#define MENU_MIN  1
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

int recursiveMenuChoice(int attempt)
{
    int choice = readInt("Enter your choice: ", MENU_MIN, MENU_EXIT);

    if (choice < MENU_MIN || choice > MENU_EXIT)
    {
        printf("Invalid choice. Attempt %d.\n", attempt);
        return recursiveMenuChoice(attempt + 1);
    }
    return choice;
}

void budgetMenuShim(void)
{
    DepartmentBudget budgets[MAX_DEPARTMENTS];
    int budCount = 0;
    int choice;

    do
    {
        printf("\n===== BUDGET MANAGEMENT =====\n");
        printf("1. Enter Department Budget\n");
        printf("2. Enter Expenditure\n");
        printf("3. Display Budget Information\n");
        printf("4. Show Departments Over Budget\n");
        printf("5. Return to Main Menu\n");

        choice = readInt("Enter your choice: ", 1, 5);

        switch (choice)
        {
            case 1: enterBudget(budgets, &budCount);             break;
            case 2: enterExpenditure(budgets, budCount);         break;
            case 3: displayBudgetInformation(budgets, budCount); break;
            case 4: identifyExceededBudgets(budgets, budCount);  break;
            case 5: printf("Returning to Main Menu.\n");         break;
        }
    } while (choice != 5);
}

void reportsMenuShim(void)
{
    extern struct Employee employees[];
    extern int employeeCount;

    displayReports(employees, employeeCount,
                   NULL, 0,
                   suppliers, supplierCount,
                   assets, assetCount);
}

void handleChoice(int choice)
{
    switch (choice)
    {
        case 1: employeeMenu();      break;
        case 2: budgetMenuShim();    break;
        case 3: supplierMenu();      break;
        case 4: assetMenu();         break;
        case 5: reportsMenuShim();   break;
        case 6: printf("\nExiting the system. Goodbye.\n"); break;
        default:
            printf("Invalid choice. Please enter a number from 1 to 6.\n");
            break;
    }
}

void runMenu(void)
{
    int choice;

    do
    {
        displayMenu();
        choice = recursiveMenuChoice(1);
        handleChoice(choice);
    } while (choice != MENU_EXIT);
}
