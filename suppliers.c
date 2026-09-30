
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "input.h"
#include "suppliers.h"

#define MAX_INPUT        100   
#define MAX_SUPPLIER_ID  999999

Supplier suppliers[MAX_SUPPLIERS];
int supplierCount = 0;

static void toLowerCopy(char *dest, const char *src, int size)
{
    int i;

    for (i = 0; i < size - 1 && src[i] != '\0'; i++)
    {
        dest[i] = (char)tolower((unsigned char)src[i]);
    }
    dest[i] = '\0';
}

static int sameText(const char *a, const char *b)
{
    char lowerA[MAX_INPUT];
    char lowerB[MAX_INPUT];

    toLowerCopy(lowerA, a, MAX_INPUT);
    toLowerCopy(lowerB, b, MAX_INPUT);

    return strcmp(lowerA, lowerB) == 0;
}

static void readLimited(const char *prompt, char *dest, int size)
{
    char temp[MAX_INPUT];

    while (1)
    {
        readString(prompt, temp, MAX_INPUT);

        if ((int)strlen(temp) < size)
        {
            strcpy(dest, temp);
            return;
        }
        printf("Too long. Maximum %d characters.\n", size - 1);
    }
}

static void readValidEmail(char *dest, int size)
{
    while (1)
    {
        readLimited("Enter Email: ", dest, size);

        if (isValidEmail(dest))
        {
            return;
        }
        printf("Invalid email. Example: sales@company.com\n");
    }
}

static void readValidPhone(char *dest, int size)
{
    while (1)
    {
        readLimited("Enter Telephone Number: ", dest, size);

        if (isValidPhone(dest))
        {
            return;
        }
        printf("Invalid telephone number. Use 7 to 15 digits, "
               "e.g. 061 207 2052 or +264 61 207 2052.\n");
    }
}

static void printSupplierHeader(void)
{
    printf("\n%-8s %-25s %-28s %-18s %-15s\n",
           "ID", "Name", "Email", "Telephone", "Town");
    printf("-------------------------------------------------------"
           "-------------------------------------\n");
}

static void printSupplierRow(const Supplier *s)
{
    printf("%-8d %-25s %-28s %-18s %-15s\n",
           s->supplierID, s->name, s->email, s->telephone, s->town);
}

int isValidEmail(const char *email)
{
    const char *at;
    const char *dot;

    if (strlen(email) < 5)
    {
        return 0;
    }
    if (strchr(email, ' ') != NULL)
    {
        return 0;
    }

    at = strchr(email, '@');
    if (at == NULL || at == email)
    {
        return 0;
    }
    if (strchr(at + 1, '@') != NULL)
    {
        return 0;
    }

    dot = strrchr(at, '.');
    if (dot == NULL || dot == at + 1 || *(dot + 1) == '\0')
    {
        return 0;
    }

    return 1;
}

int isValidPhone(const char *phone)
{
    int i;
    int digits = 0;
    int length = (int)strlen(phone);

    for (i = 0; i < length; i++)
    {
        if (isdigit((unsigned char)phone[i]))
        {
            digits++;
        }
        else if (phone[i] == ' ' || phone[i] == '-')
        {
            continue;
        }
        else if (phone[i] == '+' && i == 0)
        {
            continue;
        }
        else
        {
            return 0;
        }
    }

    return digits >= 7 && digits <= 15;
}

int findSupplierIndexByID(const Supplier list[], int count, int id)
{
    int i;

    for (i = 0; i < count; i++)
    {
        if (list[i].supplierID == id)
        {
            return i;
        }
    }
    return -1;
}


void addSupplier(Supplier list[], int *count)
{
    int id;

    printf("\nADD SUPPLIER\n");

    if (*count >= MAX_SUPPLIERS)
    {
        printf("Supplier list is full (maximum %d suppliers).\n",
               MAX_SUPPLIERS);
        return;
    }

    while (1)
    {
        id = readInt("Enter Supplier ID: ", 1, MAX_SUPPLIER_ID);

        if (findSupplierIndexByID(list, *count, id) == -1)
        {
            break;
        }
        printf("Supplier ID %d is already in use. Enter a different ID.\n",
               id);
    }

    list[*count].supplierID = id;
    readLimited("Enter Supplier Name: ", list[*count].name,
                SUPPLIER_NAME_LEN);
    readValidEmail(list[*count].email, SUPPLIER_EMAIL_LEN);
    readValidPhone(list[*count].telephone, SUPPLIER_PHONE_LEN);
    readLimited("Enter Town/Location: ", list[*count].town,
                SUPPLIER_TOWN_LEN);

    (*count)++;

    printf("Supplier added successfully.\n");
}

void displaySuppliers(const Supplier list[], int count)
{
    int i;

    printf("\nSUPPLIER LIST\n");

    if (count == 0)
    {
        printf("No suppliers registered yet.\n");
        return;
    }

    printSupplierHeader();
    for (i = 0; i < count; i++)
    {
        printSupplierRow(&list[i]);
    }
    printf("\nTotal suppliers: %d\n", count);
}

