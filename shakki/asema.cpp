#include <iostream>
#include "asema.h"
#include "minMaxPaluu.h"
#include "nappula.h"
#include "ruutu.h"

using namespace std;

Nappula* Asema::vk = new Kuningas(L"\u2654", 0, VK, 0);
Nappula* Asema::vd = new Daami(L"\u2655", 0, VD, 9);
Nappula* Asema::vt = new Torni(L"\u2656", 0, VT, 5);
Nappula* Asema::vl = new Lahetti(L"\u2657", 0, VL, 3.25);
Nappula* Asema::vr = new Ratsu(L"\u2658", 0, VR, 3);
Nappula* Asema::vs = new Sotilas(L"\u2659", 0, VS, 1);

Nappula* Asema::mk = new Kuningas(L"\u265A", 1, MK, 0);
Nappula* Asema::md = new Daami(L"\u265B", 1, MD, 9);
Nappula* Asema::mt = new Torni(L"\u265C", 1, MT, 5);
Nappula* Asema::ml = new Lahetti(L"\u265D", 1, ML, 3.25);
Nappula* Asema::mr = new Ratsu(L"\u265E", 1, MR, 3);
Nappula* Asema::ms = new Sotilas(L"\u265F", 1, MS, 1);



Asema::Asema()
{
	//Luodaan array alkuasema rivesit‰ s‰‰st‰‰ksemme if lauseissa
	Nappula* valkoistenTakaRivi[8] = { vt, vr, vl, vd, vk, vl, vr, vt };
	Nappula* mustienTakaRivi[8] = { mt, mr, ml, md, mk, ml, mr, mt };

	// Ensin alustetaan kaikki laudan ruudut nappulla "NULL", koska muuten ruuduissa satunnaista tauhkaa

	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			_lauta[y][x] = NULL;
		}
	}

	// Asetetaan alkuaseman mukaisesti nappulat ruuduille
	// Origo on vasemmassa alakulmassa (a1 = [0][0])
	// Rivi 0 = rank 1 (valkoisten takarivi)
	// Rivi 7 = rank 8 (mustien takarivi)
	for (int j = 0; j < 8; j++)
	{
		//asetetaan yksikkˆ rivit paikalleen yksi kerrallaan
		_lauta[7][j] = mustienTakaRivi[j];  // Mustat rivi 8
		_lauta[6][j] = ms;                   // Mustat sotilaat rivi 7

		_lauta[1][j] = vs;                   // Valkeat sotilaat rivi 2
		_lauta[0][j] = valkoistenTakaRivi[j]; // Valkeat rivi 1
	}


}


