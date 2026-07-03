///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Projektas LIEPA (https://liepa.raðtija.lt)
// Sintezatoriaus komponentas TextNormalization.dll
// Failas TextNormalization.cpp
// Autorius dr. Tomas Anbinderis
// 2015 09 16
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//#include "stdafx.h"
#include "stringWithLetterPosition.h"
#include "stdlib.h"

#include "LithUSS_Error.h"
#include "unicode_emoji.h"

#define VardL 0
#define KilmL 1
#define NaudL 2
#define GalL 3
#define InagL 4
#define VyrG 0
#define MotG 1

char ***abbLists;
char ***abbListsSubstitutions;
//unsigned short **abbListsIsWithSep; //20200410
int *abbSizes;
int totalFileBuffers = 0;

void unloadTextNormalization();

/*BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	if (ul_reason_for_call == DLL_PROCESS_DETACH && totalFileBuffers > 0)
	{
		unloadTextNormalization();
	}

    return TRUE;
}*/

void unloadTextNormalization()
{
	if (totalFileBuffers > 0)
	{
		for(int i=0; i<totalFileBuffers; i++)
		{
		   for(int j=0; j<2048; j++)
		   {
				delete[] abbLists[i][j];
				delete[] abbListsSubstitutions[i][j];
		   }
		   delete[] abbLists[i];
		   delete[] abbListsSubstitutions[i];
//		   delete[] abbListsIsWithSep[i]; //20200410
		}
		delete[] abbLists;
		delete[] abbListsSubstitutions;
//		delete[] abbListsIsWithSep; //20200410
		delete[] abbSizes;
	}
}

#define MAX_RULES 4*1024
string rulesArray[MAX_RULES];
int totalRules;

char* SimbPavad(char Simb)
{
	switch (Simb)
	{
		case '!' : return (char*)"ÐAUKTU`KAS";
		case '\"': return (char*)"KABU`TËS";
		case '#' : return (char*)"NU`MERIS";
		case '$' : return (char*)"DO^LERIS";
		case '%' : return (char*)"PRO`CENTAS";
		case '&' : return (char*)"A^MPERSENDAS";
		case '\'': return (char*)"APOSTRO`FAS";
		case '(' : return (char*)"SKLIAU~STAI ATSIDA~RO";
		case ')' : return (char*)"SKLIAU~STAI UÞSIDA~RO";
		case '*' : return (char*)"ÞVAIGÞDU`TË";
		case '+' : return (char*)"PLIU`S";
		case ',' : return (char*)"KABLE~LIS";
		case '-' : return (char*)"MI`NUS";
		case '.' : return (char*)"TA~ÐKAS";
		case '/' : return (char*)"ÁÞAMBU`S";
		case '0' : return (char*)"NU`LIS";
		case '1' : return (char*)"VI^ENAS";
		case '2' : return (char*)"DU`";
		case '3' : return (char*)"TRY~S";
		case '4' : return (char*)"KETURI`";
		case '5' : return (char*)"PENKI`";
		case '6' : return (char*)"ÐEÐI`";
		case '7' : return (char*)"SEPTYNI`";
		case '8' : return (char*)"AÐTUONI`";
		case '9' : return (char*)"DEVYNI`";
		case ':' : return (char*)"DVI`TAÐKIS";
		case ';' : return (char*)"KABLIA~TAÐKIS";
		case '<' : return (char*)"MAÞIAU~";
		case '=' : return (char*)"LY^GU";
		case '>' : return (char*)"DAUGIAU~";
		case '?' : return (char*)"KLAUSTU`KAS";
		case '@' : return (char*)"ETA`";
		case 'A' : return (char*)"À~";
		case 'B' : return (char*)"BË~";
		case 'C' : return (char*)"CË~";
		case 'D' : return (char*)"DË~";
		case 'E' : return (char*)"Æ~";
		case 'F' : return (char*)"E`F";
		case 'G' : return (char*)"GË~";
		case 'H' : return (char*)"HÀ~";
		case 'I' : return (char*)"I`";
		case 'J' : return (char*)"JO`T";
		case 'K' : return (char*)"KÀ~";
		case 'L' : return (char*)"E`L";
		case 'M' : return (char*)"E`M";
		case 'N' : return (char*)"E`N";
		case 'O' : return (char*)"O~";
		case 'P' : return (char*)"PË~";
		case 'Q' : return (char*)"KÛ~";
		case 'R' : return (char*)"E`R";
		case 'S' : return (char*)"E`S";
		case 'T' : return (char*)"TË~";
		case 'U' : return (char*)"U`";
		case 'V' : return (char*)"VË~";
		case 'W' : return (char*)"DVI`GUBA VË~";
		case 'X' : return (char*)"I`KS";
		case 'Y' : return (char*)"Y~ ILGO^JI";
		case 'Z' : return (char*)"ZË~";
		case '[' : return (char*)"LAUÞTI`NIAI ATSIDA~RO";
		case '\\': return (char*)"A~TVIRKÐÈIAS ÁÞAMBU`S";
		case ']' : return (char*)"LAUÞTI`NIAI UÞSIDA~RO";
		case '^' : return (char*)"STOGE~LIS";
		case '_' : return (char*)"PABRAUKI`MAS";
		case '`' : return (char*)"KIR~TIS";
		case 'a' : return (char*)"À~";
		case 'b' : return (char*)"BË~";
		case 'c' : return (char*)"CË~";
		case 'd' : return (char*)"DË~";
		case 'e' : return (char*)"Æ~";
		case 'f' : return (char*)"E`F";
		case 'g' : return (char*)"GË~";
		case 'h' : return (char*)"HÀ~";
		case 'i' : return (char*)"I`";
		case 'j' : return (char*)"JO`T";
		case 'k' : return (char*)"KÀ~";
		case 'l' : return (char*)"E`L";
		case 'm' : return (char*)"E`M";
		case 'n' : return (char*)"E`N";
		case 'o' : return (char*)"O~";
		case 'p' : return (char*)"PË~";
		case 'q' : return (char*)"KÛ~";
		case 'r' : return (char*)"E`R";
		case 's' : return (char*)"E`S";
		case 't' : return (char*)"TË~";
		case 'u' : return (char*)"U`";
		case 'v' : return (char*)"VË~";
		case 'w' : return (char*)"DVI`GUBA VË~";
		case 'x' : return (char*)"I`KS";
		case 'y' : return (char*)"Y~ ILGO^JI";
		case 'z' : return (char*)"ZË~";
		case '{' : return (char*)"RIESTI`NIAI ATSIDA~RO";
		case '|' : return (char*)"VERTIKA~LË";
		case '}' : return (char*)"RIESTI`NIAI UÞSIDA~RO";
		case '~' : return (char*)"TIL~DË";
		case 'à' : return (char*)"À~ NO^SINË";
		case 'è' : return (char*)"ÈË~";
		case 'æ' : return (char*)"Æ~ NO^SINË";
		case 'ë' : return (char*)"Ë~";
		case 'á' : return (char*)"Y~ NO^SINË";
		case 'ð' : return (char*)"E`Ð";
		case 'ø' : return (char*)"Û~ NO^SINË";
		case 'û' : return (char*)"Û~ ILGO^JI";
		case 'þ' : return (char*)"ÞË~";
		case 'À' : return (char*)"À~ NO^SINË";
		case 'È' : return (char*)"ÈË~";
		case 'Æ' : return (char*)"Æ~ NO^SINË";
		case 'Ë' : return (char*)"Ë~";
		case 'Á' : return (char*)"Y~ NO^SINË";
		case 'Ð' : return (char*)"E`Ð";
		case 'Ø' : return (char*)"Û~ NO^SINË";
		case 'Û' : return (char*)"Û~ ILGO^JI";
		case 'Þ' : return (char*)"ÞË~";
		case '\x80' : return (char*)"EU~RAS";
		case '\x84' : return (char*)"KABU`TËS ATSIDA~RO";
		case '\x8B' : return (char*)"LAUÞTI`NËS ATSIDA~RO";
		case '\x93' : return (char*)"KABU`TËS UÞSIDA~RO";
		case '\x96' : return (char*)"BRÛKÐNY~S";
		case '\x97' : return (char*)"I`LGAS BRÛKÐNY~S";
		case '\x9B' : return (char*)"LAUÞTI`NËS UÞSIDA~RO";
		case '\xA2' : return (char*)"CEN~TAS";		 //¢
		case '\xA3' : return (char*)"SVA~RAS";		 //£
		case '\xA4' : return (char*)"VALIUTA`";	 //¤
		case '\xA5' : return (char*)"JENA`";
		case '\xA6' : return (char*)"VERTIKA~LË SU TARPELIU`"; //¦
		case '\xA7' : return (char*)"PARAGRA~FAS";	 //§
		case '\xA9' : return (char*)"A^UTORIØ TE^ISËS"; //©
		case '\xAB' : return (char*)"DVI`GUBOS LAUÞTI`NËS ATSIDA~RO";
		case '\xAE' : return (char*)"REGISTRU^OTA"; //®
		case '\xB0' : return (char*)"LA^IPSNIS";	 //°
		case '\xB1' : return (char*)"PLIU`S MI`NUS"; //±
		case '\xB6' : return (char*)"PASTRA^IPA";
		case '\xBB' : return (char*)"DVI`GUBOS LAUÞTI`NËS UÞSIDA~RO";
		case '\xBC' : return (char*)"VIENA` KETVIRTO^JI";	//¼
		case '\xBD' : return (char*)"VIENA` ANTRO^JI";		//½
		case '\xBE' : return (char*)"TRY~S KETVIR~TOSIOS"; //¾
		case '\xD7' : return (char*)"DA^UGINTI";	 //×
		case '\xF7' : return (char*)"DALI`NTI";	 //÷

		default  : return (char*)"";
	}
}

char* Skaitmuo(char Sk, int linksnis, int gimine)
{
if(gimine == VyrG)
  {
  if(linksnis == VardL) 
	switch (Sk)
    {
      case '0' : return (char*)" NU`LIS";
      case '1' : return (char*)" VI^ENAS";
      case '2' : return (char*)" DU`";
      case '3' : return (char*)" TRY~S";
      case '4' : return (char*)" KETURI`";
      case '5' : return (char*)" PENKI`";
      case '6' : return (char*)" ÐEÐI`";
      case '7' : return (char*)" SEPTYNI`";
      case '8' : return (char*)" AÐTUONI`";
      case '9' : return (char*)" DEVYNI`";
      default : return (char*)"";
    }
  else if(linksnis == KilmL) 
	switch (Sk)
    {
      case '0' : return (char*)" NU`LIO";
      case '1' : return (char*)" VI^ENO";
      case '2' : return (char*)" DVIEJØ~";
      case '3' : return (char*)" TRIJØ~";
      case '4' : return (char*)" KETURIØ~";
      case '5' : return (char*)" PENKIØ~";
      case '6' : return (char*)" ÐEÐIØ~";
      case '7' : return (char*)" SEPTYNIØ~";
      case '8' : return (char*)" AÐTUONIØ~";
      case '9' : return (char*)" DEVYNIØ~";
      default : return (char*)"";
    }
  else if(linksnis == NaudL) 
	switch (Sk)
    {
      case '0' : return (char*)" NU`LIUI";
      case '1' : return (char*)" VIENA^M";
      case '2' : return (char*)" DVI^EM";
      case '3' : return (char*)" TRI`MS";
      case '4' : return (char*)" KETURI^EMS";
      case '5' : return (char*)" PENKI^EMS";
      case '6' : return (char*)" ÐEÐI^EMS";
      case '7' : return (char*)" SEPTYNI^EMS";
      case '8' : return (char*)" AÐTUONI^MS";
      case '9' : return (char*)" DEVYNI^EMS";
      default : return (char*)"";
    }
  else if(linksnis == GalL) 
	switch (Sk)
    {
      case '0' : return (char*)" NU`LÁ";
      case '1' : return (char*)" VI^ENÀ";
      case '2' : return (char*)" DU`";
      case '3' : return (char*)" TRI`S";
      case '4' : return (char*)" KE~TURIS";
      case '5' : return (char*)" PENKI`S";
      case '6' : return (char*)" ÐEÐI`S";
      case '7' : return (char*)" SEPTY^NIS";
      case '8' : return (char*)" AÐTU^ONIS";
      case '9' : return (char*)" DEVY^NIS";
      default : return (char*)"";
    }
  else if(linksnis == InagL) 
	switch (Sk)
    {
      case '0' : return (char*)" NULIU`";
      case '1' : return (char*)" VI^ENU";
      case '2' : return (char*)" DVIE~M";
      case '3' : return (char*)" TRIMI`S";
      case '4' : return (char*)" KETURIAI~S";
      case '5' : return (char*)" PENKIAI~S";
      case '6' : return (char*)" ÐEÐIAI~S";
      case '7' : return (char*)" SEPTYNIAI~S";
      case '8' : return (char*)" AÐTUONIAI~S";
      case '9' : return (char*)" DEVYNIAI~S";
      default : return (char*)"";
    }
  }
else if(gimine == MotG)
  {
  if(linksnis == VardL) 
	switch (Sk)
    {
      case '0' : return (char*)" NU`LIS";
      case '1' : return (char*)" VIENA`";
      case '2' : return (char*)" DVI`";
      case '3' : return (char*)" TRY~S";
      case '4' : return (char*)" KE~TURIOS";
      case '5' : return (char*)" PEN~KIOS";
      case '6' : return (char*)" ÐE~ÐIOS";
      case '7' : return (char*)" SEPTY^NIOS";
      case '8' : return (char*)" AÐTU^ONIOS";
      case '9' : return (char*)" DEVY^NIOS";
      default : return (char*)"";
    }
  else if(linksnis == KilmL) 
	switch (Sk)
    {
      case '0' : return (char*)" NU`LIO";
      case '1' : return (char*)" VIENO~S";
      case '2' : return (char*)" DVIEJØ~";
      case '3' : return (char*)" TRIJØ~";
      case '4' : return (char*)" KETURIØ~";
      case '5' : return (char*)" PENKIØ~";
      case '6' : return (char*)" ÐEÐIØ~";
      case '7' : return (char*)" SEPTYNIØ~";
      case '8' : return (char*)" AÐTUONIØ~";
      case '9' : return (char*)" DEVYNIØ~";
      default : return (char*)"";
    }
  else if(linksnis == NaudL) 
	switch (Sk)
    {
      case '0' : return (char*)" NU`LIUI";
      case '1' : return (char*)" VI^ENAI";
      case '2' : return (char*)" DVI^EM";
      case '3' : return (char*)" TRI`MS";
      case '4' : return (char*)" KETURIO^MS";
      case '5' : return (char*)" PENKIO^MS";
      case '6' : return (char*)" ÐEÐIO^MS";
      case '7' : return (char*)" SEPTYNIO^MS";
      case '8' : return (char*)" AÐTUONIO^MS";
      case '9' : return (char*)" DEVYNIO^MS";
      default : return (char*)"";
    }
  else if(linksnis == GalL) 
	switch (Sk)
    {
      case '0' : return (char*)" NU`LÁ";
      case '1' : return (char*)" VI^ENÀ";
      case '2' : return (char*)" DVI`";
      case '3' : return (char*)" TRI`S";
      case '4' : return (char*)" KE~TURIAS";
      case '5' : return (char*)" PENKIA`S";
      case '6' : return (char*)" ÐEÐIA`S";
      case '7' : return (char*)" SEPTY^NIAS";
      case '8' : return (char*)" AÐTU^ONIAS";
      case '9' : return (char*)" DEVY^NIAS";
      default : return (char*)"";
    }
  else if(linksnis == InagL) 
	switch (Sk)
    {
      case '0' : return (char*)" NULIU`";
      case '1' : return (char*)" VI^ENA";
      case '2' : return (char*)" DVIE~M";
      case '3' : return (char*)" TRIMI`S";
      case '4' : return (char*)" KETURIOMI`S";
      case '5' : return (char*)" PENKIOMI`S";
      case '6' : return (char*)" ÐEÐIOMI`S";
      case '7' : return (char*)" SEPTYNIOMI`S";
      case '8' : return (char*)" AÐTUONIOMI`S";
      case '9' : return (char*)" DEVYNIOMI`S";
      default : return (char*)"";
    }
  }
return (char*)"";
}

