#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "boolean.h"
#include "queue.h"
#include "list.h"

/***** Manajemen memori *****/
/* Mengirimkan address hasil alokasi sebuah elemen dengan info X.
 * Jika alokasi berhasil, modul mengembalikan P; Info(P) = X, Next(P) = NULL.
 * P adalah pointer yang menunjuk ke node Queue sebagai hasil alokasi.
 * Jika alokasi gagal, modul mengembalikan NULL.
 */

char *jenisPenyakit[9] = {
	"Penyakit Kulit",
	"Luka Ringan",
	"Bersin",
	"Cacingan",
	"Diare",
	"Luka Dalam",
	"Kerongkongan Berlendir",
	"Penyakit Kuning",
	"Terkena Virus"
}; 
 
/* Mengirimkan address hasil alokasi sebuah elemen dengan info X.
 * Jika alokasi berhasil, modul mengembalikan P; Info(P) = X, Next(P) = NULL.
 * P adalah pointer yang menunjuk ke node Queue sebagai hasil alokasi.
 * Jika alokasi gagal, modul mengembalikan NULL.
 */
addressQueue AlokasiQueue(infotype X){
	addressQueue P;
    P = (addressQueue)malloc(sizeof(NodeQueue));

    if(P != Nil) { /* Berhasil  */
        Info(P) = X;
    	Next(P) = Nil;
        return P;
   	} else {
   		return Nil;
	}
}


/* Melakukan dealokasi elemen P (pointer menunjuk ke alamat node queue).
 * I.S.: P terdefinisi.
 * F.S.: P dikembalikan ke sistem.
 */
void DealokasiQueue(addressQueue *P){
	Next(*P) = Nil;
    free(*P);
}

/***** Manajemen Queue *****/
	/* Membuat sebuah Queue kosong dengan Front(Q) = Nil dan Rear (Q) = Nil 
   	I.S. Belum terbentuk Queue 
   	F.S. Sudah terbentuk Queue
	*/	
void CreateQueue(Queue *Q){
	Front(*Q) = Nil;
	Rear(*Q) = Nil;
}

/* Mengetahui apakah Queue kosong atau tidak. 
   mengirimkan true, jika Queue Kosong yaitu Front(Q) = Nil dan Rear (Q) = Nil
   Sebaliknya false
*/
bool IsQueueEmpty(Queue Q){
	if (Front(Q) == Nil && Rear(Q) == Nil) {
		return true;
	} else {
		return false;
	}
}

/* Memasukkan info baru ke dalam Queue dengan aturan FIFO */
/* I.S. Q mungkin kosong atau Q mungkin berisi antrian */ 
/* F.S. info baru (data) menjadi Rear yang baru dengan node Rear yang lama mengaitkan pointernya ke node yang baru */ 
void enQueue(Queue *Q, infotype data){
//	addressQueue P = searchPosisi(*Q, data.kategori);
//	addressQueue X = AlokasiQueue(data);
//	if (IsQueueEmpty(*Q)){
//		Front(*Q) = X;
//		Rear(*Q) = X;
//	} else if (Next(P) == Nil) {
//		addressQueue Temp = Front(*Q);
//		Front(*Q) = X;
//		Next(X) = Temp;
//	} else if (P != Nil){
//		addressQueue Temp = Next(P);
//		Next(P) = X;
//		Next(X) = Temp;
//	} else {
//		Next(Rear(*Q)) = X;
//		Rear(*Q) = X;
//	}
	addressQueue current = Front(*Q);
	addressQueue P = AlokasiQueue(data);
	
	if (IsQueueEmpty(*Q)){
		Front(*Q) = P;
	} else {
		if (Kategori(Front(*Q)) < data.kategori)
	    {
	        Next(P) = Front(*Q);
	        Front(*Q) = P;
	    }
	    else
	    {
	        while (Next(current) != Nil && Kategori(Next(current)) > data.kategori)
	        {
	            current = Next(current);
	        }
	 
	        // Either at the ends of the list
	        // or at required position
	        Next(P) = Next(current);
	        Next(current) = P;
	    }
	}
	
	
}

