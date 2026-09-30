/*
 * main.c
 * Municipal Financial Management System (MFMS) - Project A
 * PAP521S Programming in Practice
 *
 * main.c is the hub of the program. It shows the main menu, reads a valid
 * choice and calls one menu function per module. It does not hold any
 * module data (employees, budgets, etc.) - each module owns its own data.
 */

#include <stdio.h>

#include "input.h"      /* readInt(), readFloat(), readString() */
#include "employees.h"  /* employeeMenu() */
#include "budget.h"     /* budgetMenu()   */
#include "suppliers.h"  /* supplierMenu() */
#include "assets.h"     /* assetMenu()    */
#include "reports.h"    /* reportsMenu()  */

#define MENU_MIN 1
#define MENU_EXIT 6

/* Prints the main menu. */
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

/* Sends the user to the module they chose. */
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
            /* Not reachable: readInt() only returns 1 to 6. */
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
        /* readInt() rejects letters and numbers outside 1-6 and asks again. */
        choice = readInt("Enter your choice: ", MENU_MIN, MENU_EXIT);
        handleChoice(choice);
    } while (choice != MENU_EXIT);

    return 0;
}
