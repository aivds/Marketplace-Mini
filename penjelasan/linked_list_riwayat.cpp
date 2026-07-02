#include "global.h"

// Penjelasan Konsep Linked List (Riwayat Transaksi)
// Linked List adalah seperti gerbong kereta api. Setiap node saling terkait menggunakan tali 'next'.
// Berbeda dengan Array yang ukurannya kaku, Linked List sangat dinamis, bisa nambah dan kurang kapan saja tanpa batas.
// Kita menggunakan pointer head (awal gerbong) dan tail (akhir gerbong).

void tambahRiwayat(int idPesanan, string pembeli, string penjual, int total, string detail, string status) {
    // 1. Pesan 1 gerbong memori baru
    NodeRiwayat* baru = new NodeRiwayat; 
    
    // 2. Isi muatan (data) gerbong tersebut
    baru->idPesanan = idPesanan;
    baru->pembeli = pembeli;
    baru->penjual = penjual;
    baru->totalHarga = total;
    baru->detailPesanan = detail;
    baru->status = status; 
    baru->next = NULL; // Karena dia gerbong terakhir, tali ke belakangnya kosong

    // 3. Proses menyambungkan gerbong ke kereta utama (Menambah di akhir / Insert Last)
    if (headRiwayat == NULL) { // Jika keretanya belum ada lokomotifnya sama sekali
        headRiwayat = baru; // Gerbong ini jadi awal (head)
        tailRiwayat = baru; // Gerbong ini sekaligus jadi akhir (tail)
    } else { // Jika sudah ada gerbong lain
        tailRiwayat->next = baru; // Tali belakang dari gerbong terakhir saat ini dikaitkan ke gerbong baru
        tailRiwayat = baru; // Gerbong baru ini resmi menjadi gerbong akhir yang baru (tail)
    }
}

void tampilkanRiwayatGlobal() {
    if (headRiwayat == NULL) { // Cek apakah kereta kosong
        cout << "\nBelum ada riwayat transaksi sama sekali.\n";
        return;
    }

    cout << "\n=== SEMUA RIWAYAT TRANSAKSI GLOBAL ===\n"; // Output terminal
    NodeRiwayat* temp = headRiwayat; // Mulai berjalan dari gerbong pertama (head)
    
    while (temp != NULL) { // Berjalan menelusuri gerbong satu per satu sampai gerbong terakhir
        cout << "ID Pesanan : " << temp->idPesanan << endl;
        cout << "Pembeli    : " << temp->pembeli << endl;
        cout << "Toko       : " << temp->penjual << endl;
        cout << "Detail     : " << temp->detailPesanan << endl;
        cout << "Total      : Rp" << temp->totalHarga << endl;
        cout << "Status     : " << temp->status << endl;
        cout << "---------------------------------\n";
        temp = temp->next; // Lompat ke gerbong selanjutnya
    }
}

void tampilkanRiwayatPembeli(string pembeli) {
    if (headRiwayat == NULL) { // Cek apakah riwayat kosong
        cout << "\nRiwayat belanja Anda masih kosong.\n";
        return;
    }

    cout << "\n=== RIWAYAT TRANSAKSI ANDA ===\n";
    NodeRiwayat* temp = headRiwayat; 
    bool ada = false;

    // Linear Search di dalam Linked List: menelusuri dari awal sampai akhir
    while (temp != NULL) {
        if (temp->pembeli == pembeli) { // Hanya cetak jika nama pembelinya cocok
            cout << "ID Pesanan : " << temp->idPesanan << endl;
            cout << "Toko       : " << temp->penjual << endl;
            cout << "Detail     : " << temp->detailPesanan << endl;
            cout << "Total      : Rp" << temp->totalHarga << endl;
            cout << "Status     : " << temp->status << endl;
            cout << "---------------------------------\n";
            ada = true;
        }
        temp = temp->next;
    }

    if (!ada) cout << "Anda belum pernah melakukan transaksi.\n";
}

void konfirmasiPenerimaan() {
    tampilkanRiwayatPembeli(currentUser); // Tampilkan dulu riwayatnya
    if (headRiwayat == NULL) return; // Jika kosong batal

    // Meminta user menginput ID pesanan mana yang sudah sampai di rumah
    int cariID = inputIntValid("\nMasukkan ID Pesanan yang sudah Anda terima (Status harus 'Dikirim'): ");

    NodeRiwayat* temp = headRiwayat; // Mulai dari awal list
    while (temp != NULL) {
        // Cek 3 hal: ID-nya cocok? Milik user ini? Statusnya sedang dikirim?
        if (temp->idPesanan == cariID && temp->pembeli == currentUser && temp->status == "Dikirim") {
            temp->status = "Selesai"; // Ubah statusnya (Update Data di Linked List)
            cout << "\n[Sukses] Terima kasih telah mengkonfirmasi penerimaan barang!\n";
            cetakNota(); // Panggil fungsi cetak struk TXT
            return;
        }
        temp = temp->next;
    }
    cout << "\n[Gagal] ID Pesanan tidak ditemukan atau status belum dikirim.\n";
}
