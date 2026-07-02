#include "global.h"

// Penjelasan Konsep Queue (Antrean - FIFO: First In First Out)
// Konsep ini sama persis dengan antrean di kasir supermarket.
// Siapa yang pertama kali datang (First In), maka dia yang pertama kali dilayani dan keluar (First Out).
// Kita butuh 2 pointer: frontQueue (menunjuk orang pertama di antrean) dan rearQueue (menunjuk orang terakhir).

void enqueuePesanan(string pembeli, string penjual, int total, string detail) { // Enqueue = Masuk Antrean
    // 1. Pesan tempat di memori untuk node antrean baru
    NodePesanan* baru = new NodePesanan; 
    
    // 2. Isi data pesanan ke dalam node baru tersebut
    baru->idPesanan = orderCounter++; // Mengambil ID dari penghitung global lalu menambah 1 (auto increment)
    baru->pembeli = pembeli;
    baru->penjual = penjual;
    baru->totalHarga = total;
    baru->detailPesanan = detail;
    baru->status = "Menunggu Diproses"; // Status awal
    baru->next = NULL; // Karena dia akan berada paling belakang, belakangnya pasti kosong (NULL)

    // 3. Proses penempatan di Queue
    if (frontQueue == NULL) { 
        // Jika antrean sedang kosong melompong (tidak ada orang sama sekali)
        frontQueue = baru; // Orang ini jadi yang paling depan
        rearQueue = baru;  // Orang ini sekaligus jadi yang paling belakang
    } else {
        // Jika antrean sudah ada orangnya
        rearQueue->next = baru; // Orang terakhir yang ada saat ini, menunjuk (next) ke orang baru ini
        rearQueue = baru;       // Gelar "Orang Terakhir" dipindahkan ke orang baru ini
    }
}

void tampilkanAntreanPesanan(string penjual, bool isAdmin) {
    if (frontQueue == NULL) { // Jika pointer depan kosong
        cout << "\nBelum ada pesanan masuk sama sekali.\n";
        return;
    }

    cout << "\n=== ANTREAN PESANAN MASUK ===\n"; // Output terminal dibiarkan
    NodePesanan* temp = frontQueue; // Mulai mengecek antrean dari orang paling depan
    bool ada = false; // Penanda apakah ada pesanan untuk penjual tertentu

    while (temp != NULL) { // Berjalan menelusuri antrean dari depan ke belakang
        // Tampilkan hanya jika pesanan ini milik toko si penjual, ATAU yang melihat adalah Admin (bisa lihat semua)
        if (temp->penjual == penjual || isAdmin) {
            cout << "ID Pesanan : " << temp->idPesanan << endl;
            cout << "Pembeli    : " << temp->pembeli << endl;
            if (isAdmin) cout << "Toko (Pj)  : " << temp->penjual << endl;
            cout << "Detail     : " << temp->detailPesanan << endl;
            cout << "Total      : Rp" << temp->totalHarga << endl;
            cout << "Status     : " << temp->status << endl;
            cout << "---------------------------------\n"; // Output terminal
            ada = true; // Tandai bahwa ditemukan minimal 1 pesanan
        }
        temp = temp->next; // Geser ke orang berikutnya di antrean
    }

    if (!ada) {
        cout << "Tidak ada pesanan masuk untuk toko Anda.\n";
    }
}

void dequeuePesanan(string penjual, bool isAdmin) { // Dequeue = Memproses dan Mengeluarkan dari antrean
    if (frontQueue == NULL) {
        cout << "\nAntrean pesanan kosong.\n";
        return;
    }

    // Karena di aplikasi ini 1 antrean global (frontQueue) menampung pesanan untuk banyak penjual secara acak,
    // maka Penjual A hanya boleh memproses pesanan miliknya sendiri. 
    // Jadi pencabutan antrean bisa terjadi dari tengah antrean (bukan mutlak dari depan saja).
    
    NodePesanan* temp = frontQueue; // Pointer untuk mencari node yang akan diproses
    NodePesanan* prev = NULL; // Pointer yang selalu mengikuti tepat 1 langkah di belakang 'temp'
    
    // Pencarian pesanan: Berjalan selama 'temp' tidak NULL, bukan admin, dan belum menemukan pesanan tokonya
    while (temp != NULL && !isAdmin && temp->penjual != penjual) {
        prev = temp; // 'prev' maju ke posisi 'temp'
        temp = temp->next; // 'temp' maju 1 langkah ke depan
    }

    if (temp == NULL) { // Jika jalan sampai ujung (NULL) dan tidak ketemu
        cout << "\nTidak ada pesanan masuk untuk toko Anda di antrean.\n";
        return;
    }

    // Proses Pencabutan (Dequeue) Node
    if (prev == NULL) {
        // Jika prev masih NULL, artinya pesanan yang cocok langsung ketemu di urutan pertama (paling depan)
        frontQueue = frontQueue->next; // Pindahkan kepala antrean ke orang ke-2
        if (frontQueue == NULL) rearQueue = NULL; // Jika orang ke-2 ternyata kosong, berarti antrean habis total
    } else {
        // Jika prev tidak NULL, artinya pesanan ada di tengah atau belakang antrean
        prev->next = temp->next; // Tali 'next' dari orang depan dilompatkan melewati 'temp', langsung nyambung ke orang belakangnya
        if (temp == rearQueue) rearQueue = prev; // Jika yang dicabut ternyata orang paling belakang, maka orang di depannya menjadi rear baru
    }

    // Pindahkan catatan pesanan yang sudah diproses ini ke dalam Riwayat (Linked List)
    tambahRiwayat(temp->idPesanan, temp->pembeli, temp->penjual, temp->totalHarga, temp->detailPesanan, "Dikirim");
    
    cout << "\n[Sukses] Pesanan ID " << temp->idPesanan << " telah diproses dan status berubah menjadi 'Dikirim'.\n";
    
    // Hancurkan node pesanan dari antrean agar tidak menuhi memori
    delete temp;
}
