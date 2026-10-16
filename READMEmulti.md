# Multi Agent System — Westworld

Proyek ini adalah bagian **Multi Agent System** dari tugas yang terdiri dari tiga topik:

| No | Topik | Status |
|----|-------|--------|
| 1 | Expert System | _(diisi anggota lain)_ |
| 2 | Search Algorithm | _(diisi anggota lain)_ |
| 3 | **Multi Agent System** | **Dokumen ini** |

Library yang dicoba: **[Westworld](https://github.com/TheoLvs/westworld)** oleh Théo Alves Da Costa (lisensi MIT).
Dokumentasi resmi: <https://theolvs.github.io/westworld>

---

## 1. Apa itu Multi Agent System?

Multi Agent System (MAS) adalah sistem yang terdiri dari banyak **agen** yang hidup dalam satu **lingkungan** dan saling berinteraksi. Setiap agen punya perilaku sendiri (misalnya mencari makanan, menghindar, atau berjalan acak), dan perilaku kolektif muncul dari interaksi antaragen tersebut.

## 2. Tentang Westworld

Westworld adalah library Python untuk mensimulasikan lingkungan dengan banyak agen. Terinspirasi dari Unity ML Agents, dengan target use case seperti logistik, retail, dan epidemiologi.

Fitur utama (menurut dokumentasi resmi):

- Lingkungan berbentuk grid maupun non-grid
- Objek: Agent, Obstacle, Collectible, Trigger
- Spawner untuk membuat objek secara acak di lingkungan
- Perilaku agen dasar: pathfinding, wandering, random walk, fleeing, vision range
- Pembuatan maze otomatis
- Visualisasi, replay, dan ekspor simulasi (GIF atau video)

> ⚠️ Library ini berstatus **eksperimental / alpha**. Dokumentasinya bisa saja tidak sepenuhnya mutakhir.

---

## 3. Prasyarat

- **Python 3.8 atau 3.9** (penting, lihat catatan di bawah)
- `pip` dan `git`
- Layar/desktop yang bisa menampilkan jendela (simulasi divisualisasikan dengan **PyGame**)

> **Catatan versi Python:** file `pyproject.toml` milik Westworld menetapkan `python = ">=3.8,<3.10"`, dengan dependensi seperti `pandas ^1.3`, `numpy ^1.21`, dan `pygame ^2.0`. Jika laptop memakai Python 3.10 ke atas, instalasi kemungkinan besar gagal. Solusinya: buat environment terpisah dengan Python 3.9 (lihat Opsi A atau B di bawah).

Cek versi Python di laptop:

```bash
python --version
```

---

## 4. Instalasi

### Opsi A — `venv` + `pip` (paling sederhana)

Pastikan Python 3.9 sudah terpasang, lalu:

**Windows (PowerShell / CMD)**

```bash
py -3.9 -m venv .venv
.venv\Scripts\activate
python -m pip install --upgrade pip
pip install westworld
pip install ipywidgets
```

**macOS / Linux**

```bash
python3.9 -m venv .venv
source .venv/bin/activate
python -m pip install --upgrade pip
pip install westworld
pip install ipywidgets
```

> **Kenapa ada `pip install ipywidgets`?** Westworld meng-import `ipywidgets` di kodenya, tetapi library itu tidak ikut terinstal otomatis oleh `pip install westworld`. Tanpa ini, simulasi gagal dengan `ModuleNotFoundError: No module named 'ipywidgets'` (ditemukan saat uji di Windows, Python 3.9.13).

### Opsi B — Conda (disarankan jika Python 3.9 belum terpasang)

```bash
conda create -n westworld python=3.9 -y
conda activate westworld
pip install westworld
pip install ipywidgets
```

### Opsi C — Clone repo + Poetry (untuk melihat/mengubah kode sumber)

```bash
git clone https://github.com/TheoLvs/westworld.git
cd westworld
pip install poetry
poetry install

# jalankan Jupyter Notebook atau console Python
poetry run jupyter notebook
poetry run python
```

### Cek instalasi

```bash
python -c "import westworld; print('Westworld berhasil di-import')"
```

---

## 5. Menjalankan Simulasi

Contoh di bawah diambil dari *Quickstart* dokumentasi resmi: ekosistem **kelinci** yang saling berkompetisi mencari **makanan**.

Simpan sebagai `quickstart.py`:

```python
from westworld.environment import GridEnvironment
from westworld.agents import BaseAgent
from westworld.objects import BaseCollectible
from westworld.simulation import Simulation
from westworld.colors import *

class Food(BaseCollectible):
    pass

class Rabbit(BaseAgent):

    def __init__(self, x, y, curiosity=5):
        super().__init__(x, y, color=(229, 229, 229), curiosity=curiosity)

    def step(self):
        # Cari makanan terdekat
        targets = self.find_closest(name="Food", k=1)

        # Jika masih ada makanan, bergerak menuju makanan
        if len(targets) > 0:
            target = targets[0]
            self.move_towards(obj=target, naive=True)

        # Jika tidak, berkeliaran (ganti arah setiap n langkah, n = curiosity)
        else:
            self.wander()

food_spawner = lambda x, y: Food(x, y, color=(220, 150, 50), img_asset="ball")
rabbit_spawner = lambda x, y: Rabbit(x, y, curiosity=5)

# Setup environment
env = GridEnvironment(20, 10, 20, show_grid=True,
                      background_color=(102, 178, 102),
                      grid_color=(127, 191, 127),
                      toroidal=True)
env.spawn(rabbit_spawner, 3)    # 3 kelinci
env.spawn(food_spawner, 20)     # 20 makanan
env.render()

# Jalankan simulasi
sim = Simulation(env, fps=10, name="Quickstart")
_, _ = sim.run_episode(n_steps=50, save=True, replay=True, save_format="gif")
```

Jalankan:

```bash
python quickstart.py
```

### Cara kerja singkat

| Komponen | Peran |
|----------|-------|
| `GridEnvironment` | Lingkungan grid tempat semua objek berada |
| `Rabbit` (agen) | Setiap langkah (`step`) mencari makanan terdekat lalu mendekatinya; jika makanan habis, berkeliaran |
| `Food` (collectible) | Objek yang bisa diambil agen |
| `Simulation` | Menjalankan episode simulasi, menyimpan dan me-replay hasilnya |

### Hasil yang diharapkan

Muncul jendela PyGame berisi 3 kelinci putih yang mengejar bola makanan oranye di latar hijau selama 50 langkah, lalu hasilnya disimpan sebagai GIF.

<!-- ISI: tempel screenshot/GIF hasil run di laptop kalian, contoh: -->
<!-- ![Hasil simulasi](docs/hasil_simulasi.gif) -->

---

## 6. Hasil Uji di Laptop Masing-Masing

Setiap anggota menjalankan langkah di atas dan mengisi tabel ini berdasarkan **hasil nyata** di laptopnya.

| Nama | OS (versi) | Versi Python | Cara instal (A/B/C) | Berhasil? | Catatan / error yang ditemui |
|------|------------|--------------|---------------------|-----------|------------------------------|
| Zeta Audriana Alifta | Windows _(isi versi)_ | 3.9.13 | A (`venv` + `pip`) | ✅ | Awalnya error `No module named 'ipywidgets'`; teratasi dengan `pip install ipywidgets`. Laptop sebelumnya memakai Python 3.14, jadi Python 3.9 dipasang berdampingan dan dipanggil lewat `py -3.9`. |
| _(isi)_ | | | | | |
| _(isi)_ | | | | | |

---

## 7. Kendala yang Mungkin Muncul

Bagian ini berisi dugaan kendala berdasarkan persyaratan versi library. **Perbarui dengan error yang benar-benar kalian temui.**

| Gejala | Kemungkinan penyebab | Solusi |
|--------|----------------------|--------|
| `No matching distribution found for westworld` atau error saat membangun `numpy`/`pandas`/`pygame` | Python terlalu baru (≥ 3.10) | Buat environment dengan Python 3.9 (Opsi A/B) |
| `ModuleNotFoundError: No module named 'ipywidgets'` saat `python quickstart.py` (**terjadi saat uji nyata**) | Dependensi `ipywidgets` tidak ikut terinstal oleh `pip install westworld` | `pip install ipywidgets`, lalu jalankan ulang |
| `ModuleNotFoundError: No module named 'westworld'` | Environment belum diaktifkan | Aktifkan `venv`/`conda` lalu ulangi `pip install westworld` |
| Jendela PyGame tidak muncul / error display | Dijalankan di server atau lingkungan tanpa layar (misalnya Google Colab) | Jalankan di laptop dengan desktop |
| Gagal menyimpan video (bukan GIF) | `ffmpeg` belum terpasang | Pasang `ffmpeg` dan pastikan ada di PATH, atau gunakan `save_format="gif"` |
| `poetry: command not found` | Poetry belum terpasang | `pip install poetry` |

---

## 8. Struktur Repo Sumber (ringkas)

```
westworld/
├── westworld/     # kode utama library
├── examples/      # contoh simulasi
├── notebooks/     # Jupyter notebook
├── docs/          # dokumentasi (mkdocs)
├── tests/         # unit test
├── pyproject.toml # konfigurasi Poetry & dependensi
└── requirements.txt
```

---

## 9. Referensi

- Repositori: <https://github.com/TheoLvs/westworld>
- Dokumentasi: <https://theolvs.github.io/westworld>
- Paket PyPI: <https://pypi.org/project/westworld/>
- Tutorial resmi: [Quickstart](https://theolvs.github.io/westworld/tutorials/quickstart/), [Movements](https://theolvs.github.io/westworld/tutorials/movements/), [Objects](https://theolvs.github.io/westworld/tutorials/objects/), [Maze generation](https://theolvs.github.io/westworld/tutorials/maze/)
