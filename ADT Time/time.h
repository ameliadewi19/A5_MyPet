/*
 *	File : jam.h
 *	Nama : Asri Maspupah
 *  Modified : Amelia Dewi Agustiani
 *	deskripsi : Header file dari prototype Time
 *
 */

#ifndef TIME_H
#define TIME_H
#include "../boolean.h"

typedef struct {
int Hour ; /* Hour [0..23] */
int Minute; /* Minute [0..59] */
} TIME;

/* Prototype ADT Time */

/** Konstruktor membentuk ADT TIME **/
void CreateTIME (TIME *J, int HH, int MM);
/* Membentuk sebuah TIME dari komponen-komponennya yang valid 
     Pre condition : HH,MM,SS valid untuk membentuk TIME
     I.S : J tidak terdefinisi, tidak diketahui nilainya
     F.S : membentuk sebuah TIME dari komponen-komponennya dengan J diinisialisasi nilainya dengan 
	   Hour = HH, Minute = MM, Second = SS 
*/
/*****************************************************************/

/** { Operasi terhadap komponen : selektor Get dan Set } **/
/* Selektor TIME **/
int GetHour(TIME J);
// Mengirimkan komponen Hour dari J
int GetMinute(TIME J);
// Mengirimkan komponen Hour dari J

/* Set nilai komponen */
void SetHour(TIME *J, int newHour);
// Mengirimkan komponen Hour dari J
void SetMinute(TIME *J, int newMinute);
// Mengirimkan komponen Hour dari J

/*****************************************************************/

/** {Kelompok Baca/Tulis} **/
void ReadTIME (TIME *J);
/* I.S. : J tidak terdefinisi */
/* F.S. : J terdefinisi dan merupakan TIME yang valid */
/* Proses : mengulangi membaca komponen H,M,S sehingga membentuk J yang valid.*/
/* Tidak mungkin menghasilkan J yang tidak valid */

void PrintTIME (TIME J);
/* I.S. : J sembarang */
/* F.S. : Nilai J ditulis dg format HH:MM:SS */
/* Proses : menulis nilai setiap komponen J ke layar */ 
/*****************************************************************/

/** { kelompok Validasi Type } **/
boolean IsJamValid (TIME J);
/* Mengirim true jika H,M,S dapat membentuk J yang valid */
/* dipakai untuk mentest SEBELUM membentuk sebuah TIME */
/* Konstruktor: Membentuk sebuah TIME dari komponen-komponennya */
/*****************************************************************/

/** { operator aritmatika } **/
void Reset (TIME *J);
/* I.S. J sembarang; F.S. J bernilai �nol� yaitu semua komponennya bernilai 0*/
/* Me-reset nilai J menjadi 0:0 */

/** {Kelompok Konversi Terhadap Type} **/
long int TimeToMenit (TIME J);
/* Diberikan sebuah TIME, mengkonversi menjadi Detik */
/* Rumus : detik = 3600*hour+menit*60 + detik */
/* nilai maksimum = 3600*23+59*60+59*60 */
/* hati-hati dengan representasi integer pada bahasa implementasi */
/* kebanyakan sistem mengimplementasi integer, */
/* bernilai maksimum kurang dari nilai maksimum hasil konversi */

TIME MenitToTime (long int N); 
/* Mengirim konversi detik ke TIME. Pada beberapa bahasa, representasi integer tidak cukup untuk menampung N */
/*****************************************************************/

void PrintJam (TIME J);

TIME NextNMenit (TIME J, int N);

#endif

