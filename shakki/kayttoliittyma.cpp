#include <Windows.h>
#include <iostream>
#include <string>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include "kayttoliittyma.h"

using namespace std;


Kayttoliittyma* Kayttoliittyma::instance = 0;


Kayttoliittyma* Kayttoliittyma::getInstance()
{
	if (instance == 0)
		instance = new Kayttoliittyma();
	return instance;
}


void Kayttoliittyma::piirraLauta()
{
	wchar_t kirjaimet[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
	wint_t numerot = 8;

	//asetetaan tulostus UTF16 tyyppiseksi, jotta shakkinappulat n‰kyv‰t oikein
	_setmode(_fileno(stdout), _O_U16TEXT);

	for (int i = 0; i < 8; i++)
	{	
		for (int j = 0; j < 8; j++)
		{
			if (j == 0)
			{
				//Muutetaan tulostus standardiksi, kirjainrivin tulostusta varten
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				wcout << numerot;
				numerot -= 1;

			}

			if (i % 2 == 0)
			{
				if (j % 2 == 0)
				{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
					BACKGROUND_GREEN | BACKGROUND_BLUE);
				}
				else
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY |
						BACKGROUND_GREEN);
				}
			}
			else
			{
				if (j % 2 == 0)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY |
						BACKGROUND_GREEN);		
				}
				else
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
						BACKGROUND_GREEN | BACKGROUND_BLUE);
				}
			}

			if (_asema->_lauta[i][j] != NULL)
			{
				//Koska halutaan nappula keskelle ruutua, tulostetaan ensin 1 tyhj‰, sitten nappula ja 2 tyhj‰‰
				wcout <<L" ";
				wcout << _asema->_lauta[i][j]->getUnicode();
				wcout <<L"  ";
			}
			else
			{
				wcout <<L"    ";
			}
			
			//Jos viimeisell‰ neliˆll‰ riviss‰, vaihdetaan rivi
			if (j == 7)
			{
				wcout << "\n";
			}
		}
	}
			//Asetetaan standari v‰ri ja lis‰t‰‰n loppuun kirjaimet
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN 
			| FOREGROUND_BLUE | FOREGROUND_INTENSITY);

			for (int i = 0; i < 8; i++)
			{
				wcout << L"  " << kirjaimet[i] << " ";
			
			}
}


/*
	Aliohjelma tarkistaa ett‰ k‰ytt‰j‰n antama syˆte siirroksi on 
	muodollisesti korrekti (ei tarkista aseman laillisuutta)
	Ottaa irti myˆs nappulan kirjaimen (K/D/L/R/T), tarkistaa ett‰ kirjain korrekti
*/
Siirto Kayttoliittyma::annaVastustajanSiirto()
{
	Siirto siirto;
	return siirto;
	
}


int Kayttoliittyma::kysyVastustajanVari()
{
	return 0;
}
