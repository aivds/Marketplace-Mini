#include "global.h"

// Penjelasan Main File (Program Utama)
// Ini adalah Jantung atau panggung utama berdirinya program.
// Semua file-file yang terpisah (crud, stack, dll) dipanggil dan diatur lalu lintasnya di dalam file ini.

// Inisialisasi awal variabel global secara resmi untuk dipakai se-antero C++
Produk katalog[MAX_PRODUK];
int totalProduk = 0;
Akun daftarAkun[MAX_AKUN];
int totalAkun = 0;

string currentUser = "";
string currentRole = "";
int orderCounter = 1;
int productCounter = 1;

// Pointer-pointer utama diinisialisasi NULL (kosong, belum menunjuk apapun di RAM)
NodeKeranjang* topKeranjang = NULL;
NodePesanan* frontQueue = NULL;
NodePesanan* rearQueue = NULL;
NodeRiwayat* headRiwayat = NULL;
NodeRiwayat* tailRiwayat = NULL;

// Fungsi Pelindung Input Angka (Error Handling Infinity Loop)
int inputIntValid(string prompt) {
    int val;
    while (true) { // Putar terus menerus sampai valid
        cout << prompt;
        cin >> val; 
        
        // Pengecekan krusial:
        if (cin.fail()) { // Jika cin.fail() menyala (artinya user malah ketik HURUF padahal butuh ANGKA)
            cin.clear(); // 1. Matikan alarm error dari sistem
            
            // 2. Buang isi pipa memori (maksimal 10000 karakter kotor) agar tidak nyangkut memicu infinity loop
            cin.ignore(10000, '\n'); 
            
            cout << "[Error] Masukkan angka yang valid!\n"; // 3. Peringatkan user
        } else {
            return val; // Jika berhasil berupa angka, kembalikan nilainya dan keluar dari loop
        }
    }
}

// Sistem Autentikasi
void tampilkanDaftarUser() { // Loop cetak seluruh akun untuk menu Admin
    cout << "\n=== DAFTAR USER TERDAFTAR ===\n"; // Output terminal
    cout << left << setw(15) << "USERNAME" << setw(15) << "ROLE" << endl;
    cout << "---------------------------------\n";
    for (int i = 0; i < totalAkun; i++) {
        cout << left << setw(15) << daftarAkun[i].username << setw(15) << daftarAkun[i].role << endl;
    }
    cout << "---------------------------------\n";
}

void hapusAkun() { // Fitur Admin untuk menghapus akun orang lain
    tampilkanDaftarUser();
    string usn;
    cout << "Masukkan username yang ingin dihapus: ";
    cin >> usn;
    if (usn == "admin") {
        cout << "[Gagal] Tidak bisa menghapus akun Admin utama!\n";
        return;
    }
    for (int i = 0; i < totalAkun; i++) {
        if (daftarAkun[i].username == usn) {
            // Cara menghapus array: menggeser laci-laci ke arah kiri menimpa data yang akan dihapus
            for (int j = i; j < totalAkun - 1; j++) {
                daftarAkun[j] = daftarAkun[j + 1];
            }
            totalAkun--; // Logikal data terhapus (ukuran laci mengecil 1)
            cout << "[Sukses] Akun " << usn << " dihapus!\n";
            return;
        }
    }
    cout << "[Gagal] Akun tidak ditemukan!\n";
}

bool loginProcess() { // Algoritma Linear Search untuk mencari kecocokan Akun
    string user, pass;
    cout << "\n=== LOGIN ===\n"; // Output terminal
    cout << "Username: "; cin >> user;
    cout << "Password: "; cin >> pass;

    for (int i = 0; i < totalAkun; i++) {
        if (daftarAkun[i].username == user && daftarAkun[i].password == pass) {
            currentUser = daftarAkun[i].username; // Tangkap dan ingat terus nama user yang sedang buka aplikasi
            currentRole = daftarAkun[i].role;     // Tangkap jabatan (hak aksesnya)
            cout << "\n[Login Sukses] Selamat datang, " << currentUser << "!\n";
            return true;
        }
    }
    cout << "\n[Login Gagal] Username atau password salah!\n";
    return false;
}

void registerProcess() {
    if (totalAkun >= MAX_AKUN) {
        cout << "\n[Gagal] Kapasitas user penuh.\n";
        return;
    }

    string user, pass;
    int pilRole;
    cout << "\n=== REGISTER ===\n"; // Output terminal
    cout << "Username baru: "; cin >> user;
    
    // Cek duplikasi (Username unik, tidak boleh sama)
    for (int i = 0; i < totalAkun; i++) {
        if (daftarAkun[i].username == user) {
            cout << "\n[Gagal] Username sudah terdaftar!\n";
            return;
        }
    }

    cout << "Password baru: "; cin >> pass;
    cout << "Daftar Sebagai:\n1. Penjual\n2. Pembeli\n";
    pilRole = inputIntValid("Pilih (1 atau 2): "); // Dilindungi dari input nakal

    // Mendaftarkan dan membuatkan laci array baru di indeks paling buncit (totalAkun)
    daftarAkun[totalAkun].username = user;
    daftarAkun[totalAkun].password = pass;
    daftarAkun[totalAkun].role = (pilRole == 1) ? "PENJUAL" : "PEMBELI";
    totalAkun++; // Menambah panjang array

    cout << "\n[Sukses] Akun berhasil didaftarkan. Silakan login.\n";
}

