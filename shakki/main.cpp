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

			wcout << letterA << s.getAlkuruutu().getRivi() + 1 << "-";
			wcout << letterL << s.getLoppuruutu().getRivi() + 1 << endl;

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
			if (koneenVari == 0) {
				paluu = asema.maxi(3);
			}
			else {
				paluu = asema.mini(3);
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
