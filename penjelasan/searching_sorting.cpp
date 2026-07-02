#include "global.h"

// Penjelasan Konsep Pencarian (Searching) dan Pengurutan (Sorting)

// Fungsi pembantu (Utility) agar pencarian mengabaikan huruf besar atau kecil (Case-Insensitive)
// Cara kerja: membedah huruf satu per satu dari sebuah kata, lalu dipaksa jadi huruf kecil semua.
// Contoh: "LaptOP" akan diubah paksa menjadi "laptop"
string toLower(string str) {
    string res = "";
    for (char c : str) res += tolower(c); // tolower adalah bawaan C++
    return res;
}

void cariProduk() { // Algoritma: Linear Search (Pencarian Lurus berurutan)
    if (totalProduk == 0) {
        cout << "\nBelum ada produk di etalase.\n";
        return;
    }

    string keyword;
    cout << "\nMasukkan Nama Produk yang dicari: ";
    getline(cin >> ws, keyword);
    
    // Kunci pencarian dan semua target dijadikan lowercase agar adil (Apple sama dengan apple)
    string keyLower = toLower(keyword);
    bool ketemu = false;

    cout << "\n--- HASIL PENCARIAN ---\n"; // Output terminal dibiarkan
    cout << left << setw(5) << "ID" << setw(25) << "NAMA PRODUK" << setw(15) << "HARGA" << "STOK\n";
    
    // Linear Search: Berjalan dari laci ke-0 sampai laci terakhir
    for (int i = 0; i < totalProduk; i++) {
        // find() mencari posisi kemunculan huruf. 
        // Jika tidak ketemu, C++ string akan membalikkan nilai string::npos (nilai khusus tanda tidak ketemu)
        // Jadi "!=" berarti: Jika hasilnya bukan 'tidak ketemu' (alias ADA)
        if (toLower(katalog[i].nama).find(keyLower) != string::npos) {
            cout << left << setw(5) << katalog[i].id 
                 << setw(25) << katalog[i].nama 
                 << "Rp " << setw(12) << katalog[i].harga 
                 << katalog[i].stok << endl;
            ketemu = true; // Naikkan bendera penanda
        }
    }

    if (!ketemu) cout << "Produk tidak ditemukan.\n";
}

void filterBerdasarkanKategori() { // Linear Search (Pencarian berurutan tapi khusus field Kategori)
    cout << "\nPilih Kategori:\n1. Elektronik\n2. Pakaian\n";
    int pil = inputIntValid("Pilih: ");
    string target = (pil == 1) ? "Elektronik" : "Pakaian"; // Mengubah angka menjadi teks target

    bool ketemu = false;
    cout << "\n--- KATEGORI: " << target << " ---\n";
    
    for (int i = 0; i < totalProduk; i++) {
        // Cek satu per satu apakah field 'kategori' nya cocok dengan teks 'target'
        if (katalog[i].kategori == target) {
            cout << "- " << katalog[i].nama << " (Rp" << katalog[i].harga << ")\n";
            ketemu = true;
        }
    }
    if (!ketemu) cout << "Kosong.\n";
}

void urutkanBerdasarkanHarga(bool ascending) { 
    // Algoritma: Selection Sort (Pengurutan dengan memilih nilai terekstrim)
    // Cara kerja Selection Sort: 
    // Cari laci dengan harga paling murah/mahal di antara semua laci, lalu Tukar posisinya dengan laci paling depan.
    // Lanjut cari lagi di sisa lacinya, lalu Tukar posisinya dengan laci kedua dari depan. Dan seterusnya.

    // Duplikasi Array sementara agar urutan array asli (Katalog Etalase) tidak ikut teracak permanen
    Produk temp[MAX_PRODUK];
    for (int i = 0; i < totalProduk; i++) temp[i] = katalog[i];

    // Mulai dari laci pertama sampai satu langkah sebelum terakhir
    for (int i = 0; i < totalProduk - 1; i++) {
        int idxEkstrim = i; // Anggap laci saat ini adalah pemegang rekor (terekstrim)
        
        // Cek laci sisanya di sebelah kanan untuk mencari penantang yang lebih ekstrim
        for (int j = i + 1; j < totalProduk; j++) {
            if (ascending) { // Jika mau Ascending (Termurah sampai Termahal)
                if (temp[j].harga < temp[idxEkstrim].harga) idxEkstrim = j;
            } else { // Jika mau Descending (Termahal sampai Termurah)
                if (temp[j].harga > temp[idxEkstrim].harga) idxEkstrim = j;
            }
        }
        
        // Tukar (Swap) posisi data antara laci saat ini dengan pemegang rekor baru
        Produk swapTemp = temp[i];        // Titipkan isi laci lama ke variabel sementara
        temp[i] = temp[idxEkstrim];       // Taruh si juara rekor ke laci lama
        temp[idxEkstrim] = swapTemp;      // Taruh yang dititipkan tadi ke bekas laci si juara
    }

    // Tampilkan hasil pengurutan dari array sementara (temp)
    cout << "\n--- URUTAN HARGA (" << (ascending ? "Termurah" : "Termahal") << ") ---\n";
    for (int i = 0; i < totalProduk; i++) {
        cout << "- " << temp[i].nama << " (Rp" << temp[i].harga << ")\n";
    }
}

void menuSorting() { // Tampilan Menu untuk Memilih Jenis Tampilan (Menu Adapter)
    if (totalProduk == 0) {
        cout << "\nBelum ada produk di etalase.\n";
        return;
    }
    cout << "\n--- OPSI TAMPILAN ---\n";
    cout << "1. Urutkan Harga Termurah\n";
    cout << "2. Urutkan Harga Termahal\n";
    cout << "3. Filter Kategori\n";
    cout << "4. Tampilkan Semua (Default)\n";
    
    // Minta user memasukkan angka (sudah diproteksi dari error infinity loop huruf)
    int pil = inputIntValid("Pilih (1-4): "); 

    if (pil == 1) {
        urutkanBerdasarkanHarga(true); // Memanggil Sorting Ascending
    } else if (pil == 2) {
        urutkanBerdasarkanHarga(false); // Memanggil Sorting Descending
    } else if (pil == 3) {
        filterBerdasarkanKategori(); // Memanggil Linear Search Khusus Kategori
    } else {
        tampilkanKatalogGlobal(); // Memanggil cetak array biasa
    }
}
