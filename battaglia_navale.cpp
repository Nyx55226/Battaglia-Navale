#include <iostream>
#include <ctime>
#include <windows.h>
#define MAX 10
using namespace std;

// Funzione per contare quante navi restano
int naviRimanenti(char tavola[MAX][MAX]) {
    bool N1=false, N2=false, N3=false, N4=false, N5=false;
    for(int x=0; x<MAX; x++) {
        for(int y=0; y<MAX; y++) {
            switch(tavola[x][y]) {
                case 'N': N1=true; break; // nave 1 cella
                case 'O': N2=true; break; // nave 2 celle
                case 'P': N3=true; break; // nave 3 celle
                case 'Q': N4=true; break; // nave 4 celle
                case 'R': N5=true; break; // nave 5 celle
            }
        }
    }
    int count=0;
    if(N1) count++;
    if(N2) count++;
    if(N3) count++;
    if(N4) count++;
    if(N5) count++;
    return count;
}

// Funzione per stampare la tavola
void stampaTavola(char tavola[MAX][MAX]) {
    cout << "  ";
    for (int i = 0; i < MAX; ++i) cout << i << " ";
    cout << endl;

    int rimanenti = naviRimanenti(tavola);

    for (int x = 0; x < MAX; x++) {
        cout << x << " ";
        for (int y = 0; y < MAX; y++) {
            char cella = tavola[x][y];
            char simbolo;
            switch (cella) {
                case 'A': simbolo='A'; break; 
                case 'X': simbolo='X'; break; 
                default: simbolo='_'; break;  
            }
            cout << simbolo << " ";
        }
        cout << endl;
    }
    cout<<"Navi rimanenti: " << rimanenti<<endl;
}

// Funzione per posizionare una nave
bool posizionaNave(char tavola[MAX][MAX], int lunghezza, char simbolo) {
    bool posizionata = false;
    while (!posizionata) {
        int x = rand() % MAX;
        int y = rand() % MAX;
        int direzione = rand() % 2; 
        bool spazioLibero = true;

        if (direzione == 0) { // orizzontale
            if (y + lunghezza <= MAX) {
                for (int i = 0; i < lunghezza; i++)
                    if (tavola[x][y + i] != '_') spazioLibero = false;
                if (spazioLibero) {
                    for (int i = 0; i < lunghezza; i++)
                        tavola[x][y + i] = simbolo;
                    posizionata = true;
                }
            }
        } else { 
            if (x + lunghezza <= MAX) {
                for (int i = 0; i < lunghezza; i++)
                    if (tavola[x + i][y] != '_') spazioLibero = false;
                if (spazioLibero) {
                    for (int i = 0; i < lunghezza; i++)
                        tavola[x + i][y] = simbolo;
                    posizionata = true;
                }
            }
        }
    }
    return posizionata;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    srand(time(NULL));
    int cx=0, cy=0, tentativi=0;
    char tavola[MAX][MAX];

    cout << "                                                       Battaglia navale" << endl;
    cout << "Gioca contro l'IA: lei posizionerà le navi casualmente e dovrai indovinare le loro posizioni per affondarle." << endl;
    cout << "La tavola è strutturata come una griglia 10x10, numerata da 0 a 9. Inizia con la tavola vuota e man mano che inserisci le coordinate, vedrai se hai colpito una nave con l'icona 'X' o se hai preso l'acqua con 'A'." << endl;
    cout << "Saranno generate 5 navi con lunghezze diverse: 1, 2, 3, 4 e 5 posti." << endl;
    cout << "Affonda tutte le navi nel minor numero di tentativi possibile." << endl;
    cout << endl << "Premi invio per iniziare...";
    getchar();

    for(int x=0;x<MAX;x++)
        for(int y=0;y<MAX;y++)
            tavola[x][y]='_';

    posizionaNave(tavola, 1, 'N');
    posizionaNave(tavola, 2, 'O');
    posizionaNave(tavola, 3, 'P');
    posizionaNave(tavola, 4, 'Q');
    posizionaNave(tavola, 5, 'R');

    bool controllo;
    do {
        system("cls");
        cout << "Tavola di gioco:" << endl;
        stampaTavola(tavola);
        cout << "Inserisci le coordinate da 0 a 9 (prima y, poi x): ";
        cin >> cx >> cy;
        tentativi++;

        if(cx<0 || cx>=MAX || cy<0 || cy>=MAX) {
            cout << "Coordinate non valide. Inserire coordinate tra 0 e 9." << endl;
            tentativi--;
            Sleep(1000);
            continue;
        }

        if(tavola[cx][cy]=='N' || tavola[cx][cy]=='O' || tavola[cx][cy]=='P' || tavola[cx][cy]=='Q' || tavola[cx][cy]=='R') {
            cout << "Hai colpito una nave, continua così!" << endl;
            tavola[cx][cy]='X';
        } else if(tavola[cx][cy]=='_') {
            cout << "Hai preso l'acqua!" << endl;
            tavola[cx][cy]='A';
        } else {
            cout << "Hai già inserito queste coordinate!" << endl;
            tentativi--;
        }

        controllo = naviRimanenti(tavola) > 0;
        Sleep(500);
    } while(controllo);

    system("cls");
    cout << "Congratulazioni, hai distrutto tutte le navi! Il gioco è finito, hai usato " << tentativi << " tentativi." << endl;
    cout << "Premi invio per uscire...";
    getchar();
    return 0;
}
