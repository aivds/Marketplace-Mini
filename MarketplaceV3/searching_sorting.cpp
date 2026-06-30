#include "global.h"

// Ubah text menjadi lowercase untuk pencarian yang case-insensitive
string toLower(string str) {
    string res = "";
    for (char c : str) res += tolower(c);
    return res;
}

void cariProduk() {
    if (totalProduk == 0) {
        cout << "\nBelum ada produk di etalase.\n";
        return;
    }

    string keyword;
    cout << "\nMasukkan Nama Produk yang dicari: ";
    getline(cin >> ws, keyword);
    keyword = toLower(keyword);

    bool ketemu = false;
    cout << "\n===============================================================================\n";
    cout << left << setw(5) << "ID" << setw(25) << "NAMA PRODUK" << setw(15) << "HARGA" 
         << setw(10) << "STOK" << setw(15) << "KATEGORI" << "PENJUAL\n";
    cout << "===============================================================================\n";
    
    // Linear Search
    for (int i = 0; i < totalProduk; i++) {
        if (toLower(katalog[i].nama).find(keyword) != string::npos) {
            cout << left << setw(5) << katalog[i].id 
                 << setw(25) << katalog[i].nama 
                 << "Rp " << setw(12) << katalog[i].harga 
                 << setw(10) << katalog[i].stok 
                 << setw(15) << katalog[i].kategori 
                 << katalog[i].pemilik << endl;
            ketemu = true;
        }
    }
    cout << "===============================================================================\n";
    
    if (!ketemu) cout << "Produk dengan kata kunci '" << keyword << "' tidak ditemukan.\n";
}

void urutkanBerdasarkanHarga(bool ascending) {
    // Selection Sort
    for (int i = 0; i < totalProduk - 1; i++) {
        int idx_target = i;
        for (int j = i + 1; j < totalProduk; j++) {
            if (ascending) {
                if (katalog[j].harga < katalog[idx_target].harga) idx_target = j;
            } else {
                if (katalog[j].harga > katalog[idx_target].harga) idx_target = j;
            }
        }
        if (idx_target != i) {
            Produk temp = katalog[i];
            katalog[i] = katalog[idx_target];
            katalog[idx_target] = temp;
        }
    }
    cout << "\n[Sukses] Etalase berhasil diurutkan berdasarkan harga " 
         << (ascending ? "(Termurah -> Termahal)" : "(Termahal -> Termurah)") << "!\n";
}

void filterBerdasarkanKategori() {
    cout << "\nPilih Kategori:\n1. Elektronik\n2. Pakaian\nPilih: ";
    int pil; cin >> pil;
    string target = (pil == 1) ? "Elektronik" : "Pakaian";

    bool ketemu = false;
    cout << "\n===============================================================================\n";
    cout << left << setw(5) << "ID" << setw(25) << "NAMA PRODUK" << setw(15) << "HARGA" 
         << setw(10) << "STOK" << setw(15) << "KATEGORI" << "PENJUAL\n";
    cout << "===============================================================================\n";
    
    for (int i = 0; i < totalProduk; i++) {
        if (toLower(katalog[i].kategori) == toLower(target)) {
            cout << left << setw(5) << katalog[i].id 
                 << setw(25) << katalog[i].nama 
                 << "Rp " << setw(12) << katalog[i].harga 
                 << setw(10) << katalog[i].stok 
                 << setw(15) << katalog[i].kategori 
                 << katalog[i].pemilik << endl;
            ketemu = true;
        }
    }
    cout << "===============================================================================\n";
    
    if (!ketemu) cout << "Tidak ada produk dalam kategori " << target << ".\n";
}

void menuSorting() {
    if (totalProduk == 0) {
        cout << "\nBelum ada produk di etalase.\n";
        return;
    }
    int pil;
    cout << "\n--- OPSI TAMPILAN ---\n";
    cout << "1. Urutkan Harga Termurah\n";
    cout << "2. Urutkan Harga Termahal\n";
    cout << "3. Filter Kategori\n";
    cout << "4. Tampilkan Semua (Default)\n";
    cout << "Pilih (1-4): ";
    cin >> pil;

    if (pil == 1) {
        urutkanBerdasarkanHarga(true);
        tampilkanKatalogGlobal();
    } else if (pil == 2) {
        urutkanBerdasarkanHarga(false);
        tampilkanKatalogGlobal();
    } else if (pil == 3) {
        filterBerdasarkanKategori();
    } else {
        tampilkanKatalogGlobal();
    }
}
