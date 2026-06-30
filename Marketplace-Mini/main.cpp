#include "global.h"

int main()
{
    muatDataDariFile();

    int pilihan;
    do
    {
        cout << "\n=======================================\n";
        cout << "            MARKETPLACE MINI           \n";
        cout << "=======================================\n";
        cout << "1.  Tambah Produk Baru (Create)\n";
        cout << "2.  Tampilkan Katalog (Read)\n";
        cout << "3.  Update Data Produk (Update)\n";
        cout << "4.  Hapus Data Produk (Delete)\n";
        cout << "5.  Cari Produk (Searching)\n";
        cout << "6.  Urutkan Produk (Harga Termurah)\n";
        cout << "7.  Undo Tambah Produk (Pop Stack)\n";
        cout << "8.  Buat Pesanan (Enqueue Queue)\n";
        cout << "9.  Lihat Daftar Pesanan (View Queue)\n";
        cout << "10. Proses Pesanan (Dequeue Queue)\n";   
        cout << "11. Lihat Riwayat Transaksi (Linked List)\n";
        cout << "12. Sistem Barter (Trade-In)\n"; 
        cout << "13. Ikut Patungan (Group Buying)\n"; 
        cout << "14. Ajukan Tawaran Lelang\n"; 
        cout << "15. Lihat Daftar Lelang\n"; 
        cout << "16. Simpan & Keluar\n";                
        cout << "Pilih menu (1-16): ";
        cin >> pilihan;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            pilihan = 0;
        }


        if (pilihan == 1)
            inputTambahData();
        else if (pilihan == 2)
            tampilkanData();
        else if (pilihan == 3)
            inputUpdateData();
        else if (pilihan == 4)
            inputHapusData();
        else if (pilihan == 5)
            inputCariData();
        else if (pilihan == 6)
            urutkanData();
        else if (pilihan == 7)
            popUndo();
        else if (pilihan == 8)
            inputEnqueue();
        else if (pilihan == 9)
            tampilkanAntrean();
        else if (pilihan == 10)
            dequeue();
        else if (pilihan == 11)
            tampilkanRiwayat();
        else if (pilihan == 12)
            inputBarter();
        else if (pilihan == 13)
            inputPatunganBelanja();
        else if (pilihan == 14)
            inputTambahBidLelang();
        else if (pilihan == 15)
            lihatLelang();
        else if (pilihan == 16)
            simpanDataKeFile();
        else
            cout << "Pilihan tidak valid!\n";

    } while (pilihan != 16);

    return 0;
}