#include "global.h"

void tambahKeKeranjang() {
    if (totalProduk == 0) {
        cout << "\nBelum ada produk di etalase yang bisa dibeli.\n";
        return;
    }

    tampilkanKatalogGlobal();
    int cariID, jml;
    cout << "\nMasukkan ID Produk yang ingin dibeli: ";
    cin >> cariID;

    // Cari produk di array
    int idxProduk = -1;
    for (int i = 0; i < totalProduk; i++) {
        if (katalog[i].id == cariID) {
            idxProduk = i;
            break;
        }
    }

    if (idxProduk == -1) {
        cout << "\n[Gagal] ID Produk tidak ditemukan!\n";
        return;
    }

    cout << "Jumlah yang ingin dibeli: ";
    cin >> jml;

    if (jml <= 0) {
        cout << "\n[Gagal] Jumlah beli minimal 1.\n";
        return;
    }
    if (katalog[idxProduk].stok < jml) {
        cout << "\n[Gagal] Stok tidak mencukupi (Sisa: " << katalog[idxProduk].stok << ").\n";
        return;
    }

    // Alokasi Node Stack Baru
    NodeKeranjang* baru = new NodeKeranjang;
    baru->idProduk = katalog[idxProduk].id;
    baru->namaProduk = katalog[idxProduk].nama;
    baru->harga = katalog[idxProduk].harga;
    baru->jumlah = jml;
    baru->pemilik = katalog[idxProduk].pemilik; // Pemilik toko
    
    // Push ke Stack
    baru->next = topKeranjang;
    topKeranjang = baru;

    // Kurangi stok sementara (agar tidak over-booking)
    katalog[idxProduk].stok -= jml;

    cout << "\n[Sukses] '" << baru->namaProduk << "' (" << jml << " pcs) berhasil dimasukkan ke Keranjang!\n";
}

void popKeranjang() {
    if (topKeranjang == NULL) {
        cout << "\nKeranjang Anda masih kosong!\n";
        return;
    }

    NodeKeranjang* hapus = topKeranjang;
    
    // Kembalikan stok ke katalog karena batal dibeli
    for (int i = 0; i < totalProduk; i++) {
        if (katalog[i].id == hapus->idProduk) {
            katalog[i].stok += hapus->jumlah;
            break;
        }
    }

    cout << "\n[Undo] '" << hapus->namaProduk << "' (" << hapus->jumlah << " pcs) dikeluarkan dari Keranjang.\n";
    
    topKeranjang = topKeranjang->next;
    delete hapus;
}

void tampilkanKeranjang() {
    if (topKeranjang == NULL) {
        cout << "\nKeranjang Anda masih kosong!\n";
        return;
    }

    cout << "\n=== ISI KERANJANG BELANJA ===\n";
    NodeKeranjang* temp = topKeranjang;
    int totalBelanja = 0;
    while (temp != NULL) {
        int subtotal = temp->harga * temp->jumlah;
        cout << "- " << temp->namaProduk << " (" << temp->jumlah << " pcs) @ Rp" << temp->harga 
             << " | Subtotal: Rp" << subtotal << " [Toko: " << temp->pemilik << "]\n";
        totalBelanja += subtotal;
        temp = temp->next;
    }
    cout << "---------------------------------\n";
    cout << "TOTAL BELANJA SEMENTARA: Rp" << totalBelanja << endl;
}

void clearKeranjang() {
    while (topKeranjang != NULL) {
        NodeKeranjang* hapus = topKeranjang;
        topKeranjang = topKeranjang->next;
        delete hapus;
    }
}

void checkoutKeranjang() {
    if (topKeranjang == NULL) {
        cout << "\nKeranjang Anda kosong! Tidak ada yang bisa di-checkout.\n";
        return;
    }

    tampilkanKeranjang();

    // Hitung ulang total untuk pembayaran
    int totalBelanja = 0;
    NodeKeranjang* temp = topKeranjang;
    while (temp != NULL) {
        totalBelanja += (temp->harga * temp->jumlah);
        temp = temp->next;
    }

    int bayar;
    cout << "\nMasukkan nominal pembayaran Anda: Rp";
    cin >> bayar;

    if (bayar < totalBelanja) {
        cout << "\n[Gagal] Uang Anda kurang Rp" << (totalBelanja - bayar) << "! Checkout dibatalkan.\n";
        return;
    }

    cout << "\n[Sukses] Pembayaran berhasil. Kembalian Anda: Rp" << (bayar - totalBelanja) << endl;

    // Pindahkan isi keranjang ke Queue Pesanan (Setiap item jadi 1 node queue)
    temp = topKeranjang;
    while (temp != NULL) {
        string detail = temp->namaProduk + " (" + to_string(temp->jumlah) + " pcs)";
        int subtotal = temp->harga * temp->jumlah;
        enqueuePesanan(currentUser, temp->pemilik, subtotal, detail);
        temp = temp->next;
    }

    // Kosongkan keranjang
    clearKeranjang();
    
    cout << "Semua pesanan berhasil masuk ke antrean Penjual. Silakan pantau Riwayat Pembelian Anda.\n";
}
