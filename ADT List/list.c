#include "../boolean.h"
#include "list.h"
#include <stdlib.h>
#include <stdio.h>

/* ** Prototype   **  */
/* ** Test List Kosong **  */
boolean ListEmpty(List L){
	// mengecek apakah jumlah elemen pada List kosong
	// mengirimkan true jika List kosong, mengirimkan false jika tidak
	// =========================================================================
	/** { KELOMPOK Interaksi operasi linear list, baca tulis } **/
	/**Penambahan Elemen***/
	return(First(L)==Nil);
}

void CreateList(List *L){
	First(*L)=Nil;
}

/* Manajeman  memory  			*/
/* Mengirimkan  address  hasil alokasi    sebuah elemen */
/* Jika alokasi  berhasil, maka  address tidak nil, dan misalnya  */
/* menghasilkan   P,  maka info(P)=X,  Nest(P)=Nil;               */
/* Jika alokasi  gagal,  mengirimkan  Nil 			   */
addressList AlokasiList(infoPenyakit  X){
	addressList P;
    P=(addressList)malloc(sizeof(ElmtList));
    if(P!=Nil) { /* Berhasil  */
   		Info(P)=X;
		Next(P)=Nil;
    }
    return P;
}

void DealokasiList (addressList *P){
	/*I.S : P terdefinisi
	F.S : P dikembalikan ke sistem
	Melakukan dealokasi/ pengembalian address P ke system
	*/
	Next(*P) = Nil;
	free(*P);
}

/*   ** PENCARIAN SEBUAH ELEMEN LIST **   */

boolean FSearch(List L, addressList P);
/* Mencari apakah  ada elemen List yang  beralamat   P   */
/* Mengirimkan true jika ada, false jika tidak ada  	 */


/* ** PRIMITIF BERDASARKAN NILAI ** */

/* ** Penambahan Elemen ** */
void InsFirst (List *L, infoPenyakit X){
	addressList P = AlokasiList(X);
	if(P!=Nil){
		Next(P) = First(*L);
		First(*L) = P;
	}
}

/* I.S  : L mungkin kosong          */
/* F.S  : Melakukan alokasi sebuah elemen dan                */
/*        menambahkan elemen pertama dengan nilai X jika     */
/*        Alokasi berhasil 				     */

void InsLast (List *L, infoPenyakit X){
	/*I.S : L terdefinisi, mungkin kosong
	F.S : melakukan alokasi sebuah elemen dan
	menambahkan elemen terakhir pada List dengan nilai X jika alokasi
	berhasil. Jika alokasi gagal IS = FS
	*/
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

/* I.S  : L mungkin kosong          */
/* F.S  : Melakukan alokasi sebuah elemen dan                */
/*        menambahkan elemen list di akhir; elemen terakhir  */
/*        yang baru bernilai X jika alokasi berhasil, 	     */	
/*	  Jika alokasi gagal: I.S = F.S			     */

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

/* I.S  : L mungkin kosong          */
/* F.S  : Melakukan alokasi sebuah elemen dan                */
/*        menambahkan elemen list di akhir; elemen terakhir  */
/*        yang baru bernilai X jika alokasi berhasil, 	     */	
/*	  Jika alokasi gagal: I.S = F.S			     */

/* *** Penghapusan Elemen  ***  */
	  
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
  /* I.S    : List tidak kosong  		                 */
  /* F.S    : Elemen pertama List dihapus, nilai info disimpan   */
  /*	      pada X dan alamat elemen pertama  di-dealokasi 	 */


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
  /* I.S    : List tidak kosong  		                 */
  /* F.S    : Elemen terakhir list dihapus, nilai info disimpan  */
  /*	      pada X dan alamat elemen terakhir di-dealokasi 	 */

/* *******  PRIMITIF BERDASARKAN ALAMAT ********	*/
/* Penambahan Elemen Berdasarkan Alamat 		*/

void DelAfter (List * L, infoPenyakit *X, infoPenyakit Y){
	/*I.S : L terdefinisi, mungkin kosong
	F.S : melakukan dealokasi sebuah elemen dengan nilai x setelah nilai y
	pertama ditemukan pada list.
	Nilai x yang dihapus dalam list akan disimpan sebagai keluaran dari
	prosedur
	*/
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


  /* I.S    : List tidak kosong  		                 */
  /* F.S    : Elemen terakhir list dihapus, nilai info disimpan  */
  /*	      pada X dan alamat elemen terakhir di-dealokasi 	 */

/* *******  PRIMITIF BERDASARKAN ALAMAT ********	*/
/* Penambahan Elemen Berdasarkan Alamat 		*/

/* *************PROSES SEMUA ELEMEN ****************   */
void PrintInfo(List L, char **C);
/* I.S   : List mungkin kosong 	*/
/* F.S   : Jika list tidak kosong, semua info yang disimpan pada */
/*         elemen list di-print					 */
/*         Jika list kosong, hanya menuliskan "List Kosong"	 */

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
/* Mengirimkan banyaknya elemen list, mengirimkan Nol jika kosong */
