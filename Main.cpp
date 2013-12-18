#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;

#include "red_polje.h"
//#include "red_pokazivac.h"

telement* polje;
int generate(){
	bool agen;
	int br;
	
	cout << "Koliko petorki zelite generirati: ";
	cin >> br;
	cout << "----------------------" << endl;
	polje = new telement[br];
	
	for(int i=0; i<br; i++){
		polje[i].ai = rand()%250+50;
		polje[i].bi = rand()%250+50;
		polje[i].ci = rand()%5+1;
		polje[i].di = rand()%3+1;
		do{
			polje[i].ei = rand()%5+1;
			agen = false;
			
			if(polje[i].ei == 1)
				if(polje[i].ci == 1 || polje[i].ci == 3) agen = true;
			else if(polje[i].ei == 2 || polje[i].ei == 3 || polje[i].ei == 5)
				if(polje[i].ci == 1 || polje[i].ci == 3 || polje[i].ci == 4) agen = true;
			else if(polje[i].ei == 4)
				if(polje[i].ci == 4) agen = true; 
		}while(agen);
	}
	for(int i=0; i<br; i++)
		cout << i+1 << ". petorka: " << polje[i].ai << ", " << polje[i].bi << ", " << polje[i].ci << ", "
		<< polje[i].di << ", " << polje[i].ei << "." << endl;
	cout << endl;
	return br;
}

void sortQ(que *R){
    telement elem;
    que *pomR1=InitQ(pomR1),*pomR2=InitQ(pomR2);

    for(int i=1;i<=5;i++){
        while(!IsEmptyQ(R)){
            elem = FrontQ(R);
            DeQueueQ(R);
            if(elem.ci==i) EnQueueQ(elem,pomR1);
            else EnQueueQ(elem,pomR2);
        }
        while(!IsEmptyQ(pomR2)){
            elem = FrontQ(pomR2);
            DeQueueQ(pomR2);
            EnQueueQ(elem,R);
    	}
    }
    //vracanje na originalni red
    while(!IsEmptyQ(pomR1)){
        elem = FrontQ(pomR1);
        DeQueueQ(pomR1);
        EnQueueQ(elem,R);
    }
}

string ispis_usluge(telement elem){
	string pri,usl,ord;
	//Prioriteti pacijenata
	if(elem.ci == 1) pri = "Prioritet pacijenta: Hitan slucaj";
	else if(elem.ci == 2) pri = "Prioritet pacijenta: Invalid";
	else if(elem.ci == 3) pri = "Prioritet pacijenta: Trudnica";
	else if(elem.ci == 4) pri = "Prioritet pacijenta: Dijete mlade od 6 godina";
	else if(elem.ci == 5) pri = "Prioritet pacijenta: Ostali pacijenti";
	//Vrsta usluge
	if(elem.di == 1) usl = "Vrsta usluge: Pregled";
	else if(elem.di == 2) usl = "Vrsta usluge: Previjanje";
	else if(elem.di == 3) usl = "Vrsta usluge: Recepti";
	else if(elem.di == 4) usl = "Vrsta usluge: Uputnice";
	//Vrsta ordinacije poliklinike
	if(elem.ei == 1) ord = "Vrsta ordinacije: Obiteljska medicina";
	else if(elem.ei == 2) ord = "Vrsta ordinacije: Oftalmologija";
	else if(elem.ei == 3) ord = "Vrsta ordinacije: Dermatovenerologija";
	else if(elem.ei == 4) ord = "Vrsta ordinacije: Ginekologija";
	else if(elem.ei == 5) ord = "Vrsta ordinacije: Urologija";
	
	return pri+"\n"+usl+"\n"+ord;
}

