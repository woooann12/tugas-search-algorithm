# Search Algorithm — Grid Pathfinding Simulation

Proyek ini adalah bagian **Search Algorithm** dari tugas yang terdiri dari tiga topik:

| No | Topik | Status |
|----|-------|--------|
| 1 | Expert System | _(diisi anggota lain)_ |
| 2 | **Search Algorithm** | **Dokumen ini** |
| 3 | Multi Agent System | _(diisi anggota lain)_ |

Sistem ini dikembangkan secara murni menggunakan standar **Bahasa C**, mendemonstrasikan bagaimana sebuah agen mensimulasikan pemetaan lingkungan secara *real-time* untuk mencari rute terpendek dari satu titik ke titik lain.

---

## 1. Apa itu Search Algorithm?

Dalam konteks kecerdasan buatan, **Search Algorithm** adalah metode sistematis yang digunakan oleh agen (atau mesin) untuk menelusuri serangkaian *state* (titik/kondisi) demi menemukan solusi paling optimal. Berbeda dengan agen *random walk*, agen berbasis pencarian menggunakan memori dan antrean prioritas untuk menjamin penemuan target. Ini adalah fondasi dari GPS routing dan *pathfinding* NPC dalam *video game*.

## 2. Tentang Simulasi Ini

Program ini mensimulasikan **Grid Environment 2D**, di mana sebuah agen otonom mencari target/makanan. Berbeda dengan DFS biasa, algoritma yang digunakan di sini adalah **Breadth-First Search (BFS)** dengan fitur visualisasi.

Fitur utama simulasi:
- **Environment Rendering:** Peta (*Grid*) dirender secara *frame-by-frame* di terminal/konsol.
- **Entity Objects:** Memiliki objek Agen (`S`), Target (`T`), dan Rintangan/Dinding (`#`).
- **Exploration Trace:** Menampilkan animasi gelombang pencarian agen yang menyebar (disimbolkan dengan titik `.`).
- **Optimal Pathing:** Menggunakan mekanisme *backtracking* untuk menggambar rute tercepat (disimbolkan dengan bintang `*`) tepat setelah target ditemukan.

> 💡 **Kenapa menggunakan BFS?** Pada peta *unweighted* (jarak antar blok sama), BFS secara matematis menjamin agen selalu menemukan **rute paling terpendek**, menjadikannya standar industri yang lebih reliabel dibandingkan DFS untuk kasus tata ruang spasial.

---

## 3. Prasyarat

- **Compiler Bahasa C** (GCC, Clang, atau MinGW).
- Terminal atau Command Prompt standar.
- Layar terminal yang mendukung pembersihan layar bawaan OS.

Cek apakah compiler C sudah terpasang di laptop Anda:
```bash
gcc --version
```

---

## 4. Instalasi dan Kompilasi

Karena ini adalah kode *native* C, tidak diperlukan *virtual environment* tambahan seperti Python.

### Opsi A — Melalui Terminal (Windows/macOS/Linux)

Pastikan file `maze_search.c` berada di direktori aktif Anda.

**Kompilasi:**
```bash
gcc maze_search.c -o maze_search
```

> **Catatan Dependensi Sistem:** Kode ini memiliki makro deteksi OS cerdas (`#ifdef _WIN32`). Ia akan otomatis memilih *header* yang tepat (`windows.h` atau `unistd.h`) untuk merender animasi `Sleep()`, sehingga 100% aman dikompilasi di OS apapun tanpa perlu mengubah baris kode.

### Opsi B — Menggunakan IDE (VS Code / Dev-C++)

1. Buka file `maze_search.c` di IDE Anda.
2. Gunakan fitur *Run* atau *Compile & Run* bawaan (tombol *Play* di VS Code, atau `F11` di Dev-C++).

---

## 5. Menjalankan Simulasi

Setelah file kompilasi terbentuk, jalankan perintah ini di terminal:

**Windows (PowerShell / CMD)**
```bash
.\maze_search.exe
```

**macOS / Linux**
```bash
./maze_search
```

### Analisis Cara Kerja Sistem (Komparasi dengan MAS/Westworld)

| Komponen C | Padanan dalam MAS | Peran dalam Simulasi |
|------------|-------------------|----------------------|
| Array `char grid[][]` | `GridEnvironment` | Matriks 2D ruang tempat objek dan rintangan berada. |
| Fungsi `run_simulation()` | `Simulation.run_episode()` | Loop kehidupan (*step*) di mana agen mengambil keputusan. |
| Array `queue` | `Agent.step()` Memory | Antrean FIFO untuk menavigasi agen menyebar ke segala arah. |
| Fungsi `render_grid()` | `env.render()` | Menghapus frame lama dan mencetak ulang matriks untuk menciptakan efek animasi visual. |

### Hasil yang Diharapkan
1. Terminal akan menampilkan peta labirin.
2. Titik `.` akan muncul menjalar seperti air dari agen (`S`), menunjukkan proses mesin "berpikir" dan memindai rute yang valid.
3. Begitu target (`T`) bersentuhan dengan gelombang, program berhenti memindai dan langsung menarik garis tegas `*` ke belakang untuk membentuk rute paling optimal.

---

## 6. Hasil Uji di Laptop Masing-Masing

Setiap anggota wajib menjalankan kompilasi di atas dan mendokumentasikan hasilnya.

| Nama | OS (versi) | Compiler | Cara instal/run | Berhasil? | Catatan / Error yang ditemui |
|------|------------|----------|-----------------|-----------|------------------------------|
| _(Nama Kamu)_ | Windows _(isi)_ | MinGW GCC | VS Code Terminal | ✅ | Berjalan sempurna. Animasi pencarian agen dan rendering rute *frame-by-frame* muncul tanpa cacat di terminal. |
| _(isi)_ | | | | | |
| _(isi)_ | | | | | |

---

## 7. Kendala yang Mungkin Muncul

Bagian ini memuat error yang paling umum terjadi berdasarkan manajemen lingkungan OS.

| Gejala | Kemungkinan Penyebab | Solusi |
|--------|----------------------|--------|
| `'gcc' is not recognized` | Compiler GCC belum dipasang atau belum didaftarkan di *Environment Variables (PATH)*. | Pasang MinGW (Windows), atau jalankan via IDE yang *pre-bundled* dengan compiler. |
| Animasi berkedip terlalu cepat/parah | Eksekusi `system("cls")` terlalu agresif oleh terminal modern. | Buka file C, tambah angka pada fungsi `SLEEP(50)` menjadi `SLEEP(150)`. |
| `Permission denied` saat di-*run* (Linux/Mac) | Berkas *binary* hasil kompilasi belum diberi akses eksekusi. | Ketik: `chmod +x maze_search` lalu eksekusi ulang. |

---

## 8. Struktur File

```text
/
├── maze_search.c    # Kode sumber utama agen pencari
├── README.md        # Dokumen deskripsi ini
└── maze_search.exe  # (Akan ter-generate otomatis saat proses GCC)
```