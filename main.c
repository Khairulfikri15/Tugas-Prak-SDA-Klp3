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
        printf("| %-4d | %-21s | %-19s |\n", i++, temp->nama, temp->layanan);
        temp = temp->next;
    }
    printf("+------+-----------------------+---------------------+\n");
}

// Fungsi untuk menampilkan riwayat layanan dengan waktu
void displayStack(Stack* s) {
    Nasabah* temp = s->top;
    int i = 1;
    printf("+------+-----------------------+---------------------+----------------------+\n");
    printf("| No.  | Nama Nasabah          | Layanan             | Waktu Layanan        |\n");
    printf("+------+-----------------------+---------------------+----------------------+\n");
    while (temp) {
        char waktuStr[20];
        struct tm* timeinfo = localtime(&temp->waktu);
        strftime(waktuStr, sizeof(waktuStr), "%d-%m-%Y %H:%M:%S", timeinfo);
        printf("| %-4d | %-21s | %-19s | %-20s |\n", i++, temp->nama, temp->layanan, waktuStr);
        temp = temp->next;
    }
    printf("+------+-----------------------+---------------------+----------------------+\n");
}

// Fungsi untuk membatalkan transaksi terakhir (Undo)
void undoTransaction(Stack* s, Queue* q) {
    Nasabah* last = pop(s);
    if (last) {
        enqueue(q, last->nama, last->layanan);
        printf("Transaksi %s - %s dibatalkan dan dikembalikan ke antrean.\n", last->nama, last->layanan);
    } else {
        printf("Tidak ada transaksi yang bisa dibatalkan.\n");
    }
}

int main() {
    Queue antrean;
    Stack riwayat;
    initQueue(&antrean);
    initStack(&riwayat);
    
    int pilihan;
    char nama[50];