/* Mencari data kucing */
addressQueue searchPosisi(Queue Q, int kategori){
	addressQueue P = Front(Q);
	if (IsQueueEmpty(Q)){
		return P;
	} else {
		if (Next(P) == Nil){
			if (Kategori(P) < kategori){
				return P;
			}
		} else {
			while (P != Nil){
				if (Kategori(P) < kategori){
					return P;
				}
				P = Next(P);
			}
		}
		return Nil;
	}
}

/* Proses: Mengambil info pada Front(Q) dan mengeluarkannya dari Queue dengan aturan FIFO */ 
/* I.S. Q mungkin kosong atau Q mungkin berisi antrian */  
/* F.S. info yang diambil = nilai elemen Front pd I.S. */ 
/* Front(Q) menunjuk ke next antrian atau diset menjadi NIll, Q mungkin kosong */ 
void deQueue(Queue *Q){
	addressQueue P;

	if(IsQueueEmpty(*Q)){
		printf("\n* Tidak Ada Antrian yang Terdaftar *\n\n");
	} else{

		P = (*Q).Front;
		if((*Q).Front == (*Q).Rear){
			(*Q).Front = Nil;
            (*Q).Rear = Nil;
		} else{
			(*Q).Front = (*Q).Front->next;
		}
		P->next = Nil;

		DealokasiQueue(&P);
	}
}

/* Mengirimkan banyaknya elemen queue jika Q berisi atrian atau 
   mengirimkan 0 jika Q kosong 
*/ 
int jumlahAntrian(Queue Q){
	addressQueue P;
    int jmlElement = 0;

	if(IsQueueEmpty(Q)){
		jmlElement = 0;
	} else{
        P = Front(Q);
        do {
            jmlElement++;
            P = Next(P);
        } while(P != Nil);
	}
	
}

/* Menghitung waktu mulai antrian */
int getWaktuMulai(addressQueue P, int waktuDatang);

/* Menghitung waktu mulai antrian */
int getWaktuSelesai(addressQueue P, int waktuDatang);

/* Menampilkan antrian 
 * I.S = Antrian belum tampil
 * F.S = Antrian sudah tampil, jika data kosong maka akan tampil "Data antrian kosong!"*/
void printAntrian(Queue Q){
	infotype data;
	addressQueue P;
	List L;
	addressList addressL;
	infoPenyakit penyakitHewan;
	int i = 1;
	
	P = Front(Q);
	
   	printf("					===========================================\n");
  	printf("					           Daftar Antrian Kucing\n");
   	printf("					===========================================\n");

   	if (IsQueueEmpty(Q)) { // Jika Queue Kosong
		printf("\n					      Data antrian kosong!\n\n");
    } else {
		while(P != Nil){
			printf("					No. Antrian                 : %d\n", i++);
			printData(P);		
			printf("					------------------------------------\n");
			P = Next(P);
		}
	}
}

/* Melakukan registrasi penambahan data pelanggan 
 * I.S = Q mungkin kosong atau Q mungkin berisi antrian
 * F.S = Data baru ditambahkan ke antrian */
