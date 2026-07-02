#include "global.h"

// Penjelasan Konsep File Handling (Baca dan Tulis ke Penyimpanan Fisik)
// Supaya data tidak hilang ketika komputer dimatikan atau aplikasi ditutup, memori sementara 
// dari Array (Akun, Katalog) dan Linked List (Riwayat) disedot dan dipaksa tulis ke 
// sebuah file teks sungguhan berformat CSV (Comma Separated Values) di Harddisk komputer.

void simpanSemuaData() {
    // Bagian 1: Menyimpan Array Akun ke CSV
    // ofstream (Output File Stream): Membuka saluran keluar menuju harddisk.
    // Jika file "akun.csv" tidak ada, C++ akan membuatkannya. Jika ada, akan ditimpa total dari nol.
    ofstream fileAkun("akun.csv"); 
    for (int i = 0; i < totalAkun; i++) {
        // Tulis (<<) data laci-1 ke file. Pemisahnya dipisahkan dengan tanda koma "," lalu diakhiri enter "endl".
        fileAkun << daftarAkun[i].username << "," << daftarAkun[i].password << "," << daftarAkun[i].role << endl;
    }
    fileAkun.close(); // Matikan saluran agar memori RAM tidak bocor

    // Bagian 2: Menyimpan Array Katalog ke CSV
    ofstream fileKatalog("katalog.csv");
    for (int i = 0; i < totalProduk; i++) {
        fileKatalog << katalog[i].id << "," << katalog[i].nama << "," 
                    << katalog[i].harga << "," << katalog[i].stok << "," 
                    << katalog[i].kategori << "," << katalog[i].pemilik << endl;
    }
    fileKatalog.close();

    // Bagian 3: Menyimpan Linked List Riwayat ke CSV
    ofstream fileRiwayat("riwayat.csv");
    NodeRiwayat* temp = headRiwayat; // Mulai dari gerbong lokomotif
    while (temp != NULL) { // Telusuri bergeser sampai ujung kereta
        // Perhatikan: Karena "DetailPesanan" bentuknya kalimat (bisa mengandung spasi panjang dan koma barang),
        // maka pemisah kolomnya MENGGUNAKAN SIMBOL PIPA LURUS "|", bukan koma, supaya formatnya tidak hancur saat dibaca nanti.
        fileRiwayat << temp->idPesanan << "|" << temp->pembeli << "|" 
                    << temp->penjual << "|" << temp->totalHarga << "|" 
                    << temp->detailPesanan << "|" << temp->status << endl;
        temp = temp->next;
    }
    fileRiwayat.close();
}

void muatSemuaData() { // Memuat (Load) data dari Harddisk kembali masuk ke RAM komputer
    string baris, item;

    // Bagian 1: Memuat Akun
    // ifstream (Input File Stream): Membuka saluran masuk dari harddisk untuk disedot.
    ifstream fileAkun("akun.csv"); 
    if (fileAkun.is_open()) { // Jika filenya terdeteksi ADA
        totalAkun = 0; // Reset isi array akun jadi nol
        // getline() membaca 1 baris utuh dari file CSV.
        while (getline(fileAkun, baris)) { 
            stringstream ss(baris); // stringstream: Alat pembedah baris teks. Seperti pisau daging.
            
            // Alat pembedah memotong teks setiap ketemu tanda koma ',' lalu potongan itu ditangkap oleh 'item'.
            getline(ss, item, ','); daftarAkun[totalAkun].username = item; 
            getline(ss, item, ','); daftarAkun[totalAkun].password = item;
            getline(ss, item, ','); daftarAkun[totalAkun].role = item;
            
            totalAkun++; // Angka pencatat akun naik 1
        }
        fileAkun.close();
    } else {
        // Jika file csv akun tidak ada (baru pertama kali run program), buat paksa 3 akun dummy
        daftarAkun[0] = {"admin", "admin", "ADMIN"};
        daftarAkun[1] = {"tokoA", "123", "PENJUAL"};
        daftarAkun[2] = {"budi", "123", "PEMBELI"};
        totalAkun = 3;
    }

    // Bagian 2: Memuat Katalog
    ifstream fileKatalog("katalog.csv");
    if (fileKatalog.is_open()) {
        totalProduk = 0;
        while (getline(fileKatalog, baris)) {
            stringstream ss(baris);
            getline(ss, item, ','); katalog[totalProduk].id = stoi(item); // stoi = "String TO Integer" (Konversi teks ke angka)
            getline(ss, item, ','); katalog[totalProduk].nama = item;
            getline(ss, item, ','); katalog[totalProduk].harga = stoi(item); // Konversi ke angka
            getline(ss, item, ','); katalog[totalProduk].stok = stoi(item);  // Konversi ke angka
            getline(ss, item, ','); katalog[totalProduk].kategori = item;
            getline(ss, item, ','); katalog[totalProduk].pemilik = item;
            totalProduk++;
            
            // Mekanisme keamanan: Angka productCounter utama harus disesuaikan dengan ID terbesar 
            // agar saat menambah barang baru tidak ada ID yang kembar atau berulang.
            if (katalog[totalProduk-1].id >= productCounter) {
                productCounter = katalog[totalProduk-1].id + 1;
            }
        }
        fileKatalog.close();
    }

    // Bagian 3: Memuat Riwayat (Re-Create Linked List)
    ifstream fileRiwayat("riwayat.csv");
    if (fileRiwayat.is_open()) {
        headRiwayat = NULL; // Hancurkan kereta lama, mulai dari kosong
        tailRiwayat = NULL;
        while (getline(fileRiwayat, baris)) {
            stringstream ss(baris);
            // Pisau bedah (ss) disetting memotong setiap kali ketemu simbol "|", BUKAN koma ","
            string idStr, pembeli, penjual, totalStr, detail, status;
            getline(ss, idStr, '|');
            getline(ss, pembeli, '|');
            getline(ss, penjual, '|');
            getline(ss, totalStr, '|');
            getline(ss, detail, '|');
            getline(ss, status, '|');

            // Membangun ulang kembali (merakit) gerbong-gerbong Linked List dari puing-puing teks CSV
            tambahRiwayat(stoi(idStr), pembeli, penjual, stoi(totalStr), detail, status);
            
            // Jaga keamanan counter pesanan agar penomoran berikutnya unik (teruskan dari nomor tertinggi terakhir)
            if (stoi(idStr) >= orderCounter) {
                orderCounter = stoi(idStr) + 1;
            }
        }
        fileRiwayat.close();
    }
}
