#include <list>
#include <string>
#include "asema.h"
#include "nappula.h"
using namespace std;


Nappula::Nappula(wstring unicode, int vari, int koodi, double arvo)
{
	_unicode = unicode;
	_vari = vari;
	_koodi = koodi;
	_arvo = arvo;
}


void Torni::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int x = ruutu->getSarake();
	int y = ruutu->getRivi();
	
	//Suunta oikealle
	for (int i = 1; i < 8; i++)
	{
		//Set the temporary position. Y stays the same as we are checking horizontal moves
		int tempX = x + i;
		int tempY = y;

		//If tempX is out bounds, break to stop running as the next ones will also be out of bounds
		if (tempX >= 8) break;

		if (asema->_lauta[tempY][tempX] != NULL)
		{
			Nappula* ruudunNappula = asema->_lauta[tempY][tempX];

			//If piece is ours, break to keep the legal moves on the last legal position
			if (ruudunNappula->getVari() == vari)
			{
				break;
			}
			//Else, add it to the list and break as rook has to stop on enemy square
			else
			{
				Ruutu loppuRuutu = Ruutu(tempX, tempY);
				Siirto siirto(*ruutu, loppuRuutu);
				lista.push_back(siirto);
				break;
			}
		}
		//if square was empty, add it to legal moves
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
		//Set the temporary position. Y stays the same as we are checking horizontal moves
		int tempX = x - i;
		int tempY = y;

		//If tempX is out bounds, break to stop running as the next ones will also be out of bounds
		if (tempX < 0) break;

		if (asema->_lauta[tempY][tempX] != NULL)
		{
			Nappula* ruudunNappula = asema->_lauta[tempY][tempX];

			//If piece is ours, break to keep the legal moves on the last legal position
			if (ruudunNappula->getVari() == vari)
			{
				break;
			}
			//Else, add it to the list and break as rook has to stop on enemy square
			else
			{
				Ruutu loppuRuutu = Ruutu(tempX, tempY);
				Siirto siirto(*ruutu, loppuRuutu);
				lista.push_back(siirto);
				break;
			}
		}
		//if square was empty, add it to legal moves
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
		//Set the temporary position. X stays the same as we are checking vertical moves
		int tempX = x;
		int tempY = y + i;

		//If tempY is out bounds, break to stop running as the next ones will also be out of bounds
		if (tempY >= 8) break;

		if (asema->_lauta[tempY][tempX] != NULL)
		{
			Nappula* ruudunNappula = asema->_lauta[tempY][tempX];

			//If piece is ours, break to keep the legal moves on the last legal position
			if (ruudunNappula->getVari() == vari)
			{
				break;
			}
			//Else, add it to the list and break as rook has to stop on enemy square
			else
			{
				Ruutu loppuRuutu = Ruutu(tempX, tempY);
				Siirto siirto(*ruutu, loppuRuutu);
				lista.push_back(siirto);
				break;
			}
		}
		//if square was empty, add it to legal moves
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
		//Set the temporary position. X stays the same as we are checking vertical moves
		int tempX = x;
		int tempY = y - i;

		//If tempY is out bounds, break to stop running as the next ones will also be out of bounds
		if (tempY < 0) break;

		if (asema->_lauta[tempY][tempX] != NULL)
		{
			Nappula* ruudunNappula = asema->_lauta[tempY][tempX];

			//If piece is ours, break to keep the legal moves on the last legal position
			if (ruudunNappula->getVari() == vari)
			{
				break;
			}
			//Else, add it to the list and break as rook has to stop on enemy square
			else
			{
				Ruutu loppuRuutu = Ruutu(tempX, tempY);
				Siirto siirto(*ruutu, loppuRuutu);
				lista.push_back(siirto);
				break;
			}
		}
		//if square was empty, add it to legal moves
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
	int x = ruutu->getSarake();
	int y = ruutu->getRivi();

	//Suunta vasemmalle ylös
	for (int i = 1; i < 8; i++)
	{
		//Set the temporary position. x decreases and y increments as we go diagonally to top left
		int tempX = x - i;
		int tempY = y + i;

		//If tempX is out bounds, break to stop running as the next ones will also be out of bounds
		if (tempX < 0 || tempY >= 8) break;

		if (asema->_lauta[tempY][tempX] != NULL)
		{
			Nappula* ruudunNappula = asema->_lauta[tempY][tempX];

			//If piece is ours, break to keep the legal moves on the last legal position
			if (ruudunNappula->getVari() == vari)
			{
				break;
			}
			//Else, add it to the list and break as bishop has to stop on enemy square
			else
			{
				Ruutu loppuRuutu = Ruutu(tempX, tempY);
				Siirto siirto(*ruutu, loppuRuutu);
				lista.push_back(siirto);
				break;
			}
		}
		//if square was empty, add it to legal moves
		else
		{
			Ruutu loppuRuutu = Ruutu(tempX, tempY);
			Siirto siirto(*ruutu, loppuRuutu);
			lista.push_back(siirto);
		}
	}

	//Suunta oikealle ylös
	for (int i = 1; i < 8; i++)
	{
		//Set the temporary position. x and y increment as we go diagonally to top right
		int tempX = x + i;
		int tempY = y + i;

		//If tempX is out bounds, break to stop running as the next ones will also be out of bounds
		if (tempX >= 8 || tempY >= 8) break;

		if (asema->_lauta[tempY][tempX] != NULL)
		{
			Nappula* ruudunNappula = asema->_lauta[tempY][tempX];

			//If piece is ours, break to keep the legal moves on the last legal position
			if (ruudunNappula->getVari() == vari)
			{
				break;
			}
			//Else, add it to the list and break as bishop has to stop on enemy square
			else
			{
				Ruutu loppuRuutu = Ruutu(tempX, tempY);
				Siirto siirto(*ruutu, loppuRuutu);
				lista.push_back(siirto);
				break;
			}
		}
		//if square was empty, add it to legal moves
		else
		{
			Ruutu loppuRuutu = Ruutu(tempX, tempY);
			Siirto siirto(*ruutu, loppuRuutu);
			lista.push_back(siirto);
		}
	}

	//Suunta vasemmalle alas
	for (int i = 1; i < 8; i++)
	{
		//Set the temporary position. x and y decrease as we go diagonally to bottom left
		int tempX = x - i;
		int tempY = y - i;

		//If tempY is out bounds, break to stop running as the next ones will also be out of bounds
		if (tempX < 0 || tempY < 0) break;

		if (asema->_lauta[tempY][tempX] != NULL)
		{
			Nappula* ruudunNappula = asema->_lauta[tempY][tempX];

			//If piece is ours, break to keep the legal moves on the last legal position
			if (ruudunNappula->getVari() == vari)
			{
				break;
			}
			//Else, add it to the list and break as bishop has to stop on enemy square
			else
			{
				Ruutu loppuRuutu = Ruutu(tempX, tempY);
				Siirto siirto(*ruutu, loppuRuutu);
				lista.push_back(siirto);
				break;
			}
		}
		//if square was empty, add it to legal moves
		else
		{
			Ruutu loppuRuutu = Ruutu(tempX, tempY);
			Siirto siirto(*ruutu, loppuRuutu);
			lista.push_back(siirto);
		}
	}

	//Suunta oikealle alas
	for (int i = 1; i < 8; i++)
	{
		//Set the temporary position. x increments and y decrements as we go diagonally to bottom right.
		int tempX = x + 1;
		int tempY = y - i;

		//If tempY is out bounds, break to stop running as the next ones will also be out of bounds
		if (tempX >= 8 || tempY < 0) break;

		if (asema->_lauta[tempY][tempX] != NULL)
		{
			Nappula* ruudunNappula = asema->_lauta[tempY][tempX];

			//If piece is ours, break to keep the legal moves on the last legal position
			if (ruudunNappula->getVari() == vari)
			{
				break;
			}
			//Else, add it to the list and break as bishop has to stop on enemy square
			else
			{
				Ruutu loppuRuutu = Ruutu(tempX, tempY);
				Siirto siirto(*ruutu, loppuRuutu);
				lista.push_back(siirto);
				break;
			}
		}
		//if square was empty, add it to legal moves
		else
		{
			Ruutu loppuRuutu = Ruutu(tempX, tempY);
			Siirto siirto(*ruutu, loppuRuutu);
			lista.push_back(siirto);
		}
	}
}


