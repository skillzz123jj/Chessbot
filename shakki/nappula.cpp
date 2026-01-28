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
	int x = ruutu->getSarake();
	int y = ruutu->getRivi();
	
	//Suunta oikealle
	for (int i = 1; i < 8; i++)
	{
		int tempX = x + i;
		int tempY = y;

		if (tempX >= 8) break;

		if (asema->_lauta[tempY][tempX] != NULL)
		{
			Nappula* ruudunNappula = asema->_lauta[tempY][tempX];

			if (ruudunNappula->getVari() == vari)
			{
				break;
			}
			else
			{
				Ruutu loppuRuutu = Ruutu(tempX, tempY);
				Siirto siirto(*ruutu, loppuRuutu);
				lista.push_back(siirto);
				break;
			}
		}
		else
		{
			Ruutu loppuRuutu = Ruutu(tempX, tempY);
			Siirto siirto(*ruutu, loppuRuutu);
			lista.push_back(siirto);
		}
	}

	//Suunta vasemmalle
	for (int i = 1; i < 8; i++)
	{
		int tempX = x - i;
		int tempY = y;

		if (tempX < 0) break;

		if (asema->_lauta[tempY][tempX] != NULL)
		{
			Nappula* ruudunNappula = asema->_lauta[tempY][tempX];

			if (ruudunNappula->getVari() == vari)
			{
				break;
			}
			else
			{
				Ruutu loppuRuutu = Ruutu(tempX, tempY);
				Siirto siirto(*ruutu, loppuRuutu);
				lista.push_back(siirto);
				break;
			}
		}
		else
		{
			Ruutu loppuRuutu = Ruutu(tempX, tempY);
			Siirto siirto(*ruutu, loppuRuutu);
			lista.push_back(siirto);
		}
	}

	//Suunta ylös
	for (int i = 1; i < 8; i++)
	{
		int tempX = x;
		int tempY = y + i;

		if (tempY >= 8) break;

		if (asema->_lauta[tempY][tempX] != NULL)
		{
			Nappula* ruudunNappula = asema->_lauta[tempY][tempX];

			if (ruudunNappula->getVari() == vari)
			{
				break;
			}
			else
			{
				Ruutu loppuRuutu = Ruutu(tempX, tempY);
				Siirto siirto(*ruutu, loppuRuutu);
				lista.push_back(siirto);
				break;
			}
		}
		else
		{
			Ruutu loppuRuutu = Ruutu(tempX, tempY);
			Siirto siirto(*ruutu, loppuRuutu);
			lista.push_back(siirto);
		}
	}

	//Suunta alas
	for (int i = 1; i < 8; i++)
	{
		int tempX = x;
		int tempY = y - i;

		if (tempY < 0) break;

		if (asema->_lauta[tempY][tempX] != NULL)
		{
			Nappula* ruudunNappula = asema->_lauta[tempY][tempX];

			if (ruudunNappula->getVari() == vari)
			{
				break;
			}
			else
			{
				Ruutu loppuRuutu = Ruutu(tempX, tempY);
				Siirto siirto(*ruutu, loppuRuutu);
				lista.push_back(siirto);
				break;
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

void Ratsu::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int x = ruutu->getSarake();
	int y = ruutu->getRivi();

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

		//Katsotaan meneekö laudasta ulos
		if (tempX < 0 || tempX >= 8 || tempY < 0 || tempY >= 8)
			continue;

		if (asema->_lauta[tempY][tempX] != NULL)
		{
			Nappula* ruudunNappula = asema->_lauta[tempY][tempX];

			//Jos sijainnissa oleva nappula on saman värinen niin sinne ei voi siirtyä
			if (ruudunNappula->getVari() == vari)
				continue;
			else //Se lisätään listaan mahdollisista liikkeistä jos nappula on eri värinen
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
	int x = ruutu->getSarake();
	int y = ruutu->getRivi();

	int siirrot[8][2] = {
	   { -1, 1}, { 0, 1},
	   {1,  1}, {-1, 0},
	   { -1, -1}, { 0, -1},
	   {1, -1}, { 1, 0 }
	};


	for (int i = 0; i < 8; ++i)
	{
		int tempX = x + siirrot[i][0];
		int tempY = y + siirrot[i][1];

		//Katsotaan meneekö laudasta ulos
		if (tempX < 0 || tempX >= 8 || tempY < 0 || tempY >= 8)
			continue;

		if (asema->_lauta[tempY][tempX] != NULL)
		{
			Nappula* ruudunNappula = asema->_lauta[tempY][tempX];

			//Jos sijainnissa oleva nappula on saman värinen niin sinne ei voi siirtyä
			if (ruudunNappula->getVari() == vari)
				continue;
			else //Se lisätään listaan mahdollisista liikkeistä jos nappula on eri värinen
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


void Sotilas::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
		int x = ruutu->getSarake();
		int y = ruutu->getRivi();

		if (vari == 0) //Jos väri on valkoinen
		{
			if (asema->_lauta[x][y + 1] == NULL)
			{
				//Jos sotilaan yläpuolella ei ole nappulaa voidaan liikkua
				Ruutu loppuRuutu = Ruutu(x, y + 1);
				Siirto siirto(*ruutu, loppuRuutu);
				lista.push_back(siirto);

				//Jos sotilaan kahta yläpuolella ei ole nappulaa voidaan liikkua
				if (y == 1 && asema->_lauta[x][y + 2] == NULL)
				{
					Ruutu loppuRuutu = Ruutu(x, y + 2);
					Siirto siirto(*ruutu, loppuRuutu);
					lista.push_back(siirto);
				}
			}

			//Tarkistaa saako vasemmalta syötyä vihollisen nappulan
			if (asema->_lauta[x - 1][y + 1] != NULL 
			&& asema->_lauta[x - 1][y + 1]->getVari() != 0)
			{
				Ruutu loppuRuutu = Ruutu(x, y + 2);
				Siirto siirto(*ruutu, loppuRuutu);
				lista.push_back(siirto);
			}

			//Tarkistaa saako oikealta syötyä vihollisen nappulan
			if (asema->_lauta[x + 1][y + 1] != NULL
				&& asema->_lauta[x + 1][y + 1]->getVari() != 0)
			{
				Ruutu loppuRuutu = Ruutu(x, y + 2);
				Siirto siirto(*ruutu, loppuRuutu);
				lista.push_back(siirto);
			}

		}
		else //Jos väri on musta
		{
			//Jos sotilaan yläpuolella ei ole nappulaa voidaan liikkua
			if (asema->_lauta[x][y - 1] == NULL)
			{
				Ruutu loppuRuutu = Ruutu(x, y - 1);
				Siirto siirto(*ruutu, loppuRuutu);
				lista.push_back(siirto);

				//Jos sotilaan kahta yläpuolella ei ole nappulaa voidaan liikkua
				if (y == 1 && asema->_lauta[x][y + 2] == NULL)
				{
					Ruutu loppuRuutu = Ruutu(x, y + 2);
					Siirto siirto(*ruutu, loppuRuutu);
					lista.push_back(siirto);
				}
			}

			//Tarkistaa saako vasemmalta syötyä vihollisen nappulan
			if (asema->_lauta[x - 1][y + 1] != NULL
				&& asema->_lauta[x - 1][y + 1]->getVari() != 0)
			{
				Ruutu loppuRuutu = Ruutu(x, y + 2);
				Siirto siirto(*ruutu, loppuRuutu);
				lista.push_back(siirto);
			}

			//Tarkistaa saako oikealta syötyä vihollisen nappulan
			if (asema->_lauta[x + 1][y + 1] != NULL
				&& asema->_lauta[x + 1][y + 1]->getVari() != 0)
			{
				Ruutu loppuRuutu = Ruutu(x, y + 2);
				Siirto siirto(*ruutu, loppuRuutu);
				lista.push_back(siirto);
			}
		}
	}


void Sotilas::lisaaSotilaanKorotukset(Siirto* siirto, std::list<Siirto>& lista, Asema* asema) {
	
}