void searchSupplierByID(const Supplier list[], int count)
{
    int id;
    int index;

    printf("\nSEARCH SUPPLIER BY ID\n");

    if (count == 0)
    {
        printf("No suppliers registered yet.\n");
        return;
    }

    id = readInt("Enter Supplier ID: ", 1, MAX_SUPPLIER_ID);
    index = findSupplierIndexByID(list, count, id);

    if (index == -1)
    {
        printf("Supplier not found.\n");
        return;
    }

    printf("\nSupplier found!\n");
    printSupplierHeader();
    printSupplierRow(&list[index]);
}

void searchSupplierByName(const Supplier list[], int count)
{
    char term[SUPPLIER_NAME_LEN];
    char termLower[SUPPLIER_NAME_LEN];
    char nameLower[SUPPLIER_NAME_LEN];
    int i;
    int found = 0;

    printf("\nSEARCH SUPPLIER BY NAME\n");

    if (count == 0)
    {
        printf("No suppliers registered yet.\n");
        return;
    }

    readLimited("Enter name (or part of it): ", term, SUPPLIER_NAME_LEN);
    toLowerCopy(termLower, term, SUPPLIER_NAME_LEN);

    for (i = 0; i < count; i++)
    {
        toLowerCopy(nameLower, list[i].name, SUPPLIER_NAME_LEN);

        if (strstr(nameLower, termLower) != NULL)
        {
            if (found == 0)
            {
                printSupplierHeader();
            }
            printSupplierRow(&list[i]);
            found++;
        }
    }

    if (found == 0)
    {
        printf("No supplier found matching \"%s\".\n", term);
    }
    else
    {
        printf("\n%d supplier(s) found.\n", found);
    }
}

/* Lists every supplier in the town the user types. */
void searchSupplierByTown(const Supplier list[], int count)
{
    char town[SUPPLIER_TOWN_LEN];
    int i;
    int found = 0;

    printf("\nSEARCH SUPPLIER BY TOWN/LOCATION\n");

    if (count == 0)
    {
        printf("No suppliers registered yet.\n");
        return;
    }

    readLimited("Enter Town/Location: ", town, SUPPLIER_TOWN_LEN);

    for (i = 0; i < count; i++)
    {
        if (sameText(list[i].town, town))
        {
            if (found == 0)
            {
                printSupplierHeader();
            }
            printSupplierRow(&list[i]);
            found++;
        }
    }

    if (found == 0)
    {
        printf("No suppliers found in \"%s\".\n", town);
    }
    else
    {
        printf("\n%d supplier(s) found.\n", found);
    }
}

void compareSuppliers(const Supplier list[], int count)
{
    int firstIndex;
    int secondIndex;

    printf("\nCOMPARE TWO SUPPLIERS\n");

    if (count < 2)
    {
        printf("At least two suppliers must be registered to compare.\n");
        return;
    }

    firstIndex = findSupplierIndexByID(
        list, count, readInt("Enter first Supplier ID: ", 1, MAX_SUPPLIER_ID));
    if (firstIndex == -1)
    {
        printf("First supplier not found.\n");
        return;
    }

    secondIndex = findSupplierIndexByID(
        list, count, readInt("Enter second Supplier ID: ", 1, MAX_SUPPLIER_ID));
    if (secondIndex == -1)
    {
        printf("Second supplier not found.\n");
        return;
    }

    if (firstIndex == secondIndex)
    {
        printf("You entered the same supplier twice.\n");
        return;
    }

    printSupplierHeader();
    printSupplierRow(&list[firstIndex]);
    printSupplierRow(&list[secondIndex]);

    if (sameText(list[firstIndex].town, list[secondIndex].town))
    {
        printf("\nBoth suppliers are located in %s.\n",
               list[firstIndex].town);
    }
    else
    {
        printf("\nThe suppliers are in different towns (%s and %s).\n",
               list[firstIndex].town, list[secondIndex].town);
    }
}

void supplierMenu(void)
{
    int choice;

    do
    {
        printf("\n===== SUPPLIER MANAGEMENT =====\n");
        printf("1. Add Supplier\n");
        printf("2. Display All Suppliers\n");
        printf("3. Search Supplier by ID\n");
        printf("4. Search Supplier by Name\n");
        printf("5. Search Suppliers by Town/Location\n");
        printf("6. Compare Two Suppliers\n");
        printf("7. Return to Main Menu\n");

        choice = readInt("Enter your choice: ", 1, 7);

        switch (choice)
        {
            case 1:
                addSupplier(suppliers, &supplierCount);
                break;
            case 2:
                displaySuppliers(suppliers, supplierCount);
                break;
            case 3:
                searchSupplierByID(suppliers, supplierCount);
                break;
            case 4:
                searchSupplierByName(suppliers, supplierCount);
                break;
            case 5:
                searchSupplierByTown(suppliers, supplierCount);
                break;
            case 6:
                compareSuppliers(suppliers, supplierCount);
                break;
            case 7:
                printf("Returning to Main Menu.\n");
                break;
        }
    } while (choice != 7);
}