void Asema::paivitaAsema(Siirto *siirto)
{
	
	// Kaksoisaskel-lippu on oletusarvoisesti pois p‰‰lt‰.
	kaksoisaskelSarakkeella = -1;
	// Asetetaan myˆhemmin, jos tarvii.


	//Tarkastetaan on siirto lyhyt linna
	if (siirto->onkoLyhytLinna())
	{
		//Valkoisen lyhyt linna
		if (_siirtovuoro == 0)
		{
			//Siirret‰‰n nappulat ja asetetaan flagit
			_lauta[0][7] = NULL;
			_lauta[0][6] = vk;
			_lauta[0][5] = vt;
			_lauta[0][4] = NULL;
			_onkoValkeaKTliikkunut = true;
			_onkoValkeaKuningasLiikkunut = true;

		}
		else
		{
			_lauta[7][7] = NULL;
			_lauta[7][6] = mk;
			_lauta[7][5] = mt;
			_lauta[7][4] = NULL;
			_onkoMustaKTliikkunut = true;
			_onkoMustaKuningasLiikkunut = true;
		}

		if (_siirtovuoro == 1)
		{
			_siirtovuoro = 0;
		}
		else
		{
			_siirtovuoro = 1;
		}

		wcout << "siirtovuoro: " << _siirtovuoro << endl;

		return;
	}
	// onko pitk‰ linna
	if (siirto->onkoPitk‰linna())
	{
		//Valkoisen lyhyt linna
		if (_siirtovuoro == 0)
		{
			//Siirret‰‰n nappulat ja asetetaan flagit
			_lauta[0][0] = NULL;
			_lauta[0][1] = NULL;
			_lauta[0][2] = vk;
			_lauta[0][3] = vt;
			_lauta[0][4] = NULL;
			_onkoValkeaDTliikkunut = true;
			_onkoValkeaKuningasLiikkunut = true;
		}
		else
		{
			_lauta[7][0] = NULL;
			_lauta[7][1] = NULL;
			_lauta[7][2] = mk;
			_lauta[7][3] = mt;
			_lauta[7][4] = NULL;
			_onkoMustaDTliikkunut = true;
			_onkoMustaKuningasLiikkunut = true;
		}

		if (_siirtovuoro == 1)
		{
			_siirtovuoro = 0;
		}
		else
		{
			_siirtovuoro = 1;
		}

		wcout << "siirtovuoro: " << _siirtovuoro << endl;
		return;
	}


	// Kaikki muut siirrot
	Ruutu alkuRuutu = siirto->getAlkuruutu();
	Ruutu loppuRuutu = siirto->getLoppuruutu();

	//Otetaan nappula alkuruudusta
	Nappula* siirrettyNappula = _lauta[alkuRuutu.getRivi()][alkuRuutu.getSarake()];

	//Asetetaan l‰htˆruutu tyhj‰ksi 
	_lauta[alkuRuutu.getRivi()][alkuRuutu.getSarake()] = NULL;

	//Sijoitetaan nappula uuteen sijaintiin
	_lauta[loppuRuutu.getRivi()][loppuRuutu.getSarake()] = siirrettyNappula;


	//Asetetaan nappuloiden flagit 
	switch (siirrettyNappula->getKoodi()) 
	{
		case VK:
			_onkoValkeaKuningasLiikkunut = true;
			break;
		case MK:
			_onkoMustaKuningasLiikkunut = true;
			break;
		case VT:
			if (alkuRuutu.getSarake() == 0)
			{
				_onkoValkeaDTliikkunut = true;
			}
			else
			{
				_onkoValkeaKTliikkunut = true;
			}
			break;
		case MT:
			if (alkuRuutu.getSarake() == 0)
			{
				_onkoMustaDTliikkunut = true;
			}
			else
			{
				_onkoMustaKTliikkunut = true;
			}
			break;
		case VS:
			if (loppuRuutu.getRivi() == 3 && alkuRuutu.getRivi() == 1)
			{
				kaksoisaskelSarakkeella = loppuRuutu.getSarake();
			}
			break;
		case MS:
			if (loppuRuutu.getRivi() == 4 && alkuRuutu.getRivi() == 6)
			{
				kaksoisaskelSarakkeella = loppuRuutu.getSarake();
			}
			break;
		}

	if (_siirtovuoro == 1)
	{
		_siirtovuoro = 0;
	}
	else
	{
		_siirtovuoro = 1;
	}



		//Ottaa siirron alkuruudussa olleen nappulan talteen 


		//Laittaa talteen otetun nappulan uuteen ruutuun


		// Tarkistetaan oliko sotilaan kaksoisaskel
		// (asetetaan kaksoisaskel-lippu)

		// Ohestalyˆnti on tyhj‰‰n ruutuun. Vieress‰ oleva (sotilas) poistetaan.

		//// Katsotaan jos nappula on sotilas ja rivi on p‰‰tyrivi niin ei vaihdeta nappulaa 
		////eli alkuruutuun laitetaan null ja loppuruudussa on jo kliittym‰n laittama nappula MIIKKA, ei taida minmaxin kanssa hehkua?

		//
		////muissa tapauksissa alkuruutuun null ja loppuruutuun sama alkuruudusta l‰htenyt nappula

		// katsotaan jos liikkunut nappula on kuningas niin muutetaan onkoKuningasLiikkunut arvo (molemmille v‰reille)

		// katsotaan jos liikkunut nappula on torni niin muutetaan onkoTorniLiikkunut arvo (molemmille v‰reille ja molemmille torneille)

	//p‰ivitet‰‰n _siirtovuoro

}



int Asema::getSiirtovuoro() 
{
	return _siirtovuoro;
}


