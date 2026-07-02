#include "global.h"

void tambahProduk() {
    if (totalProduk >= MAX_PRODUK) {
        cout << "\nKatalog penuh!\n";
        return;
    }
    
    Produk baru;
    baru.id = productCounter++;
    
    cout << "\n--- TAMBAH PRODUK BARU ---\n";
    cout << "Nama Produk : ";
    getline(cin >> ws, baru.nama);
    baru.harga = inputIntValid("Harga (Rp)  : ");
    baru.stok = inputIntValid("Stok        : ");
    
    int pilKat = inputIntValid("Kategori (1. Elektronik, 2. Pakaian): ");
    baru.kategori = (pilKat == 1) ? "Elektronik" : "Pakaian";
    
    baru.pemilik = currentUser; // Dimiliki oleh penjual yang sedang login

    katalog[totalProduk] = baru;
    totalProduk++;

    cout << "\n[Sukses] Produk berhasil ditambahkan ke katalog!\n";
}

void tampilkanKatalogGlobal() {
    if (totalProduk == 0) {
        cout << "\nBelum ada produk di etalase.\n";
        return;
    }

    cout << "\n===============================================================================\n";
    cout << left << setw(5) << "ID" << setw(25) << "NAMA PRODUK" << setw(15) << "HARGA" 
         << setw(10) << "STOK" << setw(15) << "KATEGORI" << "PENJUAL\n";
    cout << "===============================================================================\n";
    
    for (int i = 0; i < totalProduk; i++) {
        cout << left << setw(5) << katalog[i].id 
             << setw(25) << katalog[i].nama 
             << "Rp " << setw(12) << katalog[i].harga 
             << setw(10) << katalog[i].stok 
             << setw(15) << katalog[i].kategori 
             << katalog[i].pemilik << endl;
    }
    cout << "===============================================================================\n";
}

void tampilkanKatalogPenjual(string penjual) {
    bool ada = false;
    cout << "\n===============================================================================\n";
    cout << left << setw(5) << "ID" << setw(25) << "NAMA PRODUK" << setw(15) << "HARGA" 
         << setw(10) << "STOK" << setw(15) << "KATEGORI\n";
    cout << "===============================================================================\n";
    
    for (int i = 0; i < totalProduk; i++) {
        // Admin bisa lihat punya spesifik, atau penjual lihat miliknya
        if (katalog[i].pemilik == penjual || currentRole == "ADMIN") { 
            cout << left << setw(5) << katalog[i].id 
                 << setw(25) << katalog[i].nama 
                 << "Rp " << setw(12) << katalog[i].harga 
                 << setw(10) << katalog[i].stok 
                 << setw(15) << katalog[i].kategori << endl;
            ada = true;
        }
    }
    cout << "===============================================================================\n";
    if (!ada) cout << "Tidak ada produk dari toko Anda.\n";
}

void editProduk() {
    tampilkanKatalogPenjual(currentUser);
    if (totalProduk == 0) return;

    int cariID = inputIntValid("\nMasukkan ID Produk yang ingin diubah: ");

    for (int i = 0; i < totalProduk; i++) {
        if (katalog[i].id == cariID && (katalog[i].pemilik == currentUser || currentRole == "ADMIN")) {
            cout << "--- EDIT PRODUK [" << katalog[i].nama << "] ---\n";
            katalog[i].harga = inputIntValid("Harga Baru (Rp): ");
            int tStok = inputIntValid("Stok Tambahan  : ");
            katalog[i].stok += tStok;
            cout << "\n[Sukses] Data produk berhasil diperbarui!\n";
            return;
        }
    }
    cout << "\n[Gagal] Produk dengan ID " << cariID << " tidak ditemukan atau bukan milik Anda.\n";
}

void hapusProduk() {
    tampilkanKatalogPenjual(currentUser);
    if (totalProduk == 0) return;

    int cariID = inputIntValid("\nMasukkan ID Produk yang ingin dihapus: ");

    for (int i = 0; i < totalProduk; i++) {
        if (katalog[i].id == cariID && (katalog[i].pemilik == currentUser || currentRole == "ADMIN")) {
            for (int j = i; j < totalProduk - 1; j++) {
                katalog[j] = katalog[j + 1];
            }
            totalProduk--;
            cout << "\n[Sukses] Produk berhasil dihapus dari etalase!\n";
            return;
        }
    }
    cout << "\n[Gagal] Produk tidak ditemukan atau bukan milik Anda.\n";
}
