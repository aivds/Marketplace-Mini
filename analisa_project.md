# Analisis Project Marketplace Mini

Berdasarkan pengecekan dan perbandingan antara folder `Marketplace-Mini` dan `marketplacemini.cpp`, berikut adalah penjabaran detail mengenai perbedaan, analisis bug, kesesuaian dengan ketentuan proyek, serta saran untuk pengembangan selanjutnya.

## 1. Analisis Perbedaan Kedua Folder
Kedua folder ini pada dasarnya adalah iterasi dari project yang sama, namun terdapat beberapa perubahan penting pada versi `marketplacemini.cpp` dibandingkan `Marketplace-Mini`:

*   **Penyimpanan File Handling:** `Marketplace-Mini` menggunakan format `katalog.csv`, sedangkan `marketplacemini.cpp` mengubah format penyimpanan menjadi `katalog.txt`.
*   **Sistem Barter Baru:** Di `marketplacemini.cpp`, terdapat penambahan besar-besaran untuk fitur Sistem Barter (Case 1 hingga 4) menggunakan struktur data **Linked List** (berdasarkan `Struct BarterNode`). Versi `Marketplace-Mini` sebelumnya hanya memiliki logika barter yang sangat sederhana tanpa struktur data yang jelas.
*   **Penghapusan Validasi Input:** Kode penanganan *error input* (menggunakan `cin.fail()`) yang ada pada `main.cpp` di `Marketplace-Mini` telah dihapus di versi `marketplacemini.cpp`.
*   **Fitur Dinonaktifkan:** Beberapa fitur seperti Lelang (`inputTambahBidLelang`, `lihatLelang`) dan Patungan Belanja (`inputPatunganBelanja`) telah dinonaktifkan (di-comment `/* ... */`) pada versi `marketplacemini.cpp`.
*   **Penghapusan Logika Stok:** Pada saat memasukkan barang ke antrian (`inputEnqueue()`), logika pengurangan stok otomatis yang ada di `Marketplace-Mini` telah dihapus pada `marketplacemini.cpp`.

## 2. Bug pada Masing-Masing Folder

### Bug di `marketplacemini.cpp` (Versi Baru)
1.  **Infinite Loop pada Menu Utama (Kritis):** Karena penghapusan `cin.fail()` di `main.cpp`, jika user secara tidak sengaja menginputkan karakter/huruf saat diminta memasukkan angka pilihan menu, program akan mengalami *infinite loop* (error berulang tiada henti).
2.  **Stok Tidak Berkurang Saat Dibeli (Kritis):** Pada file `stack_queue.cpp` fungsi `inputEnqueue()`, kode `katalog[i].stok -= jmlBeli;` dihapus. Akibatnya, stok barang di etalase tidak akan pernah berkurang meskipun sudah dimasukkan ke antrian belanja, sehingga user bisa memesan barang *out-of-stock* tanpa batas.
3.  **Kesalahan Logika Undo (Stack):** Di fungsi `popUndo()`, logika penghapusan yang sebelumnya akurat menggunakan `hapusData(hapus->idTarget)` diubah menjadi sekadar `totalProduk--;`. Ini sangat berbahaya karena `totalProduk--` hanya memotong array secara paksa di bagian akhir dan dapat memicu *data corruption* jika id target bukan berada di akhir array.
4.  **Dead Code:** Terdapat banyak kode yang sekadar dijadikan komentar (di-comment) seperti fitur Lelang dan Patungan. Hal ini membuat *codebase* terlihat kotor.

### Bug di `Marketplace-Mini` (Versi Lama)
1.  **File Sampah Ter-commit:** Mengandung file *temporary* / hasil kompilasi bawaan dari ekstensi seperti `tempCodeRunnerFile.exe` dan `MarketplaceMini.exe` yang seharusnya tidak masuk ke dalam repository.
2.  **Implementasi Linked List Belum Relevan:** Logika *barter* awal belum optimal dalam merepresentasikan penggunaan *linked list* dibandingkan dengan versi terbarunya.

## 3. Kesesuaian dengan KETENTUAN FINAL PROJECT.pdf
Secara keseluruhan, kedua versi project **SUDAH MEMENUHI KETENTUAN WAJIB** yang diminta pada PDF:
*   **Struktur Data:** Keduanya sudah mengimplementasikan minimal 3 struktur data secara benar, di antaranya: Array & Struct (Katalog), Stack (Undo History), Queue (Antrian Pesanan), Pointer, dan Linked List (Sistem Barter di versi terbaru / Lelang di versi lama).
*   **Fitur CRUD:** Memiliki fitur Tambah, Tampil, Update, dan Hapus (berada pada modul CRUD).
*   **Modularitas Kode:** Fungsi-fungsi telah dipisah ke berbagai file berbeda (`main.cpp`, `file_handling.cpp`, `stack_queue.cpp`, dsb).
*   **File Handling:** Terdapat sistem simpan/baca data permanen ke ekstensi `.txt` atau `.csv`.
*   **Sorting & Searching:** Sudah digunakan pada filter katalog/barter.

**Catatan Bonus:** Dengan hilangnya fungsi `cin.fail()` di `marketplacemini.cpp`, kelompok *kehilangan peluang mendapatkan poin BONUS* untuk kriteria "Validasi Input".

## 4. Saran untuk Kedepannya
Agar project ini dapat mendapat nilai maksimal (termasuk nilai bonus), disarankan untuk melakukan perbaikan dan modifikasi berikut:

1.  **Segera Kembalikan Validasi Input:** Pasang kembali baris kode validasi di `main.cpp` untuk mengamankan input user dan memulihkan poin bonus "Validasi input".
    ```cpp
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        pilihan = 0;
    }
    ```
2.  **Perbaiki Bug Pengurangan Stok:** Pada fungsi `inputEnqueue()` di versi terbaru, pastikan untuk mengembalikan logika pengurangan stok barang ketika dimasukkan ke dalam antrian belanja.
3.  **Kembalikan Logika Undo:** Gunakan kembali `hapusData(hapus->idTarget)` pada fungsi `popUndo()` agar proses Undo tidak mengacak urutan data Array.
4.  **Pembersihan Dead Code:** Hapus secara menyeluruh fungsi-fungsi Lelang dan Patungan yang sudah dikomentari jika memang tidak lagi digunakan.
5.  **Gunakan `.gitignore`:** Tambahkan file `.gitignore` berisi `*.exe` untuk menghindari masuknya file kompilasi ke dalam Github/pengumpulan tugas.
6.  **Tingkatkan UI Interaktif (Bonus Tambahan):** Anda bisa menyisipkan fungsi `system("cls")` atau `system("clear")` setiap kali user berpindah menu agar tampilan terminal lebih rapi dan bersih. Ini akan meningkatkan aspek *UI interaktif* sesuai PDF.
7.  **Pilih Penyimpanan Konsisten:** Menggunakan format `.csv` (seperti di versi awal) biasanya lebih baik secara struktural untuk dibaca ulang oleh aplikasi pihak ketiga (seperti Excel) ketimbang menggunakan format `.txt`.
