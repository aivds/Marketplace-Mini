#include "global.h"

// Penjelasan Konsep CRUD (Create, Read, Update, Delete) Pada Array
// Array 'katalog' memiliki ukuran kaku (MAX_PRODUK = 1000).
// 'totalProduk' berfungsi sebagai penunjuk indeks batas akhir data yang valid.

void tambahProduk() { // CREATE (Menambah Data ke Array)
    if (totalProduk >= MAX_PRODUK) { // Validasi batas mentok array
        cout << "\nKatalog penuh!\n";
        return; // Tidak bisa tambah lagi
    }
    
    Produk baru; // Buat satu kotak kardus sementara bernama 'baru' dari cetakan struct Produk
    baru.id = productCounter++; // Beri nomor ID, lalu productCounter otomatis nambah 1
    
    cout << "\n--- TAMBAH PRODUK BARU ---\n"; // Output terminal
    cout << "Nama Produk : ";
    // getline digunakan karena nama produk bisa mengandung spasi (contoh: "Baju Koko")
    // (cin >> ws) dipakai untuk menyedot sisa 'Enter' atau spasi putih dari input sebelumnya
    getline(cin >> ws, baru.nama); 
    
    // Meminta harga dan stok dengan fungsi pelindung inputIntValid (agar tidak crash jika user iseng ketik huruf)
    baru.harga = inputIntValid("Harga (Rp)  : ");
    baru.stok = inputIntValid("Stok        : ");
    
    int pilKat = inputIntValid("Kategori (1. Elektronik, 2. Pakaian): ");
    // Jika pilKat = 1, isi dengan "Elektronik". Selain itu (ternary operator) isi dengan "Pakaian"
    baru.kategori = (pilKat == 1) ? "Elektronik" : "Pakaian";
    
    baru.pemilik = currentUser; // Otomatis menge-tag nama toko dari user yang saat ini sedang login
    
    // Memasukkan ke Array
    katalog[totalProduk] = baru; // Pindahkan kotak 'baru' ke dalam lemari array di laci ke-[totalProduk]
    totalProduk++; // Setelah dimasukkan, total produk otomatis bertambah 1

    cout << "\n[Sukses] Produk berhasil ditambahkan ke katalog!\n";
}

void tampilkanKatalogGlobal() { // READ GLOBAL (Menampilkan semua data untuk pembeli)
    if (totalProduk == 0) { // Jika array kosong
        cout << "\nBelum ada produk di etalase.\n";
        return;
    }

    // setw() digunakan untuk memberikan jarak spasi rapi (membuat tabel yang lurus di terminal)
    cout << "\n===============================================================================\n"; // Output terminal
    cout << left << setw(5) << "ID" << setw(25) << "NAMA PRODUK" << setw(15) << "HARGA" 
         << setw(10) << "STOK" << setw(15) << "KATEGORI" << "PENJUAL\n";
    cout << "===============================================================================\n";
    
    // Looping dari laci 0 sampai laci terakhir yang terisi (totalProduk dikurangi 1)
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

void tampilkanKatalogPenjual(string penjual) { // READ SPESIFIK (Hanya barang milik toko tertentu)
    bool ada = false; // Penanda ('bendera') untuk mengecek apakah tokonya punya barang atau tidak
    cout << "\n===============================================================================\n";
    cout << left << setw(5) << "ID" << setw(25) << "NAMA PRODUK" << setw(15) << "HARGA" 
         << setw(10) << "STOK" << setw(15) << "KATEGORI\n";
    cout << "===============================================================================\n";
    
    for (int i = 0; i < totalProduk; i++) {
        // Cek syarat: Jika barang ini milik si penjual, ATAU yang melihat ini adalah dewa (Admin)
        if (katalog[i].pemilik == penjual || currentRole == "ADMIN") { 
            cout << left << setw(5) << katalog[i].id 
                 << setw(25) << katalog[i].nama 
                 << "Rp " << setw(12) << katalog[i].harga 
                 << setw(10) << katalog[i].stok 
                 << setw(15) << katalog[i].kategori << endl;
            ada = true; // Naikkan bendera karena ada minimal 1 barang
        }
    }
    cout << "===============================================================================\n";
    if (!ada) cout << "Tidak ada produk dari toko Anda.\n"; // Jika bendera tidak naik
}

void editProduk() { // UPDATE (Mengubah isi array yang sudah ada)
    tampilkanKatalogPenjual(currentUser); // Tampilkan dulu biar user ingat ID nya
    if (totalProduk == 0) return;

    int cariID = inputIntValid("\nMasukkan ID Produk yang ingin diubah: ");

    // Linear Search: Mengecek satu persatu laci lemari dari laci 0 sampai ujung
    for (int i = 0; i < totalProduk; i++) {
        // Syarat ketemu: ID nya cocok, DAN (barangnya milik dia sendiri ATAU dia adalah Admin)
        if (katalog[i].id == cariID && (katalog[i].pemilik == currentUser || currentRole == "ADMIN")) {
            cout << "--- EDIT PRODUK [" << katalog[i].nama << "] ---\n";
            // Timpa harga lama dengan inputan harga baru (UPDATE)
            katalog[i].harga = inputIntValid("Harga Baru (Rp): ");
            // Update stok tidak ditimpa total, tapi ditambah dengan stok lama (RESTOCK)
            int tStok = inputIntValid("Stok Tambahan  : ");
            katalog[i].stok += tStok; 
            
            cout << "\n[Sukses] Data produk berhasil diperbarui!\n";
            return; // Selesai update, hentikan pencarian
        }
    }
    // Jika kode sampai ke titik ini, artinya looping dari laci 0 s/d akhir tidak menemukan syarat yang cocok
    cout << "\n[Gagal] Produk dengan ID " << cariID << " tidak ditemukan atau bukan milik Anda.\n";
}

void hapusProduk() { // DELETE (Menghapus laci di array secara logikal)
    tampilkanKatalogPenjual(currentUser);
    if (totalProduk == 0) return;

    int cariID = inputIntValid("\nMasukkan ID Produk yang ingin dihapus: ");

    for (int i = 0; i < totalProduk; i++) {
        if (katalog[i].id == cariID && (katalog[i].pemilik == currentUser || currentRole == "ADMIN")) {
            
            // Cara Menghapus Data Array (Shifting)
            // Karena array kaku (berbeda dengan Linked List yang bisa diputus-sambung dengan mudah),
            // cara menghapus laci ke-2 adalah dengan menimpa laci ke-2 dengan isi laci ke-3.
            // Lalu menimpa laci ke-3 dengan laci ke-4, dan seterusnya sampai ujung belakang.
            for (int j = i; j < totalProduk - 1; j++) {
                katalog[j] = katalog[j + 1]; // Laci sekarang ditimpa oleh laci sebelahnya
            }
            
            // Setelah semua laci bergeser ke kiri, total data dikurangi 1.
            // Secara teknis data paling ujung masih ada ampasnya di memori, tapi karena
            // totalProduk berkurang 1, ampas tersebut dianggap "tidak ada" (hilang logikal).
            totalProduk--; 
            
            cout << "\n[Sukses] Produk berhasil dihapus dari etalase!\n";
            return;
        }
    }
    cout << "\n[Gagal] Produk tidak ditemukan atau bukan milik Anda.\n";
}
