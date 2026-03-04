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

	//asetetaan tulostus UTF16 tyyppiseksi, jotta shakkinappulat n‰kyv‰t oikein
	_setmode(_fileno(stdout), _O_U16TEXT);

	// Piirret‰‰n lauta ylh‰‰lt‰ alas (rivi 8 -> 1)
	// Mutta _lauta[0] on rivi 1, joten k‰yd‰‰n l‰pi 7 -> 0
	for (int i = 7; i >= 0; i--)
	{	
		for (int j = 0; j < 8; j++)
		{
			if (j == 0)
			{
				//Muutetaan tulostus standardiksi, kirjainrivin tulostusta varten
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				wcout << (i + 1); // N‰ytet‰‰n rivinumero 1-8
			}

			// V‰ritys: a1 (i=0, j=0) on tumma ruutu
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
				//Koska halutaan nappula keskelle ruutua, tulostetaan ensin 1 tyhj‰, sitten nappula ja 2 tyhj‰‰
				wcout << _asema->_lauta[i][j]->getUnicode();
				wcout <<L" ";
			}
			else
			{
				wcout <<L"  ";
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
		wcout << L" " << kirjaimet[i];
	}

	wcout << "\n";
}


/*
	Aliohjelma tarkistaa ett‰ k‰ytt‰j‰n antama syˆte siirroksi on 
	muodollisesti korrekti (ei tarkista aseman laillisuutta)
	Ottaa irti myˆs nappulan kirjaimen (K/D/L/R/T), tarkistaa ett‰ kirjain korrekti
*/
Siirto Kayttoliittyma::annaVastustajanSiirto()
{
	wstring move;
	int lahtoX;
	int lahtoY;
	int loppuX;
	int loppuY;
	bool laillinen = false;

	while (!laillinen)
	{
		wcout << L"Anna siirtosi:" << endl;
		wcin >> move;
		Asema* asema = _asema;

		std::vector<Siirto> lista;
		lista.reserve(64);
		asema->annaLaillisetSiirrot(lista);


		for (auto siirto : lista)
		{
			if (move == L"O-O" && siirto.onkoLyhytLinna())
			{
				laillinen = true;

			}
			else if (move == L"O-O-O" && siirto.onkoPitkaLinna())
			{
				laillinen = true;

			}
			if (move.size() == 5 || move.size() == 6)
			{
				lahtoX = move[0] - 'a';
				lahtoY = move[1] - '1';
				loppuX = move[3] - 'a';
				loppuY = move[4] - '1';

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
		wcout << L"Syˆt‰ laillinen siirto." << endl;
	}

	Nappula* korotusNappula = (_asema->getSiirtovuoro() == 0) ? Asema::vd : Asema::md;
	if (move.size() == 6)
	{	
		if (move[5] == L'D' || move[5] == L'd')
		{
			korotusNappula = (_asema->getSiirtovuoro() == 0) ? Asema::vd : Asema::md;

		}
		else if (move[5] == L'R' || move[5] == L'r')
		{
			korotusNappula = (_asema->getSiirtovuoro() == 0) ? Asema::vr : Asema::mr;

		}
		else if (move[5] == L'T' || move[5] == L't')
		{
			korotusNappula = (_asema->getSiirtovuoro() == 0) ? Asema::vt : Asema::mt;

		}
		else if (move[5] == L'L' || move[5] == L'l')
		{
			korotusNappula = (_asema->getSiirtovuoro() == 0) ? Asema::vl : Asema::ml;

		}
	}
		if (move == L"O-O")
		{
			Siirto siirto(true, false);
			return siirto;

		}
		else if (move == L"O-O-O")
		{
			Siirto siirto(false, true);
			return siirto;

		}

	lahtoX = move[0] - 'a';
	lahtoY = move[1] - '1';
	loppuX = move[3] - 'a';
	loppuY = move[4] - '1';
	
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
