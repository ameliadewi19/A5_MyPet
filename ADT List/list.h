#ifndef list_H
#define list_H 

#include "../boolean.h"
#include <stdlib.h>

#define Nil NULL
#define Info(P) (P)->info
#define InfoPenyakit(P) (P)->info.penyakit
#define Next(P) (P)->next
#define First(L) ((L).First)
                   
typedef struct {
	int penyakit;
	int kategori;
	int waktu;
}infoPenyakit;
typedef struct tElmtlist *addressList;
typedef struct  tElmtlist{
	infoPenyakit info;
	addressList next;
}ElmtList;

typedef struct {
	addressList First;
}List;

/******************************************************************************************/
/*                                      Manajemen Memory                                  */
/******************************************************************************************/

// mengecek apakah jumlah elemen pada List kosong
// mengirimkan true jika List kosong, mengirimkan false jika tidak
// Author : Tabitha Salsabila Permana
boolean ListEmpty(List L);

// Membuat list dengan menginisiasikan null/nil
// I.S : List belum terbuat
// F.S : List sudah terbuat
// Author : Fadhil Radja Assydiq
void CreateList(List *L);

// Mengirimkan  address  hasil alokasi    sebuah elemen
// Jika alokasi berhasil, maka  address tidak nil, dan misalnya  
// menghasilkan P,  maka info(P)=X,  Nest(P)=Nil;               
// Jika alokasi gagal,  mengirimkan  Nil 			  
// Author : Amelia Dewi Agustiani
addressList AlokasiList(infoPenyakit  X);

// Melakukan dealokasi/ pengembalian address P ke system
// I.S : P terdefinisi
// F.S : P dikembalikan ke sistem
// Author : Tabitha Salsabila Permana
void DealokasiList (addressList *P);

/******************************************************************************************/
/*                                     Penambahan Elemen                                  */
/******************************************************************************************/

// Melakukan penambahan elemen diawal list
// I.S  : L mungkin kosong          
// F.S  : Melakukan alokasi sebuah elemen dan                
//        menambahkan elemen pertama dengan nilai X jika     
//        Alokasi berhasil 				     
// Author : Fadhil Radja Assydiq
void InsFirst (List *L, infoPenyakit X);

// Memasukan node di akhir list
// I.S : L terdefinisi, mungkin kosong
// F.S : melakukan alokasi sebuah elemen dan
// menambahkan elemen terakhir pada List dengan nilai X jika alokasi
// berhasil. Jika alokasi gagal IS = FS
// Author : Amelia Dewi Agustiani
void InsLast (List *L, infoPenyakit X);

// I.S  : L mungkin kosong          
// F.S  : Melakukan alokasi sebuah elemen dan                
//        menambahkan elemen list di akhir; elemen terakhir  
//        yang baru bernilai X jika alokasi berhasil, 	     
//		  Jika alokasi gagal: I.S = F.S			     
// Author : Tabitha Salsabila Permana
void InsAfter(List * L, infoPenyakit X, infoPenyakit Y);

/******************************************************************************************/
/*                                    Penghapusan Elemen                                  */
/******************************************************************************************/

// Melakukan delete node di awal 
// I.S : Node di akhir list belum terhapus
// F.S : Node di akhir list sudah terhapus
// Author : Fadhil Radja Assydiq
void DelFirst(List *L, infoPenyakit *X);

// Menghapus node diakhir list
// I.S    : List tidak kosong  		                 
// F.S    : Elemen pertama List dihapus, nilai info disimpan   
//	        pada X dan alamat elemen pertama  di-dealokasi 	
// Author : Amelia Dewi Agustiani
void DelLast(List *L, infoPenyakit *X);

// Menghapus node diposisi tertentu
// I.S : Delete atau penghapusan pada elemen yang dipilih 
//       belum dilakukan
// F.S : Delete atau penghapusan pada elemen yang dipilih 
//       sudah dilakukan
// Author : Tabitha Salsabila Permana
void DelAfter (List * L, infoPenyakit *X, infoPenyakit Y);

/******************************************************************************************/
/*                                       Operasi Lain                                     */
/******************************************************************************************/

// Mengirimkan banyaknya elemen list, mengirimkan Nol jika kosong 
// Author : Fadhil Radja Assydiq
int JumlahPenyakit(List L);

#endif
