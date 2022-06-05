#include "../boolean.h"
#include "list.h"
#include <stdlib.h>
#include <stdio.h>

/******************************************************************************************/
/*                                      Manajemen Memory                                  */
/******************************************************************************************/

// mengecek apakah jumlah elemen pada List kosong
// mengirimkan true jika List kosong, mengirimkan false jika tidak
// Author : Tabitha Salsabila Permana
boolean ListEmpty(List L){
	return(First(L)==Nil);
}

// Membuat list dengan menginisiasikan null/nil
// I.S : List belum terbuat
// F.S : List sudah terbuat
// Author : Fadhil Radja Assydiq
void CreateList(List *L){
	First(*L)=Nil;
}

// Mengirimkan  address  hasil alokasi    sebuah elemen
// Jika alokasi berhasil, maka  address tidak nil, dan misalnya  
// menghasilkan P,  maka info(P)=X,  Nest(P)=Nil;               
// Jika alokasi gagal,  mengirimkan  Nil 			  
// Author : Amelia Dewi Agustiani
addressList AlokasiList(infoPenyakit  X){
	addressList P;
    P=(addressList)malloc(sizeof(ElmtList));
    if(P!=Nil) { /* Berhasil  */
   		Info(P)=X;
		Next(P)=Nil;
    }
    return P;
}

// Melakukan dealokasi/ pengembalian address P ke system
// I.S : P terdefinisi
// F.S : P dikembalikan ke sistem
// Author : Tabitha Salsabila Permana
void DealokasiList (addressList *P){
	Next(*P) = Nil;
	free(*P);
}

/******************************************************************************************/
/*                                     Penambahan Elemen                                  */
/******************************************************************************************/

// Melakukan penambahan elemen diawal list
// I.S  : L mungkin kosong          
// F.S  : Melakukan alokasi sebuah elemen dan                
//        menambahkan elemen pertama dengan nilai X jika     
//        Alokasi berhasil 				     
// Author : Fadhil Radja Assydiq
void InsFirst (List *L, infoPenyakit X){
	addressList P = AlokasiList(X);
	if(P!=Nil){
		Next(P) = First(*L);
		First(*L) = P;
	}
}

// Memasukan node di akhir list
// I.S : L terdefinisi, mungkin kosong
// F.S : melakukan alokasi sebuah elemen dan
// menambahkan elemen terakhir pada List dengan nilai X jika alokasi
// berhasil. Jika alokasi gagal IS = FS
// Author : Amelia Dewi Agustiani
void InsLast (List *L, infoPenyakit X){
	addressList P = AlokasiList(X);
	addressList Last = First(*L);
	if (ListEmpty(*L)==true){
		InsFirst(&(*L), X);
	} else {
		while(Next(Last) != Nil){
			Last = Next(Last);
		}
		Next(Last) = P;
	}
}

// I.S  : L mungkin kosong          
// F.S  : Melakukan alokasi sebuah elemen dan                
//        menambahkan elemen list di akhir; elemen terakhir  
//        yang baru bernilai X jika alokasi berhasil, 	     
//		  Jika alokasi gagal: I.S = F.S			     
// Author : Tabitha Salsabila Permana
void InsAfter(List * L, infoPenyakit X, infoPenyakit Y){
	boolean ketemu = false;
	
	addressList cari = First(*L);
	addressList P = AlokasiList(X);
	
	while (cari != Nil && ketemu == false){
		if (Info(cari).penyakit == Y.penyakit ){
			Next(P) = Next(cari);
			Next(cari) = P;
			ketemu = true;
		}
		cari = Next(cari);
	}
	
	if (ketemu == false){
		printf("Tidak ditemukan tempat untuk mengisi angka!");
	}
}

/******************************************************************************************/
/*                                    Penghapusan Elemen                                  */
/******************************************************************************************/

// Melakukan delete node di awal 
// I.S : Node di akhir list belum terhapus
// F.S : Node di akhir list sudah terhapus
// Author : Fadhil Radja Assydiq
void DelFirst(List *L, infoPenyakit *X){
	addressList P = First(*L);
	if(First(*L) == Nil){
		printf("List kosong!");
	} else {
		if (Next(P) == Nil){
			DealokasiList(&P);
			First(*L) = Nil;
		} else {
			First(*L) = Next(First(*L));
			Next(P) = Nil;
 			DealokasiList(&P);
		}
		*X = Info(P);
	}
}

// Menghapus node diakhir list
// I.S    : List tidak kosong  		                 
// F.S    : Elemen pertama List dihapus, nilai info disimpan   
//	        pada X dan alamat elemen pertama  di-dealokasi 	
// Author : Amelia Dewi Agustiani
void DelLast(List *L, infoPenyakit *X){
	addressList Last = First(*L);
	addressList PrecLast;
	if(First(*L) == Nil){
		printf("List kosong!");
	} else if (Next(Last) == Nil) {
		DelFirst(&(*L),&(*X));
	} else {
		while (Next(Last) != Nil){
			PrecLast = Last;
			Last = Next(Last);
		}
		*X = Info(Last);
		DealokasiList(&Last);
		Next(PrecLast) = Nil;
	}
}

// Menghapus node diposisi tertentu
// I.S : Delete atau penghapusan pada elemen yang dipilih 
//       belum dilakukan
// F.S : Delete atau penghapusan pada elemen yang dipilih 
//       sudah dilakukan
// Author : Tabitha Salsabila Permana
void DelAfter (List * L, infoPenyakit *X, infoPenyakit Y){
	boolean ketemu = false;
	
	addressList cari = First(*L);
	addressList PrecCari;
	
	while (cari != Nil && ketemu == false){
		if (Info(cari).penyakit == Y.penyakit){
			*X = Info(cari);			
			Next(PrecCari) = Next(cari);
			DealokasiList(&cari);
			ketemu = true;
		}
		PrecCari = cari;
		cari = Next(cari);
	}
	
	if (ketemu == false){
		printf("Tidak ditemukan tempat untuk mengisi angka!");
	}
}

/******************************************************************************************/
/*                                       Operasi Lain                                     */
/******************************************************************************************/

// Mengirimkan banyaknya elemen list, mengirimkan Nol jika kosong 
// Author : Fadhil Radja Assydiq
int JumlahPenyakit(List L){
	addressList P;
  	int jumlah = 0;
  	if(ListEmpty(L)){
 		return 0;
  	} else { /* Tidak kosong */
	    P=First(L);
       	do {
		    jumlah++;  
		    P=Next(P);  
	    }while(P!=Nil);
  	}
    return jumlah;
}