//Varijabla za pohranjivanje unosa o trenutnoj godini
int trenG=0, brP=0;
void addP(que* R, int br){
	telement elem;
	int godRaz;
	que* pomR = InitQ(pomR);
	cout << "Unesite trenutnu godinu: ";
	cin >> trenG;
	cout << endl;
	
	for(int i=0; i<br; i++)
		for(int j=0; j<3; j++){
			do{
				
				cout << "Unesite spol pacijenta(M/Z): ";
				cin >> elem.spol;
				if(tolower(elem.spol) != 'm' && tolower(elem.spol) != 'z') cout << "Neispravan unos! Unesite Z,z,M ili m.\n";
			}while(tolower(elem.spol) != 'm' && tolower(elem.spol) != 'z');
			if(tolower(elem.spol) == 'm'){
				cout << "Unesite ime pacijenta: ";
				cin >> elem.ime;
				cout << "Unesite prezime pacijenta: ";
				cin >> elem.prezime;
			}
			if(tolower(elem.spol) == 'z'){
				cout << "Unesite ime pacijentice: ";
				cin >> elem.ime;
				cout << "Unesite prezime pacijentice: ";
				cin >> elem.prezime;
			}
			cout << "Unesite datum rodenja pacijenta: ";
			cin >> elem.dan, cin >> elem.mj, cin >> elem.god;
			cout << "------------" << endl;
			godRaz = trenG-elem.god;
			elem.ai = polje[i].ai;
			elem.bi = polje[i].bi;
			if((tolower(elem.spol)=='m' && polje[i].ci==3) || (godRaz>6 && polje[i].ci==4)) polje[i].ci = 5;
			if(tolower(elem.spol)=='z' && polje[i].ei == 5) polje[i].ci = 3;
			if(tolower(elem.spol)=='z' && godRaz < 16 && polje[i].ei == 4) polje[i].ci = 5;
			else if(tolower(elem.spol)=='z' && godRaz > 16 && polje[i].ei == 4) polje[i].ci = 3;
			elem.ci = polje[i].ci;
			elem.di = polje[i].di;
			if(tolower(elem.spol)=='m' && polje[i].ei == 4) polje[i].ei = 5;
			if(tolower(elem.spol)=='z' && polje[i].ei == 5) polje[i].ei = 4;
			elem.ei = polje[i].ei;
			cout << ispis_usluge(elem) << endl;
			cout << "--------------------------" << endl << endl;
			EnQueueQ(elem, R);
			brP++;
		}
		sortQ(R);
		
		cout << "Pacijentice starije od 25 godina koje idu na Oftalmologiju:\n\n";
		while(!IsEmptyQ(R)){
			elem = FrontQ(R);
			DeQueueQ(R);
			EnQueueQ(elem, pomR);
		}
		bool check;
		while(!IsEmptyQ(pomR)){
			elem = FrontQ(pomR);
			DeQueueQ(pomR);
			
			if(godRaz > 25 && elem.spol == 'z' && elem.ei == 2){
				cout << "Ime: " << elem.ime << endl;
				cout << "Prezime: " << elem.prezime << endl;
				cout << "Datum rodenja: " << elem.dan << "." << elem.mj << "." << elem.god << "." << endl;
				cout << "Godine: " << godRaz << endl;
				cout << "--------------" << endl << endl;
				check = true;
			}
			EnQueueQ(elem, R);
		}
		if(!check) cout << "Ne postoje takve pacijentice." << endl << endl;
}

void cekaonica(que* R){
	telement elem;
	que* pomR = InitQ(pomR);
	
	while(!IsEmptyQ(R)){
		elem = FrontQ(R);
		cout << "Ime: " << elem.ime << endl;
		cout << "Prezime: " << elem.prezime << endl;
		cout << "Datum rodenja: " << elem.dan << "." << elem.mj << "." << elem.god << "." << endl;
		cout << ispis_usluge(elem) << endl;
		DeQueueQ(R);
		EnQueueQ(elem, pomR);
		cout << "--------------" << endl << endl;
	}
	while(!IsEmptyQ(pomR)){
		elem = FrontQ(pomR);
		DeQueueQ(pomR);
		EnQueueQ(elem, R);
	}
}

