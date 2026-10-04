#ifndef REPORTS_H
#define REPORTS_H
 

#include "employees.h"   
#include "budget.h"  
#include "suppliers.h"
#include "assets.h"      

double grossSalary(const struct Employee *e);

void employeeReport(const struct Employee employees[], int count);
void budgetReport(const DepartmentBudget budgets[], int count);
void supplierReport(const Supplier list[], int count);
void assetReport(const Asset list[], int count);

void displayReports(const struct Employee employees[], int empCount,
    const DepartmentBudget budgets[], int budCount,
    const Supplier supplierList[], int supplierTotal,
    const Asset assetList[], int assetTotal);
void reportsMenu(void);
#endif