char* Niolika(char Sk, int linksnis)
{
  if((linksnis == VardL) || (linksnis == GalL) || (linksnis == InagL)) 
	switch (Sk)
    {
      case '0' : return (char*)" DE~ÐIMT"; //GalL DE~ÐIMTÁ ??? 
      case '1' : return (char*)" VIENU^OLIKA";
      case '2' : return (char*)" DVY^LIKA";
      case '3' : return (char*)" TRY^LIKA";
      case '4' : return (char*)" KETURIO^LIKA";
      case '5' : return (char*)" PENKIO^LIKA";
      case '6' : return (char*)" ÐEÐIO^LIKA";
      case '7' : return (char*)" SEPTYNIO^LIKA";
      case '8' : return (char*)" AÐTUONIO^LIKA";
      case '9' : return (char*)" DEVYNIO^LIKA";
    }
  else if(linksnis == KilmL) 
	switch (Sk)
    {
      case '0' : return (char*)" DEÐIMTIE~S";
      case '1' : return (char*)" VIENU^OLIKOS";
      case '2' : return (char*)" DVY^LIKOS";
      case '3' : return (char*)" TRY^LIKOS";
      case '4' : return (char*)" KETURIO^LIKOS";
      case '5' : return (char*)" PENKIO^LIKOS";
      case '6' : return (char*)" ÐEÐIO^LIKOS";
      case '7' : return (char*)" SEPTYNIO^LIKOS";
      case '8' : return (char*)" AÐTUONIO^LIKOS";
      case '9' : return (char*)" DEVYNIO^LIKOS";
    }
  else if(linksnis == NaudL) 
	switch (Sk)
    {
      case '0' : return (char*)" DE~ÐIMÈIAI";
      case '1' : return (char*)" VIENU^OLIKAI";
      case '2' : return (char*)" DVY^LIKAI";
      case '3' : return (char*)" TRY^LIKAI";
      case '4' : return (char*)" KETURIO^LIKAI";
      case '5' : return (char*)" PENKIO^LIKAI";
      case '6' : return (char*)" ÐEÐIO^LIKAI";
      case '7' : return (char*)" SEPTYNIO^LIKAI";
      case '8' : return (char*)" AÐTUONIO^LIKAI";
      case '9' : return (char*)" DEVYNIO^LIKAI";
    }
return (char*)"";
}

char* Desimtys(char Sk, int linksnis)
{
  if((linksnis == VardL) || (linksnis == GalL)) 
	switch (Sk)
    {
      case '2' : return (char*)" DVI`DEÐIMT";
      case '3' : return (char*)" TRI`SDEÐIMT";
      case '4' : return (char*)" KE~TURIASDEÐIMT";
      case '5' : return (char*)" PEN~KIASDEÐIMT";
      case '6' : return (char*)" ÐE~ÐIASDEÐIMT";
      case '7' : return (char*)" SEPTY^NIASDEÐIMT";
      case '8' : return (char*)" AÐTU^ONIASDEÐIMT";
      case '9' : return (char*)" DEVY^NIASDEÐIMT";
    }
  else if(linksnis == KilmL) 
	switch (Sk)
    {
      case '2' : return (char*)" DVIDEÐIMTIE~S";
      case '3' : return (char*)" TRISDEÐIMTIE~S";
      case '4' : return (char*)" KETURIASDEÐIMTIE~S";
      case '5' : return (char*)" PENKIASDEÐIMTIE~S";
      case '6' : return (char*)" ÐEÐIASDEÐIMTIE~S";
      case '7' : return (char*)" SEPTYNIASDEÐIMTIE~S";
      case '8' : return (char*)" AÐTUONIASDEÐIMTIE~S";
      case '9' : return (char*)" DEVYNIASDEÐIMTIE~S";
    }
  else if(linksnis == NaudL) 
	switch (Sk)
    {
      case '2' : return (char*)" DVI`DEÐIMÈIAI";
      case '3' : return (char*)" TRI`SDEÐIMÈIAI";
      case '4' : return (char*)" KE~TURIASDEÐIMÈIAI";
      case '5' : return (char*)" PEN~KIASDEÐIMÈIAI";
      case '6' : return (char*)" ÐE~ÐIASDEÐIMÈIAI";
      case '7' : return (char*)" SEPTY^NIASDEÐIMÈIAI";
      case '8' : return (char*)" AÐTU^ONIASDEÐIMÈIAI";
      case '9' : return (char*)" DEVY^NIASDEÐIMÈIAI";
    }
  else if(linksnis == InagL) 
	switch (Sk)
    {
      case '2' : return (char*)" DVI`DEÐIMÈIA";
      case '3' : return (char*)" TRI`SDEÐIMÈIA";
      case '4' : return (char*)" KE~TURIASDEÐIMÈIA";
      case '5' : return (char*)" PEN~KIASDEÐIMÈIA";
      case '6' : return (char*)" ÐE~ÐIASDEÐIMÈIA";
      case '7' : return (char*)" SEPTY^NIASDEÐIMÈIA";
      case '8' : return (char*)" AÐTU^ONIASDEÐIMÈIA";
      case '9' : return (char*)" DEVY^NIASDEÐIMÈIA";
    }
return (char*)"";
} 

int TrizSk(char TrSk[], char Eil[], int linksnis, int gimine)
  {
  int J;
  if((TrSk[0]=='0')&&(TrSk[1]=='0')&&(TrSk[2]=='0')) return -1;

  if((TrSk[0]=='0')&&(TrSk[1]=='0')&&(TrSk[2]=='1')) return 3; //1000 tukstantis
  if((TrSk[1]=='1')||(TrSk[2]=='0')) J=2;                      //12000, 20000 tukstanciu
  else if(TrSk[2]=='1') J=0;                                   //21000 tukstantis
  else J=1;                                                    //22000 tukstanciai

  if (TrSk[0] == '1')
	{
    //strcat(Eil, " ÐIM~TAS");
	switch (linksnis)
		{
		case VardL : {strcat(Eil, " ÐIM~TAS"); break;}
		case KilmL : {strcat(Eil, " ÐIM~TO");  break;}
		case NaudL : {strcat(Eil, " ÐIM~TUI"); break;}
		case GalL  : {strcat(Eil, " ÐIM~TÀ");  break;}
		case InagL : {strcat(Eil, " ÐIMTU`");}
	    }
	}
  else
    if (TrSk[0] != '0')
      {
      strcat(Eil, Skaitmuo(TrSk[0], linksnis, VyrG));
      //strcat(Eil, " ÐIMTAI~");
	  switch (linksnis)
		{
		case VardL : {strcat(Eil, " ÐIMTAI~"); break;}
		case KilmL : {strcat(Eil, " ÐIMTØ~");  break;}
		case NaudL : {strcat(Eil, " ÐIMTA^MS");break;}
		case GalL  : {strcat(Eil, " ÐIMTU`S"); break;}
		case InagL : {strcat(Eil, " ÐIMTAI~S");}
	    }
      }
  if (TrSk[1] == '1')
    {
	strcat(Eil, Niolika(TrSk[2], linksnis));
    /*switch (TrSk[2])
      {
	  case '0' : { strcat(Eil, " DE~ÐIMT");break;}
	  case '1' : { strcat(Eil, " VIENU^OLIKA");break;}
	  case '2' : { strcat(Eil, " DVY^LIKA");break;}
	  case '3' : { strcat(Eil, " TRY^LIKA");break;}
	  case '4' : { strcat(Eil, " KETURIO^LIKA");break;}
	  case '5' : { strcat(Eil, " PENKIO^LIKA");break;}
	  case '6' : { strcat(Eil, " ÐEÐIO^LIKA");break;}
	  case '7' : { strcat(Eil, " SEPTYNIO^LIKA");break;}
	  case '8' : { strcat(Eil, " AÐTUONIO^LIKA");break;}
	  case '9' : { strcat(Eil, " DEVYNIO^LIKA");}
	  }*/
    }
  else
    {
    if (TrSk[2] != '0')
		{
		strcat(Eil, Desimtys(TrSk[1], VardL));
		strcat(Eil, Skaitmuo(TrSk[2], linksnis, gimine));
		}
	else
		{
		strcat(Eil, Desimtys(TrSk[1], linksnis));
		}

//	strcat(Eil, Desimtys(TrSk[1], linksnis));
    /*switch (TrSk[1])
      {
	  case '2' : { strcat(Eil, " DVI`DEÐIMT");break;}
	  case '3' : { strcat(Eil, " TRI`SDEÐIMT");break;}
	  case '4' : { strcat(Eil, " KE~TURIASDEÐIMT");break;}
	  case '5' : { strcat(Eil, " PEN~KIASDEÐIMT");break;}
	  case '6' : { strcat(Eil, " ÐE~ÐIASDEÐIMT");break;}
	  case '7' : { strcat(Eil, " SEPTY^NIASDEÐIMT");break;}
	  case '8' : { strcat(Eil, " AÐTU^ONIASDEÐIMT");break;}
	  case '9' : { strcat(Eil, " DEVY^NIASDEÐIMT");}
      }*/
//    if (TrSk[2] != '0') strcat(Eil, Skaitmuo(TrSk[2], linksnis, gimine));
    }
return J;
}

