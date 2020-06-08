#include "Functions.h"

struct player 
{
	string nome;
	int vitaPlayer = 1000;
	int mapIndex = 0;
	int playerx = 0;
	int playery = 0;
	int key = 0;
} giocatore;

struct flags
{
	bool vsaveflag = false;
	bool menuflag = false;
	bool endflag = false;
	bool developer = false;
	bool beta = false;
} flag;

//INIZIO FUNZIONI DI GIOCO
bool carica(string name)
{
	ifstream input;
	input.open(name); //name Ã© una stringa che modifico con il giocatore.nome del file, e quindi del tileset che devo prelevare e caricare
	char a;
	
	if (input.is_open())
	{
		for (int i = 0; i < y; i++)
		{
			for (int j = 0; j < x; j++)
			{
				input >> a;
				map[j][i] = a;
			}
		}
		input.close();
		return true;
	}

	else
	{
		cout << "Error in file stream for function carica()!" << endl;
		input.close();
		system("pause");
		return false;
	}
}

void print()
{
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			if (map[j][i] == '0')
			{
				cout << " ";
			}

			else if (map[j][i] == 'L' || map[j][i] == 'S' || map[j][i] == 'B' || map[j][i] == 'R')
			{
				cout << " ";
			}

			else if (map[j][i] == 'F')
			{
				color(10);
				cout << "O";
				color(7);
			}

			else if (map[j][i] == 'E')
			{
				color(12);
				cout << "X";
				color(7);
			}

			else if (map[j][i] == 'T')
			{
				color(14);
				cout << "T";
				color(7);
			}

			else
			{
				color(8);
				cout << map[j][i];
				color(7);
			}
		}
		cout << endl;
	}
}

bool spawnS(int &coordXspawn, int &coordYspawn)
{
	if (search('S', coordXspawn, coordYspawn))
	{
		gotoxySpawn(coordXspawn, coordYspawn);
		cout << "P";
		return true;
	}

	cout << "Spawnpoint not found for function spawnS()!" << endl;
	system("pause");
	return false;
}

bool spawnR(int &coordXspawn, int &coordYspawn)
{
	if (search('R', coordXspawn, coordYspawn))
	{
		gotoxySpawn(coordXspawn, coordYspawn);
		cout << "P";
		return true;
	}

	cout << "Spawnpoint not found for function spawnR()!" << endl;
	system("pause");
	return false;
}

bool search(char s, int &xs, int &ys)
{
	int flag = 0;
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			if (map[j][i] == s)
			{
				xs = j;
				ys = i;
				flag++;
			}
		}
	}

	if (flag > 0)
	{
		return true;
	}

	cout << "Subject not found for function search()!" << endl;
	system("pause");
	return false;
}

