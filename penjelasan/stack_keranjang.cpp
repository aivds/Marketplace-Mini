#include "global.h" // Memanggil semua variabel dan struct dari global.h

// Penjelasan Konsep Stack (Tumpukan - LIFO: Last In First Out)
// Konsep keranjang ini mirip dengan menumpuk buku. Buku terakhir yang ditaruh di atas
// adalah buku pertama yang bisa diambil.
void tambahKeKeranjang() { 
    if (totalProduk == 0) { // Cek jika katalog masih kosong
        cout << "\nBelum ada produk di etalase yang bisa dibeli.\n"; // Beri pesan error
        return; // Hentikan fungsi
    }

    tampilkanKatalogGlobal(); // Tampilkan daftar barang yang bisa dibeli
    int cariID = inputIntValid("\nMasukkan ID Produk yang ingin dibeli: "); // Meminta ID produk dengan fungsi anti-error

    // Proses mencari produk di dalam array berdasarkan ID yang diinputkan
    int idxProduk = -1; // Set default -1 (tanda belum ketemu)
    for (int i = 0; i < totalProduk; i++) { // Looping sebanyak total produk yang ada
        if (katalog[i].id == cariID) { // Jika ID produk di array sama dengan ID inputan
            idxProduk = i; // Simpan indeks posisi produk tersebut
            break; // Berhenti mencari karena sudah ketemu
        }
    }

    if (idxProduk == -1) { // Jika setelah looping index masih -1 (berarti tidak ketemu)
        cout << "\n[Gagal] ID Produk tidak ditemukan!\n";
        return; // Batalkan proses
    }

    int jml = inputIntValid("Jumlah yang ingin dibeli: "); // Meminta jumlah beli

    if (jml <= 0) { // Validasi tidak boleh beli 0 atau minus
        cout << "\n[Gagal] Jumlah beli minimal 1.\n";
        return;
    }
    if (katalog[idxProduk].stok < jml) { // Validasi apakah stok toko cukup
        cout << "\n[Gagal] Stok tidak mencukupi (Sisa: " << katalog[idxProduk].stok << ").\n";
        return;
    }

    // Alokasi Memori Dinamis Untuk Node Stack (Push)
    NodeKeranjang* baru = new NodeKeranjang; // Memesan ruang di memori untuk 1 item keranjang
    
    // Menyalin data produk dari array Katalog ke dalam Node Keranjang
    baru->idProduk = katalog[idxProduk].id; 
    baru->namaProduk = katalog[idxProduk].nama;
    baru->harga = katalog[idxProduk].harga;
    baru->jumlah = jml; // Jumlah beli
    baru->pemilik = katalog[idxProduk].pemilik; // Menyimpan nama toko si penjual
    
    // Proses Push (Menumpuk node baru ke tumpukan paling atas):
    baru->next = topKeranjang; // Panah 'next' node baru menunjuk ke barang paling atas saat ini
    topKeranjang = baru; // Jadikan node baru ini sebagai barang yang Paling Atas (top)

    // Kurangi stok di katalog agar tidak dibeli orang lain secara bersamaan (booking)
    katalog[idxProduk].stok -= jml;

    cout << "\n[Sukses] '" << baru->namaProduk << "' (" << jml << " pcs) berhasil dimasukkan ke Keranjang!\n";
}

void popKeranjang() { // Fungsi Pop (Mengeluarkan data paling atas dari tumpukan)
    if (topKeranjang == NULL) { // Jika pointer top kosong, berarti keranjang tidak ada isinya
        cout << "\nKeranjang Anda masih kosong!\n";
        return;
    }

    NodeKeranjang* hapus = topKeranjang; // Buat pointer sementara menunjuk ke barang paling atas
    
    // Kembalikan stok ke katalog karena barang batal dibeli
    for (int i = 0; i < totalProduk; i++) { // Cari produk aslinya di etalase
        if (katalog[i].id == hapus->idProduk) { // Jika ID nya cocok
            katalog[i].stok += hapus->jumlah; // Tambahkan kembali jumlahnya ke etalase
            break;
        }
    }

    cout << "\n[Undo] '" << hapus->namaProduk << "' (" << hapus->jumlah << " pcs) dikeluarkan dari Keranjang.\n";
    
    // Proses Pop dari Stack:
    topKeranjang = topKeranjang->next; // Pindahkan gelar "Paling Atas" ke barang di bawahnya
    delete hapus; // Hancurkan barang yang paling atas tadi dari memori (mencegah memory leak)
}

