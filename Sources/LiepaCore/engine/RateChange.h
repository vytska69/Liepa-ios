///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Projektas LIEPA (https://liepa.raðtija.lt)
// Sintezatoriaus komponentas RateChange.dll
// Failas RateChange.h
// Autorius dr. Gintaras Skersys
// 2015 08 11
//
///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef RATECHANGE_H
#define RATECHANGE_H

//#include <windows.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

/*********************************************************
 * Konstantos
 ********************************************************/

const double pi = 3.14159265359;

// Koks didþiausias gali bûti atstumas tarp pikø reguliariame garse.
// Jei atstumas tarp pikø arba tarp piko ir garso ribos yra didesnis, 
// tai kaþkas negerai, todël negalime tam garsui trumpinti naudoti pikø
// Laikome, kad garsas negali bûti þemesnis uþ 50 Hz, 
// t.y atstumai tarp pikø negali bûti didesni uþ 1/50 s, 
// t.y. atstumai tarp pikø indeksø garso masyve negali bûti didesni uþ 22050/50=441.
#define MAX_ATSTUMAS_TARP_PIKU 441 
// t.y. atstumai tarp pikø indeksø garso masyve negali bûti didesni uþ 11025/50=221.
//#define MAX_ATSTUMAS_TARP_PIKU 221 

// koeficientas realloc funkcijai masyvo naujas_signalas pailginimui. 
// Tiek kartø bus pailgintas masyvas naujas_signalas.
// naujas_ilgis = REALLOC_COEFF * senas_ilgis, jei naujas_ilgis pakankamas
#define REALLOC_COEFF 1.2

// koeficientas, parodantis, kiek kartø daugiau reikia iðskirti atminties 
// naujo signalo masyvui, negu apytikslis ávertis (dël visa ko)
#define NAUJO_SIGNALO_MASYVO_ILGIO_KOEF 1.1f

// nurodo signalo masyvo indeksø skaièiumi, kiek bûtina palikti leistinosios srities,  
// trumpinant dusliuosius priebalsius.
// Gali bûti nulis. Normalu - apie 50.
// Nerekomenduojama > 200, nes tada kai kuriø fonemø visai nesutrumpins.
#define ISSAUGOTI_GALIMOS_SRITIES_ILGIO 100

// jei nëra pikø, imam burbulà ne pagal pikus, o simetriðkà 2*PUSE_BURBULO_ILGIO ilgio burbulà
// TODO: ar naudoti kaþkokià konstantà, ar pabandyti apsiskaièiuoti burbulo ilgá ið signalo?
//#define PUSE_BURBULO_ILGIO 240

// kadangi naujos fonemos ilgis gali bûti ir neigiamas, klaidos kodui gràþinti reikia didelës neigiamos reikðmës
#define DIDELIS_NEIGIAMAS_KLAIDOS_KODAS -10000

/*********************************************************
Fonemø klasiø numeriai pagal fonemos pavadinimo pirmàjà raidæ:
0 - turintys pikø informacijà (skardieji priebalsiai, balsiai, t.y. visi, iðskyrus x, f, p, t, k, s, S, _, r, R, z, Z, H)
1 - neturintys pikø informacijos (duslieji priebalsiai, t.y. x, f, p, t, k, s, S, _)
//2 - gali turëti ar neturëti pikø informacijos, todël gali bûti priskirti kuriai nors ið pirmøjø dviejø klasiø - reikia papildomo tikrinimo (z, Z, h),
3 - neaiðku, kà daryti (r, R).
*********************************************************/
#define FONEMU_KLASE_SKARDIEJI 0
#define FONEMU_KLASE_DUSLIEJI 1
//#define FONEMU_KLASE_ZZH 2
#define FONEMU_KLASE_RR 3

/*********************************************************
 * Burbulai
 ********************************************************/

struct burbulas
{
	// burbulo koordinatës
	size_t pradzia;
	size_t vidurys;
	size_t pabaiga;

	// kiek kartø dubliuoti burbulà
	int kartai;

	// ar burbulas sudarytas pikø pagrindu, 
	// t.y. ar jo koordinatës sutampa su pikø koordinatëmis.
	// Jei reikðmë nelygi nuliui, tai pikø pagrindu.
	//int pikai;
};

