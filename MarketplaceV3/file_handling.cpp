#include "global.h"

// Variabel Global Inisialisasi
Produk katalog[MAX_PRODUK];
int totalProduk = 0;

Akun daftarAkun[MAX_AKUN];
int totalAkun = 0;

string currentUser = "";
string currentRole = "";
int orderCounter = 1;
int productCounter = 1;

// Inisialisasi Pointer
NodeKeranjang* topKeranjang = NULL;
NodePesanan* frontQueue = NULL;
NodePesanan* rearQueue = NULL;
NodeRiwayat* headRiwayat = NULL;
NodeRiwayat* tailRiwayat = NULL;

void simpanSemuaData() {
    // simpan akun
    ofstream fileAkun("akun.csv");
    for (int i = 0; i < totalAkun; i++) {
        fileAkun << daftarAkun[i].username << "," << daftarAkun[i].password << "," << daftarAkun[i].role << endl;
    }
    fileAkun.close();

    // simpan katalog
    ofstream fileKatalog("katalog.csv");
    for (int i = 0; i < totalProduk; i++) {
        fileKatalog << katalog[i].id << "," << katalog[i].nama << "," 
                    << katalog[i].harga << "," << katalog[i].stok << ","
                    << katalog[i].kategori << "," << katalog[i].pemilik << endl;
    }
    fileKatalog.close();

    // simpan riwayat
    ofstream fileRiwayat("riwayat.csv");
    NodeRiwayat* temp = headRiwayat;
    while (temp != NULL) {
        fileRiwayat << temp->idPesanan << "|" << temp->pembeli << "|" 
                    << temp->penjual << "|" << temp->totalHarga << "|"
                    << temp->detailPesanan << "|" << temp->status << endl;
        temp = temp->next;
    }
    fileRiwayat.close();
}

void muatSemuaData() {
    string baris, item;

    // muat akun
    ifstream fileAkun("akun.csv");
    if (fileAkun.is_open()) {
        totalAkun = 0;
        while (getline(fileAkun, baris) && totalAkun < MAX_AKUN) {
            stringstream ss(baris);
            getline(ss, daftarAkun[totalAkun].username, ',');
            getline(ss, daftarAkun[totalAkun].password, ',');
            getline(ss, daftarAkun[totalAkun].role, ',');
            totalAkun++;
        }
        fileAkun.close();
    } else {
        // Akun default jika file tidak ada
        daftarAkun[0] = {"admin", "admin", "ADMIN"};
        daftarAkun[1] = {"penjual1", "123", "PENJUAL"};
        daftarAkun[2] = {"user1", "123", "PEMBELI"};
        totalAkun = 3;
    }

    // muat katalog
    ifstream fileKatalog("katalog.csv");
    if (fileKatalog.is_open()) {
        totalProduk = 0;
        int maxId = 0;
        while (getline(fileKatalog, baris) && totalProduk < MAX_PRODUK) {
            stringstream ss(baris);
            string temp;
            getline(ss, temp, ','); katalog[totalProduk].id = stoi(temp);
            if (katalog[totalProduk].id > maxId) maxId = katalog[totalProduk].id;
            getline(ss, katalog[totalProduk].nama, ',');
            getline(ss, temp, ','); katalog[totalProduk].harga = stoi(temp);
            getline(ss, temp, ','); katalog[totalProduk].stok = stoi(temp);
            getline(ss, katalog[totalProduk].kategori, ',');
            getline(ss, katalog[totalProduk].pemilik, ',');
            totalProduk++;
        }
        productCounter = maxId + 1;
        fileKatalog.close();
    }

    // muat riwayat list
    ifstream fileRiwayat("riwayat.csv");
    if (fileRiwayat.is_open()) {
        headRiwayat = NULL;
        tailRiwayat = NULL;
        int maxId = 0;
        while (getline(fileRiwayat, baris)) {
            stringstream ss(baris);
            string temp;
            NodeRiwayat* baru = new NodeRiwayat;
            
            getline(ss, temp, '|'); baru->idPesanan = stoi(temp);
            if (baru->idPesanan > maxId) maxId = baru->idPesanan;
            getline(ss, baru->pembeli, '|');
            getline(ss, baru->penjual, '|');
            getline(ss, temp, '|'); baru->totalHarga = stoi(temp);
            getline(ss, baru->detailPesanan, '|');
            getline(ss, baru->status, '|');
            baru->next = NULL;

            if (headRiwayat == NULL) {
                headRiwayat = baru;
                tailRiwayat = baru;
            } else {
                tailRiwayat->next = baru;
                tailRiwayat = baru;
            }
        }
        orderCounter = maxId + 1;
        fileRiwayat.close();
    }
}