void tambahData(Queue *Q){
	system("cls");
	infotype data;
	CreateList(&data.listPenyakit);
	infoPenyakit penyakitHewan;
	
	int tempPenyakit[9];
	int i, totalPenyakit;
	
	printf("					===========================================\n");
	printf("					              Registrasi Data   \n");
	printf("					===========================================\n");
	printf("\n					Nama Kucing                 : "); scanf("%s", &data.namaKucing);
	fflush(stdin);
	printf("					Nama Pemilik                : "); scanf("%s", &data.namaPemilik);
	fflush(stdin);
	printf("					Jenis Kelamin               : "); scanf("%c", &data.jenisKelamin);
	fflush(stdin);
	printf("					Datang di menit ke          : "); scanf("%d", &data.waktuDatang);
	fflush(stdin);
	
	printf("\n");
	printPenyakit();
	printf("\n");
	printf("				        Masukkan Jumlah Penyakit             : "); scanf("%d", &totalPenyakit);
	fflush(stdin);
	puts("					Nomor Penyakit yang Diderita  : ");
	for (i=0; i<totalPenyakit; i++){
	    printf("					");
		scanf("	%d", &tempPenyakit[i]);
	}
	
	int kategoriRingan = 0;
	int kategoriSedang = 0;
	int kategoriBerat = 0;
	
	for (i=0; i<totalPenyakit; i++){
		penyakitHewan.penyakit = tempPenyakit[i];
		penyakitHewan.kategori = getKategoriPenyakit(tempPenyakit[i]);
		penyakitHewan.waktu = getWaktuPenyakit(tempPenyakit[i]);
		InsLast(&data.listPenyakit, penyakitHewan);
		
		if ((tempPenyakit[i]>0) && (tempPenyakit[i]<4)){
			kategoriRingan++;
		}
		if ((tempPenyakit[i]>=4) && (tempPenyakit[i]<7)){
			kategoriSedang++;
		}
		if ((tempPenyakit[i]>=7) && (tempPenyakit[i]<10)){
			kategoriBerat++;
		}
	}
	
	data.kategori = getPrioritas(kategoriRingan, kategoriSedang, kategoriBerat);
	data.waktuPelayanan = getWaktuPelayanan(kategoriRingan, kategoriSedang, kategoriBerat);
	data.waktuMulai = 0;
	data.waktuSelesai = 15;
	enQueue(Q, data);
	//HitungWaktu(*(&Q));

	printf("\n");
	printf("					     Anda Sudah Terdaftar!     \n\n");
}

/* Memanggil data kucing teratas di antrian
 * I.S = Data kucing belum dipanggil (dequeue)
 * F.S = Data kucing sudah dipanggil (dequeue) 
         jika antrian kosong maka akan tampil "Data antrian kosong!"
 */
void pemanggilanKucing(Queue *Q){
	system ("cls");
	addressQueue P;
	infotype R;	
	int i=1;
	char pilih;
	
	P = (*Q).Front;
	
	printf("					===========================================\n");
  	printf("					           Daftar Antrian Kucing\n");
   	printf("					===========================================\n");
	
	if (P == Nil) { // Jika Queue Kosong
		printf("\n					        Data antrian kosong!\n\n");
    } else {
		printf("\n					No. Antrian                 : %d\n", i++);
		printData(P);	
		printf("					------------------------------------\n");
		
		R = InfoFront(*Q);
		printf("					Memulai Proses Pelayanan Untuk %s? [Y/N] ", R.namaKucing);
		fflush(stdin);
		scanf("%c", &pilih);
		
		if(pilih == 'Y' || pilih == 'y'){
			deQueue(Q);
			printf("\n");
			printf("					              Harap bersabar \n");
			printf("					         Antrian Sedang Diproses \n\n");
		} 
		else if(pilih == 'N' || pilih == 'n'){
			printf("\n					       Silahkan Kembali Ke Antrian\n");
		}
	}
}

/* Mencari alamat dari kucing di queue
 * I.S = Data belum dicari
 * F.S = Data sudah dicari jika ada maka akan mengirimkan alamat,
         Jika tidak maka akan mengirimkan null
 */
addressQueue searchData(char namaKucing[25], char namaPemilik[25], Queue Q){
	addressQueue P = Front(Q);
	while(P != Nil){
		if(strcmp(NamaKucing(P),namaKucing) == 0 && strcmp(NamaPemilik(P),namaPemilik) == 0){
			return P;
		}
		P = Next(P);
	}
	
	return Nil;
}

/* Mencari data kucing di antrian
 * I.S = Data belum dicari
 * F.S = Data kucing akan muncul jika ada di antrian
         Jika tidak ada maka akan tampil "Data kucing tidak ada di antrian!"
 */
void pencarianDataKucing(Queue Q){
	char namaKucing[25];
	char namaPemilik[25];
	addressQueue P;
	
	printf("					===========================================\n");
  	printf("					           Daftar Pencarian Kucing\n");
   	printf("					===========================================\n");
	
	printf("\n					Masukan Nama Kucing : ");
	scanf("%s", &namaKucing);
	printf("					Masukan Nama Pemilik : ");
	scanf("%s", &namaPemilik);
	
	printf("\n					-------------------------------------------\n");
	
	P = searchData(namaKucing, namaPemilik, Q);
	if (P == Nil){
		printf("\n					Data kucing tidak ada di antrian!\n");
	} else {
		printData(P);	
	} 
}

