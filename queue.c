#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>

/**
 * Persyaratan
 *  - Membuat konsumen queue
 *  - Buat simulasi konsumen masuk antrian
 *  - Buat simulasi konsumen keluar antrian
 *
 * Asumsi
 *  - Simulasi dibuat untuk keperluan antrian dari aplikasi admin.
 *  - Konsumen keluar antrian disini artinya konsumen telah mendapat gilirannya
 *      dan bukan berhenti / keluar dari antrian.
 *  - Data konsumen hanya terdiri dari nomor antrian dan nama.
 *      - Input nama, max 100 char.
 *      - Nomor antrian akan digenerate otomatis.
 *  - Memiliki menu dengan pilihan
 *      - Menampilkan daftar dan jumlah antrian saat ini
 *      - Menambahkan konsumen ke dalam antrian (simulasi masuk antrian)
 *      - Panggil konsumen berikutnya (simulasi keluar antrian)
 *      - Menampilkan konsumen yang sedang gilirannya (data konsumen ditampung di variabel lain)
 *          - bertujuan agar sementara data konsumen masih ada meskipun pindah-pindah menu
 *          - juga agar proses free memori pada simulasi keluar antrian tetap ada
 *          - data ini akan terhapus ketika admin memanggil konsumen berikutnya
 *            sedangkan data antrian sudah habis (yang berarti admin bisa idle).
 *      - Keluar
 *
 */

// menu program
typedef enum command {
    ASK,
    ADD,
    PRINT_QUEUE,
    NEXT,
    PRINT_CURRENT,
    EXIT,
} CMD;

// feature related data structure
#define MAX_NAME 101

typedef struct node {
    int order_num;
    char name[MAX_NAME];

    struct node *next;
} Node;

typedef struct queue {
    Node *front;
    Node *rear;
} Queue;

// initiate data
Queue *que = NULL;
int order_num = 0;
int curr_user_order_num = 0;
char curr_user_name[MAX_NAME] = "";

// menu functionality
void clrscr();
void flush_stream(FILE *stream);
void continue_or_back_to_menu(CMD *c, bool is_back_to_menu);
void ask(CMD *c);

// feature functionality
void add_user(CMD *c);
void print_queue(CMD *c);
void next_user(CMD *c);
void print_current_user(CMD *c);

int main() {
    clrscr();

    CMD c = ASK;

    while (c != EXIT) {
        switch (c) {
            case ASK:
                ask(&c);
                break;
            case ADD:
                add_user(&c);
                break;
            case PRINT_QUEUE:
                print_queue(&c);
                break;
            case PRINT_CURRENT:
                print_current_user(&c);
                break;
            case NEXT:
                next_user(&c);
                break;
            case EXIT:
                return 0;
        }
    }

    return 0;
}

void clrscr() {
    system("clear");
}

void flush_stream(FILE *stream) {
    char c;
    while ((c = fgetc(stream)) != '\n' && c != EOF);
}

void ask(CMD *c) {
    clrscr();

    printf(" ------------------- MENU --------------------\n");
    printf("1. Tambah antrian\n");
    printf("2. Tampilkan daftar antrian\n");
    printf("3. Tampilkan info konsumen yang dilayani saat ini\n");
    printf("4. Panggil konsumen / antrian berikutnya\n");
    printf("5. Keluar Program\n");
    printf(" ---------------------------------------------\n");
    printf("Apa yang ingin Anda lakukan? ");

    char t;
    if (scanf("%c", &t) != 1) {
        printf("Terjadi kesalahan input, pastikan hanya input 1, 2, 3, 4, atau 5.\n");
        flush_stream(stdin);
        return;
    }
    flush_stream(stdin);

    switch (t) {
        case '1':
            *c = ADD;
            break;
        case '2':
            *c = PRINT_QUEUE;
            break;
        case '3':
            *c = PRINT_CURRENT;
            break;
        case '4':
            *c = NEXT;
            break;
        case '5':
            *c = EXIT;
            break;
        default:
            printf("Terjadi kesalahan input, hanya bisa input 1, 2, 3, 4, atau 5 yang valid\n");
    }
}

void continue_or_back_to_menu(CMD *c, bool is_back_to_menu) {
    if (is_back_to_menu) {
        printf("Tekan enter untuk lanjut.");
        getc(stdin);
        *c = ASK;
        return;
    }

    printf("Input m untuk menu dan c untuk lanjut [default: c]: ");
    char o = getc(stdin);
    if (o == '\n') return;

    flush_stream(stdin);
    if (o == 'm') {
        *c = ASK;
    }
}

