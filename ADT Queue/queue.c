#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../boolean.h"
#include "queue.h"
 
TIME waktuSelesaiAwal;    // untuk menampung waktu selesai
boolean awalHari = false;   // untuk menentukan apakah hari merupakan awal atau bukan
 
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
   Jika alokasi berhasil, modul mengembalikan P; Info(P) = X, Next(P) = NULL.
   P adalah pointer yang menunjuk ke node Queue sebagai hasil alokasi.
   Jika alokasi gagal, modul mengembalikan NULL. */
// Author : Tabitha Salsabila Permana
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

// Melakukan dealokasi elemen P (pointer menunjuk ke alamat node queue).
// I.S.: P terdefinisi.
// F.S.: P dikembalikan ke sistem.
// Author : Fadhil Radja Assydiq
void DealokasiQueue(addressQueue *P){
  	Next(*P) = Nil;
    free(*P);
}

/******************************************************************************************/
/*                                      Manajemen Memory                                  */
/******************************************************************************************/

// Membuat sebuah Queue kosong dengan Front(Q) = Nil dan Rear (Q) = Nil 
// I.S. Belum terbentuk Queue 
// F.S. Sudah terbentuk Queue 
// Author : Amelia Dewi Agustiani
void CreateQueue(Queue *Q){
  	Front(*Q) = Nil;
  	Rear(*Q) = Nil;
}

/* Mengetahui apakah Queue kosong atau tidak. 
   mengirimkan true, jika Queue Kosong yaitu Front(Q) = Nil dan Rear (Q) = Nil
   Sebaliknya false */
// Author : Tabitha Salsabila Permana
bool IsQueueEmpty(Queue Q){
  	if (Front(Q) == Nil && Rear(Q) == Nil) {
    	return true;
  	} else {
    	return false;
  	}
}

/* Mengirimkan banyaknya elemen queue jika Q berisi atrian atau 
   mengirimkan 0 jika Q kosong */
// Author : Fadhil Radja Assydiq
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

// Memasukkan info baru ke dalam Queue dengan aturan FIFO 
// I.S. Q mungkin kosong atau Q mungkin berisi antrian  
// F.S. info baru (data) menjadi Rear yang baru dengan node Rear yang lama mengaitkan pointernya ke node yang baru
// Author : Amelia Dewi Agustiani
void enQueue(Queue *Q, infotype data){
  	addressQueue current = Front(*Q);
  	addressQueue P = AlokasiQueue(data);
  
  	if (IsQueueEmpty(*Q)){
    	Front(*Q) = P;
  	} else {
    	if (KategoriPrioritas(Front(*Q)) < data.kategoriPrioritas || (KategoriPrioritas(Front(*Q)) == data.kategoriPrioritas && TimeToMenit(WaktuDatang(Front(*Q))) > TimeToMenit(data.waktuDatang)))
    { // untuk data jika kategoriPrioritas jika lebih besar di posisi front
        Next(P) = Front(*Q);
        Front(*Q) = P;
    }
    else 
    { // untuk data dari posisi antrian kedua sampai akhir
      // mencari data kategoriPrioritas sampai posisi tidak lebih dari
    	while (Next(current) != Nil && KategoriPrioritas(Next(current)) > data.kategoriPrioritas)
        {
            current = Next(current);
        }
          
        // mencari data kategoriPrioritas sampai posisi sama dengan 
      	while (Next(current) != Nil && KategoriPrioritas(Next(current)) == data.kategoriPrioritas && TimeToMenit(WaktuDatang(Next(current))) <= TimeToMenit(data.waktuDatang)){ 
        	current = Next(current);
      	}
      
        // akhir atau posisi yang sesuai
        Next(P) = Next(current);
        Next(current) = P;  
    }
  }
}

