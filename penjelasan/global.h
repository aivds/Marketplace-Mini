#ifndef GLOBAL_H // Mencegah file ini di-include berulang kali yang bisa menyebabkan error
#define GLOBAL_H // Mendefinisikan GLOBAL_H

// Pustaka Standar C++
#include <iostream> // Untuk input/output dasar (cout, cin)
#include <string>   // Untuk tipe data teks (string)
#include <fstream>  // Untuk operasi baca/tulis file (File Handling: ifstream, ofstream)
#include <iomanip>  // Untuk merapikan output tabel di terminal (setw, left)
#include <sstream>  // Untuk konversi tipe data (misal stringstream)
#include <cstdlib>  // Untuk menjalankan perintah sistem operasi seperti system("cls")

using namespace std; // Agar tidak perlu menulis std:: terus-menerus

// Bagian 1: Struktur Data Utama (Berbasis Array)

// Struct Akun: Menyimpan data pengguna aplikasi
struct Akun {
    string username; // Nama pengguna (unik)
    string password; // Kata sandi
    string role;     // Hak akses pengguna: "ADMIN", "PENJUAL", atau "PEMBELI"
};

// Struct Produk: Menyimpan data barang dagangan (disimpan dalam Array)
struct Produk {
    int id;          // ID Unik produk (Dibuat otomatis berurutan)
    string nama;     // Nama barang
    int harga;       // Harga barang dalam Rupiah
    int stok;        // Jumlah stok yang tersedia
    string kategori; // Pengelompokan: "Elektronik" atau "Pakaian"
    string pemilik;  // Username dari PENJUAL yang memposting barang ini
};


// Bagian 2: Struktur Data Dinamis (Pointer dan Node)

// Struct Keranjang Belanja: Digunakan untuk STACK (Tumpukan / LIFO)
// Pembeli memasukkan barang ke keranjang satu per satu, menumpuk dari bawah ke atas.
struct NodeKeranjang {
    int idProduk;       // ID barang yang dibeli
    string namaProduk;  // Nama barang
    int harga;          // Harga satuan
    int jumlah;         // Jumlah pcs yang dipesan
    string pemilik;     // Nama toko/penjual barang ini
    NodeKeranjang* next; // Pointer menunjuk ke barang di tumpukan bawahnya
};

// Struct Antrean Pesanan: Digunakan untuk QUEUE (Antrean / FIFO)
// Setelah pembeli checkout, pesanan masuk ke antrean penjual. Siapa checkout duluan, dilayani duluan.
struct NodePesanan {
    int idPesanan;         // ID nota pesanan
    string pembeli;        // Nama username yang membeli
    string penjual;        // Nama username toko
    int totalHarga;        // Tagihan yang sudah dibayar
    string detailPesanan;  // Ringkasan (Nama barang dan Jumlah)
    string status;         // Status: "Menunggu Diproses"
    NodePesanan* next;     // Pointer menunjuk ke orang di belakang antrean
};

// Struct Riwayat Transaksi: Digunakan untuk LINKED LIST (Gerbong Berantai)
// Menyimpan sejarah permanen semua transaksi yang sudah selesai.
struct NodeRiwayat {
    int idPesanan;         
    string pembeli;
    string penjual;
    int totalHarga;
    string detailPesanan;
    string status;         // Status: "Dikirim", lalu menjadi "Selesai" jika dikonfirmasi
    NodeRiwayat* next;     // Pointer menunjuk ke gerbong catatan transaksi berikutnya
};


// Bagian 3: Variabel Global dan Pointer Utama
// Variabel ini dideklarasikan (extern) agar nilainya bisa dibagikan (diingat) oleh semua file cpp

const int MAX_PRODUK = 1000; // Kapasitas maksimal array produk
const int MAX_AKUN = 100;    // Kapasitas maksimal array akun

extern Produk katalog[MAX_PRODUK]; // Pembuatan array Katalog
extern int totalProduk;            // Penghitung jumlah produk yang saat ini ada

extern Akun daftarAkun[MAX_AKUN];  // Pembuatan array Akun
extern int totalAkun;              // Penghitung jumlah akun yang saat ini terdaftar

extern string currentUser; // Menyimpan nama user yang sedang login saat ini
extern string currentRole; // Menyimpan status role user yang sedang login (Admin/Penjual/Pembeli)
extern int orderCounter;   // Mesin pencetak ID Pesanan otomatis (selalu bertambah)
extern int productCounter; // Mesin pencetak ID Produk otomatis (selalu bertambah)

// Pointer Dasar Struktur Data
extern NodeKeranjang* topKeranjang; // Pointer menuju puncak tumpukan Stack Keranjang
extern NodePesanan* frontQueue;     // Pointer menuju orang paling depan di Queue Antrean
extern NodePesanan* rearQueue;      // Pointer menuju orang paling belakang di Queue Antrean
extern NodeRiwayat* headRiwayat;    // Pointer menuju awal gerbong Linked List Riwayat
extern NodeRiwayat* tailRiwayat;    // Pointer menuju akhir gerbong Linked List Riwayat


// Bagian 4: Deklarasi Fungsi (Daftar Isi)
// Memberi tahu C++ bahwa fungsi-fungsi di bawah ini ada, meski kode aslinya dipisah ke file lain.

// Manajemen File (file_handling.cpp) (Untuk baca/tulis ke database CSV)
void muatSemuaData();
void simpanSemuaData();

// Utilitas dan Autentikasi (main.cpp)
void clearScreen();               // Membersihkan layar terminal
void pauseScreen();               // Menahan layar sampai user menekan sembarang tombol
int inputIntValid(string prompt); // Pelindung input angka agar tidak infinite loop/crash saat diisi huruf
string toLower(string str);       // Mengubah huruf besar menjadi kecil (untuk pencarian)
bool loginProcess();              // Proses pencocokan username dan password
void registerProcess();           // Proses pembuatan akun baru

// Manajemen Akun
void tampilkanDaftarUser(); 
void hapusAkun();

// Operasi Katalog (crud_katalog.cpp) (Create, Read, Update, Delete produk)
void tambahProduk();
void tampilkanKatalogGlobal();
void tampilkanKatalogPenjual(string penjual);
void editProduk();
void hapusProduk();

// Pencarian dan Pengurutan (searching_sorting.cpp)
void cariProduk();
void menuSorting();
void urutkanBerdasarkanHarga(bool ascending);
void filterBerdasarkanKategori();

// Operasi Stack Keranjang (stack_keranjang.cpp)
void tambahKeKeranjang();
void popKeranjang();
void tampilkanKeranjang();
void checkoutKeranjang();
void clearKeranjang();

// Operasi Queue Pesanan (queue_pesanan.cpp)
void enqueuePesanan(string pembeli, string penjual, int total, string detail);
void dequeuePesanan(string penjual, bool isAdmin);
void tampilkanAntreanPesanan(string penjual, bool isAdmin);

// Operasi Linked List Riwayat (linked_list_riwayat.cpp)
void tambahRiwayat(int idPesanan, string pembeli, string penjual, int total, string detail, string status);
void tampilkanRiwayatGlobal();
void tampilkanRiwayatPembeli(string pembeli);
void konfirmasiPenerimaan();
void tampilkanStatistik();
void cetakNota();

#endif // Menutup perlindungan include
