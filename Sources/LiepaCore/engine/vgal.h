///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Projektas LIEPA (https://liepa.raðtija.lt)
// Sintezatoriaus komponentas transcrLUSS.dll
// Failas vgal.h
// Autorius dr. Pijus Kasparaitis (pkasparaitis@yahoo.com)
// 2015 08 11
//
///////////////////////////////////////////////////////////////////////////////////////////////////
#define VKS    1   //veiksmazodis
#define DAL    2   //dalyvis
#define PAD    3   //padalyvis
#define PSD    4   //pusdalyvis
#define BENDR  5   //bendratis
#define BUDN   6   //budinys
#define PRV    7   //prieveiksmis

#define ESAML  1   //esamasis laikas
#define BKL    2   //butasis kartinis laikas
#define BDL    3   //butasis dazninis laikas
#define BSL    4   //busimasis laikas
#define BTL    5   //butasis laikas

#define TIESN  1   //tiesiogine nuosaka
#define LIEPN  2   //liepiamoji nuosaka
#define TARN   3   //tariamoji nuosaka

#define VEIKR  1   //veikiamosios rusies
#define NEVR   2   //neveikiamosios rusies
#define REIK   3   //reikiamybes

#define VNS    1   //vienaskaita
#define DGS    2   //daugiskaita
#define V_D    3   //vienaskaita ir daugiskaita

#define VG     1   //vuriskoji gimine
#define MG     2   //moteriskoji gimine
#define VM     3   //vyriskoji arba moteriskoji gimine
#define BG     4   //bevarde gimine

#ifndef _VGAL_H_

// Asmenuociu kodai: A-O 1, A-Ë 2, IA-O 4, IA-Ë 8, I-O 16, O-O 32, O-Ë 64,
// A-* 3, IA-* 12, O-* 96, A-*&O-* 99, *-O 53, *-Ë 74,