void gotoxySpawn(int &x, int &y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void collisionBorder(int tplayerx, int tplayery)
{
	if (map[giocatore.playerx][giocatore.playery] == '*')
	{
		giocatore.playerx = tplayerx;
		giocatore.playery = tplayery;
	}
}

void cambiaMappa(string name, string extension, string &file)
{
	file = "";
	file = name + to_string(giocatore.mapIndex) + extension;
}

void enemyCollision()
{
	if (map[giocatore.playerx][giocatore.playery] == 'E')
	{
		system("cls");
		if (battle())
		{
			gotoxy(giocatore.playerx, giocatore.playery);
			map[giocatore.playerx][giocatore.playery] = '0';
		}
		
		else
		{
			flag.menuflag = true;
			flag.endflag = true;
		}
		
		system("cls");
		print();
		gotoxy(giocatore.playerx, giocatore.playery);
		cout << "P";
	}
}

int game()
{
	//DICHIARAZIONE VARIABILI
	int tplayerx, tplayery, tesoro;
	char stroke;
	bool tflag, victoryflag = false;
	string name = "Map/map", extension = ".ts", file;

	file = name + to_string(giocatore.mapIndex) + extension;
	system("MODE 64, 33");
	srand(time(NULL));
	
	if (!tflag)
	{
		if (carica(file))
		{
			print();
			spawnS(giocatore.playerx, giocatore.playery);
		}
		
		
		else
		{
			cout << "File stream error for function main()!" << endl;
			system("pause");
			return 0;
		}
	}
	
	else
	{
		print();
		gotoxySpawn(giocatore.playerx, giocatore.playery);
		cout<<"P";
	}
	
	time_t now=time(0);
	clock_t start, end;
	start=clock();
	
	do //CICLO DI MOVIMENTO
	{
		if(flag.developer)
		{
			gotoxy(0, 31);
			color(10);
			cout << "Developer mode";
			
			if (flag.beta)
			{
				cout << "				      Beta functions: on";
			}
			
			color(7);
		}
		
		flag.menuflag = false;
		flag.endflag = false;

		tplayerx = giocatore.playerx;
		tplayery = giocatore.playery;

		stroke = getch(); //prende il carattere digitato da tastiera, in questo caso W, A, S, D o ESC

		switch (stroke)
		{
		case 'w': //se é W
			giocatore.playery--;
			collisionBorder(tplayerx, tplayery);
			gotoxy(giocatore.playerx, giocatore.playery);
			cout << "P";
			gotoxy(giocatore.playerx, giocatore.playery + 1);
			cout << " ";
			passoSound();
			break;
		case 'a': //se é A
			giocatore.playerx--;
			collisionBorder(tplayerx, tplayery);
			gotoxy(giocatore.playerx, giocatore.playery);
			cout << "P";
			gotoxy(giocatore.playerx + 1, giocatore.playery);
			cout << " ";
			passoSound();
			break;
		case 's': //se é S
			giocatore.playery++;
			collisionBorder(tplayerx, tplayery);
			gotoxy(giocatore.playerx, giocatore.playery);
			cout << "P";
			gotoxy(giocatore.playerx, giocatore.playery - 1);
			cout << " ";
			passoSound();
			break;
		case 'd': //se é D
			giocatore.playerx++;
			collisionBorder(tplayerx, tplayery);
			gotoxy(giocatore.playerx, giocatore.playery);
			cout << "P";
			gotoxy(giocatore.playerx - 1, giocatore.playery);
			cout << " ";
			passoSound();
			break;
		case 27: //se é ESC, quindi esce
			pauseMenu();
			break;
		default: //se non é un carattere di quelli sopra, attende ancora fino allo stroke di uno di quei tasti
			break;
		}

		enemyCollision();

		if (giocatore.vitaPlayer <= 0)
		{
			flag.endflag = true;
			return 0;
		}

		if (map[giocatore.playerx][giocatore.playery] == 'L')
		{
			giocatore.mapIndex++;
			cambiaMappa(name, extension, file);
			if (carica(file))
			{
				system("cls");
				print();
				spawnS(giocatore.playerx, giocatore.playery);
			}
			
			else
			{
				cout << "File stream error for function main()!" << endl;
				system("pause");
				return 0;
			}
		}
		
		if (map[giocatore.playerx][giocatore.playery] == 'B' && flag.beta)
		{
			giocatore.mapIndex--;
			cambiaMappa(name, extension, file);
			if (carica(file))
			{
				system("cls");
				print();
				spawnR(giocatore.playerx, giocatore.playery);
			}
			
			else
			{
				cout << "File stream error for function main()!" << endl;
				system("pause");
				return 0;
			}
		}

		else if (map[giocatore.playerx][giocatore.playery] == 'F')
		{
			if (giocatore.key>=10)
			{
				system("cls");
				if (bossbattle())
				{
					finalDialogue();
					end = clock();
					tempo = ((double)(end-start))/CLOCKS_PER_SEC;
					gotoxy(0, 32);
					frase = "Complimenti, hai vinto!\n";
					nicePrint();
					
					if (!flag.vsaveflag)
					{
						frase = "Hai impiegato " + to_string(tempo/60) + " minuti per completare il gioco!\n";
						nicePrint();
					}
					
					ofstream theend;
					theend.open("TheEnd.txt");
					theend << "PlUtclUtcWQuHFcoa2MgcF9xYRvJYRAia21vaFksYV50zRAvYWHfYWMyYWIkHFExblk2XWQuHFYoal8fXRAwcVUycF8fbGUtcF8falUraBckb3Ara3IgdlkualTfYFUrHF1oaxAmzV9ia24JBj1oHGMual8faV9rcF8fYFk2YWI0zWQuHF5kaBAlXWIraxAkHGMual8fbFk1cGQub3QuHGMuYFQob2YgcGQuHFQkaBAxzWM1aGQgcF8tBkMvYWIuHGYoclEsYV50YRAjzRAia250zV51XWIkHGAkbhAwcVUycFDfb3QxXVQgHFMnYRAgbGAxYWo6axA2YWIgaVUtcFTfaV9rcF86HFMxYVExYRA2zVQka2coa2MnzR4JTFUxX2iCpRAoaBA2zVQka2coa2MuHF9xaVEoHF5uahCCpRAvzbN6HFktcFUxbGIkcFE0axAia21kHFwuHFUxXRAtYVcrzRAgal5oHCfvIx4JS3IgHFkrHGYoYFUuY2kuX28fv6jfaV9rcF8fYFjfbFmCth4JRVvfclkjYV9mzV9iaxAubl1gzRCCpRA1ahAsYWo6axAia24fzVvfbWUgaFTfX29scV5oX2ExYRvfcV4faV9jaxAvYWHfYWMvblksYWIyzRvfb2YuY2Exb2jfYRAvYWHfb29izVErzWo6XWIkKfqChRA1alDfYl9xaVDfYBcgbmQkHFQoclUxb2DfYFDfcGU0cFTfaFTfXVw0blTfbFUxX2iCpRAtYRAgX2MuaWUtXRAgaFM1alTrHFMuaVTfYlDfzVvfX2ktYV1gHBgscWMoX2DrHFYucF9mblElzVDrHFExcFjfblEvbGIkb2UtcFE0zWYkJRvfaVDfX2jfaVU0cFTfcV5gHFMub2DfX2gkHF1galMgHFDfaV9rcFTfYl9xaVTfYBcgbmQkNhArI2ktcFUxXWQ0zWYocLNgKfoVYVQoHFcoa2MgcF9xYRvfaBcgbmQkHGA1v7LfYWMyYWIkHFMuaWAxYWMgHFQgHGAuX2goHFTfaFDfaWUyzVMgHGAkbhArXRAycVDfcF90XVwocLNgHGA1blTrHF1gHFkrHGYoYFUuY2kuX28fv6jfbWUgaFMub2DfXVvfbWUgaFTfa2ctzRAkb3MkblTfcV1gal8fbGWCrxAvXWI0YVMobFExYRAgaF1kal8fcV5gHGYuaGQgHF5kaFwgHGYocFDtBjvmYWYuaGU6zV9tYRAia250zV51YWKCnRAkHFjfclkjYV9mzV9izFjfb2ExXV5taxAkHGMual8fcV5gHGAgbmQkHGAubmQgamQkHFQoHGQ1cGQuHFMov7LfX2gkHFMoHFMoblMualQkbrNgKfoMXRArI3UuaV8fv6jfb3AgclUtcFE0axAjXVwrI2kmal90axAvYWIizLNoHF1ob3Qkblkub28fYRA0XVw2a2w0XRAjzRA1alDfXlUraFU6dlDfal9tHFMuaWAxYV5yzVIoaFTtBfoSbFUxaxAizFTfcGTfX29sbGIkalQkblEoHGE1YVwraxAizFTfzF8fXWAvYV5gHFQkcGQuHFTfX2gkHFQoclUtcFjfbFExcFTfYFjfcFTfYRAjYVwrYRA0cVTfzVQkYR4JQFklYl9tYFjfaFTfcGUkHFkjYVTrHGMla3I6XWQoHFTfblUgaFk6dlDfzRA0cV9oHGMuY25oKfoNcVwrXRCCpRA0bl9vbF8faF9tcFEtaxvfYRAgHGYuaGQkHFIgb3QgHFEraGUtY2ExYRA1ahAvaxbfaFDfaVEtax4JBjcxXWooYRAvYWHfXWYkbhAmzV9iXWQuHPoSYWMmzV9mJFEqXRASYWImzV8fTGIoalMoclEraFTo" << endl;
					theend << "3 1 5 19 1 18  11 14 15 23 19 640" << endl;
					theend.close();
					flag.menuflag = true;
					flag.endflag = true;
					system("pause");
					return 0;
				}
				
				else
				{
					flag.menuflag = true;
					flag.endflag = true;
					return 0;
				}
			}
			
			else
			{
				gotoxy(0, 32);
				frase = "Ti mancano " + to_string(10-giocatore.key) + " chiavi per aprire e fuggire!\n";
				nicePrint();
				system("pause");
				system("cls");
				print();
				gotoxy(giocatore.playerx, giocatore.playery);
				cout << "P";
			}
		}

		else if (map[giocatore.playerx][giocatore.playery] == 'T' || rand()%400+1 == 1)
		{
			if (rand()%2+1 == 1)
			{
				gotoxy(0, 32);
				tesoro = rand() % 400 + 300;
				frase = "Hai trovato un tesoro e hai recuperato " + to_string(tesoro) + " di salute!\n";
				nicePrint();
				tesoroSound();
				giocatore.vitaPlayer += tesoro;
				system("pause");
				system("cls");
				map[giocatore.playerx][giocatore.playery] = '0';
				print();
				gotoxy(giocatore.playerx, giocatore.playery);
				cout << "P";
			}
			
			else
			{
				giocatore.key++;
				gotoxy(0, 32);
				frase = "Hai trovato una chiave!\n";
				nicePrint();
				frase = "Chiavi totali: " + to_string(giocatore.key) + ".\n";
				nicePrint();
				system("pause");
				system("cls");
				map[giocatore.playerx][giocatore.playery] = '0';
				print();
				gotoxy(giocatore.playerx, giocatore.playery);
				cout << "P";
				
			}
		}

	} while (!flag.menuflag);
	return 0;
}

void pauseMenu()
{
	bool tempexit = false;
	flag.menuflag = false;
	flag.endflag = false;
	char tempscelta;
	passoSound();
	
	do
	{
		system("cls");
		cout << "Vita: " << giocatore.vitaPlayer << endl; 
		cout << "Chiavi trovate: " << giocatore.key << endl << endl;
		cout << "----------------------------" << endl;
		cout << "Menu di pausa:" << endl << endl;
		cout << "q - Esci dal gioco" << endl;
		cout << "b - Torna al menu principale" << endl;
		cout << "s - Salva i progressi" << endl;
		cout << "ESC - Torna al gioco" << endl << endl;

		tempscelta = getch();

		switch (tempscelta)
		{
			case 'q':
				flag.menuflag = true;
				flag.endflag = true;
				tempexit = true;
				break;
			case 'b':
				flag.menuflag = true;
				flag.endflag = false;
				tempexit = true;
				system("cls");
				break;
			case 's':
				salva();
				break;
			case 27:
				tempexit = true;
				system("cls");
				print();
				gotoxy(giocatore.playerx, giocatore.playery);
				cout << "P";
				break;
			default:
				cout << "Input incorretto." << endl;
				Sleep(1500);
				break;
		}
	} while (!tempexit);
	passoSound();
}

void nicePrint()
{
	cout << "> ";
	for (int i=0; i<frase.length(); i++)
	{
		cout << frase[i];
		Sleep(10);
	}
	Sleep(1000);
}

void color(unsigned short color)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, color);
}

