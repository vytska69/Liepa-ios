///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Projektas LIEPA (https://liepa.raðtija.lt)
// Sintezatoriaus komponentas RateChange.dll
// Failas RateChange.cpp
// Autorius dr. Gintaras Skersys
// 2015 08 11
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//#include "stdafx.h"
#include "RateChange.h"

/*********************************************************
 * Globalûs kintamieji
 ********************************************************/

// numeris pirmojo piko, esanèio einamosios fonemos pradþioje 
// (tiksliau, pirmojo piko, nepriklausanèio prieð tai buvusiai fonemai. 
// Jis gali nepriklausyti ir einamajai, o kuriai nors tolimesnei).
int * pirmojo_piko_nr_fonemose = NULL;

// pikø skaièius fonemoje
int * piku_skaicius_fonemose = NULL;

// fonemø pradþiø indeksai signalo masyve.
// Kai naudojami dinaminiam greièio keitimui, nereikia atlaisvinti atminties, nes ji iðskiriama ne RateChange.dll'e.
// Kai naudojami statiniam greièio keitimui, atmintis iðskiriama ir atlaisvinama change_DB_rate() funkcijoje.
long * fonemu_adresai = NULL;

// jei ne nulis, iðveda papildomà informacijà apie programos darbà, apie kiekvienà apdorojamà fonemà
// jei > 100, iðveda detalià informacijà
// jei > 200, be proto daug detaliø
// jei > 10000, spausdina garso masyvus á failus (jei neuþkomentuotas toks kodas)
int debuginam = 0;

/*********************************************************
 * atlaisvinti_atminti_ir_inicializuoti
 ********************************************************/
void atlaisvinti_atminti_ir_inicializuoti ()
{
	if(signalas != NULL) {free(signalas); signalas=NULL;}
	signalo_ilgis = 0;
	if(fonemos != NULL) {
		for (size_t i=0; i < fonemu_kiekis; i++) {
			if(fonemos[i] != NULL) {free(fonemos[i]); fonemos[i]=NULL;}
		}
		free(fonemos); fonemos=NULL;
	}
	fonemu_kiekis = 0;
	if(fonemu_ilgiai != NULL) {free(fonemu_ilgiai); fonemu_ilgiai=NULL;}
	if(pikai != NULL) {free(pikai); pikai=NULL;}
	piku_kiekis = 0;
	if(skirtingos_fonemos != NULL) {free(skirtingos_fonemos); skirtingos_fonemos=NULL;}
	if(vidutiniai_fonemu_ilgiai != NULL) {free(vidutiniai_fonemu_ilgiai); vidutiniai_fonemu_ilgiai=NULL;}
	skirtingu_fonemu_kiekis = 0;
	if(pirmojo_piko_nr_fonemose != NULL) {free(pirmojo_piko_nr_fonemose); pirmojo_piko_nr_fonemose=NULL;}
	if(piku_skaicius_fonemose != NULL) {free(piku_skaicius_fonemose); piku_skaicius_fonemose=NULL;}
}

/*********************************************************
 * DllMain
 ********************************************************/
/*BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    if(ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
		// apsitvarkome
		atlaisvinti_atminti_ir_inicializuoti ();
	}
    else if(ul_reason_for_call == DLL_PROCESS_DETACH)
	{
		atlaisvinti_atminti_ir_inicializuoti ();
	}

    return TRUE;
}*/

/*********************************************************
 * spausdinti_loga
 ********************************************************/
void spausdinti_loga(char* pranesimas)
{
	// Gintaras: pridëjau laiko þymæ
	time_t mytime = time(NULL);
	//char * mytime_string = ctime(&mytime);
	char mytime_string[1024];
	strftime(mytime_string, sizeof mytime_string, "%F %H:%M:%S", localtime(&mytime));

	FILE *stream;
	stream = fopen("/sdcard/LUSS_log.txt", "a+");
	if (stream != 0) {
		fprintf(stream, "%s %s\n", mytime_string, pranesimas);
		//printf("%s%s\n", mytime_string, pranesimas);
		fclose(stream);
	}
}

/*********************************************************
* spausdinti_int_masyva
********************************************************/
template< class T>
void spausdinti_int_masyva(T masyvas, int ilgis) {
	char * pranesimas = (char*)malloc(ilgis * 30 + 100);
	char * pranesimas1 = pranesimas;
	pranesimas1 += sprintf(pranesimas, "[ ");
	for (int i = 0; i < ilgis; i++)
		pranesimas1 += sprintf(pranesimas1, "[%d, %d], ", i, *(masyvas+i));
	pranesimas1 += sprintf(pranesimas1, " ]");
	spausdinti_loga(pranesimas);
	if (pranesimas != NULL) { free(pranesimas); pranesimas = NULL; }
}
template void spausdinti_int_masyva(int* masyvas, int ilgis);
template void spausdinti_int_masyva(unsigned int* masyvas, int ilgis);
template void spausdinti_int_masyva(unsigned short* masyvas, int ilgis);

