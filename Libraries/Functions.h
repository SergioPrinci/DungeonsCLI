#include <iostream> //cout, cin, endl
#include <fstream> //stream file, per la mappa, vita e flag varie
#include <string> //gestione stringhe
#include <windows.h> //gotoxy e sleep()
#include <cstdlib> //gotoxy e rand
#include <conio.h> //gotoxy
#include <ctime> //srand
#include <limits> //per pulire il buffer di cin
#include <mmsystem.h> //per le musiche e gli effetti sonori
using namespace std;

extern const int x; //larghezza fissa per tutte le mappe
extern const int y; //altezza fissa per tutte le mappe

/*
 uso le costanti x e y in modo che non vengano create mappe 
 troppo grandi e nel rispetto delle proporzioni, nel caso 
 vengano create e usate, vengono tagliate perchÃ© lette solo in parte
*/

extern float tempo;
extern char map[64][30];
extern struct player giocatore;
extern struct flags flag;
extern string frase;

/*
 queste variabili sono poste a globali
 poiché mi sono necessarie per molte delle funzioni,
 e usarle come parametro mi tornava particolarmente scomodo
*/

//dichiarazione funzioni di gioco
int game(); //main game
	int cancellasalva(); //funzione per cancellare file di salvataggio
	bool carica(string name); //carica la mappa
	bool spawnS(int &coordXspawn, int &coordYspawn); //spawna il player nella mappa(spawn regolare)
	bool spawnR(int &coordXspawn, int &coordYspawn); //spawna il player nella mappa(respawn)
	bool search(char s, int &xs, int &ys); //funzione di ricerca nell'array
	bool finalCollision(); // funzione per finale
	bool caricasalva(); // funzione per caricare i salvataggi
	void gotoxy(int x, int y); //gotoxy per posizione e movimento
	void print(); //stampa la mappa ignorando spazi vuoti delimitati dagli 0 nel tileset
	void gotoxySpawn(int &x, int &y); //gotoxy per spawn e inizializzazione posizione
	void collisionBorder(int tplayerx, int tplayery); //funzione per collisioni contro bordi mappa
	void cambiaMappa(string name, string extension, string &file); //arrivato alla posizione L, il gioco carica la mappa successiva
	void enemyCollision(); //funzione per rilevare collisione e quindi battaglia con un nemico
	void pauseMenu(); // funzione per il menu di pausa
	void nicePrint();
	void color(unsigned short color); //funzione per cambiare colore al singolo carattere
	void salva(); //funzione per i salvataggi
	void entranceSong(); //canzone di sfondo del gioco
	void entranceDialogue(); //dialogo di inizio gioco
	void finalDialogue(); //dialogo per il finale
	void passoSound(); //suono per i passi
	void tesoroSound(); //suono per tesoro
	void tutorial(); //tutorial
	//dichiarazione funzioni di battaglia
bool battle(); //avvia la battaglia
	bool fenice(); //funzione contenente i dati per la fenice
	bool mostroAcqua(); //funzione contenente i dati per il mostro d'acqua
	bool golem(); //funzione contenente i dati del golem
	bool drago(); //funzione contenente i dati del drago
	void battaglia(float &vita, float mulFuoco, float mulAcqua, float mulTerra, float mulAria); //funzione di battaglia principale
	void keys(); //funzione di aggiornamento chiavi
	void failureSong(); //canzone di sconfitta
	void victorySong(); //canzone di vittoria
	//dichiarazione funzioni di boss battle
bool bossbattle(); //funzione per avviare la boss battle
	bool Gvng(); //funzione per la battaglia principale
	void nicePrintBoss(); //funzione per scrivere il testo(stile BOSS)
	void nicePrintRainbow(); //funzione per scrivere il testo colorato
