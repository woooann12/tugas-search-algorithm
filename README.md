# Search Algorithm — Grid Pathfinding Simulation

Proyek ini adalah bagian **Search Algorithm** dari tugas yang terdiri dari tiga topik:

| No | Topik | Status | 
| ----- | ----- | ----- | 
| 1 | Expert System | *(diisi anggota lain)* | 
| 2 | **Search Algorithm** | **Dokumen ini** | 
| 3 | Multi Agent System | *(diisi anggota lain)* | 

Program yang digunakan: **Custom BFS Grid Pathfinding** dalam bahasa C.
Sistem ini dibangun secara mandiri (*native*) tanpa *library* eksternal untuk mendemonstrasikan algoritma pencarian kecerdasan buatan murni di tingkat terminal.

## 1. Apa itu Search Algorithm?

Search Algorithm (Algoritma Pencarian) adalah metode sistematis yang digunakan oleh kecerdasan buatan (agen) untuk mengeksplorasi ruang masalah (*state space*) demi menemukan rute atau solusi paling optimal dari titik awal ke titik tujuan. Agen menggunakan antrean memori untuk mengevaluasi jalur yang mungkin, menghindari rintangan, dan mencegah pergerakan berulang (*infinite loop*).

## 2. Tentang Simulasi Ini

Simulasi ini menerapkan **Breadth-First Search (BFS)** pada sebuah *Grid Environment* 2D (labirin). Berbeda dengan DFS yang menelusuri satu jalur hingga buntu, BFS mengeksplorasi lingkungan secara radial (menyebar seperti gelombang air) ke segala arah secara bersamaan.

Fitur utama simulasi:

* **Lingkungan berbasis Grid:** Peta dua dimensi berisi rintangan (`#`).

* **Objek:** Agen (`S`) dan Target (`T`).

* **Visualisasi Terminal:** Peta dirender ulang secara *real-time* (frame-by-frame) di terminal.

* **Pathfinding & Backtracking:** Menampilkan jejak pencarian (`.`) dan, ketika target ditemukan, otomatis menggambar rute terpendek yang dijamin akurat secara matematis (`*`).

> 💡 **Kenapa menggunakan BFS?** Pada peta *unweighted* (jarak antar kotak sama besar), BFS menjamin agen selalu menemukan **rute mutlak terpendek**. Ini adalah fondasi dari sistem navigasi modern dan kecerdasan buatan pada *Non-Player Characters* (NPC).

## 3. Prasyarat

* **Compiler Bahasa C** (seperti GCC, MinGW, atau Clang).

* Terminal atau Command Prompt standar.

* Layar terminal yang mendukung pembersihan layar bawaan OS.

Cek apakah compiler C sudah terpasang di laptop Anda melalui terminal:

```
gcc --version


```

## 4. Instalasi dan Kompilasi

Karena menggunakan bahasa C *native*, program tidak membutuhkan `pip`, `venv`, atau *library* eksternal.

### Opsi A — Terminal (Paling Sederhana)

Buka direktori tempat file `search_algo.c` disimpan, lalu kompilasi kodenya:

**Windows / macOS / Linux**

```
gcc search_algo.c -o search_algo


```

### Opsi B — IDE (VS Code / Dev-C++)

1. Buka file `search_algo.c` di IDE Anda.

2. Pastikan ekstensi C/C++ sudah terpasang (jika menggunakan VS Code).

3. Gunakan fitur *Run/Play* bawaan, atau jalankan kompilasi menggunakan terminal internal IDE.

## 5. Menjalankan Simulasi

Setelah file *executable* terbentuk dari proses kompilasi, jalankan program:

**Windows (PowerShell / CMD)**

```
.\search_algo.exe


```

**macOS / Linux**

```
./search_algo


```

### Cara kerja singkat

| Komponen | Peran | 
| ----- | ----- | 
| `char grid[][]` | Lingkungan grid matriks tempat agen dan rintangan berada. | 
| Agen `S` (Start) | Titik mula yang menyebarkan antrean pencarian ke 4 arah (Atas, Bawah, Kiri, Kanan). | 
| `queue` (Antrean FIFO) | Memori yang mencatat kotak mana saja yang harus dieksplorasi selanjutnya berdasarkan kedalaman langkah. | 
| `render_grid()` | Menghapus frame terminal lama dan mencetak ulang matriks untuk efek animasi visual *real-time*. | 

### Hasil yang diharapkan

Muncul antarmuka peta labirin di terminal. Simbol `.` akan mulai menyebar dari titik `S` mencari jalan. Setelah bersentuhan dengan `T`, program akan berhenti memindai dan menarik garis bintang `*` sebagai rute terpendek, menyajikan animasi pencarian AI secara langsung.

## 6. Hasil Uji di Laptop Masing-Masing

Setiap anggota menjalankan simulasi kompilasi C ini dan mengisi tabel berdasarkan **hasil nyata** di laptopnya.

| Nama | OS (versi) | Compiler | Cara instal/run | Berhasil? | Catatan / error yang ditemui | 
| ----- | ----- | ----- | ----- | ----- | ----- | 
| Achilles | Windows 11 | MinGW GCC | VS Code Terminal (`gcc`) | ✅ | Sempat bingung cara *run* di VS Code, namun teratasi dengan menggunakan terminal internal untuk kompilasi manual. Animasi *rendering* terminal berjalan lancar tanpa cacat. | 
| *(isi)* |  |  |  |  |  | 
| *(isi)* |  |  |  |  |  | 

## 7. Kendala yang Mungkin Muncul

| Gejala | Kemungkinan penyebab | Solusi | 
| ----- | ----- | ----- | 
| `'gcc' is not recognized as an internal or external command` | Compiler MinGW/GCC belum diinstal atau PATH sistem Windows belum diatur. | Instal MinGW, atau gunakan IDE *pre-packaged* seperti Code::Blocks / Dev-C++ yang sudah membawa compiler bawaan. | 
| Layar berkedip hebat saat animasi | OS mengeksekusi perintah `cls` (clear screen) terlalu cepat. | Buka `search_algo.c`, cari `SLEEP(50)` dan naikkan nilainya menjadi `SLEEP(100)` atau lebih. | 
| `Permission denied` saat di-run | (Khusus Linux/Mac) File hasil kompilasi belum memiliki izin eksekusi. | Ketik perintah `chmod +x search_algo` lalu jalankan ulang. | 

## 8. Struktur File

```
/
├── search_algo.c    # Kode sumber utama algoritma BFS dan animasi
├── README.md        # Dokumen deskripsi ini
└── search_algo.exe  # File biner hasil kompilasi (terbuat otomatis)


```

## 9. Referensi

* Konsep Breadth-First Search: <https://en.wikipedia.org/wiki/Breadth-first_search>

* Grid-based Pathfinding di AI: <https://www.redblobgames.com/pathfinding/a-star/introduction.html>

* C Standard Library: <https://en.cppreference.com/w/c/header>