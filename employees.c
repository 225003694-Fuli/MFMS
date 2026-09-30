#include <stdio.h>
#include <string.h>
#include "employees.h"

 struct Employee employees[100];
 int employeeCount = 0;

void addEmployee(struct Employee employees[], int *employeeCount)
{
    if (*employeeCount >= 100)
{
    printf("Employee list is full. Cannot add more employees.\n");
    return;
}
     printf("\nADD EMPLOYEE\n");

    do
{
    printf("Enter Employee ID: ");
    scanf("%d", &employees[*employeeCount].id);

    if (employees[*employeeCount].id <= 0)
    {
        printf("Invalid Employee ID. Please enter a positive number.\n");
    }

} 
  while (employees[*employeeCount].id <= 0);
    printf("Enter Name:");
    scanf(" %[^\n]", employees[*employeeCount].name);
    printf("Enter Department:");
    scanf(" %[^\n]", employees[*employeeCount].department);
    do
{
    printf("Enter Basic Salary: ");
    scanf("%f", &employees[*employeeCount].basicSalary);

    if (employees[*employeeCount].basicSalary < 0)
    {
        printf("Invalid salary. Salary cannot be negative.\n");
    }

} 
  while (employees[*employeeCount].basicSalary < 0);
   
  do
{
    printf("Enter Housing Allowance: ");
    scanf("%f", &employees[*employeeCount].housingAllowance);

    if (employees[*employeeCount].housingAllowance < 0)
    {
        printf("Invalid allowance. Housing allowance cannot be negative.\n");
    }

}
  while (employees[*employeeCount].housingAllowance < 0);
   
  do
{
    printf("Enter Transport Allowance: ");
    scanf("%f", &employees[*employeeCount].transportAllowance);

    if (employees[*employeeCount].transportAllowance < 0)
    {
        printf("Invalid allowance. Transport allowance cannot be negative.\n");
    }

} 
  while (employees[*employeeCount].transportAllowance < 0);

    (*employeeCount)++;

    printf("Employee added successfully.\n");

}
void employeeMenu()
{
    int choice;

   do
{
    printf("\nEMPLOYEE MANAGEMENT\n");
    printf("1. Add Employee\n");
    printf("2. Display Employees\n");
    printf("3. Search Employee\n");
    printf("4. Calculate Salary\n");
    printf("5. Return to Main Menu\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        addEmployee(employees, &employeeCount);
    }
    else if (choice == 2)
    {
        displayEmployees(employees, employeeCount);
    }
    else if (choice == 3)
    {
        searchEmployee(employees, employeeCount);
    }
    else if (choice == 4)
    {
    calculateSalary(employees, employeeCount);
    }
    else if (choice == 5)
    {
        printf("Returning to Main Menu.\n");
    }
    else
    {
        printf("This option is not implemented yet.\n");
    }

} while (choice != 5);
}
    void displayEmployees(struct Employee employees[], int employeeCount)
{
    int i;

    printf("\nEMPLOYEE LIST\n");

    for (i = 0; i < employeeCount; i++)
    {
        printf("\nEmployee ID: %d\n", employees[i].id);
        printf("Name: %s\n", employees[i].name);
        printf("Department: %s\n", employees[i].department);
        printf("Basic Salary: %.2f\n", employees[i].basicSalary);
        printf("Housing Allowance: %.2f\n", employees[i].housingAllowance);
        printf("Transport Allowance: %.2f\n", employees[i].transportAllowance);
    }
}
void searchEmployee(struct Employee employees[], int employeeCount)
{
    int searchID;
    int found = 0;
    int i;

    printf("\nSEARCH EMPLOYEE\n");
    printf("Enter Employee ID: ");
    scanf("%d", &searchID);

    for (i = 0; i < employeeCount; i++)
    {
        if (employees[i].id == searchID)
        {
            printf("\nEmployee found!\n");
            printf("Employee ID: %d\n", employees[i].id);
            printf("Name: %s\n", employees[i].name);
            printf("Department: %s\n", employees[i].department);
            printf("Basic Salary: %.2f\n", employees[i].basicSalary);
            printf("Housing Allowance: %.2f\n", employees[i].housingAllowance);
            printf("Transport Allowance: %.2f\n", employees[i].transportAllowance);

            found = 1;
            break;
        }
    }

    if (found == 0)
    {
        printf("Employee not found.\n");
    }
}
void calculateSalary(struct Employee employees[], int employeeCount)
{
    int searchID;
    int i;
    int found = 0;
    float totalSalary;

    printf("\nCALCULATE SALARY\n");
    printf("Enter Employee ID: ");
    scanf("%d", &searchID);

    for (i = 0; i < employeeCount; i++)
    {
        if (employees[i].id == searchID)
        {
            totalSalary = employees[i].basicSalary
                        + employees[i].housingAllowance
                        + employees[i].transportAllowance;

            printf("\nEmployee: %s\n", employees[i].name);
            printf("Basic Salary: %.2f\n", employees[i].basicSalary);
            printf("Housing Allowance: %.2f\n", employees[i].housingAllowance);
            printf("Transport Allowance: %.2f\n", employees[i].transportAllowance);
            printf("Total Salary: %.2f\n", totalSalary);

            found = 1;
            break;
        }
    }

    if (found == 0)
    {
        printf("Employee not found.\n");
    }
}