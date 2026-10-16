#include <stdio.h>
int graph[5][5] = {
    {0, 1, 1, 0, 0}, 
    {1, 0, 0, 1, 0}, 
    {1, 0, 0, 0, 1}, 
    {0, 1, 0, 0, 0}, 
    {0, 0, 1, 0, 0}  
};

int visited[5] = {0, 0, 0, 0, 0}; 
int found = 0; 

void DFS(int node, int target) {
    if (found == 1) return; 
    
    printf("Mengecek Titik (Node) %d...\n", node);
    visited[node] = 1;

    if (node == target) {
        printf("\n>> Target Titik %d DITEMUKAN! <<\n", target);
        found = 1;
        return;
    }

    for (int i = 0; i < 5; i++) {
        if (graph[node][i] == 1 && visited[i] == 0) {
            DFS(i, target); 
        }
    }
}

int main() {
    printf("=== Program Search Algorithm (AI) ===\n");
    printf("Misi: Mencari Titik 4, dimulai dari Titik 0\n\n");
    
    int start_node = 0;
    int target_node = 4;
    
    DFS(start_node, target_node);
    
    return 0;
}