/*void spausdinti_int_masyva(int* masyvas, int ilgis)
{
	char * pranesimas = (char*)malloc(ilgis * 20 + 100);
	char * pranesimas1 = pranesimas;
	pranesimas1 += sprintf(pranesimas, "[ ");
	for (int i = 0; i < ilgis; i++)
		pranesimas1 += sprintf(pranesimas1, "%d, ", unitsRows[i]);
	pranesimas1 += sprintf(pranesimas1, "], retUnits=[");
	spausdinti_loga(pranesimas);
}
*/
/*********************************************************
* Spausdina short masyvo signbuf signbufsize reikðmiø á failà.
* Failo pavadinimà suformuoja ið timestamp'o (sekundþiø tikslumu) ir perduoto text.
* Iðveda apie tai informacijà á log failà.
********************************************************/
void spausdinti_short_masyva(char *text, short* signbuf, int signbufsize) {
	// suformuojame laiko þymæ
	time_t mytime = time(NULL);
	//char * mytime_string = ctime(&mytime);
	char mytime_string[1024];
	strftime(mytime_string, sizeof mytime_string, "%F %H%M%S", localtime(&mytime));

	// suformuojame failo pavadinimà
	char filename[1024];
	sprintf(filename, "/sdcard/%s %s.dat3", mytime_string, text); // "dat3" þymi, kad ið LithUSS

	// iðvedame informacijà á log failà
	char pranesimas[1024];
	sprintf(pranesimas, "writing audio to file '%s\'", filename);
	spausdinti_loga(pranesimas);

	// atspausdiname garso masyvà á failà
	FILE *f = fopen(filename, "wb");
	if (f != 0) {
		fwrite(signbuf, sizeof(short), signbufsize, f);
		fclose(f);
	}
	else {
		char pranesimas[1024];
		sprintf(pranesimas, "Klaida atidarant garso faila rasymui. Garsas neisvestas i faila.");
		spausdinti_loga(pranesimas);
	}
}

/*********************************************************
 * Prieð kvieèiant ðià funkcijà, nuskaityti duomenis ir apskaièiuoti greitinimo_koef.
 * Gràþina rekomenduojamà naujo signalo masyvo ilgá - ðiek tiek didesná, nei reiktø pagal greitinimo koeficientà.
 ********************************************************/
size_t rekomenduoti_naujo_signalo_masyvo_ilgi (int greitis, int tono_aukscio_pokytis) // ivertinti_naujo_signalo_ilgi ?
{
	// TODO: turëtø atsiþvelgti ir á tono_aukscio_pokytis (kaip?)

	if (greitis == 100 && tono_aukscio_pokytis == 100)
		// naujo signalo ilgis sutaps su seno
		return signalo_ilgis;

	double greitinimo_koef = (double) greitis/100;

	// dël visa ko dar kiek padidinkime koeficientà
	double padidintas_koef = greitinimo_koef * NAUJO_SIGNALO_MASYVO_ILGIO_KOEF;

	// jei signalà reikia labai sutrumpinti, gali bûti, kad tiek sutrumpinti nepavyks, ir signalo ilgis bus didesnis. 
	// Tokiu atveju dël visa ko geriau iðskirkime daugiau atminties.
	if (greitis < 60)
		padidintas_koef *= NAUJO_SIGNALO_MASYVO_ILGIO_KOEF;

	return (size_t) (signalo_ilgis * padidintas_koef);
}

/*********************************************************
 * Konteksto sukûrimas ir inicializavimas turi vykti tik ðioje procedûroje, 
 * kad pakeitus konteksto sandarà (pridëjus naujø laukø), 
 * uþtektø pakeisti kodà tik ðioje funkcijoje.
 ********************************************************/
void init_konteksta (struct tkontekstas * kontekstas) {
	kontekstas->fonemos_nr = 0;
	kontekstas->fonemos_pradzia = 0;
	kontekstas->fonemos_pabaiga = 0;
	kontekstas->pirmojo_piko_nr = 0;
	kontekstas->piku_sk = 0;
	kontekstas->greitinimo_koef = 1.0;
	kontekstas->tarpo_tarp_piku_didinimo_koef = 1.0;
	kontekstas->einamasis_postumis = 0;
	kontekstas->einamasis_signalo_nr = 0;
	kontekstas->naujas_signalas = NULL;
	kontekstas->naujo_signalo_masyvo_ilgis = 0;
	//kontekstas->naujo_signalo_ilgis = 0;
	kontekstas->einamasis_naujo_signalo_nr = 0;
	kontekstas->galima_pailginti_naujas_signalas = 0;
	kontekstas->keiciamu_burbulu_sk = 0;
	kontekstas->fonemos_klase = -1;
	kontekstas->keisti_tono_auksti = 0;
}

/*********************************************************
 * Konteksto spausdinimas testavimui.
 ********************************************************/
