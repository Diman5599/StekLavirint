#include "Lavirint.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>

using namespace std;

PoljeLavirinta::PoljeLavirinta()
{
	this->prolaz = 0;
	this->cilj = 0;
}

PoljeLavirinta::PoljeLavirinta(int prolaz, int cilj)
{
	this->prolaz = prolaz;
	this->cilj = cilj;
}

void PoljeLavirinta::postaviProlaz(int v)
{
	this->prolaz = v%2;
}

void PoljeLavirinta::ukloniProlaz()
{
	this->prolaz = 0;
}

void PoljeLavirinta::postaviCilj()
{
	this->cilj = 1;
}

void PoljeLavirinta::prelaz()
{
	this->predjeno = 1;
}

void PoljeLavirinta::n_prelaz()
{
	this->predjeno = 0;
}

void PoljeLavirinta::postaviKrajnje()
{
	this->krajnje_resenje = 1;
}

void PoljeLavirinta::ukloniKrajnje()
{
	this->krajnje_resenje = 0;
}

int PoljeLavirinta::vProlaz()
{
	return this->prolaz;
}

int PoljeLavirinta::vCilj()
{
	return this->cilj;
}

int PoljeLavirinta::presao()
{
	return this->predjeno;
}

int PoljeLavirinta::krajnje()
{
	return this->krajnje_resenje;
}

LavirintStek::LavirintStek()
{
	this->stek = new int[100];

}

LavirintStek::~LavirintStek()
{
	delete(this->stek);
}

LavirintStek::LavirintStek(int vel)
{
	this->stek = new int[vel];
}

int LavirintStek::vrh()
{	
	return this->vrhSteka;
}

int LavirintStek::stavi(int i)
{
	if (this->vrhSteka == 99) {
		return -1;
	}
	
	this->vrhSteka++;
	this->stek[this->vrhSteka] = i;
	return 0;
}

int LavirintStek::skini()
{
	if (this->vrhSteka == -1) {
		return  -1;
	}

	this->vrhSteka--;
	int i = this->stek[this->vrhSteka + 1];
	return i;
}

int LavirintStek::naVrhu()
{
	if (this->vrhSteka == -1) {
		return -1;
	}

	return this->stek[this->vrhSteka];

}

Lavirint::Lavirint(int redovi, int kolone)
{
	this->br = redovi;
	this->bk = kolone;
	this->matricaLavirinta = new PoljeLavirinta * [this->br];
	for (int i = 0; i < redovi; i++) {
		this->matricaLavirinta[i] = new PoljeLavirinta  [this->bk];
	}
}

Lavirint::~Lavirint()
{
	for (int i = 0; i < this->br; i++) {
		delete(this->matricaLavirinta[i]);
	}
	delete(this->matricaLavirinta);
}


void Lavirint::iscrtajLavirint()
{
	char zid = '#';
	cout << ' ';

	for (int j = 0; j < this->bk; j++) {
		cout << '*';
	}
	cout << '\n';
	for (int i = 0; i < this->br; i++) {
		cout << ' '; //odvaja ispis od ivice
		for (int j = 0; j < this->bk; j++) {
			if (this->matricaLavirinta[i][j].krajnje() == 1) { 
				cout << ">"; // ako je polje L[i][j] oznaceno kao deo krajnjeg resenja pri ispisu bice prikazano znakom '>'
			}
			else if (this->matricaLavirinta[i][j].vProlaz() == 0) {
				cout << zid; // ako neko polje predstavlja 'zid' bice prikazano znakom '#'
			}
			else if (this->matricaLavirinta[i][j].presao() == 1) {
				cout << '*';
			}
			else {
				cout << ' '; // ako je polje prolaz bice prikazano razmakom
			}	
		}
		cout << '\n';
	}
	cout << '\n';
	cout << ' ';

	for (int j = 0; j < this->bk; j++) {
		cout << '*';
	}
	cout << '\n';

	cout << "Legenda: " << endl;
	cout << "-- '" << zid << "' zid lavirinta(nema prolaza)" << endl;
	cout << "-- '>' krajnja putanja resenja  " << endl;
	cout << "-- '*' pokusaj prolaska " << endl;
	cout << "-- ' ' moguca putanja (prolaz) " << endl;
}

