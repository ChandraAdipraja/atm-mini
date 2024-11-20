#ifndef ADMIN_H
#define ADMIN_H

#include "functions.h"
#include "string.h"
// Fungsi untuk menambah user
void addUser(struct User users[], int *userCount)
{
    system("cls");
    struct User newUser;

    printf("----------------------------------\n");
    printf("\t  TAMBAH USER AKUN\n");
    printf("----------------------------------\n");
    getchar();
    printf("Masukkan Nama Pengguna : ");
    fgets(newUser.username, sizeof(newUser.username), stdin);
    newUser.username[strlen(newUser.username) - 1] = '\0';
    printf("Masukkan Kata Sandi    : ");
    scanf("%s", newUser.password);
    while (strcmp(newUser.role, "admin") != 0 && strcmp(newUser.role, "customer") != 0)
    {
        printf("Masukkan Peran (admin/customer): ");
        scanf("%s", newUser.role);
    }

    for (int i = 0; i < *userCount; i++)
    {
        if (strcmp(users[i].username, newUser.username) == 0)
        {
            printf("Username sudah digunakan! Coba lagi dengan username lain\n");
            return;
        }
    }

    newUser.amount = 0;

    users[*userCount] = newUser;
    (*userCount)++;
    printf("User %s Berhasil Ditambahkan!\n", newUser.username);
}

// Fungsi untuk menghapus user
void deleteUser(struct User users[], int *userCount)
{
    system("cls");

    char username[50];
    getchar();
    printf("----------------------------------\n");
    printf("\t  HAPUS PENGGUNA\n");
    printf("----------------------------------\n");
    printf("Masukkan Nama Pengguna Yang Akan Dihapus : ");
    fgets(username, sizeof(username), stdin);
    username[strlen(username) - 1] = '\0';

    for (int i = 0; i < *userCount; i++)
    {
        if (strcmp(users[i].username, username) == 0)
        {
            for (int j = i; j < *userCount - 1; j++)
            {
                users[j] = users[j + 1];
            }
            (*userCount)--;
            printf("Pengguna Berhasil Dihapus!\n");
            return;
        }
    }
    printf("Pengguna Tidak Ditemukan!\n");
}

// Fungsi untuk melihat daftar user
void viewUsers(struct User users[], int userCount)
{
    system("cls");
    printf("----------------------------------\n");
    printf("\t  DAFTAR PENGGUNA\n");
    printf("----------------------------------\n");
    for (int i = 0; i < userCount; i++)
    {
        printf("%d. %s (%s)\n", i + 1, users[i].username, users[i].role);
    }
}

// Fungsi untuk melihat semua transaksi
void viewAllTransactions(struct Transaction transactions[], int transactionCount)
{
    system("cls");
    printf("----------------------------------\n");
    printf("\t  DAFTAR TRANSAKSI\n");
    printf("----------------------------------\n");
    for (int i = 0; i < transactionCount; i++)
    {
        printf("Pengguna: %s, Kepada: %s, Jumlah: %.2f, Tipe: %s\n",
               transactions[i].user, transactions[i].to, transactions[i].amount, transactions[i].type);
    }
}

void menuAdmin(struct User users[], int *userCount, struct Transaction transactions[], int *transactionCount)
{

    int pilihan;
    char ulang;
    do
    {
        system("cls");
        printf("\nSelamat Datang %s Anda Login Sebagai %s\n", users->username, users->role);
        printf("\n=== Menu Admin ===\n");
        printf("1. Tambah Pengguna\n");
        printf("2. Hapus Pengguna\n");
        printf("3. Lihat Semua Pengguna\n");
        printf("4. Lihat Semua Transaksi\n");
        printf("5. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);

        switch (pilihan)
        {
        case 1:
            addUser(users, userCount);
            writeUserFile("user.txt", users, *userCount);
            writeAccountFile("account.txt", users, *userCount);
            break;
        case 2:
            deleteUser(users, userCount);
            writeUserFile("user.txt", users, *userCount);
            writeAccountFile("account.txt", users, *userCount);
            break;
        case 3:
            viewUsers(users, *userCount);
            break;
        case 4:
            readTransactionFile("transaksi.txt", transactions, transactionCount);
            viewAllTransactions(transactions, *transactionCount);
            break;
        case 5:
            printf("Logout berhasil!\n");
            return;
        default:
            printf("Pilihan tidak valid!\n");
        }
        printf("\nKembali ke menu utama? (y/n): ");
        scanf(" %c", &ulang);
        if (ulang != 'y')
        {
            printf("Terimakasih telah menggunakan layanan kami!\n");
            return;
        }
    } while (ulang == 'y' && pilihan != 5);
}

#endif