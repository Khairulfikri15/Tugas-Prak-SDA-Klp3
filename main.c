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
    int layananPilihan;
    char layanan[50];
    
    do {
        printf("\n+---------------------------------------+\n");
        printf("|        SISTEM ANTREAN BANK            |\n");
        printf("+---------------------------------------+\n");
        printf("| 1. Tambah Nasabah ke Antrean          |\n");
        printf("| 2. Proses Nasabah                     |\n");
        printf("| 3. Tampilkan Antrean Saat Ini         |\n");
        printf("| 4. Tampilkan Riwayat Layanan          |\n");
        printf("| 5. Batalkan Transaksi Terakhir (Undo) |\n");
        printf("| 6. Keluar                             |\n");
        printf("+---------------------------------------+\n");
        
        while (1) {
            printf("  Pilihan Anda: ");
            if (scanf("%d", &pilihan) != 1 || pilihan < 1 || pilihan > 6) {
                printf("\nPilihan tidak valid! Silakan pilih angka antara 1 hingga 6.\n");
                while (getchar() != '\n'); // Membersihkan buffer input
            } else {
                break;
            }
        }

        getchar(); // Membersihkan newline dari buffer
        
        switch (pilihan) {
            case 1:
                printf("Masukkan nama nasabah: ");
                fgets(nama, 50, stdin);
                nama[strcspn(nama, "\n")] = 0;
                
                while (1) {
                    printf("Pilih jenis layanan:\n  1. Setor Tunai\n  2. Tarik Tunai\n  3. Pembukaan Rekening\nPilihan (1-3): ");
                    if (scanf("%d", &layananPilihan) != 1 || layananPilihan < 1 || layananPilihan > 3) {
                        printf("\nPilihan tidak valid! Silakan pilih angka antara 1 hingga 3.\n");
                        while (getchar() != '\n'); // Membersihkan buffer input
                    } else {
                        break;
                    }
                }
                getchar();
                
                if (layananPilihan == 1) strcpy(layanan, "Setor Tunai");
                else if (layananPilihan == 2) strcpy(layanan, "Tarik Tunai");
                else strcpy(layanan, "Pembukaan Rekening");
                
                enqueue(&antrean, nama, layanan);
                printf("Nasabah %s berhasil ditambahkan ke antrean dengan layanan %s.\n", nama, layanan);
                break;
            
            case 2:
                {
                    Nasabah* nasabah = dequeue(&antrean);
                    if (nasabah) {
                        printf("Memproses nasabah: %s - %s\n", nasabah->nama, nasabah->layanan);
                        push(&riwayat, nasabah);
                        printf("Layanan selesai diproses dan dipindahkan ke riwayat.\n");
                    } else {
                        printf("Antrean kosong.\n");
                    }
                }
                break;
            
            case 3:
                displayQueue(&antrean);
                break;
            
            case 4:
                displayStack(&riwayat);
                break;
                
            case 5:
                undoTransaction(&riwayat, &antrean);
                break;
                
            case 6:
                system("cls");
                printf("Terima kasih telah menggunakan sistem antrean bank.\n");
                break;
        }
    } while (pilihan != 6);
    
    return 0;
}