Lavirint::Lavirint(const char* adr) {

	ifstream* inFile = new ifstream(adr); // otvara se ulazni tok iz datoteke cija je adresa prosledjena kao parametar konstruktora

	char** prihvat;
	int i = 0;
	int j = 0;
	int bk = 0, br = 0;
	string* bafer = new string();
	/*neophodno je da se prvo utvrdi koiko kolona i redova ima lavirint kako bi se instancirala matrica za prihvat potrebnih dimenzija*/
	while (getline(*inFile, *bafer)) // iscitava se datoteka do kraja i pri citanju svake linije broj redova se inkrementira (br. linija datoteke = br. redova lavirinta)
	{
		br++;
	}

	bk = (*bafer).length(); // br. kolona jednak je duzini jedne linije tekstualne datoteke
	delete(bafer);
	delete(inFile);

	/*instanciranje prihvatne matrice*/
	prihvat = new char* [br]; 

	for (i = 0; i < br; i++)
	{
		prihvat[i] = new char[bk];
	}

	i = 0;
	j = 0;


	ifstream *inFile2 = new ifstream(adr);
	string* bafer2 = new string();

	/*popunjavanje matrice iz tekstualne datoteke -> prihvat[i][j] elem. {'0','1'}*/
	while (getline(*inFile2, *bafer2))
	{
		const char* pom = (*bafer2).c_str();
		strcpy(prihvat[i], pom);
		i++;
	}
	/*broj kolona odnosno redova lavirinta mora biti jednak onom prihvatne matrice*/
	this->br = br;
	this->bk = bk;

	/*instanciranje polja .matricaLavirinta klase Lavirint istih dimenzija kao prihvat[][]*/
	this->matricaLavirinta = new PoljeLavirinta *[this->br];
	for ( i = 0; i < br; i++) {
		this->matricaLavirinta[i] = new PoljeLavirinta[this->bk];
	}

	/*na osnovu vrednosti polja prihvatne matrice postavljaju se elementi matrice lavirinta kao 'prolaz' odnosno 'zid'*/
	for (i = 0; i < this->br; i++)
	{
		for (j=0;j< this->bk; j++)
		{
			if (prihvat[i][j] == '1')
				this->matricaLavirinta[i][j].postaviProlaz(1);
			else
				this->matricaLavirinta[i][j].postaviProlaz(0);
		}
	}


	/*Postavljanje izlaza (cilja) iz lavirinta u poslednjoj koloni (jedino polje koje je prolaz u poslednjoj koloni mora biti izlaz)*/
	j = this->bk - 1;
	for (i = 0; i < this->br; i++)
	{
		if (this->matricaLavirinta[i][j].vProlaz() == 1)
		{
			this->matricaLavirinta[i][j].postaviCilj();
			break;
		}
	}
	delete(inFile2);
	delete(bafer2);	

	delete[] prihvat;
}

void Lavirint::resiLavirint() {

	LavirintStek* lSteki = new LavirintStek(this->bk * this->br / 2);
	LavirintStek* lStekj = new LavirintStek(this->bk * this->br / 2);

	int i, j;
	i = 0;
	j = 0;

	while (this->matricaLavirinta[i][j].vProlaz() != 1) //pretrazuje se prva kolona da bi se nasao ulaz(prvi prolaz u prvoj koloni)
	{
		i++;
	}
	this->matricaLavirinta[i][j].prelaz(); //prelazi se ulaz i pozicija ulaza se stavlja na stek
	this->matricaLavirinta[i][j].postaviKrajnje();
	lSteki->stavi(i);
	lStekj->stavi(j);
	j++; // sledece polje koje je prolaz mora biti desno od ulaza, tj. u susednoj koloni a istom redu; pozicija se ponovo stavlja na stek
	lSteki->stavi(i);
	lStekj->stavi(j);
	this->matricaLavirinta[i][j].prelaz();
	this->matricaLavirinta[i][j].postaviKrajnje();
	/*U petji se proverava da li se ponovo doslo do ulaza u lavirint(prva kolona j=0), i tada lavirint nema izlaza
	* zbog toga je neophodno da se pre ulaska u petlju "odmaknemo" od prve kolone jer u suprotnom bi se odmah izaslo iz petlje
	*/
	while (this->matricaLavirinta[i][j].vCilj() != 1  && j != 0 )
	{
		/*U petlji se proverava za svaku poziciju da li je moguce otici redom: gore, desno, dole i levo
		* Moguce je poci u nekom smeru u koliko je susedno polje u tom smeru:
		* 1)prolaz
		* 2)nije vec predjeno
		* Pri svakom pomeranju prethodna lokacija se stavlja na stek i u slucaju da se naidjen a corsokak uzima se sa stek prethodna lokacija i
		* ponovo se proverava da li je moguce poci u nekom smeru
		* Uslov za izlaz iz petlje je pronalazak izlaza ili vracanje na pocetak(ne postoji izlaz)
		* Pri prelasku preko svakog polja postavlja se ono kao deo krajnjeg resenja, a pre skidanja sa steka prethodne pozicije, ta oznaka se skida
		* sa datog polja (jer ukoliko treba da dodje do skidanja sa steka prethodne pozicije to znaci da trenutna pozicija(polje) nije deo konacne putanje
		*/
		if (this->matricaLavirinta[i - 1][j].vProlaz() == 1 && this->matricaLavirinta[i - 1][j].presao() != 1)
		{
			lSteki->stavi(i);
			lStekj->stavi(j);
			i--;
			this->matricaLavirinta[i][j].prelaz();
			this->matricaLavirinta[i][j].postaviKrajnje();
		}
		else if (this->matricaLavirinta[i][j + 1].vProlaz() == 1 && this->matricaLavirinta[i][j+1].presao() != 1)
		{
			lSteki->stavi(i);
			lStekj->stavi(j);
			j++;
			this->matricaLavirinta[i][j].prelaz();
			this->matricaLavirinta[i][j].postaviKrajnje();
		}
		else if (this->matricaLavirinta[i + 1][j].vProlaz() == 1 && this->matricaLavirinta[i + 1][j].presao() != 1)
		{
			lSteki->stavi(i);
			lStekj->stavi(j);
			i++;
			this->matricaLavirinta[i][j].prelaz();
			this->matricaLavirinta[i][j].postaviKrajnje();
		}
		else if (this->matricaLavirinta[i][j - 1].vProlaz() == 1 && this->matricaLavirinta[i][j - 1].presao() != 1)
		{
			lSteki->stavi(i);
			lStekj->stavi(j);
			j--;
			this->matricaLavirinta[i][j].prelaz();
			this->matricaLavirinta[i][j].postaviKrajnje();
		}
		else
		{
			this->matricaLavirinta[i][j].ukloniKrajnje();
			i = lSteki->skini();
			j = lStekj->skini();
		}
	}

	if (j == 0) {
		cout << "Lavirint nema izlaz\n";
	}

	delete(lSteki);
	delete(lStekj);
}