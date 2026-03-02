#pragma once

#include <vector>
#include <string>
#include "asema.h"
#include "siirto.h"


// Vakioarvot nappulatyypeille.
enum
{
	VT,VR,VL,VD,VK,VS,
	MT,MR,ML,MD,MK,MS   //Torni, ratsu, l‰hetti, daami, kuningas, sotilas
};


// Yliluokka shakkinappuloille.
class Nappula
{

private:
	std::wstring	_unicode;	// nappulaa vastaava unicode-merkki
	int				_vari;		// valkea = 0, musta = 1
	int				_koodi;		// VT, VR, MT tms.
	double			_arvo;		


public:
	Nappula(std::wstring, int, int, double);
	Nappula() {}

	// Siirtojen generointi. Puhdas virtuaalifunktio, eli aliluokat toteuttavat t‰m‰n
	// omalla tavallaan.
	virtual void annaSiirrot(std::vector<Siirto>& lista, Ruutu*, Asema*, int vari) = 0;
	virtual double annaArvo(int y, int x, bool keskipeli, int vari) = 0;

	void setUnicode(std::wstring unicode)	{ _unicode = unicode;			}
	std::wstring getUnicode()				{ return _unicode;				}
	void setVari(int vari)					{ _vari = vari;					}
	int getVari()							{ return _vari;					}
	int getKoodi()							{ return _koodi;				}
	void setKoodi(int koodi)				{ _koodi = koodi;				}
	double getArvo()						{ return _arvo;					}

};

// Torni-aliluokka. Virtuaalinen perint‰ tarkoittaa, ett‰ kantaluokka perit‰‰n moniperinn‰ss‰ vain kerran
// (koska daami perii sek‰ tornin ett‰ l‰hetin).
class Torni : public virtual Nappula {
public:
	Torni(std::wstring unicode, int vari, int koodi, double arvo) : Nappula(unicode, vari, koodi, arvo) {}
	void annaSiirrot(std::vector<Siirto>& lista, Ruutu*, Asema*, int vari);
	double annaArvo(int y, int x, bool keskipeli, int vari);

};

// Ratsu-aliluokka.
class Ratsu : public Nappula {
public:
	Ratsu(std::wstring unicode, int vari, int koodi, double arvo) : Nappula(unicode, vari, koodi, arvo) {}
	void annaSiirrot(std::vector<Siirto>& lista, Ruutu*, Asema*, int vari);
	double annaArvo(int y, int x, bool keskipeli, int vari);

};

// L‰hetti-aliluokka. Virtuaalinen perint‰ tarkoittaa, ett‰ kantaluokka perit‰‰n moniperinn‰ss‰ vain kerran
// (koska daami perii sek‰ tornin ett‰ l‰hetin).
class Lahetti : public virtual Nappula {
public:
	Lahetti(std::wstring unicode, int vari, int koodi, double arvo) : Nappula(unicode, vari, koodi, arvo) {}
	void annaSiirrot(std::vector<Siirto>& lista, Ruutu*, Asema*, int vari);
	double annaArvo(int y, int x, bool keskipeli, int vari);

};

// Daami-aliluokka. Perii sek‰ l‰hetin ett‰ tornin.
class Daami : public Lahetti, public Torni {
public:
	Daami(std::wstring unicode, int vari, int koodi, double arvo) : 
		Nappula(unicode, vari, koodi, arvo), Lahetti(unicode, vari, koodi, arvo), Torni(unicode, vari, koodi, arvo) {}
	void annaSiirrot(std::vector<Siirto>& lista, Ruutu*, Asema*, int vari);
	double annaArvo(int y, int x, bool keskipeli, int vari);

};

// Kuningas-aliluokka.
class Kuningas : public Nappula {
public:
	Kuningas(std::wstring unicode, int vari, int koodi, double arvo) : Nappula(unicode, vari, koodi, arvo) {}
	void annaSiirrot(std::vector<Siirto>& lista, Ruutu*, Asema*, int vari);
	double annaArvo(int y, int x, bool keskipeli, int vari);

};

// Sotilas-aliluokka.
class Sotilas : public Nappula {
public:
	Sotilas(std::wstring unicode, int vari, int koodi, double arvo) : Nappula(unicode, vari, koodi, arvo) {}
	void annaSiirrot(std::vector<Siirto>& lista, Ruutu*, Asema*, int vari);
	double annaArvo(int y, int x, bool keskipeli, int vari);
private:
	void lisaaSotilaanKorotukset(Siirto*, std::vector<Siirto>& lista, Asema*);
};


