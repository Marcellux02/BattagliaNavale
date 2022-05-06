//Nel gioco sono presenti 5 barche totali: 1 barca da 5, 1 barca da 4, 1 da tre e 1 da due.

#include <iostream>
#include<cstdlib>
#include<ctime>

using namespace std;
int const campo = 10;
char fieldNormal[campo][campo];
bool fieldCheck[campo][campo];
int nBarche = 4;

void setUpGame(int lenght){
	//imposta i valori predefiniti a tutte le caselle del gioco
	for(int i=0;i<lenght;i++){
        for(int j=0;j<lenght;j++){
            fieldNormal[i][j] = '-';
            fieldCheck[i][j] = false;
        }
    }
    nBarche = 4;
}

void drawField(int lenght){
	//disegna il campo di gioco
	cout<<"    0   1   2   3   4   5   6   7   8   9"<<endl;
	for(int i=0;i<lenght;i++){
		cout<<endl;
		cout<<i<<"   ";
        for(int j=0;j<lenght;j++){
            cout<<fieldNormal[i][j]<<"   ";
        }
        cout<<endl;
    }
}

bool askGame(){
	char risp[1];
	//aiuta il fatto di mettere una vettore per ricevere in input solo un singolo carattere
	//il problema persiste quando viene erroneamente inserita una stringa, il loop continua per la lunghezza della stringa
	//mentre così viene ripetuto solo per un inserimento
	cout<<"Vuoi giocare posizionando le barche in maniera casuale o manuale? (C = casuale | M = manuale): ";
	do{
		try{
		cin>>risp;
			switch(risp[0]){
				case 'c':
					return true;
				case 'C':
					return true;
				case 'm':
					return false;
				case 'M':
					return false;
				default:
					cout<<"Comando inserito NON valido, reinseriscilo: ";	
			}
		}
		catch(...){
			// i 3 punti prendono tutti i possibili errori
			cout<<"Comando inserito NON valido, reinseriscilo: ";
		}
	}while(true);
	//in questa sezione il codice non viene mai eseguito ma il compilatore lo richiede lo stesso
	return false;
}

bool *checkSpaceGap(int lenghtField, int r, int c, int boat){
	//vengono salvati rispettivamente quanto spazio c'è tra: su, destra, giù, sinistra
	int spazio[] = {(r-0+1), (lenghtField - c),(lenghtField - r),(c-0+1)};
	bool temp[4];
	cout<<endl;
	for(int i=0; i<4; i++){
		if(spazio[i]<boat) temp[i] = false; //lo spazio non è sufficiente per la barca
		else temp[i] = true; //lo spazio è sufficiente per la barca
	}
	return temp; 
}

bool checkOtherBoat(int r, int c, int boat, int rotation){
	switch(rotation){
		//faccio il controllo con la rotazione e nei casi qui sotto, blocco alcune righe o colonne della matrice per controllarle
		case 0: //su
		cout<<"Caso su"<<endl;
			for(int i=0; i<boat; i++){
				if(fieldCheck[r-i][c] == true) return false; //una delle caselle è già occupata
			}	
			//la barca può essere scritta e viene fatto
			for(int j=0; j<boat; j++){
				fieldCheck[r-j][c] = true;
				fieldNormal[r-j][c] = 'X';
			}
			break;
		case 1: //destra
		cout<<"Caso destra"<<endl;
			for(int i=0; i<boat; i++){
				if(fieldCheck[r][c+i] == true) return false; //una delle caselle è già occupata
			}	
			//la barca può essere scritta e viene fatto
			for(int j=0; j<boat; j++){
				fieldCheck[r][c+j] = true;
				fieldNormal[r][c+j] = 'X';
			}
			break;
		case 2: //giu
		cout<<"Caso giu"<<endl;
			for(int i=0; i<boat; i++){
				if(fieldCheck[r+i][c] == true) return false; //una delle caselle è già occupata
			}	
			//la barca può essere scritta e viene fatto
			for(int j=0; j<boat; j++){
				fieldCheck[r+j][c] = true;
				fieldNormal[r+j][c] = 'X';
			}
			break;
		case 3: //sinistra
		cout<<"Caso sinistra"<<endl;
			for(int i=0; i<boat; i++){
				if(fieldCheck[r][c-i] == true) return false; //una delle caselle è già occupata
			}	
			//la barca può essere scritta e viene fatto
			for(int j=0; j<boat; j++){
				fieldCheck[r][c-j] = true;
				fieldNormal[r][c-j] = 'X';
			}
			break;
	}
	return true; //se non sono state trovate complicanze, la funzione ritorna la possibilità di scrivere la barca
}