// business logic here
void read_input_data(Node *user) {
    // input data
    char str[255];
    char err_info[100] = "";

    while (1) {
        printf("---------- Isi Data ---------------\n");
        if (strcmp(err_info, "") != 0 && strlen(err_info) > 0) {
            printf("Error: %s\n", err_info);
        }

        printf("Nama: ");
        if (scanf("%[^\n]s", str) != 1) {
            printf("Silahkan masukkan nama yang sesuai.\n");
            flush_stream(stdin);
            continue;
        }
        flush_stream(stdin);

        int len = strlen(str);
        if (len <= 0 || len > MAX_NAME - 1) {
            printf("Nama harus terdiri dari 1 sampai %d karakter.\n", MAX_NAME - 1);
            continue;
        }

        strcpy(user->name, str);
        break;
    }
}

void add_user(CMD *c) {
    clrscr();

    // allocate queue if null
    if (que == NULL) {
        que = (Queue *) malloc(sizeof(Queue));
        que->front = NULL;
        que->rear = NULL;
    }

    // allocate node
    Node *user = (Node *) malloc(sizeof(Node));
    user->order_num = ++order_num;
    strcpy(user->name, "-");
    user->next = NULL;
    
    read_input_data(user);

    // handle empty queue
    if (que->front == NULL) {
        // assign new node
        que->front = user;
        que->rear = user;

        continue_or_back_to_menu(c, false);
        return;
    }

    // assign new node into rear
    if (que->front == que->rear) {
        // to handle when only 1 in the queue
        que->front->next = user;
    }
    que->rear->next = user;
    que->rear = user;

    continue_or_back_to_menu(c, false);
}

void print_data(int num, char name[MAX_NAME]) {
    printf("Nomor Urut  : %d\n", num);
    printf("Nama        : %s\n", name);
}

void print_queue_list() {
    if (que == NULL || que->front == NULL) {
        return;
    }

    Node *curr = que->front;

    while (curr != NULL) {
        printf("------------------------------------\n");
        print_data(curr->order_num, curr->name);
        curr = curr->next;
    }
    printf("------------------------------------\n");

    return;
}

void print_queue(CMD *c) {
    clrscr();

    if (que == NULL || que->front == NULL) {
        printf("----------------------------\n");
        printf(" Tidak ada antrian saat ini \n");
        printf("----------------------------\n");
    
        continue_or_back_to_menu(c, true);
        return;
    }

    print_queue_list();

    continue_or_back_to_menu(c, true);
}

void next_user(CMD *c) {
    clrscr();
    
    if (que == NULL || que->front == NULL) {
        printf("----------------------------\n");
        printf(" Tidak ada antrian saat ini \n");
        printf("----------------------------\n");

        // reset data user yang sedang dilayani (menandakan admin siap melayani user lain, tapi karena antrian sudah kosong, maka data user juga dikosongkan)
        curr_user_order_num = 0;
        strcpy(curr_user_name, "");
    
        continue_or_back_to_menu(c, true);
        return;
    }

    Node *curr = que->front;

    // move front data into temporary current user
    curr_user_order_num = curr->order_num;
    strcpy(curr_user_name, curr->name);

    // handle dequeue
    
    // set rear into null when its the last data in queue
    if (que->front->next == NULL && que->front == que->rear) {
        que->rear = NULL;
    }

    // re assign front queue
    que->front = que->front->next;

    // free memory of current node
    free(curr);

    // free queue if front and rear are null
    if (que->front == NULL && que->rear == NULL) {
        free(que);
        que = NULL;
    }

    // print the next user from queue
    print_data(curr_user_order_num, curr_user_name);

    continue_or_back_to_menu(c, false);
}

void print_current_user(CMD *c) {
    clrscr();

    if (strcmp(curr_user_name, "") == 0 || curr_user_order_num == 0) {
        printf("-----------------------------\n");
        printf(" Tidak ada konsumen saat ini \n");
        printf("-----------------------------\n");
    
        continue_or_back_to_menu(c, true);
        return;
    }

    print_data(curr_user_order_num, curr_user_name);

    continue_or_back_to_menu(c, true);
}
