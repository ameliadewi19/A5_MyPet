#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdbool.h>
#include "../boolean.h"
#include "../ADT Time/time.h"
#include "../ADT List/list.h"

#define Front(Q) (Q).Front 
#define Rear(Q) (Q).Rear 
#define InfoFront(Q) (Q).Front->info 
#define InfoRear(Q) (Q).Rear->info  
#define Info(P) (P)->info 
#define Next(P) (P)->next 
#define NamaKucing(P) (P)->info.namaKucing
#define NamaPemilik(P) (P)->info.namaPemilik
#define JenisKelamin(P) (P)->info.jenisKelamin
#define WaktuDatang(P) (P)->info.waktuDatang
#define WaktuPelayanan(P) (P)->info.waktuPelayanan
#define WaktuMulai(P) (P)->info.waktuMulai
#define WaktuSelesai(P) (P)->info.waktuSelesai
#define Kategori(P) (P)->info.kategori
#define ListPenyakit(P) (P)->info.listPenyakit

/* Definisi elemen dan address */ 
typedef struct infoPelanggan {
	char namaKucing[25]; // Nama Hewan
	char namaPemilik[25]; // Nama Pemilik
	char jenisKelamin; // Jenis Kelamin Hewan
	TIME waktuDatang; // Waktu Kedatangan
	int waktuPelayanan; // Lama Waktu Pelayanan
	TIME waktuMulai; // Waktu Kucing Mulai Dilayani
	TIME waktuSelesai; // Waktu Kucing Selesai Dilayani
	int kategori; // Nilai kategori prioritas penyakit
	List listPenyakit; // List Penyakit Hewan
}infoPelanggan;

typedef infoPelanggan infotype;
typedef struct NodeQueue *addressQueue;
typedef struct NodeQueue {
    infotype info; // info dari antrian
    addressQueue next; // address next 
} NodeQueue;

typedef struct {
    addressQueue Front; // antrian depan
    addressQueue Rear; // antrian belakang
} Queue;

/***** Manajemen memori *****/
/* Mengirimkan address hasil alokasi sebuah elemen dengan info X.
 * Jika alokasi berhasil, modul mengembalikan P; Info(P) = X, Next(P) = NULL.
 * P adalah pointer yang menunjuk ke node Queue sebagai hasil alokasi.
 * Jika alokasi gagal, modul mengembalikan NULL.
 */
addressQueue AlokasiQueue(infotype X);

/* Melakukan dealokasi elemen P (pointer menunjuk ke alamat node queue).
 * I.S.: P terdefinisi.
 * F.S.: P dikembalikan ke sistem.
 */
void DealokasiQueue(addressQueue *P);

/***** Manajemen Queue *****/
	/* Membuat sebuah Queue kosong dengan Front(Q) = Nil dan Rear (Q) = Nil 
   	I.S. Belum terbentuk Queue 
   	F.S. Sudah terbentuk Queue
	*/	
void CreateQueue(Queue *Q);

/* Mengetahui apakah Queue kosong atau tidak. 
   mengirimkan true, jika Queue Kosong yaitu Front(Q) = Nil dan Rear (Q) = Nil
   Sebaliknya false
*/
bool IsQueueEmpty(Queue Q);

/* Memasukkan info baru ke dalam Queue dengan aturan FIFO */
/* I.S. Q mungkin kosong atau Q mungkin berisi antrian */ 
/* F.S. info baru (data) menjadi Rear yang baru dengan node Rear yang lama mengaitkan pointernya ke node yang baru */ 
void enQueue(Queue *Q, infotype data);

/* Proses: Mengambil info pada Front(Q) dan mengeluarkannya dari Queue dengan aturan FIFO */ 
/* I.S. Q mungkin kosong atau Q mungkin berisi antrian */  
/* F.S. info yang diambil = nilai elemen Front pd I.S. */ 
/* Front(Q) menunjuk ke next antrian atau diset menjadi NIll, Q mungkin kosong */ 
void deQueue(Queue *Q);

/* Mengirimkan banyaknya elemen queue jika Q berisi atrian atau 
   mengirimkan 0 jika Q kosong 
*/ 
int jumlahAntrian(Queue Q); 