void entranceSong()
{
	PlaySound(TEXT("Media/LoopGame.wav"), NULL, SND_LOOP | SND_ASYNC);
}

void passoSound()
{
	Beep(587, 30);
}

void tesoroSound()
{
	Beep(523, 150);
	Beep(659, 150);
	Beep(784, 300);
}

void salva()
{
	ofstream savefile;
	savefile.open("SaveFile/save.sav");
	savefile << giocatore.nome << endl;
	savefile << giocatore.mapIndex << endl;
	savefile << giocatore.vitaPlayer << endl;
	savefile << giocatore.playerx << endl;
	savefile << giocatore.playery << endl;
	savefile << giocatore.key << endl;
	
	for (int i=0; i<30; i++)
	{
		for (int j=0; j<64; j++)
		{
			savefile << map[j][i];
		}
		savefile << endl;
	}
	
	frase = "Salvataggio completato.\n";
	nicePrint();
	savefile.close();
	system("pause");
}

bool caricasalva()
{
	char a;
	
	ifstream savefile;
	savefile.open("SaveFile/save.sav");
	
	if (savefile)
	{
		savefile >> giocatore.nome;
		savefile >> giocatore.mapIndex;
		savefile >> giocatore.vitaPlayer;
		savefile >> giocatore.playerx;
		savefile >> giocatore.playery;
		savefile >> giocatore.key;
		
		for (int i = 0; i < 30; i++)
		{
			for (int j = 0; j < 64; j++)
			{
				savefile >> a;
				map[j][i] = a;
			}
		}
		
		frase = "Salvataggio convalidato e caricato.\n";
		flag.vsaveflag = true;
		nicePrint();
		system("pause");
		return true;
	}
	
	frase = "Salvataggio corrotto o non esistente.\n";
	flag.vsaveflag = false;
	nicePrint();
	system("pause");
	return false;
}

