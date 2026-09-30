#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "input.h"
#include "assets.h"

#define MAX_INPUT        100
#define MAX_ASSET_ID     999999
#define MAX_ASSET_VALUE  1000000000000.0

Asset assets[MAX_ASSETS];
int assetCount = 0;

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

static void readAssetText(const char *prompt, char *dest, int size)
{
    char temp[MAX_INPUT];

    while (1)
    {
        readString(prompt, temp, MAX_INPUT);

        if (strlen(temp) == 0)
        {
            printf("This field cannot be empty.\n");
        }
        else if ((int)strlen(temp) >= size)
        {
            printf("Too long. Maximum %d characters.\n", size - 1);
        }
        else
        {
            strcpy(dest, temp);
            return;
        }
    }
}

static double readAssetValue(const char *prompt)
{
    char temp[MAX_INPUT];
    char extra;
    double value;

    while (1)
    {
        readString(prompt, temp, MAX_INPUT);

        if (sscanf(temp, "%lf %c", &value, &extra) != 1)
        {
            printf("Invalid number. Example: 12500.50\n");
        }
        else if (!(value >= 0))
        {
            printf("The value cannot be negative.\n");
        }
        else if (value > MAX_ASSET_VALUE)
        {
            printf("The value is too large.\n");
        }
        else
        {
            return value;
        }
    }
}

static void chooseCondition(char *dest)
{
    int choice;

    printf("Condition:\n");
    printf("1. Good\n");
    printf("2. Fair\n");
    printf("3. Poor\n");

    choice = readInt("Enter condition (1-3): ", 1, 3);

    switch (choice)
    {
        case 1:
            strcpy(dest, "Good");
            break;
        case 2:
            strcpy(dest, "Fair");
            break;
        default:
            strcpy(dest, "Poor");
    }
}

static void printAssetHeader(void)
{
    printf("\n%-8s %-22s %-14s %-16s %-15s %-9s\n",
           "ID", "Name", "Type", "Value (N$)", "Department", "Condition");
    printf("-------------------------------------------------------"
           "-----------------------------\n");
}

static void printAssetRow(const Asset *a)
{
    printf("%-8d %-22s %-14s %-16.2f %-15s %-9s\n",
           a->assetID, a->name, a->type, a->purchaseValue,
           a->department, a->condition);
}

int findAssetIndexByID(const Asset list[], int count, int id)
{
    int i;

    for (i = 0; i < count; i++)
    {
        if (list[i].assetID == id)
        {
            return i;
        }
    }
    return -1;
}

double calculateTotalAssetValue(const Asset list[], int count)
{
    int i;
    double total = 0;

    for (i = 0; i < count; i++)
    {
        total = total + list[i].purchaseValue;
    }
    return total;
}

void addAsset(Asset list[], int *count)
{
    int id;

    printf("\nADD ASSET\n");

    if (*count >= MAX_ASSETS)
    {
        printf("Asset register is full (maximum %d assets).\n", MAX_ASSETS);
        return;
    }

    while (1)
    {
        id = readInt("Enter Asset ID: ", 1, MAX_ASSET_ID);

        if (findAssetIndexByID(list, *count, id) == -1)
        {
            break;
        }
        printf("Asset ID %d is already in use. Enter a different ID.\n", id);
    }

    list[*count].assetID = id;
    readAssetText("Enter Asset Name: ", list[*count].name, ASSET_NAME_LEN);
    readAssetText("Enter Asset Type (e.g. Vehicle, Computer): ",
                  list[*count].type, ASSET_TYPE_LEN);
    list[*count].purchaseValue = readAssetValue("Enter Purchase Value (N$): ");
    readAssetText("Enter Department: ", list[*count].department,
                  ASSET_DEPT_LEN);
    chooseCondition(list[*count].condition);

    (*count)++;

    printf("Asset added successfully.\n");
}

void displayAssets(const Asset list[], int count)
{
    int i;

    printf("\nASSET REGISTER\n");

    if (count == 0)
    {
        printf("No assets registered yet.\n");
        return;
    }

    printAssetHeader();
    for (i = 0; i < count; i++)
    {
        printAssetRow(&list[i]);
    }
    printf("\nTotal assets: %d\n", count);
}

