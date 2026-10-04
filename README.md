Title: Municipal Financial Management System

Group members
Student No.   Name	             Responsibility
225003694     Fuli Ela Aimerance     Employee Management
223095796     Chantelle Kauejao      Budget Management
225006715     Malakia Muyenga	     Supplier Management
225086239     Helena kongolo	     Asset Management
226068706     Hileni Thomas 	     Reports
226165752     Musolo Gedeon 	     Functions, integration and validation (main.c, input.c)
225172569     Othello Joseph	     Testing


Project description
MFMS is a menu-driven console program that helps a municipality keep track of its employees, departmental budgets, suppliers and assets, and produce basic reports. It is the foundation version of the system and will be extended in Project B. The program is split into one module per area (a .c file and a .h file each), and main.c only shows the main menu and calls the module menus.


Project structure
MFMS/
main.c
input.c      input.h
employees.c  employees.h
budget.c     budget.h
suppliers.c  suppliers.h
assets.c     assets.h
reports.c    reports.h
README.md


Compilation instructions
You need GCC, In the project folder run:
gcc -std=c99 -Wall -Wextra main.c input.c employees.c budget.c suppliers.c assets.c reports.c -o mfms

How to run the system Run:
mfms.exe
