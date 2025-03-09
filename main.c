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
        q->front = q->rear = newNasabah;
        return;
    }
    
    q->rear->next = newNasabah;
    q->rear = newNasabah;
}

// Fungsi dequeue (memproses nasabah dari antrean)
Nasabah* dequeue(Queue* q) {
    if (q->front == NULL) return NULL;
    
    Nasabah* temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    return temp;
}

// Fungsi push (menyimpan ke stack dengan waktu layanan)
void push(Stack* s, Nasabah* nasabah) {
    nasabah->waktu = time(NULL); // Mencatat waktu layanan
    nasabah->next = s->top;
    s->top = nasabah;
}

// Fungsi pop (mengambil data dari stack)
Nasabah* pop(Stack* s) {
    if (s->top == NULL) return NULL;
    
    Nasabah* temp = s->top;
    s->top = s->top->next;
    return temp;
}

// Menampilkan antrean saat ini
void displayQueue(Queue* q) {
    Nasabah* temp = q->front;
    int i = 1;
    printf("+------+-----------------------+---------------------+\n");
    printf("| No.  | Nama Nasabah          | Layanan             |\n");
    printf("+------+-----------------------+---------------------+\n");
    while (temp) {
