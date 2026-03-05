#include <Windows.h>
#include <iostream>
#include <string>
#include <fcntl.h>
#include <io.h>
#include "kayttoliittyma.h"
#include "asema.h"


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

	//asetetaan tulostus UTF16 tyyppiseksi, jotta shakkinappulat näkyvät oikein
	_setmode(_fileno(stdout), _O_U16TEXT);

	// Piirretään lauta ylhäältä alas (rivi 8 -> 1)
	// Mutta _lauta[0] on rivi 1, joten käydään läpi 7 -> 0
	for (int i = 7; i >= 0; i--)
	{	
		for (int j = 0; j < 8; j++)
		{
			if (j == 0)
			{
				//Muutetaan tulostus standardiksi, kirjainrivin tulostusta varten
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				wcout << (i + 1); // Näytetään rivinumero 1-8
			}

			// Väritys: a1 (i=0, j=0) on tumma ruutu
			if ((i + j) % 2 == 0)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY |
					BACKGROUND_GREEN);
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
					BACKGROUND_GREEN | BACKGROUND_BLUE);
			}

			if (_asema->_lauta[i][j] != NULL)
			{
				//Koska halutaan nappula keskelle ruutua, tulostetaan ensin 1 tyhjä, sitten nappula ja 2 tyhjää
				wcout << _asema->_lauta[i][j]->getUnicode();
				wcout <<L" ";
			}
			else
			{
				wcout <<L"  ";
			}
			
			//Jos viimeisellä neliöllä rivissä, vaihdetaan rivi
			if (j == 7)
			{
				wcout << "\n";
			}
		}
	}
	//Asetetaan standari väri ja lisätään loppuun kirjaimet
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN 
		| FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	for (int i = 0; i < 8; i++)
	{
		wcout << L" " << kirjaimet[i];
	}

	wcout << "\n";
}


/*
	Aliohjelma tarkistaa että käyttäjän antama syöte siirroksi on 
	muodollisesti korrekti (ei tarkista aseman laillisuutta)
	Ottaa irti myös nappulan kirjaimen (K/D/L/R/T), tarkistaa että kirjain korrekti
*/
Siirto Kayttoliittyma::annaVastustajanSiirto()
{
	wstring raakaSyote;
	int lahtoX;
	int lahtoY;
	int loppuX;
	int loppuY;
	bool laillinen = false;
	wstring syote;

	while (!laillinen)
	{
		//Otetaan käyttäjän syöte ja muunnetaan se pieneksi
		wcout << L"Anna siirtosi:" << endl;
		wcin >> raakaSyote;
		Asema* asema = _asema;
		syote = L"";
		for (wchar_t merkki : raakaSyote)
		{
			syote.push_back(tolower(merkki));
		}

		//Pyydetään käyttäjältä siirtoja kunnes syötetty siirto on laillinen

		std::vector<Siirto> lista;
		lista.reserve(64);
		asema->annaLaillisetSiirrot(lista);


		for (auto siirto : lista)
		{
			if (syote == L"o-o" && siirto.onkoLyhytLinna())
			{
				laillinen = true;

			}
			else if (syote == L"o-o-o" && siirto.onkoPitkaLinna())
			{
				laillinen = true;

			}
			if (syote.size() == 5 || syote.size() == 6)
			{
				lahtoX = syote[0] - 'a';
				lahtoY = syote[1] - '1';
				loppuX = syote[3] - 'a';
				loppuY = syote[4] - '1';

				Ruutu lahtoRuutu = Ruutu(lahtoX, lahtoY);
				Ruutu loppuRuutu = Ruutu(loppuX, loppuY);

				int siirtoLahtoX = siirto.getAlkuruutu().getSarake();
				int siirtoLahtoY = siirto.getAlkuruutu().getRivi();

				int siirtoLoppuX = siirto.getLoppuruutu().getSarake();
				int siirtoLoppuY = siirto.getLoppuruutu().getRivi();

				Siirto siirto(lahtoRuutu, loppuRuutu);
				if (siirtoLahtoX == lahtoX && siirtoLahtoY == lahtoY &&
					siirtoLoppuX == loppuX && siirtoLoppuY == loppuY)
				{
					laillinen = true;
				}
			}
			
		}
		if (!laillinen)wcout << L"Syötä laillinen siirto." << endl;
	}
	
	//Hoida mahdolliset korotukset 
	Nappula* korotusNappula = (_asema->getSiirtovuoro() == 0) ? Asema::vd : Asema::md;

	if (syote.size() == 6)
	{	
		wchar_t korotusKirjain = tolower(syote[5]);
		if (syote[5] == L'd')
		{
			korotusNappula = (_asema->getSiirtovuoro() == 0) ? Asema::vd : Asema::md;

		}
		else if (syote[5] == L'r')
		{
			korotusNappula = (_asema->getSiirtovuoro() == 0) ? Asema::vr : Asema::mr;

		}
		else if (syote[5] == L't')
		{
			korotusNappula = (_asema->getSiirtovuoro() == 0) ? Asema::vt : Asema::mt;

		}
		else if (syote[5] == L'l')
		{
			korotusNappula = (_asema->getSiirtovuoro() == 0) ? Asema::vl : Asema::ml;

		}
	}
	// Hoida mahdolliset linnoitukset
		if (syote == L"o-o")
		{
			Siirto siirto(true, false);
			return siirto;

		}
		else if (syote == L"o-o-o")
		{
			Siirto siirto(false, true);
			return siirto;

		}

	// Luo siirrot
	lahtoX = syote[0] - 'a';
	lahtoY = syote[1] - '1';
	loppuX = syote[3] - 'a';
	loppuY = syote[4] - '1';
	
	Ruutu lahtoRuutu = Ruutu(lahtoX, lahtoY);
	Ruutu loppuRuutu = Ruutu(loppuX, loppuY);

	Siirto siirto(lahtoRuutu, loppuRuutu);
	siirto._miksikorotetaan = korotusNappula;
	
	return siirto;
	
}


int Kayttoliittyma::kysyVastustajanVari()
{
	while (true) 
	{
		wcout <<L"Valitse puolesi valkoinen (0) tai musta (1)" << endl;
		wstring vari;
		wcin >> vari;

		if (vari == L"0")
		{
			return 0;
		}
		else if (vari == L"1")
		{
			return 1;
		}
	}
}
