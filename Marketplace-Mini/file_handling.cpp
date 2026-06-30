#include "global.h"
#include <fstream>

void simpanDataKeFile()
{
    ofstream file("katalog.csv");
    for (int i = 0; i < totalProduk; i++)
    {
        file << katalog[i].id << "," << katalog[i].nama << ","
             << katalog[i].harga << "," << katalog[i].stok << endl;
    }
    file.close();
    cout << "Data berhasil disimpan ke 'katalog.csv'!\n";
}

void muatDataDariFile()
{
    ifstream file("katalog.csv");
    if (!file.is_open())
    {
        return;
    }

    int id, harga, stok;
    string nama;
    char koma;

    totalProduk = 0;
    while (file >> id >> koma && getline(file, nama, ',') && file >> harga >> koma >> stok)
    {
        katalog[totalProduk].id = id;
        katalog[totalProduk].nama = nama;
        katalog[totalProduk].harga = harga;
        katalog[totalProduk].stok = stok;
        totalProduk++;
    }
    file.close();
    cout << "[Sistem] Berhasil memuat " << totalProduk << " produk dari database 'katalog.csv'.\n";
}