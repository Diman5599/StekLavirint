#include <iostream>
#include "Lavirint.h"
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string>


using namespace std;

int main() {
	int izlaz = 1;
	while (izlaz) {
		Lavirint* l = new Lavirint("./lavirint.txt");
		l->iscrtajLavirint();
		l->resiLavirint();
		cout << "DEBUG\n";	
		l->iscrtajLavirint();
		delete(l);
		cout << "Unesite 0 da biste zavrsili...\n";
		cin >> izlaz;
	}
	return 0;
}