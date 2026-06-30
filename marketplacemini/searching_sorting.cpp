#include "global.h"
#include <cctype>
#include <iomanip>

string keHurufKecil(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        str[i] = tolower(str[i]);
    }
    return str;
}

void cariData(string keyword)
{
    bool ketemu = false;
    string keywordKecil = keHurufKecil(keyword);

    string headerTabel = "\n"
                         "================================================================\n"
                         "                         HASIL PENCARIAN                        \n"
                         "================================================================\n"
                         "ID    | "
                         "Nama Produk" +
                         string(23, ' ') + " | Harga        | Stok \n"
                         "----------------------------------------------------------------";
    for (int i = 0; i < totalProduk; i++)
    {
        string namaProdukKecil = keHurufKecil(katalog[i].nama);

        if (namaProdukKecil.find(keywordKecil) == 0)
        {
            if (!ketemu)
            {
                cout << headerTabel << endl;
                ketemu = true;
            }

            cout << left << setw(5) << katalog[i].id << " | "
                 << left << setw(34) << katalog[i].nama << " | "
                 << "Rp" << left << setw(10) << katalog[i].harga << " | "
                 << left << setw(4) << katalog[i].stok << endl;
        }
    }

    if (ketemu)
    {
        cout << "================================================================\n";
    }
    else
    {
        cout << "\nProduk '" << keyword << "' tidak ditemukan.\n";
    }
}

void inputCariData()
{
    string key;
    cout << "Cari Nama Produk: ";
    getline(cin >> ws, key);
    cariData(key);
}

void urutkanData()
{
    if (totalProduk == 0)
    {
        cout << "\nPengurutan Gagal: Data Produk masih kosong!\n";
        return;
    }

    Produk katalogUrut[100];
    for (int i = 0; i < totalProduk; i++)
    {
        katalogUrut[i] = katalog[i];
    }

    for (int i = 0; i < totalProduk - 1; i++)
    {
        for (int j = 0; j < totalProduk - i - 1; j++)
        {
            if (katalogUrut[j].harga > katalogUrut[j + 1].harga)
            {
                Produk temp = katalogUrut[j];
                katalogUrut[j] = katalogUrut[j + 1];
                katalogUrut[j + 1] = temp;
            }
        }
    }

    string headerTabel = "\n"
                         "================================================================\n"
                         "             KATALOG PRODUK (URUTAN HARGA TERMURAH)             \n"
                         "================================================================\n"
                         "ID    | Nama Produk                         | Harga        | Stok \n"
                         "----------------------------------------------------------------\n";
    cout << headerTabel;

    for (int i = 0; i < totalProduk; i++)
    {
        cout << left << setw(5) << katalogUrut[i].id << " | "
             << left << setw(34) << katalogUrut[i].nama << " | "
             << "Rp" << left << setw(10) << katalogUrut[i].harga << " | "
             << left << setw(4) << katalogUrut[i].stok << endl;
    }
    cout << "================================================================\n";
}

// --- BARTER ---
void prosesBarter(string pembeli, string produkTujuan, string barangBekas)
{
    bool ketemu = false;
    int indexProduk = -1;

    string produkTujuanKecil = keHurufKecil(produkTujuan);

    for (int i = 0; i < totalProduk; i++)
    {
        if (keHurufKecil(katalog[i].nama) == produkTujuanKecil)
        {
            ketemu = true;
            indexProduk = i;
            break;
        }
    }
    if (!ketemu)
    {
        cout << "Barter Gagal: Produk tidak ada.\n";
        return;
    }

    int nilaiBarter = 150000;
    int hargaAkhir = katalog[indexProduk].harga - nilaiBarter;
    if (hargaAkhir < 0)
        hargaAkhir = 0;

    cout << "\n--- SISTEM BARTER ---\n";
    cout << "Barang bekas (" << barangBekas << ") dihargai: Rp" << nilaiBarter << endl;
    cout << "Harga " << produkTujuan << " menjadi: Rp" << hargaAkhir << endl;
    enqueue(pembeli, produkTujuan + " (Hasil Barter)");
}



BarterNode* headBarter = NULL;
int counterBarter = 1;

// CASE 1: Ajukan Barter Pertama Kali
void ajukanBarter() {
    string pmb, prd, brg;
    cout << "\n--- 1. AJUKAN BARTER ---\n";
    cout << "Nama Pembeli: ";
    getline(cin >> ws, pmb);
    cout << "Produk Marketplace yang Diincar: ";
    getline(cin >> ws, prd);
    cout << "Barang Bekas Anda yang Ditukarkan: ";
    getline(cin >> ws, brg);

    bool ketemu = false;
    for (int i = 0; i < totalProduk; i++) {
        if (keTitleCase(katalog[i].nama) == keTitleCase(prd)) {
            ketemu = true;
            prd = katalog[i].nama; 
            break;
        }
    }

    if (!ketemu) {
        cout << "[Gagal] Produk '" << prd << "' tidak ditemukan di katalog!\n";
        return;
    }

    BarterNode* baru = new BarterNode;
    baru->idBarter = counterBarter++;
    baru->pembeli = keTitleCase(pmb);
    baru->produkTujuan = prd;
    baru->barangBekas = brg;
    baru->tambahDana = 0;
    baru->status = "PENDING";
    baru->next = headBarter;
    headBarter = baru;

    cout << "[Sukses] Barter berhasil diajukan! Menunggu respons penjual (Cek di menu Lihat Permintaan).\n";
}

