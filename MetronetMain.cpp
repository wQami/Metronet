#include "Metronet.h"
#include "Station.h"
#include "Tram.h"

using namespace std;

int main(){
    Metronet DeLijn("Advanced.xml");
    DeLijn.run(14);
    DeLijn.write();
    DeLijn.reset();

    Metronet DeStreep("Basic.xml");
    DeStreep.run(11);
    DeStreep.write();
    DeStreep.reset();

    return 0;
}

// Indien u de kunst van onze logbook wilt waarnemen in volle kwaliteit, dan gelieve het te openen in CLION :P