struct VeiksmazodziuGalunes{const char *Galune; short KamTipas; char Sangrazine;
                            char Asmenuote; char KircRaide; char Priegaide;
	                        char KircTaisykle; char PriesdTE;
							char KalbDal; char Laikas; char NuosakaRusis;
							char AsmuoLinksnis; char Skaicius;
							char Gimine; char Apibreztumas;} GalMasV[1066] = {
// Ið esamojo laiko kamieno daromø veiksmaþodþio formø galûnës
// 1 Esamasis laikas ir sangraziniai
// A asmenuote
{"U",    0,0, 3, 0, 0,0,0, VKS, ESAML, TIESN, 1, VNS, -1, -1},
{"I",    0,0, 3, 0, 0,0,0, VKS, ESAML, TIESN, 2, VNS, -1, -1},
{"A",    0,0, 3,-1,-1,1,1, VKS, ESAML, TIESN, 3, V_D, -1, -1},
{"EMA",  0,0, 3,-1,-1,1,0, VKS, ESAML, TIESN, 1, DGS, -1, -1},
{"MA",   0,0, 3,-1,-1,1,0, VKS, ESAML, TIESN, 1, DGS, -1, -1},
{"ETA",  0,0, 3,-1,-1,1,0, VKS, ESAML, TIESN, 2, DGS, -1, -1},
{"TA",   0,0, 3,-1,-1,1,0, VKS, ESAML, TIESN, 2, DGS, -1, -1},
{"ISOU", 0,1, 3, 3, 1,0,0, VKS, ESAML, TIESN, 1, VNS, -1, -1},
{"SOU",  0,1, 3, 2, 1,0,0, VKS, ESAML, TIESN, 1, VNS, -1, -1},
{"ISEI", 0,1, 3, 3, 1,0,0, VKS, ESAML, TIESN, 2, VNS, -1, -1},
{"SEI",  0,1, 3, 2, 1,0,0, VKS, ESAML, TIESN, 2, VNS, -1, -1},
{"ISA",  0,1, 3,-1,-1,1,0, VKS, ESAML, TIESN, 3, V_D, -1, -1},
{"SA",   0,1, 3,-1,-1,1,0, VKS, ESAML, TIESN, 3, V_D, -1, -1},
{"SËMA", 0,1, 3,-1,-1,1,0, VKS, ESAML, TIESN, 1, DGS, -1, -1},
{"SËTA", 0,1, 3,-1,-1,1,0, VKS, ESAML, TIESN, 2, DGS, -1, -1},

// IA asmenuote
{"UI",   0,0,12, 0, 0,0,0, VKS, ESAML, TIESN, 1, VNS, -1, -1},
{"I",    0,0,12, 0, 0,0,0, VKS, ESAML, TIESN, 2, VNS, -1, -1},
{"AI",   0,0,12,-1,-1,1,1, VKS, ESAML, TIESN, 3, V_D, -1, -1},
{"EMAI", 0,0,12,-1,-1,1,0, VKS, ESAML, TIESN, 1, DGS, -1, -1},
{"MAI",  0,0,12,-1,-1,1,0, VKS, ESAML, TIESN, 1, DGS, -1, -1},
{"ETAI", 0,0,12,-1,-1,1,0, VKS, ESAML, TIESN, 2, DGS, -1, -1},
{"TAI",  0,0,12,-1,-1,1,0, VKS, ESAML, TIESN, 2, DGS, -1, -1},
{"ISOUI",0,1,12, 3, 1,0,0, VKS, ESAML, TIESN, 1, VNS, -1, -1},
{"SOUI", 0,1,12, 2, 1,0,0, VKS, ESAML, TIESN, 1, VNS, -1, -1},
{"ISEI", 0,1,12, 3, 1,0,0, VKS, ESAML, TIESN, 2, VNS, -1, -1},
{"SEI",  0,1,12, 2, 1,0,0, VKS, ESAML, TIESN, 2, VNS, -1, -1},
{"ISAI", 0,1,12,-1,-1,1,0, VKS, ESAML, TIESN, 3, V_D, -1, -1},
{"SAI",  0,1,12,-1,-1,1,0, VKS, ESAML, TIESN, 3, V_D, -1, -1},
{"SËMAI",0,1,12,-1,-1,1,0, VKS, ESAML, TIESN, 1, DGS, -1, -1},
{"SËTAI",0,1,12,-1,-1,1,0, VKS, ESAML, TIESN, 2, DGS, -1, -1},

// I asmenuote
{"UI",   0,0,16, 0, 0,0,0, VKS, ESAML, TIESN, 1, VNS, -1, -1},
{"I",    0,0,16, 0, 0,0,0, VKS, ESAML, TIESN, 2, VNS, -1, -1},
{"I",    0,0,16,-1,-1,1,1, VKS, ESAML, TIESN, 3, V_D, -1, -1},
{"EMI",  0,0,16,-1,-1,1,0, VKS, ESAML, TIESN, 1, DGS, -1, -1},
{"MI",   0,0,16,-1,-1,1,0, VKS, ESAML, TIESN, 1, DGS, -1, -1},
{"ETI",  0,0,16,-1,-1,1,0, VKS, ESAML, TIESN, 2, DGS, -1, -1},
{"TI",   0,0,16,-1,-1,1,0, VKS, ESAML, TIESN, 2, DGS, -1, -1},
{"ISOUI",0,1,16, 3, 1,0,0, VKS, ESAML, TIESN, 1, VNS, -1, -1},
{"SOUI", 0,1,16, 2, 1,0,0, VKS, ESAML, TIESN, 1, VNS, -1, -1},
{"ISEI", 0,1,16, 3, 1,0,0, VKS, ESAML, TIESN, 2, VNS, -1, -1},
{"SEI",  0,1,16, 2, 1,0,0, VKS, ESAML, TIESN, 2, VNS, -1, -1},
{"ISI",  0,1,16,-1,-1,1,0, VKS, ESAML, TIESN, 3, V_D, -1, -1},
{"SI",   0,1,16,-1,-1,1,0, VKS, ESAML, TIESN, 3, V_D, -1, -1},
{"SËMI", 0,1,16,-1,-1,1,0, VKS, ESAML, TIESN, 1, DGS, -1, -1},
{"SËTI", 0,1,16,-1,-1,1,0, VKS, ESAML, TIESN, 2, DGS, -1, -1},

// O asmenuote
{"UA",   0,0,96, 0, 2,0,0, VKS, ESAML, TIESN, 1, VNS, -1, -1},
{"IA",   0,0,96, 0, 2,0,0, VKS, ESAML, TIESN, 2, VNS, -1, -1},
{"O",    0,0,96,-1,-1,1,1, VKS, ESAML, TIESN, 3, V_D, -1, -1},
{"EMO",  0,0,96,-1,-1,1,0, VKS, ESAML, TIESN, 1, DGS, -1, -1},
{"MO",   0,0,96,-1,-1,1,0, VKS, ESAML, TIESN, 1, DGS, -1, -1},
{"ETO",  0,0,96,-1,-1,1,0, VKS, ESAML, TIESN, 2, DGS, -1, -1},
{"TO",   0,0,96,-1,-1,1,0, VKS, ESAML, TIESN, 2, DGS, -1, -1},
{"ISUA", 0,1,96, 2, 2,0,0, VKS, ESAML, TIESN, 1, VNS, -1, -1},
{"SUA",  0,1,96, 1, 2,0,0, VKS, ESAML, TIESN, 1, VNS, -1, -1},
{"ISIA", 0,1,96, 2, 2,0,0, VKS, ESAML, TIESN, 2, VNS, -1, -1},
{"SIA",  0,1,96, 1, 2,0,0, VKS, ESAML, TIESN, 2, VNS, -1, -1},
{"ISO",  0,1,96,-1,-1,1,0, VKS, ESAML, TIESN, 3, V_D, -1, -1},
{"SO",   0,1,96,-1,-1,1,0, VKS, ESAML, TIESN, 3, V_D, -1, -1},
{"SËMO", 0,1,96,-1,-1,1,0, VKS, ESAML, TIESN, 1, DGS, -1, -1},
{"SËTO", 0,1,96,-1,-1,1,0, VKS, ESAML, TIESN, 2, DGS, -1, -1},

// 2 Liepiamosios nuosakos 3 asmuo
{"EI",    0,0,31, 0, 2,2,1, VKS, -1, LIEPN, 3, V_D, -1, -1},
{"IA",    0,0,96,-1,-1,3,1, VKS, -1, LIEPN, 3, V_D, -1, -1},

// 3 Esamojo laiko padalyvis
{"TNA",   0,0,99,-1,-1,1,0, PAD, ESAML, -1, -1, -1, -1, -1},
{"SITNA", 0,1,99,-1,-1,1,0, PAD, ESAML, -1, -1, -1, -1, -1},
{"TNAI",  0,0,12,-1,-1,1,0, PAD, ESAML, -1, -1, -1, -1, -1},
{"SITNAI",0,1,12,-1,-1,1,0, PAD, ESAML, -1, -1, -1, -1, -1},
{"TNI",   0,0,16,-1,-1,1,0, PAD, ESAML, -1, -1, -1, -1, -1},
{"SITNI", 0,1,16,-1,-1,1,0, PAD, ESAML, -1, -1, -1, -1, -1},

// 4 Esamojo laiko veikiamasis dalyvis
// AO asmenuotes
{"SÀ",          0,0,99, 1, 2,4,0, DAL, ESAML, VEIKR, 1, VNS, VG, 0},
{"À",           0,0,99, 0, 2,4,0, DAL, ESAML, VEIKR, 1, DGS, VG, 0},  // v.g.trumpos gal.

{"SISÀ",        0,1,99,-1,-1,1,0, DAL, ESAML, VEIKR, 1, VNS, VG, 0},
{"ISÀ",         0,1,99,-1,-1,1,0, DAL, ESAML, VEIKR, 1, DGS, VG, 0},  // sangrazines

{"SITNA",       0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 1, VNS, VG, 0},
{"OIÈNA",       0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 2, VNS, VG, 0},    // v.g.
{"MAIÈNA",      0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 3, VNS, VG, 0},
{"ÁTNA",        0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 4, VNS, VG, 0},
{"UIÈNA",       0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 5, VNS, VG, 0},
{"EMAIÈNA",     0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 6, VNS, VG, 0},
{"SYTNA",       0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 1, DGS, VG, 0},
{"ØIÈNA",       0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 2, DGS, VG, 0},
{"SMEITNA",     0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 3, DGS, VG, 0},
{"MEITNA",      0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 3, DGS, VG, 0},
{"SUIÈNA",      0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 4, DGS, VG, 0},
{"SIAIÈNA",     0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 5, DGS, VG, 0},
{"ESOUIÈNA",    0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 6, DGS, VG, 0},
{"SOUIÈNA",     0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 6, DGS, VG, 0},

{"SISYTNA",     0,0,99, 3, 2,4,0, DAL, ESAML, VEIKR, 1, VNS, VG, 1},
{"OJOIÈNA",     0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 2, VNS, VG, 1},  // v.g.ivardziuot.
{"MAJAIÈNA",    0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 3, VNS, VG, 1},
{"ÁJÁTNA",      0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 4, VNS, VG, 1},
{"UJOUIÈNA",    0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 5, VNS, VG, 1},
{"EMAJAIÈNA",   0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 6, VNS, VG, 1},
{"IJEITNA",     0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 1, DGS, VG, 1},
{"ØJØIÈNA",     0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 2, DGS, VG, 1},
{"SMEISEITNA",  0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 3, DGS, VG, 1},
{"MEISEITNA",   0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 3, DGS, VG, 1},
{"SUISOUIÈNA",  0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 4, DGS, VG, 1},
{"SIAISIAIÈNA", 0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 5, DGS, VG, 1},
{"ESOUISOUIÈNA",0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 6, DGS, VG, 1},
{"SOUISOUIÈNA", 0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 6, DGS, VG, 1},

{"ITNA",        0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 1, VNS, MG, 0},
{"SOIÈNA",      0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 2, VNS, MG, 0},    // m.g.
{"IAIÈNA",      0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 3, VNS, MG, 0},
{"ÀIÈNA",       0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 4, VNS, MG, 0},
{"AIÈNA",       0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 5, VNS, MG, 0},
{"EJOIÈNA",     0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 6, VNS, MG, 0},
{"JOIÈNA",      0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 6, VNS, MG, 0},
{"SMOIÈNA",     0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 3, DGS, MG, 0},
{"MOIÈNA",      0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 3, DGS, MG, 0},
{"SAIÈNA",      0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 4, DGS, MG, 0},
{"SIMOIÈNA",    0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 5, DGS, MG, 0},
{"ESOIÈNA",     0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 6, DGS, MG, 0},

{"IJOIÈNA",     0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 1, VNS, MG, 1},
{"SOISOIÈNA",   0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 2, VNS, MG, 1}, // m.g.ivardziuot.
{"IAJAIÈNA",    0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 3, VNS, MG, 1},
{"ÀJÀIÈNA",     0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 4, VNS, MG, 1},
{"AJÀIÈNA",     0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 5, VNS, MG, 1},
{"EJOJOIÈNA",   0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 6, VNS, MG, 1},
{"JOJOIÈNA",    0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 6, VNS, MG, 1},
{"SMOISOIÈNA",  0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 3, DGS, MG, 1},
{"MOISOIÈNA",   0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 3, DGS, MG, 1},
{"SAISÀIÈNA",   0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 4, DGS, MG, 1},
{"SIMOISOIÈNA", 0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 5, DGS, MG, 1},
{"ESOISOIÈNA",  0,0,99,-1,-1,1,0, DAL, ESAML, VEIKR, 6, DGS, MG, 1},

// IA asmenuote
{"SÀI",         0,0,12, 1, 2,4,0, DAL, ESAML, VEIKR, 1, VNS, VG, 0},
{"ÀI",          0,0,12, 0, 2,4,0, DAL, ESAML, VEIKR, 1, DGS, VG, 0},        // v.g.trumpos gal.

{"SISÀI",       0,1,12,-1,-1,1,0, DAL, ESAML, VEIKR, 1, VNS, VG, 0},
{"ISÀI",        0,1,12,-1,-1,1,0, DAL, ESAML, VEIKR, 1, DGS, VG, 0},  // sangrazines

{"SITNAI",      0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 1, VNS, VG, 0},
{"OIÈNAI",      0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 2, VNS, VG, 0},    // v.g.
{"MAIÈNAI",     0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 3, VNS, VG, 0},
{"ÁTNAI",       0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 4, VNS, VG, 0},
{"UIÈNAI",      0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 5, VNS, VG, 0},
{"EMAIÈNAI",    0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 6, VNS, VG, 0},
{"SYTNAI",      0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 1, DGS, VG, 0},
{"ØIÈNAI",      0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 2, DGS, VG, 0},
{"SMEITNAI",    0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 3, DGS, VG, 0},
{"MEITNAI",     0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 3, DGS, VG, 0},
{"SUIÈNAI",     0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 4, DGS, VG, 0},
{"SIAIÈNAI",    0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 5, DGS, VG, 0},
{"ESOUIÈNAI",   0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 6, DGS, VG, 0},
{"SOUIÈNAI",    0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 6, DGS, VG, 0},

{"SISYTNAI",    0,0,12, 3, 2,4,0, DAL, ESAML, VEIKR, 1, VNS, VG, 1},
{"OJOIÈNAI",    0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 2, VNS, VG, 1},  // v.g.ivardziuot.
{"MAJAIÈNAI",   0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 3, VNS, VG, 1},
{"ÁJÁTNAI",     0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 4, VNS, VG, 1},
{"UJOUIÈNAI",   0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 5, VNS, VG, 1},
{"EMAJAIÈNAI",  0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 6, VNS, VG, 1},
{"IJEITNAI",    0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 1, DGS, VG, 1},
{"ØJØIÈNAI",    0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 2, DGS, VG, 1},
{"SMEISEITNAI", 0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 3, DGS, VG, 1},
{"MEISEITNAI",  0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 3, DGS, VG, 1},
{"SUISOUIÈNAI", 0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 4, DGS, VG, 1},
{"SIAISIAIÈNAI",0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 5, DGS, VG, 1},
{"ESOUISOUIÈNAI",0,0,12,-1,-1,1,0,DAL, ESAML, VEIKR, 6, DGS, VG, 1},
{"SOUISOUIÈNAI",0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 6, DGS, VG, 1},

{"ITNAI",       0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 1, VNS, MG, 0},
{"SOIÈNAI",     0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 2, VNS, MG, 0},    // m.g.
{"IAIÈNAI",     0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 3, VNS, MG, 0},
{"ÀIÈNAI",      0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 4, VNS, MG, 0},
{"AIÈNAI",      0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 5, VNS, MG, 0},
{"EJOIÈNAI",    0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 6, VNS, MG, 0},
{"JOIÈNAI",     0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 6, VNS, MG, 0},
{"SMOIÈNAI",    0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 3, DGS, MG, 0},
{"MOIÈNAI",     0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 3, DGS, MG, 0},
{"SAIÈNAI",     0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 4, DGS, MG, 0},
{"SIMOIÈNAI",   0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 5, DGS, MG, 0},
{"ESOIÈNAI",    0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 6, DGS, MG, 0},

{"IJOIÈNAI",    0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 1, VNS, MG, 1},
{"SOISOIÈNAI",  0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 2, VNS, MG, 1}, // m.g.ivardziuot.
{"IAJAIÈNAI",   0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 3, VNS, MG, 1},
{"ÀJÀIÈNAI",    0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 4, VNS, MG, 1},
{"AJÀIÈNAI",    0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 5, VNS, MG, 1},
{"EJOJOIÈNAI",  0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 6, VNS, MG, 1},
{"JOJOIÈNAI",   0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 6, VNS, MG, 1},
{"SMOISOIÈNAI", 0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 3, DGS, MG, 1},
{"MOISOIÈNAI",  0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 3, DGS, MG, 1},
{"SAISÀIÈNAI",  0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 4, DGS, MG, 1},
{"SIMOISOIÈNAI",0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 5, DGS, MG, 1},
{"ESOISOIÈNAI", 0,0,12,-1,-1,1,0, DAL, ESAML, VEIKR, 6, DGS, MG, 1},

// I asmenuote
{"SÁ",          0,0,16, 1, 2,4,0, DAL, ESAML, VEIKR, 1, VNS, VG, 0},
{"Á",           0,0,16, 0, 2,4,0, DAL, ESAML, VEIKR, 1, DGS, VG, 0},        // v.g.trumpos gal.

{"SISÁ",        0,1,16,-1,-1,1,0, DAL, ESAML, VEIKR, 1, VNS, VG, 0},
{"ISÁ",         0,1,16,-1,-1,1,0, DAL, ESAML, VEIKR, 1, DGS, VG, 0},  // sangrazines

{"SITNI",       0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 1, VNS, VG, 0},
{"OIÈNI",       0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 2, VNS, VG, 0},    // v.g.
{"MAIÈNI",      0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 3, VNS, VG, 0},
{"ÁTNI",        0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 4, VNS, VG, 0},
{"UIÈNI",       0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 5, VNS, VG, 0},
{"EMAIÈNI",     0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 6, VNS, VG, 0},
{"SYTNI",       0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 1, DGS, VG, 0},
{"ØIÈNI",       0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 2, DGS, VG, 0},
{"SMEITNI",     0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 3, DGS, VG, 0},
{"MEITNI",      0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 3, DGS, VG, 0},
{"SUIÈNI",      0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 4, DGS, VG, 0},
{"SIAIÈNI",     0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 5, DGS, VG, 0},
{"ESOUIÈNI",    0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 6, DGS, VG, 0},
{"SOUIÈNI",     0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 6, DGS, VG, 0},

{"SISYTNI",     0,0,16, 3, 2,4,0, DAL, ESAML, VEIKR, 1, VNS, VG, 1},
{"OJOIÈNI",     0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 2, VNS, VG, 1},  // v.g.ivardziuot.
{"MAJAIÈNI",    0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 3, VNS, VG, 1},
{"ÁJÁTNI",      0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 4, VNS, VG, 1},
{"UJOUIÈNI",    0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 5, VNS, VG, 1},
{"EMAJAIÈNI",   0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 6, VNS, VG, 1},
{"IJEITNI",     0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 1, DGS, VG, 1},
{"ØJØIÈNI",     0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 2, DGS, VG, 1},
{"SMEISEITNI",  0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 3, DGS, VG, 1},
{"MEISEITNI",   0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 3, DGS, VG, 1},
{"SUISOUIÈNI",  0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 4, DGS, VG, 1},
{"SIAISIAIÈNI", 0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 5, DGS, VG, 1},
{"ESOUISOUIÈNI",0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 6, DGS, VG, 1},
{"SOUISOUIÈNI", 0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 6, DGS, VG, 1},

{"ITNI",        0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 1, VNS, MG, 0},
{"SOIÈNI",      0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 2, VNS, MG, 0},    // m.g.
{"IAIÈNI",      0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 3, VNS, MG, 0},
{"ÀIÈNI",       0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 4, VNS, MG, 0},
{"AIÈNI",       0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 5, VNS, MG, 0},
{"EJOIÈNI",     0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 6, VNS, MG, 0},
{"JOIÈNI",      0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 6, VNS, MG, 0},
{"SMOIÈNI",     0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 3, DGS, MG, 0},
{"MOIÈNI",      0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 3, DGS, MG, 0},
{"SAIÈNI",      0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 4, DGS, MG, 0},
{"SIMOIÈNI",    0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 5, DGS, MG, 0},
{"ESOIÈNI",     0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 6, DGS, MG, 0},

{"IJOIÈNI",     0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 1, VNS, MG, 1},
{"SOISOIÈNI",   0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 2, VNS, MG, 1}, // m.g.ivardziuot.
{"IAJAIÈNI",    0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 3, VNS, MG, 1},
{"ÀJÀIÈNI",     0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 4, VNS, MG, 1},
{"AJÀIÈNI",     0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 5, VNS, MG, 1},
{"EJOJOIÈNI",   0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 6, VNS, MG, 1},
{"JOJOIÈNI",    0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 6, VNS, MG, 1},
{"SMOISOIÈNI",  0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 3, DGS, MG, 1},
{"MOISOIÈNI",   0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 3, DGS, MG, 1},
{"SAISÀIÈNI",   0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 4, DGS, MG, 1},
{"SIMOISOIÈNI", 0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 5, DGS, MG, 1},
{"ESOISOIÈNI",  0,0,16,-1,-1,1,0, DAL, ESAML, VEIKR, 6, DGS, MG, 1},

// 5 Esamojo laiko neveikiamasis dalyvis
// A asmenuote
{"SAMA",      0,0,3,-1,-1,1,0, DAL, ESAML, NEVR, 1, VNS, VG, 0},
{"OMA",       0,0,3,-1,-1,1,0, DAL, ESAML, NEVR, 2, VNS, VG, 0},    // v.g.
{"MAMA",      0,0,3, 1, 1,5,0, DAL, ESAML, NEVR, 3, VNS, VG, 0},
{"ÀMA",       0,0,3,-1,-1,1,0, DAL, ESAML, NEVR, 4, VNS, VG, 0},
{"UMA",       0,0,3,-1,-1,1,0, DAL, ESAML, NEVR, 5, VNS, VG, 0},
{"EMAMA",     0,0,3, 0, 0,5,0, DAL, ESAML, NEVR, 6, VNS, VG, 0},
{"IMA",       0,0,3, 0, 0,5,0, DAL, ESAML, NEVR, 1, DGS, VG, 0},
{"ØMA",       0,0,3, 0, 2,5,0, DAL, ESAML, NEVR, 2, DGS, VG, 0},
{"SMEIMA",    0,0,3, 3, 1,5,0, DAL, ESAML, NEVR, 3, DGS, VG, 0},
{"MEIMA",     0,0,3, 2, 1,5,0, DAL, ESAML, NEVR, 3, DGS, VG, 0},
{"SUMA",      0,0,3,-1,-1,1,0, DAL, ESAML, NEVR, 4, DGS, VG, 0},
{"SIAMA",     0,0,3, 1, 2,5,0, DAL, ESAML, NEVR, 5, DGS, VG, 0},
{"ESOUMA",    0,0,3, 0, 0,5,0, DAL, ESAML, NEVR, 6, DGS, VG, 0},
{"SOUMA",     0,0,3, 1, 2,5,0, DAL, ESAML, NEVR, 6, DGS, VG, 0},

{"SISAMA",    0,0,3, 3, 0,5,0, DAL, ESAML, NEVR, 1, VNS, VG, 1},
{"OJOMA",     0,0,3,-1,-1,1,0, DAL, ESAML, NEVR, 2, VNS, VG, 1}, // v.g.ivardziuot.
{"MAJAMA",    0,0,3, 3, 1,5,0, DAL, ESAML, NEVR, 3, VNS, VG, 1},
{"ÁJÀMA",     0,0,3,-1,-1,1,0, DAL, ESAML, NEVR, 4, VNS, VG, 1},
{"UJOUMA",    0,0,3, 3, 1,5,0, DAL, ESAML, NEVR, 5, VNS, VG, 1},
{"EMAJAMA",   0,0,3, 4, 2,5,0, DAL, ESAML, NEVR, 6, VNS, VG, 1},
{"IJEIMA",    0,0,3, 3, 1,5,0, DAL, ESAML, NEVR, 1, DGS, VG, 1},
{"ØJØMA",     0,0,3, 2, 2,5,0, DAL, ESAML, NEVR, 2, DGS, VG, 1},
{"SMEISEIMA", 0,0,3, 6, 1,5,0, DAL, ESAML, NEVR, 3, DGS, VG, 1},
{"MEISEIMA",  0,0,3, 5, 1,5,0, DAL, ESAML, NEVR, 3, DGS, VG, 1},
{"SUISOUMA",  0,0,3, 5, 1,5,0, DAL, ESAML, NEVR, 4, DGS, VG, 1},
{"SIAISIAMA", 0,0,3, 5, 2,5,0, DAL, ESAML, NEVR, 5, DGS, VG, 1},
{"ESOUISOUMA",0,0,3, 6, 2,5,0, DAL, ESAML, NEVR, 6, DGS, VG, 1},
{"SOUISOUMA", 0,0,3, 5, 2,5,0, DAL, ESAML, NEVR, 6, DGS, VG, 1},

{"AMA",       0,0,3, 0, 0,5,0, DAL, ESAML, NEVR, 1, VNS, MG, 0},
{"SOMA",      0,0,3, 1, 2,5,0, DAL, ESAML, NEVR, 2, VNS, MG, 0},    // m.g.
{"IAMA",      0,0,3,-1,-1,1,0, DAL, ESAML, NEVR, 3, VNS, MG, 0},
{"AMA",       0,0,3,-1,-1,1,0, DAL, ESAML, NEVR, 5, VNS, MG, 0},
{"EJOMA",     0,0,3, 0, 0,5,0, DAL, ESAML, NEVR, 6, VNS, MG, 0},
{"JOMA",      0,0,3, 1, 2,5,0, DAL, ESAML, NEVR, 6, VNS, MG, 0},
{"SOMA",      0,0,3,-1,-1,1,0, DAL, ESAML, NEVR, 1, DGS, MG, 0},
{"SMOMA",     0,0,3, 2, 1,5,0, DAL, ESAML, NEVR, 3, DGS, MG, 0},
{"MOMA",      0,0,3, 1, 1,5,0, DAL, ESAML, NEVR, 3, DGS, MG, 0},
{"SAMA",      0,0,3,-1,-1,1,0, DAL, ESAML, NEVR, 4, DGS, MG, 0},
{"SIMOMA",    0,0,3, 1, 0,5,0, DAL, ESAML, NEVR, 5, DGS, MG, 0},
{"ESOMA",     0,0,3, 0, 0,5,0, DAL, ESAML, NEVR, 6, DGS, MG, 0},

{"IJOMA",     0,0,3, 2, 1,5,0, DAL, ESAML, NEVR, 1, VNS, MG, 1},
{"SOISOMA",   0,0,3, 4, 2,5,0, DAL, ESAML, NEVR, 2, VNS, MG, 1}, // m.g.ivardziuot.
{"IAJAMA",    0,0,3,-1,-1,1,0, DAL, ESAML, NEVR, 3, VNS, MG, 1},
{"ÀJÀMA",     0,0,3,-1,-1,1,0, DAL, ESAML, NEVR, 4, VNS, MG, 1},
{"AJÀMA",     0,0,3, 2, 1,5,0, DAL, ESAML, NEVR, 5, VNS, MG, 1},
{"EJOJOMA",   0,0,3, 4, 2,5,0, DAL, ESAML, NEVR, 6, VNS, MG, 1},
{"JOJOMA",    0,0,3, 3, 2,5,0, DAL, ESAML, NEVR, 6, VNS, MG, 1},
{"SOISOMA",   0,0,3,-1,-1,1,0, DAL, ESAML, NEVR, 1, DGS, MG, 1},
{"SMOISOMA",  0,0,3, 5, 1,5,0, DAL, ESAML, NEVR, 3, DGS, MG, 1},
{"MOISOMA",   0,0,3, 4, 1,5,0, DAL, ESAML, NEVR, 3, DGS, MG, 1},
{"SAISÀMA",   0,0,3, 4, 1,5,0, DAL, ESAML, NEVR, 4, DGS, MG, 1},
{"SIMOISOMA", 0,0,3, 6, 2,5,0, DAL, ESAML, NEVR, 5, DGS, MG, 1},
{"ESOISOMA",  0,0,3, 5, 2,5,0, DAL, ESAML, NEVR, 6, DGS, MG, 1},

{"AMA",       0,0,3,-1,-1,1,0, DAL, ESAML, NEVR, -1, -1, BG, 0},
{"ISAMA",     0,1,3,-1,-1,1,0, DAL, ESAML, NEVR, -1, -1, BG, 0},     // bev.g.

// IA asmenuote
{"SAMAI",     0,0,12,-1,-1,1,0, DAL, ESAML, NEVR, 1, VNS, VG, 0},
{"OMAI",      0,0,12,-1,-1,1,0, DAL, ESAML, NEVR, 2, VNS, VG, 0},    // v.g.
{"MAMAI",     0,0,12, 1, 1,5,0, DAL, ESAML, NEVR, 3, VNS, VG, 0},
{"ÀMAI",      0,0,12,-1,-1,1,0, DAL, ESAML, NEVR, 4, VNS, VG, 0},
{"UMAI",      0,0,12,-1,-1,1,0, DAL, ESAML, NEVR, 5, VNS, VG, 0},
{"EMAMAI",    0,0,12, 0, 0,5,0, DAL, ESAML, NEVR, 6, VNS, VG, 0},
{"IMAI",      0,0,12, 0, 0,5,0, DAL, ESAML, NEVR, 1, DGS, VG, 0},
{"ØMAI",      0,0,12, 0, 2,5,0, DAL, ESAML, NEVR, 2, DGS, VG, 0},
{"SMEIMAI",   0,0,12, 3, 1,5,0, DAL, ESAML, NEVR, 3, DGS, VG, 0},
{"MEIMAI",    0,0,12, 2, 1,5,0, DAL, ESAML, NEVR, 3, DGS, VG, 0},
{"SUMAI",     0,0,12,-1,-1,1,0, DAL, ESAML, NEVR, 4, DGS, VG, 0},
{"SIAMAI",    0,0,12, 1, 2,5,0, DAL, ESAML, NEVR, 5, DGS, VG, 0},
{"ESOUMAI",   0,0,12, 0, 0,5,0, DAL, ESAML, NEVR, 6, DGS, VG, 0},
{"SOUMAI",    0,0,12, 1, 2,5,0, DAL, ESAML, NEVR, 6, DGS, VG, 0},

{"SISAMAI",   0,0,12, 3, 0,5,0, DAL, ESAML, NEVR, 1, VNS, VG, 1},
{"OJOMAI",    0,0,12,-1,-1,1,0, DAL, ESAML, NEVR, 2, VNS, VG, 1}, // v.g.ivardziuot.
{"MAJAMAI",   0,0,12, 3, 1,5,0, DAL, ESAML, NEVR, 3, VNS, VG, 1},
{"ÁJÀMAI",    0,0,12,-1,-1,1,0, DAL, ESAML, NEVR, 4, VNS, VG, 1},
{"UJOUMAI",   0,0,12, 3, 1,5,0, DAL, ESAML, NEVR, 5, VNS, VG, 1},
{"EMAJAMAI",  0,0,12, 4, 2,5,0, DAL, ESAML, NEVR, 6, VNS, VG, 1},
{"IJEIMAI",   0,0,12, 3, 1,5,0, DAL, ESAML, NEVR, 1, DGS, VG, 1},
{"ØJØMAI",    0,0,12, 2, 2,5,0, DAL, ESAML, NEVR, 2, DGS, VG, 1},
{"SMEISEIMAI",0,0,12, 6, 1,5,0, DAL, ESAML, NEVR, 3, DGS, VG, 1},
{"MEISEIMAI", 0,0,12, 5, 1,5,0, DAL, ESAML, NEVR, 3, DGS, VG, 1},
{"SUISOUMAI", 0,0,12, 5, 1,5,0, DAL, ESAML, NEVR, 4, DGS, VG, 1},
{"SIAISIAMAI",0,0,12, 5, 2,5,0, DAL, ESAML, NEVR, 5, DGS, VG, 1},
{"ESOUISOUMAI",0,0,12,6, 2,5,0, DAL, ESAML, NEVR, 6, DGS, VG, 1},
{"SOUISOUMAI",0,0,12, 5, 2,5,0, DAL, ESAML, NEVR, 6, DGS, VG, 1},

{"AMAI",      0,0,12, 0, 0,5,0, DAL, ESAML, NEVR, 1, VNS, MG, 0},
{"SOMAI",     0,0,12, 1, 2,5,0, DAL, ESAML, NEVR, 2, VNS, MG, 0},    // m.g.
{"IAMAI",     0,0,12,-1,-1,1,0, DAL, ESAML, NEVR, 3, VNS, MG, 0},
{"AMAI",      0,0,12,-1,-1,1,0, DAL, ESAML, NEVR, 5, VNS, MG, 0},
{"EJOMAI",    0,0,12, 0, 0,5,0, DAL, ESAML, NEVR, 6, VNS, MG, 0},
{"JOMAI",     0,0,12, 1, 2,5,0, DAL, ESAML, NEVR, 6, VNS, MG, 0},
{"SOMAI",     0,0,12,-1,-1,1,0, DAL, ESAML, NEVR, 1, DGS, MG, 0},
{"SMOMAI",    0,0,12, 2, 1,5,0, DAL, ESAML, NEVR, 3, DGS, MG, 0},
{"MOMAI",     0,0,12, 1, 1,5,0, DAL, ESAML, NEVR, 3, DGS, MG, 0},
{"SAMAI",     0,0,12,-1,-1,1,0, DAL, ESAML, NEVR, 4, DGS, MG, 0},
{"SIMOMAI",   0,0,12, 1, 0,5,0, DAL, ESAML, NEVR, 5, DGS, MG, 0},
{"ESOMAI",    0,0,12, 0, 0,5,0, DAL, ESAML, NEVR, 6, DGS, MG, 0},

{"IJOMAI",    0,0,12, 2, 1,5,0, DAL, ESAML, NEVR, 1, VNS, MG, 1},
{"SOISOMAI",  0,0,12, 4, 2,5,0, DAL, ESAML, NEVR, 2, VNS, MG, 1}, // m.g.ivardziuot.
{"IAJAMAI",   0,0,12,-1,-1,1,0, DAL, ESAML, NEVR, 3, VNS, MG, 1},
{"ÀJÀMAI",    0,0,12,-1,-1,1,0, DAL, ESAML, NEVR, 4, VNS, MG, 1},
{"AJÀMAI",    0,0,12, 2, 1,5,0, DAL, ESAML, NEVR, 5, VNS, MG, 1},
{"EJOJOMAI",  0,0,12, 4, 2,5,0, DAL, ESAML, NEVR, 6, VNS, MG, 1},
{"JOJOMAI",   0,0,12, 3, 2,5,0, DAL, ESAML, NEVR, 6, VNS, MG, 1},
{"SOISOMAI",  0,0,12,-1,-1,1,0, DAL, ESAML, NEVR, 1, DGS, MG, 1},
{"SMOISOMAI", 0,0,12, 5, 1,5,0, DAL, ESAML, NEVR, 3, DGS, MG, 1},
{"MOISOMAI",  0,0,12, 4, 1,5,0, DAL, ESAML, NEVR, 3, DGS, MG, 1},
{"SAISÀMAI",  0,0,12, 4, 1,5,0, DAL, ESAML, NEVR, 4, DGS, MG, 1},
{"SIMOISOMAI",0,0,12, 6, 2,5,0, DAL, ESAML, NEVR, 5, DGS, MG, 1},
{"ESOISOMAI", 0,0,12, 5, 2,5,0, DAL, ESAML, NEVR, 6, DGS, MG, 1},

{"AMAI",      0,0,12,-1,-1,1,0, DAL, ESAML, NEVR, -1, -1, BG, 0},
{"ISAMAI",    0,1,12,-1,-1,1,0, DAL, ESAML, NEVR, -1, -1, BG, 0},     // bev.g.

// I asmenuote
{"SAMI",      0,0,16,-1,-1,1,0, DAL, ESAML, NEVR, 1, VNS, VG, 0},
{"OMI",       0,0,16,-1,-1,1,0, DAL, ESAML, NEVR, 2, VNS, VG, 0},    // v.g.
{"MAMI",      0,0,16, 1, 1,5,0, DAL, ESAML, NEVR, 3, VNS, VG, 0},
{"ÀMI",       0,0,16,-1,-1,1,0, DAL, ESAML, NEVR, 4, VNS, VG, 0},
{"UMI",       0,0,16,-1,-1,1,0, DAL, ESAML, NEVR, 5, VNS, VG, 0},
{"EMAMI",     0,0,16, 0, 0,5,0, DAL, ESAML, NEVR, 6, VNS, VG, 0},
{"IMI",       0,0,16, 0, 0,5,0, DAL, ESAML, NEVR, 1, DGS, VG, 0},
{"ØMI",       0,0,16, 0, 2,5,0, DAL, ESAML, NEVR, 2, DGS, VG, 0},
{"SMEIMI",    0,0,16, 3, 1,5,0, DAL, ESAML, NEVR, 3, DGS, VG, 0},
{"MEIMI",     0,0,16, 2, 1,5,0, DAL, ESAML, NEVR, 3, DGS, VG, 0},
{"SUMI",      0,0,16,-1,-1,1,0, DAL, ESAML, NEVR, 4, DGS, VG, 0},
{"SIAMI",     0,0,16, 1, 2,5,0, DAL, ESAML, NEVR, 5, DGS, VG, 0},
{"ESOUMI",    0,0,16, 0, 0,5,0, DAL, ESAML, NEVR, 6, DGS, VG, 0},
{"SOUMI",     0,0,16, 1, 2,5,0, DAL, ESAML, NEVR, 6, DGS, VG, 0},

{"SISAMI",    0,0,16, 3, 0,5,0, DAL, ESAML, NEVR, 1, VNS, VG, 1},
{"OJOMI",     0,0,16,-1,-1,1,0, DAL, ESAML, NEVR, 2, VNS, VG, 1}, // v.g.ivardziuot.
{"MAJAMI",    0,0,16, 3, 1,5,0, DAL, ESAML, NEVR, 3, VNS, VG, 1},
{"ÁJÀMI",     0,0,16,-1,-1,1,0, DAL, ESAML, NEVR, 4, VNS, VG, 1},
{"UJOUMI",    0,0,16, 3, 1,5,0, DAL, ESAML, NEVR, 5, VNS, VG, 1},
{"EMAJAMI",   0,0,16, 4, 2,5,0, DAL, ESAML, NEVR, 6, VNS, VG, 1},
{"IJEIMI",    0,0,16, 3, 1,5,0, DAL, ESAML, NEVR, 1, DGS, VG, 1},
{"ØJØMI",     0,0,16, 2, 2,5,0, DAL, ESAML, NEVR, 2, DGS, VG, 1},
{"SMEISEIMI", 0,0,16, 6, 1,5,0, DAL, ESAML, NEVR, 3, DGS, VG, 1},
{"MEISEIMI",  0,0,16, 5, 1,5,0, DAL, ESAML, NEVR, 3, DGS, VG, 1},
{"SUISOUMI",  0,0,16, 5, 1,5,0, DAL, ESAML, NEVR, 4, DGS, VG, 1},
{"SIAISIAMI", 0,0,16, 5, 2,5,0, DAL, ESAML, NEVR, 5, DGS, VG, 1},
{"ESOUISOUMI",0,0,16, 6, 2,5,0, DAL, ESAML, NEVR, 6, DGS, VG, 1},
{"SOUISOUMI", 0,0,16, 5, 2,5,0, DAL, ESAML, NEVR, 6, DGS, VG, 1},

{"AMI",       0,0,16, 0, 0,5,0, DAL, ESAML, NEVR, 1, VNS, MG, 0}, 
{"SOMI",      0,0,16, 1, 2,5,0, DAL, ESAML, NEVR, 2, VNS, MG, 0},    // m.g.
{"IAMI",      0,0,16,-1,-1,1,0, DAL, ESAML, NEVR, 3, VNS, MG, 0},
{"AMI",       0,0,16,-1,-1,1,0, DAL, ESAML, NEVR, 5, VNS, MG, 0},
{"EJOMI",     0,0,16, 0, 0,5,0, DAL, ESAML, NEVR, 6, VNS, MG, 0},
{"JOMI",      0,0,16, 1, 2,5,0, DAL, ESAML, NEVR, 6, VNS, MG, 0},
{"SOMI",      0,0,16,-1,-1,1,0, DAL, ESAML, NEVR, 1, DGS, MG, 0},
{"SMOMI",     0,0,16, 2, 1,5,0, DAL, ESAML, NEVR, 3, DGS, MG, 0},
{"MOMI",      0,0,16, 1, 1,5,0, DAL, ESAML, NEVR, 3, DGS, MG, 0},
{"SAMI",      0,0,16,-1,-1,1,0, DAL, ESAML, NEVR, 4, DGS, MG, 0},
{"SIMOMI",    0,0,16, 1, 0,5,0, DAL, ESAML, NEVR, 5, DGS, MG, 0},
{"ESOMI",     0,0,16, 0, 0,5,0, DAL, ESAML, NEVR, 6, DGS, MG, 0},

{"IJOMI",     0,0,16, 2, 1,5,0, DAL, ESAML, NEVR, 1, VNS, MG, 1},
{"SOISOMI",   0,0,16, 4, 2,5,0, DAL, ESAML, NEVR, 2, VNS, MG, 1}, // m.g.ivardziuot.
{"IAJAMI",    0,0,16,-1,-1,1,0, DAL, ESAML, NEVR, 3, VNS, MG, 1},
{"ÀJÀMI",     0,0,16,-1,-1,1,0, DAL, ESAML, NEVR, 4, VNS, MG, 1},
{"AJÀMI",     0,0,16, 2, 1,5,0, DAL, ESAML, NEVR, 5, VNS, MG, 1},
{"EJOJOMI",   0,0,16, 4, 2,5,0, DAL, ESAML, NEVR, 6, VNS, MG, 1},
{"JOJOMI",    0,0,16, 3, 2,5,0, DAL, ESAML, NEVR, 6, VNS, MG, 1},
{"SOISOMI",   0,0,16,-1,-1,1,0, DAL, ESAML, NEVR, 1, DGS, MG, 1},
{"SMOISOMI",  0,0,16, 5, 1,5,0, DAL, ESAML, NEVR, 3, DGS, MG, 1},
{"MOISOMI",   0,0,16, 4, 1,5,0, DAL, ESAML, NEVR, 3, DGS, MG, 1},
{"SAISÀMI",   0,0,16, 4, 1,5,0, DAL, ESAML, NEVR, 4, DGS, MG, 1},
{"SIMOISOMI", 0,0,16, 6, 2,5,0, DAL, ESAML, NEVR, 5, DGS, MG, 1},
{"ESOISOMI",  0,0,16, 5, 2,5,0, DAL, ESAML, NEVR, 6, DGS, MG, 1},

{"AMI",       0,0,16,-1,-1,1,0, DAL, ESAML, NEVR, -1, -1, BG, 0},
{"ISAMI",     0,1,16,-1,-1,1,0, DAL, ESAML, NEVR, -1, -1, BG, 0},     // bev.g.

// O asmenuote
{"SAMO",      0,0,96,-1,-1,1,0, DAL, ESAML, NEVR, 1, VNS, VG, 0},
{"OMO",       0,0,96,-1,-1,1,0, DAL, ESAML, NEVR, 2, VNS, VG, 0},    // v.g.
{"MAMO",      0,0,96, 1, 1,5,0, DAL, ESAML, NEVR, 3, VNS, VG, 0},
{"ÀMO",       0,0,96,-1,-1,1,0, DAL, ESAML, NEVR, 4, VNS, VG, 0},
{"UMO",       0,0,96,-1,-1,1,0, DAL, ESAML, NEVR, 5, VNS, VG, 0},
{"EMAMO",     0,0,96, 0, 0,5,0, DAL, ESAML, NEVR, 6, VNS, VG, 0},
{"IMO",       0,0,96, 0, 0,5,0, DAL, ESAML, NEVR, 1, DGS, VG, 0},
{"ØMO",       0,0,96, 0, 2,5,0, DAL, ESAML, NEVR, 2, DGS, VG, 0},
{"SMEIMO",    0,0,96, 3, 1,5,0, DAL, ESAML, NEVR, 3, DGS, VG, 0},
{"MEIMO",     0,0,96, 2, 1,5,0, DAL, ESAML, NEVR, 3, DGS, VG, 0},
{"SUMO",      0,0,96,-1,-1,1,0, DAL, ESAML, NEVR, 4, DGS, VG, 0},
{"SIAMO",     0,0,96, 1, 2,5,0, DAL, ESAML, NEVR, 5, DGS, VG, 0},
{"ESOUMO",    0,0,96, 0, 0,5,0, DAL, ESAML, NEVR, 6, DGS, VG, 0},
{"SOUMO",     0,0,96, 1, 2,5,0, DAL, ESAML, NEVR, 6, DGS, VG, 0},

{"SISAMO",    0,0,96, 3, 0,5,0, DAL, ESAML, NEVR, 1, VNS, VG, 1},
{"OJOMO",     0,0,96,-1,-1,1,0, DAL, ESAML, NEVR, 2, VNS, VG, 1}, // v.g.ivardziuot.
{"MAJAMO",    0,0,96, 3, 1,5,0, DAL, ESAML, NEVR, 3, VNS, VG, 1},
{"ÁJÀMO",     0,0,96,-1,-1,1,0, DAL, ESAML, NEVR, 4, VNS, VG, 1},
{"UJOUMO",    0,0,96, 3, 1,5,0, DAL, ESAML, NEVR, 5, VNS, VG, 1},
{"EMAJAMO",   0,0,96, 4, 2,5,0, DAL, ESAML, NEVR, 6, VNS, VG, 1},
{"IJEIMO",    0,0,96, 3, 1,5,0, DAL, ESAML, NEVR, 1, DGS, VG, 1},
{"ØJØMO",     0,0,96, 2, 2,5,0, DAL, ESAML, NEVR, 2, DGS, VG, 1},
{"SMEISEIMO", 0,0,96, 6, 1,5,0, DAL, ESAML, NEVR, 3, DGS, VG, 1},
{"MEISEIMO",  0,0,96, 5, 1,5,0, DAL, ESAML, NEVR, 3, DGS, VG, 1},
{"SUISOUMO",  0,0,96, 5, 1,5,0, DAL, ESAML, NEVR, 4, DGS, VG, 1},
{"SIAISIAMO", 0,0,96, 5, 2,5,0, DAL, ESAML, NEVR, 5, DGS, VG, 1},
{"ESOUISOUMO",0,0,96, 6, 2,5,0, DAL, ESAML, NEVR, 6, DGS, VG, 1},
{"SOUISOUMO", 0,0,96, 5, 2,5,0, DAL, ESAML, NEVR, 6, DGS, VG, 1},

{"AMO",       0,0,96, 0, 0,5,0, DAL, ESAML, NEVR, 1, VNS, MG, 0},
{"SOMO",      0,0,96, 1, 2,5,0, DAL, ESAML, NEVR, 2, VNS, MG, 0},    // m.g.
{"IAMO",      0,0,96,-1,-1,1,0, DAL, ESAML, NEVR, 3, VNS, MG, 0},
{"AMO",       0,0,96,-1,-1,1,0, DAL, ESAML, NEVR, 5, VNS, MG, 0},
{"EJOMO",     0,0,96, 0, 0,5,0, DAL, ESAML, NEVR, 6, VNS, MG, 0},
{"JOMO",      0,0,96, 1, 2,5,0, DAL, ESAML, NEVR, 6, VNS, MG, 0},
{"SOMO",      0,0,96,-1,-1,1,0, DAL, ESAML, NEVR, 1, DGS, MG, 0},
{"SMOMO",     0,0,96, 2, 1,5,0, DAL, ESAML, NEVR, 3, DGS, MG, 0},
{"MOMO",      0,0,96, 1, 1,5,0, DAL, ESAML, NEVR, 3, DGS, MG, 0},
{"SAMO",      0,0,96,-1,-1,1,0, DAL, ESAML, NEVR, 4, DGS, MG, 0},
{"SIMOMO",    0,0,96, 1, 0,5,0, DAL, ESAML, NEVR, 5, DGS, MG, 0},
{"ESOMO",     0,0,96, 0, 0,5,0, DAL, ESAML, NEVR, 6, DGS, MG, 0},

{"IJOMO",     0,0,96, 2, 1,5,0, DAL, ESAML, NEVR, 1, VNS, MG, 1},
{"SOISOMO",   0,0,96, 4, 2,5,0, DAL, ESAML, NEVR, 2, VNS, MG, 1}, // m.g.ivardziuot.
{"IAJAMO",    0,0,96,-1,-1,1,0, DAL, ESAML, NEVR, 3, VNS, MG, 1},
{"ÀJÀMO",     0,0,96,-1,-1,1,0, DAL, ESAML, NEVR, 4, VNS, MG, 1},
{"AJÀMO",     0,0,96, 2, 1,5,0, DAL, ESAML, NEVR, 5, VNS, MG, 1},
{"EJOJOMO",   0,0,96, 4, 2,5,0, DAL, ESAML, NEVR, 6, VNS, MG, 1},
{"JOJOMO",    0,0,96, 3, 2,5,0, DAL, ESAML, NEVR, 6, VNS, MG, 1},
{"SOISOMO",   0,0,96,-1,-1,1,0, DAL, ESAML, NEVR, 1, DGS, MG, 1},
{"SMOISOMO",  0,0,96, 5, 1,5,0, DAL, ESAML, NEVR, 3, DGS, MG, 1},
{"MOISOMO",   0,0,96, 4, 1,5,0, DAL, ESAML, NEVR, 3, DGS, MG, 1},
{"SAISÀMO",   0,0,96, 4, 1,5,0, DAL, ESAML, NEVR, 4, DGS, MG, 1},
{"SIMOISOMO", 0,0,96, 6, 2,5,0, DAL, ESAML, NEVR, 5, DGS, MG, 1},
{"ESOISOMO",  0,0,96, 5, 2,5,0, DAL, ESAML, NEVR, 6, DGS, MG, 1},

{"AMO",       0,0,96,-1,-1,1,0, DAL, ESAML, NEVR, -1, -1, BG, 0},
{"ISAMO",     0,1,96,-1,-1,1,0, DAL, ESAML, NEVR, -1, -1, BG, 0},     // bev.g.

// 6 Esamojo laiko veikiamasis prieveiksmis
{"IAIÈNA",    0,0,99,-1,-1,1,0},
{"IAIÈNAI",   0,0,12,-1,-1,1,0},
{"IAIÈNI",    0,0,16,-1,-1,1,0},

// 7 Esamojo laiko neveikiamasis prieveiksmis
{"IAMA",      0,0, 3, 0, 2,6,0},
{"IAMAI",     0,0,12, 0, 2,6,0},
{"IAMI",      0,0,16, 0, 2,6,0},
{"IAMO",      0,0,96, 0, 2,6,0},

//--------------------------------------------------------------------
// Ið bûtojo kartinio laiko kamieno daromø veiksmaþodþio formø galûnës
// 8 Bûtasis kartinis laikas ir sangraziniai
// O asmenuote
{"UA",   1,0,53, 0, 2,7,0, VKS, BKL, TIESN, 1, VNS, -1, -1},
{"IA",   1,0,53, 0, 2,7,0, VKS, BKL, TIESN, 2, VNS, -1, -1},
{"O",    1,0,53,-1,-1,8,0, VKS, BKL, TIESN, 3, V_D, -1, -1},
{"EMO",  1,0,53,-1,-1,8,0, VKS, BKL, TIESN, 1, DGS, -1, -1},
{"MO",   1,0,53,-1,-1,8,0, VKS, BKL, TIESN, 1, DGS, -1, -1},
{"ETO",  1,0,53,-1,-1,8,0, VKS, BKL, TIESN, 2, DGS, -1, -1},
{"TO",   1,0,53,-1,-1,8,0, VKS, BKL, TIESN, 2, DGS, -1, -1},
{"ISUA", 1,1,53, 2, 2,7,0, VKS, BKL, TIESN, 1, VNS, -1, -1},
{"SUA",  1,1,53, 1, 2,7,0, VKS, BKL, TIESN, 1, VNS, -1, -1},
{"ISIA", 1,1,53, 2, 2,7,0, VKS, BKL, TIESN, 2, VNS, -1, -1},
{"SIA",  1,1,53, 1, 2,7,0, VKS, BKL, TIESN, 2, VNS, -1, -1},
{"ISO",  1,1,53,-1,-1,8,0, VKS, BKL, TIESN, 3, V_D, -1, -1},
{"SO",   1,1,53,-1,-1,8,0, VKS, BKL, TIESN, 3, V_D, -1, -1},
{"SËMO", 1,1,53,-1,-1,8,0, VKS, BKL, TIESN, 1, DGS, -1, -1},
{"SËTO", 1,1,53,-1,-1,8,0, VKS, BKL, TIESN, 2, DGS, -1, -1},

// Ë asmenuote
{"UAI",  1,0,74, 0, 2,7,0, VKS, BKL, TIESN, 1, VNS, -1, -1},
{"IE",   1,0,74, 0, 2,7,0, VKS, BKL, TIESN, 2, VNS, -1, -1},
{"Ë",    1,0,74,-1,-1,8,0, VKS, BKL, TIESN, 3, V_D, -1, -1},
{"EMË",  1,0,74,-1,-1,8,0, VKS, BKL, TIESN, 1, DGS, -1, -1},
{"MË",   1,0,74,-1,-1,8,0, VKS, BKL, TIESN, 1, DGS, -1, -1},
{"ETË",  1,0,74,-1,-1,8,0, VKS, BKL, TIESN, 2, DGS, -1, -1},
{"TË",   1,0,74,-1,-1,8,0, VKS, BKL, TIESN, 2, DGS, -1, -1},
{"ISUAI",1,1,74, 2, 2,7,0, VKS, BKL, TIESN, 1, VNS, -1, -1},
{"SUAI", 1,1,74, 1, 2,7,0, VKS, BKL, TIESN, 1, VNS, -1, -1},
{"ISIE", 1,1,74, 2, 2,7,0, VKS, BKL, TIESN, 2, VNS, -1, -1},
{"SIE",  1,1,74, 1, 2,7,0, VKS, BKL, TIESN, 2, VNS, -1, -1},
{"ISË",  1,1,74,-1,-1,8,0, VKS, BKL, TIESN, 3, V_D, -1, -1},
{"SË",   1,1,74,-1,-1,8,0, VKS, BKL, TIESN, 3, V_D, -1, -1},
{"SËMË", 1,1,74,-1,-1,8,0, VKS, BKL, TIESN, 1, DGS, -1, -1},
{"SËTË", 1,1,74,-1,-1,8,0, VKS, BKL, TIESN, 2, DGS, -1, -1},

// 9 Bûtojo kartinio laiko padalyvis
{"SU",   1,0,63,-1,-1,9,0, PAD, BKL, -1, -1, -1, -1, -1},
{"SISU", 1,1,63,-1,-1,9,0, PAD, BKL, -1, -1, -1, -1, -1},
{"SUI",  1,0,64,-1,-1,9,0, PAD, BKL, -1, -1, -1, -1, -1},
{"SISUI",1,1,64,-1,-1,9,0, PAD, BKL, -1, -1, -1, -1, -1},

// 10 Bûtojo kartinio laiko veikiamasis dalyvis
{"SÆ",         1,0,127,-1,-1,9,0, DAL, BKL, VEIKR, 1, VNS, VG, 0},
{"OISU",       1,0,63, -1,-1,9,0, DAL, BKL, VEIKR, 2, VNS, VG, 0},    // v.g.
{"MAISU",      1,0,63, -1,-1,9,0, DAL, BKL, VEIKR, 3, VNS, VG, 0},
{"ÁSU",        1,0,63, -1,-1,9,0, DAL, BKL, VEIKR, 4, VNS, VG, 0},
{"UISU",       1,0,63, -1,-1,9,0, DAL, BKL, VEIKR, 5, VNS, VG, 0},
{"EMAISU",     1,0,63, -1,-1,9,0, DAL, BKL, VEIKR, 6, VNS, VG, 0},
{"Æ",          1,0,127,-1,-1,9,0, DAL, BKL, VEIKR, 1, DGS, VG, 0},
{"ØISU",       1,0,63, -1,-1,9,0, DAL, BKL, VEIKR, 2, DGS, VG, 0},
{"SMEISU",     1,0,63, -1,-1,9,0, DAL, BKL, VEIKR, 3, DGS, VG, 0},
{"MEISU",      1,0,63, -1,-1,9,0, DAL, BKL, VEIKR, 3, DGS, VG, 0},
{"SUISU",      1,0,63, -1,-1,9,0, DAL, BKL, VEIKR, 4, DGS, VG, 0},
{"SIAISU",     1,0,63, -1,-1,9,0, DAL, BKL, VEIKR, 5, DGS, VG, 0},
{"ESOUISU",    1,0,63, -1,-1,9,0, DAL, BKL, VEIKR, 6, DGS, VG, 0},
{"SOUISU",     1,0,63, -1,-1,9,0, DAL, BKL, VEIKR, 6, DGS, VG, 0},

{"SISYSU",     1,0,63,-1,-1,9,0, DAL, BKL, VEIKR, 1, VNS, VG, 1},
{"OJOISU",     1,0,63,-1,-1,9,0, DAL, BKL, VEIKR, 2, VNS, VG, 1}, // v.g.ivardziuot.
{"MAJAISU",    1,0,63,-1,-1,9,0, DAL, BKL, VEIKR, 3, VNS, VG, 1},
{"ÁJÁSU",      1,0,63,-1,-1,9,0, DAL, BKL, VEIKR, 4, VNS, VG, 1},
{"UJOUISU",    1,0,63,-1,-1,9,0, DAL, BKL, VEIKR, 5, VNS, VG, 1},
{"EMAJAISU",   1,0,63,-1,-1,9,0, DAL, BKL, VEIKR, 6, VNS, VG, 1},
{"IJEISU",     1,0,63,-1,-1,9,0, DAL, BKL, VEIKR, 1, DGS, VG, 1},
{"ØJØISU",     1,0,63,-1,-1,9,0, DAL, BKL, VEIKR, 2, DGS, VG, 1},
{"SMEISEISU",  1,0,63,-1,-1,9,0, DAL, BKL, VEIKR, 3, DGS, VG, 1},
{"MEISEISU",   1,0,63,-1,-1,9,0, DAL, BKL, VEIKR, 3, DGS, VG, 1},
{"SUISOUISU",  1,0,63,-1,-1,9,0, DAL, BKL, VEIKR, 4, DGS, VG, 1},
{"SIAISIAISU", 1,0,63,-1,-1,9,0, DAL, BKL, VEIKR, 5, DGS, VG, 1},
{"ESOUISOUISU",1,0,63,-1,-1,9,0, DAL, BKL, VEIKR, 6, DGS, VG, 1},
{"SOUISOUISU", 1,0,63,-1,-1,9,0, DAL, BKL, VEIKR, 6, DGS, VG, 1},

{"SISÆ",       1,1,127,-1,-1,9,0, DAL, BKL, VEIKR, 1, VNS, VG, 0},
{"ISÆ",        1,1,127,-1,-1,9,0, DAL, BKL, VEIKR, 1, DGS, VG, 0},  // v.g.sangraziniai.

{"ISU",        1,0,63,-1,-1,9,0, DAL, BKL, VEIKR, 1, VNS, MG, 0},
{"SOISU",      1,0,63,-1,-1,9,0, DAL, BKL, VEIKR, 2, VNS, MG, 0},    // m.g.
{"IAISU",      1,0,63,-1,-1,9,0, DAL, BKL, VEIKR, 3, VNS, MG, 0},
{"ÀISU",       1,0,63,-1,-1,9,0, DAL, BKL, VEIKR, 4, VNS, MG, 0},
{"AISU",       1,0,63,-1,-1,9,0, DAL, BKL, VEIKR, 5, VNS, MG, 0},
{"EJOISU",     1,0,63,-1,-1,9,0, DAL, BKL, VEIKR, 6, VNS, MG, 0},
{"JOISU",      1,0,63,-1,-1,9,0, DAL, BKL, VEIKR, 6, VNS, MG, 0},
{"SMOISU",     1,0,63,-1,-1,9,0, DAL, BKL, VEIKR, 3, DGS, MG, 0},
{"MOISU",      1,0,63,-1,-1,9,0, DAL, BKL, VEIKR, 3, DGS, MG, 0},
{"SAISU",      1,0,63,-1,-1,9,0, DAL, BKL, VEIKR, 4, DGS, MG, 0},
{"SIMOISU",    1,0,63,-1,-1,9,0, DAL, BKL, VEIKR, 5, DGS, MG, 0},
{"ESOISU",     1,0,63,-1,-1,9,0, DAL, BKL, VEIKR, 6, DGS, MG, 0},

{"IJOISU",     1,0,63,-1,-1,9,0, DAL, BKL, VEIKR, 1, VNS, MG, 1},
{"SOISOISU",   1,0,63,-1,-1,9,0, DAL, BKL, VEIKR, 2, VNS, MG, 1}, // m.g.ivardziuot.
{"IAJAISU",    1,0,63,-1,-1,9,0, DAL, BKL, VEIKR, 3, VNS, MG, 1},
{"ÀJÀISU",     1,0,63,-1,-1,9,0, DAL, BKL, VEIKR, 4, VNS, MG, 1},
{"AJÀISU",     1,0,63,-1,-1,9,0, DAL, BKL, VEIKR, 5, VNS, MG, 1},
{"EJOJOISU",   1,0,63,-1,-1,9,0, DAL, BKL, VEIKR, 6, VNS, MG, 1},
{"JOJOISU",    1,0,63,-1,-1,9,0, DAL, BKL, VEIKR, 6, VNS, MG, 1},
{"SMOISOISU",  1,0,63,-1,-1,9,0, DAL, BKL, VEIKR, 3, DGS, MG, 1},
{"MOISOISU",   1,0,63,-1,-1,9,0, DAL, BKL, VEIKR, 3, DGS, MG, 1},
{"SAISÀISU",   1,0,63,-1,-1,9,0, DAL, BKL, VEIKR, 4, DGS, MG, 1},
{"SIMOISOISU", 1,0,63,-1,-1,9,0, DAL, BKL, VEIKR, 5, DGS, MG, 1},
{"ESOISOISU",  1,0,63,-1,-1,9,0, DAL, BKL, VEIKR, 6, DGS, MG, 1},

{"SISU",       1,1,63,-1,-1,9,0, DAL, BKL, VEIKR, 1, VNS, MG, 0},
{"ISOISU",     1,1,63,-1,-1,9,0, DAL, BKL, VEIKR, 1, DGS, MG, 0},  // m.g.sangraziniai.

{"OISUI",      1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 2, VNS, VG, 0},    // v.g.
{"MAISUI",     1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 3, VNS, VG, 0},
{"ÁSUI",       1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 4, VNS, VG, 0},
{"UISUI",      1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 5, VNS, VG, 0},
{"EMAISUI",    1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 6, VNS, VG, 0},
{"ØISUI",      1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 2, DGS, VG, 0},
{"SMEISUI",    1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 3, DGS, VG, 0},
{"MEISUI",     1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 3, DGS, VG, 0},
{"SUISUI",     1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 4, DGS, VG, 0},
{"SIAISUI",    1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 5, DGS, VG, 0},
{"ESOUISUI",   1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 6, DGS, VG, 0},
{"SOUISUI",    1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 6, DGS, VG, 0},

{"SISYSUI",    1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 1, VNS, VG, 1},
{"OJOISUI",    1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 2, VNS, VG, 1}, // v.g.ivardziuot.
{"MAJAISUI",   1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 3, VNS, VG, 1},
{"ÁJÁSUI",     1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 4, VNS, VG, 1},
{"UJOUISUI",   1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 5, VNS, VG, 1},
{"EMAJAISUI",  1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 6, VNS, VG, 1},
{"IJEISUI",    1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 1, DGS, VG, 1},
{"ØJØISUI",    1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 2, DGS, VG, 1},
{"SMEISEISUI", 1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 3, DGS, VG, 1},
{"MEISEISUI",  1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 3, DGS, VG, 1},
{"SUISOUISUI", 1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 4, DGS, VG, 1},
{"SIAISIAISUI",1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 5, DGS, VG, 1},
{"ESOUISOUISUI",1,0,64,-1,-1,9,0,DAL, BKL, VEIKR, 6, DGS, VG, 1},
{"SOUISOUISUI",1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 6, DGS, VG, 1},

{"ISUI",       1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 1, VNS, MG, 0},
{"SOISUI",     1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 2, VNS, MG, 0},    // m.g.
{"IAISUI",     1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 3, VNS, MG, 0},
{"ÀISUI",      1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 4, VNS, MG, 0},
{"AISUI",      1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 5, VNS, MG, 0},
{"EJOISUI",    1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 6, VNS, MG, 0},
{"JOISUI",     1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 6, VNS, MG, 0},
{"SMOISUI",    1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 3, DGS, MG, 0},
{"MOISUI",     1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 3, DGS, MG, 0},
{"SAISUI",     1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 4, DGS, MG, 0},
{"SIMOISUI",   1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 5, DGS, MG, 0},
{"ESOISUI",    1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 6, DGS, MG, 0},

{"IJOISUI",    1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 1, VNS, MG, 1},
{"SOISOISUI",  1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 2, VNS, MG, 1}, // m.g.ivardziuot.
{"IAJAISUI",   1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 3, VNS, MG, 1},
{"ÀJÀISUI",    1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 4, VNS, MG, 1},
{"AJÀISUI",    1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 5, VNS, MG, 1},
{"EJOJOISUI",  1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 6, VNS, MG, 1},
{"JOJOISUI",   1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 6, VNS, MG, 1},
{"SMOISOISUI", 1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 3, DGS, MG, 1},
{"MOISOISUI",  1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 3, DGS, MG, 1},
{"SAISÀISUI",  1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 4, DGS, MG, 1},
{"SIMOISOISUI",1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 5, DGS, MG, 1},
{"ESOISOISUI", 1,0,64,-1,-1,9,0, DAL, BKL, VEIKR, 6, DGS, MG, 1},

{"SISUI",      1,1,64,-1,-1,9,0, DAL, BKL, VEIKR, 1, VNS, MG, 0},
{"ISOISUI",    1,1,64,-1,-1,9,0, DAL, BKL, VEIKR, 1, DGS, MG, 0},  // m.g.sangraziniai.

// 11 Bûtojo kartinio laiko veikiamasis prieveiksmis
{"IAISU",  1,0,63,-1,-1,9,0},
{"IAISUI", 1,0,64,-1,-1,9,0},

// Ið bendraties kamieno daromø veiksmaþodþio formø galûnës
// 12 Bendratis
{"IT",     2,0,127,-1,-1,10,0, BENDR, -1, -1, -1, -1, -1, -1},
{"T",      2,0,127,-1,-1,10,0, BENDR, -1, -1, -1, -1, -1, -1},
{"SIT",    2,1,127,-1,-1,10,0, BENDR, -1, -1, -1, -1, -1, -1},

// 13 Bûtasis daþninis laikas
{"UAVAD",  2,0,127,-1,-1,10,0, VKS, BDL, TIESN, 1, VNS, -1, -1},
{"ISUAVAD",2,1,127,-1,-1,10,0, VKS, BDL, TIESN, 1, VNS, -1, -1},
{"SUAVAD", 2,1,127,-1,-1,10,0, VKS, BDL, TIESN, 1, VNS, -1, -1},
{"IAVAD",  2,0,127,-1,-1,10,0, VKS, BDL, TIESN, 2, VNS, -1, -1},
{"ISIAVAD",2,1,127,-1,-1,10,0, VKS, BDL, TIESN, 2, VNS, -1, -1},
{"SIAVAD", 2,1,127,-1,-1,10,0, VKS, BDL, TIESN, 2, VNS, -1, -1},
{"OVAD",   2,0,127,-1,-1,10,0, VKS, BDL, TIESN, 3, V_D, -1, -1},
{"ISOVAD", 2,1,127,-1,-1,10,0, VKS, BDL, TIESN, 3, V_D, -1, -1},
{"SOVAD",  2,1,127,-1,-1,10,0, VKS, BDL, TIESN, 3, V_D, -1, -1},
{"EMOVAD", 2,0,127,-1,-1,10,0, VKS, BDL, TIESN, 1, DGS, -1, -1},
{"MOVAD",  2,0,127,-1,-1,10,0, VKS, BDL, TIESN, 1, DGS, -1, -1},
{"SËMOVAD",2,1,127,-1,-1,10,0, VKS, BDL, TIESN, 1, DGS, -1, -1},
{"ETOVAD", 2,0,127,-1,-1,10,0, VKS, BDL, TIESN, 2, DGS, -1, -1},
{"TOVAD",  2,0,127,-1,-1,10,0, VKS, BDL, TIESN, 2, DGS, -1, -1},
{"SËTOVAD",2,1,127,-1,-1,10,0, VKS, BDL, TIESN, 2, DGS, -1, -1},

// 14 Bûsimasis laikas
{"UIS",    2,0,127,-1,-1,10,0, VKS, BSL, TIESN, 1, VNS, -1, -1},
{"ISOUIS", 2,1,127,-1,-1,10,0, VKS, BSL, TIESN, 1, VNS, -1, -1},
{"SOUIS",  2,1,127,-1,-1,10,0, VKS, BSL, TIESN, 1, VNS, -1, -1},
{"IS",     2,0,127,-1,-1,10,0, VKS, BSL, TIESN, 2, VNS, -1, -1},
{"ISEIS",  2,1,127,-1,-1,10,0, VKS, BSL, TIESN, 2, VNS, -1, -1},
{"SEIS",   2,1,127,-1,-1,10,0, VKS, BSL, TIESN, 2, VNS, -1, -1},
{"S",      2,0,127,-1,-1,14,1, VKS, BSL, TIESN, 3, V_D, -1, -1},
{"SIS",    2,1,127,-1,-1,14,0, VKS, BSL, TIESN, 3, V_D, -1, -1},
{"EMIS",   2,0,127,-1,-1,10,0, VKS, BSL, TIESN, 1, DGS, -1, -1},
{"MIS",    2,0,127,-1,-1,10,0, VKS, BSL, TIESN, 1, DGS, -1, -1},
{"SËMIS",  2,1,127,-1,-1,10,0, VKS, BSL, TIESN, 1, DGS, -1, -1},
{"ETIS",   2,0,127,-1,-1,10,0, VKS, BSL, TIESN, 2, DGS, -1, -1},
{"TIS",    2,0,127,-1,-1,10,0, VKS, BSL, TIESN, 2, DGS, -1, -1},
{"SËTIS",  2,1,127,-1,-1,10,0, VKS, BSL, TIESN, 2, DGS, -1, -1},

{"UIÐ",    2,0,127,-1,-1,10,0, VKS, BSL, TIESN, 1, VNS, -1, -1},
{"ISOUIÐ", 2,1,127,-1,-1,10,0, VKS, BSL, TIESN, 1, VNS, -1, -1},
{"SOUIÐ",  2,1,127,-1,-1,10,0, VKS, BSL, TIESN, 1, VNS, -1, -1},
{"IÐ",     2,0,127,-1,-1,10,0, VKS, BSL, TIESN, 2, VNS, -1, -1},
{"ISEIÐ",  2,1,127,-1,-1,10,0, VKS, BSL, TIESN, 2, VNS, -1, -1},
{"SEIÐ",   2,1,127,-1,-1,10,0, VKS, BSL, TIESN, 2, VNS, -1, -1},
{"Ð",      2,0,127,-1,-1,14,1, VKS, BSL, TIESN, 3, V_D, -1, -1},
{"SIÐ",    2,1,127,-1,-1,14,0, VKS, BSL, TIESN, 3, V_D, -1, -1},
{"EMIÐ",   2,0,127,-1,-1,10,0, VKS, BSL, TIESN, 1, DGS, -1, -1},
{"MIÐ",    2,0,127,-1,-1,10,0, VKS, BSL, TIESN, 1, DGS, -1, -1},
{"SËMIÐ",  2,1,127,-1,-1,10,0, VKS, BSL, TIESN, 1, DGS, -1, -1},
{"ETIÐ",   2,0,127,-1,-1,10,0, VKS, BSL, TIESN, 2, DGS, -1, -1},
{"TIÐ",    2,0,127,-1,-1,10,0, VKS, BSL, TIESN, 2, DGS, -1, -1},
{"SËTIÐ",  2,1,127,-1,-1,10,0, VKS, BSL, TIESN, 2, DGS, -1, -1},

// 15 Tariamoji nuosaka
{"UAIÈ",   2,0,127,-1,-1,10,0, VKS, -1, TARN, 1, VNS, -1, -1},
{"ISUAIÈ", 2,1,127,-1,-1,10,0, VKS, -1, TARN, 1, VNS, -1, -1},
{"SUAIÈ",  2,1,127,-1,-1,10,0, VKS, -1, TARN, 1, VNS, -1, -1},
{"IEMUT",  2,0,127,-1,-1,10,0, VKS, -1, TARN, 2, VNS, -1, -1},
{"MUT",    2,0,127,-1,-1,10,0, VKS, -1, TARN, 2, VNS, -1, -1},
{"ISIEMUT",2,1,127,-1,-1,10,0, VKS, -1, TARN, 2, VNS, -1, -1},
{"SIEMUT", 2,1,127,-1,-1,10,0, VKS, -1, TARN, 2, VNS, -1, -1},
{"ØT",     2,0,127,-1,-1,10,0, VKS, -1, TARN, 3, V_D, -1, -1},
{"ISØT",   2,1,127,-1,-1,10,0, VKS, -1, TARN, 3, V_D, -1, -1},
{"SØT",    2,1,127,-1,-1,10,0, VKS, -1, TARN, 3, V_D, -1, -1},
{"EMËMUT", 2,0,127,-1,-1,10,0, VKS, -1, TARN, 1, DGS, -1, -1},
{"MËMUT",  2,0,127,-1,-1,10,0, VKS, -1, TARN, 1, DGS, -1, -1},
{"EMUT",   2,0,127,-1,-1,10,0, VKS, -1, TARN, 1, DGS, -1, -1},
{"SËMËMUT",2,1,127,-1,-1,10,0, VKS, -1, TARN, 1, DGS, -1, -1},
{"SËMUT",  2,1,127,-1,-1,10,0, VKS, -1, TARN, 1, DGS, -1, -1},
{"ETËMUT", 2,0,127,-1,-1,10,0, VKS, -1, TARN, 2, DGS, -1, -1},
{"TËMUT",  2,0,127,-1,-1,10,0, VKS, -1, TARN, 2, DGS, -1, -1},
{"ETUT",   2,0,127,-1,-1,10,0, VKS, -1, TARN, 2, DGS, -1, -1},
{"SËTËMUT",2,1,127,-1,-1,10,0, VKS, -1, TARN, 2, DGS, -1, -1},
{"SËTUT",  2,1,127,-1,-1,10,0, VKS, -1, TARN, 2, DGS, -1, -1},

// 16 Liepiamoji nuosaka
{"IK",     2,0,127,-1,-1,10,0, VKS, -1, LIEPN, 2, VNS, -1, -1},
{"K",      2,0,127,-1,-1,10,0, VKS, -1, LIEPN, 2, VNS, -1, -1},
{"SIK",    2,1,127,-1,-1,10,0, VKS, -1, LIEPN, 2, VNS, -1, -1},
{"EMIK",   2,0,127,-1,-1,10,0, VKS, -1, LIEPN, 1, DGS, -1, -1},
{"MIK",    2,0,127,-1,-1,10,0, VKS, -1, LIEPN, 1, DGS, -1, -1},
{"SËMIK",  2,1,127,-1,-1,10,0, VKS, -1, LIEPN, 1, DGS, -1, -1},
{"ETIK",   2,0,127,-1,-1,10,0, VKS, -1, LIEPN, 2, DGS, -1, -1},
{"TIK",    2,0,127,-1,-1,10,0, VKS, -1, LIEPN, 2, DGS, -1, -1},
{"SËTIK",  2,1,127,-1,-1,10,0, VKS, -1, LIEPN, 2, DGS, -1, -1},

// 17 Pusdalyvis
{"SAMAD",  2,0,127,-1,-1,10,0, PSD, -1, -1, -1, VNS, VG, -1},
{"AMAD",   2,0,127, 0, 0,11,0, PSD, -1, -1, -1, VNS, MG, -1},
{"SISAMAD",2,1,127,-1,-1,10,0, PSD, -1, -1, -1, VNS, VG, -1},
{"ISAMAD", 2,1,127,-1,-1,10,0, PSD, -1, -1, -1, VNS, MG, -1},
{"IMAD",   2,0,127, 0, 0,11,0, PSD, -1, -1, -1, DGS, VG, -1},
{"SOMAD",  2,0,127,-1,-1,10,0, PSD, -1, -1, -1, DGS, MG, -1},
{"ISEIMAD",2,1,127,-1,-1,10,0, PSD, -1, -1, -1, DGS, VG, -1},
{"ISOMAD", 2,1,127,-1,-1,10,0, PSD, -1, -1, -1, DGS, MG, -1},

// 18 Bûtojo daþninio ir bûsimojo laiko padalyvis
{"SUVAD",  2,0,127,-1,-1,10,0, PAD, BDL, -1, -1, -1, -1, -1},
{"SISUVAD",2,1,127,-1,-1,10,0, PAD, BDL, -1, -1, -1, -1, -1},

{"TNAIS",  2,0,127,-1,-1,10,0, PAD, BSL, -1, -1, -1, -1, -1},
{"SITNAIS",2,1,127,-1,-1,10,0, PAD, BSL, -1, -1, -1, -1, -1},
{"TNAIÐ",  2,0,127,-1,-1,10,0, PAD, BSL, -1, -1, -1, -1, -1},
{"SITNAIÐ",2,1,127,-1,-1,10,0, PAD, BSL, -1, -1, -1, -1, -1},

// 19 Bûtojo daþninio laiko veikiamasis dalyvis
{"SÆVAD",     2,0,127,-1,-1,10,0, DAL, BDL, VEIKR, 1, VNS, VG, 0},
{"OISUVAD",   2,0,127,-1,-1,10,0, DAL, BDL, VEIKR, 2, VNS, VG, 0},     // v.g.
{"MAISUVAD",  2,0,127,-1,-1,10,0, DAL, BDL, VEIKR, 3, VNS, VG, 0},
{"ÁSUVAD",    2,0,127,-1,-1,10,0, DAL, BDL, VEIKR, 4, VNS, VG, 0},
{"UISUVAD",   2,0,127,-1,-1,10,0, DAL, BDL, VEIKR, 5, VNS, VG, 0},
{"EMAISUVAD", 2,0,127,-1,-1,10,0, DAL, BDL, VEIKR, 6, VNS, VG, 0},
{"ÆVAD",      2,0,127,-1,-1,10,0, DAL, BDL, VEIKR, 1, DGS, VG, 0},
{"ØISUVAD",   2,0,127,-1,-1,10,0, DAL, BDL, VEIKR, 2, DGS, VG, 0},
{"SMEISUVAD", 2,0,127,-1,-1,10,0, DAL, BDL, VEIKR, 3, DGS, VG, 0},
{"MEISUVAD",  2,0,127,-1,-1,10,0, DAL, BDL, VEIKR, 3, DGS, VG, 0},
{"SUISUVAD",  2,0,127,-1,-1,10,0, DAL, BDL, VEIKR, 4, DGS, VG, 0},
{"SIAISUVAD", 2,0,127,-1,-1,10,0, DAL, BDL, VEIKR, 5, DGS, VG, 0},
{"ESOUISUVAD",2,0,127,-1,-1,10,0, DAL, BDL, VEIKR, 6, DGS, VG, 0},
{"SOUISUVAD", 2,0,127,-1,-1,10,0, DAL, BDL, VEIKR, 6, DGS, VG, 0},

{"SISÆVAD",   2,1,127,-1,-1,10,0, DAL, BDL, VEIKR, 1, VNS, VG, 0},
{"ISÆVAD",    2,1,127,-1,-1,10,0, DAL, BDL, VEIKR, 1, DGS, VG, 0},  // sangr.

{"ISUVAD",    2,0,127,-1,-1,10,0, DAL, BDL, VEIKR, 1, VNS, MG, 0},
{"SOISUVAD",  2,0,127,-1,-1,10,0, DAL, BDL, VEIKR, 2, VNS, MG, 0},  // m.g.
{"IAISUVAD",  2,0,127,-1,-1,10,0, DAL, BDL, VEIKR, 3, VNS, MG, 0},
{"ÀISUVAD",   2,0,127,-1,-1,10,0, DAL, BDL, VEIKR, 4, VNS, MG, 0},
{"AISUVAD",   2,0,127,-1,-1,10,0, DAL, BDL, VEIKR, 5, VNS, MG, 0},
{"EJOISUVAD", 2,0,127,-1,-1,10,0, DAL, BDL, VEIKR, 6, VNS, MG, 0},
{"JOISUVAD",  2,0,127,-1,-1,10,0, DAL, BDL, VEIKR, 6, VNS, MG, 0},
{"SOISUVAD",  2,0,127,-1,-1,10,0, DAL, BDL, VEIKR, 1, DGS, MG, 0},
{"ØISUVAD",   2,0,127,-1,-1,10,0, DAL, BDL, VEIKR, 2, DGS, MG, 0},
{"SMOISUVAD", 2,0,127,-1,-1,10,0, DAL, BDL, VEIKR, 3, DGS, MG, 0},
{"MOISUVAD",  2,0,127,-1,-1,10,0, DAL, BDL, VEIKR, 3, DGS, MG, 0},
{"SAISUVAD",  2,0,127,-1,-1,10,0, DAL, BDL, VEIKR, 4, DGS, MG, 0},
{"SIMOISUVAD",2,0,127,-1,-1,10,0, DAL, BDL, VEIKR, 5, DGS, MG, 0},
{"ESOISUVAD", 2,0,127,-1,-1,10,0, DAL, BDL, VEIKR, 6, DGS, MG, 0},

{"SISUVAD",   2,1,127,-1,-1,10,0, DAL, BDL, VEIKR, 1, VNS, MG, 0},
{"ISOISUVAD", 2,1,127,-1,-1,10,0, DAL, BDL, VEIKR, 1, DGS, MG, 0},  // sangr.

// 20 Bûsimojo laiko veikiamasis dalyvis
{"SÀIS",         2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 1, VNS, VG, 0},
{"SITNAIS",      2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 1, VNS, VG, 0},
{"OIÈNAIS",      2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 2, VNS, VG, 0},         // v.g.
{"MAIÈNAIS",     2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 3, VNS, VG, 0},
{"ÁTNAIS",       2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 4, VNS, VG, 0},
{"UIÈNAIS",      2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 5, VNS, VG, 0},
{"EMAIÈNAIS",    2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 6, VNS, VG, 0},
{"ÀIS",          2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 1, DGS, VG, 0},
{"SYTNAIS",      2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 1, DGS, VG, 0},
{"ØIÈNAIS",      2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 2, DGS, VG, 0},
{"SMEITNAIS",    2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 3, DGS, VG, 0},
{"MEITNAIS",     2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 3, DGS, VG, 0},
{"SUIÈNAIS",     2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 4, DGS, VG, 0},
{"SIAIÈNAIS",    2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 5, DGS, VG, 0},
{"ESOUIÈNAIS",   2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 6, DGS, VG, 0},
{"SOUIÈNAIS",    2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 6, DGS, VG, 0},

{"SISYTNAIS",    2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 1, VNS, VG, 1},
{"OJOIÈNAIS",    2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 2, VNS, VG, 1},  // v.g.ivardz.
{"MAJAIÈNAIS",   2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 3, VNS, VG, 1},
{"ÁJÁTNAIS",     2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 4, VNS, VG, 1},
{"UJOUIÈNAIS",   2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 5, VNS, VG, 1},
{"EMAJAIÈNAIS",  2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 6, VNS, VG, 1},
{"IJEITNAIS",    2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 1, DGS, VG, 1},
{"ØJØIÈNAIS",    2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 2, DGS, VG, 1},
{"SMEISEITNAIS", 2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 3, DGS, VG, 1},
{"MEISEITNAIS",  2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 3, DGS, VG, 1},
{"SUISOUIÈNAIS", 2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 4, DGS, VG, 1},
{"SIAISIAIÈNAIS",2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 5, DGS, VG, 1},
{"ESOUISOUIÈNAIS",2,0,127,-1,-1,10,0,DAL, BSL, VEIKR, 6, DGS, VG, 1},
{"SOUISOUIÈNAIS",2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 6, DGS, VG, 1},

{"SISÀIS",       2,1,127,-1,-1,10,0, DAL, BSL, VEIKR, 1, VNS, VG, 0},
{"ISÀIS",        2,1,127,-1,-1,10,0, DAL, BSL, VEIKR, 1, DGS, VG, 0},  // v.g.sangr.

{"ITNAIS",       2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 1, VNS, MG, 0},
{"SOIÈNAIS",     2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 2, VNS, MG, 0},  // m.g.
{"IAIÈNAIS",     2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 3, VNS, MG, 0},
{"ÀIÈNAIS",      2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 4, VNS, MG, 0},
{"AIÈNAIS",      2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 5, VNS, MG, 0},
{"EJOIÈNAIS",    2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 6, VNS, MG, 0},
{"JOIÈNAIS",     2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 6, VNS, MG, 0},
{"SMOIÈNAIS",    2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 3, DGS, MG, 0},
{"MOIÈNAIS",     2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 3, DGS, MG, 0},
{"SAIÈNAIS",     2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 4, DGS, MG, 0},
{"SIMOIÈNAIS",   2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 5, DGS, MG, 0},
{"ESOIÈNAIS",    2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 6, DGS, MG, 0},

{"IJOIÈNAIS",    2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 1, VNS, MG, 1},
{"SOISOIÈNAIS",  2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 2, VNS, MG, 1},  // m.g.ivardz.
{"IAJAIÈNAIS",   2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 3, VNS, MG, 1},
{"ÀJÀIÈNAIS",    2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 4, VNS, MG, 1},
{"AJÀIÈNAIS",    2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 5, VNS, MG, 1},
{"EJOJOIÈNAIS",  2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 6, VNS, MG, 1},
{"JOJOIÈNAIS",   2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 6, VNS, MG, 1},
{"SMOISOIÈNAIS", 2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 3, DGS, MG, 1},
{"MOISOIÈNAIS",  2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 3, DGS, MG, 1},
{"SAISÀIÈNAIS",  2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 4, DGS, MG, 1},
{"SIMOISOIÈNAIS",2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 5, DGS, MG, 1},
{"ESOISOIÈNAIS", 2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 6, DGS, MG, 1},

{"SITNAIS",      2,1,127,-1,-1,10,0, DAL, BSL, VEIKR, 1, VNS, MG, 0},
{"ISOIÈNAIS",    2,1,127,-1,-1,10,0, DAL, BSL, VEIKR, 1, DGS, MG, 0},  // m.g.sangr.

{"SÀIÐ",         2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 1, VNS, VG, 0},
{"SITNAIÐ",      2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 1, VNS, VG, 0},
{"OIÈNAIÐ",      2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 2, VNS, VG, 0},         // v.g.
{"MAIÈNAIÐ",     2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 3, VNS, VG, 0},
{"ÁTNAIÐ",       2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 4, VNS, VG, 0},
{"UIÈNAIÐ",      2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 5, VNS, VG, 0},
{"EMAIÈNAIÐ",    2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 6, VNS, VG, 0},
{"ÀIÐ",          2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 1, DGS, VG, 0},
{"SYTNAIÐ",      2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 1, DGS, VG, 0},
{"ØIÈNAIÐ",      2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 2, DGS, VG, 0},
{"SMEITNAIÐ",    2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 3, DGS, VG, 0},
{"MEITNAIÐ",     2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 3, DGS, VG, 0},
{"SUIÈNAIÐ",     2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 4, DGS, VG, 0},
{"SIAIÈNAIÐ",    2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 5, DGS, VG, 0},
{"ESOUIÈNAIÐ",   2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 6, DGS, VG, 0},
{"SOUIÈNAIÐ",    2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 6, DGS, VG, 0},

{"SISYTNAIÐ",    2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 1, VNS, VG, 1},
{"OJOIÈNAIÐ",    2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 2, VNS, VG, 1},  // v.g.ivardz.
{"MAJAIÈNAIÐ",   2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 3, VNS, VG, 1},
{"ÁJÁTNAIÐ",     2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 4, VNS, VG, 1},
{"UJOUIÈNAIÐ",   2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 5, VNS, VG, 1},
{"EMAJAIÈNAIÐ",  2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 6, VNS, VG, 1},
{"IJEITNAIÐ",    2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 1, DGS, VG, 1},
{"ØJØIÈNAIÐ",    2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 2, DGS, VG, 1},
{"SMEISEITNAIÐ", 2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 3, DGS, VG, 1},
{"MEISEITNAIÐ",  2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 3, DGS, VG, 1},
{"SUISOUIÈNAIÐ", 2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 4, DGS, VG, 1},
{"SIAISIAIÈNAIÐ",2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 5, DGS, VG, 1},
{"ESOUISOUIÈNAIÐ",2,0,127,-1,-1,10,0,DAL, BSL, VEIKR, 6, DGS, VG, 1},
{"SOUISOUIÈNAIÐ",2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 6, DGS, VG, 1},

{"SISÀIÐ",       2,1,127,-1,-1,10,0, DAL, BSL, VEIKR, 1, VNS, VG, 0},
{"ISÀIÐ",        2,1,127,-1,-1,10,0, DAL, BSL, VEIKR, 1, DGS, VG, 0},  // v.g.sangr.

{"ITNAIÐ",       2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 1, VNS, MG, 0},
{"SOIÈNAIÐ",     2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 2, VNS, MG, 0},     // m.g.
{"IAIÈNAIÐ",     2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 3, VNS, MG, 0},
{"ÀIÈNAIÐ",      2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 4, VNS, MG, 0},
{"AIÈNAIÐ",      2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 5, VNS, MG, 0},
{"EJOIÈNAIÐ",    2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 6, VNS, MG, 0},
{"JOIÈNAIÐ",     2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 6, VNS, MG, 0},
{"SMOIÈNAIÐ",    2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 3, DGS, MG, 0},
{"MOIÈNAIÐ",     2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 3, DGS, MG, 0},
{"SAIÈNAIÐ",     2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 4, DGS, MG, 0},
{"SIMOIÈNAIÐ",   2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 5, DGS, MG, 0},
{"ESOIÈNAIÐ",    2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 6, DGS, MG, 0},

{"IJOIÈNAIÐ",    2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 1, VNS, MG, 1},
{"SOISOIÈNAIÐ",  2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 2, VNS, MG, 1},  // m.g.ivardz.
{"IAJAIÈNAIÐ",   2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 3, VNS, MG, 1},
{"ÀJÀIÈNAIÐ",    2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 4, VNS, MG, 1},
{"AJÀIÈNAIÐ",    2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 5, VNS, MG, 1},
{"EJOJOIÈNAIÐ",  2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 6, VNS, MG, 1},
{"JOJOIÈNAIÐ",   2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 6, VNS, MG, 1},
{"SMOISOIÈNAIÐ", 2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 3, DGS, MG, 1},
{"MOISOIÈNAIÐ",  2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 3, DGS, MG, 1},
{"SAISÀIÈNAIÐ",  2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 4, DGS, MG, 1},
{"SIMOISOIÈNAIÐ",2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 5, DGS, MG, 1},
{"ESOISOIÈNAIÐ", 2,0,127,-1,-1,10,0, DAL, BSL, VEIKR, 6, DGS, MG, 1},

{"SITNAIÐ",      2,1,127,-1,-1,10,0, DAL, BSL, VEIKR, 1, VNS, MG, 0},
{"ISOIÈNAIÐ",    2,1,127,-1,-1,10,0, DAL, BSL, VEIKR, 1, DGS, MG, 0},  // m.g.sangr.

// 21 Bûtojo laiko neveikiamasis dalyvis
{"SAT",       2,0,127,-1,-1,13,0, DAL, BTL, NEVR, 1, VNS, VG, 0},
{"OT",        2,0,127,-1,-1,13,0, DAL, BTL, NEVR, 2, VNS, VG, 0},          // v.g.
{"MAT",       2,0,127, 1, 1,11,0, DAL, BTL, NEVR, 3, VNS, VG, 0},
{"ÀT",        2,0,127,-1,-1,13,0, DAL, BTL, NEVR, 4, VNS, VG, 0},
{"UT",        2,0,127, 0, 0,15,0, DAL, BTL, NEVR, 5, VNS, VG, 0},
{"EMAT",      2,0,127, 0, 0,11,0, DAL, BTL, NEVR, 6, VNS, VG, 0},
{"IT",        2,0,127, 0, 0,11,0, DAL, BTL, NEVR, 1, DGS, VG, 0},
{"ØT",        2,0,127, 0, 2,11,0, DAL, BTL, NEVR, 2, DGS, VG, 0},
{"SMEIT",     2,0,127, 3, 1,11,0, DAL, BTL, NEVR, 3, DGS, VG, 0},
{"MEIT",      2,0,127, 2, 1,11,0, DAL, BTL, NEVR, 3, DGS, VG, 0},
{"SUT",       2,0,127, 1, 0,15,0, DAL, BTL, NEVR, 4, DGS, VG, 0},
{"SIAT",      2,0,127, 1, 2,11,0, DAL, BTL, NEVR, 5, DGS, VG, 0},
{"ESOUT",     2,0,127, 0, 0,11,0, DAL, BTL, NEVR, 6, DGS, VG, 0},
{"SOUT",      2,0,127, 1, 2,11,0, DAL, BTL, NEVR, 6, DGS, VG, 0},

{"SISAT",     2,0,127, 3, 0,11,0, DAL, BTL, NEVR, 1, VNS, VG, 1},
{"OJOT",      2,0,127,-1,-1,13,0, DAL, BTL, NEVR, 2, VNS, VG, 1},        // v.g.ivardz.
{"MAJAT",     2,0,127, 3, 1,11,0, DAL, BTL, NEVR, 3, VNS, VG, 1},
{"ÁJÀT",      2,0,127,-1,-1,13,0, DAL, BTL, NEVR, 4, VNS, VG, 1},
{"UJOUT",     2,0,127, 3, 1,11,0, DAL, BTL, NEVR, 5, VNS, VG, 1},
{"EMAJAT",    2,0,127, 4, 2,11,0, DAL, BTL, NEVR, 6, VNS, VG, 1},
{"IJEIT",     2,0,127, 3, 1,11,0, DAL, BTL, NEVR, 1, DGS, VG, 1},
{"ØJØT",      2,0,127, 2, 2,11,0, DAL, BTL, NEVR, 2, DGS, VG, 1},
{"SMEISEIT",  2,0,127, 6, 1,11,0, DAL, BTL, NEVR, 3, DGS, VG, 1},
{"MEISEIT",   2,0,127, 5, 1,11,0, DAL, BTL, NEVR, 3, DGS, VG, 1},
{"SUISOUT",   2,0,127, 5, 1,11,0, DAL, BTL, NEVR, 4, DGS, VG, 1},
{"SIAISIAT",  2,0,127, 5, 2,11,0, DAL, BTL, NEVR, 5, DGS, VG, 1},
{"ESOUISOUT", 2,0,127, 6, 2,11,0, DAL, BTL, NEVR, 6, DGS, VG, 1},
{"SOUISOUT",  2,0,127, 5, 2,11,0, DAL, BTL, NEVR, 6, DGS, VG, 1},

{"AT",        2,0,127, 0, 0,11,0, DAL, BTL, NEVR, 1, VNS, MG, 0},
{"SOT",       2,0,127, 1, 2,11,0, DAL, BTL, NEVR, 2, VNS, MG, 0},              // m.g.
{"IAT",       2,0,127, 1, 1,12,0, DAL, BTL, NEVR, 3, VNS, MG, 0},
{"AT",        2,0,127, 0, 0,12,0, DAL, BTL, NEVR, 5, VNS, MG, 0},
{"EJOT",      2,0,127, 0, 0,11,0, DAL, BTL, NEVR, 6, VNS, MG, 0},
{"JOT",       2,0,127, 1, 2,11,0, DAL, BTL, NEVR, 6, VNS, MG, 0},
{"SOT",       2,0,127,-1,-1,13,0, DAL, BTL, NEVR, 1, DGS, MG, 0},
{"SMOT",      2,0,127, 2, 1,11,0, DAL, BTL, NEVR, 3, DGS, MG, 0},
{"MOT",       2,0,127, 1, 1,11,0, DAL, BTL, NEVR, 3, DGS, MG, 0},
{"SAT",       2,0,127, 1, 0,15,0, DAL, BTL, NEVR, 4, DGS, MG, 0},
{"SIMOT",     2,0,127, 1, 1,11,0, DAL, BTL, NEVR, 5, DGS, MG, 0},
{"ESOT",      2,0,127, 0, 0,11,0, DAL, BTL, NEVR, 6, DGS, MG, 0},

{"IJOT",      2,0,127, 2, 1,11,0, DAL, BTL, NEVR, 1, VNS, MG, 1},
{"SOISOT",    2,0,127, 4, 2,11,0, DAL, BTL, NEVR, 2, VNS, MG, 1},         // m.g.ivardz.
{"IAJAT",     2,0,127,-1,-1,13,0, DAL, BTL, NEVR, 3, VNS, MG, 1},
{"ÀJÀT",      2,0,127,-1,-1,13,0, DAL, BTL, NEVR, 4, VNS, MG, 1},
{"AJÀT",      2,0,127, 2, 1,11,0, DAL, BTL, NEVR, 5, VNS, MG, 1},
{"EJOJOT",    2,0,127, 4, 2,11,0, DAL, BTL, NEVR, 6, VNS, MG, 1},
{"JOJOT",     2,0,127, 3, 2,11,0, DAL, BTL, NEVR, 6, VNS, MG, 1},
{"SOISOT",    2,0,127,-1,-1,13,0, DAL, BTL, NEVR, 1, DGS, MG, 1},
{"SMOISOT",   2,0,127, 5, 1,11,0, DAL, BTL, NEVR, 3, DGS, MG, 1},
{"MOISOT",    2,0,127, 4, 1,11,0, DAL, BTL, NEVR, 3, DGS, MG, 1},
{"SAISÀT",    2,0,127, 4, 1,11,0, DAL, BTL, NEVR, 4, DGS, MG, 1},
{"SIMOISOT",  2,0,127, 6, 2,11,0, DAL, BTL, NEVR, 5, DGS, MG, 1},
{"ESOISOT",   2,0,127, 5, 2,11,0, DAL, BTL, NEVR, 6, DGS, MG, 1},

{"AT",        2,0,127,-1,-1,13,0, DAL, BTL, NEVR, -1, -1, BG, 0},
{"ISAT",      2,0,127,-1,-1,13,0, DAL, BTL, NEVR, -1, -1, BG, 0},  // bev.g.

// 22 Bûsimojo laiko neveikiamasis dalyvis
{"SAMIS",     2,0,127,-1,-1,10,0, DAL, BSL, NEVR, 1, VNS, VG, 0},
{"OMIS",      2,0,127,-1,-1,10,0, DAL, BSL, NEVR, 2, VNS, VG, 0},      // v.g.
{"MAMIS",     2,0,127, 1, 1,11,0, DAL, BSL, NEVR, 3, VNS, VG, 0},
{"ÀMIS",      2,0,127,-1,-1,10,0, DAL, BSL, NEVR, 4, VNS, VG, 0},
{"UMIS",      2,0,127,-1,-1,10,0, DAL, BSL, NEVR, 5, VNS, VG, 0},
{"EMAMIS",    2,0,127, 0, 0,11,0, DAL, BSL, NEVR, 6, VNS, VG, 0},
{"IMIS",      2,0,127, 0, 0,11,0, DAL, BSL, NEVR, 1, DGS, VG, 0},
{"ØMIS",      2,0,127, 0, 2,11,0, DAL, BSL, NEVR, 2, DGS, VG, 0},
{"SMEIMIS",   2,0,127, 3, 1,11,0, DAL, BSL, NEVR, 3, DGS, VG, 0},
{"MEIMIS",    2,0,127, 2, 1,11,0, DAL, BSL, NEVR, 3, DGS, VG, 0},
{"SUMIS",     2,0,127,-1,-1,10,0, DAL, BSL, NEVR, 4, DGS, VG, 0},
{"SIAMIS",    2,0,127, 1, 2,11,0, DAL, BSL, NEVR, 5, DGS, VG, 0},
{"ESOUMIS",   2,0,127, 0, 0,11,0, DAL, BSL, NEVR, 6, DGS, VG, 0},
{"SOUMIS",    2,0,127, 1, 2,11,0, DAL, BSL, NEVR, 6, DGS, VG, 0},

{"SISAMIS",   2,0,127, 3, 0,11,0, DAL, BSL, NEVR, 1, VNS, VG, 1},
{"OJOMIS",    2,0,127,-1,-1,10,0, DAL, BSL, NEVR, 2, VNS, VG, 1},    // v.g.ivardz.
{"MAJAMIS",   2,0,127, 3, 1,11,0, DAL, BSL, NEVR, 3, VNS, VG, 1},
{"ÁJÀMIS",    2,0,127,-1,-1,10,0, DAL, BSL, NEVR, 4, VNS, VG, 1},
{"UJOUMIS",   2,0,127, 3, 1,11,0, DAL, BSL, NEVR, 5, VNS, VG, 1},
{"EMAJAMIS",  2,0,127, 4, 2,11,0, DAL, BSL, NEVR, 6, VNS, VG, 1},
{"IJEIMIS",   2,0,127, 3, 1,11,0, DAL, BSL, NEVR, 1, DGS, VG, 1},
{"ØJØMIS",    2,0,127, 2, 2,11,0, DAL, BSL, NEVR, 2, DGS, VG, 1},
{"SMEISEIMIS",2,0,127, 6, 1,11,0, DAL, BSL, NEVR, 3, DGS, VG, 1},
{"MEISEIMIS", 2,0,127, 5, 1,11,0, DAL, BSL, NEVR, 3, DGS, VG, 1},
{"SUISOUMIS", 2,0,127, 5, 1,11,0, DAL, BSL, NEVR, 4, DGS, VG, 1},
{"SIAISIAMIS",2,0,127, 5, 2,11,0, DAL, BSL, NEVR, 5, DGS, VG, 1},
{"ESOUISOUMIS",2,0,127,6, 2,11,0, DAL, BSL, NEVR, 6, DGS, VG, 1},
{"SOUISOUMIS",2,0,127, 5, 2,11,0, DAL, BSL, NEVR, 6, DGS, VG, 1},

{"AMIS",      2,0,127, 0, 0,11,0, DAL, BSL, NEVR, 1, VNS, MG, 0},
{"SOMIS",     2,0,127, 1, 2,11,0, DAL, BSL, NEVR, 2, VNS, MG, 0},          // m.g.
{"IAMIS",     2,0,127,-1,-1,10,0, DAL, BSL, NEVR, 3, VNS, MG, 0},
{"AMIS",      2,0,127,-1,-1,10,0, DAL, BSL, NEVR, 5, VNS, MG, 0},
{"EJOMIS",    2,0,127, 0, 0,11,0, DAL, BSL, NEVR, 6, VNS, MG, 0},
{"JOMIS",     2,0,127, 1, 2,11,0, DAL, BSL, NEVR, 6, VNS, MG, 0},
{"SOMIS",     2,0,127,-1,-1,10,0, DAL, BSL, NEVR, 1, DGS, MG, 0},
{"SMOMIS",    2,0,127, 2, 1,11,0, DAL, BSL, NEVR, 3, DGS, MG, 0},
{"MOMIS",     2,0,127, 1, 1,11,0, DAL, BSL, NEVR, 3, DGS, MG, 0},
{"SAMIS",     2,0,127,-1,-1,10,0, DAL, BSL, NEVR, 4, DGS, MG, 0},
{"SIMOMIS",   2,0,127, 1, 0,11,0, DAL, BSL, NEVR, 5, DGS, MG, 0},
{"ESOMIS",    2,0,127, 0, 0,11,0, DAL, BSL, NEVR, 6, DGS, MG, 0},

{"IJOMIS",    2,0,127, 2, 1,11,0, DAL, BSL, NEVR, 1, VNS, MG, 1},
{"SOISOMIS",  2,0,127, 4, 2,11,0, DAL, BSL, NEVR, 2, VNS, MG, 1},     // m.g.ivardz.
{"IAJAMIS",   2,0,127,-1,-1,10,0, DAL, BSL, NEVR, 3, VNS, MG, 1},
{"ÀJÀMIS",    2,0,127,-1,-1,10,0, DAL, BSL, NEVR, 4, VNS, MG, 1},
{"AJÀMIS",    2,0,127, 2, 1,11,0, DAL, BSL, NEVR, 5, VNS, MG, 1},
{"EJOJOMIS",  2,0,127, 4, 2,11,0, DAL, BSL, NEVR, 6, VNS, MG, 1},
{"JOJOMIS",   2,0,127, 3, 2,11,0, DAL, BSL, NEVR, 6, VNS, MG, 1},
{"SOISOMIS",  2,0,127,-1,-1,10,0, DAL, BSL, NEVR, 1, DGS, MG, 1},
{"SMOISOMIS", 2,0,127, 5, 1,11,0, DAL, BSL, NEVR, 3, DGS, MG, 1},
{"MOISOMIS",  2,0,127, 4, 1,11,0, DAL, BSL, NEVR, 3, DGS, MG, 1},
{"SAISÀMIS",  2,0,127, 4, 1,11,0, DAL, BSL, NEVR, 4, DGS, MG, 1},
{"SIMOISOMIS",2,0,127, 6, 2,11,0, DAL, BSL, NEVR, 5, DGS, MG, 1},
{"ESOISOMIS", 2,0,127, 5, 2,11,0, DAL, BSL, NEVR, 6, DGS, MG, 1},

{"AMIS",      2,0,127,-1,-1,10,0, DAL, BSL, NEVR, -1, -1, BG, 0},
{"ISAMIS",    2,0,127,-1,-1,10,0, DAL, BSL, NEVR, -1, -1, BG, 0},  // bev.g.

{"SAMIÐ",     2,0,127,-1,-1,10,0, DAL, BSL, NEVR, 1, VNS, VG, 0},
{"OMIÐ",      2,0,127,-1,-1,10,0, DAL, BSL, NEVR, 2, VNS, VG, 0},      // v.g.
{"MAMIÐ",     2,0,127, 1, 1,11,0, DAL, BSL, NEVR, 3, VNS, VG, 0},
{"ÀMIÐ",      2,0,127,-1,-1,10,0, DAL, BSL, NEVR, 4, VNS, VG, 0},
{"UMIÐ",      2,0,127,-1,-1,10,0, DAL, BSL, NEVR, 5, VNS, VG, 0},
{"EMAMIÐ",    2,0,127, 0, 0,11,0, DAL, BSL, NEVR, 6, VNS, VG, 0},
{"IMIÐ",      2,0,127, 0, 0,11,0, DAL, BSL, NEVR, 1, DGS, VG, 0},
{"ØMIÐ",      2,0,127, 0, 2,11,0, DAL, BSL, NEVR, 2, DGS, VG, 0},
{"SMEIMIÐ",   2,0,127, 3, 1,11,0, DAL, BSL, NEVR, 3, DGS, VG, 0},
{"MEIMIÐ",    2,0,127, 2, 1,11,0, DAL, BSL, NEVR, 3, DGS, VG, 0},
{"SUMIÐ",     2,0,127,-1,-1,10,0, DAL, BSL, NEVR, 4, DGS, VG, 0},
{"SIAMIÐ",    2,0,127, 1, 2,11,0, DAL, BSL, NEVR, 5, DGS, VG, 0},
{"ESOUMIÐ",   2,0,127, 0, 0,11,0, DAL, BSL, NEVR, 6, DGS, VG, 0},
{"SOUMIÐ",    2,0,127, 1, 2,11,0, DAL, BSL, NEVR, 6, DGS, VG, 0},

{"SISAMIÐ",   2,0,127, 3, 0,11,0, DAL, BSL, NEVR, 1, VNS, VG, 1},
{"OJOMIÐ",    2,0,127,-1,-1,10,0, DAL, BSL, NEVR, 2, VNS, VG, 1},    // v.g.ivardz.
{"MAJAMIÐ",   2,0,127, 3, 1,11,0, DAL, BSL, NEVR, 3, VNS, VG, 1},
{"ÁJÀMIÐ",    2,0,127,-1,-1,10,0, DAL, BSL, NEVR, 4, VNS, VG, 1},
{"UJOUMIÐ",   2,0,127, 3, 1,11,0, DAL, BSL, NEVR, 5, VNS, VG, 1},
{"EMAJAMIÐ",  2,0,127, 4, 2,11,0, DAL, BSL, NEVR, 6, VNS, VG, 1},
{"IJEIMIÐ",   2,0,127, 3, 1,11,0, DAL, BSL, NEVR, 1, DGS, VG, 1},
{"ØJØMIÐ",    2,0,127, 2, 2,11,0, DAL, BSL, NEVR, 2, DGS, VG, 1},
{"SMEISEIMIÐ",2,0,127, 6, 1,11,0, DAL, BSL, NEVR, 3, DGS, VG, 1},
{"MEISEIMIÐ", 2,0,127, 5, 1,11,0, DAL, BSL, NEVR, 3, DGS, VG, 1},
{"SUISOUMIÐ", 2,0,127, 5, 1,11,0, DAL, BSL, NEVR, 4, DGS, VG, 1},
{"SIAISIAMIÐ",2,0,127, 5, 2,11,0, DAL, BSL, NEVR, 5, DGS, VG, 1},
{"ESOUISOUMIÐ",2,0,127,6, 2,11,0, DAL, BSL, NEVR, 6, DGS, VG, 1},
{"SOUISOUMIÐ",2,0,127, 5, 2,11,0, DAL, BSL, NEVR, 6, DGS, VG, 1},

{"AMIÐ",      2,0,127, 0, 0,11,0, DAL, BSL, NEVR, 1, VNS, MG, 0},
{"SOMIÐ",     2,0,127, 1, 2,11,0, DAL, BSL, NEVR, 2, VNS, MG, 0},          // m.g.
{"IAMIÐ",     2,0,127,-1,-1,10,0, DAL, BSL, NEVR, 3, VNS, MG, 0},
{"AMIÐ",      2,0,127,-1,-1,10,0, DAL, BSL, NEVR, 5, VNS, MG, 0},
{"EJOMIÐ",    2,0,127, 0, 0,11,0, DAL, BSL, NEVR, 6, VNS, MG, 0},
{"JOMIÐ",     2,0,127, 1, 2,11,0, DAL, BSL, NEVR, 6, VNS, MG, 0},
{"SOMIÐ",     2,0,127,-1,-1,10,0, DAL, BSL, NEVR, 1, DGS, MG, 0},
{"SMOMIÐ",    2,0,127, 2, 1,11,0, DAL, BSL, NEVR, 3, DGS, MG, 0},
{"MOMIÐ",     2,0,127, 1, 1,11,0, DAL, BSL, NEVR, 3, DGS, MG, 0},
{"SAMIÐ",     2,0,127,-1,-1,10,0, DAL, BSL, NEVR, 4, DGS, MG, 0},
{"SIMOMIÐ",   2,0,127, 1, 0,11,0, DAL, BSL, NEVR, 5, DGS, MG, 0},
{"ESOMIÐ",    2,0,127, 0, 0,11,0, DAL, BSL, NEVR, 6, DGS, MG, 0},

{"IJOMIÐ",    2,0,127, 2, 1,11,0, DAL, BSL, NEVR, 1, VNS, MG, 1},
{"SOISOMIÐ",  2,0,127, 4, 2,11,0, DAL, BSL, NEVR, 2, VNS, MG, 1},     // m.g.ivardz.
{"IAJAMIÐ",   2,0,127,-1,-1,10,0, DAL, BSL, NEVR, 3, VNS, MG, 1},
{"ÀJÀMIÐ",    2,0,127,-1,-1,10,0, DAL, BSL, NEVR, 4, VNS, MG, 1},
{"AJÀMIÐ",    2,0,127, 2, 1,11,0, DAL, BSL, NEVR, 5, VNS, MG, 1},
{"EJOJOMIÐ",  2,0,127, 4, 2,11,0, DAL, BSL, NEVR, 6, VNS, MG, 1},
{"JOJOMIÐ",   2,0,127, 3, 2,11,0, DAL, BSL, NEVR, 6, VNS, MG, 1},
{"SOISOMIÐ",  2,0,127,-1,-1,10,0, DAL, BSL, NEVR, 1, DGS, MG, 1},
{"SMOISOMIÐ", 2,0,127, 5, 1,11,0, DAL, BSL, NEVR, 3, DGS, MG, 1},
{"MOISOMIÐ",  2,0,127, 4, 1,11,0, DAL, BSL, NEVR, 3, DGS, MG, 1},
{"SAISÀMIÐ",  2,0,127, 4, 1,11,0, DAL, BSL, NEVR, 4, DGS, MG, 1},
{"SIMOISOMIÐ",2,0,127, 6, 2,11,0, DAL, BSL, NEVR, 5, DGS, MG, 1},
{"ESOISOMIÐ", 2,0,127, 5, 2,11,0, DAL, BSL, NEVR, 6, DGS, MG, 1},

{"AMIÐ",      2,0,127,-1,-1,10,0, DAL, BSL, NEVR, -1, -1, BG, 0},
{"ISAMIÐ",    2,0,127,-1,-1,10,0, DAL, BSL, NEVR, -1, -1, BG, 0},  // bev.g.

// 23 Reikiamybäs dalyvis
{"SANIT",     2,0,127,-1,-1,10,0, DAL, -1, REIK, 1, VNS, VG, 0},
{"ONIT",      2,0,127,-1,-1,10,0, DAL, -1, REIK, 2, VNS, VG, 0},  // v.g.
{"MANIT",     2,0,127, 1, 1,11,0, DAL, -1, REIK, 3, VNS, VG, 0},
{"ÀNIT",      2,0,127,-1,-1,10,0, DAL, -1, REIK, 4, VNS, VG, 0},
{"UNIT",      2,0,127,-1,-1,10,0, DAL, -1, REIK, 5, VNS, VG, 0},
{"EMANIT",    2,0,127, 0, 0,11,0, DAL, -1, REIK, 6, VNS, VG, 0},
{"INIT",      2,0,127, 0, 0,11,0, DAL, -1, REIK, 1, DGS, VG, 0},
{"ØNIT",      2,0,127, 0, 2,11,0, DAL, -1, REIK, 2, DGS, VG, 0},
{"SMEINIT",   2,0,127, 3, 1,11,0, DAL, -1, REIK, 3, DGS, VG, 0},
{"MEINIT",    2,0,127, 2, 1,11,0, DAL, -1, REIK, 3, DGS, VG, 0},
{"SUNIT",     2,0,127,-1,-1,10,0, DAL, -1, REIK, 4, DGS, VG, 0},
{"SIANIT",    2,0,127, 1, 2,11,0, DAL, -1, REIK, 5, DGS, VG, 0},
{"ESOUNIT",   2,0,127, 0, 0,11,0, DAL, -1, REIK, 6, DGS, VG, 0},
{"SOUNIT",    2,0,127, 1, 2,11,0, DAL, -1, REIK, 6, DGS, VG, 0},

{"SISANIT",   2,0,127, 3, 0,11,0, DAL, -1, REIK, 1, VNS, VG, 1},
{"OJONIT",    2,0,127,-1,-1,13,0, DAL, -1, REIK, 2, VNS, VG, 1},  // v.g.ivardz.
{"MAJANIT",   2,0,127, 3, 1,11,0, DAL, -1, REIK, 3, VNS, VG, 1},
{"ÁJÀNIT",    2,0,127,-1,-1,13,0, DAL, -1, REIK, 4, VNS, VG, 1},
{"UJOUNIT",   2,0,127, 3, 1,11,0, DAL, -1, REIK, 5, VNS, VG, 1},
{"EMAJANIT",  2,0,127, 4, 2,11,0, DAL, -1, REIK, 6, VNS, VG, 1},
{"IJEINIT",   2,0,127, 3, 1,11,0, DAL, -1, REIK, 1, DGS, VG, 1},
{"ØJØNIT",    2,0,127, 2, 2,11,0, DAL, -1, REIK, 2, DGS, VG, 1},
{"SMEISEINIT",2,0,127, 6, 1,11,0, DAL, -1, REIK, 3, DGS, VG, 1},
{"MEISEINIT", 2,0,127, 5, 1,11,0, DAL, -1, REIK, 3, DGS, VG, 1},
{"SUISOUNIT", 2,0,127, 5, 1,11,0, DAL, -1, REIK, 4, DGS, VG, 1},
{"SIAISIANIT",2,0,127, 5, 2,11,0, DAL, -1, REIK, 5, DGS, VG, 1},
{"ESOUISOUNIT",2,0,127,6, 2,11,0, DAL, -1, REIK, 6, DGS, VG, 1},
{"SOUISOUNIT",2,0,127, 5, 2,11,0, DAL, -1, REIK, 6, DGS, VG, 1},

{"ANIT",      2,0,127, 0, 0,11,0, DAL, -1, REIK, 1, VNS, MG, 0},
{"SONIT",     2,0,127, 1, 2,11,0, DAL, -1, REIK, 2, VNS, MG, 0},              // m.g.
{"IANIT",     2,0,127,-1,-1,10,0, DAL, -1, REIK, 3, VNS, MG, 0},
{"ANIT",      2,0,127,-1,-1,10,0, DAL, -1, REIK, 5, VNS, MG, 0},
{"EJONIT",    2,0,127, 0, 0,11,0, DAL, -1, REIK, 6, VNS, MG, 0},
{"JONIT",     2,0,127, 1, 2,11,0, DAL, -1, REIK, 6, VNS, MG, 0},
{"SONIT",     2,0,127,-1,-1,10,0, DAL, -1, REIK, 1, DGS, MG, 0},
{"SMONIT",    2,0,127, 2, 1,11,0, DAL, -1, REIK, 3, DGS, MG, 0},
{"MONIT",     2,0,127, 1, 1,11,0, DAL, -1, REIK, 3, DGS, MG, 0},
{"SANIT",     2,0,127,-1,-1,10,0, DAL, -1, REIK, 4, DGS, MG, 0},
{"SIMONIT",   2,0,127, 1, 1,11,0, DAL, -1, REIK, 5, DGS, MG, 0},
{"ESONIT",    2,0,127, 0, 0,11,0, DAL, -1, REIK, 6, DGS, MG, 0},

{"IJONIT",    2,0,127, 2, 1,11,0, DAL, -1, REIK, 1, VNS, MG, 1},
{"SOISONIT",  2,0,127, 4, 2,11,0, DAL, -1, REIK, 2, VNS, MG, 1},         // m.g.ivardz.
{"IAJANIT",   2,0,127,-1,-1,13,0, DAL, -1, REIK, 3, VNS, MG, 1},
{"ÀJÀNIT",    2,0,127,-1,-1,13,0, DAL, -1, REIK, 4, VNS, MG, 1},
{"AJÀNIT",    2,0,127, 2, 1,11,0, DAL, -1, REIK, 5, VNS, MG, 1},
{"EJOJONIT",  2,0,127, 4, 2,11,0, DAL, -1, REIK, 6, VNS, MG, 1},
{"JOJONIT",   2,0,127, 3, 2,11,0, DAL, -1, REIK, 6, VNS, MG, 1},
{"SOISONIT",  2,0,127,-1,-1,13,0, DAL, -1, REIK, 1, DGS, MG, 1},
{"SMOISONIT", 2,0,127, 5, 1,11,0, DAL, -1, REIK, 3, DGS, MG, 1},
{"MOISONIT",  2,0,127, 4, 1,11,0, DAL, -1, REIK, 3, DGS, MG, 1},
{"SAISÀNIT",  2,0,127, 4, 1,11,0, DAL, -1, REIK, 4, DGS, MG, 1},
{"SIMOISONIT",2,0,127, 6, 2,11,0, DAL, -1, REIK, 5, DGS, MG, 1},
{"ESOISONIT", 2,0,127, 5, 2,11,0, DAL, -1, REIK, 6, DGS, MG, 1},

{"ANIT",      2,0,127,-1,-1,10,0, DAL, -1, REIK, -1, -1, BG, 0}, // bev.g.

// 24 Bûdinys
{"ET",        2,0,127, 0, 0,11,0, BUDN, -1, -1, -1, -1, -1, -1},
{"IANIT",     2,0,127, 0, 2,11,0, BUDN, -1, -1, -1, -1, -1, -1},

// 25 Bûtojo laiko neveikiamasis prieveiksmis
{"IAT",       2,0,127, 0, 2,11,0}};

