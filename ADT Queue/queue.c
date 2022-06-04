#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../boolean.h"
#include "queue.h"

/***** Manajemen memori *****/
/* Mengirimkan address hasil alokasi sebuah elemen dengan info X.
 * Jika alokasi berhasil, modul mengembalikan P; Info(P) = X, Next(P) = NULL.
 * P adalah pointer yang menunjuk ke node Queue sebagai hasil alokasi.
 * Jika alokasi gagal, modul mengembalikan NULL.
 */
 
TIME waktuSelesaiAwal;
boolean awalHari = false;

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

/******************************************************************************************/
/*                                    Tambah Data Kucing                                  */
/******************************************************************************************/

/* Memasukkan info baru ke dalam Queue dengan aturan FIFO */
/* I.S. Q mungkin kosong atau Q mungkin berisi antrian */ 
/* F.S. info baru (data) menjadi Rear yang baru dengan node Rear yang lama mengaitkan pointernya ke node yang baru */ 
void enQueue(Queue *Q, infotype data){
	addressQueue current = Front(*Q);
	addressQueue P = AlokasiQueue(data);
	
	if (IsQueueEmpty(*Q)){
		Front(*Q) = P;
	} else {
		if (Kategori(Front(*Q)) < data.kategori || (Kategori(Front(*Q)) == data.kategori && TimeToMenit(WaktuDatang(Front(*Q))) > TimeToMenit(data.waktuDatang)))
	    { // untuk data jika kategori salah 
	        Next(P) = Front(*Q);
	        Front(*Q) = P;
	    }
	    else 
	    { // untuk data dari posisi antrian kedua sampai akhir
	    	// mencari data kategori sampai posisi tidak lebih dari
	        while (Next(current) != Nil && Kategori(Next(current)) > data.kategori)
	        {
	            current = Next(current);
	        }
	        
	        // mencari data kategori sampai posisi sama dengan 
	 		while (Next(current) != Nil && Kategori(Next(current)) == data.kategori && TimeToMenit(WaktuDatang(Next(current))) <= TimeToMenit(data.waktuDatang)){	
				current = Next(current);
			}
			
	        // akhir atau posisi yang sesuai
	        Next(P) = Next(current);
	        Next(current) = P;	
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
	boolean jenisKel;
	
	int tempPenyakit[9];
	int i, totalPenyakit;
	
	printf("					===========================================\n");
	printf("					              Registrasi Data   \n");
	printf("					===========================================\n");
	printf("\n					Nama Kucing                 : "); scanf("%s", &data.namaKucing);
	fflush(stdin);
	printf("					Nama Pemilik                : "); scanf("%s", &data.namaPemilik);
	fflush(stdin);	
	do {
		printf("					Jenis Kelamin [J/B]         : "); scanf("%c", &data.jenisKelamin);
		fflush(stdin);
	} while (!cekInputJK(data.jenisKelamin));
	
	do {
		printf("					Datang di menit ke [HH MM]  : "); scanf("%d %d", &data.waktuDatang.Hour, &data.waktuDatang.Minute);
		fflush(stdin);
	} while (!IsJamValid(data.waktuDatang));
	
	printf("\n");
	printPenyakit();
	printf("\n");
	
	do {
		printf("				        Masukkan Jumlah Penyakit             : "); scanf("%d", &totalPenyakit);
		fflush(stdin);
	} while (!cekInputJumlahPenyakit(totalPenyakit));
	
	do {
		puts("					Nomor Penyakit yang Diderita  : ");
		for (i=0; i<totalPenyakit; i++){
		    printf("					");
			scanf("	%d", &tempPenyakit[i]);
		}
	} while (!cekInputNomorPenyakit(totalPenyakit, tempPenyakit));
	
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
	enQueue(Q, data);
	hitungWaktuAntrian(&(*Q));

	printf("\n");
	printf("					            Anda Sudah Terdaftar!     \n\n");
}

/******************************************************************************************/
/*                                  Pemanggilan Data Kucing                               */
/******************************************************************************************/

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

/* Memanggil data kucing teratas di antrian
 * I.S = Data kucing belum dipanggil (dequeue)
 * F.S = Data kucing sudah dipanggil (dequeue) 
         jika antrian kosong maka akan tampil "Data antrian kosong!"
 */
void pemanggilanKucing(Queue *Q, Queue *sedangDiproses){
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
		printf("\n						   Data antrian kosong!\n\n");
    } else {
		printf("\n					No. Antrian                 : %d\n", i++);
		printData(P);	
		printf("					------------------------------------\n");
		
		R = InfoFront(*Q);
		printf("					Memulai Proses Pelayanan Untuk %s? [Y/N] ", R.namaKucing);
		fflush(stdin);
		scanf("%c", &pilih);
		
		if(pilih == 'Y' || pilih == 'y'){
			saveData(Q);
			int waktu = WaktuPelayanan(Front(*Q));
			Front(*sedangDiproses) = AlokasiQueue(Info(Front(*Q)));
			if(awalHari == false){
				waktuSelesaiAwal = WaktuSelesai(Front(*Q));
				awalHari = true;
			}
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

/******************************************************************************************/
/*                                   Pencarian Data Kucing                                */
/******************************************************************************************/

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

/******************************************************************************************/
/*                                    Perhitungan Antrian                                 */
/******************************************************************************************/

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

/* Menghitung waktu mulai antrian */
TIME getWaktuMulai(addressQueue P, addressQueue P2, Queue Q){
	TIME mulai;
	mulai.Hour = 0;
	mulai.Minute = 0;
	if (Front(Q) == P){
		if (awalHari == false){
			mulai = WaktuDatang(P);	
		} else {
			mulai = NextNMenit(waktuSelesaiAwal, 1);
		}
	} else if (TimeToMenit(WaktuDatang(P)) > TimeToMenit(WaktuSelesai(P2))) {
		mulai = WaktuDatang(P);
	} else {
		mulai = NextNMenit(WaktuSelesai(P2),1);
	}
	
	return mulai;
}

/* Menghitung waktu mulai antrian */
TIME getWaktuSelesai(addressQueue P){
	TIME waktu = WaktuMulai(P);
	return NextNMenit(waktu, WaktuPelayanan(P));
}

/* Mengupdate semua waktu di antrian dari awal hingga akhir
 * I.S = Waktu di antrian belum dihitung dan terupdate
 * F.S = Waktu di antrian sudah dihitung dan terupdate */
void hitungWaktuAntrian(Queue *Q){
	addressQueue P = Front(*Q);
	addressQueue PrevP;
	
	if(P == Front(*Q)){
		WaktuMulai(P) = getWaktuMulai(P, Nil, *Q);
		WaktuSelesai(P) = getWaktuSelesai(P);
		PrevP = P;
	} 
	
	while (Next(PrevP) != Nil){
		WaktuMulai(Next(PrevP)) = getWaktuMulai(Next(PrevP), PrevP, *Q);
		WaktuSelesai(Next(PrevP)) = getWaktuSelesai(Next(PrevP));
		PrevP = Next(PrevP);
	}
}

/******************************************************************************************/
/*                                       Print                                            */
/******************************************************************************************/

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
		printf("\n						   Data antrian kosong!\n\n");
    } else {
		while(P != Nil){
			printf("					No. Antrian                 : %d\n", i++);
			printData(P);		
			printf("					-------------------------------------------\n");
			P = Next(P);
		}
	}
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
		printf("					   %d. %s\n", i++, jenisPenyakit[InfoPenyakit(addL)-1]);
		addL = Next(addL);
	}
}

/* I.S   : Data Belum Tampil 	*/
/* F.S   : Data sudah tampil dan code menjadi lebih ringkas */
void printData(addressQueue P){
	printf("					Nama Hewan                  : %s\n", NamaKucing(P));
	printf("					Nama Pemilik                : %s\n", NamaPemilik(P));
	printf("					Jenis Kelamin               : %c ", JenisKelamin(P));
	if (JenisKelamin(P) == 'J' || JenisKelamin(P) == 'j')
		printf ("(Jantan)\n");
	else 
		printf ("(Betina)\n");
		
	printf("					Datang di menit ke          : "); PrintJam(WaktuDatang(P)); 
	puts("\n					Penyakit yang Diderita      :");
	PrintInfoPenyakit(ListPenyakit(P));
	printf("					Nilai Prioritas             : %d ", Kategori(P));
	if (Kategori(P) == 1){
		printf ("(Satu)\n");
	} else if (Kategori(P) == 2){
		printf ("(Dua)\n");
	} else if (Kategori(P) == 3){
		printf ("(Tiga)\n");
	} else {
		printf ("(Empat)\n");
	}
	printf("					Estimasi Waktu Pelayanan    : %d Menit", WaktuPelayanan(P));
	printf("\n					Waktu Mulai Pelayanan       : "); PrintJam(WaktuMulai(P));
	printf("\n					Waktu Selesai Pelayanan     : "); PrintJam(WaktuSelesai(P));
	printf("\n");
}

void printDataDiproses(Queue sedangDiproses){	
   	
   	printf("\n\n\n\n");
   	printf("				            *** KUCING YANG SEDANG DIPROSES ***\n\n");
	printf("				-----------------------------------------------------------\n");
  	printf("				   Nama   | Waktu Pelayanan | Waktu Mulai | Waktu Selesai \n");
   	printf("				-----------------------------------------------------------\n");
   	
	if (IsQueueEmpty(sedangDiproses)) { // Jika Queue Kosong
	printf("				    -             -               -               -       \n");
	} else {
    	addressQueue P = sedangDiproses.Front;
   									
    	printf("				 %8s	  %d", NamaKucing(P), WaktuPelayanan(P));
    	printf("            ");
    	PrintJam(WaktuMulai(P));
		printf("           ");
    	PrintJam(WaktuSelesai(P));
    	printf("           \n");
	}
	printf("				-----------------------------------------------------------\n\n");
}


/******************************************************************************************/
/*                                    Pengecekan                                          */
/******************************************************************************************/

/*Mengembalikan nilai cek inputan jenis kelamin
  Jika inputan J/j/B/b maka menghasilkan hasil true
  Jika inputan lain maka akan menghasilkan false
*/
boolean cekInputJK(char jk){
	if ( jk == 'J' || jk == 'j' || jk == 'B' || jk == 'b' )
		return true;
	else {
		printf("					Jenis kelamin harus (B/b/J/j)!\n");
		return false;
	}
}

/* Mengirimkan hasil cek kevalidan inputan jumlah jenis penyakit*/
/* Jika inputan antara 1 sampai 10 maka akan mengirimkan true */
boolean cekInputJumlahPenyakit(int jumlahPenyakit){
	if ( jumlahPenyakit >= 1 && jumlahPenyakit <= 9 )
		return true;
	else{
		printf("					Jumlah penyakit harus berada di antara 1-9!\n"); 
		return false;
	}
}

/* Mengirimkan hasil cek kevalidan inputan jumlah jenis penyakit*/
/* Jika inputan antara 1 sampai 10 maka akan mengirimkan true */
boolean cekInputNomorPenyakit(int jumlahPenyakit, int penyakit[]){
	int i, j;
	
	// cek nomor yang diinputkan valid
	for ( i = 0; i < jumlahPenyakit; i++ ){
		if (!(penyakit[i] >= 1 && penyakit[i] <= 9)){
			printf("					Nomor penyakit harus berada di antara 1-9!\n");
			return false;
		}
	}
	
	// cek nomor yang diinputkan tidak berulang
	for ( i = 0; i < jumlahPenyakit; i++ ){
		for ( j = 0; j < jumlahPenyakit; j++){
			if ( i != j && penyakit[i] == penyakit[j]){
				printf("\n					Nomor penyakit tidak boleh duplikat!\n");
				return false;
			}
		}
	}
	
	return true;
}

void saveData(Queue *Q){
	addressQueue P;
	P = (*Q).Front;
	
	List L = ListPenyakit(P);
	addressList addL = First(L);
	int i = 1;
	
	FILE *out=fopen("RiwayatData.txt","a");
	
	fprintf(out, "Nama Hewan               : %s\n", NamaKucing(P));
	fprintf(out, "Nama Pemilik             : %s\n", NamaPemilik(P));
	fprintf(out, "Jenis Kelamin            : %c\n", JenisKelamin(P));
	fprintf(out, "Datang di menit ke       : %d\n", WaktuDatang(P));
	fprintf(out, "Penyakit yang Diderita   :\n");
	
	while (addL != Nil){
		fprintf(out, "        %d. %s\n", i++, jenisPenyakit[InfoPenyakit(addL)-1]);
		addL = Next(addL);
	}
	
	fprintf(out, "Nilai Prioritas          : %d\n", Kategori(P));
	fprintf(out, "Estimasi Waktu Pelayanan : %d\n", WaktuPelayanan(P));
	fprintf(out, "Waktu Mulai Pelayanan    : %d\n", WaktuMulai(P));
	fprintf(out, "Waktu Selesai Pelayanan  : %d\n", WaktuSelesai(P));
	fprintf(out, "------------------------------------\n\n");

	fclose(out);
}