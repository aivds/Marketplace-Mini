#ifndef GLOBAL_H
#define GLOBAL_H

#include <iostream>
#include <string>
using namespace std;

// --- 1. STRUCT UTAMA ---
struct Produk {
    int id;
    string nama;
    int harga;
    int stok;
};

// Struct Lelang Terbalik (Linked List)
struct BidNode {
    string pembeli;
    int hargaTawaran;
    BidNode* next;
};

// --- 2. VARIABEL GLOBAL ---
extern Produk katalog[100];
extern int totalProduk;
extern BidNode* headBid; 
extern string grupPatungan[3]; 
extern int kuotaPatungan;

// --- 3. DEKLARASI FUNGSI ---
// (CRUD)
void tambahData(int id, string nama, int harga, int stok);
void inputTambahData();
void tampilkanData();
void updateData(int id, string namaBaru, int hargaBaru, int stokBaru);
void inputUpdateData();
void hapusData(int id); 
void inputHapusData();

// (File Handling)
void simpanDataKeFile();
void muatDataDariFile();

// (Stack & Queue)
void pushUndo(string aksi, int id);
void popUndo();
void enqueue(string pembeli, string produk, int jmlBeli = 1);
void inputEnqueue();
string keTitleCase(string str);
void tampilkanAntrean();
void dequeue();
void patunganBelanja(string pembeli, string produk); 
void inputPatunganBelanja();

// (Searching & Sorting)
void cariData(string keyword);
void inputCariData();
void urutkanData();
void prosesBarter(string pembeli, string produkTujuan, string barangBekas); 
void inputBarter();

// (Linked List & Integrasi)
void tambahRiwayat(string log);
void tampilkanRiwayat();
void tambahBidLelang(string pembeli, int harga); 
void inputTambahBidLelang();
void lihatLelang(); 

#endif