// Menu Aplikasi
void menuAdmin() {
    int pilihan;
    do {
        clearScreen();
        cout << "=======================================\n";
        cout << "       TERMINAL ADMINISTRATOR          \n";
        cout << "=======================================\n";
        cout << "1. Lihat Daftar Akun\n";
        cout << "2. Hapus Akun\n";
        cout << "3. Lihat Semua Katalog (Global)\n";
        cout << "4. Hapus Produk Pelanggaran (Force Delete)\n";
        cout << "5. Pantau Antrean Pesanan\n";
        cout << "6. Statistik Transaksi Global\n";
        cout << "0. Logout\n";
        pilihan = inputIntValid("Pilih menu (0-6): "); // Routing dengan switch logic menggunakan If

        if (pilihan == 1) tampilkanDaftarUser();
        else if (pilihan == 2) hapusAkun();
        else if (pilihan == 3) tampilkanKatalogGlobal();
        else if (pilihan == 4) hapusProduk(); // Admin numpang pakai fungsi punya penjual tapi dengan 'Kekuatan Penuh'
        else if (pilihan == 5) tampilkanAntreanPesanan("", true); 
        else if (pilihan == 6) tampilkanStatistik();
        
        if (pilihan != 0) pauseScreen();
    } while (pilihan != 0); // Putar-putar terus menu admin sampai pilih Logout (0)
}

void menuPenjual() {
    int pilihan;
    do {
        clearScreen();
        cout << "=======================================\n";
        cout << "       TERMINAL PENJUAL        \n";
        cout << "=======================================\n";
        cout << "1. Tambah Produk Dagangan\n";
        cout << "2. Lihat Katalog Produk Saya\n";
        cout << "3. Edit Produk\n";
        cout << "4. Hapus Produk\n";
        cout << "5. Lihat Antrean Pesanan Masuk\n";
        cout << "6. Proses Pesanan (Kirim)\n";
        cout << "0. Logout\n";
        pilihan = inputIntValid("Pilih menu (0-6): ");

        if (pilihan == 1) tambahProduk();
        else if (pilihan == 2) tampilkanKatalogPenjual(currentUser);
        else if (pilihan == 3) editProduk();
        else if (pilihan == 4) hapusProduk();
        else if (pilihan == 5) tampilkanAntreanPesanan(currentUser, false);
        else if (pilihan == 6) dequeuePesanan(currentUser, false);
        
        if (pilihan != 0) pauseScreen();
    } while (pilihan != 0);
}

void menuPembeli() {
    int pilihan;
    do {
        clearScreen();
        cout << "=======================================\n";
        cout << "           TERMINAL PEMBELI            \n";
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
        else if (pilihan == 3) tambahKeKeranjang(); // Fungsi Push ke Stack Keranjang
        else if (pilihan == 4) {
            tampilkanKeranjang(); // Intip ujung Stack Keranjang
            if (topKeranjang != NULL) {
                cout << "\nAda barang teratas di keranjang. Ingin Undo (keluarkan)?\n1. Ya\n2. Tidak\n";
                int un = inputIntValid("Pilih (1 atau 2): ");
                if (un == 1) popKeranjang(); // Batal atau Undo barang
            }
        }
        else if (pilihan == 5) checkoutKeranjang(); // Memindahkan semua dari Stack pindah ke Queue 
        else if (pilihan == 6) konfirmasiPenerimaan();
        else if (pilihan == 7) tampilkanRiwayatPembeli(currentUser);
        else if (pilihan == 8) cetakNota();
        
        if (pilihan != 0) pauseScreen();
    } while (pilihan != 0);
}

// Fungsi Inti C++ Mulai Disini (Entry Point)
int main() {
    // 1. Dijalankan paling awal untuk menyedot semua data dari harddisk/CSV (Membangun Array dan Linked List kembali)
    muatSemuaData(); 

    int pilihan;
    do {
        clearScreen();
        cout << "=======================================\n";
        cout << "        MARKETPLACE MINI               \n";
        cout << "=======================================\n";
        cout << "1. Login\n";
        cout << "2. Register Akun Baru\n";
        cout << "0. Keluar Program\n";
        pilihan = inputIntValid("Pilih (0-2): "); // Root Routing Utama

        if (pilihan == 1) {
            if (loginProcess()) {
                pauseScreen();
                // Persimpangan Switch Controller: Buka menu sesuai pangkat (Role)
                if (currentRole == "ADMIN") menuAdmin();
                else if (currentRole == "PENJUAL") menuPenjual();
                else if (currentRole == "PEMBELI") menuPembeli();
                
                // Ketika keluar dari menu, hapus dan lupakan username-nya (Clear Session Logout)
                currentUser = "";
                currentRole = "";
            } else {
                pauseScreen(); // Gagal login
            }
        } 
        else if (pilihan == 2) {
            registerProcess();
            pauseScreen();
        }

    } while (pilihan != 0); // Looping abadi sampai di input angka 0

    // 2. Dijalankan paling akhir saat user memilih keluar Program (0).
    // Menyedot kembali semua Array & Linked List yang ada di RAM komputer dan merapikannya ke Harddisk (CSV)
    simpanSemuaData();
    cout << "\nData berhasil disimpan. Terima kasih telah menggunakan Marketplace Mini!\n";
    return 0; // Mengirim pesan ke sistem operasi (Windows) bahwa program sukses ditutup (Status 0).
}
