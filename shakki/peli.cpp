#include "peli.h"

using namespace std;
int vastustajanVari = 0;

Peli::Peli(int ihmisenVari)
{
	_koneenVari = (ihmisenVari == 0) ? 1 : 0;

}


int Peli::getKoneenVari(){
	return _koneenVari;
}
