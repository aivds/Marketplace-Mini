#include "global.h"

void clearScreen() {
    system("cls"); // Untuk clear terminal
}

void pauseScreen() {
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.ignore(10000, '\n');
    cin.get();
}

int inputIntValid(string prompt) {
    int val;
    while (true) {
        cout << prompt;
        cin >> val;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "[Error] Masukkan angka yang valid!\n";
        } else {
            return val;
        }
    }
}

// sistem autentikasi
void tampilkanDaftarUser() {
    cout << "\n=== DAFTAR USER TERDAFTAR ===\n";
    cout << left << setw(15) << "USERNAME" << setw(15) << "ROLE" << endl;
    cout << "---------------------------------\n";
    for (int i = 0; i < totalAkun; i++) {
        cout << left << setw(15) << daftarAkun[i].username << setw(15) << daftarAkun[i].role << endl;
    }
    cout << "---------------------------------\n";
}

void hapusAkun() {
    tampilkanDaftarUser();
    string target;
    cout << "\nMasukkan username yang ingin dihapus: ";
    cin >> target;

    if (toLower(target) == "admin") {
        cout << "\n[Gagal] Akun Super Admin tidak boleh dihapus!\n";
        return;
    }

    for (int i = 0; i < totalAkun; i++) {
        if (daftarAkun[i].username == target) {
            for (int j = i; j < totalAkun - 1; j++) {
                daftarAkun[j] = daftarAkun[j + 1];
            }
            totalAkun--;
            cout << "\n[Sukses] Akun '" << target << "' berhasil dihapus!\n";
            return;
        }
    }
    cout << "\n[Gagal] Username tidak ditemukan.\n";
}

bool loginProcess() {
    string user, pass;
    cout << "\n=== LOGIN ===\n";
    cout << "Username: "; cin >> user;
    cout << "Password: "; cin >> pass;

    for (int i = 0; i < totalAkun; i++) {
        if (daftarAkun[i].username == user && daftarAkun[i].password == pass) {
            currentUser = user;
            currentRole = daftarAkun[i].role;
            cout << "\n[Login Sukses] Selamat datang, " << user << " (" << currentRole << ")!\n";
            return true;
        }
    }
    cout << "\n[Gagal] Username atau Password salah!\n";
    return false;
}

void registerProcess() {
    if (totalAkun >= MAX_AKUN) {
        cout << "\n[Gagal] Kapasitas user penuh.\n";
        return;
    }

    string user, pass;
    int pilRole;
    cout << "\n=== REGISTER ===\n";
    cout << "Username baru: "; cin >> user;
    
    for (int i = 0; i < totalAkun; i++) {
        if (daftarAkun[i].username == user) {
            cout << "\n[Gagal] Username sudah terdaftar!\n";
            return;
        }
    }

    cout << "Password baru: "; cin >> pass;
    cout << "Daftar Sebagai:\n1. Penjual\n2. Pembeli\nPilih (1/2): ";
    pilRole = inputIntValid("Pilih (1/2): ");

    daftarAkun[totalAkun].username = user;
    daftarAkun[totalAkun].password = pass;
    daftarAkun[totalAkun].role = (pilRole == 1) ? "PENJUAL" : "PEMBELI";
    totalAkun++;

    cout << "\n[Sukses] Akun berhasil didaftarkan. Silakan login.\n";
}

// menu aplikasi
void menuAdmin() {
    int pilihan;
    do {
        clearScreen();
        cout << "=======================================\n";
        cout << "            TERMINAL ADMIN             \n";
        cout << "=======================================\n";
        cout << "1. Kelola Semua Katalog (CRUD Bebas)\n";
        cout << "2. Lihat Daftar User Aktif\n";
        cout << "3. Hapus/Banned Akun User\n";
        cout << "4. Proses Semua Antrean Pesanan\n";
        cout << "5. Lihat Seluruh Riwayat Transaksi\n";
        cout << "6. Lihat Statistik Global\n";
        cout << "0. Logout\n";
        pilihan = inputIntValid("Pilih menu (0-6): ");

        if (pilihan == 1) {
            int p2;
            cout << "\n-- CRUD GLOBAL --\n1. Tambah Produk\n2. Lihat Katalog\n3. Edit Produk\n4. Hapus Produk\nPilih: ";
            p2 = inputIntValid("Pilih: ");
            if (p2 == 1) tambahProduk();
            else if (p2 == 2) tampilkanKatalogGlobal();
            else if (p2 == 3) editProduk();
            else if (p2 == 4) hapusProduk();
        } 
        else if (pilihan == 2) tampilkanDaftarUser();
        else if (pilihan == 3) hapusAkun();
        else if (pilihan == 4) {
            tampilkanAntreanPesanan("", true);
            cout << "\nKetik 1 untuk memproses pesanan paling depan, atau 0 batal: ";
            if (inputIntValid("Pilih: ") == 1) dequeuePesanan("", true);
        }
        else if (pilihan == 5) tampilkanRiwayatGlobal();
        else if (pilihan == 6) tampilkanStatistik();

        if (pilihan != 0) pauseScreen();
    } while (pilihan != 0);
}