void Asema::setSiirtovuoro(int vuoro) 
{
	_siirtovuoro = vuoro;
}


bool Asema::getOnkoValkeaKuningasLiikkunut() 
{
	return _onkoValkeaKuningasLiikkunut;
}


bool Asema::getOnkoMustaKuningasLiikkunut() 
{

	return _onkoMustaKuningasLiikkunut;
}


bool Asema::getOnkoValkeaDTliikkunut() 
{
	return _onkoValkeaDTliikkunut;
}


bool Asema::getOnkoValkeaKTliikkunut() 
{
	return _onkoValkeaKTliikkunut;
}


bool Asema::getOnkoMustaDTliikkunut() 
{
	return _onkoMustaDTliikkunut;
}


bool Asema::getOnkoMustaKTliikkunut() 
{
	return _onkoMustaKTliikkunut;
}


/* 1. Laske nappuloiden arvo
Daami = 9
Torni = 5
L‰hetti = 3,25
Ratsu = 3
Sotilas = 1

2. Kuninkaan hyvyys
Jos avaus tai keskipeli, niin hyv‰ ett‰ kunigas g1 tai b1/c1
Loppupeliss‰ vaikea sanoa halutaanko olla auttamassa omaa sotilasta korottumaan
vai olla est‰m‰ss‰ vastustajan korotusta siksi ei oteta kantaa
3. Arvosta keskustaa sotilailla ja ratsuilla
4. Arvosta pitki‰ linjoja daami, torni ja l‰hetti
*/
double Asema::evaluoi() 
{
	double valkoiset = laskeNappuloidenArvo(0);
	double mustat = laskeNappuloidenArvo(1);

	//kertoimet asetettu sen takia ett‰ niiden avulla asioiden painoarvoa voidaan s‰‰t‰‰ helposti yhdest‰ paikasta
	
	//1. Nappuloiden arvo
	
	//2. Kuningas turvassa
	
	//3. Arvosta keskustaa
	
	// 4. Arvosta linjoja
	
	return valkoiset - mustat;
}


double Asema::laskeNappuloidenArvo(int vari) 
{
	int mustat = 0;
	int valkoiset = 0;

	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			if (_lauta[y][x] != NULL)
			{
				if (_lauta[y][x]->getVari() == 0)
				{
					valkoiset += _lauta[y][x]->getArvo();
				}
				else
				{
					mustat += _lauta[y][x]->getArvo();
				}
			}
		}
	}
	if (vari == 0)
	{
		return valkoiset;
	}
	else
	{
		return mustat;
	}
}


bool Asema::onkoAvausTaiKeskipeli(int vari) 
{
	return 0;
	// Jos upseereita 3 tai v‰hemm‰n on loppupeli
	// mutta jos daami laudalla on loppueli vasta kun kuin vain daami j‰ljell‰
	
	//Jos vari on 0 eli valkoiset
	//niin on keskipeli jos mustalla upseereita yli 2 tai jos daami+1
	

}


double Asema::nappuloitaKeskella(int vari) 
{
	return 0;

	//sotilaat ydinkeskustassa + 0.25/napa
	//ratsut ydinkeskustassa + 0.25/napa
	//sotilaat laitakeskustassa + 0.11/napa
	//ratsut laitakeskustassa + 0.11/napa
	
	//valkeille ydinkeskusta

	
	
	//valkeille laitakeskusta
	


	//mustille ydinkeskusta
	
	//mustille laitakeskusta
	
}


double Asema::linjat(int vari) 
{
	return 0;
	
	//valkoiset
	
	//mustat
	
}

// https://chessprogramming.wikispaces.com/Minimax MinMax-algoritmin pseudokoodi (lis‰sin parametrina aseman)
//int maxi(int depth, asema a) 
//	if (depth == 0) return evaluate();
//	int max = -oo;
//	for (all moves ) {
//		score = mini(depth - 1, seuraaja);
//		if (score > max)
//			max = score;
//	}
//	return max;
//}

