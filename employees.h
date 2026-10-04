#ifndef EMPLOYEES_H
#define EMPLOYEES_H

struct Employee
{
    int id;
    char name[50];
    char department[50];
    float basicSalary;
    float housingAllowance;
    float transportAllowance;
};

extern struct Employee employees[100];
extern int employeeCount;
void employeeMenu(void);
void addEmployee(struct Employee employees[], int *employeeCount);
void displayEmployees(struct Employee employees[], int employeeCount);
void searchEmployee(struct Employee employees[], int employeeCount);
void calculateSalary(struct Employee employees[], int employeeCount);

#endif
