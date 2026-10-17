# Search Algorithm — Grid Pathfinding Simulation (Python Version)

Proyek ini adalah bagian **Search Algorithm** dari tugas kelompok yang menggunakan implementasi **Breadth-First Search (BFS)** berbasis Python untuk pencarian jalur (*pathfinding*) pada lingkungan *grid* 2D di terminal.

---

## 1. Introduction

**Search Algorithm** (Algoritma Pencarian) adalah metode sistematis yang digunakan oleh agen cerdas untuk mengeksplorasi ruang masalah (*state space*) demi menemukan rute paling optimal dari titik awal ke titik tujuan, sekaligus menghindari rintangan dan *infinite loop*.

Simulasi ini menerapkan algoritma **Breadth-First Search (BFS)** pada sebuah *Grid Environment* 2D (labirin). Berbeda dengan DFS yang menelusuri satu jalur sampai buntu, BFS mengeksplorasi lingkungan secara radial (seperti gelombang air) ke segala arah secara bersamaan.

### Fitur Utama:

* **Lingkungan Grid:** Peta dua dimensi berbasis teks dengan rintangan (`#`).
* **Objek Dinamis:** Agen awal (`S`) dan Target (`T`).
* **Visualisasi Terminal:** Peta dirender ulang secara *real-time* menggunakan jeda waktu (*delay*) agar proses pencarian terlihat hidup.
* **Jaminan Jalur Terpendek:** Karena peta bersifat *unweighted* (jarak antar kotak seragam), BFS menjamin ditemukannya **rute mutlak terpendek** yang ditandai dengan simbol (`*`).

---

## 2. Requirement

Karena dibangun murni menggunakan **Python Standard Library** (tanpa modul eksternal seperti NumPy atau Pygame), prasyaratnya sangat ringan:

* **Python 3.x** terinstal di komputer.
* Terminal, Command Prompt, atau IDE (VS Code, PyCharm, dll.) yang mendukung pembersihan layar terminal.

Cek apakah Python sudah terpasang melalui terminal Anda:

```bash
python --version

```

*(Atau gunakan `python3 --version` tergantung sistem operasi Anda).*

---

## 3. How to Use

### A. Struktur File

Simpan kode program ke dalam satu file utama:

```text
/
├── search_algo.py    # Kode sumber utama BFS dan animasi grid
└── README.md         # Dokumentasi proyek

```

### B. Cara Menjalankan Program

Buka terminal pada direktori tempat file `search_algo.py` disimpan, lalu jalankan perintah berikut:

**Windows (PowerShell / CMD)**

```bash
python search_algo.py

```

**macOS / Linux**

```bash
python3 search_algo.py

```

### C. Komponen Program & Cara Kerja

| Komponen | Peran dalam Program |
| --- | --- |
| `grid` (Matriks List) | Representasi peta labirin tempat agen dan rintangan berada. |
| Agen `S` (Start) | Titik awal yang memicu antrean pencarian ke 4 arah (Atas, Bawah, Kiri, Kanan). |
| `deque` (Antrean FIFO) | Struktur data memori untuk mencatat kotak yang harus dieksplorasi berikutnya. |
| Fungsi Render | Membersihkan terminal secara berkala dan mencetak ulang matriks untuk efek animasi visual. |

---

## 4. Result

### A. Hasil yang Diharapkan

Saat program dijalankan di terminal, Anda akan melihat animasi peta labirin di mana simbol titik (`.`) menyebar dari posisi `S` untuk memindai area. Setelah jalur terhubung ke `T`, program berhenti memindai dan menggambar garis bintang (`*`) sebagai rute terpendek yang valid.

### B. Tabel Hasil Uji Coba Anggota Tim

Berikut adalah rekap hasil uji coba program di perangkat masing-masing anggota:

| Nama | OS (Versi) | Versi Python | Cara Menjalankan | Berhasil? | Catatan / Kendala |
| --- | --- | --- | --- | --- | --- |
| Achilles | Windows 11 | Python 3.11 | Terminal VS Code (`python search_algo.py`) | ✅ | Animasi *rendering* berjalan lancar. Penyesuaian waktu *sleep* diperlukan agar pergerakan gelombang BFS terlihat jelas di mata. |
| *(Isi Anggota)* | ... | ... | ... | ⬜ | ... |
| *(Isi Anggota)* | ... | ... | ... | ⬜ | ... |

### C. Kendala dan Solusi Umum

* **Perintah `python` tidak dikenali:** Pastikan Python sudah ditambahkan ke *Environment Variables* (PATH) saat instalasi di Windows, atau gunakan perintah `python3` di macOS/Linux.
* **Layar terminal berkedip terlalu cepat:** Buka file `search_algo.py`, cari fungsi jeda waktu (seperti `time.sleep(0.05)`), lalu sesuaikan durasinya menjadi sedikit lebih lambat (misal `0.1`) agar animasi lebih nyaman dilihat.
