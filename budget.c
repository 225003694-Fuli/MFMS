#include <stdio.h>
#include "budget.h"
#include "input.h"

DepartmentBudget departments[MAX_DEPARTMENTS];
int departmentCount = 0;

void enterBudget(DepartmentBudget departments[], int *count)
{
    if (*count >= MAX_DEPARTMENTS)
    {

    printf("Maximum number of departments reached.\n");
    return;
}

printf("\n---Enter Department Budget---\n");
printf("Enter Department ID: ");
scanf("%d", &departments[*count].departmentID);

printf("Enter Department Name: ");
scanf(" %49[^\n]", departments[*count].departmentName);

printf("Enter Budget Amount: N$");
scanf("%f", &departments[*count].budget);

departments[*count].expenditure = 0.0;

(*count)++;

printf("Budget entered successfully!\n");
}
void enterExpenditure(DepartmentBudget departments[], int count)
{
    int departmentID;
    int found = 0;

    printf("\n---Enter Expenditure---\n");

    printf("Enter Department ID: ");
    scanf("%d", &departmentID);

    for(int i = 0; i < count; i++)
    {
        if (departments[i].departmentID == departmentID)
        {
            printf("Enter expenditure for %s: N$",
            departments[i].departmentName);

            scanf("%f", &departments[i].expenditure);
            found = 1;

            printf("Expenditure entered successfully!\n");
            break;
        }
    }
    if (!found)
    {
        printf("Department not found. \n");
    }
}

float calculateRemainingBudget(DepartmentBudget department)
{
    return department.budget - department.expenditure;
}
int isWithinBudget(DepartmentBudget department)
{
    return department.expenditure <= department.budget;
}

void displayBudgetInformation(DepartmentBudget departments[], int count)
{
    printf("\n-----------BUDGET INFORMATION--------------\n");

    if(count == 0)
    {
        printf("No departmental budgets entered.\n");
        return;
    }
    for (int i = 0; i< count; i++)
    {
        float remaining = calculateRemainingBudget(departments[i]);

        printf("\nDepartment ID: %d\n",
        departments[i].departmentID);

        printf("Department: %s\n", 
        departments[i].departmentName);

        printf("Budget: N$%.2f\n",
        departments[i].budget);

        printf("Expenditure: N$%.2f\n",
        departments[i].expenditure);

        printf("Remaining Budget: N$%.2f\n",
        remaining);

        if(isWithinBudget(departments[i]))
        {
            printf("Status: Within Budget\n");
        }
        else
        {
            printf("Status: OVER BUDGET\n");
        }
    }
}

void identifyExceededBudgets(DepartmentBudget departments[], int count)
{
    int exceeded = 0;

    printf("\n----------DEPARTMENTS OVER BUDGET---------\n");

    for(int i = 0 ; i < count; i++)
    {
        if(!isWithinBudget(departments[i]))
        {
            float exceededAmount =
                departments[i].expenditure - departments[i].budget;
            
            printf("\nDepartment: %s\n",
            departments[i].departmentName);
        
            printf("Budget: N$%.2f\n",
            departments[i].budget);
        
            printf("Expenditure: N$%.2f\n",
            departments[i].expenditure);
        
            printf("Amount Exceeded: N$%.2f\n",
            exceededAmount);
        exceeded = 1;
        }
    }
    if (!exceeded)
    {
        printf("No departments have exceeded their budgets. \n");
    }
}