// CASE 3: Sisi Penjual (Memproses Permintaan Barter)
void lihatPermintaanBarter() {
    if (headBarter == NULL) {
        cout << "\nBelum ada pengajuan barter masuk.\n";
        return;
    }

    cout << "\n--- 3. PERMINTAAN BARTER MASUK (SISI PENJUAL) ---\n";
    BarterNode* temp = headBarter;
    while (temp != NULL) {
        cout << "ID: " << temp->idBarter 
             << " | Pembeli: " << temp->pembeli 
             << " | Ingin Tukar: [" << temp->barangBekas << "] dengan [" << temp->produkTujuan << "]\n"
             << "  Status Saat Ini: " << temp->status << "\n-----------------------------------------\n";
        temp = temp->next;
    }

    int idPilih;
    cout << "Masukkan ID Barter yang Ingin Diproses (0 untuk kembali): ";
    cin >> idPilih;
    if (idPilih == 0) return;

    temp = headBarter;
    while (temp != NULL && temp->idBarter != idPilih) {
        temp = temp->next;
    }

    if (temp == NULL) {
        cout << "ID Barter tidak ditemukan.\n";
        return;
    }

    cout << "\nOpsi Penjual untuk ID " << idPilih << ":\n";
    cout << "1. Setujui Barter murni\n";
    cout << "2. Tolak Barter\n";
    cout << "3. Minta Tukar Tambah (Tambah Dana)\n";
    cout << "Pilih tindakan (1-3): ";
    int aksi;
    cin >> aksi;

    if (aksi == 1) {
        temp->status = "DISETUJUI";
        cout << "Barter disetujui! Pesanan otomatis masuk antrean belanja.\n";
        enqueue(temp->pembeli, temp->produkTujuan + " (Barter: " + temp->barangBekas + ")", 1);
    } else if (aksi == 2) {
        temp->status = "DITOLAK";
        cout << "Barter berhasil ditolak.\n";
    } else if (aksi == 3) {
        int dana;
        cout << "Masukkan nominal dana tambahan yang diminta: Rp";
        cin >> dana;
        temp->tambahDana = dana;
        temp->status = "BUTUH_DANA";
        cout << "Permintaan tukar tambah berhasil dikirim ke pembeli.\n";
    } else {
        cout << "Aksi tidak valid!\n";
    }
}

// CASE 2: Sisi Pembeli (Melihat Hasil / Status Barter)
void lihatHasilBarter() {
    if (headBarter == NULL) {
        cout << "\nBelum ada riwayat pengajuan barter.\n";
        return;
    }

    cout << "\n--- 2. STATUS HASIL BARTER ANDA ---\n";
    BarterNode* temp = headBarter;
    while (temp != NULL) {
        cout << "Pembeli: " << temp->pembeli 
             << " | Produk: " << temp->produkTujuan 
             << " | Status: " << temp->status;
        if (temp->status == "BUTUH_DANA") {
            cout << " (Diminta tambah dana: Rp" << temp->tambahDana << ")";
        }
        cout << "\n";
        temp = temp->next;
    }
}

// CASE 4: Sisi Pembeli (Eksekusi Opsi Tukar Tambah jika BUTUH_DANA)
void opsiTukarTambah() {
    if (headBarter == NULL) {
        cout << "\nBelum ada data barter.\n";
        return;
    }

    cout << "\n--- 4. OPSI TUKAR TAMBAH (PEMBELI) ---\n";
    BarterNode* temp = headBarter;
    bool ada = false;
    while (temp != NULL) {
        if (temp->status == "BUTUH_DANA") {
            cout << "ID: " << temp->idBarter 
                 << " | Pembeli: " << temp->pembeli 
                 << " | Produk: " << temp->produkTujuan 
                 << " | Tambah Dana: Rp" << temp->tambahDana << "\n";
            ada = true;
        }
        temp = temp->next;
    }

    if (!ada) {
        cout << "Tidak ada penawaran tukar tambah yang menggantung saat ini.\n";
        return;
    }

    int idPilih;
    cout << "Masukkan ID Barter untuk dieksekusi: ";
    cin >> idPilih;

    temp = headBarter;
    while (temp != NULL && temp->idBarter != idPilih) {
        temp = temp->next;
    }

    if (temp == NULL || temp->status != "BUTUH_DANA") {
        cout << "ID tidak valid atau status bukan Tukar Tambah!\n";
        return;
    }

    cout << "Apakah Anda setuju membayar tambahan Rp" << temp->tambahDana << "? (y/n): ";
    char pil;
    cin >> pil;

    if (pil == 'y' || pil == 'Y') {
        temp->status = "DISETUJUI";
        cout << "Tukar tambah berhasil! Pesanan masuk antrean.\n";
        enqueue(temp->pembeli, temp->produkTujuan + " (Tukar Tambah)", 1);
    } else {
        temp->status = "DITOLAK";
        cout << "Anda menolak tukar tambah. Barter dibatalkan.\n";
    }
}

// Fungsi Utama Sub-Menu Barter yang dipanggil oleh main()
void inputBarter() {
    int subMenu;
    cout << "\n=======================================\n";
    cout << "          SUB-SISTEM BARTER v2.0       \n";
    cout << "=======================================\n";
    cout << "1. Ajukan Barter (Case 1)\n";
    cout << "2. Lihat Hasil Barter (Case 2 - Sisi Pembeli)\n";
    cout << "3. Lihat Permintaan Barter (Case 3 - Sisi Penjual)\n";
    cout << "4. Opsi Tukar Tambah (Case 4)\n";
    cout << "Pilih sub-menu (1-4): ";
    cin >> subMenu;

    if (subMenu == 1) ajukanBarter();
    else if (subMenu == 2) lihatHasilBarter();
    else if (subMenu == 3) lihatPermintaanBarter();
    else if (subMenu == 4) opsiTukarTambah();
    else cout << "Pilihan salah!\n";
}