// Melakukan registrasi penambahan data pelanggan 
// I.S = Q mungkin kosong atau Q mungkin berisi antrian
// F.S = Data baru ditambahkan ke antrian 
// Author : Tabitha Salsabila Permana
void tambahData(Queue *Q, Queue sedangDiproses){
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
  	printf("					Keterangan :  J = Jantan, B = Betina \n");
  	printf("			        		      Jam & Menit Dipisah Spasi\n\n");
  	printf("\n					Nama Kucing                 : "); scanf("%s", &data.namaKucing);
  	fflush(stdin);
  	printf("					Nama Pemilik                : "); scanf("%s", &data.namaPemilik);
  	fflush(stdin);  
  	do {
    	printf("					Jenis Kelamin [J/B]         : "); scanf("%c", &data.jenisKelamin);
    	fflush(stdin);
  	} while (!cekInputJK(data.jenisKelamin));
  
  	if(IsQueueEmpty(sedangDiproses)){
    	do {
      		printf("					Datang di menit ke [HH MM]  : "); scanf("%d %d", &data.waktuDatang.Hour, &data.waktuDatang.Minute);
      		fflush(stdin);
    	} 	while (!IsJamValid(data.waktuDatang, data.waktuDatang));
  	} else {
    	do {
	    	printf("					Datang di menit ke [HH MM]  : "); scanf("%d %d", &data.waktuDatang.Hour, &data.waktuDatang.Minute);
    		fflush(stdin);  
    	} while (!IsJamValid(data.waktuDatang, WaktuDatang(Front(sedangDiproses))));
  	}
  
  	printf("\n");
  	printPenyakit();
  	printf("\n");
  
  	do {
    	printf("					Masukkan Jumlah Penyakit             : "); scanf("%d", &totalPenyakit);
    	fflush(stdin);
  	} while (!cekInputJumlahPenyakit(totalPenyakit));
  
  	do {
    	puts("					Nomor Penyakit yang Diderita  : ");
    	for (i=0; i<totalPenyakit; i++){
        	printf("					");
      		scanf(" %d", &tempPenyakit[i]);
    	}
  	} while (!cekInputNomorPenyakit(totalPenyakit, tempPenyakit));
  	
  	// menampung jumlah penyakit sesuai kategoriPrioritas
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
  
  	data.kategoriPrioritas = getPrioritas(kategoriRingan, kategoriSedang, kategoriBerat);
  	data.waktuPelayanan = getWaktuPelayanan(kategoriRingan, kategoriSedang, kategoriBerat);
  	enQueue(Q, data); // enqueue data ke antrian
  	hitungWaktuAntrian(&(*Q)); // untuk menambahkan waktu mulai dan selesai

  	printf("\n");
  	printf("					       Anda Sudah Terdaftar!     \n\n");
}

/******************************************************************************************/
/*                                  Pemanggilan Data Kucing                               */
/******************************************************************************************/

// Proses: Mengambil info pada Front(Q) dan mengeluarkannya dari Queue dengan aturan FIFO
// I.S. Q mungkin kosong atau Q mungkin berisi antrian 
// F.S. info yang diambil = nilai elemen Front pd I.S.  
// Author : Fadhil Radja Assydiq
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

// Memanggil data kucing teratas di antrian
// I.S = Data kucing belum dipanggil (dequeue)
/* F.S = Data kucing sudah dipanggil (dequeue) 
        jika antrian kosong maka akan tampil "Data antrian kosong!"*/