void spausdinti_konteksta (struct tkontekstas * kontekstas) {
	char pranesimas [2048];
	sprintf (pranesimas, "Kontekstas: [fonemos_nr: %d][fonemos_pav: %s][fonemos_pradzia: %d][fonemos_pabaiga: %d][fonemos_ilgis: %d][pirmojo_piko_nr: %d][paskutiniojo_piko_nr: %d][piku_sk: %d][pirmojo_piko_vieta: %d][paskutiniojo_piko_vieta: %d][einamasis_postumis: %d][einamasis_signalo_nr: %d][naujo_signalo_masyvo_ilgis: %d][einamasis_naujo_signalo_nr: %d][galima_pailginti_naujas_signalas: %d][fonemos_klase: %d][keisti_tono_auksti: %d][keiciamu_burbulu_sk: %d][greitinimo_koef: %.3f][tarpo_tarp_piku_didinimo_koef: %.3f]",
		kontekstas->fonemos_nr, 
		fonemos [kontekstas->fonemos_nr],
		kontekstas->fonemos_pradzia, 
		kontekstas->fonemos_pabaiga, 
		kontekstas->fonemos_pabaiga - kontekstas->fonemos_pradzia,
		kontekstas->pirmojo_piko_nr,
		kontekstas->pirmojo_piko_nr + kontekstas->piku_sk - 1,
		kontekstas->piku_sk,
		(kontekstas->pirmojo_piko_nr<piku_kiekis)?pikai [kontekstas->pirmojo_piko_nr]:-1,
		(kontekstas->pirmojo_piko_nr<piku_kiekis && kontekstas->pirmojo_piko_nr + kontekstas->piku_sk > 0)?pikai [kontekstas->pirmojo_piko_nr + kontekstas->piku_sk - 1]:-1,
		kontekstas->einamasis_postumis,
		kontekstas->einamasis_signalo_nr,
		kontekstas->naujo_signalo_masyvo_ilgis,
		kontekstas->einamasis_naujo_signalo_nr,
		kontekstas->galima_pailginti_naujas_signalas,
		kontekstas->fonemos_klase,
		kontekstas->keisti_tono_auksti,
		kontekstas->keiciamu_burbulu_sk,
		kontekstas->greitinimo_koef,
		kontekstas->tarpo_tarp_piku_didinimo_koef);
	spausdinti_loga (pranesimas);
}

/*********************************************************
Gràþina fonemos klasës numerá pagal fonemos pavadinimo pirmàjà raidæ:
0 - turintys pikø informacijà (skardieji priebalsiai, balsiai, t.y. visi, iðskyrus x, f, p, t, k, s, S, _, r, R, z, Z, H)
1 - neturintys pikø informacijos (duslieji priebalsiai, t.y. x, f, p, t, k, s, S, _)
2 - gali turëti ar neturëti pikø informacijos, todël gali bûti priskirti kuriai nors ið pirmøjø dviejø klasiø - reikia papildomo tikrinimo (z, Z, h),
3 - neaiðku, kà daryti (r, R).
*********************************************************/
int fonemosKlase (struct tkontekstas * kontekstas)
{

	switch (fonemos[kontekstas->fonemos_nr][0]) {

	case 'r':
	case 'R':
		return FONEMU_KLASE_RR;

	case 'x':
	case 'f':
	case 'p':
	case 't':
	case 'k':
	case 's':
	case 'S':
	case '_':
		return FONEMU_KLASE_DUSLIEJI;

	case 'z':
	case 'Z':
	case 'h':
		if (reguliarus_pikai (kontekstas))
			return FONEMU_KLASE_SKARDIEJI;
		else {

			if (debuginam) {
				char pranesimas [1024];
				sprintf (pranesimas, "RateChange.cpp: fonemosKlase(): nereguliarus garsas: %s, nr: %d, piku_sk: %d", 
					fonemos[kontekstas->fonemos_nr], kontekstas->fonemos_nr, kontekstas->piku_sk);
				spausdinti_loga (pranesimas);
			}

			return FONEMU_KLASE_DUSLIEJI;
		}

	default:
		return FONEMU_KLASE_SKARDIEJI;
	}

}

/*********************************************************
 * apskaiciuoti_pirmojo_piko_nr_fonemose
 ********************************************************/
int apskaiciuoti_pirmojo_piko_nr_fonemose ()
{
	// iðskiriame atminties
	pirmojo_piko_nr_fonemose = (int *) malloc ((fonemu_kiekis+1) * sizeof(int));
	if(pirmojo_piko_nr_fonemose == NULL) 
		return ERROR_RATECHANGE_MEMORY_ALLOCATION_FOR_PIK_INFO;
	piku_skaicius_fonemose = (int *) malloc ((fonemu_kiekis+1) * sizeof(int));
	if(pirmojo_piko_nr_fonemose == NULL) 
		return ERROR_RATECHANGE_MEMORY_ALLOCATION_FOR_PIK_INFO;

	// einamosios fonemos pradþia ir pabaiga
	unsigned int fonemos_pradzia = 0;
	unsigned int fonemos_pabaiga = 0;

	// numeris pirmojo piko, esanèio einamosios fonemos pradþioje 
	// (tiksliau, pirmojo piko, nepriklausanèio prieð tai buvusiai fonemai. 
	// Jis gali nepriklausyti ir einamajai, o kuriai nors tolimesnei).
	int pirmojo_piko_nr = 0;

	// kiekvienai fonemai darome ðtai kà:
	for (size_t fonemos_nr = 0; fonemos_nr < fonemu_kiekis; fonemos_nr++) {

		// randame fonemos pabaigà
		fonemos_pabaiga = fonemos_pradzia + fonemu_ilgiai[fonemos_nr];

		// suskaièiuojame, kiek pikø yra tarp pradþios ir pabaigos
		int piku_sk = 0; 
		size_t i = pirmojo_piko_nr;
		while (i < piku_kiekis && pikai[i] < fonemos_pabaiga) 
			i++;
		piku_sk = (int) i - pirmojo_piko_nr;

		// ásimename
		pirmojo_piko_nr_fonemose [fonemos_nr] = pirmojo_piko_nr;
		piku_skaicius_fonemose [fonemos_nr] = piku_sk;

		// atnaujiname fonemos pradþià ir pirmojo piko nr
		fonemos_pradzia = fonemos_pabaiga;
		pirmojo_piko_nr += piku_sk;
	}

	return 0;
}

