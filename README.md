# Tugas AI - Search Algorithm (DFS)

## Deskripsi
Program ini adalah implementasi dari **Search Algorithm** menggunakan metode **Depth-First Search (DFS)** dalam bahasa C. Program akan mencari titik tujuan (target node) di dalam sebuah struktur graf/peta secara otomatis.

## Cara Menjalankan Program (Lokal)
1. Buka Terminal atau Command Prompt.
2. Masuk ke direktori tempat file `search_algo.c` disimpan.
3. Compile kode menggunakan perintah berikut:
   `gcc search_algo.c -o search_algo`
4. Jalankan program dengan perintah:
   - Untuk Windows: `.\search_algo.exe`
   - Untuk Mac/Linux: `./search_algo`

## Penjelasan Output (Logika Pencarian AI)
Setelah program berhasil di-*run*, Terminal akan menampilkan jejak penelusuran (*search trace*) berikut:

```text
=== Program Search Algorithm (AI) ===
Misi: Mencari Titik 4, dimulai dari Titik 0

Mengecek Titik (Node) 0...
Mengecek Titik (Node) 1...
Mengecek Titik (Node) 3...
Mengecek Titik (Node) 2...
Mengecek Titik (Node) 4...

>> Target Titik 4 DITEMUKAN! <<