// Author : Fadhil Radja Assydiq        
void pemanggilanKucing(Queue *Q, Queue *sedangDiproses){
  	system ("cls");
  	addressQueue P;
  	infotype R; 
  	int i=1;
  	char pilih;
  
  	P = (*Q).Front;
  
  	printf("					===========================================\n");
    printf("					          Daftar Antrian Kucing\n");
    printf("					===========================================\n");
  
  	if (P == Nil) { // Jika Queue Kosong
    	printf("\n					           Data antrian kosong!\n\n");
    } else {
    	printf("\n					No. Antrian                 : %d\n", i++);
    	printData(P); 
    	printf("					------------------------------------\n");
    
    	R = InfoFront(*Q);
    	printf("					Memulai Proses Pelayanan Untuk %s? [Y/N] ", R.namaKucing);
    	fflush(stdin);
    	scanf("%c", &pilih);
    
	    if(pilih == 'Y' || pilih == 'y'){
      	saveData(Q); // menyimpan data ke file
      	Front(*sedangDiproses) = AlokasiQueue(Info(Front(*Q))); // menyimpan data ke data yang sedang di proses
      	if(awalHari == false){
        	waktuSelesaiAwal = WaktuSelesai(Front(*Q));
        	awalHari = true;
      	}
      	deQueue(Q); // melakukan dequeue
      	printf("\n");
      	printf("					             Harap bersabar \n");
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

// Mencari data kucing di antrian
// I.S = Data belum dicari
/* F.S = Data kucing akan muncul jika ada di antrian
         Jika tidak ada maka akan tampil "Data kucing tidak ada di antrian!" */
// Author : Amelia Dewi Agustiani
void pencarianDataKucing(Queue Q){
  	char namaKucing[25];
  	char namaPemilik[25];
  	addressQueue P;
  
  	printf("					===========================================\n");
    printf("					         Daftar Pencarian Kucing\n");
    printf("					===========================================\n");
  
  	printf("\n					Masukan Nama Kucing : ");
  	scanf("%s", &namaKucing);
  	printf("					Masukan Nama Pemilik : ");
  	scanf("%s", &namaPemilik);
  
  	printf("\n					-------------------------------------------\n");
  
  	P = searchData(namaKucing, namaPemilik, Q);
  	if (P == Nil){
    	printf("\n					     Data kucing tidak ada di antrian!\n");
  	} else {
    	printData(P); 
  	} 
}

// Mencari alamat dari kucing di queue
// I.S = Data belum dicari
/* F.S = Data sudah dicari jika ada maka akan mengirimkan alamat,
         Jika tidak maka akan mengirimkan null */
// Author : Amelia Dewi Agustiani
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

/* Mengembalikan kategoriPrioritas penyakit kucing 
   1: ringan, 2: sedang, 3: berat 
*/
// Author : Amelia Dewi Agustiani
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
// Author : Amelia Dewi Agustiani
int getWaktuPenyakit(int Penyakit){
  	if (Penyakit<4){
    	return 15; // penyakit ringan
  	} else if (Penyakit<7){
    	return 30; // penyakit sedang
  	} else if (Penyakit<10){
    	return 40; // penyakit berat
  	}
}

/* Mengembalikan kategoriPrioritas prioritas penyakit kucing */
// Author : Amelia Dewi Agustiani
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
// Author : Fadhil Radja Assydiq
int getWaktuPelayanan(int Ringan, int Sedang, int Berat){
  	return (Ringan*15) + (Sedang*30) + (Berat*45);
}

/* Menghitung waktu mulai antrian */
// Author : Amelia Dewi Agustiani
TIME getWaktuMulai(addressQueue P, addressQueue P2, Queue Q){
  	TIME mulai;
  	mulai.Hour = 0;
  	mulai.Minute = 0;
  	if (Front(Q) == P){ // jika ada pergantian di front
    	if (awalHari == false){
      		mulai = WaktuDatang(P); 
    	} else {
      		mulai = NextNMenit(waktuSelesaiAwal, 1);
    	}
  	} else if (TimeToMenit(WaktuDatang(P)) > TimeToMenit(WaktuSelesai(P2))) { 
    	// jika waktu datang data selanjutnya lebih besar dari waktu selesai data sebelumnya
    	mulai = WaktuDatang(P);
  	} else {
    	// jika waktu datang data selanjutnya lebih kecil dari waktu selesai data sebelumnya
    	mulai = NextNMenit(WaktuSelesai(P2),1);
  	}
  
  	return mulai;
}

/* Menghitung waktu mulai antrian */
// Author : Tabitha Salsabila Permana
TIME getWaktuSelesai(addressQueue P){
  	TIME waktu = WaktuMulai(P);
  	return NextNMenit(waktu, WaktuPelayanan(P));
}

// Mengupdate semua waktu di antrian dari awal hingga akhir
// I.S = Waktu di antrian belum dihitung dan terupdate
// F.S = Waktu di antrian sudah dihitung dan terupdate 
// Author : Amelia Dewi Agustiani
void hitungWaktuAntrian(Queue *Q){
  	addressQueue P = Front(*Q);
  	addressQueue PrevP;
  
  	if(P == Front(*Q)){ // untuk awal antrian 
    	WaktuMulai(P) = getWaktuMulai(P, Nil, *Q);
    	WaktuSelesai(P) = getWaktuSelesai(P);
    	PrevP = P;
  	} 
  
  	while (Next(PrevP) != Nil){ // untuk data selain awal antrian
    	WaktuMulai(Next(PrevP)) = getWaktuMulai(Next(PrevP), PrevP, *Q);
    	WaktuSelesai(Next(PrevP)) = getWaktuSelesai(Next(PrevP));
    	PrevP = Next(PrevP);
  	}
}

/******************************************************************************************/
/*                                       Print                                            */
/******************************************************************************************/

// Menampilkan antrian 
// I.S = Antrian belum tampil
// F.S = Antrian sudah tampil, jika data kosong maka akan tampil "Data antrian kosong!"*/
// Author : Amelia Dewi Agustiani
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
    	printf("\n					            Data antrian kosong!\n\n");
    } else {
    	while(P != Nil){
      		printf("					No. Antrian                 : %d\n", i++);
      		printData(P);   
      		printf("					-------------------------------------------\n");
      		P = Next(P);
    	}
  	}
}

// Menampilkan list penyakit
/* I.S   : List penyakit belum tampil */
/* F.S   : List penyakit sudah tampil */
// Author : Tabitha Salsabila Permana
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
// 
// I.S   : List mungkin kosong  
/* F.S   : Jika list tidak kosong, semua info yang disimpan pada
           elemen list di-print          
           Jika list kosong, hanya menuliskan "List Kosong" */
// Author : Amelia Dewi Agustiani
void PrintInfoPenyakit(List L){
  	addressList addL = First(L);
  	int i = 1;
  	while (addL != Nil){
    	printf("					   %d. %s\n", i++, jenisPenyakit[InfoPenyakit(addL)-1]);
    	addL = Next(addL);
  	}
}

// Menampilkan data kucing
// I.S   : Data Belum Tampil  
// F.S   : Data sudah tampil dan code menjadi lebih ringkas 
// Author : Amelia Dewi Agustiani
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
  	printf("					Nilai Prioritas             : %d ", KategoriPrioritas(P));
  	if (KategoriPrioritas(P) == 1){
    	printf ("(Satu)\n");
  	} else if (KategoriPrioritas(P) == 2){
    	printf ("(Dua)\n");
  	} else if (KategoriPrioritas(P) == 3){
    	printf ("(Tiga)\n");
  	} else {
    	printf ("(Empat)\n");
  	}
  	printf("					Estimasi Waktu Pelayanan    : %d Menit", WaktuPelayanan(P));
  	printf("\n					Waktu Mulai Pelayanan       : "); PrintJam(WaktuMulai(P));
  	printf("\n					Waktu Selesai Pelayanan     : "); PrintJam(WaktuSelesai(P));
  	printf("\n");
}

