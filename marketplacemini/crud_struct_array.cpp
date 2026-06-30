#include "global.h"
#include <cctype>
#include <iomanip>

Produk katalog[100];
int totalProduk = 0;

string keTitleCase(string str)
{
    if (str.empty())
        return str;

    string hasilAkhir = "";
    bool dalamPetik = false;
    bool kataBaru = true;

    for (size_t i = 0; i < str.length(); i++)
    {
        if (str[i] == '\'')
        {
            dalamPetik = !dalamPetik;
            continue;
        }

        if (str[i] == ' ')
        {
            kataBaru = true;
            hasilAkhir += str[i];
            continue;
        }

        if (dalamPetik)
        {
            hasilAkhir += toupper(str[i]);
            kataBaru = false;
        }
        else
        {
            if (kataBaru)
            {
                hasilAkhir += toupper(str[i]);
                kataBaru = false;
            }
            else
            {
                hasilAkhir += tolower(str[i]);
            }
        }
    }
    return hasilAkhir;
}

void tampilkanData()
{
    if (totalProduk == 0)
    {
        cout << "\nKatalog masih kosong!\n";
        return;
    }

    string headerTabel = "\n"
                         "================================================================\n"
                         "                         KATALOG PRODUK                        \n"
                         "================================================================\n"
                         "ID    | "
                         "Nama Produk" +
                         string(23, ' ') + " | Harga        | Stok \n"
                         "----------------------------------------------------------------\n";
    cout << headerTabel;

    for (int i = 0; i < totalProduk; i++)
    {
        cout << left << setw(5) << katalog[i].id << " | "
             << left << setw(34) << katalog[i].nama << " | "
             << "Rp" << left << setw(10) << katalog[i].harga << " | "
             << left << setw(4) << katalog[i].stok << endl;
    }
    cout << "================================================================\n";
}

void tambahData(int id, string nama, int harga, int stok)
{
    katalog[totalProduk].id = id;
    katalog[totalProduk].nama = keTitleCase(nama);
    katalog[totalProduk].harga = harga;
    katalog[totalProduk].stok = stok;
    totalProduk++;

    cout << "Produk '" << katalog[totalProduk - 1].nama << "' berhasil ditambahkan!\n";

    pushUndo("TAMBAH", id);
}

void inputTambahData()
{
    int id, hrg, stk;
    string nm;
    cout << "ID: ";
    cin >> id;
    cout << "Nama Produk (Bisa Pakai Spasi): ";
    getline(cin >> ws, nm);
    cout << "Harga: ";
    cin >> hrg;
    cout << "Stok: ";
    cin >> stk;
    tambahData(id, nm, hrg, stk);
}

void updateData(int id, string namaBaru, int hargaBaru, int stokBaru)
{
    for (int i = 0; i < totalProduk; i++)
    {
        if (katalog[i].id == id)
        {
            katalog[i].nama = keTitleCase(namaBaru);
            katalog[i].harga = hargaBaru;
            katalog[i].stok = stokBaru;
            cout << "Produk ID " << id << " berhasil diperbarui!\n";
            return;
        }
    }
    cout << "Produk dengan ID " << id << " tidak ditemukan.\n";
}

void inputUpdateData()
{
    int id, hrg, stk;
    string nmBaru;
    cout << "Masukkan ID Produk yang diupdate: ";
    cin >> id;
    cout << "Nama Baru: ";
    getline(cin >> ws, nmBaru);
    cout << "Harga Baru: Rp";
    cin >> hrg;
    cout << "Stok Baru: ";
    cin >> stk;
    updateData(id, nmBaru, hrg, stk);
}

void hapusData(int id)
{
    int indexHapus = -1;
    for (int i = 0; i < totalProduk; i++)
    {
        if (katalog[i].id == id)
        {
            indexHapus = i;
            break;
        }
    }

    if (indexHapus == -1)
    {
        cout << "Produk dengan ID " << id << " tidak ditemukan.\n";
        return;
    }

    for (int i = indexHapus; i < totalProduk - 1; i++)
    {
        katalog[i] = katalog[i + 1];
    }
    totalProduk--;
    cout << "Produk ID " << id << " berhasil dihapus dari katalog!\n";
}

void inputHapusData()
{
    int id;
    cout << "Masukkan ID Produk yang dihapus: ";
    cin >> id;
    hapusData(id);
}