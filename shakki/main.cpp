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
	wcout << "HeippariShakki\n";
	wcout << "Tervetuloa pelaamaan!\n";
	int lopetus = 100;
	Asema asema;
	Kayttoliittyma::getInstance()->aseta_asema(&asema);

	Peli peli(Kayttoliittyma::getInstance()->
		kysyVastustajanVari());
	std::list<Siirto> lista;
	system("cls");
	int koneenVari = peli.getKoneenVari();

	while (lopetus != 0) {
		lista.clear();
		system("cls");
		Kayttoliittyma::getInstance()->piirraLauta();
		wcout << "\n";
		// Tarkasta onko peli loppu?
		asema.annaLaillisetSiirrot(lista);

		for (Siirto s : lista)
		{
			if (s.onkoLyhytLinna())
			{
				wcout << "O-O" << endl;
				continue;
			}
			if (s.onkoPitkaLinna())
			{
				wcout << "O-O-O" << endl;
				continue;
			}
			wchar_t letterA = s.getAlkuruutu().getSarake() + L'a';
			wchar_t letterL = s.getLoppuruutu().getSarake() + L'a';

			//wcout << letterA << s.getAlkuruutu().getRivi() + 1 << "-";
			//wcout << letterL << s.getLoppuruutu().getRivi() + 1 << endl;

		}
		wcout << lista.size() << endl;

		
		if (lista.size() == 0) {
			lopetus = 0;
			std::wcout << "Peli loppui";
			continue;
		}
		Siirto siirto;
		if (asema.getSiirtovuoro() == koneenVari) {
			MinMaxPaluu paluu;
			int syvyys = 4;
			double alpha = -10000;
			double beta = 10000;
			if (koneenVari == 0) {
				paluu = asema.maxi(syvyys, alpha, beta);
			}
			else {
				paluu = asema.mini(syvyys, alpha, beta);
			}
			siirto = paluu._parasSiirto;
		}
		else {
			siirto = Kayttoliittyma::getInstance()->
				annaVastustajanSiirto();
		}
		asema.paivitaAsema(&siirto);
	}


	return 0;
}