void delinvP(que* R){
	telement elem;
	int godRaz;
	bool check;
	que* pomR = InitQ(pomR);
	
	while(!IsEmptyQ(R)){
		elem = FrontQ(R);
		EnQueueQ(elem, pomR);
		DeQueueQ(R);
	}
	cout << "Invalidi stariji od 50 godina koji cekaju previjanje kod lijecnika obiteljske medicine:\n";
	while(!IsEmptyQ(pomR)){
		elem = FrontQ(pomR);
		DeQueueQ(pomR);
		godRaz = trenG - elem.god;
		
		if(godRaz > 50 && elem.ci == 2 && elem.di == 2 && elem.ei == 1){
			cout << "Ime: " << elem.ime << endl;
			cout << "Prezime: " << elem.prezime << endl;
			cout << "Datum rodenja: " << elem.dan << "." << elem.mj << "." << elem.god << "." << endl;
			cout << "Godine: " << godRaz << endl;
			cout << "--------------" << endl << endl;
			check = true;
		}
		else EnQueueQ(elem, R);
	}
	if(!check) cout << "Ne postoje takvi pacijenti u redu." << endl << endl;
	cout << "------- Cekaonica ---------" << endl;
	cekaonica(R);
}

void brzi_red(que *R, que* quickQ){
	telement elem;
    
    if(IsEmptyQ(R)) return;
    else{
        elem=FrontQ(R);
        DeQueueQ(R);
        brzi_red(R, quickQ);
    }
    static int percent = (0.3*brP)+0.5;
    if(!percent)
		EnQueueQ(elem,R);
    else 
		if(elem.di == 3 || elem.di == 4){
			EnQueueQ(elem,quickQ);
			percent--;
			brP--;
		}
}
//Funkcija koja vraca pacijente u glavni red, u originalnom poretku.  
void return_orderQ(que *R){
    telement elem;
    if(IsEmptyQ(R)) return;
    else{
        elem=FrontQ(R);
        DeQueueQ(R);
        return_orderQ(R);
    }
    EnQueueQ(elem,R);
}

int main(){
	que* R = InitQ(R);
	que* quickQ = InitQ(quickQ);
	short choice, brN;
	bool alocate = false;
	srand(time(NULL));
	rand();
	
	do{
		cout << "I z b o r n i k" << endl;
		cout << "-------------------" << endl;
		cout << "1. Generiranje petorki vezanih uz pacijente." << endl;
		cout << "2. Unos podataka o pacijentima." << endl;
		cout << "3. Brisanje invalida starijih od 50 godina." << endl;
		cout << "4. Red brzih usluga." << endl;
		cout << "0. Izlaz iz programa." << endl;
		cout << "-------------------" << endl;
		do{
			cout << "Koji je Vas odabir: ";
			cin >> choice;
			cin.ignore();
			if(choice < 0 || choice > 4) cout << "Vas izbor nije podrzan, ponovite unos!" << endl << endl;
		}while(choice < 0 || choice > 4);
		cout << endl;
			
		switch(choice){
			case 1:
				brN = generate();
				if(brN) alocate = true; 
				break;
			case 2: 
				if(alocate) addP(R, brN);
				else cout << "Red nije alociran!" << endl << endl;
				break;
			case 3: 
				if(alocate) delinvP(R);
				else cout << "Red nije alcoiran!" << endl << endl;
				break;
			case 4: 
				if(alocate){
					brzi_red(R, quickQ);
	                return_orderQ(R);
	                cout << "Brzi red: " << endl;
	                cout << "----------" << endl;
	                cekaonica(quickQ);
	            	cout << "Originalni red: " << endl;
	            	cout << "----------------" << endl;
	                cekaonica(R);
	            }
	            else cout << "Red nije alociran!" << endl << endl;
				break;
			default: break;
		}
	}while(choice);
}