/* Menentukan nilai prioritas dari suatu antrian berdasarkan jumlah penyakit yang diderita */
int getPrioritas(int Ringan, int Sedang, int Berat);

/* Mengembalikan kategori penyakit kucing 
   1: ringan, 2: sedang, 3: berat 
*/
int getKategoriPenyakit(int Penyakit);	

/* Mengembalikan waktu estimasi pelayanan berdasarkan nilai prioritas antrian */
int getWaktuPenyakit(int Penyakit);

/* Menghitung waktu estimasi pelayanan */
int getWaktuPelayanan(int Ringan, int Sedang, int Berat);

/* Menghitung waktu mulai antrian */
TIME getWaktuMulai(addressQueue P2, addressQueue P, Queue Q);

/* Menghitung waktu mulai antrian */
TIME getWaktuSelesai(addressQueue P);

/* Mengupdate semua waktu di antrian dari awal hingga akhir
 * I.S = Waktu di antrian belum dihitung dan terupdate
 * F.S = Waktu di antrian sudah dihitung dan terupdate */
void hitungWaktuAntrian(Queue *Q);

/* Menampilkan antrian 
 * I.S = Antrian belum tampil
 * F.S = Antrian sudah tampil, jika data kosong maka akan tampil "Data antrian kosong!"*/
void printAntrian(Queue Q);

/* Melakukan registrasi penambahan data pelanggan 
 * I.S = Q mungkin kosong atau Q mungkin berisi antrian
 * F.S = Data baru ditambahkan ke antrian */
void tambahData(Queue *Q);
 
/* Memanggil data kucing teratas di antrian
 * I.S = Data kucing belum dipanggil (dequeue)
 * F.S = Data kucing sudah dipanggil (dequeue) 
         jika antrian kosong maka akan tampil "Data antrian kosong!"
 */
void pemanggilanKucing(Queue *Q, Queue *sedangDiproses);

/* Mencari data kucing di antrian
 * I.S = Data kucing belum dicari
 * F.S = Jika ada di antrian maka akan muncul data kucing
         Jika tidak ada maka akan tampil "Data tidak ada di antrian"
 */
addressQueue searchData(char namaKucing[25], char namaPemilik[25], Queue Q);

/* Mencari data kucing di antrian
 * I.S = Data belum dicari
 * F.S = Data kucing akan muncul jika ada di antrian
         Jika tidak ada maka akan tampil "Data kucing tidak ada di antrian!"
 */
void pencarianDataKucing(Queue Q);

/* Mencari data kucing */
addressQueue searchPosisi(Queue Q, int kategori);

/* I.S   : List penyakit belum tampil */
/* F.S   : List penyakit sudah tampil */
void printPenyakit();

/* I.S   : List mungkin kosong 	*/
/* F.S   : Jika list tidak kosong, semua info yang disimpan pada */
/*         elemen list di-print					 */
/*         Jika list kosong, hanya menuliskan "List Kosong"	 */
void PrintInfoPenyakit(List L);

/* I.S   : Data Belum Tampil 	*/
/* F.S   : Data sudah tampil dan code menjadi lebih ringkas */
void printData(addressQueue P);

/* Mengirimkan hasil cek kevalidan inputan jenis kelamin kucing*/
/* Jika inputan J/j/B/b maka akan mengirimkan true */
boolean cekInputJK(char jk);

/* Mengirimkan hasil cek kevalidan inputan jumlah jenis penyakit*/
/* Jika inputan antara 1 sampai 10 maka akan mengirimkan true */
boolean cekInputJumlahPenyakit(int jumlahPenyakit);

/* Mengirimkan hasil cek kevalidan inputan jumlah jenis penyakit*/
/* Jika inputan antara 1 sampai 10 maka akan mengirimkan true */
boolean cekInputNomorPenyakit(int jumlahPenyakit, int penyakit[]);

/* I.S   : Data kucing belum masuk ke file 	*/
/* F.S   : Data kucing sudah masuk ke file */
void saveData(Queue *Q);

void printDataDiproses(Queue sedangDiproses);

#endif // QUEUE_H