/*********************************************************
 * pakeiciam fonemos, kurios numeris yra fonemos_nr, greitá ir tono aukðtá.
 * Parametras "greitis" nurodo procentais, kiek pailginti fonemà (pavyzdþiui, 120 reiðkia pailginti 1,2 karto).
 * Parametras "tono_aukscio_pokytis" nurodo procentais, kiek paaukðtinti pagrindiná tonà 
 * (pavyzdþiui, 120 reiðkia paaukðtinti 1,2 karto: jei pagrindinis tonas buvo 100 Hz, pasidarys 120 Hz).
 * Patá naujà signalà áraðo á naujas_signalas masyvà (tiksliau, prie jo prisumuoja).
 * Laikome, kad "naujas_signalas" rodo á prieð tai buvusios (jei buvo) fonemos pabaigà+1.
 *
 * Gràþina naujo signalo ilgá, jei pavyko, ir -1, jei nepavyko (jei masyve naujas_signalas neuþteko vietos).
 ********************************************************/
int change_phoneme_rate_internal (int greitis, int tono_aukscio_pokytis, unsigned int fonemos_nr, 
						 short ** naujas_signalas, size_t * naujo_signalo_masyvo_ilgis,  //20201204 unsigned int
						 int galima_pailginti_naujas_signalas, unsigned int einamasis_naujo_signalo_nr)
{
	if (debuginam) {
		char pranesimas [1024];
		sprintf (pranesimas, "RateChange.dll: RateChange.cpp: change_phoneme_rate_internal(): pradedame doroti fonema '%s\' (nr: %d), greitis %d, tono_aukscio_pokytis %d", fonemos[fonemos_nr], fonemos_nr, greitis, tono_aukscio_pokytis);
		spausdinti_loga (pranesimas);
	}

	//if (debuginam > 10000) {
	//	// spausdinkime pradinës fonemos masyvà á failà
	//	char pranesimas[1024];
	//	sprintf(pranesimas, "1 %d %s", i, sakinys);
	//	spausdinti_short_masyva(pranesimas, signbuf, *signbufsize);
	//}

	// ------------------------- Inicializuojame parametrus --------------------------------- //

	// sukuriame kontekstà
	struct tkontekstas kkontekstas;
	struct tkontekstas * kontekstas = &kkontekstas;
	init_konteksta (kontekstas);

	if (debuginam > 100) {
		spausdinti_loga ((char*)"RateChange.dll: RateChange.cpp: change_phoneme_rate_internal(): sukureme konteksta");
		//spausdinti_konteksta (kontekstas);
	}

	kontekstas->fonemos_nr = fonemos_nr;

	// inicializuojame rezultatø masyvà
	kontekstas->naujas_signalas = *naujas_signalas;
	kontekstas->naujo_signalo_masyvo_ilgis = *naujo_signalo_masyvo_ilgis;
	kontekstas->galima_pailginti_naujas_signalas = galima_pailginti_naujas_signalas;

	// gràþiname rodykles á pradþià
	kontekstas->einamasis_signalo_nr = fonemu_adresai [fonemos_nr];
	kontekstas->einamasis_naujo_signalo_nr = einamasis_naujo_signalo_nr;

	// inicializuojam einamàjá postûmá
	kontekstas->einamasis_postumis = 0;
	
	// einamosios fonemos pradþia ir pabaiga
	kontekstas->fonemos_pradzia = (int) fonemu_adresai [fonemos_nr];
	kontekstas->fonemos_pabaiga = kontekstas->fonemos_pradzia + fonemu_ilgiai[fonemos_nr];

	// numeris pirmojo piko, esanèio einamosios fonemos pradþioje 
	// (tiksliau, pirmojo piko, nepriklausanèio prieð tai buvusiai fonemai. 
	// Jis gali nepriklausyti ir einamajai, o kuriai nors tolimesnei).
	kontekstas->pirmojo_piko_nr = pirmojo_piko_nr_fonemose [fonemos_nr];

	// kiek pikø yra tarp pradþios ir pabaigos
	kontekstas->piku_sk = piku_skaicius_fonemose [fonemos_nr];
	
	// nustatome fonemos klasæ
	kontekstas->fonemos_klase = fonemosKlase (kontekstas);

	// ar keisti tono aukðtá
	kontekstas->keisti_tono_auksti =
		(kontekstas->fonemos_klase == FONEMU_KLASE_SKARDIEJI || kontekstas->fonemos_klase == FONEMU_KLASE_RR)
		&& (tono_aukscio_pokytis != 100)
		&& (kontekstas->piku_sk > 1);

	// nustatome tarpo tarp pikø keitimo koeficientà
	if (kontekstas->keisti_tono_auksti)
		kontekstas->tarpo_tarp_piku_didinimo_koef = 100.0 / tono_aukscio_pokytis;
	else
		kontekstas->tarpo_tarp_piku_didinimo_koef = 1.0;

	// jei r, R, tai greièio nekeièiame (nors tono aukðtá galime keisti), t.y. neatsiþvelgiame á nurodytà greitinimo koeficiento reikðmæ
	// (t.y. jei tono aukðtá keisime, teks keisti ir greitá, bet tik tiek, kad atstatytume fonemos ilgá á buvusá).
	//if (kontekstas->fonemos_klase == FONEMU_KLASE_RR)
	//	greitis = 100;

	// apskaièiuojame reikiamà greitinimo koeficientà pagal pateiktus greitinimo ir tono keitimo koeficientus
	//kontekstas->greitinimo_koef = (((double)greitis) / 100) / kontekstas->tarpo_tarp_piku_didinimo_koef;
		
	// apskaièiuojame reikiamà greitinimo koeficientà pagal pateiktus greitinimo ir tono keitimo koeficientus
	if (kontekstas->fonemos_klase == FONEMU_KLASE_RR)
		// jei r, R, tai greièio nekeièiame (nors tono aukðtá galime keisti), t.y. neatsiþvelgiame á nurodytà greitinimo koeficiento reikðmæ
		if (kontekstas->tarpo_tarp_piku_didinimo_koef < 1)
			// jei tono aukðtá didinsime, teks keisti ir greitá, bet tik tiek, kad atstatytume fonemos ilgá á buvusá
			kontekstas->greitinimo_koef = 1 / kontekstas->tarpo_tarp_piku_didinimo_koef;
		else
			// jei tono aukðtá maþinsime (ar jo nekeisime), greièio nekeisime (neatstatysime fonemos ilgio á buvusá)
			// (t.y. jei fonemos r, R tono aukðtá maþinsime, tai jos ilgis padidës)
			kontekstas->greitinimo_koef = 1;
	else
		// skardþiosioms fonemoms
		kontekstas->greitinimo_koef = (((double)greitis) / 100) / kontekstas->tarpo_tarp_piku_didinimo_koef;

	// ------------------------- Euristika --------------------------------- //

	// keièiamø (ðalinamø ar dubliuojamø) burbulø skaièius
	kontekstas->keiciamu_burbulu_sk = 0;
	
	if (debuginam) {
		spausdinti_loga ((char*)"RateChange.dll: RateChange.cpp: change_phoneme_rate_internal(): inicializavome parametrus");
		spausdinti_konteksta (kontekstas);
	}

	// euristiðkai parinkti burbuliukus iðmetimui
	euristika (kontekstas);
	
	if (debuginam > 100) {
		spausdinti_loga ((char*)"RateChange.dll: RateChange.cpp: change_phoneme_rate_internal(): pritaikeme euristika");
		spausdinti_konteksta (kontekstas);
		spausdinti_burbulus (kontekstas->burbulai, kontekstas->keiciamu_burbulu_sk);
	}

	// ------------------------- Apdorojame signalà --------------------------------- //

	// jei pavyko == -1, viskà stabdome, nes nepavyko iðskirti atminties
	int pavyko = 0;

	// tono aukðèio keitimas: apdorojame pusæ pirmo burbulo, iðlendanèià á prieð tai buvusià fonemà
	if (kontekstas->keisti_tono_auksti)
		pavyko = kopijuoti_signala_pradzioj (kontekstas);
	// jei nepavyko, viskà stabdome
	if (pavyko == -1)
		return DIDELIS_NEIGIAMAS_KLAIDOS_KODAS;

	if (debuginam > 100) {
		spausdinti_loga ((char*)"RateChange.dll: RateChange.cpp: change_phoneme_rate_internal(): nukopijavome signala, esanti ant fonemos pradzios ribos (jei keiciame tono auksti)");
		spausdinti_konteksta (kontekstas);
	}

	// iðmesti parinktus burbuliukus, perskaièiuoti masyvus
	if (kontekstas->greitinimo_koef<1)
		pavyko = trumpinti_fonema (kontekstas);
	else
		pavyko = ilginti_fonema (kontekstas);
	// jei nepavyko, viskà stabdome
	if (pavyko == -1) {
		return DIDELIS_NEIGIAMAS_KLAIDOS_KODAS; 
	}

	if (debuginam > 100) {
		spausdinti_loga ((char*)"RateChange.dll: RateChange.cpp: change_phoneme_rate_internal(): sutrumpinome/pailginome fonema");
		spausdinti_konteksta (kontekstas);
	}

	// nustatome, iki kiek kopijuojame signalà
	int iki = 0;
	if (kontekstas->keisti_tono_auksti)
		// tono aukðèio keitimas: kopijuosime iki paskutinio piko
		iki = pikai [kontekstas->pirmojo_piko_nr + kontekstas->piku_sk -1];
	else
		// jei nekeisime tono aukðèio, kopijuosime iki fonemos pabaigos
		iki = kontekstas->fonemos_pabaiga;

	// pabaigiame nukopijuoti signalo masyvà
	// jei yra nenukopijuoto signalo
	// nukopijuojame (prisumuojame) signalo duomenis iki signalo pabaigos
	// (negalime kopijuoti su memcpy, nes prarasime jau ten esanèià informacijà).
	// Tuo paèiu ir atnaujiname einamàsias signalø masyvø reikðmes.
	pavyko = kopijuoti_signala (iki, kontekstas);
	// jei nepavyko, viskà stabdome
	if (pavyko == -1) {
		return DIDELIS_NEIGIAMAS_KLAIDOS_KODAS; 
	}

	if (debuginam > 100) {
		spausdinti_loga ((char*)"RateChange.dll: RateChange.cpp: change_phoneme_rate_internal(): nukopijavome likusi signala");
		spausdinti_konteksta (kontekstas);
	}

	// tono aukðèio keitimas: apdorojame pusæ paskutinio burbulo, iðlendanèià á po to einanèià fonemà
	if (kontekstas->keisti_tono_auksti)
		pavyko = kopijuoti_signala_pabaigoj (kontekstas);
	// jei nepavyko, viskà stabdome
	if (pavyko == -1)
		return DIDELIS_NEIGIAMAS_KLAIDOS_KODAS;

	if (debuginam > 100) {
		spausdinti_loga ((char*)"RateChange.dll: RateChange.cpp: change_phoneme_rate_internal(): nukopijavome signala, esanti ant fonemos pabaigos ribos (jei keiciame tono auksti)");
		spausdinti_konteksta (kontekstas);
	}

	// apskaièiuojame naujàjá fonemos ilgá
	int naujas_fonemos_ilgis = fonemu_ilgiai[fonemos_nr] + kontekstas->einamasis_postumis;

	// atnaujiname reikðmes
	*naujas_signalas = kontekstas->naujas_signalas;
	*naujo_signalo_masyvo_ilgis = kontekstas->naujo_signalo_masyvo_ilgis;

	if (debuginam) {
		char pranesimas [1024];
		sprintf (pranesimas, "RateChange.dll: RateChange.cpp: change_phoneme_rate_internal(): sekmingai apdorota fonema '%s\' (nr: %d), buves ilgis=%d, naujas ilgis=%d, faktinis pailgejimas=%.3f", 
			fonemos[fonemos_nr], fonemos_nr, kontekstas->fonemos_pabaiga - kontekstas->fonemos_pradzia, naujas_fonemos_ilgis, 
			(double)naujas_fonemos_ilgis/(kontekstas->fonemos_pabaiga - kontekstas->fonemos_pradzia));
		spausdinti_loga (pranesimas);
		spausdinti_konteksta (kontekstas);
	}

	return naujas_fonemos_ilgis;
}

