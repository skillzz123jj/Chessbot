#include <iostream>
#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#include <iostream>
#include <string>
#include "kayttoliittyma.h"
#include "Siirto.h"
#include "asema.h"

using namespace std; 

int main()
{
	Peli peli(Kayttoliittyma::getInstance()->kysyVastustajanVari());
	
	wcout << "HeippariShakki\n";
	wcout << "Tervetuloa pelaamaan!\n";
	//int lopetus = 100;
	Asema asema; 
	Kayttoliittyma::getInstance()->aseta_asema(&asema);
	Kayttoliittyma::getInstance()->piirraLauta();
	
	while (true)
	{
	
		Siirto siirto;
		siirto = Kayttoliittyma::getInstance()->
		annaVastustajanSiirto();
		asema.paivitaAsema(&siirto);
	
		//system("cls");
		Kayttoliittyma::getInstance()->piirraLauta();
	}
/*
* z
	std::list<Siirto> lista;
	int koneenVari = peli.getKoneenVari();

	while (lopetus != 0)*/// {
	/*	lista.clear();*/
	//	wcout << "\n";
	//	// Tarkasta onko peli loppu?
	//	asema.annaLaillisetSiirrot(lista);
	//	if (lista.size() == 0) {
	//		lopetus = 0;
	//		std::wcout << "Peli loppui";
	//		continue;
	//	}
	//	if (asema.getSiirtovuoro() == koneenVari) {
	//		MinMaxPaluu paluu;
	//		if (koneenVari == 0) {
	//			paluu = asema.maxi(3);
	//		}
	//		else {
	//			paluu = asema.mini(3);
	//		}
	//		siirto = paluu._parasSiirto;
	//	}
	//	else {
	//	}
	//}


	
	return 0;
}
