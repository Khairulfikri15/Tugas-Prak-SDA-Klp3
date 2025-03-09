#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Struktur untuk menyimpan data nasabah
typedef struct Nasabah {
    char nama[50];
    char layanan[50];
    time_t waktu; // Menyimpan waktu layanan
    struct Nasabah* next;
} Nasabah;

// Struktur antrean (Queue)
typedef struct {
    Nasabah* front;
    Nasabah* rear;
} Queue;

// Struktur riwayat layanan (Stack)
typedef struct Stack {
    Nasabah* top;
} Stack;

// Inisialisasi antrean
void initQueue(Queue* q) {
    q->front = q->rear = NULL;
}

// Inisialisasi stack
void initStack(Stack* s) {
    s->top = NULL;
}

// Fungsi enqueue (menambahkan nasabah ke antrean)
void enqueue(Queue* q, char* nama, char* layanan) {
    Nasabah* newNasabah = (Nasabah*)malloc(sizeof(Nasabah));
    strcpy(newNasabah->nama, nama);
    strcpy(newNasabah->layanan, layanan);
    newNasabah->next = NULL;
    
    if (q->rear == NULL) {
