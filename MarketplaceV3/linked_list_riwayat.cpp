#include "global.h"

void tambahRiwayat(int idPesanan, string pembeli, string penjual, int total, string detail, string status) {
    NodeRiwayat* baru = new NodeRiwayat;
    baru->idPesanan = idPesanan;
    baru->pembeli = pembeli;
    baru->penjual = penjual;
    baru->totalHarga = total;
    baru->detailPesanan = detail;
    baru->status = status;
    baru->next = NULL;

    if (headRiwayat == NULL) {
        headRiwayat = tailRiwayat = baru;
    } else {
        tailRiwayat->next = baru;
        tailRiwayat = baru;
    }
}

void tampilkanRiwayatGlobal() {
    if (headRiwayat == NULL) {
        cout << "\nBelum ada riwayat transaksi di sistem.\n";
        return;
    }

    cout << "\n=== SEMUA RIWAYAT TRANSAKSI (ADMIN) ===\n";
    NodeRiwayat* temp = headRiwayat;
    while (temp != NULL) {
        cout << "ID: " << temp->idPesanan 
             << " | Pembeli: " << temp->pembeli 
             << " | Toko: " << temp->penjual
             << " | Total: Rp" << temp->totalHarga 
             << " | Status: " << temp->status 
             << "\n  Detail: " << temp->detailPesanan << "\n----------------------------------------\n";
        temp = temp->next;
    }
}

void tampilkanRiwayatPembeli(string pembeli) {
    if (headRiwayat == NULL) {
        cout << "\nAnda belum memiliki riwayat transaksi.\n";
        return;
    }

    cout << "\n=== RIWAYAT PEMBELIAN ANDA ===\n";
    NodeRiwayat* temp = headRiwayat;
    bool ada = false;
    while (temp != NULL) {
        if (temp->pembeli == pembeli) {
            cout << "ID: " << temp->idPesanan 
                 << " | Toko: " << temp->penjual
                 << " | Total: Rp" << temp->totalHarga 
                 << " | Status: " << temp->status 
                 << "\n  Detail: " << temp->detailPesanan << "\n----------------------------------------\n";
            ada = true;
        }
        temp = temp->next;
    }
    
    if (!ada) cout << "Tidak ada riwayat untuk akun ini.\n";
}

void konfirmasiPenerimaan() {
    tampilkanRiwayatPembeli(currentUser);
    if (headRiwayat == NULL) return;

    int cariID;
    cout << "\nMasukkan ID Pesanan yang sudah Anda terima (Status harus 'Dikirim'): ";
    cin >> cariID;

    NodeRiwayat* temp = headRiwayat;
    while (temp != NULL) {
        if (temp->idPesanan == cariID && temp->pembeli == currentUser) {
            if (temp->status == "Dikirim") {
                temp->status = "Selesai";
                cout << "\n[Sukses] Terima kasih! Pesanan ID " << cariID << " telah selesai.\n";
            } else {
                cout << "\n[Gagal] Pesanan tersebut belum dikirim atau sudah selesai.\n";
            }
            return;
        }
        temp = temp->next;
    }
    cout << "\n[Gagal] ID Pesanan tidak ditemukan atau bukan milik Anda.\n";
}

void cetakNota() {
    if (headRiwayat == NULL) {
        cout << "\nBelum ada transaksi untuk dicetak.\n";
        return;
    }

    NodeRiwayat* temp = headRiwayat;
    NodeRiwayat* terakhir = NULL;

    // Cari transaksi terakhir milik user
    while (temp != NULL) {
        if (temp->pembeli == currentUser) {
            terakhir = temp;
        }
        temp = temp->next;
    }

    if (terakhir == NULL) {
        cout << "\nAnda belum melakukan transaksi apapun.\n";
        return;
    }

    cout << "\n=======================================\n";
    cout << "         NOTA PEMBELIAN (COPY)         \n";
    cout << "=======================================\n";
    cout << "ID Pesanan : " << terakhir->idPesanan << endl;
    cout << "Pembeli    : " << terakhir->pembeli << endl;
    cout << "Penjual    : " << terakhir->penjual << endl;
    cout << "Barang     : " << terakhir->detailPesanan << endl;
    cout << "Total Bayar: Rp" << terakhir->totalHarga << endl;
    cout << "Status     : " << terakhir->status << endl;
    cout << "=======================================\n";
    cout << " Terima kasih telah berbelanja!\n";
}

void tampilkanStatistik() {
    int totalSukses = 0;
    int omzet = 0;

    NodeRiwayat* temp = headRiwayat;
    while (temp != NULL) {
        totalSukses++;
        omzet += temp->totalHarga;
        temp = temp->next;
    }

    cout << "\n=======================================\n";
    cout << "   DASHBOARD STATISTIK MARKETPLACE     \n";
    cout << "=======================================\n";
    cout << "Total Pengguna Terdaftar : " << totalAkun << " Akun\n";
    cout << "Total Produk di Etalase  : " << totalProduk << " Jenis Barang\n";
    cout << "Total Pesanan Dibuat     : " << (orderCounter - 1) << " Pesanan\n";
    cout << "---------------------------------------\n";
    cout << "Total Transaksi Diproses : " << totalSukses << " Transaksi\n";
    cout << "Total Perputaran Uang    : Rp" << omzet << "\n";
    cout << "=======================================\n";
}
