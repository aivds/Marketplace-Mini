#include "global.h"
#include <iomanip>
// --- STACK (UNDO) ---
struct NodeStack
{
    string aksi;
    int idTarget;
    NodeStack *next;
};
NodeStack *topUndo = NULL;

void pushUndo(string aksi, int id)
{
    NodeStack *baru = new NodeStack;
    baru->aksi = aksi;
    baru->idTarget = id;
    baru->next = topUndo;
    topUndo = baru;
}

void popUndo()
{
    if (topUndo == NULL)
    {
        cout << "Tidak ada aksi untuk di-undo!\n";
        return;
    }
    NodeStack *hapus = topUndo;
    if (hapus->aksi == "TAMBAH")
    {
        hapusData(hapus->idTarget);
        cout << "\nUndo: Penambahan produk dengan ID " << hapus->idTarget << " dibatalkan.\n";
    }
    topUndo = topUndo->next;
    delete hapus;
}

// --- QUEUE (ANTRIAN PESANAN) ---
struct NodeQueue
{
    string namaPembeli;
    string namaProduk;
    int jumlah;
    NodeQueue *next;
};
NodeQueue *frontQueue = NULL;
NodeQueue *rearQueue = NULL;

void enqueue(string pembeli, string produk, int jmlBeli)
{
    NodeQueue *baru = new NodeQueue;
    baru->namaPembeli = pembeli;
    baru->namaProduk = produk;
    baru->jumlah = jmlBeli;
    baru->next = NULL;
    if (rearQueue == NULL)
        frontQueue = rearQueue = baru;
    else
    {
        rearQueue->next = baru;
        rearQueue = baru;
    }
    cout << "Pesanan " << pembeli << " masuk antrian!\n";
}

void inputEnqueue()
{
    string pilihan;

    do
    {
        if (totalProduk == 0)
        {
            cout << "\n[Gagal] Tidak dapat membuat pesanan karena katalog produk masih kosong.\n";
            return;
        }

        string pmb, prd;
        int jmlBeli;

        cout << "\n--- INPUT PESANAN ---\n";
        cout << "Nama Pembeli: ";
        getline(cin >> ws, pmb);
        cout << "Nama Produk: ";
        getline(cin >> ws, prd);
        cout << "Jumlah Beli : ";
        cin >> jmlBeli;

        pmb = keTitleCase(pmb);

        string prdKecil = prd;
        for (size_t i = 0; i < prdKecil.length(); i++)
        {
            prdKecil[i] = tolower(prdKecil[i]);
        }

        bool produkDitemukan = false;
        int stokTersedia = 0;
        string namaProdukAsli = "";

        for (int i = 0; i < totalProduk; i++)
        {
            string katalogKecil = katalog[i].nama;
            for (size_t k = 0; k < katalogKecil.length(); k++)
            {
                katalogKecil[k] = tolower(katalogKecil[k]);
            }

            if (katalogKecil == prdKecil)
            {
                produkDitemukan = true;
                namaProdukAsli = katalog[i].nama;
                stokTersedia = katalog[i].stok;
                break;
            }
        }

        if (!produkDitemukan)
        {
            cout << "\n[Gagal] Pesanan ditolak! Produk '" << prd << "' tidak terdaftar di katalog.\n";
        }
        else if (stokTersedia <= 0)
        {
            cout << "\n[Gagal] Pesanan ditolak! Stok untuk '" << namaProdukAsli << "' sedang kosong.\n";
        }
        else if (jmlBeli <= 0)
        {
            cout << "\n[Gagal] Pesanan ditolak! Jumlah pembelian harus minimal 1 pcs.\n";
        }
        else if (jmlBeli > stokTersedia)
        {
            cout << "\n[Gagal] Pesanan ditolak! Stok tidak cukup (Tersedia: " << stokTersedia << " pcs).\n";
        }
        else
        {
            enqueue(pmb, namaProdukAsli, jmlBeli);
            for (int i = 0; i < totalProduk; i++) {
                if (katalog[i].nama == namaProdukAsli) {
                    katalog[i].stok -= jmlBeli;
                    break;
                }
            }
        }

        cout << "\nTambah pesanan? (y/n): ";
        cin.ignore();
        getline(cin, pilihan);

    } while (pilihan == "y" || pilihan == "Y" || pilihan.empty());

    cout << "\nKembali ke menu utama...\n";
}

void dequeue()
{
    if (frontQueue == NULL)
    {
        cout << "\nAntrian pesanan kosong!\n";
        return;
    }
    NodeQueue *hapus = frontQueue;
    cout << "\nMemproses pesanan: " << hapus->namaProduk << " untuk " << hapus->namaPembeli << "\n";
    tambahRiwayat("Terjual: " + hapus->namaProduk + " ke " + hapus->namaPembeli);
    frontQueue = frontQueue->next;
    if (frontQueue == NULL)
        rearQueue = NULL;
    delete hapus;
}

// --- GROUP BUYING ---
string grupPatungan[3];
int kuotaPatungan = 0;

void patunganBelanja(string pembeli, string produk)
{
    if (kuotaPatungan < 3)
    {
        grupPatungan[kuotaPatungan] = pembeli;
        kuotaPatungan++;
        cout << pembeli << " bergabung patungan " << produk << "! (Kuota: " << kuotaPatungan << "/3)\n";
    }
    if (kuotaPatungan == 3)
    {
        cout << "\n[!] KUOTA PATUNGAN PENUH! Pesanan masuk ke antrian...\n";
        for (int i = 0; i < 3; i++)
        {
            enqueue(grupPatungan[i], produk + "_(Harga_Diskon)");
        }
        kuotaPatungan = 0;
    }
}

void inputPatunganBelanja()
{
    string pmb, prd;
    cout << "Nama Pembeli: ";
    getline(cin >> ws, pmb);
    cout << "Produk Patungan: ";
    getline(cin >> ws, prd);
    patunganBelanja(pmb, prd);
}

void tampilkanAntrean()
{
    if (frontQueue == NULL)
    {
        cout << "\n========================================================================\n";
        cout << "                         DAFTAR ANTREAN PESANAN                         \n";
        cout << "========================================================================\n";
        cout << "          [Kosong] Belum ada pesanan aktif dalam antrean saat ini.\n";
        cout << "========================================================================\n";
        return;
    }

    NodeQueue *saatIni = frontQueue;
    int nomor = 1;

    cout << "\n========================================================================\n";
    cout << "                         DAFTAR ANTREAN PESANAN                         \n";
    cout << "========================================================================\n";
    cout << left << setw(5) << "No" << " | "
         << left << setw(23) << "Nama Pembeli" << " | "
         << left << setw(27) << "Produk Diorder" << " | "
         << "Quantity" << endl;
    cout << "------------------------------------------------------------------------\n";

    while (saatIni != NULL)
    {
        cout << left << setw(5) << nomor << " | "
             << left << setw(23) << saatIni->namaPembeli << " | "
             << left << setw(27) << saatIni->namaProduk << " | "
             << saatIni->jumlah << " pcs" << endl;

        saatIni = saatIni->next;
        nomor++;
    }
    cout << "========================================================================\n";
}