int IsverstiSkEil(char Sk[], char ZodzEil[], int bufs, int linksnis, int gimine)
{
  int J, Posl, PrIlgis, i;
  char Skaic[100];
  strcpy(&Skaic[2], Sk);
  Skaic[0] = '0';  Skaic[1] = '0';
  PrIlgis = strlen(Skaic);
  if (PrIlgis > 14)
    {
    for(i=2; i<PrIlgis; i++)
		if(strlen(ZodzEil)<bufs-20) {strcat(ZodzEil, Skaitmuo(Skaic[i], VardL, VyrG));}
		else {return 1;}
    switch (Skaic[PrIlgis-1])
      {
      case '0' : return 2;
      case '1' : return 0;
      default : return 1;
      }
    }
  Posl = PrIlgis % 3;

while (Posl < PrIlgis)
  {
//  J = TrizSk(&Skaic[Posl], ZodzEil, linksnis, gimine);
  switch (PrIlgis - Posl)
    {
      case 3 : {
		J = TrizSk(&Skaic[Posl], ZodzEil, linksnis, gimine);
		if(J==3) strcat(ZodzEil, Skaitmuo('1', linksnis, gimine) /*" VI^ENAS"*/);
		if (ZodzEil[0] == ' ')
//		     strcpy(ZodzEil, &ZodzEil[1]);
			memmove(ZodzEil, &ZodzEil[1], strlen(ZodzEil)); // 20190902

		if(J==-1) return 2; else return J;
	       }
      case 6 : {
		J = TrizSk(&Skaic[Posl], ZodzEil, linksnis, VyrG);
        switch (J)
           {
	       case 0 : case 3 : { 
			   //strcat(ZodzEil, " TÛ^KSTANTIS");
				switch (linksnis)
					{
					case VardL : {strcat(ZodzEil, " TÛ^KSTANTIS"); break;}
					case KilmL : {strcat(ZodzEil, " TÛ^KSTANÈIO"); break;}
					case NaudL : {strcat(ZodzEil, " TÛ^KSTANÈIUI");break;}
					case GalL  : {strcat(ZodzEil, " TÛ^KSTANTÁ");  break;}
					case InagL : {strcat(ZodzEil, " TÛ^KSTANÈIU");}
					}
			   break;}
	       case 1 : { 
			   //strcat(ZodzEil, " TÛ^KSTANÈIAI");
				switch (linksnis)
					{
					case VardL : {strcat(ZodzEil, " TÛ^KSTANÈIAI"); break;}
					case KilmL : {strcat(ZodzEil, " TÛ^KSTANÈIØ");  break;}
					case NaudL : {strcat(ZodzEil, " TÛ^KSTANÈIAMS");break;}
					case GalL  : {strcat(ZodzEil, " TÛ^KSTANÈIUS"); break;}
					case InagL : {strcat(ZodzEil, " TÛ^KSTANÈIAIS");}
					}
			   break;}
	       case 2 : { strcat(ZodzEil, " TÛ^KSTANÈIØ");}
           }
		 break;
	       }
      case 9 : {
		J = TrizSk(&Skaic[Posl], ZodzEil, linksnis, VyrG);
        switch (J)
           {
	       case 0 : case 3 : { 
			   //strcat(ZodzEil, " MILIJO~NAS");
				switch (linksnis)
					{
					case VardL : {strcat(ZodzEil, " MILIJO~NAS"); break;}
					case KilmL : {strcat(ZodzEil, " MILIJO~NO");  break;}
					case NaudL : {strcat(ZodzEil, " MILIJO~NUI"); break;}
					case GalL  : {strcat(ZodzEil, " MILIJO~NÀ");  break;}
					case InagL : {strcat(ZodzEil, " MILIJO~NU");}
					}
			   break;}
	       case 1 : { 
			   //strcat(ZodzEil, " MILIJO~NAI");
				switch (linksnis)
					{
					case VardL : {strcat(ZodzEil, " MILIJO~NAI"); break;}
					case KilmL : {strcat(ZodzEil, " MILIJO~NØ");  break;}
					case NaudL : {strcat(ZodzEil, " MILIJO~NAMS");break;}
					case GalL  : {strcat(ZodzEil, " MILIJO~NUS"); break;}
					case InagL : {strcat(ZodzEil, " MILIJO~NAIS");}
					}
			   break;}
	       case 2 : { strcat(ZodzEil, " MILIJO~NØ");}
           }
		 break;
	       }
     case 12 : {
		J = TrizSk(&Skaic[Posl], ZodzEil, linksnis, VyrG);
        switch (J)
           {
	       case 0 : case 3 : { 
			   //strcat(ZodzEil, " MILIJA^RDAS");
				switch (linksnis)
					{
					case VardL : {strcat(ZodzEil, " MILIJA^RDAS"); break;}
					case KilmL : {strcat(ZodzEil, " MILIJA^RDO");  break;}
					case NaudL : {strcat(ZodzEil, " MILIJA^RDUI"); break;}
					case GalL  : {strcat(ZodzEil, " MILIJA^RDÀ");  break;}
					case InagL : {strcat(ZodzEil, " MILIJA^RDU");}
					}
			   break;}
	       case 1 : { 
			   //strcat(ZodzEil, " MILIJA^RDAI");
				switch (linksnis)
					{
					case VardL : {strcat(ZodzEil, " MILIJA^RDAI"); break;}
					case KilmL : {strcat(ZodzEil, " MILIJA^RDØ");  break;}
					case NaudL : {strcat(ZodzEil, " MILIJA^RDAMS");break;}
					case GalL  : {strcat(ZodzEil, " MILIJA^RDUS"); break;}
					case InagL : {strcat(ZodzEil, " MILIJA^RDAIS");}
					}
			   break;}
	       case 2 : { strcat(ZodzEil, " MILIJA^RDØ");}
           }
	       }
    }
  Posl += 3;
  }
return 1;
}

int VisasSkaicius(char Sk[], char ZodzEil[], int bufsize, int linksnis, int gimine)
{
  ZodzEil[0]=0;
  int i=0;
  int J, Jfinal=1;
  int ilg=strlen(Sk);
  char skaicius[100];
  do
  {
  if(Sk[i]=='+') {strcat(ZodzEil, " PLIUS"); i++;}
  else if(Sk[i]=='-') {if(isdigit(Sk[i+1])) strcat(ZodzEil, " MI`NUS"); i++;}

  while(Sk[i]=='0') {strcat(ZodzEil, " NU`LIS"); i++; if(Jfinal!=4) Jfinal=2;}
  int j=0;
  while(isdigit(Sk[i])) {skaicius[j]=Sk[i]; j++; i++;}
  if(j>0)
    {
    skaicius[j]=0;
    J=IsverstiSkEil(skaicius, ZodzEil, bufsize, linksnis, gimine);
    if(Jfinal!=4) Jfinal=J;
    }
  if(Sk[i]==',') {strcat(ZodzEil, " KABLE~LIS"); i++; Jfinal=4;}
  else //if(Sk[i]=='%')
	{
    switch (Jfinal)
      {
      case 0 : case 3 : { 
//		  strcat(ZodzEil, " #VnsV#");
				switch (linksnis)
					{
					case VardL : {strcat(ZodzEil, " #VnsV#"); break;}
					case KilmL : {strcat(ZodzEil, " #VnsK#"); break;}
					case NaudL : {strcat(ZodzEil, " #VnsN#"); break;}
					case GalL  : {strcat(ZodzEil, " #VnsG#"); break;}
					case InagL : {strcat(ZodzEil, " #VnsI#");}
					}
		  break;}
      case 2 : { strcat(ZodzEil, " #DgsK#");break;}
      case 4 : { strcat(ZodzEil, " #VnsK#");break;}
      default : {
//		  strcat(ZodzEil, " #DgsV#");
				switch (linksnis)
					{
					case VardL : {strcat(ZodzEil, " #DgsV#"); break;}
					case KilmL : {strcat(ZodzEil, " #DgsK#"); break;}
					case NaudL : {strcat(ZodzEil, " #DgsN#"); break;}
					case GalL  : {strcat(ZodzEil, " #DgsG#"); break;}
					case InagL : {strcat(ZodzEil, " #DgsI#");}
					}
				}
      }
	i++;
    }
  if(Jfinal!=4) Jfinal=1;
  }
  while(i<ilg);

return strlen(ZodzEil);
}

	string years[] = {
		"PIRMØ~",
		"ANTRØ~",
		"TREÈIØ~",
		"KETVIRTØ~",
		"PENKTØ~",
		"ÐEÐTØ~",
		"SEPTINTØ~",
		"AÐTUNTØ~",
		"DEVINTØ~",
		"DEÐIMTØ~",
		"VIENU^OLIKTØ",
		"DVY^LIKTØ",
		"TRY^LIKTØ",
		"KETURIO^LIKTØ",
		"PENKIO^LIKTØ",
		"ÐEÐIO^LKTØ",
		"SEPTYNIO^LIKTØ",
		"AÐTUONIO^LIKTØ",
		"DEVYNIO^LIKTØ"
	};
	string months[] = {
		"SAUSIO",
		"VASARIO",
		"KOVO",
		"BALANDÞIO",
		"GEGUÞËS",
		"BIRÞELIO",
		"LIEPOS",
		"RUGPJÛÈIO",
		"RUGSËJO",
		"SPALIO",
		"LAPKRIÈIO",
		"GRUODÞIO"
	};
	string days[] = {
		"PIRMA`",
		"ANTRA`",
		"TREÈIA`",
		"KETVIRTA`",
		"PENKTA`",
		"ÐEÐTA`",
		"SEPTINTA`", 
		"AÐTUNTA`",
		"DEVINTA`", 
		"DEÐIMTA`",
		"VIENU^OLIKTA",
		"DVY^LIKTA",
		"TRY^LIKTA",
		"KETURIO^LIKTA",
		"PENKIO^LIKTA",
		"ÐEÐIO^LIKTA",
		"SEPTYNIO^LIKTA",
		"AÐTUONIO^LIKTA",
		"DEVYNIO^LIKTA",
		"DVIDEÐIMTA`",
		"DVI`DEÐIMT PIRMA`",
		"DVI`DEÐIMT ANTRA`",
		"DVI`DEÐIMT TREÈIA`",
		"DVI`DEÐIMT KETVIRTA`",
		"DVI`DEÐIMT PENKTA`",
		"DVI`DEÐIMT ÐEÐTA`",
		"DVI`DEÐIMT SEPTINTA`", 
		"DVI`DEÐIMT AÐTUNTA`",
		"DVI`DEÐIMT DEVINTA`", 
		"TRISDEÐIMTA`",
		"TRI`SDEÐIMT PIRMA`"
	};
	

	
int expandDate(int yearNumber, int monthNumber, int dayNumber, int mode, char returnText[])
{
	char resTmp[256];
	char inputTmp[256];
	resTmp[0]=0;
	sprintf(inputTmp, "%d", yearNumber);
//	VisasSkaicius(inputTmp, resTmp, 256, VardL, VyrG);
	IsverstiSkEil(inputTmp, resTmp, 256, VardL, VyrG);
	string yearsString = resTmp;

	int findResult = -1;

	if (yearNumber == 0)
	{
		yearsString = "NULINIØ";
	}
	else if ((yearNumber % 1000) == 0)
	{
		if (yearNumber == 1000)
		{
			findResult = yearsString.rfind("TÛ^KSTANTIS");//1000
			if (findResult != -1) yearsString.replace(findResult, strlen("TÛ^KSTANTIS"), "TÛKSTANTØ~JØ");
			else return -1;
		}
		else //2000,3000,... 
		{
			findResult = yearsString.rfind("TÛ^KSTANÈIAI");
			if (findResult != -1) yearsString.replace(findResult, strlen("TÛ^KSTANÈIAI"), "TÛKSTANTØ~JØ");
			else return -1;
		}
	}
	else if ((yearNumber % 100) == 0)
	{
		findResult = yearsString.rfind("ÐIM~TAS"); //100,1100,2100,...
		if (findResult != -1) yearsString.replace(findResult, strlen("ÐIM~TAS"), "ÐIMTØ~JØ");
		else
		{
			findResult = yearsString.rfind("ÐIMTAI~"); //200,300,...,800,900,1200,...,1800,1900,2200,...
			if (findResult != -1) yearsString.replace(findResult, strlen("ÐIMTAI~"), "ÐIMTØ~JØ");
			else return -1;
		}
	}
	else if ((yearNumber % 10) == 0)
	{
		findResult = yearsString.rfind("ÐIMT"); //10,20,...,90,...,1980,1990,2010,2020,...
		if (findResult != -1) yearsString.replace(findResult, strlen("ÐIMT"), "ÐIMTØ~JØ");					
		else return -1;

	}
	else if ((yearNumber % 100) < 20) //...,1901,1902,...1919,2001,...
	{
		int SkTmp = yearNumber - (yearNumber % 100);
		resTmp[0]=0;
		sprintf(inputTmp, "%d", SkTmp);
//		VisasSkaicius(inputTmp, resTmp, 256, VardL, VyrG);
		IsverstiSkEil(inputTmp, resTmp, 256, VardL, VyrG);
		string yearsString2 = resTmp;
		yearsString = yearsString2 + " " + years[(yearNumber % 100)-1];
	}
	else if ((yearNumber % 100) > 20) //...,1921,1922,...1999,2021,...
	{
		int SkTmp = yearNumber - (yearNumber % 10);
		resTmp[0]=0;
		sprintf(inputTmp, "%d", SkTmp);
//		VisasSkaicius(inputTmp, resTmp, 256, VardL, VyrG);
		IsverstiSkEil(inputTmp, resTmp, 256, VardL, VyrG);
		string yearsString2 = resTmp;
		yearsString = yearsString2 + " " + years[(yearNumber % 10)-1];		
	}
	else return -1;

	string returnTextStringTmp;
	if (mode == 0)
		returnTextStringTmp = yearsString + " " + months[monthNumber-1] + " " + days[dayNumber-1];
	else 
		returnTextStringTmp = yearsString + " ME~TØ " + months[monthNumber-1] + " " + days[dayNumber-1] + " DIENA`";
	sprintf(returnText, "%s", returnTextStringTmp.c_str());

	return 0;
}

//OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
int expandTime(int hourNumber, int minNumber, int secNumber, int mode, char returnText[])
{
	char resTmp[256];
	char inputTmp[256];

	if((hourNumber < 0) || (hourNumber > 24)) return -1;
	if((minNumber < 0) || (minNumber > 60)) return -1;

/*	if(hourNumber > 0) 
	{
		resTmp[0]=0;
		sprintf(inputTmp, "%d", hourNumber);
		IsverstiSkEil(inputTmp, resTmp, 256, VardL, MotG);
	}
	else
	{
		strcpy(resTmp, "NU`LIS ");
	}
	string hourString = resTmp;

	if(minNumber > 0)
	{
		resTmp[0]=0;
		sprintf(inputTmp, "%d", minNumber);
		IsverstiSkEil(inputTmp, resTmp, 256, VardL, MotG);
	}
	else
	{
		strcpy(resTmp, "NU`LIS ");
	}
	string minString = resTmp;*/

	sprintf(inputTmp, "%d", hourNumber);
	VisasSkaicius(inputTmp, resTmp, 256, VardL, MotG);
	string hourString = resTmp;

	sprintf(inputTmp, "%d", minNumber);
	VisasSkaicius(inputTmp, resTmp, 256, VardL, MotG);
	string minString = resTmp;

	if (minNumber < 10)
	{
		minString.insert(0, (char*)"NU`LIS ");
	}

	string returnTextStringTmp;
	if (mode == 0)
		returnTextStringTmp = hourString + " " + minString; // + " " + secString;
	else 
		returnTextStringTmp = hourString + " val " + minString + " min"; // + secString + " sek";
	sprintf(returnText, "%s", returnTextStringTmp.c_str());

	return 0;
}

int initTextNorm(char * rulesFilesDirectory, char * rulesFileName) 
{
	char buffer_temp[1024];	

	totalRules = 0;
	totalFileBuffers = 0;
	sprintf(buffer_temp, "%s%s", rulesFilesDirectory, rulesFileName);
	FILE * file = fopen (buffer_temp, "r");
	if (file == NULL)
		return ERROR_TEXTNORMALIZATION_OPENING_RULES_FILE;
	while (fgets(buffer_temp , 1024 , file) != NULL)
	{
		if (buffer_temp[0] != '/')
		{
			rulesArray[totalRules].assign(buffer_temp);
			totalRules++;

			// File buffers
			if (strstr(buffer_temp, "AbbSeparateWord:") != NULL || strstr(buffer_temp, "ReplaceWithFile:") != NULL)
				totalFileBuffers++;
		}
	}
	fclose(file);
	
	// File buffers
	if (totalFileBuffers > 0)
	{
		abbLists = new char**[totalFileBuffers];
		abbListsSubstitutions = new char**[totalFileBuffers];
//		abbListsIsWithSep = new unsigned short*[totalFileBuffers]; //20200410
		abbSizes = new int[totalFileBuffers];
		for(int i=0; i<totalFileBuffers; i++)
		{
		   abbLists[i] = new char*[2048];
		   abbListsSubstitutions[i] = new char*[2048];
//		   abbListsIsWithSep[i] = new unsigned short[2048]; //20200410
		   for(int j=0; j<2048; j++)
		   {
			   abbLists[i][j] = new char[64];
			   abbListsSubstitutions[i][j] = new char[256];
		   }
		}

		int currentFileBuffer = 0;
		sprintf(buffer_temp, "%s%s", rulesFilesDirectory, rulesFileName);
		file = fopen (buffer_temp, "r");
		if (file == NULL) 
			return  ERROR_TEXTNORMALIZATION_OPENING_RULES_FILE;
		while (fgets(buffer_temp , 1024 , file) != NULL)
		{
			if (buffer_temp[0] != '/')
			{			
				if (strstr(buffer_temp, "AbbSeparateWord:") != NULL || strstr(buffer_temp, "ReplaceWithFile:") != NULL)
				{
					char * fileName = strstr(buffer_temp, ":") + 1;
					memset(strstr(fileName, "@"), 0, 1);
					abbSizes[currentFileBuffer] = 0;
					char fileNameTemp[128];	
					strcpy(fileNameTemp, fileName);	
					sprintf(buffer_temp, "%s%s", rulesFilesDirectory, fileNameTemp);
					FILE * fileAbb = fopen (buffer_temp, "r");
					if (fileAbb == NULL) 
					{
						fclose(file);
						return ERROR_TEXTNORMALIZATION_OPENING_FILE_SPECIFIED_IN_RULES_FILE;
					}
					while (fgets(buffer_temp, 1024, fileAbb) != NULL)
					{
						int rez = sscanf(buffer_temp, "%63[^@]@%255[^@]", 
							abbLists[currentFileBuffer][abbSizes[currentFileBuffer]], 
							abbListsSubstitutions[currentFileBuffer][abbSizes[currentFileBuffer]]);
						if(rez < 2)
							abbListsSubstitutions[currentFileBuffer][abbSizes[currentFileBuffer]][0] = 0; //Pijaus 20161220, nes neveike aaa@@
/*						if (abbLists[currentFileBuffer][abbSizes[currentFileBuffer]][strlen(abbLists[currentFileBuffer][abbSizes[currentFileBuffer]])-1] == '.')
							abbListsIsWithSep[currentFileBuffer][abbSizes[currentFileBuffer]] = 1;
						else
							abbListsIsWithSep[currentFileBuffer][abbSizes[currentFileBuffer]] = 0;*/              //20200410
						abbSizes[currentFileBuffer]++;
					}
					fclose(fileAbb);

					currentFileBuffer++;
				}
			}
		}		
	}
	fclose(file);

	return NO_ERR;
}

