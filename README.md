# Simulasi Animasi Algoritma Pencarian (BFS) di Terminal

Proyek ini adalah implementasi visual dari algoritma **Breadth-First Search (BFS)** menggunakan bahasa C. Program ini berjalan langsung di terminal atau command prompt dan menampilkan animasi frame-by-frame bagaimana sebuah "agen" mengeksplorasi peta (grid) untuk menemukan rute terpendek dari titik awal ke titik tujuan tanpa menabrak rintangan.

## ✨ Fitur Utama

- **Visualisasi Real-time:** Menampilkan animasi langkah demi langkah saat agen mencari jalan (eksplorasi) dan saat menggambar rute terpendek yang ditemukan.
- **Cross-Platform:** Kode ini secara otomatis mendeteksi sistem operasi dan menyesuaikan fungsi jeda (sleep) serta pembersihan layar (clear screen) untuk **Windows, macOS, dan Linux**.
- **Algoritma BFS Optimal:** Menjamin penemuan rute terpendek (shortest path) pada grid yang tidak memiliki bobot langkah (unweighted grid).
- **Sistem Backtracking:** Setelah target ditemukan, agen akan melacak kembali (backtrack) jejaknya untuk membentuk garis rute yang jelas.

## 🗺️ Legenda Peta (Grid)

Saat simulasi berjalan, Anda akan melihat berbagai simbol di layar. Berikut adalah artinya:

- `[S]` : **Start** - Posisi awal agen.
- `[T]` : **Target** - Posisi tujuan atau makanan yang dicari agen.
- `[#]` : **Obstacle/Wall** - Dinding atau rintangan yang tidak bisa dilewati.
- `[.]` : **Visited** - Jejak area yang sudah dieksplorasi oleh agen selama proses pencarian.
- `[*]` : **Path** - Garis rute terpendek menuju target (muncul di akhir jika rute ditemukan).
- `[ ]` : **Empty** - Ruang kosong yang belum dieksplorasi.

## 🚀 Cara Menjalankan Program

### Prasyarat
Pastikan Anda sudah menginstal *compiler* C (seperti GCC) di komputer Anda.

### 1. Kompilasi Kode
Buka terminal atau command prompt, arahkan ke folder tempat file `search_algo.c` berada, lalu jalankan perintah berikut:

```bash
gcc search_algo.c -o search_algo
```

### 2. Jalankan Program
Setelah berhasil dikompilasi, jalankan program dengan perintah berikut sesuai sistem operasi Anda:

- **Windows:**
  ```cmd
  search_algo.exe
  ```
- **macOS / Linux:**
  ```bash
  ./search_algo
  ```

## 🛠️ Cara Mengkustomisasi Peta

Anda dapat dengan mudah mengubah bentuk peta atau posisi Start dan Target dengan mengedit file `search_algo.c`:

1. **Mengubah Peta:** 
   Cari variabel `char grid[ROWS][COLS]` di dalam kode dan ubah susunan `#` dan spasi sesuai keinginan Anda. Pastikan ukurannya tetap sesuai dengan konstanta `ROWS` (10) dan `COLS` (20), atau ubah juga nilai konstantanya jika ingin ukuran peta yang berbeda.

2. **Mengubah Posisi Start / Target:**
   Cari di dalam fungsi `int main()`.
   ```c
   Point start = {1, 1};   // Ubah koordinat (Baris, Kolom)
   Point target = {7, 14}; // Ubah koordinat (Baris, Kolom)
   ```
   *Catatan: Indeks baris dan kolom dimulai dari angka 0.*

3. **Mengatur Kecepatan Animasi:**
   Anda bisa mengubah angka pada fungsi `SLEEP(50)` untuk pencarian dan `SLEEP(100)` untuk penggambaran rute di dalam fungsi `run_simulation()`. Semakin kecil angkanya, semakin cepat animasinya.

## 📝 Lisensi
Proyek ini bersifat *open-source* dan bebas untuk dimodifikasi maupun dipelajari untuk keperluan edukasi.