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
#define KategoriPrioritas(P) (P)->info.kategoriPrioritas
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
	int kategoriPrioritas; // Nilai kategori prioritas penyakit
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

typedef struct Riwayat {
	char namaKucing[25]; // Nama Hewan
	char namaPemilik[25]; // Nama Pemilik
	char jenisKelamin; // Jenis Kelamin Hewan
	TIME waktuDatang; // Waktu Kedatangan
	int waktuPelayanan; // Lama Waktu Pelayanan
	TIME waktuMulai; // Waktu Kucing Mulai Dilayani
	TIME waktuSelesai; // Waktu Kucing Selesai Dilayani
	int kategoriPrioritas; // Nilai kategori prioritas penyakit
	infoPenyakit listPenyakit[9]; // List Penyakit Hewan
} Riwayat;

/* Mengirimkan address hasil alokasi sebuah elemen dengan info X.
   Jika alokasi berhasil, modul mengembalikan P; Info(P) = X, Next(P) = NULL.
   P adalah pointer yang menunjuk ke node Queue sebagai hasil alokasi.
   Jika alokasi gagal, modul mengembalikan NULL. */
// Author : Tabitha Salsabila Permana
addressQueue AlokasiQueue(infotype X);

// Melakukan dealokasi elemen P (pointer menunjuk ke alamat node queue).
// I.S.: P terdefinisi.
// F.S.: P dikembalikan ke sistem.
// Author : Fadhil Radja Assydiq
void DealokasiQueue(addressQueue *P);

/******************************************************************************************/
/*                                      Manajemen Memory                                  */
/******************************************************************************************/

// Membuat sebuah Queue kosong dengan Front(Q) = Nil dan Rear (Q) = Nil 
// I.S. Belum terbentuk Queue 
// F.S. Sudah terbentuk Queue	
// Author : Amelia Dewi Agustiani
void CreateQueue(Queue *Q);

/* Mengetahui apakah Queue kosong atau tidak. 
   mengirimkan true, jika Queue Kosong yaitu Front(Q) = Nil dan Rear (Q) = Nil
   Sebaliknya false */
// Author : Tabitha Salsabila Permana
bool IsQueueEmpty(Queue Q);

/* Mengirimkan banyaknya elemen queue jika Q berisi atrian atau 
   mengirimkan 0 jika Q kosong */
// Author : Fadhil Radja Assydiq
int jumlahAntrian(Queue Q);

/******************************************************************************************/
/*                                    Tambah Data Kucing                                  */
/******************************************************************************************/

// Memasukkan info baru ke dalam Queue dengan aturan FIFO 
// I.S. Q mungkin kosong atau Q mungkin berisi antrian  
// F.S. info baru (data) menjadi Rear yang baru dengan node Rear yang lama mengaitkan pointernya ke node yang baru
// Author : Amelia Dewi Agustiani
void enQueue(Queue *Q, infotype data);

// Melakukan registrasi penambahan data pelanggan 
// I.S = Q mungkin kosong atau Q mungkin berisi antrian
// F.S = Data baru ditambahkan ke antrian 
// Author : Tabitha Salsabila Permana
void tambahData(Queue *Q, Queue sedangDiproses);

/******************************************************************************************/
/*                                  Pemanggilan Data Kucing                               */
/******************************************************************************************/

// Proses: Mengambil info pada Front(Q) dan mengeluarkannya dari Queue dengan aturan FIFO
// I.S. Q mungkin kosong atau Q mungkin berisi antrian 
// F.S. info yang diambil = nilai elemen Front pd I.S.  
// Author : Fadhil Radja Assydiq
void deQueue(Queue *Q);

// Memanggil data kucing teratas di antrian
// I.S = Data kucing belum dipanggil (dequeue)
/* F.S = Data kucing sudah dipanggil (dequeue) 
        jika antrian kosong maka akan tampil "Data antrian kosong!"*/
// Author : Fadhil Radja Assydiq        
void pemanggilanKucing(Queue *Q, Queue *sedangDiproses);

/******************************************************************************************/
/*                                   Pencarian Data Kucing                                */
/******************************************************************************************/

// Mencari data kucing di antrian
// I.S = Data belum dicari
/* F.S = Data kucing akan muncul jika ada di antrian
         Jika tidak ada maka akan tampil "Data kucing tidak ada di antrian!" */
// Author : Amelia Dewi Agustiani
void pencarianDataKucing(Queue Q);

// Mencari alamat dari kucing di queue
// I.S = Data belum dicari
/* F.S = Data sudah dicari jika ada maka akan mengirimkan alamat,
         Jika tidak maka akan mengirimkan null */