void Daami::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	Torni::annaSiirrot(lista, ruutu, asema, vari);
	Lahetti::annaSiirrot(lista, ruutu, asema, vari);
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
			if (asema->_lauta[y + 1][x] == NULL)
			{
				//Jos sotilaan yläpuolella ei ole nappulaa voidaan liikkua
				Ruutu loppuRuutu = Ruutu(x, y + 1);
				Siirto siirto(*ruutu, loppuRuutu);

				// Katsotaan onko ruutu korotusruutu
				if (y + 1 == 7)
				{
					lisaaSotilaanKorotukset(&siirto, lista, asema);
				}
				else
				{
					lista.push_back(siirto);
				}

				//Jos sotilaan kahta yläpuolella ei ole nappulaa voidaan liikkua
				if (y == 1 && asema->_lauta[y + 2][x] == NULL)
				{
					Ruutu loppuRuutu = Ruutu(x, y + 2);
					Siirto siirto(*ruutu, loppuRuutu);
					lista.push_back(siirto);
				}
			}

			if (x - 1 >= 0 && y + 1 < 8)
			{
				//Tarkistaa saako vasemmalta syötyä vihollisen nappulan
				if (asema->_lauta[y + 1][x - 1] != NULL
					&& asema->_lauta[y + 1][x - 1]->getVari() != 0)
				{
					Ruutu loppuRuutu = Ruutu(x - 1, y + 1);
					Siirto siirto(*ruutu, loppuRuutu);

					if (y + 1 == 7)
					{
						lisaaSotilaanKorotukset(&siirto, lista, asema);
					}
					else
					{
						lista.push_back(siirto);
					}
				}
			}

			if (x + 1 < 8 && y + 1 < 8)
			{
				//Tarkistaa saako oikealta syötyä vihollisen nappulan
				if (asema->_lauta[y + 1][x + 1] != NULL
					&& asema->_lauta[y + 1][x + 1]->getVari() != 0)
				{
					Ruutu loppuRuutu = Ruutu(x + 1, y + 1);
					Siirto siirto(*ruutu, loppuRuutu);

					if (y + 1 == 7)
					{
						lisaaSotilaanKorotukset(&siirto, lista, asema);
					}
					else
					{
						lista.push_back(siirto);
					}
				}
			}
				//Katsotaan onko kaksoisaskel on tapahtunut
				if (y == 4 && asema->kaksoisaskelSarakkeella != -1)
				{
					//Tehdään ohestalyönti oikealle
					if (asema->kaksoisaskelSarakkeella == x + 1)
					{
						if (asema->_lauta[y + 1][x + 1] == NULL)
						{
							lista.push_back(Siirto(*ruutu, Ruutu(x + 1, y + 1)));
						}

					}//Tehdään ohestalyönti vasemmalle
					if (asema->kaksoisaskelSarakkeella == x - 1)
					{
						if (asema->_lauta[y + 1][x - 1] == NULL)
						{
							lista.push_back(Siirto(*ruutu, Ruutu(x - 1, y + 1)));
						}
					}
				}

		}
		else //Jos väri on musta
		{
			//Jos sotilaan yläpuolella ei ole nappulaa voidaan liikkua
			if (asema->_lauta[y - 1][x] == NULL)
			{
				Ruutu loppuRuutu = Ruutu(x, y - 1);
				Siirto siirto(*ruutu, loppuRuutu);

				if (y - 1 == 0)
				{
					lisaaSotilaanKorotukset(&siirto, lista, asema);
				}
				else
				{
					lista.push_back(siirto);
				}

				//Jos sotilaan kahta yläpuolella ei ole nappulaa voidaan liikkua
				if (y == 6 && asema->_lauta[y - 2][x] == NULL)
				{
					Ruutu loppuRuutu = Ruutu(x, y - 2);
					Siirto siirto(*ruutu, loppuRuutu);
					lista.push_back(siirto);
				}
			}

			if (x - 1 >= 0 && y - 1 <= 0)
			{
				//Tarkistaa saako vasemmalta syötyä vihollisen nappulan
				if (asema->_lauta[y - 1][x - 1] != NULL
					&& asema->_lauta[y - 1][x - 1]->getVari() != 1)
				{
					Ruutu loppuRuutu = Ruutu(x - 1, y - 1);
					Siirto siirto(*ruutu, loppuRuutu);
					
					if (y - 1 == 0)
					{
						lisaaSotilaanKorotukset(&siirto, lista, asema);
					}
					else
					{
						lista.push_back(siirto);
					}
					
				}
			}

			if (x - 1 >= 0 && y - 1 <= 8)
			{
				//Tarkistaa saako oikealta syötyä vihollisen nappulan
				if (asema->_lauta[y - 1][x + 1] != NULL
					&& asema->_lauta[y - 1][x + 1]->getVari() != 1)
				{
					Ruutu loppuRuutu = Ruutu(x + 1, y - 1);
					Siirto siirto(*ruutu, loppuRuutu);
					
					if (y - 1 == 0)
					{
						lisaaSotilaanKorotukset(&siirto, lista, asema);
					}
					else
					{
						lista.push_back(siirto);
					}
				}
			}

			//Katsotaan onko kaksoisaskel on tapahtunut
			if (y == 3 && asema->kaksoisaskelSarakkeella != -1)
			{
				//Tehdään ohestalyönti oikealle
				if (asema->kaksoisaskelSarakkeella == x + 1)
				{
					if (asema->_lauta[y - 1][x + 1] == NULL)
					{
						lista.push_back(Siirto(*ruutu, Ruutu(x + 1, y - 1)));
					}

				}//Tehdään ohestalyönti vasemmalle
				if (asema->kaksoisaskelSarakkeella == x - 1)
				{
					if (asema->_lauta[y - 1][x - 1] == NULL)
					{
						lista.push_back(Siirto(*ruutu, Ruutu(x - 1, y - 1)));
					}
				}
			}
		}
	}