// Menampilkan data kucing yang sedang di proses
// I.S : data kucing yang sedang di proses belum tampil
// F.S : data kucing yang sedang di proses sudah tampil
// Author : Amelia Dewi Agustiani
void printDataDiproses(Queue sedangDiproses){ 
    printf("\n\n\n\n");
    printf("			                    *** KUCING YANG SEDANG DIPROSES ***\n\n");
  	printf("			---------------------------------------------------------------------------\n");
    printf("			    Nama   | Waktu Datang | Waktu Pelayanan | Waktu Mulai | Waktu Selesai \n");
    printf("			---------------------------------------------------------------------------\n");
    
  	if (IsQueueEmpty(sedangDiproses)) { // Jika Queue Kosong
  		printf("			     -             -               -               -               -\n");
  	} else {
      	addressQueue P = sedangDiproses.Front;
                    
	    printf("			%8s         ", NamaKucing(P)); 
		PrintJam(WaktuDatang(P));
		printf("            %3d            ", WaktuPelayanan(P));
	    PrintJam(WaktuMulai(P));
	    printf("          ");
	    PrintJam(WaktuSelesai(P));
	    printf("\n");
  	}
  	printf("			---------------------------------------------------------------------------\n");
}

/******************************************************************************************/
/*                                    Pengecekan                                          */
/******************************************************************************************/

/*Mengembalikan nilai cek inputan jenis kelamin
  Jika inputan J/j/B/b maka menghasilkan hasil true
  Jika inputan lain maka akan menghasilkan false */
