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
// Mengirimkan komponen Menit dari J

/* Set nilai komponen */
void SetHour(TIME *J, int newHour);
// Set nilai Hour dari J
void SetMinute(TIME *J, int newMinute);
// Set nilai Minute dari J

/*****************************************************************/
/** {Kelompok Baca/Tulis} **/
void PrintJam (TIME J);
/* I.S. : J sembarang */
/* F.S. : Nilai J ditulis dg format HH:MM */
/* Proses : menulis nilai setiap komponen J ke layar */ 
/*****************************************************************/

/** { kelompok Validasi Type } **/
boolean IsJamValid (TIME J);
/* Mengirim true jika H,M,S dapat membentuk J yang valid */
/* dipakai untuk mentest SEBELUM membentuk sebuah TIME */
/* Konstruktor: Membentuk sebuah TIME dari komponen-komponennya */
/*****************************************************************/

/** {Kelompok Konversi Terhadap Type} **/
long int TimeToMenit (TIME J);
/* Diberikan sebuah TIME, mengkonversi menjadi Menit */

TIME MenitToTime (long int N); 
/* Mengirim konversi detik ke TIME. Pada beberapa bahasa, representasi integer tidak cukup untuk menampung N */
/*****************************************************************/

TIME NextNMenit (TIME J, int N);
/* Menambah menit dengan N*/

#endif

