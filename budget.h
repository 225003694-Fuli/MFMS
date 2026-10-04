#ifndef BUDGET_H
#define BUDGET_H

#define MAX_DEPARTMENTS 50

typedef struct {
    int departmentID;
    char departmentName[50];
    float budget;
    float expenditure;
} DepartmentBudget;

extern DepartmentBudget departments[MAX_DEPARTMENTS];
extern int departmentCount;
void budgetMenu(void);
void enterBudget(DepartmentBudget departments[], int *count);
void enterExpenditure(DepartmentBudget departments[], int count);
float calculateRemainingBudget(DepartmentBudget department);
int isWithinBudget(DepartmentBudget department);
void displayBudgetInformation(DepartmentBudget departments[], int count);
void identifyExceededBudgets(DepartmentBudget departments[], int count);

#endif