void entranceDialogue()
{
	system("cls");
	
	frase = giocatore.nome + ", " + giocatore.nome + "!\n";  //qui uso una stringa al posto di un'array di char perché mi torna piú comodo usare l'operatore "+"
	nicePrint();
	frase = "Per favore " + giocatore.nome + ", svegliati.\n";
	nicePrint();
	frase = "So che sei confuso, e che non sai dove sei.\n";
	nicePrint();
	frase = "Devi trovare la forza di alzarti.\n";
	nicePrint();
	frase = "Non ho idea di che posto sia questo...\n";
	nicePrint();
	frase = "Devi uscire di qui il piu' in fretta possibile.\n";
	nicePrint();
	frase = "Raggiungi la fine del dungeon.\n";
	nicePrint();
	frase = "Supera gli ostacoli piu' ardui.\n";
	nicePrint();
	frase = "Non so quanto tempo tu abbia prima che questo luogo venga sigillato...\n";
	nicePrint();
	system("pause");
}

int cancellasalva()
{
	char scelta;
	
	do
	{
		system("cls");
		
		cout << "Sei sicuro di voler cancellare tutti i dati di salvataggio?(y/n)" << endl;
		cin >> scelta;
		
		switch(scelta)
		{
			case 'y':
				system("del SaveFile/save.sav");
				cout << "Salvataggio cancellato." << endl;
				system("pause");
				return 0;
				break;
			case 'n':
				cout << "Annullamento cancellazione salvataggio." << endl;
				system("pause");
				return 0;
				break;
			default:
				cout << "Scelta non esistente!" << endl;
				system("pause");
				break;
		}
	} while(1);
}

