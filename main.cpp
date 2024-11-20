#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "admin.h"
#include "user.h"
#include "functions.h"

#define MAX_USERS 100
#define MAX_TRANSACTIONS 100

// Dzikra's Duty
int main()
{
    struct User users[MAX_USERS];
    struct Transaction transactions[MAX_TRANSACTIONS];
    int userCount = 0, transactionCount = 0;

    struct CurrentUser currentUser;

    // Load user and transaction data from files
    readUserFile("user.txt", users, &userCount);
    readAccountFile("account.txt", users, userCount);
    readTransactionFile("transaksi.txt", transactions, &transactionCount);

    int pilihan;
    do
    {
        printf("\n=== BSI ===\n");
        printf("1. Login\n");
        printf("2. Keluar\n");
        printf("Pilih menu: ");

        scanf("%d", &pilihan);

        if (pilihan == 1)
        {
            system("cls");
            if (login(users, userCount, &currentUser, 3))
            {
                if (strcmp(currentUser.role, "admin") == 0)
                {
                    menuAdmin(users, &userCount, transactions, &transactionCount);
                }
                else if (strcmp(currentUser.role, "customer") == 0)
                {
                    menuCustomer(users, userCount, &currentUser, transactions, &transactionCount);
                }
            }
            else
            {
                return 0;
            }
        }
        else if (pilihan == 2)
        {
            printf("Terima kasih!\n");
            break;
        }
        else
        {
            printf("Tidak ada menu yang dipilih\n");
        }
    } while (pilihan != 1 || pilihan != 2);

    printf("Program selesai.\n");

    // // Save user and transaction data back to files
    // writeUserFile("user.txt", users, userCount);
    // writeAccountFile("account.txt", users, userCount);
    // writeTransactionFile("transaksi.txt", transactions, transactionCount);

    return 0;
}