#define VPriesdSk 252

struct PriesdeliuGrupes{const char *Pavadinimas; char VisadKirc; char KircRaide;
                        char Priegaide;} PriesdGrup[VPriesdSk] = {
{"",0,0,0},
{"AP",0,0,0}, {"API",0,2,0}, {"AT",0,0,0}, {"ATI",0,2,0},
{"Á",0,0,2}, {"IÐ",0,0,0}, {"NU",0,1,0}, {"PA",0,1,0},
{"PAR",0,2,2}, {"PRA",0,2,0}, {"PRI",0,2,0}, {"SU",0,1,0},
{"UÞ",0,0,0}, {"NE",0,1,0}, {"NEBE",0,3,0}, {"TE",0,1,0},
{"TEBE",0,3,0}, {"BE",0,1,0}, {"PER",1,1,1},

{"NEAP",0,2,0}, {"NEAPI",0,4,0}, {"NEAT",0,2,0}, {"NEATI",0,4,0},
{"NEÁ",0,2,2}, {"NEIÐ",0,2,0}, {"NENU",0,3,0}, {"NEPA",0,3,0},
{"NEPAR",0,4,2}, {"NEPRA",0,4,0}, {"NEPRI",0,4,0}, {"NESU",0,3,0},
{"NEUÞ",0,2,0}, {"NEPER",1,3,1},

{"BEAP",0,2,0}, {"BEAPI",0,4,0}, {"BEAT",0,2,0}, {"BEATI",0,4,0},
{"BEÁ",0,2,2}, {"BEIÐ",0,2,0}, {"BENU",0,3,0}, {"BEPA",0,3,0},
{"BEPAR",0,4,2}, {"BEPRA",0,4,0}, {"BEPRI",0,4,0}, {"BESU",0,3,0},
{"BEUÞ",0,2,0}, {"BEPER",1,3,1},

{"NEBEAP",0,4,0}, {"NEBEAPI",0,6,0}, {"NEBEAT",0,4,0}, {"NEBEATI",0,6,0},
{"NEBEÁ",0,4,2}, {"NEBEIÐ",0,4,0}, {"NEBENU",0,5,0}, {"NEBEPA",0,5,0},
{"NEBEPAR",0,6,2}, {"NEBEPRA",0,6,0}, {"NEBEPRI",0,6,0}, {"NEBESU",0,5,0},
{"NEBEUÞ",0,4,0}, {"NEBEPER",1,5,1},

{"TEAP",0,2,0}, {"TEAPI",0,4,0}, {"TEAT",0,2,0}, {"TEATI",0,4,0},
{"TEÁ",0,2,2}, {"TEIÐ",0,2,0}, {"TENU",0,3,0}, {"TEPA",0,3,0},
{"TEPAR",0,4,2}, {"TEPRA",0,4,0}, {"TEPRI",0,4,0}, {"TESU",0,3,0},
{"TEUÞ",0,2,0}, {"TENE",0,3,0}, {"TENEBE",0,5,0}, {"TEPER",1,3,1},

{"TEBEAP",0,4,0}, {"TEBEAPI",0,6,0}, {"TEBEAT",0,4,0}, {"TEBEATI",0,6,0},
{"TEBEÁ",0,4,2}, {"TEBEIÐ",0,4,0}, {"TEBENU",0,5,0}, {"TEBEPA",0,5,0},
{"TEBEPAR",0,6,2}, {"TEBEPRA",0,6,0}, {"TEBEPRI",0,6,0}, {"TEBESU",0,5,0},
{"TEBEUÞ",0,4,0}, {"TEBENE",0,5,0}, {"TEBEPER",1,5,1},

{"TENEAP",0,4,0}, {"TENEAPI",0,6,0}, {"TENEAT",0,4,0}, {"TENEATI",0,6,0},
{"TENEÁ",0,4,2}, {"TENEIÐ",0,4,0}, {"TENENU",0,5,0}, {"TENEPA",0,5,0},
{"TENEPAR",0,6,2}, {"TENEPRA",0,6,0}, {"TENEPRI",0,6,0}, {"TENESU",0,5,0},
{"TENEUÞ",0,4,0}, {"TENEPER",1,5,1},

{"TENEBEAP",0,6,0}, {"TENEBEAPI",0,8,0}, {"TENEBEAT",0,6,0}, {"TENEBEATI",0,8,0},
{"TENEBEÁ",0,6,2}, {"TENEBEIÐ",0,6,0}, {"TENEBENU",0,7,0}, {"TENEBEPA",0,7,0},
{"TENEBEPAR",0,8,2}, {"TENEBEPRA",0,8,0}, {"TENEBEPRI",0,8,0}, {"TENEBESU",0,7,0},
{"TENEBEUÞ",0,6,0}, {"TENEBEPER",1,7,1},

{"TEBENEAP",0,6,0}, {"TEBENEAPI",0,8,0}, {"TEBENEAT",0,6,0}, {"TEBENEATI",0,8,0},
{"TEBENEÁ",0,6,2}, {"TEBENEIÐ",0,6,0}, {"TEBENENU",0,7,0}, {"TEBENEPA",0,7,0},
{"TEBENEPAR",0,8,2}, {"TEBENEPRA",0,8,0}, {"TEBENEPRI",0,8,0}, {"TEBENESU",0,7,0},
{"TEBENEUÞ",0,6,0}, {"TEBENEPER",1,7,1},

{"APSI",0,3,0}, {"ATSI",0,3,0}, {"ÁSI",0,2,0}, {"IÐSI",0,3,0},
{"NUSI",0,3,0}, {"PASI",0,3,0}, {"PARSI",0,4,0}, {"PRASI",0,4,0},
{"PRISI",0,4,0}, {"SUSI",0,3,0}, {"UÞSI",0,3,0}, {"NESI",0,3,0},
{"NEBESI",0,5,0}, {"TESI",0,3,0}, {"TEBESI",0,5,0}, {"PERSI",1,1,1},
{"BESI",0,3,0},//{"BNESI",0,3,0},

{"NEAPSI",0,5,0}, {"NEATSI",0,5,0}, {"NEÁSI",0,4,0}, {"NEIÐSI",0,5,0},
{"NENUSI",0,5,0}, {"NEPASI",0,5,0}, {"NEPARSI",0,6,0}, {"NEPRASI",0,6,0},
{"NEPRISI",0,6,0}, {"NESUSI",0,5,0}, {"NEUÞSI",0,5,0}, {"NEPERSI",1,3,1},

{"BEAPSI",0,5,0}, {"BEATSI",0,5,0}, {"BEÁSI",0,4,0}, {"BEIÐSI",0,5,0},
{"BENUSI",0,5,0}, {"BEPASI",0,5,0}, {"BEPARSI",0,6,0}, {"BEPRASI",0,6,0},
{"BEPRISI",0,6,0}, {"BESUSI",0,5,0}, {"BEUÞSI",0,5,0}, {"BEPERSI",1,3,1},

{"NEBEAPSI",0,7,0}, {"NEBEATSI",0,7,0}, {"NEBEÁSI",0,6,0}, {"NEBEIÐSI",0,7,0},
{"NEBENUSI",0,7,0}, {"NEBEPASI",0,7,0}, {"NEBEPARSI",0,8,0}, {"NEBEPRASI",0,8,0},
{"NEBEPRISI",0,8,0}, {"NEBESUSI",0,7,0}, {"NEBEUÞSI",0,7,0}, {"NEBEPERSI",1,5,1},

{"TEAPSI",0,5,0}, {"TEATSI",0,5,0}, {"TEÁSI",0,4,0}, {"TEIÐSI",0,5,0},
{"TENUSI",0,5,0}, {"TEPASI",0,5,0}, {"TEPARSI",0,6,0}, {"TEPRASI",0,6,0},
{"TEPRISI",0,6,0}, {"TESUSI",0,5,0}, {"TEUÞSI",0,5,0}, {"TENESI",0,5,0},
{"TENEBESI",0,7,0}, {"TEPERSI",1,3,1},

{"TEBEAPSI",0,7,0}, {"TEBEATSI",0,7,0}, {"TEBEÁSI",0,6,0}, {"TEBEIÐSI",0,7,0},
{"TEBENUSI",0,7,0}, {"TEBEPASI",0,7,0}, {"TEBEPARSI",0,8,0}, {"TEBEPRASI",0,8,0},
{"TEBEPRISI",0,8,0}, {"TEBESUSI",0,7,0}, {"TEBEUÞSI",0,7,0}, {"TEBENESI",0,7,0},
{"TEBENEBESI",0,9,0}, {"TEBEPERSI",1,5,1},
						
{"TENEAPSI",0,7,0}, {"TENEATSI",0,7,0}, {"TENEÁSI",0,6,0}, {"TENEIÐSI",0,7,0},
{"TENENUSI",0,7,0}, {"TENEPASI",0,7,0}, {"TENEPARSI",0,8,0}, {"TENEPRASI",0,8,0},
{"TENEPRISI",0,8,0}, {"TENESUSI",0,7,0}, {"TENEUÞSI",0,7,0}, {"TENEPERSI",1,5,1},

{"TENEBEAPSI",0,9,0}, {"TENEBEATSI",0,9,0}, {"TENEBEÁSI",0,8,0}, {"TENEBEIÐSI",0,9,0},
{"TENEBENUSI",0,9,0}, {"TENEBEPASI",0,9,0}, {"TENEBEPARSI",0,10,0}, {"TENEBEPRASI",0,10,0},
{"TENEBEPRISI",0,10,0}, {"TENEBESUSI",0,9,0}, {"TENEBEUÞSI",0,9,0}, {"TENEBEPERSI",1,7,1},

{"TEBENEAPSI",0,9,0}, {"TEBENEATSI",0,9,0}, {"TEBENEÁSI",0,8,0}, {"TEBENEIÐSI",0,9,0},
{"TEBENENUSI",0,9,0}, {"TEBENEPASI",0,9,0}, {"TEBENEPARSI",0,10,0}, {"TEBENEPRASI",0,10,0},
{"TEBENEPRISI",0,10,0}, {"TEBENESUSI",0,9,0}, {"TEBENEUÞSI",0,9,0}, {"TEBENEPERSI",1,7,1}}; 

#else
extern struct VeiksmazodziuGalunes{char *Galune; char KamTipas; char Sangrazine;
                            char Asmenuote; char KircRaide; char Priegaide;
	                        char KircTaisykle; char PriesdTE;
							char KalbDal; char Laikas; char NuosakaRusis;
							char AsmuoLinksnis; char Skaicius;
							char Gimine; char Apibreztumas;} GalMasV[1089];
extern struct PriesdeliuGrupes{char *Pavadinimas; char VisadKirc; char KircRaide;
                        char Priegaide;} PriesdGrup[252];
#endif