void finalDialogue()
{
	system("cls");
	PlaySound(TEXT("Media/VictorySong.wav"), NULL, SND_ASYNC);
	frase = "E' tutto finito ormai.\n";
	nicePrint();
	frase = "A quanto pare ce la hai fatta, " + giocatore.nome + ".\n";
	nicePrint();
	frase = "Sei riuscito ad uscire dal dungeon...non credevo che tu potessi farcela.\n";
	nicePrint();
	frase = "Beh, per questa volta mi hai sconfitto...ma la prossima non sará cosí facile.\n";
	nicePrint();
	frase = "Ci ricorderemo di te, " + giocatore.nome + " , stanne certo...\n";
	nicePrint();
}

void tutorial()
{
	system("cls");
	cout << "-----------------------------------------------------------------" << endl;
	cout << "Guida iniziale:" << endl;
	frase = "Per muoversi utilizzare i tasti WASD\n\n";
	nicePrint();
	frase = "Combatti i nemici per raccogliere le 10 chiavi per uscire!\n\n";
	nicePrint();
	frase = "Ogni nemico ha una debolezza, e' tuo compito cercare di scoprirla!\n\n";
	nicePrint();
	frase = "Se stai per perdere tutta la vita, cerca i tesori nella mappa(T)!\n> Potresti anche trovare una chiave!\n\n";
	nicePrint();
	frase = "Raggiungi la fine del dungeon per vincere!\n";
	nicePrint();
	cout << "-----------------------------------------------------------------" << endl;
}
//FINE FUNZIONI DI GIOCO

