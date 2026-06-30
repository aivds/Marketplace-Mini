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

void inputBarter()
{
    string pmb, prd, brg;
    cout << "Nama Pembeli: ";
    getline(cin >> ws, pmb);
    cout << "Produk Tujuan: ";
    getline(cin >> ws, prd);
    cout << "Barang Bekas Anda: ";
    getline(cin >> ws, brg);
    prosesBarter(pmb, prd, brg);
}