void automaticInsert(){
	srand(time(NULL));
	int n = 0;
	while(n < nBarche){
		//Sceglie una riga e colonna casuale tra le n (campo) 
		int r = rand()%campo;
		int c = rand()%campo;
		if(fieldCheck[r][c] == true) continue; //caso in cui prendiamo una casella già occupata in partenza, inutile fare calcoli
		bool *space = checkSpaceGap(campo, r, c, nBarche+1);
		int check = 0;
		cout<<"Riga: "<<r<<" Colonna: "<<c<<" Spazi: "<<space[0]<<" "<<space[1]<<" "<<space[2]<<" "<<space[3]<<endl;
		for(int i=0; i<4; i++){
			int rotation = rand()%4;
			cout<<"Rotazione numero: "<<rotation<<" "<<space[rotation]<<" ";
			if(space[rotation] == true) {
				cout<<"Rotazione corretta: "<<rotation<<" Barca: "<<nBarche+1<<endl;
				if (checkOtherBoat(r, c, nBarche+1, rotation)){
					cout<<"Problema"<<endl;
					continue;
					//la funzione check ritorna false che negato fa true quindi posso evitare il == 
					//la barca non può essere inserita e quindi si ripete il ciclo senza aggiornare la grandezza della barc
				} 
			}
			else{
				cout<<"Non c'e' spazio"<<endl;
				check++;
				continue;
				//caso in cui l'orientamento della barca non sia favorevole
			} 
		}
		if(check==4) continue;
		cout<<"Barca "<<nBarche+1<<" inserita"<<endl;
		nBarche--;
	}
}

void manualInsert(){
	int r,c,boat,rotazione;
	while(true){
		while(true){
			try{
				cout<<"Inserisci la RIGA: "; 
				cin>>r;
				if(r<0 || r>campo){
					cout<<"Inserimento riga errato, reinserire"<<endl;
					continue;
				}
				cout<<"Inserisci la COLONNA: "; 
				cin>>c;
				if(c<0 || c>campo){
					cout<<"Inserimento colonna errato, reinserire"<<endl;
					continue;
				}
				cout<<"Dimensione della BARCA: ";
				cin>>boat;
				if(boat<0 || boat >5){
					cout<<"Inserimento lunghezza barca errato, reinserire"<<endl;
					continue;
				}
				break;
			}
			catch(...){
				cout<<"Errore nell'inserimento della riga o colonna o barca"<<endl;
				continue;
			}
		}
		while(true){
			try{
				cout<<"Inserisci orientamento della barca (0 su, 1 destra, 2 giu', 3 sinistra): ";
				cin>>rotazione;
				if(rotazione<0 || rotazione>3){
					cout<<"Errore logico, reinserire"<<endl;
					continue;
				}
				bool *space = checkSpaceGap(campo, r, c, boat);
				if(space[rotazione]){
					break;
				}
				else{
					cout<<"Orientamento non consentito, va oltre ai bordi"<<endl;
					continue;
				}
			}
			catch(...){
				cout<<"Errore nell'inserimento della barca o rotazione"<<endl;
			}
		}
		if(checkOtherBoat(r, c, boat, rotazione)){
			drawField(campo);
			break;
		}
		else{
			cout<<"La barca inserita va a colpire altre barche o il bordo, reinserisci"<<endl;
			continue;
		}
	}
}

int main(){
	setUpGame(campo);
	drawField(campo);
	if(askGame()){
		//Inzia il gioco con barche messe in modo casuale
		bool a = checkOtherBoat(5, 5, 4, 3);
		drawField(campo);
	}
	else{
		//Inizia il gioco con barche messe in modo deciso dall'utente
		while(true){
			manualInsert();
		}
	}
	
	
	system("pause");
		
}