void menuPenjual() {
    int pilihan;
    do {
        clearScreen();
        cout << "=======================================\n";
        cout << "       🏪 TERMINAL PENJUAL 🏪        \n";
        cout << "=======================================\n";
        cout << "1. Tambah Produk Dagangan\n";
        cout << "2. Lihat Katalog Produk Saya\n";
        cout << "3. Edit Harga/Stok Produk Saya\n";
        cout << "4. Hapus Produk Saya\n";
        cout << "5. Proses Pesanan Masuk Toko Saya\n";
        cout << "0. Logout\n";
        pilihan = inputIntValid("Pilih menu (0-5): ");

        if (pilihan == 1) tambahProduk();
        else if (pilihan == 2) tampilkanKatalogPenjual(currentUser);
        else if (pilihan == 3) editProduk();
        else if (pilihan == 4) hapusProduk();
        else if (pilihan == 5) {
            tampilkanAntreanPesanan(currentUser, false);
            cout << "\nKetik 1 untuk memproses pesanan paling depan, atau 0 batal: ";
            if (inputIntValid("Pilih: ") == 1) dequeuePesanan(currentUser, false);
        }

        if (pilihan != 0) pauseScreen();
    } while (pilihan != 0);
}

void menuPembeli() {
    int pilihan;
    do {
        clearScreen();
        cout << "=======================================\n";
        cout << "       🛒 TERMINAL PEMBELI 🛒        \n";
        cout << "=======================================\n";
        cout << "1. Lihat Semua Etalase Barang\n";
        cout << "2. Cari Barang\n";
        cout << "3. Masukkan Barang ke Keranjang\n";
        cout << "4. Lihat & Undo Isi Keranjang\n";
        cout << "5. Checkout Keranjang & Bayar\n";
        cout << "6. Konfirmasi Barang Diterima\n";
        cout << "7. Lihat Riwayat Pembelian Saya\n";
        cout << "8. Cetak Nota Pembelian Terakhir\n";
        cout << "0. Logout\n";
        pilihan = inputIntValid("Pilih menu (0-8): ");

        if (pilihan == 1) menuSorting();
        else if (pilihan == 2) cariProduk();
        else if (pilihan == 3) tambahKeKeranjang();
        else if (pilihan == 4) {
            tampilkanKeranjang();
            if (topKeranjang != NULL) {
                cout << "\nKetik 1 untuk membatalkan (Undo/Pop) barang terakhir, atau 0 kembali: ";
                if (inputIntValid("Pilih: ") == 1) popKeranjang();
            }
        }
        else if (pilihan == 5) checkoutKeranjang();
        else if (pilihan == 6) konfirmasiPenerimaan();
        else if (pilihan == 7) tampilkanRiwayatPembeli(currentUser);
        else if (pilihan == 8) cetakNota();

        if (pilihan != 0) pauseScreen();
    } while (pilihan != 0);
}

int main() {
    muatSemuaData(); // Load data saat startup

    int pilihan = -1;
    do {
        clearScreen();
        cout << "=======================================\n";
        cout << "        MARKETPLACE MINI v3.0          \n";
        cout << "=======================================\n";
        cout << "1. Login\n";
        cout << "2. Register Akun Baru\n";
        cout << "0. Keluar Program\n";
        pilihan = inputIntValid("Pilih (0-2): ");

        if (pilihan == 1) {
            if (loginProcess()) {
                pauseScreen();
                if (currentRole == "ADMIN") menuAdmin();
                else if (currentRole == "PENJUAL") menuPenjual();
                else if (currentRole == "PEMBELI") menuPembeli();
                
                currentUser = "";
                currentRole = "";
            } else {
                pauseScreen();
            }
        } 
        else if (pilihan == 2) {
            registerProcess();
            pauseScreen();
        }

    } while (pilihan != 0);

    simpanSemuaData(); // Save data sebelum exit
    cout << "\nData berhasil disimpan. Terima kasih telah menggunakan Marketplace Mini!\n";
    return 0;
}
