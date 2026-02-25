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

double Torni::annaArvo(int y, int x, bool keskipeli)
{
	int mg_piece_value = 477;
	int eg_piece_value = 512;

	if (keskipeli)
	{
		int mg_rook_table[64] = {
		 32,  42,  32,  51, 63,  9,  31,  43,
		 27,  32,  58,  62, 80, 67,  26,  44,
		 -5,  19,  26,  36, 17, 45,  61,  16,
		-24, -11,   7,  26, 24, 35,  -8, -20,
		-36, -26, -12,  -1,  9, -7,   6, -23,
		-45, -25, -16, -17,  3,  0,  -5, -33,
		-44, -16, -20,  -9, -1, 11,  -6, -71,
		-19, -13,   1,  17, 16,  7, -37, -26,
		};

		int index = y * 8 + x;

		return mg_piece_value +	mg_rook_table[index];
	}
	else
	{
		int eg_rook_table[64] = {
		13, 10, 18, 15, 12,  12,   8,   5,
		11, 13, 13, 11, -3,   3,   8,   3,
		 7,  7,  7,  5,  4,  -3,  -5,  -3,
		 4,  3, 13,  1,  2,   1,  -1,   2,
		 3,  5,  8,  4, -5,  -6,  -8, -11,
		-4,  0, -5, -1, -7, -12,  -8, -16,
		-6, -6,  0,  2, -9,  -9, -11,  -3,
		-9,  2,  3, -1, -5, -13,   4, -20,
		};

		int index = y * 8 + x;

		return eg_piece_value + eg_rook_table[index];

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

double Ratsu::annaArvo(int y, int x, bool keskipeli)
{
	int mg_piece_value = 337;
	int eg_piece_value = 281;

	if (keskipeli)
	{
		int mg_knight_table[64] = {
		-167, -89, -34, -49,  61, -97, -15, -107,
		 -73, -41,  72,  36,  23,  62,   7,  -17,
		 -47,  60,  37,  65,  84, 129,  73,   44,
		  -9,  17,  19,  53,  37,  69,  18,   22,
		 -13,   4,  16,  13,  28,  19,  21,   -8,
		 -23,  -9,  12,  10,  19,  17,  25,  -16,
		 -29, -53, -12,  -3,  -1,  18, -14,  -19,
		-105, -21, -58, -33, -17, -28, -19,  -23,
		};

		int index = y * 8 + x;

		return mg_piece_value + mg_knight_table[index];
	}
	else
	{
		int eg_knight_table[64] = {
		-58, -38, -13, -28, -31, -27, -63, -99,
		-25,  -8, -25,  -2,  -9, -25, -24, -52,
		-24, -20,  10,   9,  -1,  -9, -19, -41,
		-17,   3,  22,  22,  22,  11,   8, -18,
		-18,  -6,  16,  25,  16,  17,   4, -18,
		-23,  -3,  -1,  15,  10,  -3, -20, -22,
		-42, -20, -10,  -5,  -2, -20, -23, -44,
		-29, -51, -23, -15, -22, -18, -50, -64,
		};

		int index = y * 8 + x;

		return eg_piece_value + eg_knight_table[index];

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
		int tempX = x + i;
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

double Lahetti::annaArvo(int y, int x, bool keskipeli)
{
	int mg_piece_value = 365;
	int eg_piece_value = 297;

	if (keskipeli)
	{
		int mg_bishop_table[64] = {
		-29,   4, -82, -37, -25, -42,   7,  -8,
		-26,  16, -18, -13,  30,  59,  18, -47,
		-16,  37,  43,  40,  35,  50,  37,  -2,
		 -4,   5,  19,  50,  37,  37,   7,  -2,
		 -6,  13,  13,  26,  34,  12,  10,   4,
		  0,  15,  15,  15,  14,  27,  18,  10,
		  4,  15,  16,   0,   7,  21,  33,   1,
		-33,  -3, -14, -21, -13, -12, -39, -21,
		};

		int index = y * 8 + x;

		return mg_piece_value + mg_bishop_table[index];
	}
	else
	{
		int eg_bishop_table[64] = {
		-14, -21, -11,  -8, -7,  -9, -17, -24,
		 -8,  -4,   7, -12, -3, -13,  -4, -14,
		  2,  -8,   0,  -1, -2,   6,   0,   4,
		 -3,   9,  12,   9, 14,  10,   3,   2,
		 -6,   3,  13,  19,  7,  10,  -3,  -9,
		-12,  -3,   8,  10, 13,   3,  -7, -15,
		-14, -18,  -7,  -1,  4,  -9, -15, -27,
		-23,  -9, -23,  -5, -9, -16,  -5, -17,
		};

		int index = y * 8 + x;

		return eg_piece_value + eg_bishop_table[index];

	}
}


void Daami::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	Torni::annaSiirrot(lista, ruutu, asema, vari);
	Lahetti::annaSiirrot(lista, ruutu, asema, vari);
}

double Daami::annaArvo(int y, int x, bool keskipeli)
{
	int mg_piece_value = 1025;
	int eg_piece_value = 936;

	if (keskipeli)
	{
		int mg_queen_table[64] = {
		-28,   0,  29,  12,  59,  44,  43,  45,
		-24, -39,  -5,   1, -16,  57,  28,  54,
		-13, -17,   7,   8,  29,  56,  47,  57,
		-27, -27, -16, -16,  -1,  17,  -2,   1,
		 -9, -26,  -9, -10,  -2,  -4,   3,  -3,
		-14,   2, -11,  -2,  -5,   2,  14,   5,
		-35,  -8,  11,   2,   8,  15,  -3,   1,
		 -1, -18,  -9,  10, -15, -25, -31, -50,
		};

		int index = y * 8 + x;

		return mg_piece_value + mg_queen_table[index];
	}
	else
	{
		int eg_queen_table[64] = {
		 -9,  22,  22,  27,  27,  19,  10,  20,
		-17,  20,  32,  41,  58,  25,  30,   0,
		-20,   6,   9,  49,  47,  35,  19,   9,
		  3,  22,  24,  45,  57,  40,  57,  36,
		-18,  28,  19,  47,  31,  34,  39,  23,
		-16, -27,  15,   6,   9,  17,  10,   5,
		-22, -23, -30, -16, -16, -23, -36, -32,
		-33, -28, -22, -43,  -5, -32, -20, -41,
		};

		int index = y * 8 + x;

		return eg_piece_value + eg_queen_table[index];

	}
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

	Siirto lyhytLinna(true, false);
	Siirto pitkaLinna(false, true);
	lista.push_back(lyhytLinna);
	lista.push_back(pitkaLinna);
}

double Kuningas::annaArvo(int y, int x, bool keskipeli)
{
	if (keskipeli)
	{
		int mg_king_table[64] = {
		-65,  23,  16, -15, -56, -34,   2,  13,
		 29,  -1, -20,  -7,  -8,  -4, -38, -29,
		 -9,  24,   2, -16, -20,   6,  22, -22,
		-17, -20, -12, -27, -30, -25, -14, -36,
		-49,  -1, -27, -39, -46, -44, -33, -51,
		-14, -14, -22, -46, -44, -30, -15, -27,
		  1,   7,  -8, -64, -43, -16,   9,   8,
		-15,  36,  12, -54,   8, -28,  24,  14,
		};

		int index = y * 8 + x;

		return mg_king_table[index];
	}
	else
	{
		int eg_king_table[64] = {
		-74, -35, -18, -18, -11,  15,   4, -17,
		-12,  17,  14,  17,  17,  38,  23,  11,
		 10,  17,  23,  15,  20,  45,  44,  13,
		 -8,  22,  24,  27,  26,  33,  26,   3,
		-18,  -4,  21,  24,  27,  23,   9, -11,
		-19,  -3,  11,  21,  23,  16,   7,  -9,
		-27, -11,   4,  13,  14,   4,  -5, -17,
		-53, -34, -21, -11, -28, -14, -24, -43
		};

		int index = y * 8 + x;

		return eg_king_table[index];

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

	double Sotilas::annaArvo(int y, int x, bool keskipeli)
	{
		int mg_piece_value = 82;
		int eg_piece_value = 94;

		if (keskipeli)
		{
			int mg_pawn_table[64] = {
			  0,   0,   0,   0,   0,   0,  0,   0,
			 98, 134,  61,  95,  68, 126, 34, -11,
			 -6,   7,  26,  31,  65,  56, 25, -20,
			-14,  13,   6,  21,  23,  12, 17, -23,
			-27,  -2,  -5,  12,  17,   6, 10, -25,
			-26,  -4,  -4, -10,   3,   3, 33, -12,
			-35,  -1, -20, -23, -15,  24, 38, -22,
			  0,   0,   0,   0,   0,   0,  0,   0,
			};

			int index = y * 8 + x;

			return mg_piece_value + mg_pawn_table[index];
		}
		else
		{
			int eg_pawn_table[64] = {
			  0,   0,   0,   0,   0,   0,   0,   0,
			178, 173, 158, 134, 147, 132, 165, 187,
			 94, 100,  85,  67,  56,  53,  82,  84,
			 32,  24,  13,   5,  -2,   4,  17,  17,
			 13,   9,  -3,  -7,  -7,  -8,   3,  -1,
			  4,   7,  -6,   1,   0,  -5,  -1,  -8,
			 13,   8,   8,  10,  13,   0,   2,  -7,
			  0,   0,   0,   0,   0,   0,   0,   0,
			};

			int index = y * 8 + x;

			return eg_piece_value + eg_pawn_table[index];

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