void tampilkanKeranjang() {
    if (topKeranjang == NULL) { // Cek apakah stack kosong
        cout << "\nKeranjang Anda masih kosong!\n";
        return;
    }

    cout << "\n=== ISI KERANJANG BELANJA ===\n"; // Teks output dibiarkan dengan simbol
    NodeKeranjang* temp = topKeranjang; // Pointer pembaca dimulai dari tumpukan paling atas
    int totalBelanja = 0; // Variabel penyimpan total tagihan
    
    while (temp != NULL) { // Selama pointer belum mencapai dasar tumpukan (NULL)
        int subtotal = temp->harga * temp->jumlah; // Hitung subtotal per item
        cout << "- " << temp->namaProduk << " (" << temp->jumlah << " pcs) @ Rp" << temp->harga 
             << " | Subtotal: Rp" << subtotal << " [Toko: " << temp->pemilik << "]\n";
        totalBelanja += subtotal; // Tambahkan subtotal ke total tagihan
        temp = temp->next; // Geser pointer pembaca ke barang di bawahnya
    }
    cout << "---------------------------------\n"; // Teks output
    cout << "TOTAL BELANJA SEMENTARA: Rp" << totalBelanja << endl;
}

void clearKeranjang() { // Membersihkan seluruh stack sampai habis
    while (topKeranjang != NULL) { // Lakukan terus Pop sampai top = NULL
        NodeKeranjang* hapus = topKeranjang; // Pegang elemen paling atas
        topKeranjang = topKeranjang->next; // Turunkan posisi top
        delete hapus; // Hapus elemen
    }
}

void checkoutKeranjang() {
    if (topKeranjang == NULL) { // Tidak bisa checkout jika keranjang kosong
        cout << "\nKeranjang Anda kosong! Tidak ada yang bisa di-checkout.\n";
        return;
    }

    tampilkanKeranjang(); // Tampilkan tagihan sebelum bayar

    // Hitung ulang total untuk pembayaran
    int totalBelanja = 0;
    NodeKeranjang* temp = topKeranjang;
    while (temp != NULL) { // Looping menelusuri stack
        totalBelanja += (temp->harga * temp->jumlah);
        temp = temp->next;
    }

    int bayar = inputIntValid("\nMasukkan nominal pembayaran Anda: Rp"); // Input uang user

    if (bayar < totalBelanja) { // Jika uang tidak cukup
        cout << "\n[Gagal] Uang Anda kurang Rp" << (totalBelanja - bayar) << "! Checkout dibatalkan.\n";
        return; // Proses berhenti, barang tetap aman di keranjang
    }

    cout << "\n[Sukses] Pembayaran berhasil. Kembalian Anda: Rp" << (bayar - totalBelanja) << endl;

    // Proses Pemindahan dari Keranjang (Stack) ke Antrean (Queue)
    temp = topKeranjang; // Mulai dari barang teratas di keranjang
    while (temp != NULL) {
        string detail = temp->namaProduk + " (" + to_string(temp->jumlah) + " pcs)"; // Buat teks deskripsi
        int subtotal = temp->harga * temp->jumlah; 
        
        // Kirim pesanan ini ke fungsi Antrean milik toko/penjual masing-masing
        enqueuePesanan(currentUser, temp->pemilik, subtotal, detail); 
        
        temp = temp->next; // Lanjut ke barang berikutnya di keranjang
    }

    // Setelah semua dioper ke sistem antrean penjual, hancurkan keranjang
    clearKeranjang();
    
    cout << "Semua pesanan berhasil masuk ke antrean Penjual. Silakan pantau Riwayat Pembelian Anda.\n";
}
