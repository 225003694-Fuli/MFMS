#ifndef MENU_H
#define MENU_H

/*
 * menu.h
 * ------
 * Integration & menu layer for the Municipal Financial Management System.
 * Owner: Member 6
 */

/* Entry point - called by main() */
void runMenu(void);

/* Top-level menu display */
void displayMenu(void);

/* Route a validated choice to the correct module */
void handleChoice(int choice);

/* Shims for modules without their own menu yet */
void budgetMenuShim(void);
void reportsMenuShim(void);

/*
 * recursiveMenuChoice
 * -------------------
 * Recursive input reader for the main menu.
 * Week 8 recursion requirement.
 */
int recursiveMenuChoice(int attempt);

#endif
