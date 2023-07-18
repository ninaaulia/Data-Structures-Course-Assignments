// Buatlah sebuah program database sederhana dengan menggunakan singly linked
// list! Program tersebut memiliki pilihan(menu) sebagai berikut:
// 1. Push data karyawan. Ketika dijalankan, akan diminta input berupa Employee
// ID, Nama Lengkap, Tempat Lahir, Tanggal Lahir, dan Jabatan. Validasi Employee
// ID maksimal 5 angka, Nama Lengkap dan Tempat lahir maksimal 30 karakter, dan
// Jabatan maksimal 50 karakter. Validasi jumlah data yang dapat diinput adalah
// maksimal 5 data.
// 2. Menampilkan semua daftar Karyawan di database terdiri dari Employee ID,
// Nama Lengkap, Tempat Tanggal Lahir, dan Jabatan. Data karyawan ditampilkan
// secara terurut (sort) berdasarkan Employee ID.
// 3. Hapus data karyawan berdasarkan Employee ID
// 4. Hapus semua data karyawan
// 5. Keluar dari program.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struktur data untuk menampung informasi karyawan
struct karyawan {
  int id;
  char nama[31];
  char tempat_lahir[31];
  char tanggal_lahir[11];
  char jabatan[51];
  struct karyawan *next;
};

// menambahkan data karyawan ke dalam linked list
void push(struct karyawan **head_ref) {
  struct karyawan *new_karyawan =
      (struct karyawan *)malloc(sizeof(struct karyawan));
  struct karyawan *last = *head_ref;
  int id;
  char nama[31], tempat_lahir[31], tanggal_lahir[11], jabatan[51];

  // meminta input dari pengguna
  printf("Input Employee ID (max 5 angka): ");
  scanf("%d", &id);
  printf("Input Nama Lengkap (max 30 karakter): ");
  scanf(" %[^\n]s", nama);
  printf("Input Tempat Lahir (max 30 karakter): ");
  scanf(" %[^\n]s", tempat_lahir);
  printf("Input Tanggal Lahir (format DD/MM/YYYY): ");
  scanf("%s", tanggal_lahir);
  printf("Input Jabatan (max 50 karakter): ");
  scanf(" %[^\n]s", jabatan);

  // validasi input
  if (id <= 0 || id > 99999) {
    printf("Employee ID harus terdiri dari maksimal 5 angka.\n");
    return;
  }
  if (strlen(nama) > 30) {
    printf("Nama Lengkap harus maksimal 30 karakter.\n");
    return;
  }
  if (strlen(tempat_lahir) > 30) {
    printf("Tempat Lahir harus maksimal 30 karakter.\n");
    return;
  }
  if (strlen(jabatan) > 50) {
    printf("Mata Kuliah harus maksimal 50 karakter.\n");
    return;
  }

  // memasukkan data karyawan ke dalam linked list
  new_karyawan->id = id;
  strcpy(new_karyawan->nama, nama);
  strcpy(new_karyawan->tempat_lahir, tempat_lahir);
  strcpy(new_karyawan->tanggal_lahir, tanggal_lahir);
  strcpy(new_karyawan->jabatan, jabatan);
  new_karyawan->next = NULL;

  if (*head_ref == NULL) {
    *head_ref = new_karyawan;
    return;
  }

  while (last->next != NULL) {
    last = last->next;
  }

  last->next = new_karyawan;
}

// menampilkan semua data karyawan dalam linked list
void tampilkan(struct karyawan *head) {
  struct karyawan *karyawan = head;

  if (karyawan == NULL) {
    printf("Tidak ada data karyawan yang tersimpan.\n");
    return;
  }

  printf("Data karyawan:\n");
  printf(" Employee ID|Nama Lengkap|Tempat|Tanggal Lahir|Jabatan \n");

  // mengurutkan data karyawan berdasarkan Employee ID
  for (int i = 1; i <= 99999; i++) {
    karyawan = head;
    while (karyawan != NULL) {
      if (karyawan->id == i) {
        printf("\t%d\t|%s|%s|%s|%s\n", karyawan->id, karyawan->nama,
               karyawan->tempat_lahir, karyawan->tanggal_lahir,
               karyawan->jabatan);
      }
      karyawan = karyawan->next;
    }
  }
}

void hapus(struct karyawan **head_ref) {
  int id;
  printf("Input ID karyawan yang akan dihapus: ");
  scanf("%d", &id);

  struct karyawan *temp = *head_ref, *prev;

  if (temp != NULL && temp->id == id) {
    *head_ref = temp->next;
    free(temp);
    return;
  }

  while (temp != NULL && temp->id != id) {
    prev = temp;
    temp = temp->next;
  }

  if (temp == NULL) {
    printf("Kesalahan: karyawan dengan ID %d tidak ditemukan.\n", id);
    return;
  }

  prev->next = temp->next;

  free(temp);
}

void hapus_semua(struct karyawan **head_ref) {
  struct karyawan *current = *head_ref;
  struct karyawan *next;

  while (current != NULL) {
    next = current->next;
    free(current);
    current = next;
  }

  *head_ref = NULL;
}

int main() {
  struct karyawan *head = NULL;
  int pilihan;

  do {
    printf("\n\nDatabase Karyawan\n");
    printf("\nMenu:\n");
    printf("\n1. Input data karyawan\n");
    printf("2. Menampilkan semua daftar karyawan di database\n");
    printf("3. Hapus data karyawan berdasarkan Employee ID\n");
    printf("4. Hapus semua data karyawan\n");
    printf("5. Keluar dari program.\n");
    printf("Pilih: ");
    scanf("%d", &pilihan);

    switch (pilihan) {
    case 1:
      push(&head);
      break;
    case 2:
      tampilkan(head);
      break;
    case 3:
      hapus(&head);
      break;
    case 4:
      hapus_semua(&head);
      printf("\nData karyawan berhasil dihapus.\n");
      break;
    case 5:
      printf("\nProgram selesai.\n");
      break;
    default:
      printf("\nPilihan tidak tersedia.\n");
      break;
    }
  } while (pilihan != 5);

  return 0;
}