//INIZIO FUNZIONI DI BATTAGLIA
bool battle()
{
	system("MODE 80, 33");
	srand(time(NULL));
	int random = rand() % 4 + 1;

	switch (random)
	{
		case 1:
			cout << "Sei incappato in una fenice! Devi combattere e batterla per proseguire." << endl;
			if (fenice())
			{
				system("pause");
				system("MODE 64, 33");
				return true;
			}
			
			break;
		case 2:
			cout << "Sei incappato in un mostro d'acqua! Devi combattere e batterlo per proseguire." << endl;
			if (mostroAcqua())
			{
				system("pause");
				system("MODE 64, 33");
				return true;
			}
			
			break;
		case 3:
			cout << "Sei incappato in un golem! Devi combattere e batterlo per proseguire." << endl;
			if (golem())
			{
				system("pause");
				system("MODE 64, 33");
				return true;
			}
			
			break;
		case 4:
			cout << "Sei incappato in un drago! Devi combattere e batterlo per proseguire." << endl;
			if (drago())
			{
				system("pause");
				system("MODE 64, 33");
				return true;
			}
			
			break;
	}
	
	system("pause");
	system("MODE 64, 33");
	return false;
}

bool fenice()
{
	float mulAcqua = 2, mulFuoco = 0.5, mulTerra = 1, mulAria = 1, vita = 150;
	cout << "Inizio combattimento." << endl;

	battaglia(vita, mulFuoco, mulAcqua, mulTerra, mulAria);
	
	if (giocatore.vitaPlayer <= 0)
	{
		cout << "Oh no, sei stato sconfitto..." << endl;
		failureSong();
		return false;
	}

	cout << "Bravo, hai battuto la fenice!" << endl;
	victorySong();

	keys();

	return true;
}

bool mostroAcqua()
{
	float mulAcqua = 0.5, mulFuoco = 1, mulTerra = 2, mulAria = 1, vita = 200;

	cout << "Inizio combattimento." << endl;

	battaglia(vita, mulFuoco, mulAcqua, mulTerra, mulAria);

	if (giocatore.vitaPlayer <= 0)
	{
		cout << "Oh no, sei stato sconfitto..." << endl;
		failureSong();
		return false;
	}

	cout << "Bravo, hai battuto il mostro d'acqua!" << endl;
	victorySong();

	keys();

	return true;
}

bool golem()
{
	float mulAcqua = 1, mulFuoco = 1, mulTerra = 0.5, mulAria = 2, vita = 300;
	cout << "Inizio combattimento." << endl;

	battaglia(vita, mulFuoco, mulAcqua, mulTerra, mulAria);

	if (giocatore.vitaPlayer <= 0)
	{
		cout << "Oh no, sei stato sconfitto..." << endl;
		failureSong();
		return false;
	}

	cout << "Bravo, hai battuto il golem!" << endl;

	keys();

	victorySong();
	return true;
}

bool drago()
{
	float mulAcqua = 1, mulFuoco = 2, mulTerra = 1, mulAria = 0.5, vita = 100;

	cout << "Inizio combattimento." << endl;

	battaglia(vita, mulFuoco, mulAcqua, mulTerra, mulAria);

	if (giocatore.vitaPlayer <= 0)
	{
		cout << "Oh no, sei stato sconfitto..." << endl;
		failureSong();
		return false;
	}

	cout << "Bravo, hai battuto il drago!" << endl;
	victorySong();

	keys();

	return true;
}