// Author : Tabitha Salsabila Permana
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
// Author : Fadhil Radja Assydiq
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
// Author : Amelia Dewi Agustiani
boolean cekInputNomorPenyakit(int jumlahPenyakit, int penyakit[]){
  	int i, j;
  	
  	// cek nomor yang diinputkan valid
  	for ( i = 0; i < jumlahPenyakit; i++ ){
    	if (!(penyakit[i] >= 1 && penyakit[i] <= 9)){
      	printf("\n					Nomor penyakit harus berada di antara 1-9!\n");
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

// Menyimpan data riwayat ke file
// I.S : Data kucing belum tersimpan di file
// F.S : Data kucing sudah tersimpan 
// Author : Fadhil Radja Assydiq & Amelia Dewi Agustiani
void saveData(Queue *Q){
	int i, n=2;
	Riwayat *s;
	addressQueue P=Front(*Q);
	
	FILE *fp;
	
	s=(Riwayat*)calloc(n, sizeof(Riwayat));	
	fp = fopen("RiwayatData.dat", "a");
    
    if (fp == NULL)
    {
        /* Unable to open file hence exit */
        printf("\nUnable to open 'RiwayatData.dat' file.\n");
        printf("Please check whether file exists and you have write privilege.\n");
        exit(EXIT_FAILURE);
    }
	
	strcpy(s[0].namaKucing,NamaKucing(P));
	strcpy(s[0].namaPemilik,NamaPemilik(P));
	s[0].jenisKelamin = JenisKelamin(P);
	s[0].waktuDatang = WaktuDatang(P);
	s[0].waktuMulai = WaktuMulai(P);
	s[0].waktuSelesai = WaktuSelesai(P);
	s[0].waktuPelayanan = WaktuPelayanan(P);
	s[0].kategoriPrioritas = KategoriPrioritas(P);
	
	addressList L = First(ListPenyakit(P));
	i = 0;
	while(L != Nil){
		s[0].listPenyakit[i].penyakit = L->info.penyakit;
		s[0].listPenyakit[i].kategori = L->info.kategori;
		s[0].listPenyakit[i].waktu = L->info.waktu;
		i++;
		L = Next(L);
	}
	
	fwrite(&s[0],sizeof(Riwayat),1,fp);
	
	fclose(fp);
}

void pencarianRiwayatDataKucing(){
	char namaKucing[20], namaPemilik[20];
	printf("					===========================================\n");
    printf("					         Pencarian Riwayat Kucing\n");
    printf("					===========================================\n");
  
  	printf("\n					Masukan Nama Kucing : ");
  	scanf("%s", &namaKucing);
  	printf("					Masukan Nama Pemilik : ");
  	scanf("%s", &namaPemilik);
  
  	printf("\n					-------------------------------------------\n");
	
	int i, j, n;
	Riwayat *s;
	boolean cari = false;
	
	FILE *fp;
	fp = fopen("RiwayatData.dat", "r");
	fseek(fp,0,SEEK_END);
	n=ftell(fp)/sizeof(Riwayat);
	s=(Riwayat*)calloc(n, sizeof(Riwayat));	

	if (fp == NULL)
    {
        /* Unable to open file hence exit */
        printf("\nUnable to open 'RiwayatData.dat' file.\n");
        printf("Please check whether file exists and you have write privilege.\n");
        exit(EXIT_FAILURE);
    }

	rewind(fp);
	for(i = 0; i < n; i++){
		fread(&s[i],sizeof(Riwayat),1,fp);
		if (strcmp(s[i].namaKucing, namaKucing) == 0 && strcmp(s[i].namaPemilik, namaPemilik) == 0){
			printf("					Nama Hewan                  : %s\n", s[i].namaKucing);
		  	printf("					Nama Pemilik                : %s\n", s[i].namaPemilik);
		  	printf("					Jenis Kelamin               : %c ", s[i].jenisKelamin);
		  	if (s[i].jenisKelamin == 'J' || s[i].jenisKelamin == 'j')
		    	printf ("(Jantan)\n");
		  	else 
		    	printf ("(Betina)\n");
		    
		  	printf("					Datang di menit ke          : "); PrintJam(s[i].waktuDatang); 
		  	puts("\n					Penyakit yang Diderita      :");
		  	for ( j = 0; j < 9; j++){
		    	if (s[i].listPenyakit[j].penyakit > 0 && s[i].listPenyakit[j].penyakit < 10){
		    		printf("					   %d. %s\n", j+1, jenisPenyakit[(s[i].listPenyakit[j].penyakit)-1]);
				}
			}
		  	printf("					Nilai Prioritas             : %d ", s[i].kategoriPrioritas);
		  	if (s[i].kategoriPrioritas == 1){
		    	printf ("(Satu)\n");
		  	} else if (s[i].kategoriPrioritas == 2){
		    	printf ("(Dua)\n");
		  	} else if (s[i].kategoriPrioritas == 3){
		    	printf ("(Tiga)\n");
		  	} else {
		    	printf ("(Empat)\n");
		  	}
		  	printf("					Estimasi Waktu Pelayanan    : %d Menit", s[i].waktuPelayanan);
		  	printf("\n					Waktu Mulai Pelayanan       : "); PrintJam(s[i].waktuMulai);
		  	printf("\n					Waktu Selesai Pelayanan     : "); PrintJam(s[i].waktuSelesai);
		  	printf("\n					-------------------------------------------\n");
		  	cari = true;
		}
	}
	
	if (cari == false){
		printf("\n					     Data kucing tidak ada di riwayat!\n");
	}
	
	fclose(fp);
}

void printRiwayatDataKucing(){
	int i, j, n;
	Riwayat *s;
	boolean isi = false;
	
	FILE *fp;
	fp = fopen("RiwayatData.dat", "r");
	fseek(fp,0,SEEK_END);
	n=ftell(fp)/sizeof(Riwayat);
	s=(Riwayat*)calloc(n, sizeof(Riwayat));	

	if (fp == NULL)
    {
        /* Unable to open file hence exit */
        printf("\nUnable to open 'RiwayatData.dat' file.\n");
        printf("Please check whether file exists and you have write privilege.\n");
        exit(EXIT_FAILURE);
    }

	rewind(fp);
	printf("					===========================================\n");
    printf("					            Data Riwayat Kucing\n");
    printf("					===========================================\n");
	for(i = 0; i < n; i++){
		fread(&s[i],sizeof(Riwayat),1,fp);
		printf("					Nama Hewan                  : %s\n", s[i].namaKucing);
	  	printf("					Nama Pemilik                : %s\n", s[i].namaPemilik);
	  	printf("					Jenis Kelamin               : %c ", s[i].jenisKelamin);
		if (s[i].jenisKelamin == 'J' || s[i].jenisKelamin == 'j')
	    	printf ("(Jantan)\n");
	 	else 
	    	printf ("(Betina)\n");
	    
	  	printf("					Datang di menit ke          : "); PrintJam(s[i].waktuDatang); 
	  	puts("\n					Penyakit yang Diderita      :");
	  	for ( j = 0; j < 9; j++){
	    	if (s[i].listPenyakit[j].penyakit > 0 && s[i].listPenyakit[j].penyakit < 10){
	    		printf("					   %d. %s\n", j+1, jenisPenyakit[(s[i].listPenyakit[j].penyakit)-1]);
			}
		}
	  	printf("					Nilai Prioritas             : %d ", s[i].kategoriPrioritas);
	 	if (s[i].kategoriPrioritas == 1){
	    	printf ("(Satu)\n");
	  	} else if (s[i].kategoriPrioritas == 2){
	    	printf ("(Dua)\n");
	  	} else if (s[i].kategoriPrioritas == 3){
	    	printf ("(Tiga)\n");
	  	} else {
	    	printf ("(Empat)\n");
	  	}
	  	printf("					Estimasi Waktu Pelayanan    : %d Menit", s[i].waktuPelayanan);
	  	printf("\n					Waktu Mulai Pelayanan       : "); PrintJam(s[i].waktuMulai);
	  	printf("\n					Waktu Selesai Pelayanan     : "); PrintJam(s[i].waktuSelesai);
	  	printf("\n					-------------------------------------------\n");
	  	isi = true;
	}
	
	if (isi == false){
		printf("					     Data riwayat kucing tidak ada!\n");
	}
	
	fclose(fp);
}