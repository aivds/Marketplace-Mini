#include "global.h"

// --- LINKED LIST (RIWAYAT TRANSAKSI) ---
struct NodeList
{
    string logTransaksi;
    NodeList *next;
};
NodeList *headRiwayat = NULL;

void tambahRiwayat(string log)
{
    NodeList *baru = new NodeList;
    baru->logTransaksi = log;
    baru->next = headRiwayat;
    headRiwayat = baru;
}

void tampilkanRiwayat()
{
    if (headRiwayat == NULL)
    {
        cout << "\nBelum ada riwayat.\n";
        return;
    }
    cout << "\n--- RIWAYAT TRANSAKSI ---\n";
    NodeList *temp = headRiwayat;
    while (temp != NULL)
    {
        cout << "- " << temp->logTransaksi << endl;
        temp = temp->next;
    }
}

// --- LELANG ---
BidNode *headBid = NULL;

void tambahBidLelang(string pembeli, int harga)
{
    BidNode *baru = new BidNode;
    baru->pembeli = pembeli;
    baru->hargaTawaran = harga;
    baru->next = headBid;
    headBid = baru;
    cout << "Tawaran " << pembeli << " (Rp" << harga << ") berhasil masuk!\n";
}

void inputTambahBidLelang()
{
    /*
    string pmb;
    int hrg;
    cout << "Nama Pembeli: ";
    getline(cin >> ws, pmb);
    cout << "Harga Tawaran: Rp";
    cin >> hrg;
    tambahBidLelang(pmb, hrg);
    */
}

void lihatLelang()
{
    /*
    if (headBid == NULL)
    {
        cout << "Belum ada tawaran lelang.\\n";
        return;
    }
    cout << "\n--- DAFTAR LELANG TERBALIK ---\n";
    BidNode *temp = headBid;
    while (temp != NULL)
    {
        cout << "Pembeli: " << temp->pembeli << " | Tawaran: Rp" << temp->hargaTawaran << endl;
        temp = temp->next;
    }
    */
}