/*********************************************************
 * Nuskaitom BD is failu ir pakeiciam kalbejimo greiti
 ********************************************************/
int change_DB_rate (char *katVardas, int greitis, int tono_aukscio_pokytis, char dbfv1[][4], 
					int *dbilg1, long *dbadr1, short ** wholeinputt1)
{
	clock_t begin_time,end_time;

	if (debuginam) {
		char pranesimas [1024];
		sprintf (pranesimas, "RateChange.cpp: change_DB_rate(): pradzia. Katalogas: %s, koef=%d", katVardas, greitis);
		spausdinti_loga (pranesimas);
		begin_time = clock ();
	}

	// ------------------------- Nuskaitome duomenis --------------------------------- //

	// apsitvarkome

	atlaisvinti_atminti_ir_inicializuoti ();

	// pasiruoðimas duomenø nuskaitymui

	// sudarome garsø duomenø bazës failo pavadinimà
	strcpy (signalo_failo_pavadinimas, katVardas);
	strcat (signalo_failo_pavadinimas, "db.raw");

	// sudarome fonemø failo pavadinimà
	strcpy(fonemu_failo_pavadinimas, katVardas);
	strcat(fonemu_failo_pavadinimas, "db_fon_weights.txt");

	// sudarome pikø failo pavadinimà
	strcpy(piku_failo_pavadinimas, katVardas);
	strcat(piku_failo_pavadinimas, "db_pik.txt");

	// nuskaitome duomenis is failu (uþpildome duomenø masyvus)
	int a = nuskaityti_duomenis();
	if (a < 0) return a;

	if (debuginam) {
		end_time = clock ();
		char pranesimas [1024];
		sprintf (pranesimas, "RateChange.cpp: change_DB_rate(): duomenys nuskaityti per %.3f sec", ((double)(end_time-begin_time))/CLOCKS_PER_SEC);
		spausdinti_loga (pranesimas);
		begin_time = clock ();
	}

	// ------------------------- Inicializuojame parametrus --------------------------------- //

	// apskaièiuojame pagalbinius masyvus darbui su pikais
	a = apskaiciuoti_pirmojo_piko_nr_fonemose ();
	if (a < 0) return a;

	// sukuriame kontekstà
	//struct tkontekstas kkontekstas;
	//struct tkontekstas * kontekstas = &kkontekstas;
	//init_konteksta (kontekstas);

	// nustatome greitinimo koeficientà
	//kontekstas->greitinimo_koef = ((double)greitis) / 100;

	if (debuginam) {
		char pranesimas [1024];
		sprintf (pranesimas, "RateChange.cpp: change_DB_rate(): Greitinimo koeficientas: %d", greitis);
		spausdinti_loga (pranesimas);
	}

	// ávertiname pailginto signalo masyvo ilgá
	size_t naujo_signalo_masyvo_ilgis = rekomenduoti_naujo_signalo_masyvo_ilgi (greitis, tono_aukscio_pokytis);

	// paþymime, kad masyvà naujas_signalas galima ilginti, jei netyèia jam iðskirta per maþai atminties
	int galima_pailginti_naujas_signalas = 1;

	if (debuginam) {
		char pranesimas [1024];
		sprintf (pranesimas, "RateChange.cpp: change_DB_rate(): signalo ilgis: %d, naujo_signalo_masyvo_ilgis: %d", 
			signalo_ilgis, naujo_signalo_masyvo_ilgis);
		spausdinti_loga (pranesimas);
	}

	// inicializuojame rezultatø masyvus

	short * naujas_signalas = (short *) calloc (naujo_signalo_masyvo_ilgis, sizeof(short)); // kad uþpildytø nuliais
	if (naujas_signalas == NULL) {
		return ERROR_RATECHANGE_MEMORY_ALLOCATION_FOR_CHANGED_RATE_DB; 
	}

	// susikuriame ir uþpildome pagalbiná fonemø adresø masyvà
	
	fonemu_adresai = (long *) calloc (fonemu_kiekis+1, sizeof(long));
	if (fonemu_adresai == NULL) {
		return ERROR_RATECHANGE_MEMORY_ALLOCATION_FOR_CHANGED_RATE_DB; 
	}

	unsigned int l;
	fonemu_adresai[0]=0;
	for(l=0; l<fonemu_kiekis; l++) {
		fonemu_adresai[l+1] = fonemu_adresai[l] + fonemu_ilgiai[l];
	}

	// nauji_fonemu_ilgiai

	nauji_fonemu_ilgiai = dbilg1;

	if (debuginam) {
		spausdinti_loga ((char*)"RateChange.cpp: change_DB_rate(): pasiruoseme greicio keitimui");
	}

	// ------------------------- Skaièiuojame --------------------------------- //

	size_t einamasis_naujo_signalo_nr = 0;

	for (size_t fonemos_nr = 0; fonemos_nr < fonemu_kiekis; fonemos_nr++) {
		
		// kiekvienai fonemai kvieèiame change_phoneme_rate_internal() funkcijà
		int naujas_fonemos_ilgis = change_phoneme_rate_internal (
			greitis, tono_aukscio_pokytis, fonemos_nr, 
			&naujas_signalas, &naujo_signalo_masyvo_ilgis, 
			galima_pailginti_naujas_signalas, einamasis_naujo_signalo_nr);
		// jei nepavyko, viskà stabdome
		if (naujas_fonemos_ilgis == DIDELIS_NEIGIAMAS_KLAIDOS_KODAS)
			return ERROR_RATECHANGE_MEMORY_ALLOCATION_FOR_CHANGED_RATE_DB;

		// perskaièiuojame fonemø ilgiø masyvà
		nauji_fonemu_ilgiai[fonemos_nr] = naujas_fonemos_ilgis;

		// atnaujiname einamasis_naujo_signalo_nr
		einamasis_naujo_signalo_nr += naujas_fonemos_ilgis;
		
	}

	if (debuginam) {
		end_time = clock ();
		char pranesimas [1024];
		sprintf (pranesimas, "RateChange.cpp: change_DB_rate(): greicio keitimas baigtas per %.3f sec\nFaktinis ilginimo koeficientas = %.3f", ((double)(end_time-begin_time))/CLOCKS_PER_SEC, (double)einamasis_naujo_signalo_nr/signalo_ilgis);
		spausdinti_loga (pranesimas);
		begin_time = clock ();
	}

	// ------------------------- pritaikome rezultatus LithUSS'ui --------------------------------- //

	*wholeinputt1 = naujas_signalas;

	nauji_fonemu_ilgiai[fonemu_kiekis]=0;

	dbadr1[0]=0;
	for(l=0; l<fonemu_kiekis; l++) {
		dbadr1[l+1] = dbadr1[l] + nauji_fonemu_ilgiai[l];
		dbfv1[l][0] = fonemos[l][0];
		dbfv1[l][1] = fonemos[l][1];
		if (dbfv1[l][1] == 0) dbfv1[l][2] = 0; else dbfv1[l][2] = fonemos[l][2];
		if (dbfv1[l][2] == 0) dbfv1[l][3] = 0; else dbfv1[l][3] = fonemos[l][3];
	}

	if (debuginam) {
		spausdinti_loga ((char*)"change_DB_rate: rezultatai paruosti");
	}

	// apsitvarkome
	atlaisvinti_atminti_ir_inicializuoti ();
	// turime atlaisvinti atminti ðioje funkcijoje, nes èia sukûrëme, o dinaminiu reþimu visai nereikia atlaisvinti
	if(fonemu_adresai != NULL) {free(fonemu_adresai); fonemu_adresai=NULL;}
	
	if (debuginam) {
		end_time = clock ();
		char pranesimas [1024];
		sprintf (pranesimas, "RateChange.cpp: change_DB_rate(): pabaiga per %.3f sec", ((double)(end_time-begin_time))/CLOCKS_PER_SEC);
		spausdinti_loga (pranesimas);
	}

	return NO_ERR;
}

