#include "global.h"

void enqueuePesanan(string pembeli, string penjual, int total, string detail) {
    NodePesanan* baru = new NodePesanan;
    baru->idPesanan = orderCounter++;
    baru->pembeli = pembeli;
    baru->penjual = penjual;
    baru->totalHarga = total;
    baru->detailPesanan = detail;
    baru->status = "Menunggu Diproses";
    baru->next = NULL;

    if (rearQueue == NULL) {
        frontQueue = rearQueue = baru;
    } else {
        rearQueue->next = baru;
        rearQueue = baru;
    }
}

void tampilkanAntreanPesanan(string namaPenjual, bool isAdmin) {
    if (frontQueue == NULL) {
        cout << "\nAntrean pesanan kosong.\n";
        return;
    }

    cout << "\n=== DAFTAR ANTREAN PESANAN MASUK ===\n";
    NodePesanan* temp = frontQueue;
    bool ada = false;

    while (temp != NULL) {
        if (temp->penjual == namaPenjual || isAdmin) {
            cout << "ID Pesanan : " << temp->idPesanan << endl;
            cout << "Pembeli    : " << temp->pembeli << endl;
            cout << "Toko Tujuan: " << temp->penjual << endl;
            cout << "Detail     : " << temp->detailPesanan << endl;
            cout << "Total Bayar: Rp" << temp->totalHarga << endl;
            cout << "Status     : " << temp->status << endl;
            cout << "--------------------------------------\n";
            ada = true;
        }
        temp = temp->next;
    }

    if (!ada) {
        cout << "Tidak ada pesanan masuk untuk Anda.\n";
    }
}

void dequeuePesanan(string namaPenjual, bool isAdmin) {
    if (frontQueue == NULL) {
        cout << "\nAntrean pesanan kosong.\n";
        return;
    }

    // Mencari pesanan pertama yang sesuai dengan penjual (atau bebas jika admin)
    NodePesanan* temp = frontQueue;
    NodePesanan* prev = NULL;
    
    while (temp != NULL && !isAdmin && temp->penjual != namaPenjual) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        cout << "\nTidak ada pesanan masuk untuk toko Anda di antrean.\n";
        return;
    }

    // Eksekusi Dequeue
    if (prev == NULL) {
        frontQueue = frontQueue->next;
        if (frontQueue == NULL) rearQueue = NULL;
    } else {
        prev->next = temp->next;
        if (temp->next == NULL) rearQueue = prev;
    }

    // Ubah status dan pindahkan ke Riwayat (Linked List)
    tambahRiwayat(temp->idPesanan, temp->pembeli, temp->penjual, temp->totalHarga, temp->detailPesanan, "Dikirim");

    cout << "\n[Sukses] Pesanan ID " << temp->idPesanan << " dari " << temp->pembeli 
         << " berhasil diproses dan dikirim!\n";

    delete temp;
}
