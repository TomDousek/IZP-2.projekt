#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#define PODMINKA_OKRAJE(c, r, map) ((((c - 1) % map->cols) == 0) || ((r == 1) && (((r - 1) * map->cols + (c - 1)) % 2) == 0) || (((r == map->rows) && ((((map->cols % 2) != 0) && ((((r - 1) * map->cols + (c - 1)) % 2) != 0)) || (((map->cols % 2) == 0) && (((((r % 2) == 0) && ((((r - 1) * map->cols + (c - 1)) % 2) == 0))) || (((r % 2) != 0) && ((((r - 1) * map->cols + (c - 1)) % 2) != 0))))))) || ((c % (map->cols)) == 0))

// 🐏

typedef struct
{
	int rows;
	int cols;
	unsigned char *cells;
} Map;

// funkce zjisti, zda je dane hranici zed
bool isborder(Map *map, int r, int c, int border)
{
	int p[3] = {0, 0, 0};
	// nacitam hodnotu aktualniho policka
	int hod = map->cells[(r - 1) * map->cols + (c - 1)];
	// zdi reprezentuji v triprvkovem poli hodnotou 1
	// pokud mohu od hodnoty policka odecist 4, resp. 2, 1, tak je na dane
	// hranici zed
	for (int i = 0; i < 3; i++)
	{
		if (hod - 4 >= 0)
		{
			p[2] = 1;
			hod -= 4;
		}
		if (hod - 2 >= 0)
		{
			p[1] = 1;
			hod -= 2;
		}
		if (hod - 1 == 0)
		{
			p[0] = 1;
			hod -= 1;
		}
	}
	if (p[border] == 1)
	{ // overeni zdi na konkretni hranici
		return true;
	}
	else
		return false;
}

int start_border(Map *map, int r, int c, int leftright, int *smer)
{
	// bude vracet 0 = leva, 1 = prava, 2 = h/d hranice, 3 kdyz nastane chyba

	// Funkce vraci returnem hodnotu prvni hranice a smer
	// ze ktereho jsme prisli.
	// algoritmus:
	//			  1) nastane podminka podle aktualni polohy
	//			  2) je na dane hranici zed?
	//			  3) pokud ne, tak je smer prichodu ze strany teto hranice
	//			  4) vraceni prvni hranice

	if (leftright == 1)
	{ // pravidlo prave ruky
		if (((c - 1) % map->cols) == 0)
		{ // vstup do bludiste zleva
			if (map->cols == 1)
			{
				if (!isborder(map, r, c, 0))
				{
					*smer = 0;
					if ((r % 2) == 0)
					{
						return 2;
					}
					else
						return 1;
				}
				else if (!isborder(map, r, c, 1))
				{
					*smer = 1;
					if ((r % 2) == 0)
					{
						return 1;
					}
					else
						return 2;
				}
			}
			if (r == 1)
			{ // horni hrana
				if (isborder(map, r, c, 0))
				{
					*smer = 3;
				}
				else
					*smer = 0;
			}
			else if (r == map->rows)
			{ // dolni hrana
				if (isborder(map, r, c, 0))
				{
					*smer = 2;
				}
				else
					*smer = 0;
			}
			else
				*smer = 0; // zbytek
			if ((r % 2) != 0)
			{
				if (r == 1 && c == 1)
				{
					if (isborder(map, r, c, 0))
					{
						return 0;
					}
					else
						return 1;
				}
				return 1;
			}
			else
			{
				return 2;
			}
		}
		else if ((c % map->cols) == 0)
		{
			if (r == 1)
			{
				if (isborder(map, r, c, 2))
				{
					*smer = 1;
				}
				else
					*smer = 3;
			}
			else if (r == map->rows)
			{
				if (isborder(map, r, c, 2))
				{
					*smer = 1;
				}
				else
					*smer = 2;
			}
			else
				*smer = 1;

			if ((map->cols % 2) == 0)
			{
				if ((r % 2) == 0)
				{
					return 2;
				}
				else
				{
					return 0;
				}
			}
			else
			{
				if ((r % 2) == 0)
				{
					return 0;
				}
				else
				{
					return 2;
				}
			}
		}
		else if (r == 1)
		{
			if (map->rows == 1)
			{
				if ((c % 2) == 0)
				{
					*smer = 2;
					return 1;
				}
			}
			*smer = 3;
			return 0;
		}
		else if (r == map->rows)
		{
			*smer = 2;
			return 1;
		}
	}
	else
	{ // pravidlo leve ruky
		if (((c - 1) % map->cols) == 0)
		{
			if (map->cols == 1)
			{
				if (!isborder(map, r, c, 0))
				{
					*smer = 0;
					if ((r % 2) == 0)
					{
						return 1;
					}
					else
						return 2;
				}
				else if (!isborder(map, r, c, 1))
				{
					*smer = 1;
					if ((r % 2) == 0)
					{
						return 2;
					}
					else
						return 1;
				}
			}
			if (r == 1)
			{
				if (isborder(map, r, c, 0))
				{
					*smer = 3;
				}
				else
					*smer = 0;
			}
			else if (r == map->rows)
			{
				if (isborder(map, r, c, 0))
				{
					*smer = 2;
				}
				else
					*smer = 0;
			}
			else
				*smer = 0;
			if ((r % 2) != 0)
			{
				return 2;
			}
			else
				return 1;
		}
		else if ((c % map->cols) == 0)
		{
			if (r == 1)
			{
				if (isborder(map, r, c, 2))
				{
					*smer = 1;
				}
				else
					*smer = 3;
			}
			else if (r == map->rows)
			{
				if (isborder(map, r, c, 2))
				{
					*smer = 1;
				}
				else
					*smer = 2;
			}
			else
				*smer = 1;
			if ((map->cols % 2) == 0)
			{
				if ((r % 2) == 0)
				{
					return 0;
				}
				else
					return 2;
			}
			else
			{
				if ((r % 2) == 0)
				{
					return 2;
				}
				else
					return 0;
			}
		}
		else if (r == 1)
		{
			if (map->rows == 1)
			{
				*smer = 2;
				return 0;
			}
			*smer = 3;
			return 1;
		}
		else if (r == map->rows)
		{
			*smer = 2;
			return 0;
		}
	}
	return 3;
}