/*********************************************************
 * Nuskaitom BD is failu
 ********************************************************/
int initRateChange (char *katVardas, char dbfv1[][4], int *dbilg1, long *dbadr1, short ** wholeinput1)
{
	clock_t begin_time, end_time;

	if (debuginam) {
		char pranesimas [1024];
		sprintf (pranesimas, "RateChange.cpp: initRateChange(): pradzia. Katalogas: %s", katVardas);
		spausdinti_loga (pranesimas);
		begin_time = clock ();
	}

	// apsitvarkome
	atlaisvinti_atminti_ir_inicializuoti ();
	
	// pasiruoðimas duomenø nuskaitymui

	// sudarome garsø duomenø bazës failo pavadinimà
	strcpy (signalo_failo_pavadinimas, katVardas);
	strcat (signalo_failo_pavadinimas, "db.raw");

	// sudarome fonemø failo pavadinimà
	strcpy(fonemu_failo_pavadinimas, katVardas);
	strcat(fonemu_failo_pavadinimas, "db_fon_weights.txt");

	// sudarome pikø failo pavadinimà
	strcpy(piku_failo_pavadinimas, katVardas);
	strcat(piku_failo_pavadinimas, "db_pik.txt");

	// nuskaitome duomenis is failu (uþpildome duomenø masyvus)
	int a = nuskaityti_duomenis();
	if (a < 0) return a;

	if (debuginam) {
		end_time = clock ();
		char pranesimas [1024];
		sprintf (pranesimas, "RateChange.cpp: initRateChange(): duomenys nuskaityti per %.3f sec", ((double)(end_time-begin_time))/CLOCKS_PER_SEC);
		spausdinti_loga (pranesimas);
		begin_time = clock ();
	}

	// apskaièiuojame pagalbinius masyvus darbui su pikais
	a = apskaiciuoti_pirmojo_piko_nr_fonemose ();
	if (a < 0) return a;

	// ásimename fonemø pradþiø indeksø masyvà. 
	// Já naudosime dinaminiam greièio keitimui.
	// (Gal pasidaryti kopijà?)
	fonemu_adresai = dbadr1;

	// pritaikome duomenis Pijaus LithUSS'ui

	*wholeinput1 = signalas;

	dbilg1[fonemu_kiekis]=0;

	unsigned int l;
	fonemu_adresai[0]=0;
	for(l=0; l<fonemu_kiekis; l++) {
		dbilg1[l] = fonemu_ilgiai[l];
		fonemu_adresai[l+1] = fonemu_adresai[l] + fonemu_ilgiai[l];
		dbfv1[l][0] = fonemos[l][0];
		dbfv1[l][1] = fonemos[l][1];
		if (dbfv1[l][1] == 0) dbfv1[l][2] = 0; else dbfv1[l][2] = fonemos[l][2];
		if (dbfv1[l][2] == 0) dbfv1[l][3] = 0; else dbfv1[l][3] = fonemos[l][3];
	}

	if (debuginam) {
		end_time = clock ();
		char pranesimas [1024];
		sprintf (pranesimas, "RateChange.cpp: initRateChange(): pabaiga per %.3f sec", ((double)(end_time-begin_time))/CLOCKS_PER_SEC);
		spausdinti_loga (pranesimas);
	}
	return NO_ERR;
}

