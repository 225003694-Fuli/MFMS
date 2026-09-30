#ifndef SUPPLIERS_H
#define SUPPLIERS_H

#define MAX_SUPPLIERS 100

#define SUPPLIER_NAME_LEN  50
#define SUPPLIER_EMAIL_LEN 50
#define SUPPLIER_PHONE_LEN 20
#define SUPPLIER_TOWN_LEN  30

typedef struct {
    int  supplierID;
    char name[SUPPLIER_NAME_LEN];
    char email[SUPPLIER_EMAIL_LEN];
    char telephone[SUPPLIER_PHONE_LEN];
    char town[SUPPLIER_TOWN_LEN];
} Supplier;

extern Supplier suppliers[MAX_SUPPLIERS];
extern int supplierCount;

void supplierMenu(void);

void addSupplier(Supplier list[], int *count);
void displaySuppliers(const Supplier list[], int count);
void searchSupplierByID(const Supplier list[], int count);
void searchSupplierByName(const Supplier list[], int count);
void searchSupplierByTown(const Supplier list[], int count);
void compareSuppliers(const Supplier list[], int count);

int findSupplierIndexByID(const Supplier list[], int count, int id);
int isValidEmail(const char *email);
int isValidPhone(const char *phone);

#endif