// nurodo, kiek burbulø vienai fonemai gali tekti keisti (paðalinti ar dubliuoti)
#define MAX_KEICIAMI_BURBULAI 500

// kad nesigautø periodinis signalas, dusliøjø priebalsiø burbulai, jei juos reikës kartoti > 1 kartà, gaminami nesimetriðki. 
// Ðis parametras nurodo, kurioje burbulo vietoje bus jo centras (vidurys). 
// Jei = 0.0, tai vidurys sutaps su pradzia, jei = 1.0, sutaps su pabaiga, jei = 0.5, bus lygiai per vidurá tarp pradzios ir pabaigos. 
// Kad burbulas bûtø nesimetriðkas, rinktis reikðmæ != 0.5. 
//#define BURBULO_CENTRO_POZICIJA 0.50

/*********************************************************
 * Kontekstas
 * 
 * Kad sintezavimas veiktø daugelio gijø reþimu 
 * (kai pakrauta viena garsø bazë, taèiau funkcija change_phoneme_rate() ið RateChange.cpp gali bûti vienu metu kvieèiama ið skirtingø gijø), 
 * neturi bûti globaliø kintamøjø, á kuriuos raðoma sintezavimo metu 
 * (pastaba: gali bûti globalûs kintamieji, á kuriuos raðoma garsø bazës uþkrovimo metu). 
 * Visus tokius globalius kintamuosius, á kuriuos iki ðiol buvo raðoma sintezavimo metu, nuo ðiol reikia perduoti kaip funkcijø parametrus. 
 * Kadangi jø nemaþai, juos sudedu á vienà struktûrà, kurià ir perduosiu.
 ********************************************************/

struct tkontekstas {
	// einamosios fonemos numeris
	unsigned int fonemos_nr;

	// einamosios fonemos pradþia ir pabaiga
	unsigned int fonemos_pradzia;
	unsigned int fonemos_pabaiga;

	// numeris pirmojo piko, esanèio einamosios fonemos pradþioje 
	// (tiksliau, pirmojo piko, nepriklausanèio prieð tai buvusiai fonemai. 
	// Jis gali nepriklausyti ir einamajai, o kuriai nors tolimesnei).
	unsigned int pirmojo_piko_nr;

	// kiek pikø yra tarp fonemos pradþios ir pabaigos
	unsigned int piku_sk;
	
	// Greitinimo koeficientas (kiek kartø turi pailgëti signalas)
	double greitinimo_koef;

	// Tarpo tarp pikø didinimo koeficientas (kiek kartø turi padidëti tarpas tarp pikø)
	double tarpo_tarp_piku_didinimo_koef;
	
	// skirtumas tarp to, koks plotis buvo panaudotas rezultatuose, ir koks duomenyse.
	// Bus neigiamas, jei signalo rezultatas sutrumpëjo, ir teigiamas, jei pailgëjo.
	// Per tiek padidës fonemø ilgiai
	int einamasis_postumis;
	
	// einamasis garso signalo masyvo indeksas
	size_t einamasis_signalo_nr;
	
	// garso signalo masyvas, iðskiriamas dinamiðkai
	short * naujas_signalas;
	
	// naujojo garso signalo masyvo ilgis (ne signalo ilgis, o kiek iðskirta vietos masyvui. 
	// Paprastai masyvo ilgis didesnis uþ signalo ilgá)
	size_t naujo_signalo_masyvo_ilgis;
	
	// garso signalo ilgis
	//size_t naujo_signalo_ilgis;
	
	// einamasis naujo garso signalo masyvo indeksas
	size_t einamasis_naujo_signalo_nr;

	// nurodo, ar galima pailginti masyvà naujas_signalas, jei per trumpas (0 - negalima, !=0 - galima)
	// (negalima - jei masyvas naujas_signalas gautas ið iðorës (jei greitinama ið funkcijos change_phoneme_rate), 
	// galima - jei atmintis jam iðskirta viduje (RateChange.dll'e) (jei greitinama ið funkcijos change_DB_rate))
	int galima_pailginti_naujas_signalas;
	