int applyPhrasesFilter(stringWithLetterPosition * bufferString)
{			
	char bruks = '–';
	string wordSeparatorsList = "\t [{(\"„“']}).?!;:,-\r\n=";
	wordSeparatorsList.append(1, bruks);
	string phraseSeparatorsList = ".?!;:\r\n,";
	phraseSeparatorsList.append(1, bruks);
	string leadAndTrailSymbolsList = "[{()}]\"'";


	int phraseStartIndex = 0;
	int phraseEndIndex = bufferString->find_first_of(phraseSeparatorsList, phraseStartIndex);
	while (phraseEndIndex != -1)
	{
		if ( ((bufferString->at(phraseEndIndex) != bruks) && (bufferString->at(phraseEndIndex) != ',')) || 

			 ((bufferString->at(phraseEndIndex) == ',') && (((phraseEndIndex - phraseStartIndex) >= 25) && ((phraseEndIndex - phraseStartIndex) <= 120))) ||

			 ((bufferString->at(phraseEndIndex) == bruks) && 
			 (phraseEndIndex > 0) && 
			 (phraseEndIndex < (bufferString->length()-1)) && 
			 (bufferString->at(phraseEndIndex+1) == ' ') && 
			 (bufferString->at(phraseEndIndex-1) == ' ') && 
			 (((phraseEndIndex - phraseStartIndex) >= 25) && ((phraseEndIndex - phraseStartIndex) <= 120)))
			)
		{
			if ( (bufferString->at(phraseEndIndex) != '\n') && 
				 ((phraseEndIndex >= (bufferString->length()-1)) || (bufferString->at(phraseEndIndex+1) != '\n'))
				)
			{
				bufferString->insert(phraseEndIndex+1, (char*)"\n");
				phraseEndIndex+=1;					
			}
		}
		else
		{

			bufferString->erase(phraseEndIndex, 1);
			phraseEndIndex-=1;
		}

		if ((phraseEndIndex - phraseStartIndex) > 120)
		{
			string phraseSecondarySeparatorsList = "[{(]})\"'";
			int r = bufferString->find_first_of(phraseSecondarySeparatorsList, phraseStartIndex+25);
			if ((r != -1) && (r <= phraseStartIndex+120))
			{
				bufferString->insert(r+1, (char*)"\n");
				phraseEndIndex=r+1;		
			}
			else
			{
				string phraseTertiarySeparatorsList[] = {"ir","bei","ar","arba"};
				int r = -1;
				int bestR = bufferString->length();
				int bestI = -1;
				for (int i = 0; i < 4; i++)
				{
					r = bufferString->find(phraseTertiarySeparatorsList[i], phraseStartIndex+55);
					if ((r != -1) && (r < bestR) && (r <= phraseStartIndex+120))
					{
						bool isSeparateWord = true;

						if (((r-1) >= 0) && 
							(wordSeparatorsList.find(bufferString->at(r-1)) == -1))
								isSeparateWord = false;

						if (((r + phraseTertiarySeparatorsList[i].length()) <= (bufferString->length()-1)) && 
							(wordSeparatorsList.find(bufferString->at(r+phraseTertiarySeparatorsList[i].length())) == -1))
								isSeparateWord = false;

						if (isSeparateWord == true)
						{
							bestR = r;
							bestI = i;
						}
					}
				}
				if (bestR != bufferString->length())
				{
					bufferString->insert(bestR, (char*)"\n");
					phraseEndIndex=bestR;
				}
				else
				{
					bool isDone = false;
					int r = bufferString->rfind(' ', phraseStartIndex+120);
					while (r != -1)
					{
						if ( ( r > 0 ) && ( r < ( bufferString->length() - 1) ) && 
							 ( bufferString->letPos[r-1] != bufferString->letPos[r+1] ) )
						{
							bufferString->insert(r+1, (char*)"\n");
							phraseEndIndex=r+1;
							isDone = true;
							break;
						}
						r = bufferString->rfind(' ', r-1);
					}

					if ( ! isDone )
					{
						bufferString->insert(phraseStartIndex+120, (char*)"\n");
						phraseEndIndex=phraseStartIndex+120;	
					}
				}
			}				
		}

		phraseStartIndex = phraseEndIndex+1;
		phraseEndIndex = bufferString->find_first_of(phraseSeparatorsList, phraseStartIndex);
	}

	int findResult = bufferString->find_first_of(leadAndTrailSymbolsList, 0);
	while (findResult != -1)
	{
		bufferString->erase(findResult, 1);
		findResult = bufferString->find_first_of(leadAndTrailSymbolsList, 0);
	}

	return NO_ERR;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int priesdfound = 0;

char *priesd[5][88] = {{
	(char*)"Anot",   (char*)"anot",
	(char*)"Ant",    (char*)"ant",
	(char*)"Arti",   (char*)"arti",
	(char*)"Aukðèiau",(char*)"aukðèiau",
	(char*)"Be",     (char*)"be",
	(char*)"Dëka",   (char*)"dëka",
	(char*)"Dël",    (char*)"dël",
	(char*)"Dëlei",  (char*)"dëlei",
	(char*)"Greta",  (char*)"greta",
	(char*)"Iki",    (char*)"iki",
	(char*)"Lig",    (char*)"lig",
	(char*)"Ligi",   (char*)"ligi",
	(char*)"Ið",     (char*)"ið",
	(char*)"Link",   (char*)"link",
	(char*)"Linkui", (char*)"linkui",
	(char*)"Netoli", (char*)"netoli",
	(char*)"Nuo",    (char*)"nuo",
	(char*)"Pasak",  (char*)"pasak",
	(char*)"Pirmiau",(char*)"pirmiau",
	(char*)"Pirm",   (char*)"pirm",
	(char*)"Prie",   (char*)"prie",
	(char*)"Pusiau", (char*)"pusiau",
	(char*)"Ðalia",  (char*)"ðalia",
	(char*)"Tarp",   (char*)"tarp",
	(char*)"Toliau", (char*)"toliau",
	(char*)"Þemiau", (char*)"þemiau",
	(char*)"Vidury", (char*)"vidury",
	(char*)"Vidur",  (char*)"vidur",
	(char*)"Vietoj", (char*)"vietoj",
	(char*)"Virð",   (char*)"virð",
	(char*)"Virðum", (char*)"virðum",
	(char*)"Virðuj", (char*)"virðuj",
	(char*)"Iðilgai",  (char*)"iðilgai",
	(char*)"Ástriþai", (char*)"ástriþai",
	(char*)"Ákypai",   (char*)"ákypai",
	(char*)"Skersai",  (char*)"skersai",
	(char*)"Kiaurai",  (char*)"kiaurai",
	(char*)"Skradþiai",(char*)"skradþiai",
	(char*)"Abipus",   (char*)"abipus",
	(char*)"Anapus",   (char*)"anapus",
	(char*)"Ðiapus",   (char*)"ðiapus",
	(char*)"Abigaliai",(char*)"abigaliai",
	(char*)"Ið po",    (char*)"ið po",
	(char*)"Ið uþ",    (char*)"ið uþ"},
//	(char*)"Ið tarp",  (char*)"ið tarp",
//	(char*)"Ið anapus",(char*)"ið anapus",
//	(char*)"Á anapus", (char*)"á anapus",
//	(char*)"Uþ anapus",(char*)"uþ anapus"},

   {(char*)"Apie",   (char*)"apie", // Gal
	(char*)"Aplink", (char*)"aplink",
	(char*)"Aplinkui", (char*)"aplinkui",
	(char*)"Á",      (char*)"á",
	(char*)"Pagal",  (char*)"pagal",
	(char*)"Palei",  (char*)"palei",
	(char*)"Pas",    (char*)"pas",
	(char*)"Paskui", (char*)"paskui",
	(char*)"Paskum", (char*)"paskum",
	(char*)"Per",    (char*)"Per",
	(char*)"Prieð",  (char*)"prieð",
	(char*)"Prieðais", (char*)"prieðais",
	(char*)"Pro",    (char*)"pro"},

   {(char*)"Su",    (char*)"su", // Inag
	(char*)"Sulig", (char*)"sulig",
	(char*)"Ties",  (char*)"ties"},

   {(char*)"Uþ",  (char*)"uþ"}, // Kilm (atstumas, laikas) Gal (pinigai)
   {(char*)"Po",  (char*)"po"}}; // Kilm (laikas) Gal (kitais atv) Inag

int priesdkiek[5] = {88, 26, 6, 2, 2};

char *matvntmot[] = { (char*)"min", (char*)"val", (char*)"s", (char*)"sek", (char*)"ms", (char*)"t",
		(char*)"h", (char*)"mph", (char*)"mi/h", (char*)"kWh", (char*)"mi", (char*)"ft"};

int matvntmotkiek = 12;

char *matvntlaikas[] = { (char*)"min", (char*)"val", (char*)"s", (char*)"sek", (char*)"ms", 
		(char*)"h", (char*)"d", (char*)"mën"};

int matvntlaikaskiek = 8;

char *matvntatstumas[] = { (char*)"mm", (char*)"cm", (char*)"dm", (char*)"m", (char*)"km", 
		(char*)"ft", (char*)"yd", (char*)"mi"};

int matvntatstumaskiek = 8;

int getmatvnttype(const char *eilute/*stringWithLetterPosition bufferString*/, int digitsWordEndIndex, int kiek, char** matvnt)
{
//	const char *eilute = bufferString.c_str();
	while((digitsWordEndIndex < strlen(eilute)) && (eilute[digitsWordEndIndex] == ' ')) digitsWordEndIndex++;
	for(int j=0; j<kiek; j++)
		{
		int i=0;
		while((digitsWordEndIndex + i < strlen(eilute)) 
			&& (i < strlen(matvnt[j]))
			&&(eilute[digitsWordEndIndex + i] == matvnt[j][i]))
			i++;
		if(i == strlen(matvnt[j]))
			if(!strchr("aàbcèdeæëfghiáyjklmnoprsðtuøûvzþxwqAÀBCÈDEÆËFGHIÁYJKLMNOPRSÐTUØÛVZÞXWQ", eilute[digitsWordEndIndex + i])) 
				return 1; //MotG;
		}

	return 0; //VyrG;
}

int getLinksnis(const char *eilute/*stringWithLetterPosition bufferString*/, int digitsWordStartIndex, int digitsWordEndIndex)
{
//	const char *eilute = bufferString.c_str();
	while((digitsWordStartIndex > 0) && (eilute[digitsWordStartIndex] == ' ')) digitsWordStartIndex--;
	int i;

	if(priesdfound)
		{
		i=0;
		if((digitsWordStartIndex - i > 0) && (eilute[digitsWordStartIndex - i] == '.')) i++; //20170120 taskas santrumpos gale

		while((digitsWordStartIndex - i > 0) && 
			strchr("abcdefghiyjklmnoprstuvzxwqABCDEFGHIYJKLMNOPRSTUVZXWQ/%$€£", eilute[digitsWordStartIndex - i]) &&
			(i < 4)) i++;
		while((digitsWordStartIndex - i > 0) && (eilute[digitsWordStartIndex - i] == ' '))
			i++;
		if((digitsWordStartIndex - i > 0) && (eilute[digitsWordStartIndex - i] == '#'))
			{return priesdfound; /*KilmL;*/}
		else
			{priesdfound = 0;}
		}

	if(!priesdfound)
		{
		for(int jj=0; jj<5; jj++)
		for(int j=0; j<priesdkiek[jj]; j++) //98 - priesdeliu su Kilm skaicius
			{
			i=0;
			int k=strlen(priesd[jj][j]); 
			while((digitsWordStartIndex - i >= 0) 
				&& (i < k)
				&&(eilute[digitsWordStartIndex - i] == priesd[jj][j][k-i-1]))
				i++;
			if(i == k)
				if((digitsWordStartIndex - i < 0) 
					|| !strchr("aàbcèdeæëfghiáyjklmnoprsðtuøûvzþxwqAÀBCÈDEÆËFGHIÁYJKLMNOPRSÐTUØÛVZÞXWQ", eilute[digitsWordStartIndex - i])) 
					{
					switch(jj)
					{
					case 0 : {priesdfound = KilmL; break;}
					case 1 : {priesdfound = GalL; break;}
					case 2 : {priesdfound = InagL; break;}
					case 3 : {	int ismatvntatstumas = getmatvnttype(eilute, digitsWordEndIndex, matvntatstumaskiek, matvntatstumas); //Uz
								int ismatvntlaikas = getmatvnttype(eilute, digitsWordEndIndex, matvntlaikaskiek, matvntlaikas);
if (ismatvntatstumas || ismatvntlaikas)
{
	priesdfound = KilmL;
}
else
{
	priesdfound = GalL;
}
break; }
					case 4: {	int ismatvntlaikas = getmatvnttype(eilute, digitsWordEndIndex, matvntlaikaskiek, matvntlaikas); //po
						if (ismatvntlaikas)
						{
							priesdfound = KilmL;
						}
						else
						{
							priesdfound = GalL;
						}
						break; }
					}

					return priesdfound;
					}
			}
		}

		priesdfound = 0;
		return priesdfound; //VardL;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int spellText(char * buffer, char * retBuffer, int bufferSize, int * letPos)
{
	stringWithLetterPosition bufferString(buffer, letPos, bufferSize);
	if (bufferString.at(bufferString.length() - 1) != '\n') bufferString.append((char*)"\n");

	// Spelling
	int currentIndex = 0;
	while (bufferString.at(currentIndex) != '\n')
	{
		char * symbolText = SimbPavad(bufferString.at(currentIndex));
		int symbolTextLength = strlen(symbolText);
		bufferString.replace(currentIndex, 1, symbolText);
		currentIndex += symbolTextLength;
		if (bufferString.at(currentIndex) != ' ')
			bufferString.insert(currentIndex, 1, ' ');

		currentIndex += 1;
	}

	// Phrases
	applyPhrasesFilter(&bufferString);

	// Checking if buffer is OK
	int currentSize = bufferString.length();
	if (currentSize > bufferSize) return ERROR_TEXTNORMALIZATION_BUFFER_OVERFLOW;

	// Filling return buffer
	memcpy(retBuffer, bufferString.c_str(), currentSize);
	retBuffer[currentSize] = '\0';

	return NO_ERR;
}

#include "RateChange1.h" // log spausdinimui
// jei ne nulis, iðveda papildomà informacijà apie programos darbà, apie kiekvienà apdorojamà fonemà
int debug2 = 0;

//---Unicode to char new---------------------------------------------------
/*int UtoChar(unsigned short* eiluteU, stringWithLetterPosition* bufferString, int ilgis, int readEmoji)
{
	int i, j, k, m, ukodilg, maxkodu;
	if (readEmoji) { maxkodu = MAX_KODU; } else { maxkodu = MAX_UKODU; } //20200410
	for (i = 0, j = 0; j < ilgis; i++, j++)
	{
		for (k = 0; k < maxkodu; k++)
		{
			ukodilg = 1; while(Kod[k].ukod[ukodilg] != 0) ukodilg++;
			m = 0;
			while ((m < ukodilg) && (eiluteU[j + m] == Kod[k].ukod[m])) m++;
			if (m == ukodilg)
			{
				bufferString->replace(i, ukodilg, Kod[k].ckod);
				i += strlen(Kod[k].ckod) - 1;
				j += ukodilg - 1;
				break;
			}
		}
		if (k == maxkodu)
		{
			if ((eiluteU[j] >> 8) == 0) { bufferString->replace(i, 1, 1, (char)eiluteU[j]); }
			else { bufferString->replace(i, 1, 1, ' '); }
		}
	}

	return i; // 2019-11-23 GS: eilutës ilgis bus i, nes nuo 0 iki i-1 //buvo i-1 ???
}*/

//--- Unicode to char 2020-10-16 ---------------------------------------------------
// Realizuotas fonemø pavadinimø skaitymas.
// Jei sintezatorius gauna eilutæ, kuri nuo antro þenklo sutampa su specialaus pavidalo eilute, 
// pirmà þenklà reikës pakeisti á jo pavadinimà, o ne á patá þenklà.
// Specialios kodavimo taisyklës pateiktos unicode_emoji.h faile.
// Jei reikia pakeisti á pavadinimà, o specialioje taisyklëje pavadinimas nenurodytas arba NULL, pakeis á þenklà ið specialios taisyklës
// Jei reikia pakeisti á þenklà, o specialioje taisyklëje þenklas lygus NULL, pritaiko bendrà taisyklæ
// (bendra taisyklë: jei galima cast'inti á char, taip ir daro, jei ne, keièia á tarpo þenklà)

#define SPEC_PAVIDALO_EILUCIU_SKAICIUS 6
// specialaus pavidalo eilutës, pradedant nuo antro þenklo
// (pirmas þenklas gali kisti, o nuo antro iki pabaigos jos yra fiksuotos)
const char16_t* SpecPavidaloEilutes[SPEC_PAVIDALO_EILUCIU_SKAICIUS] = {
	u"",
	u" did\u017Eioji",
	u", Lauko prad\u017Eia",
	u", Lauko pabaiga",
	u" did\u017Eioji, Lauko prad\u017Eia",
	u" did\u017Eioji, Lauko pabaiga" };
// specialaus pavidalo eiluèiø ilgiai, pradedant nuo antro þenklo
const int SpecPavidaloEiluciuIlgiai[SPEC_PAVIDALO_EILUCIU_SKAICIUS] = {0, 9, 15, 15, 24, 24};

// Patikrina, ar paduota eilutë yra specialaus pavidalo
bool arEiluteSpecPavidalo(unsigned short* eiluteU, int ilgis) {
	// pradësime lyginti tik nuo antro þenklo, todël perskaièiuojam eiluteU ir ilgis
	eiluteU++; ilgis--;
	for (int i = 0; i < SPEC_PAVIDALO_EILUCIU_SKAICIUS; i++)
		if (ilgis == SpecPavidaloEiluciuIlgiai[i]) {
			int m = 0;
			while ((m < ilgis) && (eiluteU[m] == SpecPavidaloEilutes[i][m])) m++;
			if (m == ilgis)
				return true;
		}
	return false;
}

int UtoChar(unsigned short* eiluteU, stringWithLetterPosition* bufferString, int ilgis, int readEmoji)
{
	int i, j, k, m, ukodilg, maxkodu;
	if (readEmoji) { maxkodu = MAX_KODU; }
	else { maxkodu = MAX_UKODU; } //20200410
	// nustatome, ar eilutë specialaus pavidalo
	bool specialausPavidalo = arEiluteSpecPavidalo(eiluteU, ilgis);
	for (i = 0, j = 0; j < ilgis; i++, j++)
	{
		bool taikytiBendraTaisykle = false;
		for (k = 0; k < maxkodu; k++)
		{
			ukodilg = 1; while (Kod[k].ukod[ukodilg] != 0) ukodilg++;
			m = 0;
			while ((m < ukodilg) && (eiluteU[j + m] == Kod[k].ukod[m])) m++;
			if (m == ukodilg)
			{
				// jei: 1) tekstas specialaus pavidalo, ir 
				//      2) tai pirmasis teksto þenklas, ir
				//      3) specialioje taisyklëje pateiktas þenklo pavadinimas
				if (specialausPavidalo && (j == 0) && (Kod[k].pavad != NULL)) {
					// reikia áterpti pavadinimà
					bufferString->replace(i, ukodilg, Kod[k].pavad);
					i += strlen(Kod[k].pavad) - 1;
					j += ukodilg - 1;
				}
				else {
					// Reikia áterpti þenklà
					if (Kod[k].ckod != NULL) {
						// Jei þenklas pateiktas specialioje taisyklëje, áterpiame já ið ten
						bufferString->replace(i, ukodilg, Kod[k].ckod);
						i += strlen(Kod[k].ckod) - 1;
						j += ukodilg - 1;
					}
					else {
						// jei þenklas specialioje taisyklëje nepateiktas, naudosime bendrà taisyklæ.
						// Uþstatome poþymá, kad reikia taikyti bendrà taisyklæ
						taikytiBendraTaisykle = true;
					}
				}
				break;
			}
		}
		if ((k == maxkodu) || taikytiBendraTaisykle)
		{
			if ((eiluteU[j] >> 8) == 0) { bufferString->replace(i, 1, 1, (char)eiluteU[j]); }
			else { bufferString->replace(i, 1, 1, ' '); }
		}
	}

	return i; // 2019-11-23 GS: eilutës ilgis bus i, nes nuo 0 iki i-1 //buvo i-1 ???
}

//--------------------------------------------------------------------------------------
//int normalizeText(char * buffer, char * retBuffer, int bufferSize, int * letPos) 
//int normalizeText(unsigned short* unikodo_tekstas, unsigned int textsize, char * retBuffer, int bufferSize, int * letPos)
int normalizeText(unsigned short* unikodo_tekstas, unsigned int textsize, char * retBuffer, int bufferSize, int * letPos, 
	int skaiciu_rezimas, int skyrybos_rezimas, int expandAbbr, int readEmoji) //20200410
{
		char* buffer = (char*)malloc(textsize + 1);
		if (buffer == NULL)
		{
			return ERROR_LITHUSS_MEMORY_ALLOCATION;
		}
		for (int i = 0; i < textsize; i++) buffer[i] = '_'; // GS 2020-03-10: uþpildyti nenuliais, kad korektiðkai veiktø stringWithLetterPosition funkcijos
		buffer[textsize] = 0;

		stringWithLetterPosition bufferString(buffer, letPos, bufferSize);

		free(buffer);

	if (debug2) {
		char pranesimas[1024];
		sprintf(pranesimas, "normalizeText: letPos masyvas pries UtoChar:"); spausdinti_loga(pranesimas);
		spausdinti_int_masyva(letPos, textsize);
	}

	UtoChar(unikodo_tekstas, &bufferString, textsize, readEmoji);

	if (debug2) {
		char pranesimas[1024];
		sprintf(pranesimas, "normalizeText: letPos masyvas po UtoChar:"); spausdinti_loga(pranesimas);
		spausdinti_int_masyva(letPos, bufferString.length());
	}

		if (bufferString.at(bufferString.length()-1) != '\n') bufferString.append((char*)"\n");

		char bruks = '–';

		string wordSeparatorsList = "\t [{(\"„“']}).?!;:,-\r\n=";
		wordSeparatorsList.append(1, bruks);
		string leadAndTrailSymbolsList = "[{()}]\"'";
		string digitsList = "1234567890";
		string smallLettersList = "aàbcèdeæëfghiáyjklmnoprsðtuøûvzþxwq";
		string capitalLettersList = "AÀBCÈDEÆËFGHIÁYJKLMNOPRSÐTUØÛVZÞXWQ";
		string lettersList = smallLettersList + capitalLettersList;
		string phraseSeparatorsList = ".?!;:\r\n,";
		phraseSeparatorsList.append(1, bruks);

		int currentFileBuffer = 0;

		for (int rn = 0; rn < totalRules; rn++)
		{
			string rulesBufferString = rulesArray[rn];

			int findResult = -1;

			findResult = rulesBufferString.find("\\r", 0);
			while (findResult != -1) 
			{
				rulesBufferString.replace(findResult, 2, "\r"); 
				findResult = rulesBufferString.find("\\r", 0); 
			}
			findResult = rulesBufferString.find("\\n", 0);
			while (findResult != -1) 
			{ 
				rulesBufferString.replace(findResult, 2, "\n"); 
				findResult = rulesBufferString.find("\\n", 0); 
			}

            findResult = rulesBufferString.find("\\t", 0);
            while (findResult != -1)
            {
            	rulesBufferString.replace(findResult, 2, "\t");
            	findResult = rulesBufferString.find("\\t", 0);
            }

			int paramCounter = 0;
			int functionNameIndex = rulesBufferString.find(':');
			string functionName = rulesBufferString.substr(0, functionNameIndex);
			int param1Index = rulesBufferString.find('@', functionNameIndex+1);
			int param2Index = rulesBufferString.find('@', param1Index+1);
			string param1Text, param2Text;
			if (param1Index != -1) {
				param1Text = rulesBufferString.substr(functionNameIndex+1, (param1Index-functionNameIndex-1));
				if (param1Text != "")
					paramCounter++;
			}
			if ((param1Index != -1) && (param2Index != -1)) {
				param2Text = rulesBufferString.substr(param1Index+1, (param2Index-param1Index-1));
				paramCounter++;
			}


			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if (functionName == "Replace" && paramCounter == 2) 
			{			
				findResult = bufferString.find(param1Text);
				while (findResult != -1) 
				{
					bufferString.replace(findResult, param1Text.length(), param2Text); 
					findResult = bufferString.find(param1Text);
				}			
			}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if (functionName == "ReplaceWithFile" && paramCounter <= 2) //==1 20200410
			{
				if ((param2Text[0] != 'N') || expandAbbr) //20200410  allways replace Y/N
				for (int g = 0; g < abbSizes[currentFileBuffer]; g++)
				{					
					findResult = bufferString.find(abbLists[currentFileBuffer][g]);
					while (findResult != -1) 
					{
						bufferString.replace(findResult, strlen(abbLists[currentFileBuffer][g]), abbListsSubstitutions[currentFileBuffer][g]); 
						findResult = bufferString.find(abbLists[currentFileBuffer][g]);
					}		
					
				}
				currentFileBuffer++;
			}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			else if ((functionName == "RomanNumerals") && (paramCounter == 2) && expandAbbr) //expandAbbr 20200410
			{
				findResult = bufferString.find(param1Text);
				while (findResult != -1) 
				{
					int findResult2 = bufferString.find(param2Text);
					if (findResult2 != -1)
					{
						string strToReplace = "\nPI^RMAS"; //20200410
						int findResultDif = findResult2-findResult;
						if (param1Text[1] == 'V')
						{
							findResultDif = findResult-findResult2;
							strToReplace = "\nPEN~KTAS"; //20200410
						}

						if ((findResultDif < 500) && (findResultDif > 0))
						{
							bufferString.replace(findResult, param1Text.length(), strToReplace); 
						}
					}
					findResult = bufferString.find(param1Text, findResult+1);
				}
			}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			else if (functionName == "DigitsPattern" && (paramCounter == 1 || paramCounter == 2)) 
			{				
				findResult = param1Text.find('(');
				string patternSeed = param1Text.substr(0, findResult);				
				int patternSeedLength = patternSeed.length();
				int patternFinish = 0;
				int patternStart = bufferString.find(patternSeed, patternFinish);
				while (patternStart != -1)
				{					
					string patternString = param1Text.substr(patternSeedLength);
					patternFinish = patternStart+patternSeedLength;
					string filledPattern = "";
					bool isPatternFits = true;  //20170105
					int foundSymbolsNum = 0;
					for (int z = patternStart+patternSeedLength; z < bufferString.length(); z++)
					{
						if (patternString == "")
							break;

						int currentGroupFinish = patternString.find(')',2);  //,2 20191031
						string currentGroupString = patternString.substr(1, currentGroupFinish-1);
						patternString = patternString.substr(currentGroupFinish+1);
						int maxSymbolsNumStart = currentGroupString.find('[');
						bool isFound = false;
						for (int u = 0; u < maxSymbolsNumStart; u++)
						{
							//skaitmuo, perskaitomas paraidziui
							if ((currentGroupString[u] == 'D') && (digitsList.find(bufferString.at(z)) != -1))
							{
								isFound = true;
								filledPattern += currentGroupString[u];
								break;
							}
							//skaitmuo, paliekamas
							else if ((currentGroupString[u] == 'S') && (digitsList.find(bufferString.at(z)) != -1))
							{
								isFound = true;
								filledPattern += currentGroupString[u];
								break;
							}
							//didzioji raide, perskaitoma paraidziui
							else if ((currentGroupString[u] == 'L') && (/*lettersList*/ capitalLettersList.find(bufferString.at(z)) != -1))
							{
								isFound = true;
								filledPattern += currentGroupString[u];
								break;
							}
							//raide, paliekama
							else if ((currentGroupString[u] == 'l') && (lettersList.find(bufferString.at(z)) != -1))
							{
								isFound = true;
								filledPattern += currentGroupString[u];
								break;
							}
							//zodzio pabaigos simbolis, paliekamas
							else if ((currentGroupString[u] == 'W') && (wordSeparatorsList.find(bufferString.at(z)) != -1))
							{
								isFound = true;
								filledPattern += currentGroupString[u];
								break;
							}
							//tarpas, pasalinamas
							else if ((currentGroupString[u] == 'x') && (bufferString.at(z) == ' '))
							{
								isFound = true;
								filledPattern += currentGroupString[u];
								break;
							}
							else if (bufferString.at(z) == currentGroupString[u])
							{
								isFound = true;
								filledPattern += currentGroupString[u];
								break;
							}
						}
						if (isFound == true)
						{
							foundSymbolsNum++;
							patternFinish = z;
							int minSymbolsNum, maxSymbolsNum;
							string tmpBuf = currentGroupString.substr(maxSymbolsNumStart+1, currentGroupString.length()-maxSymbolsNumStart-2);
							sscanf(tmpBuf.c_str(), "%d-%d", &minSymbolsNum, &maxSymbolsNum);
							maxSymbolsNum--;
							if (maxSymbolsNum > 0)
							{
								tmpBuf = currentGroupString.substr(0, maxSymbolsNumStart);
								char tmpBufChar[256];
								sprintf(tmpBufChar, "(%s[%d-%d])", tmpBuf.c_str(), minSymbolsNum, maxSymbolsNum);
								patternString = tmpBufChar + patternString;
							}
							else
								foundSymbolsNum = 0;
						}
						else
						{
							int minSymbolsNum, maxSymbolsNum;
							string tmpBuf = currentGroupString.substr(maxSymbolsNumStart+1, currentGroupString.length()-maxSymbolsNumStart-2);
							sscanf(tmpBuf.c_str(), "%d-%d", &minSymbolsNum, &maxSymbolsNum);

							if (foundSymbolsNum >= minSymbolsNum)
							{
								foundSymbolsNum = 0; //20170126 ????????????????????????????
								z--; 
								continue;
							}
							else
							{isPatternFits = false; break;}  //20170105
						}
					}

					//Read by letter from patternStart to patternFinish
					if(isPatternFits) //20170105
					if ((patternFinish - (patternStart+patternSeedLength)) > 0)
					{
						bool addPauses = false;
						
						if (param2Text == "addPauses")
							addPauses = true;

						int wordStartIndex = (patternStart+patternSeedLength);
						int wordEndIndex = patternFinish;
						int patternIndex = 0;
						for (int w = wordStartIndex; w <= wordEndIndex; w++)
						{								
							if ((addPauses == true) && (bufferString.at(w) == ' ') && (wordSeparatorsList.find(bufferString.at(w-1)) != -1)) //20191031
							{
								bufferString.replace(w-1, 1, 1, '.');
							}

							if ((filledPattern[patternIndex] == 'L') || (filledPattern[patternIndex] == 'D'))
							{
								char * symbolText = SimbPavad(bufferString.at(w));
								int symbolTextLength = strlen(symbolText);
								if (symbolTextLength != 0)
								{
									if ((w > 0) && (bufferString.at(w-1) != ' ') && (bufferString.at(w-1) != '\n') 
										&& (bufferString.at(w-1) != '\r') && (bufferString.at(w-1) != '-')) //20170127 tais
									{
										bufferString.insert(w, 1, ' ');
										wordEndIndex++;
										w++;
									}
									bufferString.replace(w, 1, symbolText);
									wordEndIndex += (symbolTextLength-1);
									w += (symbolTextLength-1);
									if (w < (wordEndIndex-1))
									{
										if((filledPattern[patternIndex] == 'L') && (filledPattern[patternIndex + 1] == 'L'))
											bufferString.insert(w+1, (char*)"-");
										else
											bufferString.insert(w+1, (char*)" ");
										wordEndIndex++;
										w++;
									}
								}
								else
								{
									bufferString.erase(w, 1);
									wordEndIndex--;
									w--;
								}
							}
							else if(filledPattern[patternIndex] == 'x')
							{
								bufferString.erase(w, 1);
								wordEndIndex--;
								w--;
							}

							patternIndex++;
						}
						patternFinish = wordEndIndex; //20170126
					}

					if(patternSeedLength > 0) //20170127 taisyta 5 eil
						patternStart = bufferString.find(patternSeed, patternFinish);
					else
						patternStart = bufferString.find_first_of(wordSeparatorsList, patternFinish) + 1;
					if(patternStart == 0) break;
				}
			}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			else if (functionName == "ReadByLetter" && (paramCounter == 1 || paramCounter == 2))
			{
				
				/*if (param1Text.find("Num[") != -1) //20200410 Sis gabalas nebenaudojamas, funkcionalumas perkeltas i DigitsPattern
				{
					string patternString = param1Text;
					string patternStringParams = param1Text;
					int numParams = 0;
					int minRange[32];
					int maxRange[32];

					findResult = patternString.find("Num[");
					while (findResult != -1)
					{
						int findResultEnd = patternString.find("]", findResult);
						string range = patternString.substr(findResult+4, (findResultEnd-findResult-4));
						int digitsNum = range.find("-", 0);
						patternString.replace(findResult, (findResultEnd-findResult+1), digitsNum, 'D');
						patternStringParams.replace(findResult, (findResultEnd-findResult+1), digitsNum, numParams);

						minRange[numParams] = atoi(range.substr(0, digitsNum).c_str());
						maxRange[numParams] = atoi(range.substr(digitsNum+1, range.length()-digitsNum).c_str());
						numParams++;

						findResult = patternString.find("Num[");
					}

					for (int k = 0; k < bufferString.length(); k++)
					{
						int patternLength = patternString.length();
						string str = bufferString.substr(k, patternLength);
						bool is_pattern_found = true;
						string paramsText[32];
						for (int i = 0; i < patternString.length(); i++)
						{
							if (patternString[i] == 'D')
							{
								if ((str[i] < 0x30) || (str[i] > 0x39)) {is_pattern_found = false; break; }
								paramsText[(int)patternStringParams[i]] += str[i];
							}
							else if (patternString[i] == '?')
							{
								if (lettersList.find(str[i]) == -1) {is_pattern_found = false; break; }
							}
							else if (patternString[i] == '*') {} //Do nothing 
							else if (patternString[i] != str[i]) {is_pattern_found = false; break; }
						}
						
						if (is_pattern_found == true)
						{
							for (int asd = 0; asd < numParams; asd++)
							{
								if (paramsText[asd] == "") {is_pattern_found = false; break; }

								int ppp = atoi(paramsText[asd].c_str());
								if (ppp < minRange[asd]) {is_pattern_found = false; break; }
								if (ppp > maxRange[asd]) {is_pattern_found = false; break; }
							}
						}

						if (is_pattern_found == true)
						{
							bool addPauses = false;
							
							if (param2Text == "addPauses")
								addPauses = true;


							int wordStartIndex = k;
							int wordEndIndex = k + patternLength;
							for (int w = wordStartIndex; w < wordEndIndex; w++)
							{								
								if ((addPauses == true) && (bufferString.at(w) == ' '))
								{
									bufferString.replace(w-1, 1, 1, '.');
									wordEndIndex++;
									continue;
								}


								if (digitsList.find(bufferString.at(w))!=-1)
								{
									char * symbolText = SimbPavad(bufferString.at(w));
									int symbolTextLength = strlen(symbolText);
									if (symbolTextLength != 0)
									{
										if ((w > 0) && (bufferString.at(w-1) != ' '))
										{
											bufferString.insert(w, 1, ' ');
											w++;
										}
										bufferString.replace(w, 1, symbolText);
										wordEndIndex += (symbolTextLength-1);
										w += (symbolTextLength-1);
										if (w < (wordEndIndex-1))
										{
											bufferString.insert(w+1, (char*)" ");
											wordEndIndex++;
											w++;
										}
									}
									else
									{
										bufferString.erase(w, 1);
										wordEndIndex--;
										w--;
									}
								}
							}
						}
					}
				}
/////////////////////////////////////////Nauja realizacija 20200415///////////////////////////////////////////////
				else*/ if ((param1Text[0] == '{') && (param1Text[param1Text.length() - 1] == '}')) //20200415 Nauja realizacija
				{
					if (skyrybos_rezimas > 1)
					{
						string readByLetterSymbolsList = param1Text.substr(1, param1Text.length() - 2);
						findResult = bufferString.find_first_of(readByLetterSymbolsList, 0);
						while (findResult != -1)
						{
							char * symbolText = SimbPavad(bufferString.at(findResult));
							int symbolTextLength = strlen(symbolText);

							if ((findResult > 0) && (bufferString.at(findResult - 1) != ' '))
							{
								bufferString.insert(findResult, (char*)" ");
								findResult++;
							}
							if ((findResult < (bufferString.length() - 1)) && (bufferString.at(findResult + 1) != ' '))
								bufferString.insert(findResult + 1, (char*)" ");

							if (symbolTextLength != 0)
								{
									bufferString.replace(findResult, 1, symbolText); //cia replace
									findResult += symbolTextLength;
								}
								else bufferString.erase(findResult, 1);

							findResult = bufferString.find_first_of(readByLetterSymbolsList, findResult);
						}
					}
					if (skyrybos_rezimas > 2)
					{
						//Isskaidom param2Text pagal skirtuka #
						int param1IndexA = param2Text.find('#', 0); //#
						int param2IndexA = param2Text.length();
						if (param1IndexA != -1) {
							param1Text = param2Text.substr(0, param1IndexA);
						}
						if ((param1IndexA != -1) && (param2IndexA != -1)) {
							param2Text = param2Text.substr(param1IndexA + 1, (param2IndexA - param1IndexA - 1));
						}

						string readByLetterSymbolsList = param1Text.substr(1, param1Text.length() - 2);
						findResult = bufferString.find_first_of(readByLetterSymbolsList, 0);
						while (findResult != -1)
						{
							char * symbolText = SimbPavad(bufferString.at(findResult));
							int symbolTextLength = strlen(symbolText);

							if ((findResult > 0) && (bufferString.at(findResult - 1) != ' '))
							{
								bufferString.insert(findResult, (char*)" ");
								findResult++;
							}
							if ((findResult < (bufferString.length() - 1)) && (bufferString.at(findResult + 1) != ' '))
								bufferString.insert(findResult + 1, (char*)" ");

							if (symbolTextLength != 0)
							{
								bufferString.insert(findResult, symbolText); //cia insert
								findResult += symbolTextLength + 1;
							}
							else bufferString.erase(findResult, 1);

							findResult = bufferString.find_first_of(readByLetterSymbolsList, findResult);
						}
					}
					if (skyrybos_rezimas > 3)
					{
						string readByLetterSymbolsList = param2Text.substr(1, param2Text.length() - 2); //param2Text
						findResult = bufferString.find_first_of(readByLetterSymbolsList, 0);
						while (findResult != -1)
						{
							char * symbolText = SimbPavad(bufferString.at(findResult));
							int symbolTextLength = strlen(symbolText);

							if ((findResult > 0) && (bufferString.at(findResult - 1) != ' '))
							{
								bufferString.insert(findResult, (char*)" ");
								findResult++;
							}
							if ((findResult < (bufferString.length() - 1)) && (bufferString.at(findResult + 1) != ' '))
								bufferString.insert(findResult + 1, (char*)" ");

							if (symbolTextLength != 0)
							{
								bufferString.insert(findResult, symbolText); //cia insert
								findResult += symbolTextLength + 1;
							}
							else bufferString.erase(findResult, 1);

							findResult = bufferString.find_first_of(readByLetterSymbolsList, findResult);
						}
					}
				}
//Ligi 20200415 buvusi realizacija
				/*else*/ /*if ((param1Text[0] == '{') && (param1Text[param1Text.length()-1] == '}'))//Stress symbols (~^`)
				{					
					string readByLetterSymbolsList = param1Text.substr(1, param1Text.length()-2);//"~^`";
					findResult = bufferString.find_first_of(readByLetterSymbolsList, 0);
					while (findResult != -1)
					{
						bool isToBeSkipped = false;
						if (param2Text == "checkForNoSpaceAfter")
						{
							if (
								(findResult == (bufferString.length()-1)) || 
								(bufferString.at(findResult+1) == ' ') || 
								(bufferString.at(findResult+1) == '\r') || 
								(bufferString.at(findResult+1) == '\n')	
							   )
							{
								isToBeSkipped = true;
								findResult++;
							}
						}
						
						if (isToBeSkipped == false)
						{
							char * symbolText = SimbPavad(bufferString.at(findResult));
							int symbolTextLength = strlen(symbolText);
												
							if ((findResult > 0) && (bufferString.at(findResult-1) != ' '))
							{
								bufferString.insert(findResult, (char*)" ");
								findResult++;
							}
							if ((findResult < (bufferString.length()-1)) && (bufferString.at(findResult+1) != ' '))
								bufferString.insert(findResult+1, (char*)" ");

							if ((param2Text == "") || (param2Text == "checkForNoSpaceAfter"))
							{
								if (symbolTextLength != 0)
								{
									bufferString.replace(findResult, 1, symbolText);
									findResult+=symbolTextLength;
								}
								else bufferString.erase(findResult, 1);
							}
							else if (param2Text == "LeaveOriginalDup")
							{
								if (symbolTextLength != 0)
								{
									bufferString.insert(findResult+1, symbolText);
									findResult++;
									findResult+=symbolTextLength;
								}
							}
						}

						findResult = bufferString.find_first_of(readByLetterSymbolsList, findResult);
					}
				}*/
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				else if (param1Text == "WordNoVowels")
				{
					int wordStartIndex = 0;
					int wordEndIndex = bufferString.find_first_of(wordSeparatorsList, wordStartIndex);
					string vowelsList = "aeiyouàæëáøûAEIYOUÀÆËÁØÛ";

					while (wordEndIndex != -1)
					{
						int wordLength = (wordEndIndex-wordStartIndex);
						if (wordLength > 0)
						{
							bool isWordNoVowels = true;
							for (int w = wordStartIndex; w < wordEndIndex; w++)
							{
								if (vowelsList.find(bufferString.at(w)) != -1)
								{
									isWordNoVowels = false;
									break;
								}
							}

							if (isWordNoVowels == true)
							{
								for (int w = wordStartIndex; w < wordEndIndex; w++)
								{
									char * symbolText = SimbPavad(bufferString.at(w));
									int symbolTextLength = strlen(symbolText);
									if (symbolTextLength != 0)
									{
										bufferString.replace(w, 1, symbolText);
										wordEndIndex += (symbolTextLength-1);
										w += (symbolTextLength-1);
										if (w < (wordEndIndex-1))
										{
											bufferString.insert(w+1, (char*)"-"); //santrumpas skaidom skiemenimis
											wordEndIndex++;
											w++;
										}
									}
									else
									{
										bufferString.erase(w, 1);
										wordEndIndex--;
										w--;
									}
								}
							}
						}
						wordStartIndex = wordEndIndex+1;
						wordEndIndex = bufferString.find_first_of(wordSeparatorsList, wordStartIndex);
					}
				}
			}			
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			else if ((functionName == "Date") && (paramCounter == 1) && (skaiciu_rezimas == 4) && expandAbbr) //(skaiciu_rezimas == 4) 20200410, expandAbbr 20201028
			{
				int MonthVar = 1;
				if (param1Text.find("{MONTHS}") != -1)
				{
					MonthVar = 12;
				}
				for (int mv = 0; mv < MonthVar; mv++)
				{
					string patternString = param1Text;
					int zxc;
					if (MonthVar == 12)
					{
						zxc = patternString.find("{MONTHS}");
						if (zxc != -1)
							patternString.replace(zxc, 8, months[mv]); 
					}
					for (int k = 0; k < bufferString.length(); k++)
					{
						int patternLength = patternString.length();
						string str = bufferString.substr(k, patternLength);
						if (str.length() != patternLength) break;
								string strNormalized = str;
								if (MonthVar == 12)
								{
									for (int ss = zxc; ss < zxc+months[mv].length(); ss++)
									{
										switch (strNormalized[ss])
										{
										case 'à':
										case 'è':
										case 'æ':
										case 'ë':
										case 'á':
										case 'ð':
										case 'ø':
										case 'û':
										case 'þ':
											strNormalized[ss]-=0x20;
											break;
										default:
											strNormalized[ss] = toupper(strNormalized[ss]);
											break;
										}
									}
								}
						bool is_pattern_found = true;
						string yearStr, monthStr, dayStr;
						for (int i = 0; i < patternString.length(); i++)
						{
							if (patternString[i] == 'Y')
							{
								if ((strNormalized[i] < 0x30) || (strNormalized[i] > 0x39)) {is_pattern_found = false; break; }
								yearStr += strNormalized[i];
							}
							else if (patternString[i] == 'M')
							{
								if ((strNormalized[i] < 0x30) || (strNormalized[i] > 0x39)) {is_pattern_found = false; break; }
								monthStr += strNormalized[i];
							}
							else if (patternString[i] == 'Q')	//20161230 Pakeiciau is D i Q, nes nesuveikia balandzio ir gruodzio
							{
								if ((strNormalized[i] < 0x30) || (strNormalized[i] > 0x39)) {is_pattern_found = false; break; }
								dayStr += strNormalized[i];
							}
							else if (patternString[i] == '?')
							{
								if (isalpha(strNormalized[i]) == 0) {is_pattern_found = false; break; }
							}
							else if (patternString[i] == '*') {} //Do nothing 
							else if (patternString[i] != strNormalized[i]) {is_pattern_found = false; break; }
						}
						int y = 0; int m = 0; int d = 0;					
						if (is_pattern_found == true)
						{
							y = atoi(yearStr.c_str());
							if (MonthVar == 12)
							{
								m = mv+1;
							}
							else
								m = atoi(monthStr.c_str());
							d = atoi(dayStr.c_str());
							if (y <= 0) is_pattern_found = false;
							else if ((m <= 0) || (m >= 13)) is_pattern_found = false;
							else if ((d <= 0) || (d >= 32)) is_pattern_found = false;
						}
						if (is_pattern_found == true)
						{
							int mode = 0;
							if (str.find(" m.") != -1)
								mode = 1;
							char bufferTmp[256];
							if (expandDate(y,m,d, mode, bufferTmp) == -1)
							{
							}
							else
							{

								if ( (k > 0) && (wordSeparatorsList.find(bufferString.at(k-1)) == -1) )
								{
									bufferString.insert(k, (char*)" ");
									k++;
								}
								if ( ((k+patternLength) < bufferString.length()) && (wordSeparatorsList.find(bufferString.at((k+patternLength))) == -1) )
								{
									bufferString.insert((k+patternLength), (char*)" ");
								}

								bufferString.replace(k, patternLength, bufferTmp);
							}
						}
					}
				}
			}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			else if ((functionName == "Time") && (paramCounter == 1) && (skaiciu_rezimas == 4) && expandAbbr) //(skaiciu_rezimas == 4) 20200410, expandAbbr 20201028
			{
				int z, h=0, m=0, mode=0;
				string hourStr, minStr;
				char bufferTmp[256];
				int silg = param1Text.length();

				if(param1Text.at(1) == ':') //H:MM
				{
					for (z = 0; z < bufferString.length() - silg; z++)
						if(((z == 0) || (digitsList.find(bufferString.at(z-1)) == -1)) &&
							(digitsList.find(bufferString.at(z)) != -1) && 
							(bufferString.at(z+1) == ':') &&
							(digitsList.find(bufferString.at(z+2)) != -1) && (digitsList.find(bufferString.at(z+3)) != -1) &&
							((z == bufferString.length() - silg - 1) || (digitsList.find(bufferString.at(z+4)) == -1)))
						{
							hourStr = bufferString.substr(z, 1);
							h = atoi(hourStr.c_str());
							minStr = bufferString.substr(z+2, 2);
							m = atoi(minStr.c_str());
							if (expandTime(h, m, -1, mode, bufferTmp) == 0)
							{
								if((z < bufferString.length() - silg -1) && (bufferString.at(z+4) == '-')) //"-" keiciam ". "
									bufferString.replace(z+4, 1, (char*)". ");
								bufferString.replace(z, param1Text.length(), bufferTmp);
							}
						}
				}
				else //HH:MM
				{
					for (z = 0; z < bufferString.length() - silg; z++)
						if(((z == 0) || (digitsList.find(bufferString.at(z-1)) == -1)) &&
							(digitsList.find(bufferString.at(z)) != -1) && (digitsList.find(bufferString.at(z+1)) != -1) && 
							(bufferString.at(z+2) == ':') &&
							(digitsList.find(bufferString.at(z+3)) != -1) && (digitsList.find(bufferString.at(z+4)) != -1) &&
							((z == bufferString.length() - silg - 1) || (digitsList.find(bufferString.at(z+5)) == -1)))
						{
							hourStr = bufferString.substr(z, 2);
							h = atoi(hourStr.c_str());
							minStr = bufferString.substr(z+3, 2);
							m = atoi(minStr.c_str());
							if (expandTime(h, m, -1, mode, bufferTmp) == 0)
							{
								if((z < bufferString.length() - silg -1) && (bufferString.at(z+5) == '-')) //"-" keiciam ". "
									bufferString.replace(z+5, 1, (char*)". ");
								bufferString.replace(z, param1Text.length(), bufferTmp);
							}
						}
				}
			}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			else if (functionName == "AbbSeparateWord" && paramCounter <= 2) //==1 20200410
			{
				if ((param2Text[1] != 'N') || expandAbbr) //20200410	"RN" "RY" "LN" "LY" - Remove/LeaveDot, allways expand Y/N
				for (int g = 0; g < abbSizes[currentFileBuffer]; g++)
				{
					findResult = bufferString.find(abbLists[currentFileBuffer][g], 0);
					while (findResult != -1)
					{						
						bool isSeparateWord = true;

						if (((findResult-1) >= 0) && 
							(wordSeparatorsList.find(bufferString.at(findResult-1)) == -1))
								isSeparateWord = false;

						int abbLength = strlen(abbLists[currentFileBuffer][g]); //20200410
						if (((findResult + abbLength) <= (bufferString.length() - 1)) &&
							(wordSeparatorsList.find(bufferString.at(findResult + abbLength)) == -1) &&
							(abbLists[currentFileBuffer][g][abbLength - 1] != '.')) //Jei santrumpa baigiasi '.', tai ir yra zodzio pabaiga 20200410
							isSeparateWord = false;

						if (isSeparateWord == true)
						{
							bool isLeaveSep = false;
//							if (abbListsIsWithSep[currentFileBuffer][g] == 1)
							if (abbLists[currentFileBuffer][g][abbLength - 1] == '.') //20200410
							{
								if (((findResult + abbLength + 1) < bufferString.length()) && //sugrieztinti tikrinima !!!!!!!!!!!
									(bufferString.at(findResult + abbLength) != ' '))
								{
									bufferString.insert(findResult + abbLength, (char*)" ");
								}
								if (((findResult + abbLength + 2) < bufferString.length()) && //sugrieztinti tikrinima !!!!!!!!!!!
									(bufferString.at(findResult + abbLength) == ' ') &&
									(capitalLettersList.find(bufferString.at(findResult + abbLength + 1))!=-1) && // V. Pavarde
									((smallLettersList.find(bufferString.at(findResult + abbLength + 2)) != -1) || // Jei "val. DU", tai nelaikom sakinio pradzia
										bufferString.at(findResult + abbLength + 2) == ' ') &&						// Jei "val. O saule", tai laikom sakinio pradzia
										((findResult + abbLength + 3) < bufferString.length()) &&
										(smallLettersList.find(bufferString.at(findResult + abbLength + 3)) != -1))
								{
									if (param2Text[0] != 'R') // "RemoveDot" "LeaveDot"
										isLeaveSep = true;
								}
								if (bufferString.at(findResult + abbLength) == '\n') //20200415
									isLeaveSep = true;
							}

							if (isLeaveSep == true)
							{
								bufferString.replace(findResult, strlen(abbLists[currentFileBuffer][g])-1, abbListsSubstitutions[currentFileBuffer][g]);
								abbLength = strlen(abbListsSubstitutions[currentFileBuffer][g]) + 1;
							}
							else
							{
								bufferString.replace(findResult, strlen(abbLists[currentFileBuffer][g]), abbListsSubstitutions[currentFileBuffer][g]);
								abbLength = strlen(abbListsSubstitutions[currentFileBuffer][g]);
							}
						}
						findResult = bufferString.find(abbLists[currentFileBuffer][g], findResult+abbLength+1);				
					}			
				}
				currentFileBuffer++;
			}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			else if (functionName == "Numbers" && paramCounter == 0)
			{
				//Digits	
//{+-}{1234567890}{,}{1234567890}{%$\x80\xA3} \x80 - euras, \xA3 - svaras
//ilgiausias skaicius +777777777777,777777777777% uzima 444 simb.
//ilgesni skaiciai sakomi po skaitmeni, o ilgiausio skaitmens ilgis 9. 
//440 turetu pakakti 44 zenklu skaiciui, imkim 512

				int lastDigitIndex = bufferString.find_first_of(digitsList, 0);
				while (lastDigitIndex != -1)
				{
					int digitsWordStartIndex = lastDigitIndex-1;
					int digitsWordEndIndex = lastDigitIndex+1;
					if ((digitsWordStartIndex >= 0) && ((bufferString.at(digitsWordStartIndex) == '+') || (bufferString.at(digitsWordStartIndex) == '-'))) // "-" ???
						digitsWordStartIndex--;
					while ((digitsWordEndIndex < bufferString.length()) && (digitsList.find(bufferString.at(digitsWordEndIndex)) != -1))
						if ((skaiciu_rezimas < 4) && (digitsWordEndIndex - lastDigitIndex >= skaiciu_rezimas)) {	break; } else //20200321
						digitsWordEndIndex++;
					if (skaiciu_rezimas == 4) //20200321
					{
						if ((digitsWordEndIndex < bufferString.length() - 1) && (bufferString.at(digitsWordEndIndex) == ',') && (digitsList.find(bufferString.at(digitsWordEndIndex + 1)) != -1))
							digitsWordEndIndex += 2;
						while ((digitsWordEndIndex < bufferString.length()) && (digitsList.find(bufferString.at(digitsWordEndIndex)) != -1))
							digitsWordEndIndex++;
					}
//					if ((digitsWordEndIndex < bufferString.length()) && ((bufferString.at(digitsWordEndIndex) == '%') || (bufferString.at(digitsWordEndIndex) == '$')
//						|| (bufferString.at(digitsWordEndIndex) == '\x80') || (bufferString.at(digitsWordEndIndex) == '\xA3')))
//						digitsWordEndIndex++;
					if(digitsWordEndIndex > digitsWordStartIndex + 44) digitsWordEndIndex = digitsWordStartIndex + 44; //apsauga kad tilptu

					string singleWord = bufferString.substr(digitsWordStartIndex+1, (digitsWordEndIndex-digitsWordStartIndex-1));

					const char *eilute = bufferString.c_str();
					int linksnis, gimine;
					if((eilute[digitsWordEndIndex] == '-') &&				//uz 25-ojoje
						strchr("aàbcèdeæëfghiáyjklmnoprsðtuøûvzþxwqAÀBCÈDEÆËFGHIÁYJKLMNOPRSÐTUØÛVZÞXWQ", eilute[digitsWordEndIndex + 1]))
						{
						linksnis = VardL;
						gimine = VyrG;
						priesdfound = 0;
						}
					else
						{
						linksnis = getLinksnis(eilute, digitsWordStartIndex, digitsWordEndIndex);
						gimine = getmatvnttype(eilute, digitsWordEndIndex, matvntmotkiek, matvntmot);
						if (!expandAbbr) gimine = VyrG;	//Pijus 20200915 21 g 21 t
					}

					char bufferTmp[512];
//					if (skaiciu_rezimas == 4) //20200321
						VisasSkaicius(&singleWord[0], bufferTmp, 512, linksnis, gimine);
//					else
//						IsverstiSkEil(&singleWord[0], bufferTmp, 512, VardL, VyrG);

					bufferString.replace(digitsWordStartIndex+1, (digitsWordEndIndex-digitsWordStartIndex-1), bufferTmp);
					digitsWordEndIndex += (strlen(bufferTmp)-(digitsWordEndIndex-digitsWordStartIndex-1));

					if ( (digitsWordStartIndex >= 0) && (wordSeparatorsList.find(bufferString.at(digitsWordStartIndex)) == -1) ) //20170101 >=
					{
						bufferString.insert(digitsWordStartIndex+1, (char*)" ");
						digitsWordEndIndex++;
					}
					if ( (digitsWordEndIndex < (bufferString.length()-1)) && (wordSeparatorsList.find(bufferString.at(digitsWordEndIndex)) == -1) )
					{
						bufferString.insert(digitsWordEndIndex, (char*)" ");
						digitsWordEndIndex++;
					}
							
					lastDigitIndex = bufferString.find_first_of(digitsList, digitsWordEndIndex);
				}
			}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			else if (functionName == "Phrases" && paramCounter == 0)//Phrase boundaries			
			{			
				

				int phraseStartIndex = 0;
				int phraseEndIndex = bufferString.find_first_of(phraseSeparatorsList, phraseStartIndex);
				while (phraseEndIndex != -1)
				{
					if ((phraseEndIndex - phraseStartIndex) <= 120)
					{
						if ( ((bufferString.at(phraseEndIndex) != bruks) && (bufferString.at(phraseEndIndex) != ',')) || 
	
							 ((bufferString.at(phraseEndIndex) == ',') && (((phraseEndIndex - phraseStartIndex) >= 25) && ((phraseEndIndex - phraseStartIndex) <= 120))) ||
	
							 ((bufferString.at(phraseEndIndex) == bruks) && 
							 (phraseEndIndex > 0) && 
							 (phraseEndIndex < (bufferString.length()-1)) && 
							 (bufferString.at(phraseEndIndex+1) == ' ') && 
							 (bufferString.at(phraseEndIndex-1) == ' ') && 
							 (((phraseEndIndex - phraseStartIndex) >= 25) && ((phraseEndIndex - phraseStartIndex) <= 120)))
							)
						{
							if ( (bufferString.at(phraseEndIndex) != '\n') && 
								 ((phraseEndIndex >= (bufferString.length()-1)) || (bufferString.at(phraseEndIndex+1) != '\n'))
								)
							{
								bufferString.insert(phraseEndIndex+1, (char*)"\n");
								phraseEndIndex+=1;					
							}
						}
						else
						{
	
							bufferString.erase(phraseEndIndex, 1);
							phraseEndIndex=phraseStartIndex-1;
						}
					}
					else //if ((phraseEndIndex - phraseStartIndex) >= 120)
					{
						string phraseSecondarySeparatorsList = "[{(]})\"'";
						int r = bufferString.find_first_of(phraseSecondarySeparatorsList, phraseStartIndex+25);
						if ((r > -1) && (r <= phraseStartIndex+120))
						{
							bufferString.insert(r+1, (char*)"\n");
							phraseEndIndex=r+1;		
						}
						else
						{
							string phraseTertiarySeparatorsList[] = {"ir","bei","ar","arba"};
							int r = -1;
							int bestR = bufferString.length();
							int bestI = -1;
							for (int i = 0; i < 4; i++)
							{
								r = bufferString.find(phraseTertiarySeparatorsList[i], phraseStartIndex+55);
								if ((r > -1) && (r < bestR) && (r <= phraseStartIndex+120))
								{
									bool isSeparateWord = true;

									if (((r-1) >= 0) && 
										(wordSeparatorsList.find(bufferString.at(r-1)) == -1))
											isSeparateWord = false;

									if (((r + phraseTertiarySeparatorsList[i].length()) <= (bufferString.length()-1)) && 
										(wordSeparatorsList.find(bufferString.at(r+phraseTertiarySeparatorsList[i].length())) == -1))
											isSeparateWord = false;

									if (isSeparateWord == true)
									{
										bestR = r;
										bestI = i;
									}
								}
							}
							if (bestR != bufferString.length())
							{
								bufferString.insert(bestR, (char*)"\n");
								phraseEndIndex=bestR; 
							}
							else
							{
								int r = bufferString.rfind(' ', phraseStartIndex+120);
								if(r <= phraseStartIndex) {r = bufferString.rfind('-', phraseStartIndex+120);}
								if (r > phraseStartIndex)
								{
									bufferString.insert(r+1, (char*)"\n");
									phraseEndIndex=r+1;	
								}
								else
								{
									bufferString.insert(phraseStartIndex+120, (char*)"\n");
									phraseEndIndex=phraseStartIndex+120;	
								}
							}
						}
					}

					phraseStartIndex = phraseEndIndex+1;
					phraseEndIndex = bufferString.find_first_of(phraseSeparatorsList, phraseStartIndex);
				}

				findResult = bufferString.find_first_of(leadAndTrailSymbolsList, 0);
				while (findResult != -1)
				{
					bufferString.erase(findResult, 1);
					findResult = bufferString.find_first_of(leadAndTrailSymbolsList, 0);
				}
			}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			else if (functionName == "ToUPPERCASE" && paramCounter == 0)
			{
				//ToUPPERCASE
				int s = bufferString.length();
				for (int g = 0; g < s; g++)
				{
					switch (bufferString.at(g))
					{
					case 'à':
					case 'è':
					case 'æ':
					case 'ë':
					case 'á':
					case 'ð':
					case 'ø':
					case 'û':
					case 'þ':
						bufferString.set_at(g, bufferString.at(g)-0x20);
						break;
					default:
						bufferString.set_at(g, toupper(bufferString.at(g)));
						break;
					}
				}
			}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		}
		int retBufferSize = bufferString.length();

		if(retBufferSize > bufferSize) return ERROR_TEXTNORMALIZATION_BUFFER_OVERFLOW; 

		memcpy(retBuffer, bufferString.c_str(), retBufferSize);	
		retBuffer[retBufferSize] = '\0';
	
	return NO_ERR;
}
