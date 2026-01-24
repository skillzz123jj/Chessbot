#include <list>
#include <string>
#include "asema.h"
#include "nappula.h"
using namespace std;


Nappula::Nappula(wstring unicode, int vari, int koodi)
{
	_unicode = unicode;
	_vari = vari;
	_koodi = koodi;
}


void Torni::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	
}


void Ratsu::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int x = ruutu->getRivi();
	int y = ruutu->getSarake();

	int siirrot[8][2] = {
	   { 2,  1}, { 2, -1},
	   {-2,  1}, {-2, -1},
	   { 1,  2}, { 1, -2},
	   {-1,  2}, {-1, -2}
	};

	for (int i = 0; i < 8; ++i)
	{
		int tempX = x + siirrot[i][0];
		int tempY = y + siirrot[i][1];

		//Katsotaan meneekˆ laudasta ulos
		if (tempX < 0 || tempX >= 8 || tempY < 0 || tempY >= 8)
			continue;

		if (asema->_lauta[tempX][tempY] != NULL)
		{
			Nappula* ruudunNappula = asema->_lauta[tempX][tempY];

			//Jos sijainnissa oleva nappula on saman v‰rinen niin sinne ei voi siirty‰
			if (ruudunNappula->getVari() == asema->getSiirtovuoro())
				continue;
			else //Se lis‰t‰‰n listaan mahdollisista liikkeist‰ jos nappula on eri v‰rinen
			{
				Ruutu loppuRuutu = Ruutu(tempX, tempY);
				Siirto siirto(*ruutu, loppuRuutu);
				lista.push_back(siirto);
			}
		}
		else
		{
			Ruutu loppuRuutu = Ruutu(tempX, tempY);
				Siirto siirto(*ruutu, loppuRuutu);
				lista.push_back(siirto);
		}
	}
}


void Lahetti::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	
}


void Daami::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	
}


void Kuningas::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	/*perusidea on ett‰ kaikki viereiset ruudut ovat sallittuja. kuten tornilla ja l‰hetill‰,
	oman nappulan p‰‰lle ei voi menn‰ ja vastustajan nappulan voi syˆd‰.

	Kaikki muu kuninkaaseen liittyv‰ tarkistus tehd‰‰n eri paikassa*/


	
}


void Sotilas::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	
}


void Sotilas::lisaaSotilaanKorotukset(Siirto* siirto, std::list<Siirto>& lista, Asema* asema) {
	
}
