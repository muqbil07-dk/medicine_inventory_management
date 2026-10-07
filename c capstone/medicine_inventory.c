#include <stdio.h>
#include <string.h>
#define MAX_MEDICINES 100

/* Structure to store medicine details */
struct Medicine {
    char name[50];
    char batchID[20];
    int quantity;
    int expMonth;
    int expYear;
    int daysLeft;
};

/* Function to calculate remaining days */
void calculateDaysLeft(struct Medicine *med, int currentMonth, int currentYear)
{
    int monthsLeft;
    monthsLeft = (med->expYear - currentYear) * 12
                 + (med->expMonth - currentMonth);

    med->daysLeft = monthsLeft * 30;
}

/* Function to clear input buffer */
void clearBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        /* Clear buffer */
    }
}

int main()
{
    struct Medicine med[MAX_MEDICINES];
    struct Medicine temp;
    int count;
    int choice;
    int found;
    int i;
    int j;
    char searchID[20];

    /* Current date */
    int currentMonth;
    int currentYear;
    count = 0;
    currentMonth = 8;
    currentYear = 2026;

    /* Initial medicine data */
    struct Medicine initialData[] = {
        {"Paracetamol 500 mg",  "PCM24001", 250, 8,  2026, 0},
        {"Amoxicillin 500 mg",  "AMX24015", 120, 7,  2026, 0},
        {"Cetirizine 10 mg",    "CET24102", 180, 9,  2026, 0},
        {"Ibuprofen 400 mg",    "IBU24089", 90,  8,  2026, 0},
        {"Metformin 500 mg",    "MET24111", 320, 12, 2026, 0},
        {"Azithromycin 250 mg", "AZI24055", 60,  7,  2026, 0},
        {"Pantoprazole 40 mg",  "PAN24210", 150, 10, 2026, 0},
        {"Vitamin C 500 mg",    "VTC24167", 400, 8,  2026, 0},
        {"Dolo 650",            "DOL24234", 280, 11, 2026, 0},
        {"Omeprazole 20 mg",    "OME24098", 110, 8,  2026, 0},
        {"Aspirin 75 mg",       "ASP24256", 200, 1,  2027, 0},
        {"Amlodipine 5 mg",     "AML24311", 140, 3,  2027, 0},
        {"Levocetirizine 5 mg", "LVC24190", 75,  8,  2026, 0},
        {"Cough Syrup",         "CSY24043", 45,  7,  2026, 0},
        {"ORS Powder",          "ORS24281", 350, 2,  2027, 0},
        {"Zinc Tablets",        "ZNC24154", 210, 8,  2026, 0},
        {"Calcium Tablets",     "CAL24320", 180, 5,  2027, 0},
        {"Insulin Injection",   "INS24277", 30,  8,  2026, 0},
        {"Diclofenac Gel",      "DIC24166", 95,  9,  2026, 0},
        {"Antacid Suspension",  "ANT24299", 65,  8,  2026, 0}
    };

    int initialCount;
    initialCount = sizeof(initialData) / sizeof(initialData[0]);

    /* Copy initial data into inventory */
    for (i = 0; i < initialCount; i++)
    {
        med[count] = initialData[i];
        calculateDaysLeft(
            &med[count],
            currentMonth,
            currentYear
        );
        count++;
    }

    /* Main menu */
    while (1)
    {
        printf("\n=============================================\n");
        printf("     MEDICINE INVENTORY MANAGEMENT SYSTEM\n");
        printf("     Current Date: %02d/%d\n",
               currentMonth,
               currentYear);
        printf("=============================================\n");
        printf("1. Add New Medicine\n");
        printf("2. View All Medicines (Sorted by Expiry)\n");
        printf("3. Search Medicine by Batch ID\n");
        printf("4. View Medicines Expiring Within 30 Days\n");
        printf("5. View Expired Medicines\n");
        printf("6. Exit\n");
        printf("---------------------------------------------\n");
        printf("Enter your choice (1-6): ");
        if (scanf("%d", &choice) != 1)
        {
            printf("\n[Error] Please enter a valid number.\n");
            clearBuffer();
            continue;
        }

        switch (choice)
        {
            /* ========================================= */
            /* 1. ADD NEW MEDICINE                       */
            /* ========================================= */

            case 1:
                if (count >= MAX_MEDICINES)
                {
                    printf("\n[Error] Inventory is full!\n");
                    break;
                }
                printf("\n---------- ADD NEW MEDICINE ----------\n");
                clearBuffer();
                printf("Enter Medicine Name: ");
                scanf("%49[^\n]", med[count].name);
                clearBuffer();
                printf("Enter Batch ID: ");
                scanf("%19s", med[count].batchID);
                printf("Enter Quantity in Stock: ");
                scanf("%d", &med[count].quantity);
                printf("Enter Expiry Month (1-12): ");
                scanf("%d", &med[count].expMonth);
                while (med[count].expMonth < 1 ||
                       med[count].expMonth > 12)
                {
                    printf("Invalid month. Enter again (1-12): ");
                    scanf("%d", &med[count].expMonth);
                }
                printf("Enter Expiry Year: ");
                scanf("%d", &med[count].expYear);
                while (med[count].expYear < currentYear)
                {
                    printf("Invalid year. Enter %d or later: ",
                           currentYear);
                    scanf("%d", &med[count].expYear);
                }
                calculateDaysLeft(
                    &med[count],
                    currentMonth,
                    currentYear
                );
                count++;
                printf("\n-> Medicine added successfully!\n");
                break;

            /* ========================================= */
            /* 2. VIEW ALL MEDICINES                     */
            /* ========================================= */

            case 2:
                if (count == 0)
                {
                    printf("\n[Notice] No medicine records found.\n");
                    break;
                }
                /*
                   Bubble Sort
                   Sort medicines according to days left.
                */

                for (i = 0; i < count - 1; i++)
                {
                    for (j = 0; j < count - i - 1; j++)
                    {
                        if (med[j].daysLeft >
                            med[j + 1].daysLeft)
                        {
                            temp = med[j];
                            med[j] = med[j + 1];
                            med[j + 1] = temp;
                        }
                    }
                }
                printf("\n");
                printf("=============== ALL MEDICINES ===============\n");
                printf("%-22s %-12s %-8s %-10s %-10s\n",
                       "Medicine Name",
                       "Batch ID",
                       "Stock",
                       "Expiry",
                       "Days Left");
                printf("---------------------------------------------------------------\n");
                for (i = 0; i < count; i++)
                {
                    printf("%-22s %-12s %-8d %02d/%-7d %-10d\n",
                           med[i].name,
                           med[i].batchID,
                           med[i].quantity,
                           med[i].expMonth,
                           med[i].expYear,
                           med[i].daysLeft);
                }
                break;


            /* ========================================= */
            /* 3. SEARCH MEDICINE                        */
            /* ========================================= */

            case 3:
                if (count == 0)
                {
                    printf("\n[Notice] Inventory is empty!\n");
                    break;
                }
                printf("\nEnter Batch ID to Search: ");
                scanf("%19s", searchID);
                found = 0;
                for (i = 0; i < count; i++)
                {
                    if (strcmp(med[i].batchID, searchID) == 0)
                    {
                        printf("\n---------- MEDICINE FOUND ----------\n");
                        printf("Medicine Name  : %s\n",
                               med[i].name);
                        printf("Batch ID       : %s\n",
                               med[i].batchID);
                        printf("Stock Quantity : %d\n",
                               med[i].quantity);
                        printf("Expiry Date    : %02d/%d\n",
                               med[i].expMonth,
                               med[i].expYear);
                        printf("Days Left      : %d\n",
                               med[i].daysLeft);
                        found = 1;
                        break;
                    }
                }
                if (found == 0)
                {
                    printf("\n[Error] No medicine found with Batch ID: %s\n",
                           searchID);
                }
                break;


            /* ========================================= */
            /* 4. EXPIRING WITHIN 30 DAYS                */
            /* ========================================= */

            case 4:
                if (count == 0)
                {
                    printf("\n[Notice] Inventory is empty!\n");
                    break;
                }
                printf("\n");
                printf("======= MEDICINES EXPIRING WITHIN 30 DAYS =======\n");

                found = 0;

                for (i = 0; i < count; i++)
                {
                    if (med[i].daysLeft >= 0 &&
                        med[i].daysLeft <= 30)
                    {
                        printf("%-22s Batch ID: %-10s "
                               "Qty: %-6d Days Left: %d\n",

                               med[i].name,
                               med[i].batchID,
                               med[i].quantity,
                               med[i].daysLeft);

                        found = 1;
                    }
                }

                if (found == 0)
                {
                    printf("No medicines are expiring within 30 days.\n");
                }

                break;


            /* ========================================= */
            /* 5. EXPIRED MEDICINES                      */
            /* ========================================= */

            case 5:

                if (count == 0)
                {
                    printf("\n[Notice] Inventory is empty!\n");
                    break;
                }

                printf("\n");
                printf("============= EXPIRED MEDICINES =============\n");

                found = 0;

                for (i = 0; i < count; i++)
                {
                    if (med[i].daysLeft < 0)
                    {
                        printf("%-22s Batch ID: %-10s "
                               "Qty: %-6d Expired %d days ago\n",

                               med[i].name,
                               med[i].batchID,
                               med[i].quantity,
                               -med[i].daysLeft);

                        found = 1;
                    }
                }

                if (found == 0)
                {
                    printf("No expired medicines found.\n");
                }

                break;


            /* ========================================= */
            /* 6. EXIT                                   */
            /* ========================================= */

            case 6:

                printf("\n");
                printf("Exiting Medicine Inventory Management System.\n");
                printf("Goodbye!\n");

                return 0;


            /* ========================================= */
            /* INVALID CHOICE                            */
            /* ========================================= */

            default:

                printf("\n[Error] Invalid choice!\n");
                printf("Please enter a number between 1 and 6.\n");
        }
    }

    return 0;
}