void searchAsset(const Asset list[], int count)
{
    int option;
    int id;
    int index;
    int i;
    int match;
    int found = 0;
    char term[MAX_INPUT];
    char termLower[MAX_INPUT];
    char nameLower[MAX_INPUT];

    printf("\nSEARCH ASSETS\n");

    if (count == 0)
    {
        printf("No assets registered yet.\n");
        return;
    }

    printf("1. Search by Asset ID\n");
    printf("2. Search by Name (or part of it)\n");
    printf("3. Search by Type\n");
    printf("4. Search by Department\n");
    option = readInt("Enter your choice: ", 1, 4);

    if (option == 1)
    {
        id = readInt("Enter Asset ID: ", 1, MAX_ASSET_ID);
        index = findAssetIndexByID(list, count, id);

        if (index == -1)
        {
            printf("Asset not found.\n");
            return;
        }

        printf("\nAsset found!\n");
        printAssetHeader();
        printAssetRow(&list[index]);
        return;
    }

    readAssetText("Enter search text: ", term, MAX_INPUT);
    toLowerCopy(termLower, term, MAX_INPUT);

    for (i = 0; i < count; i++)
    {
        match = 0;

        switch (option)
        {
            case 2:
                toLowerCopy(nameLower, list[i].name, MAX_INPUT);
                if (strstr(nameLower, termLower) != NULL)
                {
                    match = 1;
                }
                break;
            case 3:
                if (sameText(list[i].type, term))
                {
                    match = 1;
                }
                break;
            case 4:
                if (sameText(list[i].department, term))
                {
                    match = 1;
                }
                break;
        }

        if (match == 1)
        {
            if (found == 0)
            {
                printAssetHeader();
            }
            printAssetRow(&list[i]);
            found++;
        }
    }

    if (found == 0)
    {
        printf("No assets found matching \"%s\".\n", term);
    }
    else
    {
        printf("\n%d asset(s) found.\n", found);
    }
}

void displayAssetReport(const Asset list[], int count)
{
    int i;
    int poorCount = 0;
    double highest;
    double lowest;

    printf("\nASSET REPORT\n");

    if (count == 0)
    {
        printf("No assets registered yet.\n");
        return;
    }

    highest = list[0].purchaseValue;
    lowest = list[0].purchaseValue;

    for (i = 0; i < count; i++)
    {
        if (list[i].purchaseValue > highest)
        {
            highest = list[i].purchaseValue;
        }
        if (list[i].purchaseValue < lowest)
        {
            lowest = list[i].purchaseValue;
        }
        if (strcmp(list[i].condition, "Poor") == 0)
        {
            poorCount++;
        }
    }

    printf("Total Assets: %d\n", count);
    printf("Total Purchase Value: N$%.2f\n", calculateTotalAssetValue(list, count));
    printf("Highest Value: N$%.2f\n", highest);
    printf("Lowest Value: N$%.2f\n", lowest);
    printf("Assets in Poor Condition: %d\n", poorCount);

    printAssetHeader();
    for (i = 0; i < count; i++)
    {
        printAssetRow(&list[i]);
    }
}

void assetMenu(void)
{
    int choice;

    do
    {
        printf("\n===== ASSET MANAGEMENT =====\n");
        printf("1. Add Asset\n");
        printf("2. Display All Assets\n");
        printf("3. Search Assets\n");
        printf("4. Asset Report\n");
        printf("5. Return to Main Menu\n");

        choice = readInt("Enter your choice: ", 1, 5);

        switch (choice)
        {
            case 1:
                addAsset(assets, &assetCount);
                break;
            case 2:
                displayAssets(assets, assetCount);
                break;
            case 3:
                searchAsset(assets, assetCount);
                break;
            case 4:
                displayAssetReport(assets, assetCount);
                break;
            case 5:
                printf("Returning to Main Menu.\n");
                break;
        }
    } while (choice != 5);
}
