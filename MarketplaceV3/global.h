#ifndef GLOBAL_H
#define GLOBAL_H

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cstdlib> // Untuk system("cls")

using namespace std;

// Struktur Data Utama

// Struct Akun
struct Akun {
    string username;
    string password;
    string role; // "ADMIN", "PENJUAL", "PEMBELI"
};

// Struct Produk (Katalog Array)
struct Produk {
    int id;
    string nama;
    int harga;
    int stok;
    string kategori; // "Elektronik" atau "Pakaian"
    string pemilik;  // Username penjual
};

// Struktur Data Dinamis

// Struct Keranjang Belanja
struct NodeKeranjang {
    int idProduk;
    string namaProduk;
    int harga;
    int jumlah;
    string pemilik; // Penjual produk
    NodeKeranjang* next;
};

// Struct Antrean Pesanan
struct NodePesanan {
    int idPesanan;
    string pembeli;
    string penjual;
    int totalHarga;
    string detailPesanan;
    string status; // "Menunggu Diproses"
    NodePesanan* next;
};

// Struct Riwayat Transaksi
struct NodeRiwayat {
    int idPesanan;
    string pembeli;
    string penjual;
    int totalHarga;
    string detailPesanan;
    string status; // "Dikirim", "Selesai"
    NodeRiwayat* next;
};

// Variabel Global
const int MAX_PRODUK = 1000;
const int MAX_AKUN = 100;

extern Produk katalog[MAX_PRODUK];
extern int totalProduk;

extern Akun daftarAkun[MAX_AKUN];
extern int totalAkun;

extern string currentUser;
extern string currentRole;
extern int orderCounter;
extern int productCounter;

// Pointer Struktur Dinamis
extern NodeKeranjang* topKeranjang;
extern NodePesanan* frontQueue;
extern NodePesanan* rearQueue;
extern NodeRiwayat* headRiwayat;
extern NodeRiwayat* tailRiwayat;

// Deklarasi Fungsi

// Manajemen File
void muatSemuaData();
void simpanSemuaData();

// Utilitas dan Autentikasi
void clearScreen();
void pauseScreen();
string toLower(string str);
bool loginProcess();
void registerProcess();

// Manajemen Akun
void tampilkanDaftarUser();
void hapusAkun();

// Operasi Katalog
void tambahProduk();
void tampilkanKatalogGlobal();
void tampilkanKatalogPenjual(string penjual);
void editProduk();
void hapusProduk();

// Pencarian dan Pengurutan
void cariProduk();
void menuSorting();
void urutkanBerdasarkanHarga(bool ascending);
void filterBerdasarkanKategori();

// Operasi Stack Keranjang
void tambahKeKeranjang();
void popKeranjang();
void tampilkanKeranjang();
void checkoutKeranjang();
void clearKeranjang();

// Operasi Queue Pesanan
void enqueuePesanan(string pembeli, string penjual, int total, string detail);
void dequeuePesanan(string penjual, bool isAdmin);
void tampilkanAntreanPesanan(string penjual, bool isAdmin);

// Operasi Linked List Riwayat
void tambahRiwayat(int idPesanan, string pembeli, string penjual, int total, string detail, string status);
void tampilkanRiwayatGlobal();
void tampilkanRiwayatPembeli(string pembeli);
void konfirmasiPenerimaan();
void tampilkanStatistik();
void cetakNota();

#endif
