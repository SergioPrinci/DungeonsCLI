#include "Libraries/Functions.h"

const int x = 64; //larghezza fissa per tutte le mappe
const int y = 30; //altezza fissa per tutte le mappe

/*
 uso le costanti x e y in modo che non vengano create mappe 
 troppo grandi e nel rispetto delle proporzioni, nel caso 
 vengano create e usate, vengono tagliate perchÃ© lette solo in parte
*/

float tempo = 0;
char map[64][30] = { 0 };
string frase;

struct player 
{
	string nome;
	int vitaPlayer = 1000;
	int mapIndex = 0;
	int playerx = 0;
	int playery = 0;
	int key = 0;
};

struct flags
{
	bool vsaveflag = false;
	bool menuflag = false;
	bool endflag = false;
	bool developer = false;
	bool beta = false;
};

/*
 queste variabili sono poste a globali
 poiché mi sono necessarie per molte delle funzioni,
 e usarle come parametro mi tornava particolarmente scomodo
*/

int main()
{
	int scelta;
	
	entranceSong();
	
	do
	{
		system("cls");
		system("MODE 95, 40");
		color(12);
		cout << "-----------------------------------------------------------------------------------------------" << endl;
		cout << "|:::::::-.    ...    :::: ::.    :::.   .,-:::::   .,::::::     ...     :::.    :::.  .::::::.|" << endl;
		cout << "|  ;;,   `';, ;;     ;;;` ;;;;,  `;;;, ;;-'````'   ;;;;''''  .;;;;;;;.  `;;;;,  `;;; ;;;`    `|" << endl;
		cout << "|  `[[     [[ [['     [[[  [[[[[. '[[[ [[   [[[[[[ /[[cccc  ,[[      [[, [[[[[. '[[' [==/[[[[,|" << endl;
		cout << "|   $$,    $$ $$      $$$  $$$ 'Y$c$$' $$c.    '$$ $$''''   $$$,      $$ $$$$ 'Y$c$    '''   $|" << endl;
		cout << "|   888_,o8P' 88    .d888  888    Y88  `Y8bo,,,o88 o888oo,__'888, _ _,88 P888   Y88  88b   dP |" << endl;
		cout << "|   MMMMP'`    'YmmMMMM''  MMM     YM    `'YMUP'YM M''''YUMM  'YMMMMMP'  MMM     YM   'YMmMY' |" << endl;
		cout << "-----------------------------------------------------------------------------------------------" << endl;
		cout << "		  			 ____________" << endl;
		cout << "			   	       .~      ,   . ~." << endl;
		cout << " 			   	     |               ,  |" << endl;
		cout << " 		 	  	     |  __          __  |" << endl;
		cout << "  	 		   XX       |  |  |        |  |  |       XX" << endl;
		cout << "  	 		 XX  X      | |     |    |     | |      X  XX" << endl;
		cout << "  	 	       XX     X     |  |____|    |____|  |     X     XX" << endl;
		cout << "  	 	  XXXXX     XX      |         ||        ,|      XX     XXXXX" << endl;
		cout << "  	 	 X        XX%;;@     |,      |  |     ,|      @%%;XX        X" << endl;
		cout << "  	 	 X       X  @%%;;@     |           '  |     @%%;;@  X       X " << endl;
		cout << "  	 	 X      X     @%%;;@   |. ` ; ; ; ;  ,|   @%%;;@     X      X" << endl;
		cout << "  	 	  X    X        @%%;;@                  @%%;;@        X    X" << endl;
		cout << "	   	   X  X            @%%;;@            @%%;;@            X  X" << endl;
		cout << "  	 	    XX X             @%%;;@        @%%;;@             X XX" << endl;
		cout << "	   	     XXX              @%%;;@      @%%;;@              XXX" << endl;
		cout << "		   			  @%%;;%%;;@" << endl;
		cout << "		 	  		    @%%;;@" << endl;
		cout << "	  	 			  @%%;;@..@@" << endl;
		cout << "	  	 		        @%%;;@  @%%;;@" << endl;
		cout << "	  	 		     @%%;;@        @%%;;@" << endl;
		color(7);															                               
		cout << endl << endl << endl;
		cout << "1 - Nuovo gioco" << endl;
		cout << "2 - Carica salvataggio" << endl;
		cout << "3 - Cancella salvataggio" << endl;
		cout << "4 - Esci dal gioco" << endl;
		cout << ">";
		cin >> scelta;

		switch (scelta)
		{
			case 1:
				system("MODE 40, 5");
				system("cls");
				cout << "Come vuoi essere chiamato nel gioco? " << endl;
				cin.ignore(1000, '\n');
				getline(cin, giocatore.nome);
				system("MODE 95, 40");
				tutorial();
				system("pause");
				entranceDialogue();
				game();

				if (flag.endflag)
				{
					return 0;
				}

				break;
			case 2:
				{
					if (caricasalva())
					{
						game();
						system("MODE 95, 40");
			
						if (flag.endflag)
						{
							return 0;
						}
					}
					
					else
					{
						break;
					}
				}
			case 3:
				cancellasalva();
				break;
			case 4:
				return 0;
			case 2003:
				system("cls");
				color(10);
				cout << "Developer mode: on" << endl;
				flag.developer = true;
				cout << "Set vita: ";
				cin >> giocatore.vitaPlayer;
				cout << "Set key number: ";
				cin >> giocatore.key;
				cout << "Set mapIndex: ";
				cin >> giocatore.mapIndex;
				cout << "Set name: ";
				cin >> giocatore.nome;
				cout << "Beta functions(1 o 0): ";
				cin >> flag.beta;
				Sleep(1000);
				color(7);
				game();
			default:
				cout << "Opzione non valida!" << endl;
				Sleep(1500);
				system("cls");
				break;
		}
	} while (1);
}
