#include <stdio.h>
#include <stdlib.h>
#include "time.h"

/******************************************************************************************/
/*                                 Konstruktor membentuk ADT TIME                         */
/******************************************************************************************/

// Membentuk sebuah TIME dari komponen-komponennya yang valid 
// Pre condition : HH,MM,SS valid untuk membentuk TIME
// I.S : J tidak terdefinisi, tidak diketahui nilainya
/* F.S : membentuk sebuah TIME dari komponen-komponennya dengan J diinisialisasi nilainya dengan 
   Hour = HH, Minute = MM, Second = SS  */
// Author : Amelia Dewi Agustiani
void CreateTIME (TIME *J, int HH, int MM)
{
    (*J).Hour = HH;
    (*J).Minute = MM;
}

/******************************************************************************************/
/*                    Operasi terhadap komponen : selektor Get dan Set                    */
/******************************************************************************************/

// Mengirimkan komponen Hour dari J
// Author : Amelia Dewi Agustiani
int GetHour(TIME J)
{
    return J.Hour;
}

// Mengirimkan komponen Menit dari J
// Author : Amelia Dewi Agustiani
int GetMinute(TIME J)
{
    return J.Minute;
}

// Set nilai Hour dari J
// Author : Amelia Dewi Agustiani
void SetHour(TIME *J, int newHour)
{
    (*J).Hour = newHour;
}

// Set nilai Minute dari J
// Author : Amelia Dewi Agustiani
void SetMinute(TIME *J, int newMinute)
{
    (*J).Minute = newMinute;
}

/******************************************************************************************/
/*                                   Kelompok Baca/Tulis                                  */
/******************************************************************************************/

/* Proses : menulis nilai setiap komponen J ke layar */ 
/* I.S. : J sembarang */
/* F.S. : Nilai J ditulis dg format HH:MM */
// Author : Amelia Dewi Agustiani
void PrintJam(TIME J){
	printf("%02d:%02d", GetHour(J), GetMinute(J));
}

/******************************************************************************************/
/*                                 kelompok Validasi Type                                 */
/******************************************************************************************/

/* Mengirim true jika H,M,S dapat membentuk J yang valid */
/* dipakai untuk mentest SEBELUM membentuk sebuah TIME */
// Author : Amelia Dewi Agustiani
boolean IsJamValid (TIME J)
{
	boolean cek = ((J.Hour >= 0) && (J.Hour <= 23)) && ((J.Minute >= 0) && (J.Minute <= 59)); 
	if (cek == false){
		printf("					Jam yang anda inputkan salah!\n");
	}
    return cek;
}

/******************************************************************************************/
/*                              Kelompok Konversi Terhadap Type                           */
/******************************************************************************************/

/* Diberikan sebuah TIME, mengkonversi menjadi Menit */
// Author : Amelia Dewi Agustiani
long int TimeToMenit (TIME J)
{
    return (60 * J.Hour) + J.Minute;
}

/* Mengirim konversi detik ke TIME. Pada beberapa bahasa, representasi integer tidak cukup untuk menampung N */
// Author : Amelia Dewi Agustiani
TIME MenitToTime (long int N)
{
    TIME J;
	
    J.Hour = N/60;
    N %= 60;
	
    J.Minute = N;
	
	return J;
}

/* Menambah menit dengan N*/
// Author : Amelia Dewi Agustiani
TIME NextNMenit (TIME J, int N)
{
    int menit = TimeToMenit(J) + N;
    return MenitToTime(menit);
}