bool kontrola_kraje(Map *map, int r, int c)
{

	// Funkce zkontroluje, zda jsme na kraji a zda je mozne vstoupit na danem
	// miste do bludiste, tzn. funkce umozni vstup pouze pokud jsme na okraji
	// a neni na okrajove hranici zed.

	if (r < 1 || c < 1 || r > map->rows || c > map->cols)
	{
		return false;
	}
	if (PODMINKA_OKRAJE(c, r, map))
	{
		if (((c - 1) % map->cols) == 0)
		{ // leva hrana
			if (r == 1 || r == map->rows)
			{
				if (!isborder(map, r, c, 0) || !isborder(map, r, c, 2))
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else if (map->cols == 1)
			{
				if (!isborder(map, r, c, 0) || !isborder(map, r, c, 1))
				{
					return true;
				}
			}
			else if (!isborder(map, r, c, 0))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if ((r == 1) && (c < map->cols))
		{ // horni hrana
			if ((c % 2) != 0)
			{
				if (!isborder(map, r, c, 2))
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				if (map->rows == 1)
				{
					if (!isborder(map, r, c, 0))
					{
						return true;
					}
					else
						return false;
				}
				return false;
			}
		}
		else if ((c % map->cols) == 0)
		{ // prava hrana
			if (r == 1 || r == map->rows)
			{
				if (!isborder(map, r, c, 1) || !isborder(map, r, c, 2))
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else if (!isborder(map, r, c, 1))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if ((r == map->rows) && (c != 1) && (c != map->cols))
		{ // dolni hrana
			if (((map->rows % 2) == 0) && ((map->cols % 2) == 0))
			{
				if ((((r - 1) * map->cols + (c - 1)) % 2) == 0)
				{
					if (!isborder(map, r, c, 2))
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
			else
			{
				if ((((r - 1) * map->cols + (c - 1)) % 2) != 0)
				{
					if (!isborder(map, r, c, 2))
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
		}
	}
	else
	{
		return false;
	}
	return false;
}

int posun(Map *map, int *r, int *c, int hranice, int *smer)
{

	// tato funkce dela posun na dalsi policko
	// Vyuziva k tomu hranici, pres kterou se ma posunout a upravuje smer
	// ve kterem vesla do nasledujiciho policka.
	// Funkce vraci 1, pokud probehl posun v poradku a 0, pokud se posunula
	// mimo rozmery bludiste.

	if (hranice == 0)
	{
		(*c)--;
		*smer = 1;
	}
	else if (hranice == 1)
	{
		(*c)++;
		*smer = 0;
	}
	else if (hranice == 2)
	{
		if ((map->cols % 2) != 0)
		{ // pocet sloupcu lichy
			if (((((*r) - 1) * map->cols + (*c) - 1) % 2) != 0)
			{ // index pozice lichy
				(*r)++;
				*smer = 3;
			}
			else
			{ // index pozice sudy
				(*r)--;
				*smer = 2;
			}
		}
		else if ((map->cols % 2) == 0)
		{ // pocet sloupcu sudy
			if (((*r) % 2) != 0)
			{ // radek lichy
				if (((((*r) - 1) * map->cols + (*c) - 1) % 2) != 0)
				{ // index pozice lichy
					(*r)++;
					*smer = 3;
				}
				else
				{ // index pozice sudy
					(*r)--;
					*smer = 2;
				}
			}
			else
			{ // pocet sloupcu lichy
				if (((((*r) - 1) * map->cols + (*c) - 1) % 2) != 0)
				{ // index pozice lichy
					(*r)--;
					*smer = 2;
				}
				else
				{ // index pozice sudy
					(*r)++;
					*smer = 3;
				}
			}
		}
	}
	if (((*c) > map->cols) || ((*c) < 1) || ((*r) > map->rows) || ((*r) < 1))
	{
		return 0; // posun mimo rozmery bludiste
	}
	return 1;
}

void pocitadlo_hranice(Map *map, int r, int c, int *nova_hranice, int smer, int puv_hr, int leftright)
{
	// smer: doprava=0, doleva=1, nahoru=2, dolu=3

	// tato funkce vraci hranici, o ktere budeme zjistovat,
	// zda na ni je hranice, cyklus v (r/l)pathu tuto hranici
	// pouzije jako pocatecni hodnotu

	// Vypocita nasledujici hranici na zaklade smeru, ze ktereho jsme prisli,
	// a aktualni polohy, na ktere se nachazime (index muze byt sudy/lichy; radek,
	// sloupec taky; podle toho se lisi, zda ma policko horni, nebo dolni hranici).

	if (leftright == 1)
	{ // pravidlo prave ruky
		if ((map->cols % 2) != 0)
		{
			if (smer == 0)
			{
				if ((((r - 1) * map->cols + c - 1) % 2) == 0)
				{
					int d = 1;
					// Cyklus while se opakuje, dokud nenalezne prazdnou hranici bez zdi a tu
					// pak vrati. Nasledne bude spustena funkce posun, ktera presune pozici skrz
					// vracenou hranici. Tento princip je stejny pro vsechny moznosti smeru a
					// pozic, lisi se pouze ve zpusobu vypoctu hranice pomoci d.
					while (true)
					{
						d = (d % 3); // hranice v poradi 1, 2, 0
						if (isborder(map, r, c, d))
						{
							d++;
						}
						else
						{
							*nova_hranice = d;
							return;
						}
					}
				}
				else
				{
					int d = 2; // hranice v poradi 2, 1, 0
					while (true)
					{
						if (isborder(map, r, c, d))
						{
							d--;
						}
						else
						{
							*nova_hranice = d;
							return;
						}
					}
				}
			}
			else if (smer == 1)
			{
				if ((((r - 1) * map->cols + c - 1) % 2) == 0)
				{
					int d = 2; // hranice v poradi 2, 0, 1
					while (true)
					{
						d = (d % 3);
						if (isborder(map, r, c, d))
						{
							d++;
						}
						else
						{
							*nova_hranice = d;
							return;
						}
					}
				}
				else
				{
					if (((*nova_hranice) != puv_hr) && !isborder(map, r, c, puv_hr))
					{
						return;
					}
					int d = 3;
					while (true)
					{
						if (isborder(map, r, c, (d % 3)))
						{
							d--;
						}
						else
						{
							*nova_hranice = (d % 3);
							return;
						}
					}
				}
			}
			else if (smer == 2)
			{
				int d = 4;
				while (true)
				{
					if (isborder(map, r, c, (d % 3)))
					{
						d--;
					}
					else
					{
						*nova_hranice = (d % 3);
						return;
					}
				}
			}
			else
			{
				int d = 0;
				while (true)
				{
					d = (d % 3);
					if (isborder(map, r, c, d))
					{
						d++;
					}
					else
					{
						*nova_hranice = d;
						return;
					}
				}
			}
		}
		else
		{
			if (smer == 0)
			{
				if (((r % 2) != 0 && ((((r - 1) * map->cols + c - 1) % 2) != 0)) || ((r % 2) == 0 && ((((r - 1) * map->cols + c - 1) % 2) == 0)))
				{
					int d = 2;
					while (true)
					{
						if (isborder(map, r, c, d))
						{
							d--;
						}
						else
						{
							*nova_hranice = d;
							return;
						}
					}
				}
				else
				{
					int d = 1;
					while (true)
					{
						d = (d % 3);
						if (isborder(map, r, c, d))
						{
							d++;
						}
						else
						{
							*nova_hranice = d;
							return;
						}
					}
				}
			}
			else if (smer == 1)
			{
				if (((r % 2) != 0 && ((((r - 1) * map->cols + c - 1) % 2) != 0)) || ((r % 2) == 0 && ((((r - 1) * map->cols + c - 1) % 2) == 0)))
				{
					int d = 3;
					while (true)
					{
						if (isborder(map, r, c, (d % 3)))
						{
							d--;
						}
						else
						{
							*nova_hranice = (d % 3);
							return;
						}
					}
				}
				else
				{
					int d = 2;
					while (true)
					{
						d = (d % 3);
						if (isborder(map, r, c, d))
						{
							d++;
						}
						else
						{
							*nova_hranice = d;
							return;
						}
					}
				}
			}
			else if (smer == 2)
			{
				if (((r % 2) != 0 && ((((r - 1) * map->cols + c - 1) % 2) != 0)) || ((r % 2) == 0 && ((((r - 1) * map->cols + c - 1) % 2) == 0)))
				{
					int d = 4; // hranice v poradi 1, 0, 2
					while (true)
					{
						if (isborder(map, r, c, (d % 3)))
						{
							d--;
						}
						else
						{
							*nova_hranice = (d % 3);
							return;
						}
					}
				}
			}
			else
			{
				if (((r % 2) != 0 && ((((r - 1) * map->cols + c - 1) % 2) == 0)) || ((r % 2) == 0 && ((((r - 1) * map->cols + c - 1) % 2) != 0)))
				{
					int d = 0;
					while (true)
					{
						d = (d % 3);
						if (isborder(map, r, c, d))
						{
							d++;
						}
						else
						{
							*nova_hranice = d;
							return;
						}
					}
				}
			}
		}
	}
	else
	{ // pravidlo leve ruky
		if ((map->cols % 2) != 0)
		{
			if (smer == 0)
			{
				if ((((r - 1) * map->cols + c - 1) % 2) == 0)
				{
					int d = 2;
					while (true)
					{
						if (isborder(map, r, c, d))
						{
							d--;
						}
						else
						{
							*nova_hranice = d;
							return;
						}
					}
				}
				else
				{
					int d = 1;
					while (true)
					{
						d = (d % 3);
						if (isborder(map, r, c, d))
						{
							d++;
						}
						else
						{
							*nova_hranice = d;
							return;
						}
					}
				}
			}
			else if (smer == 1)
			{
				if ((((r - 1) * map->cols + c - 1) % 2) == 0)
				{
					int d = 3;
					while (true)
					{
						if (isborder(map, r, c, (d % 3)))
						{
							d--;
						}
						else
						{
							*nova_hranice = (d % 3);
							return;
						}
					}
				}
				else
				{
					if (((*nova_hranice) != puv_hr) && !isborder(map, r, c, puv_hr))
					{
						return;
					}
					int d = 2;
					while (true)
					{
						if (isborder(map, r, c, (d % 3)))
						{
							d++;
						}
						else
						{
							*nova_hranice = (d % 3);
							return;
						}
					}
				}
			}
			else if (smer == 2)
			{
				int d = 0;
				while (true)
				{
					if (isborder(map, r, c, d))
					{
						d++;
					}
					else
					{
						*nova_hranice = (d % 3);
						return;
					}
				}
			}
			else
			{
				int d = 4;
				while (true)
				{
					if (isborder(map, r, c, (d % 3)))
					{
						d--;
					}
					else
					{
						*nova_hranice = (d % 3);
						return;
					}
				}
			}
		}
		else
		{
			if (smer == 0)
			{
				if (((r % 2) != 0 && ((((r - 1) * map->cols + c - 1) % 2) != 0)) || ((r % 2) == 0 && ((((r - 1) * map->cols + c - 1) % 2) == 0)))
				{
					int d = 1;
					while (true)
					{
						if (isborder(map, r, c, (d % 3)))
						{
							d++;
						}
						else
						{
							*nova_hranice = (d % 3);
							return;
						}
					}
				}
				else
				{
					int d = 2;
					while (true)
					{
						if (isborder(map, r, c, d))
						{
							d--;
						}
						else
						{
							*nova_hranice = d;
							return;
						}
					}
				}
			}
			else if (smer == 1)
			{
				if (((r % 2) != 0 && ((((r - 1) * map->cols + c - 1) % 2) != 0)) || ((r % 2) == 0 && ((((r - 1) * map->cols + c - 1) % 2) == 0)))
				{
					int d = 2;
					while (true)
					{
						if (isborder(map, r, c, (d % 3)))
						{
							d++;
						}
						else
						{
							*nova_hranice = (d % 3);
							return;
						}
					}
				}
				else
				{
					int d = 3;
					while (true)
					{
						if (isborder(map, r, c, (d % 3)))
						{
							d--;
						}
						else
						{
							*nova_hranice = (d % 3);
							return;
						}
					}
				}
			}
			else if (smer == 2)
			{
				if (((r % 2) != 0 && ((((r - 1) * map->cols + c - 1) % 2) != 0)) || ((r % 2) == 0 && ((((r - 1) * map->cols + c - 1) % 2) == 0)))
				{
					int d = 0;
					while (true)
					{
						if (isborder(map, r, c, d))
						{
							d++;
						}
						else
						{
							*nova_hranice = (d % 3);
							return;
						}
					}
				}
			}
			else
			{
				if (((r % 2) != 0 && ((((r - 1) * map->cols + c - 1) % 2) == 0)) || ((r % 2) == 0 && ((((r - 1) * map->cols + c - 1) % 2) != 0)))
				{
					int d = 4;
					while (true)
					{
						if (isborder(map, r, c, (d % 3)))
						{
							d--;
						}
						else
						{
							*nova_hranice = (d % 3);
							return;
						}
					}
				}
			}
		}
	}
}

int ukonceni_cyklu(Map *map, int r, int c, int d, int smer, int leftright)
{
	// Cyklus skonci tehdy, kdyz jsme na kraji bludiste a aktualni hranice
	// je shodna s okrajovou hranici a zaroven na teto hranici nesmi byt zed.
	// Funkce vraci 1 v pripade, ze ma cyklus skoncit.
	if ((PODMINKA_OKRAJE(c, r, map)))
	{
		int e; // e je okrajova hranice, d je aktualni hranice
		if (r == 1)
		{
			e = 2;
		}
		else if (r == map->rows)
		{
			if (((c - 1) % map->cols) == 0)
			{
				e = 0;
			}
			else if ((c % map->cols) == 0)
			{
				e = 1;
			}
			else
				e = 2;
		}
		else if (c == map->cols)
		{
			e = 1;
		}
		else
		{
			e = 0;
		}
		pocitadlo_hranice(map, r, c, &d, smer, d, leftright);
		if (e != d)
		{
			return 0;
		}
		if (!isborder(map, r, c, d))
		{
			return 1;
		}
	}
	return 0;
}

void rpath(Map *map, int r, int c)
{
	// algoritmus:
	//			1) Kontrola, zda na danem miste muzeme vstoupit do bludiste
	//			   pomoci funkce kontrola_kraje().
	//			2) Zjisteni z jakeho smeru jsme prisli do bludiste a nalezeni
	//			   vstupni hranice pomoci start_border().
	//			3) Nalezeni prvni kontrolovane hranice pomoci
	//			   pocitadla_hranice().
	//			4) Cyklus pruchodu, vzdy nejprve spocita dalsi hranici a overi,
	//			   jestli nejsme u vychodu. Dale bud posune pozici na nasledujici
	//			   policko, anebo nalezne hranici, pres kterou prejdeme na
	//			   dalsi pozici. Pruchod muze skoncit i tim, ze uz neni kam se
	//			   dale posunout.

	if (!kontrola_kraje(map, r, c))
	{
		printf("Na danem miste se neda vstoupit do bludiste!\n");
		return;
	}
	int smer;
	int d = start_border(map, r, c, 1, &smer); // leftright: 0 = left, 1 = right
	pocitadlo_hranice(map, r, c, &d, smer, d, 1);
	int i = 0;
	while (true)
	{ // cyklus pruchodu
		pocitadlo_hranice(map, r, c, &d, smer, d, 1);
		if ((i > 0) && ukonceni_cyklu(map, r, c, d, smer, 1))
		{
			printf("%d,%d\n", r, c);
			return;
		}
		if (i > 0)
			pocitadlo_hranice(map, r, c, &d, smer, d, 1);
		if (isborder(map, r, c, d))
		{
			d = ((d - 1) % 3);
			if (PODMINKA_OKRAJE(c, r, map))
			{
				printf("%d,%d\n", r, c);
				return;
			}
			else
			{
				printf("%d,%d\n", r, c);
				if ((i > 0) && ukonceni_cyklu(map, r, c, d, smer, 1))
					return;
				if (posun(map, &r, &c, d, &smer) == 0)
				{
					return;
				}
			}
		}
		else
		{
			printf("%d,%d\n", r, c);
			if ((i > 0) && ukonceni_cyklu(map, r, c, d, smer, 1))
				return;
			if (posun(map, &r, &c, d, &smer) == 0)
			{
				return;
			}
		}
		i++;
	}
}

void lpath(Map *map, int r, int c)
{
	// algoritmus je stejny jako u rpath, lisi se pouze v nalezani dalsich hranic

	if (!kontrola_kraje(map, r, c))
	{
		return;
	}
	int smer;
	int d = start_border(map, r, c, 0, &smer); // leftright: 0 = left, 1 = right
	pocitadlo_hranice(map, r, c, &d, smer, d, 0);
	int i = 0;
	while (true)
	{ // cyklus pruchodu
		if ((i > 0) && ukonceni_cyklu(map, r, c, d, smer, 0))
		{
			printf("%d,%d\n", r, c);
			return;
		}
		if (i > 0)
			pocitadlo_hranice(map, r, c, &d, smer, d, 0);
		if (isborder(map, r, c, d))
		{
			d = ((d - 1) % 3);
			if (PODMINKA_OKRAJE(c, r, map))
			{
				printf("%d,%d\n", r, c);
				return;
			}
			else
			{
				printf("%d,%d\n", r, c);
				if ((i > 0) && ukonceni_cyklu(map, r, c, d, smer, 0))
					return;
				if (posun(map, &r, &c, d, &smer) == 0)
				{
					return;
				}
			}
		}
		else
		{
			printf("%d,%d\n", r, c);
			if ((i > 0) && ukonceni_cyklu(map, r, c, d, smer, 0))
				return;
			if (posun(map, &r, &c, d, &smer) == 0)
			{
				return;
			}
		}
		i++;
	}
}

int test(Map *map, int *rozmer)
{

	// funkce pro kontrolu spravneho zadani bludiste, zda si sedi zdi
	// sousednich policek

	int i = 0, j = 1, c = 0;
	int souc[3];				// pozice 0 = l, pozice 1 = r, pozice 2 = nahore/dole
	int p1[3], p2[3], p3[3];	// 0 = zed neni, 1 = zed je
	int k1 = 0, k2 = 0, k3 = 0; // kontrolni promenne, tyto promenne pouzivam
								// ke zjisteni, jestli ma dane policko souseda
								// pokud k1 = 1, tak ma policko souseda vpravo,
								// k2 - soused vlevo, k3 - soused nahore/dole
	for (i = 0; i < 3; i++)
	{
		souc[i] = p1[i] = p2[i] = p3[i] = 0;
	}
	for (i = 0; i < (*rozmer); i++)
	{
		// vypocet hranic policka pomoci jeho hodnoty
		// algoritmus vypoctu:
		// 			Opakovane nacitam hodnotu aktualniho policka a zjistuji,
		//			jesli se od ni da odecist 4, pokud ano, tak ma dane policko
		//			zed nahore/dole, dale pro zed vpravo a nakonec pro zed vlevo.

		c = map->cells[i];
		if (c - 4 >= 0)
		{
			souc[2] = 1;
			c -= 4;
		}
		if (c - 2 >= 0)
		{
			souc[1] = 1;
			c -= 2;
		}
		if (c - 1 == 0)
		{
			souc[0] = 1;
			c -= 1;
		}
		if (((i > 0)) && ((i % map->cols) == 0))
		{
			j++;
		}

		// zde overuji existenci sousedu daneho policka
		if (i == 0)
		{ // levy horni roh
			k1 = 1;
		}
		else if ((j == 1) && ((i > 0) && (i < map->cols - 1)))
		{ // horni hrana
			if ((i % 2) != 0)
			{
				k1 = k2 = k3 = 1;
			}
			else
				k1 = k2 = 1;
		}
		else if ((i > 0) && ((i % map->cols) == 0) && (j < map->rows))
		{ // leva hrana
			k1 = k3 = 1;
		}
		else if (((j > 1) && (j < map->rows)) && ((i % map->cols) == map->cols - 1))
		{ // prava hrana
			k2 = k3 = 1;
		}
		else if (i == map->cols - 1)
		{ // pravy horni roh (p.h.r.)
			if ((map->cols % 2) == 0)
			{
				k2 = k3 = 1;
			}
			else
				k2 = 1;
		}
		else if ((j == map->rows) && ((i % map->cols) == 0))
		{ //(k)l.d.r.  :D
			if ((map->rows % 2) == 0)
			{
				k1 = 1;
			}
			else
				k1 = k3 = 1;
		}
		else if (i == ((map->rows) * (map->cols) - 1))
		{ // p.d.r.
			if ((((map->rows % 2) == 0) && ((map->cols % 2) == 0)) || (((map->rows % 2) != 0) && ((map->cols % 2) != 0)))
			{
				k2 = k3 = 1;
			}
			else
				k2 = 1;
		}
		// d.h.
		else if ((j == map->rows) && (((i % map->cols) != 0)) && (i != ((map->rows) * (map->cols) - 1)))
		{
			if ((map->rows % 2) != 0)
			{
				if ((i % 2) != 0)
				{
					k1 = k2 = 1;
				}
				else
					k1 = k2 = k3 = 1;
			}
			else if ((map->rows % 2) == 0)
			{
				if ((map->cols % 2) == 0)
				{
					if ((i % 2) != 0)
					{
						k1 = k2 = k3 = 1;
					}
					else
						k1 = k2 = 1;
				}
				else
				{
					if ((i % 2) == 0)
					{
						k1 = k2 = k3 = 1;
					}
					else
						k1 = k2 = 1;
				}
			}
		}
		else
			k1 = k2 = k3 = 1; // else plati pro vsechna policka,
							  // ktera nejsou na okraji bludiste

		if (map->rows == 1)
		{ // vynulovani neexistujicich sousedu
			k3 = 0;
		}
		if (map->cols == 1)
		{ // -||-
			k1 = k2 = 0;
		}

		if (k1 == 1)
		{
			c = map->cells[i + 1]; // policko vpravo
			if (c - 4 >= 0)
			{
				p1[2] = 1;
				c -= 4;
			}
			if (c - 2 >= 0)
			{
				p1[1] = 1;
				c -= 2;
			}
			if (c - 1 == 0)
			{
				p1[0] = 1;
				c -= 1;
			}
		}
		if (k2 == 1)
		{
			c = map->cells[i - 1]; // policko vlevo
			if (c - 4 >= 0)
			{
				p2[2] = 1;
				c -= 4;
			}
			if (c - 2 >= 0)
			{
				p2[1] = 1;
				c -= 2;
			}
			if (c - 1 == 0)
			{
				p2[0] = 1;
				c -= 1;
			}
		}

		if (k3 == 1)
		{ // policko hore/dole
			if ((map->cols % 2) == 0)
			{ // umisteni hornich a dolnich hranic
			  // se lisi, pokud je sudy/lichy pocet
			  // sloupcu
				if ((j % 2) == 0)
				{
					if ((i % 2) != 0)
					{
						c = map->cells[i - (map->cols)]; // do c nacitam hodnotu
					}									 // sousedniho policka
					else
					{
						c = map->cells[i + (map->cols)];
					}
				}
				else
				{
					if ((i % 2) != 0)
					{
						c = map->cells[i + (map->cols)];
					}
					else
					{
						c = map->cells[i - (map->cols)];
					}
				}
			}
			else if ((map->cols % 2) != 0)
			{
				if ((j % 2) == 0)
				{
					if ((i % 2) != 0)
					{
						c = map->cells[i + (map->cols)];
					}
					else
					{
						c = map->cells[i - (map->cols)];
					}
				}
				else
				{
					if ((i % 2) != 0)
					{
						c = map->cells[i + (map->cols)];
					}
					else
					{
						c = map->cells[i - (map->cols)];
					}
				}
			}
			if (c - 4 >= 0)
			{
				p3[2] = 1;
				c -= 4;
			}
			if (c - 2 >= 0)
			{
				p3[1] = 1;
				c -= 2;
			}
			if (c - 1 == 0)
			{
				p3[0] = 1;
				c -= 1;
			}
		}
		// pokud si nesouhlasi hodnotou zadana stejna zed v sousednich polickach
		// tak je bludiste zadano spatne
		if ((k1 == 1) && (k2 == 0) && (k3 == 0))
		{
			if (souc[1] != p1[0])
			{
				printf("Invalid\n");
				return 0;
			}
		}
		if ((k1 == 0) && (k2 == 1) && (k3 == 0))
		{
			if (souc[0] != p2[1])
			{
				printf("Invalid\n");
				return 0;
			}
		}
		if ((k1 == 0) && (k2 == 0) && (k3 == 1))
		{
			if (souc[2] != p3[2])
			{
				printf("Invalid\n");
				return 0;
			}
		}
		if ((k1 == 1) && (k2 == 1) && (k3 == 0))
		{
			if ((souc[1] != p1[0]) || (souc[0] != p2[1]))
			{
				printf("Invalid\n");
				return 0;
			}
		}
		if ((k1 == 1) && (k2 == 0) && (k3 == 1))
		{
			if ((souc[1] != p1[0]) || (souc[2] != p3[2]))
			{
				printf("Invalid\n");
				return 0;
			}
		}
		if ((k1 == 0) && (k2 == 1) && (k3 == 1))
		{
			if ((souc[0] != p2[1]) || (souc[2] != p3[2]))
			{
				printf("Invalid\n");
				return 0;
			}
		}
		if ((k1 == 1) && (k2 == 1) && (k3 == 1))
		{
			if ((souc[1] != p1[0]) || (souc[0] != p2[1]) || (souc[2] != p3[2]))
			{
				printf("Invalid\n");
				return 0;
			}
		}
		// nulovani poli s hodnotami zdi
		souc[0] = souc[1] = souc[2] = 0;
		p1[0] = p1[1] = p1[2] = 0;
		p2[0] = p2[1] = p2[2] = 0;
		p3[0] = p3[1] = p3[2] = 0;
		k1 = k2 = k3 = 0;
	}
	// konec cyklu
	printf("Valid\n");
	return 0;
}

int nacti(Map *map, FILE *f, int *rozmer, int *delka_bludiste, int *zakazane_znaky)
{
	// tato funkce nacte ze vstupniho souboru bludiste do struktury map

	int c = 0;
	int cislo = 0;
	int i = 0, j = 0;

	while ((i < 2))
	{ // nacteni rozmeru bludiste z prvnich dvou cisel
		c = fgetc(f);
		if (c == '\n')
			break;
		if ((c >= '0') && (c <= '9'))
		{ // nacitam pouze znaky od 0 do 9
			if (i == 0)
			{ // prvni rozmer
				while (c != ' ')
				{									// pro pripad vicecifernych rozmeru bludiste, nacitam dokud mohu nejake cifry nacitat
					cislo = cislo * 10 + (c - '0'); // predchozi_cifra*10 + aktualni_cifra
					c = fgetc(f);					// nacteni dalsiho znaku
				}
				if (c == ' ')
				{
					i++;
					map->rows = cislo; // ulozeni cisla jako rozmer bludiste
					cislo = 0;
				}
			}
			if (i == 1)
			{ // druhy rozmer
				c = fgetc(f);
				while (c != '\n')
				{
					cislo = cislo * 10 + (c - '0');
					c = fgetc(f);
				}
				if (c == '\n')
				{
					i++;
					map->cols = cislo;
				}
			}
		}
	}

	*rozmer = (map->rows) * (map->cols);		  // vypocet celkove delky bludiste
	map->cells = malloc((*rozmer) * sizeof(int)); // alokovani pameti o velikosti delky bludiste

	for (i = 0; c != -1; i++)
	{ // -1 je ascii hodnota konce souboru (EOF)
		c = fgetc(f);
		if (((c > ' ') && (c < '0')) || (c > '9'))
		{
			*zakazane_znaky = 1; // pokud se v zadani bludiste vyskytnou zakazane znaky, koncime
			return 0;
		}
		if ((c >= '0') && (c <= '9'))
		{
			map->cells[j] = c - '0'; // nacitani bludiste
			j++;					 // j meri skutecnou delku bludiste bez mezer a znaku konce radku
		}
	}
	map->cells[j] = '\0';
	if (j != (*rozmer))
	{ // porovnavam skutecnou velikost bludiste s ocekavanou
		*delka_bludiste = 0;
	}
	return 1;
}

//		M		  M 	   A		I I I	N     N
//		M  M   M  M		  A A		  I		N N   N
//		M	 M    M		 A   A		  I		N  N  N
//		M		  M		A A A A		  I		N	N N
//		M		  M    A	   A	I I I	N	  N

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("Nedostatecny pocet argumentu!\n");
		return 0;
	}
	char *parametr = argv[1]; // ukladam druh operace, kterou budu provadet
	char *nazev = argv[1];	  // pole pro ulozeni nazvu souboru s bludistem
	int r = 0, c = 0;		  // vstupni souradnice
	char *ptr;				  // zbytek stringu z fce strtoul

	//--help
	if ((strcmp(parametr, "--help") == 0) && (argc == 2))
	{
		printf("\nProgram pro vyhledani cesty z bludiste lze spustit s argumenty:\n");
		printf("--help       vypise manual pro praci s programem a ukonci program\n");
		printf("--test       zkontroluje validitu bludiste\n");
		printf("--rpath      vyhleda cestuza pomoci pravidla prave ruky\n");
		printf("--lpath      vyhleda cestu pomoci pravidla leve ruky\n");
		printf("--shortest   vyhledal by nejkratsi cestu kdyby byl naprogramovany :)\n\n");
		return 0;
	}

	//--test
	if (strcmp(parametr, "--test") == 0)
	{
		nazev = argv[2];
	}

	//--rpath --lpath
	if ((strcmp(parametr, "--rpath") == 0) || (strcmp(parametr, "--lpath") == 0))
	{
		if (argc < 5)
		{
			printf("Nedostatecny pocet argumentu!\n");
			return 0;
		}
		nazev = argv[4];
		r = strtoul(argv[2], &ptr, 10); // prevod souradnic, ktere jsou pri zadavani reprezentovany jako string, na int
		c = strtoul(argv[3], &ptr, 10);
	}

	FILE *f;
	if ((nazev == argv[1]) || ((f = fopen(nazev, "r")) == 0))
	{ // kontrola + otevreni souboru pro cteni
		printf("Chyba otevreni souboru!\n");
		return 0;
	}

	Map map;				// definice promenne map typu struktura Map
	int rozmer = 0;			// delka bludiste dana prvnimi dvema cisly v souboru s bludistem
	int delka_bludiste = 1; // skutecna delka bludiste
	int zakazane_znaky = 0;
	nacti(&map, f, &rozmer, &delka_bludiste, &zakazane_znaky);
	if (zakazane_znaky == 1)
	{
		printf("Invalid\n"); // kontrola, zda v zadani bludiste nejsou zakazane znaky
		return 0;
	}
	if (strcmp(parametr, "--test") == 0)
	{
		if (delka_bludiste == 0)
		{ // kontrola skutecne delky bludiste oproti ocekavane
			printf("Invalid\n");
			return 0;
		}
		test(&map, &rozmer);
	}
	if (strcmp(parametr, "--rpath") == 0)
	{ // spusteni rpath
		rpath(&map, r, c);
	}
	if (strcmp(parametr, "--lpath") == 0)
	{ // spusteni lpath
		lpath(&map, r, c);
	}

	free(map.cells); // vymazani alokovane pameti
	fclose(f);		 // uzavreni otevreneho souboru s bludistem
	return 0;
}
