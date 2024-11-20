#ifndef USER_H
#define USER_H

#include "functions.h"
#include "time.h"

// Fungsi untuk mengecek saldo
// Parhan
void checkBalance(struct User users[], int userCount, const char *username)
{
    system("cls");
    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].username, username) == 0)
        {
            printf("----------------------------------\n");
            printf("\t  SALDO\n");
            printf("----------------------------------\n");
            printf("Saldo Anda : %.2f\n", users[i].amount);
            return;
        }
    }
    printf("Username tidak ditemukan!\n");
}

// Fungsi untuk penarikan
// Parhan
void withdraw(struct User users[], int userCount, struct Transaction transactions[], int *transactionCount, const char *username)
{
    time_t sekarang;
    struct tm *waktu;

    time(&sekarang);
    waktu = localtime(&sekarang);

    system("cls");
    float amount;
    printf("----------------------------------\n");
    printf("\t  TARIK TUNAI\n");
    printf("----------------------------------\n");
    printf("Masukkan nominal penarikan: ");

    scanf("%f", &amount);

    // menambahkan pengecheckan nominal penarikan tidak boleh negatif
    if (amount < 0)
    {
        printf("Nominal penarikan tidak valid!\n");
        return;
    }

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].username, username) == 0)
        {
            if (users[i].amount >= amount)
            {
                users[i].amount -= amount;
                strcpy(transactions[*transactionCount].user, username);
                strcpy(transactions[*transactionCount].to, username);
                transactions[*transactionCount].amount = amount;
                strcpy(transactions[*transactionCount].type, "Tarik Tunai");
                (*transactionCount)++;
                printf("Penarikan berhasil!\n");
                printf("Tanggal \t Waktu\n%02d-%02d-%04d \t %02d:%02d\n", waktu->tm_mday, waktu->tm_mon + 1, waktu->tm_year + 1900, waktu->tm_hour, waktu->tm_min);
                return;
            }
            else
            {
                printf("Saldo tidak mencukupi!\n");
                return;
            }
        }
    }
    printf("User tidak ditemukan!\n");
}

// Fungsi untuk setoran
void deposit(struct User users[], int userCount, struct Transaction transactions[], int *transactionCount, const char *username)
{
    time_t sekarang;
    struct tm *waktu;

    time(&sekarang);
    waktu = localtime(&sekarang);

    system("cls");
    float amount;
    printf("----------------------------------\n");
    printf("\t  SETOR TUNAI\n");
    printf("----------------------------------\n");
    printf("Masukkan nominal setoran: ");
    scanf("%f", &amount);

    if (amount <= 0)
    {
        printf("Nominal Tidak Valid\n");
        return;
    }

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].username, username) == 0)
        {
            users[i].amount += amount;
            strcpy(transactions[*transactionCount].user, username);
            strcpy(transactions[*transactionCount].to, username);
            transactions[*transactionCount].amount = amount;
            strcpy(transactions[*transactionCount].type, "Setor Tunai");
            (*transactionCount)++;
            printf("Setoran berhasil!\n");
            printf("Tanggal \t Waktu\n%02d-%02d-%04d \t %02d:%02d\n", waktu->tm_mday, waktu->tm_mon + 1, waktu->tm_year + 1900, waktu->tm_hour, waktu->tm_min);
            return;
        }
    }
}
// Dzikra
// Fungsi untuk transfer
void transfer(struct User users[], int userCount, struct Transaction transactions[], int *transactionCount, const char *username)
{
    time_t sekarang;
    struct tm *waktu;

    time(&sekarang);
    waktu = localtime(&sekarang);
    system("cls");
    char recipient[50];
    float amount;
    char password[50];
    printf("----------------------------------\n");
    printf("\t  TRANSFER\n");
    printf("----------------------------------\n");
    printf("Masukkan username penerima: ");
    scanf("%s", recipient);
    if (strcmp(username, recipient) == 0)
    {
        printf("Tidak bisa transfer ke diri sendiri!\n");
        return;
    }

    printf("Masukkan nominal transfer: ");
    scanf("%f", &amount);

    if (amount <= 0)
    {
        printf("Nominal tranfer tidak valid!\n");
        return;
    }
    printf("Masukkan password: ");
    scanf("%s", password);

    // buat pengecheckan supaya tidak bisa transfer ke diri sendiri

    int senderIndex = -1, recipientIndex = -1;
    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].username, username) == 0)
        {
            senderIndex = i;
        }
        if (strcmp(users[i].username, recipient) == 0)
        {
            recipientIndex = i;
        }
    }

    if (senderIndex != -1 && strcmp(users[senderIndex].password, password) == 0)
    {
        if (recipientIndex != -1)
        {
            if (users[senderIndex].amount >= amount)
            {
                users[senderIndex].amount -= amount;
                users[recipientIndex].amount += amount;
                strcpy(transactions[*transactionCount].user, username);
                strcpy(transactions[*transactionCount].to, recipient);
                transactions[*transactionCount].amount = amount;
                strcpy(transactions[*transactionCount].type, "Transfer");
                (*transactionCount)++;
                printf("Transfer berhasil!\n");
                printf("Tanggal \t Waktu\n%02d-%02d-%04d \t %02d:%02d\n", waktu->tm_mday, waktu->tm_mon + 1, waktu->tm_year + 1900, waktu->tm_hour, waktu->tm_min);
            }
            else
            {
                printf("Saldo tidak mencukupi!\n");
            }
        }
        else
        {
            printf("Penerima tidak ditemukan!\n");
        }
    }
    else
    {
        printf("Password salah!\n");
    }
}