void Sotilas::lisaaSotilaanKorotukset(Siirto* siirto, std::list<Siirto>& lista, Asema* asema) {
	int vari = this->getVari();

	//Alustetaan jokaisen korotustyypin siirto
	Siirto daamiKorotus = *siirto;
	Siirto torniKorotus = *siirto;
	Siirto lahettiKorotus = *siirto;
	Siirto ratsuKorotus = *siirto;

	//Jos väri on valkoinen, asetetaan valkoiset napit, muuten mustat
	if (vari == 0)
	{
		daamiKorotus._miksikorotetaan = asema->vd;
		torniKorotus._miksikorotetaan = asema->vt;
		lahettiKorotus._miksikorotetaan = asema->vl;
		ratsuKorotus._miksikorotetaan = asema->vr;
	}
	else
	{
		daamiKorotus._miksikorotetaan = asema->md;
		torniKorotus._miksikorotetaan = asema->mt;
		lahettiKorotus._miksikorotetaan = asema->ml;
		ratsuKorotus._miksikorotetaan = asema->mr;
	}

	//Lisätään listaan kaikki siirrot
	lista.push_back(daamiKorotus);
	lista.push_back(torniKorotus);
	lista.push_back(lahettiKorotus);
	lista.push_back(ratsuKorotus);
}