void battaglia(float &vita, float mulFuoco, float mulAcqua, float mulTerra, float mulAria)
{
	float attacco, abilita, random, attaccoMostro;
	int scelta;

	while (vita > 0 && giocatore.vitaPlayer > 0)
	{
		scelta = 0;
		cout << "Salute: " << giocatore.vitaPlayer << endl;
		cout << "Salute mostro: " << vita << endl << endl;
		cout << "-------------------------" << endl;
		cout << "Quale attacco vuoi usare?" << endl;
		color(12);
		cout << "1 - Turbine infuocato" << endl;
		color(11);
		cout << "2 - Raggio acquatico" << endl;
		color(2);
		cout << "3 - Pioggia di rocce" << endl;
		color(13);
		cout << "4 - Ventata distruttiva" << endl;
		color(7);
		cout << "--------------------------" << endl;

		while(!(cin >> scelta))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Input incorretto." << endl;
		}

		cout << "Potenziale d'attacco: " << endl;
		cout << "Indovina il numero da 1 a 10(escluso 0)!" << endl;
		random = rand() % 10 + 1;

		while (!(cin >> abilita))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Input incorretto." << endl;
		}

		if (random == abilita)
		{
			cout << "Wow, danno pieno!" << endl;
			attacco = 50;
		}

		else if (abilita > random - 2 && abilita < random + 1)
		{
			cout << "Danno elevato" << endl;
			attacco = 35;
		}

		else
		{
			cout << "Danno normale" << endl;
			attacco = 25;
		}

		switch (scelta)
		{
			case 1:
				attacco = attacco * mulFuoco;
				break;
			case 2:
				attacco = attacco * mulAcqua;
				break;
			case 3:
				attacco = attacco * mulTerra;
				break;
			case 4:
				attacco = attacco * mulAria;
				break;
			default:
				cout << "Attacco non esistente!" << endl;
				attacco = attacco * 0.25;
				break;
		}

		cout << "Danno inflitto: " << attacco << "!" << endl;
		vita -= attacco;
		attaccoMostro = rand() % 50 + 75;
		cout << "Il mostro ti arreca " << attaccoMostro << " di danno!" << endl;
		giocatore.vitaPlayer -= attaccoMostro;
		system("pause");
		system("cls");
	}
}

void failureSong()
{
	Beep(659, 300);
	Beep(622, 300);
	Beep(587, 300);
	Beep(554, 1000);
	Beep(554, 300);
	Beep(523, 300);
	Beep(494, 300);
	Beep(466, 1000);
	Beep(440, 1500);
}

void victorySong()
{
	Beep(587, 100);
	Beep(587, 100);
	Sleep(50);
	Beep(698, 200);
	Beep(784, 500);
}

void keys()
{
	if (rand()%2+1 == 1)
	{
		giocatore.key++;
		cout << "Hai trovato una chiave!" << endl;

		if (10-giocatore.key<=0)
		{
			cout<<"Hai trovato tutte le chiavi per scappare!" << endl;
		}

		else
		{
			cout << "Chiavi mancanti per scappare: " << 10-giocatore.key << endl;
		}
	}

	else
	{
		cout << "Nessuna chiave qui..." << endl;
	}
}
//FINE FUNZIONI DI BATTAGLIA

//INIZIO FUNZIONI DI BOSS BATTLE
bool bossbattle()
{
	system("MODE 120, 33");
	
	PlaySound(TEXT("Media/BossSong.wav"), NULL, SND_LOOP | SND_ASYNC);
	
	cout << "BOSS FINALE: " << endl;
	Sleep(500);
	frase = "GVNG, SIGNORE DEL DUNGEON\n";
	nicePrintBoss();
	color(6);
	cout << "		********" << endl;
	cout << "	    ****************" << endl;
	cout << "	  ********************" << endl;
	cout << "	************************" << endl;
	cout << "	*******"; color(8); cout << "O"; color (6); cout << "********"; color(8); cout << "O"; color(6); cout << "*******" << endl;
	cout << "        ******"; color(8); cout << "OOO"; color(6); cout << "******"; color(8); cout << "OOO"; color (6); cout << "******" << endl;
	cout << "	*******"; color(8); cout << "O"; color (6); cout << "********"; color(8); cout << "O"; color(6); cout << "*******" << endl;
	cout << "	************************" << endl;
	cout << "	  **********************" << endl;
	cout << "	    ****"; color(8); cout << "ZZZZZZZZ"; color(6); cout << "****" << endl;
	cout << "	    ****************" << endl;
	cout << "		********" << endl;
	color(10);
	cout << "		TT TT TT" << endl;
	cout << "      	       TT  TT  TT" << endl;
	cout << "     	      TT        TT" << endl;
	color(7);
	system("pause");
	system("cls");
	
	if (Gvng())
	{
		return true;
	}
	
	return false;
}

