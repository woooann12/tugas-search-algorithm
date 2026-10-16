# Expert System — Experta (Diagnosa Laptop)

Proyek ini adalah bagian **Expert System** dari tugas yang terdiri dari tiga topik:

| No | Topik | Status |
|----|-------|--------|
| 1 | **Expert System** | **Dokumen ini** |
| 2 | Search Algorithm | _(diisi anggota lain)_ |
| 3 | Multi Agent System | Lihat README Westworld (terpisah) |

Library yang dipakai: **[Experta](https://pypi.org/project/experta/)**, library Python untuk membangun expert system.

---

## 1. Apa itu Expert System?

Expert System adalah program yang meniru cara seorang pakar mengambil keputusan. Pengetahuan pakar ditulis dalam bentuk **aturan** `JIKA ... MAKA ...`, lalu program mencocokkan **fakta** yang diketahui dengan aturan-aturan itu untuk menghasilkan kesimpulan atau diagnosa.

Komponen utamanya:

| Komponen | Fungsi |
|----------|--------|
| **Knowledge base** (basis pengetahuan) | Kumpulan aturan `JIKA-MAKA` |
| **Working memory** (memori kerja) | Fakta yang diketahui saat ini |
| **Inference engine** (mesin inferensi) | Mencocokkan fakta dengan aturan dan menjalankan aturan yang cocok |
| **User interface** | Cara pengguna memasukkan fakta dan melihat hasil |

## 2. Tentang Experta

Experta adalah library Python untuk membangun expert system yang banyak terinspirasi dari CLIPS, dan merupakan fork dari PyKnow. Aturan ditulis sebagai method Python dengan dekorator `@Rule`, fakta direpresentasikan dengan `Fact`, dan mesinnya adalah `KnowledgeEngine`.

- Halaman paket: <https://pypi.org/project/experta/>
- Tautan repositori GitHub dan contoh lainnya tersedia di halaman PyPI tersebut.

## 3. Studi Kasus: Diagnosa Laptop

Program menanyakan kondisi laptop kepada pengguna, lalu memberi diagnosa kemungkinan penyebab masalah.

### Basis aturan

| No | JIKA (kondisi) | MAKA (diagnosa) |
|----|----------------|-----------------|
| 1 | Laptop tidak menyala **dan** lampu charger mati | Adaptor/charger atau stop kontak bermasalah |
| 2 | Laptop tidak menyala **dan** lampu charger menyala | Baterai atau motherboard kemungkinan bermasalah |
| 3 | Laptop menyala **dan** layar gelap | Layar atau kabel layar kemungkinan bermasalah |
| 4 | Laptop menyala **dan** layar normal **dan** sangat panas | Pendinginan kurang baik (kipas/lubang udara kotor) |
| 5 | Laptop menyala **dan** layar normal **dan** tidak panas | Tidak ada masalah terdeteksi |

> Aturan di atas adalah contoh sederhana untuk keperluan pembelajaran, bukan pengganti teknisi.

---

## 4. Prasyarat

- **Python 3.9** (disarankan, sama dengan proyek Multi Agent System). Kompatibilitas Experta dengan versi Python yang lebih baru belum diuji di proyek ini.
- `pip`
- Terminal: CMD (Windows), Terminal (macOS/Linux)

Cek versi Python:

```bash
python --version
```

> Jika laptop memakai Python versi lain (misalnya 3.14), pasang Python 3.9 berdampingan dan panggil dengan `py -3.9` di Windows.

---

## 5. Instalasi

### Windows (CMD)

Jalankan **satu per satu**:

```bat
cd %USERPROFILE%\Documents
mkdir proyek-expert
cd proyek-expert
py -3.9 -m venv .venv
.venv\Scripts\activate
python -m pip install --upgrade pip
pip install experta
```

### macOS / Linux

```bash
mkdir proyek-expert && cd proyek-expert
python3.9 -m venv .venv
source .venv/bin/activate
python -m pip install --upgrade pip
pip install experta
```

### Cek instalasi

```bash
python -c "import experta; print('Experta berhasil di-import')"
```

---

## 6. Menjalankan Program

### 6.1 Contoh resmi: lampu lalu lintas (`lampu.py`)

Contoh ini diambil dari dokumentasi Experta untuk memastikan library berjalan di laptop.

```python
from random import choice
from experta import *


class Light(Fact):
    """Info about the traffic light."""
    pass


class RobotCrossStreet(KnowledgeEngine):
    @Rule(Light(color='green'))
    def green_light(self):
        print("Walk")

    @Rule(Light(color='red'))
    def red_light(self):
        print("Don't walk")

    @Rule(AS.light << Light(color=L('yellow') | L('blinking-yellow')))
    def cautious(self, light):
        print("Be cautious because light is", light["color"])


engine = RobotCrossStreet()
engine.reset()
engine.declare(Light(color=choice(['green', 'yellow', 'blinking-yellow', 'red'])))
engine.run()
```

```bash
python lampu.py
```

Hasilnya satu dari tiga keluaran ("Walk", "Don't walk", atau "Be cautious ...") tergantung warna lampu yang dipilih acak.

### 6.2 Program utama: diagnosa laptop (`diagnosa_laptop.py`)

```python
from experta import *


class DiagnosaLaptop(KnowledgeEngine):

    @Rule(Fact(menyala="tidak"), Fact(lampu_charger="mati"))
    def charger_bermasalah(self):
        print("Diagnosa: adaptor/charger atau stop kontak bermasalah. Coba ganti adaptor atau colokan lain.")

    @Rule(Fact(menyala="tidak"), Fact(lampu_charger="menyala"))
    def baterai_atau_motherboard(self):
        print("Diagnosa: baterai atau motherboard kemungkinan bermasalah. Bawa ke teknisi.")

    @Rule(Fact(menyala="ya"), Fact(layar="gelap"))
    def layar_bermasalah(self):
        print("Diagnosa: layar atau kabel layar kemungkinan bermasalah. Coba sambungkan monitor eksternal.")

    @Rule(Fact(menyala="ya"), Fact(layar="normal"), Fact(panas="ya"))
    def terlalu_panas(self):
        print("Diagnosa: pendinginan kurang baik. Bersihkan kipas dan lubang udara.")

    @Rule(Fact(menyala="ya"), Fact(layar="normal"), Fact(panas="tidak"))
    def normal(self):
        print("Diagnosa: tidak ada masalah terdeteksi.")


def tanya(pertanyaan, pilihan):
    while True:
        jawab = input(f"{pertanyaan} ({'/'.join(pilihan)}): ").strip().lower()
        if jawab in pilihan:
            return jawab
        print("Jawaban tidak valid, coba lagi.")


engine = DiagnosaLaptop()
engine.reset()

menyala = tanya("Apakah laptop menyala?", ["ya", "tidak"])
engine.declare(Fact(menyala=menyala))

if menyala == "tidak":
    engine.declare(Fact(lampu_charger=tanya("Lampu charger", ["menyala", "mati"])))
else:
    engine.declare(Fact(layar=tanya("Kondisi layar", ["normal", "gelap"])))
    engine.declare(Fact(panas=tanya("Apakah laptop sangat panas?", ["ya", "tidak"])))

engine.run()
```

```bash
python diagnosa_laptop.py
```

### Contoh interaksi

Contoh berikut diturunkan dari logika aturan di atas. **Ganti dengan screenshot hasil run di laptop kalian.**

```
Apakah laptop menyala? (ya/tidak): tidak
Lampu charger (menyala/mati): mati
Diagnosa: adaptor/charger atau stop kontak bermasalah. Coba ganti adaptor atau colokan lain.
```

<!-- ISI: tempel screenshot hasil run, contoh: -->
<!-- ![Hasil diagnosa](docs/hasil_diagnosa.png) -->

---

## 7. Cara Kerja

| Komponen | Di kode |
|----------|---------|
| Knowledge base | Kumpulan `@Rule` di class `DiagnosaLaptop` |
| Working memory | `Fact(...)` yang di-`declare` dari jawaban pengguna |
| Inference engine | `KnowledgeEngine`, dijalankan dengan `engine.run()` |
| User interface | Fungsi `tanya()` yang memakai `input()` |

Alur program:

1. `engine.reset()` menyiapkan mesin dalam keadaan bersih.
2. Program menanyakan kondisi laptop, lalu jawaban dimasukkan sebagai fakta dengan `engine.declare(Fact(...))`.
3. `engine.run()` mencocokkan fakta dengan semua aturan. Aturan yang kondisinya terpenuhi akan dijalankan dan mencetak diagnosa.

Metode penalarannya **forward chaining**, yaitu dari fakta menuju kesimpulan, seperti pada CLIPS yang menjadi inspirasi Experta.

Pada versi ini, urutan pertanyaan diatur oleh `if` biasa di Python, bukan oleh aturan.

---

## 8. Hasil Uji di Laptop Masing-Masing

Setiap anggota menjalankan langkah di atas dan mengisi tabel berdasarkan **hasil nyata**.

| Nama | OS (versi) | Versi Python | `lampu.py` | `diagnosa_laptop.py` | Catatan / error yang ditemui |
|------|------------|--------------|------------|----------------------|------------------------------|
| _(isi)_ | _(contoh: Windows 11)_ | _(contoh: 3.9.13)_ | ✅ / ❌ | ✅ / ❌ | _(isi)_ |
| _(isi)_ | | | | | |
| _(isi)_ | | | | | |

---

## 9. Kendala yang Mungkin Muncul

Berikut dugaan kendala. **Perbarui dengan error yang benar-benar kalian temui.**

| Gejala | Kemungkinan penyebab | Solusi |
|--------|----------------------|--------|
| `ModuleNotFoundError: No module named 'experta'` | Environment belum aktif, sehingga Python bawaan laptop yang dipakai | Aktifkan dengan `.venv\Scripts\activate`, lalu ulangi |
| Error saat `pip install experta` | Versi Python tidak cocok | Gunakan Python 3.9 (`py -3.9 -m venv .venv`) |
| `The system cannot find the path specified` | Belum berada di folder proyek | `cd` ke folder `proyek-expert`, cek isinya dengan `dir` |
| Program meminta jawaban terus-menerus | Jawaban tidak sesuai pilihan | Ketik persis salah satu pilihan di dalam kurung, misalnya `ya` atau `tidak` |
| Tidak ada diagnosa yang muncul | Kombinasi fakta tidak cocok dengan aturan mana pun | Periksa ejaan nilai di `@Rule` dan di `tanya(...)` |

---

## 10. Struktur Folder

```
proyek-expert/
├── .venv/               # environment Python (jangan di-commit ke GitHub)
├── lampu.py             # contoh resmi Experta
├── diagnosa_laptop.py   # expert system diagnosa laptop
└── README.md
```

---

## 11. Ide Pengembangan

- Tambah aturan dan gejala lain (misalnya suara kipas, bunyi beep saat menyala, kondisi baterai).
- Pindahkan logika bertanya ke dalam aturan agar seluruh alur dikendalikan mesin inferensi.
- Tambahkan tingkat keyakinan (certainty factor) pada tiap diagnosa.
- Buat antarmuka grafis atau web agar tidak memakai terminal.

---

## 12. Referensi

- Experta di PyPI: <https://pypi.org/project/experta/>