// Fungsi untuk melihat transaksi user tertentu
// Farrel
void viewUserTransactions(struct Transaction transactions[], int transactionCount, const char *username)
{
    system("cls");
    printf("\n=== Transaksi untuk %s ===\n", username);
    int found = 0;
    for (int i = 0; i < transactionCount; i++)
    {
        if (strcmp(transactions[i].user, username) == 0)
        {
            printf("Kepada: %s, Jumlah: %.2f, Tipe: %s\n", transactions[i].to, transactions[i].amount, transactions[i].type);
            found = 1;
        }
    }
    if (!found)
    {
        printf("Belum ada transaksi untuk user ini.\n");
    }
}

// Farrel
void menuCustomer(struct User users[], int userCount, struct CurrentUser *currentUser, struct Transaction transactions[], int *transactionCount)
{
    system("cls");
    int pilihan;
    char ulang;
    do
    {
        printf("\n=== Menu Customer ===\n");
        printf("1. Lihat Saldo\n");
        printf("2. Tarik Tunai\n");
        printf("3. Setor Tunai\n");
        printf("4. Transfer\n");
        printf("5. Lihat Transaksi\n");
        printf("6. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);
        printf("\n=====================\n");

        switch (pilihan)
        {
        case 1:
            system("cls");
            checkBalance(users, userCount, currentUser->username);
            break;
        case 2:
            system("cls");
            withdraw(users, userCount, transactions, transactionCount, currentUser->username);
            writeAccountFile("account.txt", users, userCount);
            writeTransactionFile("transaksi.txt", transactions, *transactionCount);
            break;
        case 3:
            system("cls");
            deposit(users, userCount, transactions, transactionCount, currentUser->username);
            writeAccountFile("account.txt", users, userCount);
            writeTransactionFile("transaksi.txt", transactions, *transactionCount);
            break;
        case 4:
            system("cls");
            transfer(users, userCount, transactions, transactionCount, currentUser->username);
            writeAccountFile("account.txt", users, userCount);
            writeTransactionFile("transaksi.txt", transactions, *transactionCount);
            break;
        case 5:
            system("cls");
            viewUserTransactions(transactions, *transactionCount, currentUser->username);
            break;
        case 6:
            printf("Logout berhasil!\n");
            return;
        default:
            printf("Pilihan tidak valid!\n");
        }

        printf("Kembali ke menu utama? (y/n): ");
        scanf(" %c", &ulang);
        if (ulang != 'y')
        {
            printf("Terimakasih telah menggunakan layanan kami!\n");
            return;
        }
    } while (ulang == 'y');
}

#endif
