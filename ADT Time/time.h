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

/******************************************************************************************/
/*                                 Konstruktor membentuk ADT TIME                         */
/******************************************************************************************/

// Membentuk sebuah TIME dari komponen-komponennya yang valid 
// Pre condition : HH,MM,SS valid untuk membentuk TIME
// I.S : J tidak terdefinisi, tidak diketahui nilainya
/* F.S : membentuk sebuah TIME dari komponen-komponennya dengan J diinisialisasi nilainya dengan 
   Hour = HH, Minute = MM, Second = SS  */
// Author : Amelia Dewi Agustiani
void CreateTIME (TIME *J, int HH, int MM);

/******************************************************************************************/
/*                    Operasi terhadap komponen : selektor Get dan Set                    */
/******************************************************************************************/

// Mengirimkan komponen Hour dari J
// Author : Amelia Dewi Agustiani
int GetHour(TIME J);

// Mengirimkan komponen Menit dari J
// Author : Amelia Dewi Agustiani
int GetMinute(TIME J);

// Set nilai Hour dari J
// Author : Amelia Dewi Agustiani
void SetHour(TIME *J, int newHour);

// Set nilai Minute dari J
// Author : Amelia Dewi Agustiani
void SetMinute(TIME *J, int newMinute);

/******************************************************************************************/
/*                                   Kelompok Baca/Tulis                                  */
/******************************************************************************************/

/* Proses : menulis nilai setiap komponen J ke layar */ 
/* I.S. : J sembarang */
/* F.S. : Nilai J ditulis dg format HH:MM */
// Author : Amelia Dewi Agustiani
void PrintJam (TIME J);

/******************************************************************************************/
/*                                 kelompok Validasi Type                                 */
/******************************************************************************************/

/* Mengirim true jika H,M,S dapat membentuk J yang valid */
/* dipakai untuk mentest SEBELUM membentuk sebuah TIME */
// Author : Amelia Dewi Agustiani
boolean IsJamValid (TIME J);

/******************************************************************************************/
/*                              Kelompok Konversi Terhadap Type                           */
/******************************************************************************************/

/* Diberikan sebuah TIME, mengkonversi menjadi Menit */
// Author : Amelia Dewi Agustiani
long int TimeToMenit (TIME J);

/* Mengirim konversi detik ke TIME. Pada beberapa bahasa, representasi integer tidak cukup untuk menampung N */
// Author : Amelia Dewi Agustiani
TIME MenitToTime (long int N); 

/* Menambah menit dengan N*/
// Author : Amelia Dewi Agustiani
TIME NextNMenit (TIME J, int N);

#endif