	// Euristika nustatys, kuriuos burbuliukus reikia paðalinti ar dubliuoti. 
	// Jø sàraðà pateiks ðiame kintamajame "burbulai". 
	// Kad nereikëtø pastoviai iðskirinëti jam atminties, 
	// èia iðskiriame vienà kartà ir pastoviai naudojame.
	// TODO: pastoviai tikrinti, ar nevirðijo MAX_BURBULAI. Virðijus kaþkà daryti.
	struct burbulas burbulai[MAX_KEICIAMI_BURBULAI];

	// keièiamø (ðalinamø ar dubliuojamø) burbulø skaièius
	int keiciamu_burbulu_sk;
	
	// fonemos klasë, nurodanti, ar ilginimui turime pikø informacijà, ar ne 
	// (FONEMU_KLASE_SKARDIEJI - turime, FONEMU_KLASE_DUSLIEJI - ne, FONEMU_KLASE_RR - nieko nedarome)
	int fonemos_klase;

	// nurodo, ar keisti pagrindinio tono aukðtá (0 - negalima, !=0 - galima)
	// Keisti, jei:
	// 1) fonema balsë arba skardusis priebalsis
	// 2) fonema turi > 1 pikà (prieðingu atveju pagrindinis tonas nëra patikimas, nes abiejose pusëse gali bûti fonemos be pikø 
	// - kaip tokiu atveju rasti tarpà tarp pikø?)
	// 3) funkcija change_phoneme_rate() iðkviesta su parametru tono_aukscio_pokytis != 100
	int keisti_tono_auksti;
};

/*********************************************************
 * Greitis.cpp
 ********************************************************/

extern char signalo_failo_pavadinimas[];
extern short * signalas;
extern size_t signalo_ilgis;
extern const char * naujo_signalo_failo_pavadinimas;
extern char fonemu_failo_pavadinimas[];
extern char ** fonemos;
extern int * fonemu_ilgiai;
extern size_t fonemu_kiekis;
extern const char * naujo_fonemu_failo_pavadinimas;
extern int * nauji_fonemu_ilgiai;
extern char vidutiniu_ilgiu_fonemu_failo_pavadinimas[];
extern char ** skirtingos_fonemos;
extern int * vidutiniai_fonemu_ilgiai;
extern size_t skirtingu_fonemu_kiekis;
extern char piku_failo_pavadinimas[];
extern unsigned int * pikai;
extern size_t piku_kiekis;
extern const int scenarijus;
extern double scenarijaus5_koeficientas;

void klaida (char * klaidos_pranesimas);
void spausdinti_burbulus (struct burbulas * burbulai, int burbulu_sk);
int kopijuoti_signala_pradzioj (struct tkontekstas * kontekstas);
int kopijuoti_signala_pabaigoj (struct tkontekstas * kontekstas);
int kopijuoti_signala (size_t iki, struct tkontekstas * kontekstas);
int trumpinti_fonema (struct tkontekstas * kontekstas);
int ilginti_fonema (struct tkontekstas * kontekstas);
int vykdyti (int greitis, int tono_aukscio_pokytis, struct tkontekstas * kontekstas);

/*********************************************************
 * VeiksmaiSuFailais.cpp
 ********************************************************/

void sukurti_kataloga (char * katalogoVardas);
int failu_sarasas_is_katalogo (char * katalogoVardas, char ** failu_vardai);

int nuskaityti_anotacijas (char * fonemu_failo_pavadinimas, char *** fonemos1, int ** fonemu_ilgiai1, size_t * fonemu_kiekis1);
int nuskaityti_duomenis ();
int nuskaityti_ilginimo_koeficientus (char * failo_pavadinimas, float ** pateikti_koef1, float ** faktiniai_koef1, int * koef_skaicius);

int irasyti_anotacijas ();
int irasyti_duomenis (struct tkontekstas * kontekstas);

/*********************************************************
 * Euristika.cpp
 ********************************************************/

void euristika (struct tkontekstas * kontekstas);
bool reguliarus_pikai (struct tkontekstas * kontekstas);

/*********************************************************
 * RateChange.cpp
 ********************************************************/

extern int debuginam;

void spausdinti_loga(char* pranesimas);
void spausdinti_konteksta (struct tkontekstas * kontekstas);
int fonemosKlase (struct tkontekstas * kontekstas);

/*********************************************************
 * Klaidø kodai
 ********************************************************/
#include "LithUSS_Error.h"

#endif