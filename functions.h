#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Struktur data untuk User dan Transaction
struct User
{
    char username[50];
    char password[50];
    char role[10];
    float amount;
};

struct Transaction
{
    char user[50];
    char to[50];
    float amount;
    char type[20];
};

struct CurrentUser
{
    char username[50];
    char role[10];
};

int login(struct User users[], int userCount, struct CurrentUser *currentUser, int attempt)
{
    char username[50], password[50];

    if (attempt == 0)
    {
        printf("Terlalu Banyak Melakukan Percobaan, Coba Lagi Nanti\n");
        return 0;
    }
    getchar();
    printf("============= Login ==============\n");
    printf("| Masukkan username: ");

    fgets(username, sizeof(username), stdin);
    username[strlen(username) - 1] = '\0';

    printf("| Masukkan password: ");
    scanf("%s", password);
    printf("==================================\n");

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0)
        {
            strcpy(currentUser->username, users[i].username);
            strcpy(currentUser->role, users[i].role);
            printf("Login berhasil sebagai %s!\n", currentUser->role);
            return 1;
        }
    }

    printf("Username atau password salah!\n");
    return login(users, userCount, currentUser, attempt - 1);
}

// Fungsi untuk membaca data user dari file
int readUserFile(const char *filename, struct User users[], int *userCount)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("Gagal membuka file %s\n", filename);
        return 0;
    }

    char line[150];
    *userCount = 0;
    while (fgets(line, sizeof(line), f))
    {
        line[strcspn(line, "\n")] = 0;
        char *token = strtok(line, ",");
        if (token != NULL)
        {
            strcpy(users[*userCount].username, token);
            token = strtok(NULL, ",");

            strcpy(users[*userCount].password, token);
            token = strtok(NULL, ",");

            strcpy(users[*userCount].role, token);
            users[*userCount].amount = 0;
            (*userCount)++;
        }
    }
    fclose(f);
    return 1;
}

// Fungsi untuk menulis data user ke file
int writeUserFile(const char *filename, struct User users[], int userCount)
{
    FILE *f = fopen(filename, "w");
    if (f == NULL)
    {
        printf("Gagal membuka file %s untuk menulis\n", filename);
        return 0;
    }

    for (int i = 0; i < userCount; i++)
    {
        fprintf(f, "%s,%s,%s\n", users[i].username, users[i].password, users[i].role);
    }

    fclose(f);
    return 1;
}

// Fungsi untuk membaca saldo dari file account.txt dan memperbarui saldo pengguna
int readAccountFile(const char *filename, struct User users[], int userCount)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("Gagal membuka file %s\n", filename);
        return 0;
    }

    char line[100];
    while (fgets(line, sizeof(line), f))
    {
        line[strcspn(line, "\n")] = 0;

        char *token = strtok(line, ",");

        char username[50];
        float amount = 0;

        if (token != NULL)
        {
            strcpy(username, token);
            token = strtok(NULL, ",");
            amount = atof(token);
        }

        // Update amount di users jika username cocok
        for (int i = 0; i < userCount; i++)
        {
            if (strcmp(users[i].username, username) == 0)
            {
                users[i].amount = amount;
                break;
            }
        }
    }
    fclose(f);
    return 1;
}

// Fungsi untuk menulis saldo ke file account.txt
int writeAccountFile(const char *filename, struct User users[], int userCount)
{
    FILE *f = fopen(filename, "w");
    if (f == NULL)
    {
        printf("Gagal membuka file %s untuk menulis\n", filename);
        return 0;
    }

    for (int i = 0; i < userCount; i++)
    {
        fprintf(f, "%s,%.2f\n", users[i].username, users[i].amount);
    }

    fclose(f);
    return 1;
}

// Fungsi untuk membaca data transaksi dari file
int readTransactionFile(const char *filename, struct Transaction transactions[], int *transactionCount)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("Gagal membuka file %s\n", filename);
        return 0;
    }

    char line[150];
    *transactionCount = 0;
    while (fgets(line, sizeof(line), f))
    {
        line[strcspn(line, "\n")] = 0; // Menghilangkan newline
        char *token = strtok(line, ",");
        if (token != NULL)
        {
            strcpy(transactions[*transactionCount].user, token);
            token = strtok(NULL, ",");

            strcpy(transactions[*transactionCount].to, token);
            token = strtok(NULL, ",");

            transactions[*transactionCount].amount = atof(token);
            token = strtok(NULL, ",");

            strcpy(transactions[*transactionCount].type, token);
            (*transactionCount)++;
        }
    }
    fclose(f);
    return 1;
}

// Fungsi untuk menulis data transaksi ke file
int writeTransactionFile(const char *filename, struct Transaction transactions[], int transactionCount)
{
    FILE *f = fopen(filename, "w");
    if (f == NULL)
    {
        printf("Gagal membuka file %s untuk menulis\n", filename);
        return 0;
    }

    for (int i = 0; i < transactionCount; i++)
    {
        fprintf(f, "%s,%s,%.2f,%s\n", transactions[i].user, transactions[i].to, transactions[i].amount, transactions[i].type);
    }

    fclose(f);
    return 1;
}

#endif
