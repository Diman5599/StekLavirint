#pragma once

/*Klasa koja predstavlja polja lavirinta od kojih je sastavjena matrica lavirinta
*Ima mogucnost postavljanja sledecih oznaka:
-da li je dato polje "prolaz"(atribut prolaz = 1) ili "zid" (atribut prolaz = 0)
-da li dato polje predstavllja cilj lavirinta (atribut cilj = 1)
-da li preko datog poja predjeno prilikom resavanja lavirinta
*/
class PoljeLavirinta {

	private:
		int prolaz=0;
		int cilj=0;
		int predjeno = 0;
		int krajnje_resenje = 0;

	public:
		PoljeLavirinta();
		PoljeLavirinta(int prolaz, int cilj);

		void postaviProlaz(int v); //metoda koja postavlja prolaz ili zid na datom polju u zavisnosti od parametra v, v elem. {0,1,2,...}, prolaz = v%2;
		void ukloniProlaz();	//metoda koja postavlja polje prolaz na 0
		void postaviCilj(); //metoda koja oznacava polje kao cilj (polje.cilj=1)
		void prelaz();	//metoda koja oznacava da je polje predjeno 
		void n_prelaz(); //uklanja oznaku prelaska
		void postaviKrajnje(); // oznacava da ce se polje ispisati kao krajnje resenje
		void ukloniKrajnje(); // uklanja oznaku krajnjeg resenja

		int vProlaz(); //vraca vrednost atributa prolaz datog polja
		int vCilj(); //vraca vrednost atributa cilj datog polja
		int presao(); //vraca vrednost atributa predjeno datog polja
		int krajnje();

};

/*Stek(sekvencijalna implementacija) koji je koriscen za potrebe smestanja koordinata prethodnih pozicija pri prolasku kroz lavirint*/
class LavirintStek {

	private:
		int* stek;			//atribut koji predstavja sam niz u koji se smesta po jedan koordinata (celobrojna vrednost)
		int vrhSteka = -1;

	public:
		LavirintStek();   //konstruktor koji ne prima argument i definise stek (instancira niz celih br.) kapaciteta 100
		LavirintStek(int vel);   //konstruktor kome se prosledjuje kapacitet steka
		~LavirintStek();   //destruktor koji oslobadja i memoriju koju zauzima sam niz *stek;

		int vrh(); //metoda koja vraca vrednost indeksa elementa na vrhu steka
		int stavi(int i); //metoda za stavljanje na stek
		int skini(); //metoda za skidanje sa steka
		int naVrhu(); //metoda koja vraca element sa vrha steka bez skidanja

};


/*Klasa koja predstavlja sam lavirint
* atribut matricaLavirinta predstavlja dvodimenzionalni niz popunjen objektima(referencama) klase PoljeLavirinta
*/
class Lavirint {

	private:
		PoljeLavirinta** matricaLavirinta;
		int br; //broj redova lavirinta
		int bk; //broj kolona lavirinta

	public:
		Lavirint(int redovi, int kolone); //konstruktor koji na osnovu prosledjenog broja kolona/redova instancira lavirint kod koga su sva polja "zidovi"
		Lavirint(const char* adr); // konstruktor koji instancira lavirint na osnovu tekstualne datoteke cija mu je adresa prosledjena 
		/*Lavirint se u datoteci predstavlja matricom nula i jedinica gde je 0 zid a 1 prolaz
		 *Neophodno je da ulaz u lavirint bude na levoj, a izlaz na desnoj strani lavirinta
		*/
		~Lavirint();

		void iscrtajLavirint(); //metoda za prikaz lavirinta na konzoli
		void resiLavirint();	//metoda za prolazak kroz lavirint 
		
};