//int mini(int depth, asema a) {
//	if (depth == 0) return -evaluate();
//	int min = +oo;
//	for (all moves) {
//		score = maxi(depth - 1);
//		if (score < min)
//			min = score;
//	}
//	return min;
//}
MinMaxPaluu Asema::minimax(int syvyys)
{
	MinMaxPaluu paluuarvo;
	if (getSiirtovuoro() == 0)
	{
		paluuarvo = maxi(syvyys);
	}
	else
	{
		paluuarvo = mini(syvyys);
	}


	// Generoidaan aseman lailliset siirrot.
	
	// Rekursion kantatapaus 1: peli on loppu
	
	// Rekursion kantatapaus 2: katkaisusyvyydess‰
	
	// Rekursioaskel: kokeillaan jokaista laillista siirtoa s
	// (alustetaan paluuarvo huonoimmaksi mahdolliseksi).
	
	return paluuarvo;
}


MinMaxPaluu Asema::maxi(int syvyys) 
{
	MinMaxPaluu paluu;
	double maximi = -10000;
	
	return paluu;
}


MinMaxPaluu Asema::mini(int syvyys) 
{
	MinMaxPaluu paluu;
	return paluu;
}


bool Asema::onkoRuutuUhattu(Ruutu* ruutu, int vastustajanVari)
{
	list<Siirto> raakaLista;

	//K‰yd‰‰n lauta l‰pi ja kasataan kaikki vastustajan raakasiirrot
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			//Jos laudalla on vastustajan nappi niin sille haetaan kaikki raakasirrot
			if (_lauta[y][x] != NULL && _lauta[y][x]->getVari() == vastustajanVari)
			{
				Ruutu ruutu(x, y);
				_lauta[y][x]->annaSiirrot(raakaLista, &ruutu, this, vastustajanVari);
			}
		}
	}

	//Katsotaan vastaako mik‰‰n siirto vastustajan kuninkaan koordinaatteja
	for (Siirto s : raakaLista)
	{
		int y = s.getLoppuruutu().getRivi();
		int x = s.getLoppuruutu().getSarake();

		if (ruutu->getRivi() == y && ruutu->getSarake() == x)
		{
			return true;
		}
	}

	return false;
}


void Asema::huolehdiKuninkaanShakeista(std::list<Siirto>& lista, int vari) 
{ 
	list<Siirto> laillisetSiirrot;
	int vastustajanVari = (vari == 0) ? 1 : 0;
	// Asetetaan ulos laudasta, ettei tule sekannusta tilanteessa jossa kuningasta ei lˆydy
	int kuninkaanX = -1;
	int kuninkaanY = -1;
	Asema asemanKopio = *this;

	//K‰yd‰‰n raakasiirrot l‰pi 
	for (Siirto s : lista)
	{
		paivitaAsema(&s);   

		//K‰yd‰‰n lauta l‰pi ja p‰ivitet‰‰n kuninkaan koordinaatit 
		for (int y = 0; y < 8; y++)
		{
			for (int x = 0; x < 8; x++)
			{
				if (_lauta[y][x] && _lauta[y][x]->getKoodi() == VK && vari == 0)
				{
					kuninkaanX = x;
					kuninkaanY = y;

				}
				else if (_lauta[y][x] && _lauta[y][x]->getKoodi() == MK && vari == 1)
				{
					kuninkaanX = x;
					kuninkaanY = y;
				}
			}
		}

		Ruutu kuninkaanRuutu(kuninkaanX, kuninkaanY);
		if (!onkoRuutuUhattu(&kuninkaanRuutu, vastustajanVari))
		{
			laillisetSiirrot.push_back(s);
		}

		// Siirron tarkastuksen j‰lkeen palataan alkutilanteeseen
		*this = asemanKopio;
	}

	lista = laillisetSiirrot;
}


void Asema::annaLaillisetSiirrot(std::list<Siirto>& lista) {

	//K‰yd‰‰n lauta l‰pi ja otetaan siiron tekev‰n v‰rin raakasiirrot
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			if (_lauta[y][x] != NULL && _lauta[y][x]->getVari() == _siirtovuoro)
			{
				Ruutu ruutu(x, y);
				_lauta[y][x]->annaSiirrot(lista, &ruutu, this, _lauta[y][x]->getVari());
			}
		}
	}

	huolehdiKuninkaanShakeista(lista, _siirtovuoro);
}
