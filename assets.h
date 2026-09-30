#ifndef ASSETS_H
#define ASSETS_H

#define MAX_ASSETS          100
#define ASSET_NAME_LEN      50
#define ASSET_TYPE_LEN      30
#define ASSET_DEPT_LEN      30
#define ASSET_CONDITION_LEN 10

typedef struct
{
    int assetID;
    char name[ASSET_NAME_LEN];
    char type[ASSET_TYPE_LEN];
    double purchaseValue;
    char department[ASSET_DEPT_LEN];
    char condition[ASSET_CONDITION_LEN];
} Asset;

extern Asset assets[MAX_ASSETS];
extern int assetCount;

void addAsset(Asset list[], int *count);
void displayAssets(const Asset list[], int count);
void searchAsset(const Asset list[], int count);
int findAssetIndexByID(const Asset list[], int count, int id);
double calculateTotalAssetValue(const Asset list[], int count);
void displayAssetReport(const Asset list[], int count);
void assetMenu(void);

#endif
