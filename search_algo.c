#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* --- Konfigurasi Sistem untuk Animasi --- */
#ifdef _WIN32
#include <windows.h> // Untuk Windows
#define SLEEP(ms) Sleep(ms)
#define CLEAR_SCREEN "cls"
#else
#include <unistd.h> // Untuk Mac/Linux
#define SLEEP(ms) usleep((ms) * 1000)
#define CLEAR_SCREEN "clear"
#endif

/* --- Konfigurasi Lingkungan (Environment) --- */
#define ROWS 10
#define COLS 20

// Simbol Objek dalam Grid (Mirip Objek di Westworld)
#define WALL '#'
#define EMPTY ' '
#define START 'S'
#define TARGET 'T'
#define VISITED '.'
#define PATH '*'

// Struktur Koordinat Agen
typedef struct {
    int r, c;
} Point;

// Peta / Grid Environment
char grid[ROWS][COLS] = {
    "####################",
    "#S   #             #",
    "#    #  ######     #",
    "#       #    #     #",
    "#####   #    #     #",
    "#       #    #     #",
    "#  ######    ####  #",
    "#            #T    #",
    "#            #     #",
    "####################"
};

// Arah pergerakan: Atas, Bawah, Kiri, Kanan
int dRow[] = {-1, 1, 0, 0};
int dCol[] = {0, 0, -1, 1};

/* --- Fungsi Visualisasi --- */
// Fungsi ini setara dengan env.render() di library MAS
void render_grid(int step) {
    system(CLEAR_SCREEN); // Bersihkan layar untuk efek animasi frame-by-frame
    
    printf("=== SIMULASI SEARCH ALGORITHM (BFS) ===\n");
    printf("Status: Agen sedang mencari rute... (Langkah: %d)\n", step);
    printf("Legenda: [S] Start, [T] Target, [#] Obstacle\n");
    printf("         [.] Jejak Pencarian, [*] Rute Ditemukan\n\n");

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%c ", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/* --- Mesin Utama: Breadth-First Search --- */
// Fungsi ini setara dengan sim.run_episode()
void run_simulation(Point start, Point target) {
    // Antrean (Queue) untuk mengatur langkah agen
    Point queue[ROWS * COLS];
    int front = 0, rear = 0;

    // Tracker jejak (Backtracking) dan memori kunjungan
    Point parent[ROWS][COLS];
    bool visited[ROWS][COLS] = {false};

    // Inisialisasi posisi awal agen
    queue[rear++] = start;
    visited[start.r][start.c] = true;
    parent[start.r][start.c] = (Point){-1, -1};

    bool found = false;
    int steps = 0;

    // Looping Simulasi Agen Bergerak
    while (front < rear) {
        Point current = queue[front++];

        // Jika agen menemukan makanan/target
        if (current.r == target.r && current.c == target.c) {
            found = true;
            break;
        }

        // Tandai jalur yang sedang dieksplorasi (Kecuali titik S dan T)
        if (grid[current.r][current.c] != START && grid[current.r][current.c] != TARGET) {
            grid[current.r][current.c] = VISITED;
            steps++;
            render_grid(steps);
            SLEEP(50); // Kecepatan animasi pencarian (50ms)
        }

        // Cek 4 arah (Mata Agen)
        for (int i = 0; i < 4; i++) {
            int newR = current.r + dRow[i];
            int newC = current.c + dCol[i];

            // Validasi: Apakah kotak di depannya kosong dan belum dikunjungi?
            if (newR >= 0 && newR < ROWS && newC >= 0 && newC < COLS && 
                !visited[newR][newC] && grid[newR][newC] != WALL) {
                
                queue[rear++] = (Point){newR, newC};
                visited[newR][newC] = true;
                parent[newR][newC] = current; // Ingat dari mana agen berasal
            }
        }
    }

    // --- REPLAY HASIL: Gambar Rute Terpendek ---
    if (found) {
        Point curr = parent[target.r][target.c];
        while (curr.r != start.r || curr.c != start.c) {
            grid[curr.r][curr.c] = PATH;
            curr = parent[curr.r][curr.c];
            render_grid(steps);
            SLEEP(100); // Kecepatan animasi menggambar jalur (100ms)
        }
        printf(">> [SUCCESS] Agen berhasil menemukan rute terpendek ke Target! <<\n");
    } else {
        printf(">> [FAILED] Agen terjebak, tidak ada jalan menuju Target. <<\n");
    }
}

int main() {
    // Setup Environment & Agent (Sesuai dengan peta)
    Point start = {1, 1};   // Posisi Agen (S)
    Point target = {7, 14}; // Posisi Target (T)

    // Render awal sebelum agen bergerak
    render_grid(0);
    printf("Persiapan simulasi dalam 2 detik...\n");
    SLEEP(2000); 

    // Jalankan mesin AI
    run_simulation(start, target);

    return 0;
}