#include <stdio.h>
#include <string.h>
#include "reports.h"


double grossSalary(const struct Employee *e){
    return e->basicSalary + e->housingAllowance + e->transportAllowance;
}

static void printLine(char ch, int n){
    int i;
    for (i = 0; i < n; i++)
    putchar(ch);
    putchar('\n');
}

static void printTitle(const char *title){
    printLine('=', 60);
    printf("%s\n", title);
    printLine('=', 60);
}

static int readChoice(void){
    char buffer[32];
    int choice;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
     return -1;
    if (sscanf(buffer, "%d", &choice) != 1)
     return -1;
    return choice;
}


void employeeReport(const struct Employee employees[], int count){
    int i;
    double total = 0.0, average, highest, lowest, gross;
    int highIdx = 0, lowIdx = 0;

    printTitle("EMPLOYEE REPORT");

    if (count <= 0) {
        printf("No employees registered.\n\n");
        return;
    }

    highest = lowest = grossSalary(&employees[0]);

    for (i = 0; i < count; i++) {
        gross = grossSalary(&employees[i]);
        total += gross;

        if (gross > highest) {
            highest = gross;
            highIdx = i;
        }
        if (gross < lowest) {
            lowest = gross;
            lowIdx = i;
        }
    }
    average = total / count;

    printf("Total Employees : %d\n", count);
    printf("Average Salary  : N$%.2f\n", average);
    printf("Highest Salary  : N$%.2f (%s)\n", highest, employees[highIdx].name);
    printf("Lowest Salary   : N$%.2f (%s)\n", lowest, employees[lowIdx].name);
    printf("Total Payroll   : N$%.2f\n\n", total);

    printf("%-6s %-20s %-15s %12s\n", "ID", "Name", "Department", "Gross (N$)");
    printLine('-', 60);
    for (i = 0; i < count; i++) {
        printf("%-6d %-20s %-15s %12.2f\n",
            employees[i].id, employees[i].name,
            employees[i].department, grossSalary(&employees[i]));
    }
    printf("\n");
}


void budgetReport(const DepartmentBudget budgets[], int count){
    int i, exceeded = 0;
    double totalAllocated = 0.0, totalSpent = 0.0;

    printTitle("BUDGET REPORT");

    if (count <= 0) {
        printf("No budgets registered.\n\n");
        return;
    }

    for (i = 0; i < count; i++) {
        totalAllocated += budgets[i].budget;
        totalSpent += budgets[i].expenditure;
    }

    printf("Total Allocated Budget : N$%.2f\n", totalAllocated);
    printf("Total Expenditure      : N$%.2f\n", totalSpent);
    printf("Remaining Budget       : N$%.2f\n\n", totalAllocated - totalSpent);

    printf("%-6s %-18s %12s %12s %12s  %s\n",
           "ID", "Department", "Allocated", "Spent", "Remaining", "Status");
    printLine('-', 76);
    for (i = 0; i < count; i++) {
        double remaining = budgets[i].budget - budgets[i].expenditure;
        printf("%-6d %-18.18s %12.2f %12.2f %12.2f  %s\n",
            budgets[i].departmentID, budgets[i].departmentName,
            budgets[i].budget, budgets[i].expenditure, remaining,
            (remaining >= 0) ? "WITHIN BUDGET" : "OVER BUDGET");
    }

    printf("\nDepartments exceeding budget:\n");
    for (i = 0; i < count; i++) {
        if (budgets[i].expenditure > budgets[i].budget) {
            printf("  - %s (over by N$%.2f)\n", budgets[i].departmentName,
                budgets[i].expenditure - budgets[i].budget);
            exceeded++;
        }
    }
    if (exceeded == 0)
        printf("  None. All departments are within budget.\n");
    printf("\n");
}


void supplierReport(const Supplier list[], int count){
    int i;

    printTitle("SUPPLIER REPORT");

    if (count <= 0) {
        printf("No suppliers registered.\n\n");
        return;
    }

    printf("Total Suppliers: %d\n\n", count);
    printf("%-8s %-20s %-26s %-16s %-12s\n",
           "ID", "Name", "Email", "Telephone", "Town");
    printLine('-', 84);
    for (i = 0; i < count; i++) {
        printf("%-8d %-20.20s %-26.26s %-16.16s %-12.12s\n",
            list[i].supplierID, list[i].name, list[i].email,
            list[i].telephone, list[i].town);
    }
    printf("\n");
}


void assetReport(const Asset list[], int count){
    int i;

    printTitle("ASSET REPORT");

    if (count <= 0) {
        printf("No assets registered.\n\n");
        return;
    }

    printf("%-8s %-18s %-12s %14s %-14s %-10s\n",
           "ID", "Name", "Type", "Value (N$)", "Department", "Condition");
    printLine('-', 80);
    for (i = 0; i < count; i++) {
        printf("%-8d %-18.18s %-12.12s %14.2f %-14.14s %-10s\n",
            list[i].assetID, list[i].name, list[i].type,
            list[i].purchaseValue, list[i].department,
            list[i].condition);
    }
    printf("\nTotal Assets: %d\n", count);
    printf("Total Purchase Value: N$%.2f\n\n",
        calculateTotalAssetValue(list, count));
}



void displayReports(const struct Employee employees[], int empCount,
    const DepartmentBudget budgets[], int budCount,
    const Supplier supplierList[], int supplierTotal,
    const Asset assetList[], int assetTotal){
    int choice;

    do {
        printf("\n========================================\n");
        printf("               REPORTS\n");
        printf("========================================\n");
        printf("1. Employee Report\n");
        printf("2. Budget Report\n");
        printf("3. Supplier Report\n");
        printf("4. Asset Report\n");
        printf("5. Back to Main Menu\n");
        printf("Enter your choice: ");

        choice = readChoice();

        switch (choice) {
        case 1: employeeReport(employees, empCount); break;
        case 2: budgetReport(budgets, budCount);      break;
        case 3: supplierReport(supplierList, supplierTotal);  break;
        case 4: assetReport(assetList, assetTotal);      break;
        case 5: break;
        default:
            printf("Invalid choice. Please enter a number from 1 to 5.\n");
        }
    } while (choice != 5);
}