// Author : Amelia Dewi Agustiani
addressQueue searchData(char namaKucing[25], char namaPemilik[25], Queue Q);

/******************************************************************************************/
/*                                    Perhitungan Antrian                                 */
/******************************************************************************************/

/* Mengembalikan kategori penyakit kucing 
   1: ringan, 2: sedang, 3: berat 
*/
// Author : Amelia Dewi Agustiani
int getKategoriPenyakit(int Penyakit);

/* Mengembalikan waktu estimasi pelayanan berdasarkan nilai prioritas antrian */
// Author : Amelia Dewi Agustiani
int getWaktuPenyakit(int Penyakit);

/* Mengembalikan kategori prioritas penyakit kucing */
// Author : Amelia Dewi Agustiani
int getPrioritas(int Ringan, int Sedang, int Berat);

/* Menghitung waktu estimasi pelayanan */
// Author : Fadhil Radja Assydiq
int getWaktuPelayanan(int Ringan, int Sedang, int Berat);

/* Menghitung waktu mulai antrian */
// Author : Amelia Dewi Agustiani
TIME getWaktuMulai(addressQueue P, addressQueue P2, Queue Q);

/* Menghitung waktu mulai antrian */
// Author : Tabitha Salsabila Permana
TIME getWaktuSelesai(addressQueue P);

// Mengupdate semua waktu di antrian dari awal hingga akhir
// I.S = Waktu di antrian belum dihitung dan terupdate
// F.S = Waktu di antrian sudah dihitung dan terupdate 
// Author : Amelia Dewi Agustiani
void hitungWaktuAntrian(Queue *Q);

/******************************************************************************************/
/*                                       Print                                            */
/******************************************************************************************/

// Menampilkan antrian 
// I.S = Antrian belum tampil
// F.S = Antrian sudah tampil, jika data kosong maka akan tampil "Data antrian kosong!"*/
// Author : Amelia Dewi Agustiani
void printAntrian(Queue Q);

// Menampilkan list penyakit
/* I.S   : List penyakit belum tampil */
/* F.S   : List penyakit sudah tampil */
// Author : Tabitha Salsabila Permana
void printPenyakit();
 
// I.S   : List mungkin kosong 	
/* F.S   : Jika list tidak kosong, semua info yang disimpan pada
           elemen list di-print					 
           Jika list kosong, hanya menuliskan "List Kosong"	*/
// Author : Amelia Dewi Agustiani
void PrintInfoPenyakit(List L);

// Menampilkan data kucing
// I.S   : Data Belum Tampil 	
// F.S   : Data sudah tampil dan code menjadi lebih ringkas 
// Author : Amelia Dewi Agustiani
void printData(addressQueue P);

// Menampilkan data kucing yang sedang di proses
// I.S : data kucing yang sedang di proses belum tampil
// F.S : data kucing yang sedang di proses sudah tampil
// Author : Amelia Dewi Agustiani
void printDataDiproses(Queue sedangDiproses);

/******************************************************************************************/
/*                                    Pengecekan                                          */
/******************************************************************************************/

/*Mengembalikan nilai cek inputan jenis kelamin
  Jika inputan J/j/B/b maka menghasilkan hasil true
  Jika inputan lain maka akan menghasilkan false */
// Author : Tabitha Salsabila Permana
boolean cekInputJK(char jk);

/* Mengirimkan hasil cek kevalidan inputan jumlah jenis penyakit*/
/* Jika inputan antara 1 sampai 10 maka akan mengirimkan true */
// Author : Fadhil Radja Assydiq
boolean cekInputJumlahPenyakit(int jumlahPenyakit);

/* Mengirimkan hasil cek kevalidan inputan jumlah jenis penyakit*/
/* Jika inputan antara 1 sampai 10 maka akan mengirimkan true */
// Author : Amelia Dewi Agustiani
boolean cekInputNomorPenyakit(int jumlahPenyakit, int penyakit[]);

// Menyimpan data riwayat ke file
// I.S : Data kucing belum tersimpan di file
// F.S : Data kucing sudah tersimpan 
// Author : Fadhil Radja Assydiq & Amelia Dewi Agustiani
void saveData(Queue *Q);

// Mencari data kucing di file riwayat
// I.S : Data kucing belum dicari di file
// F.S : Data kucing sudah dicari
// Author : Amelia Dewi Agustiani
void pencarianRiwayatDataKucing();

// Menampilkan data kucing di file riwayat
// I.S : Data kucing belum tampil
// F.S : Data kucing sudah tampil
// Author : Amelia Dewi Agustiani
void printRiwayatDataKucing();

#endif // QUEUE_H