bool Gvng()
{
	int scelta;
	float vita, mulFuoco, mulAcqua, mulTerra, mulAria, attacco, abilita, random, attaccoMostro;
	char x;
	
	cout << "Gvng: ";
	frase = "PERIRAI PER MANO MIA\n";
	nicePrintBoss();
	frase = "Una forza ti assale, e la premura di uscire da questo posto ti da piu' forza e vigore!\n";
	nicePrint();
	frase = "Finalmente, hai la forza che hai sempre desiderato, e potrai usarla per sconfiggere il male piu' assoluto!\n";
	nicePrint();
	frase = "Ora e' il momento. RACCOGLI TUTTE LE TUE ENERGIE E SCONFIGGI IL SIGNORE DEL DUNGEON!\n";
	nicePrint();
	system("pause");
	system("cls");
	vita = 2000;
	mulFuoco = 5;
	mulAcqua = 5;
	mulTerra = 5;
	mulAria = 5;
	
	while (vita > 0 && giocatore.vitaPlayer > 0)
	{
		scelta = 0;
		cout << "Salute: " << giocatore.vitaPlayer << endl;
		cout << "Salute Gvng: " << vita << endl << endl;
		cout << "-------------------------" << endl;
		cout << "Quale attacco vuoi usare?" << endl;
		color(12);
		cout << "1 - Turbine infuocato" << endl;
		color(11);
		cout << "2 - Raggio acquatico" << endl;
		color(2);
		cout << "3 - Pioggia di rocce" << endl;
		color(13);
		cout << "4 - Ventata distruttiva" << endl;
		
		if (giocatore.vitaPlayer<=250)
		{
			frase =  "5 - Furia Elementale\n";
			nicePrintRainbow();
		}
		
		color(7);
		cout << "--------------------------" << endl;

		while(!(cin >> scelta))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Input incorretto." << endl;
		}

		cout << "Potenziale d'attacco: " << endl;
		cout << "Indovina il numero da 1 a 10(escluso 0)!" << endl;
		random = rand() % 10 + 1;

		while (!(cin >> abilita))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Input incorretto." << endl;
		}

		if (random == abilita)
		{
			cout << "Wow, danno pieno!" << endl;
			attacco = 50;
		}

		else if (abilita > random - 2 && abilita < random + 1)
		{
			cout << "Danno elevato" << endl;
			attacco = 35;
		}

		else
		{
			cout << "Danno normale" << endl;
			attacco = 25;
		}

		switch (scelta)
		{
			case 1:
				attacco = attacco * mulFuoco;
				break;
			case 2:
				attacco = attacco * mulAcqua;
				break;
			case 3:
				attacco = attacco * mulTerra;
				break;
			case 4:
				attacco = attacco * mulAria;
				break;
			case 5:
				if (giocatore.vitaPlayer <= 250)
				{
					attacco = rand()%30000+10000;
				}
				
				else
				{
					cout << "Attacco non esistente!" << endl;
					attacco = attacco * 0.25;
				}
				
				break;
			default:
				cout << "Attacco non esistente!" << endl;
				attacco = attacco * 0.25;
				break;
		}

		cout << "Danno inflitto: " << attacco << "!" << endl;
		vita -= attacco;
		attaccoMostro = rand() % 150 + 50;
		cout << "Il mostro ti arreca " << attaccoMostro << " di danno!" << endl;
		giocatore.vitaPlayer -= attaccoMostro;
		system("pause");
		system("cls");
	}
	
	if (giocatore.vitaPlayer>0)
	{
		frase = "QUESTA POTENZA, NOOOOOooo...\n";
		nicePrintBoss();
		frase = "...\n";
		nicePrint();
		frase = "...\n";
		nicePrint();
		frase = "...\n";
		nicePrint();
		return true;
	}
	
	cout << "Mi dispiace, ma ";
	frase = "ORA SOFFRIRAI IN ETERNO ASSIEME AGLI ALTRI.\n";
	nicePrintBoss();
	return false;

}

void nicePrintBoss()
{
	for (int i=0; i<frase.length(); i++)
	{
		cout << frase[i];
		Sleep(150);
	}
	Sleep(1000);
}

void nicePrintRainbow()
{
	for (int i=0; i<frase.length(); i++)
	{
		color(rand()%16);
		cout << frase[i];
		Sleep(1);
	}
	color(7);
}