/* Mengembalikan kategori penyakit kucing 
   1: ringan, 2: sedang, 3: berat 
*/
int getKategoriPenyakit(int Penyakit){
	if (Penyakit<4){
		return 1; // penyakit ringan
	} else if (Penyakit<7){
		return 2; // penyakit sedang
	} else if (Penyakit<10){
		return 3; // penyakit berat
	}
}	

/* Mengembalikan waktu estimasi pelayanan berdasarkan nilai prioritas antrian */
int getWaktuPenyakit(int Penyakit){
	if (Penyakit<4){
		return 15; // penyakit ringan
	} else if (Penyakit<7){
		return 30; // penyakit sedang
	} else if (Penyakit<10){
		return 40; // penyakit berat
	}
}

/* Mengembalikan kategori prioritas penyakit kucing */
int getPrioritas(int Ringan, int Sedang, int Berat){
	if (Berat > 0){
		return 4;
	} if (Sedang > 1){
		return 3;
	} if (Ringan > 2){
		return 2;
	} else {
		return 1;
	}
}

/* Menghitung waktu estimasi pelayanan */
int getWaktuPelayanan(int Ringan, int Sedang, int Berat){
	return (Ringan*15) + (Sedang*30) + (Berat*45);
}

/* I.S   : List penyakit belum tampil */
/* F.S   : List penyakit sudah tampil */
void printPenyakit(){
	printf("                                        ++=======================================++\n");
	printf("                                        ||            List Penyakit              ||\n");
	printf("                                        ++=======================================++\n");
	printf("                                        || Penyakit ringan   | Penyakit sedang   ||\n");
	printf("                                        || 1. Penyakit kulit | 4. Cacingan       ||\n");
	printf("                                        || 2. Luka ringan    | 5. Diare          ||\n");
	printf("                                        || 3. Bersin         | 6. Luka dalam     ||\n");
	printf("                                        ++---------------------------------------++\n");
	printf("                                        || Penyakit berat                        ||\n");
	printf("                                        || 7. Kerongkongan berlendir dan berbau  ||\n");
	printf("                                        ||    busuk                              ||\n");
	printf("                                        || 8. Penyakit kuning                    ||\n");
	printf("                                        || 9. Terkena virus                      ||\n");
	printf("                                        ++=======================================++\n");
}

/* I.S   : List mungkin kosong 	*/
/* F.S   : Jika list tidak kosong, semua info yang disimpan pada */
/*         elemen list di-print					 */
/*         Jika list kosong, hanya menuliskan "List Kosong"	 */
void PrintInfoPenyakit(List L){
	addressList addL = First(L);
	int i = 1;
	while (addL != Nil){
		printf("					   %d. %s\n", i++, jenisPenyakit[InfoPenyakit(addL)]);
		addL = Next(addL);
	}
}

/* I.S   : Data Belum Tampil 	*/
/* F.S   : Data sudah tampil dan code menjadi lebih ringkas */
void printData(addressQueue P){
	printf("					Nama Hewan                  : %s\n", NamaKucing(P));
	printf("					Nama Pemilik                : %s\n", NamaPemilik(P));
	printf("					Jenis Kelamin               : %c\n", JenisKelamin(P));
	printf("					Datang di menit ke          : %d\n", WaktuDatang(P));
	puts("					Penyakit yang Diderita      :");
	PrintInfoPenyakit(ListPenyakit(P));
	printf("					Nilai Prioritas             : %d\n", Kategori(P));
	printf("					Estimasi Waktu Pelayanan    : %d\n", WaktuPelayanan(P));
	printf("					Waktu Mulai Pelayanan       : %d\n", WaktuMulai(P));
	printf("					Waktu Selesai Pelayanan     : %d\n", WaktuSelesai(P));
}