/*********************************************************
 * pakeiciam fonemos, kurios numeris yra fonemos_nr, greitá ir tono aukðtá.
 * Parametras "greitis" nurodo procentais, kiek pailginti fonemà (pavyzdþiui, 120 reiðkia pailginti 1,2 karto).
 * Parametras "tono_aukscio_pokytis" nurodo procentais, kiek paaukðtinti pagrindiná tonà 
 * (pavyzdþiui, 120 reiðkia paaukðtinti 1,2 karto: jei pagrindinis tonas buvo 100 Hz, pasidarys 120 Hz).
 * Patá naujà signalà áraðo á naujas_signalas masyvà (tiksliau, prie jo prisumuoja).
 * Laikome, kad "naujas_signalas" rodo á prieð tai buvusios (jei buvo) fonemos pabaigà+1.
 *
 * Gràþina naujo signalo ilgá, jei pavyko, ir -1, jei nepavyko (jei masyve naujas_signalas neuþteko vietos).
 ********************************************************/
int change_phoneme_rate (int greitis, int tono_aukscio_pokytis, unsigned int fonemos_nr, 
						 short * naujas_signalas, size_t naujo_signalo_masyvo_ilgis) //20201204 unsigned int
{
	int galima_pailginti_naujas_signalas = 0;
	unsigned int einamasis_naujo_signalo_nr = 0;
	int naujas_fonemos_ilgis = change_phoneme_rate_internal (greitis, tono_aukscio_pokytis, fonemos_nr, &naujas_signalas, &naujo_signalo_masyvo_ilgis, 
		galima_pailginti_naujas_signalas, einamasis_naujo_signalo_nr);
	// jei nepavyko, viskà stabdome
	if (naujas_fonemos_ilgis == DIDELIS_NEIGIAMAS_KLAIDOS_KODAS)
		return ERROR_RATECHANGE_SIGNAL_BUFFER_OVERFLOW;
	else
		return naujas_fonemos_ilgis;
}