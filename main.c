#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "queue.h"
#include "list.h"

void showMenu(){
	system("cls");
	printf("\n\n\n\n\n				   ____ ____   _   _    ______   ______   _______");
	printf("\n				  |  _ V _  | | | | |  |  __  | |  ____| |__   __|");
	printf("\n				  | | | | | | | |_| |  | |__| | | |____     | |");
	printf("\n				  | | | | | | |_   _|  |  ____| |  ____|    | |");
	printf("\n				  | | |_| | |   | |    | |      | |____     | |");
	printf("\n				  |_|     |_|   |_|    |_|      |______|    |_|");
	printf("\n");
	printf("\n				  -----------------------------------------------");
	printf("\n				            By: Amelia, Fadhil, Tabitha");
	printf("\n				  -----------------------------------------------");
	printf("\n");
	printf("\n					     1 . Registrasi Data");
	printf("\n					     2 . Daftar Antrian");
	printf("\n					     3 . Pemanggilan Data");
	printf("\n					     4 . Mencari Data Kucing");
	printf("\n					     5 . Quit");
	printf("\n");
}

int main(){
	system("cls");
	Queue Q;
	CreateQueue(&Q);
	
	
	char menuPilihan;    
	
	do{
	 	showMenu();
    	printf("\n					     Masukkan Pilihan : "); scanf(" %c", &menuPilihan);
    	
    	if(menuPilihan == '1'){
    		system("cls");
			tambahData(&Q);  
    		system("pause");	
		                                                         
		}		                                                         
		else if(menuPilihan == '2'){
			system("cls");
			printAntrian(Q);       
			system("pause");

		}
		else if(menuPilihan == '3'){
			system("cls");
			pemanggilanKucing(&Q);  
			system("pause");

		}
		else if(menuPilihan == '4'){
			system("cls");
			pencarianDataKucing(Q);
			system("pause");
		}
		else if(menuPilihan == '5'){
			system("cls");
			exit(0);
		}
		else{
		
			printf("\n				Maaf angka yang anda inputkan tidak ada dalam menu\n");
			system("pause");
	
		}
	
	} while(menuPilihan != '5');
	
	return 0;

}