#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "ADT Queue/queue.h"
#include "ADT List/list.h"

void awalAplikasi(){
	printf("\n\n\n\n\n\n				   ____ ____   _   _    ______   ______   _______");
	printf("\n				  |  _ V _  | | | | |  |  __  | |  ____| |__   __|");
	printf("\n				  | | | | | | | |_| |  | |__| | | |____     | |");
	printf("\n				  | | | | | | |_   _|  |  ____| |  ____|    | |");
	printf("\n				  | | |_| | |   | |    | |      | |____     | |");
	printf("\n				  |_|     |_|   |_|    |_|      |______|    |_|");
	printf("\n");
	printf("\n				  -----------------------------------------------");
	printf("\n				            By: Amelia, Fadhil, Tabitha");
	printf("\n				  -----------------------------------------------");
	printf("\n\n\n\n\n				  ");
	system("pause");
	system("cls");
}

void showMenu(){
	printf("\n				                    *** MAIN MENU ***");
	printf("\n");
	printf("\n					     1. Registrasi Data");
	printf("\n					     2. Daftar Antrian");
	printf("\n					     3. Pemanggilan Data");
	printf("\n					     4. Mencari Data Kucing");
	printf("\n					     5. Quit");
	printf("\n");
}

void showExit(){
	printf("\n\n\n\n\n\n");
	printf("\n			    	 _____     __  __    ______      _____    __  __    ______");
	printf("\n			    	| |  ||   | | | ||  |  ____||   | |  ||  | | | ||  |  ____||");
	printf("\n			    	| |__||   | |_| ||  | ||___     | |__||  | |_| ||  | ||___");
	printf("\n			    	| |   ||  |_   _||  |  ____||   | |   || |_   _||  |  ____||");
	printf("\n			    	| |   ||    | ||    | ||____    | |   ||   | ||    | ||____");
	printf("\n			    	|_|___||    |_||    |______||   |_|___||   |_||    |______||");
	printf("\n");
	printf("\n\n\n\n\n\n");
}

int main(){
	system("cls");
	Queue Q, sedangDiproses;
	CreateQueue(&Q);
	CreateQueue(&sedangDiproses);
	
	char menuPilihan;    
	
	awalAplikasi();
	
	do{
		printDataDiproses(sedangDiproses);
	 	showMenu();
    	printf("\n					     Masukkan Pilihan : "); scanf(" %c", &menuPilihan);
    	
    	if(menuPilihan == '1'){
    		system("cls");
			tambahData(&Q); 
			printf("\n				        ");     
    		system("pause");	
		                                                         
		}		                                                         
		else if(menuPilihan == '2'){
			system("cls");
			printAntrian(Q);
			printf("\n				        ");       
			system("pause");
		}
		else if(menuPilihan == '3'){
			system("cls");
			pemanggilanKucing(&Q, &sedangDiproses);  
			printf("\n				        ");     
			system("pause");

		}
		else if(menuPilihan == '4'){
			system("cls");
			pencarianDataKucing(Q);
			printf("\n				        ");     
			system("pause");
		}
		else if(menuPilihan == '5'){
			system("cls");
			showExit();
			exit(0);
		}
		else{
			printf("\n				Maaf angka yang anda inputkan tidak ada dalam menu\n");
			printf("\n				");
			system("pause");
		}
		system("cls");
	} while(menuPilihan != '5');
	
	return 0;

}