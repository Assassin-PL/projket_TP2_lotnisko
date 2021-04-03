#include <iostream>
#include <random>
#include <list>
#include <array>
#include <string>

using namespace std;

const int ROW = 10;
const int COL = 100;
const int probability = 100;

class Tile
{
public:
	char tile_view = ' ';
	Tile(char new_tile);
	~Tile();
	void print_tile()
	{
		cout << tile_view;
	}
	void set_tile(char tile_new)
	{
		tile_view = tile_new;
	}
private:

};

Tile::Tile(char new_tile = ' ')
{
	tile_view = new_tile;
}

Tile::~Tile()
{
}

class Plane
{
public:
	int x, y, deley=0, command;
	bool direction;
	char nazwa;
	Plane(int row_value, int column_value, int plain_value_of_deley, int set_command, bool flight_direction, char name_of_plain);
	~Plane();
	void set_plane(int row_value, int column_value, int plain_value_of_deley, int set_command, bool flight_direction, char name_of_plain)
	{
		if (row_value >= 0 && row_value < ROW)
		{
			x = row_value;
		}
		else
		{
			x = 0;
		}
		if (column_value >= 0 && column_value < COL)
		{
			y = column_value;
		}
		else
		{
			y = 0;
		}
		deley = plain_value_of_deley;
		if (set_command == 0 || set_command == 1 || set_command == 2)
		{
			command = set_command;
		}
		else
		{
			command = 0;
		}
		direction = flight_direction;
		nazwa = name_of_plain;
	}
private:

};

Plane::Plane(int row_value, int column_value, int plain_value_of_deley, int set_command, bool flight_direction, char name_of_plain)
{
	if (row_value >= 0 && row_value < ROW)
	{
		x = row_value;
	}
	else
	{
		x = 0;
	}
	if (column_value >= 0 && column_value < COL)
	{
		y = column_value;
	}
	else
	{
		y = 0;
	}
	deley = plain_value_of_deley;
	if (set_command == 0 || set_command == 1 || set_command == 2)
	{
		command = set_command;
	}
	else
	{
		command = 0;
	}
	direction = flight_direction;
	nazwa = name_of_plain;
}

Plane::~Plane()
{
}

void losuj_samolot(list<Plane>& samolot);
void menu(list<Plane>& samolot, array<array<Tile, COL>, ROW>& board);
void set_board(array<array<Tile, COL>, ROW>& board);
void view_board(array<array<Tile, COL>, ROW>& board);
void fill_the_board(array<array<Tile, COL>, ROW>& board, list<Plane>& samolot);
void move_plain(list<Plane>& samolot, array<array<Tile, COL>, ROW>& board, char nazwa);
int algorytm_losujacy(int beg, int end);
int check_number(int number, list<Plane>& samolot, bool direction, int& tries);
bool check_neigbours(bool direction, int which_row, array<array<Tile, COL>, ROW> board);
char check_name(char name, list<Plane>& samolot);
list<Plane>::iterator get_itterator_of_plane(list<Plane>& samolot, char nazwa);

int main()
{
	setlocale(LC_CTYPE, "Polish");
	array<array<Tile, COL>, ROW> board;
	set_board(board);
	//view_board(board);
	list<Plane> samolot;
	losuj_samolot(samolot);
	fill_the_board(board, samolot);
	cout << endl;
	view_board(board);
	menu(samolot, board);
	return 0;
}

int algorytm_losujacy(int beg, int end)
{
	random_device rd; // obtain a random number from hardware
	mt19937 gen(rd()); // seed the generator
	uniform_int_distribution<> distr(beg, end); // define the range

	return distr(gen);
}

void set_board(array<array<Tile, COL>, ROW>& board)
{
	char board_borders = '=';
	char board_rows = '|';
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (i == 0 || i == (ROW - 1))
			{
				board[i][j].set_tile(board_borders);
			}
			else
			{
				if (j == 1 || j == (COL - 2))
				{
					board[i][j].set_tile(board_rows);
				}
			}

		}
	}
}

void view_board(array<array<Tile, COL>, ROW>& board)
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			board[i][j].print_tile();
		}
		cout << endl;
		cout << endl;
	}
}

void fill_the_board(array<array<Tile, COL>, ROW>& board, list<Plane>& samolot)
{
	for (list<Plane>::const_iterator i = samolot.begin(); i != samolot.end(); ++i)
	{
		board[i->x][i->y] = i->nazwa;
	}
}

void losuj_samolot(list<Plane>& samolot)
{
	int a, b, c, d;
	d = 0;
	Plane obj1(0, 0, 0, 0, 0, '=');
	c = algorytm_losujacy(0, 1);
	if (c == 1)
	{
		a = algorytm_losujacy(1, ROW - 2);
		a = check_number(a, samolot, 1, d);//jesli zostanie zwrocone 0 to znaczy ze nie moze sie pojawic nowy samolot na hangarze
		if (a > 0 && a < ROW - 2)
		{
			obj1.set_plane(a, 0, 0, 0, 1, check_name('A', samolot));
			samolot.push_back(obj1);
		}
	}
	else
	{
		b = algorytm_losujacy(1, ROW - 2);
		b = check_number(b, samolot, 0, d);
		if (b > 0 && b < ROW - 2)
		{
			obj1.set_plane(b, COL - 1, 0, 0, 0, check_name('A', samolot));
			samolot.push_back(obj1);
		}
	}
}

int check_number(int number, list<Plane>& samolot, bool direction, int& tries)
{
	if (tries < 10000000)// sprawdzanie czy nie nastapilo wiecej niz zalecane liczba losowan
	{
		for (list<Plane>::const_iterator i = samolot.begin(); i != samolot.end(); ++i)
		{
			if (i->x == number && direction == 1)
			{
				number = algorytm_losujacy(1, ROW - 2);
				tries++;//za kazdym razem wylosowania nowej liczby zwieksza sie liczba tries
				number = check_number(number, samolot, direction, tries);
			}
			if (i->x == number && direction == 0)
			{
				number = algorytm_losujacy(1, ROW - 2);
				tries++;
				number = check_number(number, samolot, direction, tries);
			}
		}
		return number;
	}
	else //jesli liczba prob przekroczy 10000000 to funkcja zwroci 0 i to spowoduje ze juz sie nie pojawi samolot
	{
		return 0;
	}
}

char check_name(char name, list<Plane>& samolot)
{
	for (list<Plane>::const_iterator i = samolot.begin(); i != samolot.end(); ++i)// funkcja sprawdza po kazdyym elemencie samolotu czy jest zarezerwowana taka nazwa
	{// kod sie zaczyna od pierwszej litery zapisanej w liscie samolotow
		if (i->nazwa == name)
		{
			name += 1;//jesli tak to inkrementiuje literke podana do funkcji
		}
		else
		{
			return name;//jesli takiej literki nie ma to zwraca ja 
		}
	}
	return name;//jesli lista jest pusta i for nie moze sie wykonac to wtedy jest zwracana podana podana literka
}
bool check_neigbours(bool direction, int which_row, array<array<Tile, COL>, ROW> board)
{
	if (direction == 1)
	{
		for (int i = 2; i < 7; i++)
		{
			if (board[which_row + i][COL].tile_view == ' ')
			{
				return true;
			}
		}
		return false;
	}
	else
	{
		for (int i = 2; i < 7; i++)
		{
			if (board[which_row - i][COL].tile_view == ' ')
			{
				return true;
			}
		}
		return false;
	}
}

void move_plain(list<Plane>& samolot, array<array<Tile, COL>, ROW>& board, char nazwa)
{
	list<Plane>::iterator wsk_plane;
	wsk_plane = get_itterator_of_plane(samolot, nazwa);
	if (wsk_plane->direction == 1)
	{
		board[wsk_plane->x][wsk_plane->y] = ' ';
		if (wsk_plane->y == 0)
		{
			wsk_plane->y += 2;
		}
		else
		{
			board[wsk_plane->x][wsk_plane->y - 1] = ' ';
			board[wsk_plane->x][wsk_plane->y + 1] = ' ';
			board[wsk_plane->x][wsk_plane->y + 2] = ' ';
			board[wsk_plane->x][wsk_plane->y + 3] = ' ';
		}
		switch (wsk_plane->command)
		{
		case 0:
			wsk_plane->y += 1;
			break;
		case 1:
			wsk_plane->x += 1;
			wsk_plane->y += 1;
			break;
		case 2:
			wsk_plane->x -= 1;
			wsk_plane->y += 1;
			break;
		default:
			wsk_plane->y += 1;
			break;
		}
		board[wsk_plane->x][wsk_plane->y] = wsk_plane->nazwa;
		board[wsk_plane->x][wsk_plane->y - 1] = '(';
		board[wsk_plane->x][wsk_plane->y + 1] = char(wsk_plane->deley + '0');
		board[wsk_plane->x][wsk_plane->y + 2] = ')';
		switch (wsk_plane->command)
		{
		case 0:
			board[wsk_plane->x][wsk_plane->y + 3] = '=';
			break;
		case 1:
			board[wsk_plane->x][wsk_plane->y + 3] = '\\';
			break;
		case 2:
			board[wsk_plane->x][wsk_plane->y + 3] = '/';
			break;
		default:
			board[wsk_plane->x][wsk_plane->y + 3] = '=';
			break;
		}
	}
	else
	{
		board[wsk_plane->x][wsk_plane->y] = ' ';
		if (wsk_plane->y == COL - 1)
		{
			wsk_plane->y -= 3;
		}
		else
		{
			board[wsk_plane->x][wsk_plane->y + 2] = ' ';
			board[wsk_plane->x][wsk_plane->y + 1] = ' ';
			board[wsk_plane->x][wsk_plane->y - 1] = ' ';
			board[wsk_plane->x][wsk_plane->y - 2] = ' ';
		}
		switch (wsk_plane->command)
		{
		case 0:
			wsk_plane->y -= 1;
			break;
		case 1:
			wsk_plane->x += 1;
			wsk_plane->y -= 1;
			break;
		case 2:
			wsk_plane->x -= 1;
			wsk_plane->y -= 1;
			break;
		default:
			wsk_plane->y -= 1;
			break;
		}
		board[wsk_plane->x][wsk_plane->y] = wsk_plane->nazwa;
		board[wsk_plane->x][wsk_plane->y - 1] = '(';
		board[wsk_plane->x][wsk_plane->y + 1] = char(wsk_plane->deley +'0');
		board[wsk_plane->x][wsk_plane->y + 2] = ')';
		switch (wsk_plane->command)
		{
		case 0:
			board[wsk_plane->x][wsk_plane->y - 2] = '=';
			break;
		case 1:
			board[wsk_plane->x][wsk_plane->y - 2] = '/';
			break;
		case 2:
			board[wsk_plane->x][wsk_plane->y - 2] = '\\';
			break;
		default:
			board[wsk_plane->x][wsk_plane->y - 2] = '=';
			break;
		}
	}
}

void make_turn(list<Plane>& samolot, array<array<Tile, COL>, ROW>& board)
{
	for (list<Plane>::iterator i = samolot.begin(); i != samolot.end(); ++i)// zaczynamy od zliczania kazdego samolotu
	{
		if (i->direction == 1)//sprawdzamy w jakim kierunku nasz samolot leci, 1 oznacza ze leci w prawo
		{
			if (i->y + 2 == COL)//jesli samolotowi leczosemu w prawo zostana 2 pola do konca tablicy to znaczy ze samolot wykonal ruch
			{
				samolot.erase(i);//funkcja zajmujaca sie kasowaniem samolotu zaznacznego itteratorem i
			}
			else
			{
				if (i->deley > 0 && i->deley < 10)//funkcja liczaca opoznienie, jesli zwroci prawde to bedzie sie poruszalo w kierunku command
				{
					move_plain(samolot, board, i->nazwa);
					i->deley--;
				}
				else//jesli nie to defultowo jest zaznaczone ze samolot leci lotem prostym
				{
					i->command = 0;
					move_plain(samolot, board, i->nazwa);
				}
			}
		}
		else//to samo co powyzej tylko dla lewej strony
		{
			if (i->y - 2 == 0)
			{
				samolot.erase(i);
			}
			else
			{
				if (i->deley > 0 && i->deley < 10)
				{
					move_plain(samolot, board, i->nazwa);
					i->deley--;
				}
				else
				{
					i->command = 0;
					move_plain(samolot, board, i->nazwa);
				}
			}
		}
	}
	if (algorytm_losujacy(0, 100) <= probability)losuj_samolot(samolot);//po kazdym ruchu jest inicjalizacja pojawienia sie samolotu
}

list<Plane>::iterator get_itterator_of_plane(list<Plane>& samolot, char nazwa)
{
	for (list<Plane>::iterator i = samolot.begin(); i != samolot.end(); ++i)
	{
		if (i->nazwa == nazwa)
		{
			return i;
		}
	}
}

bool WpisPoprawny(list<Plane>& samolot, char nazwa, char gdzie, int ile) {
	ile -= '0';
	if ((ile > 9 || ile < 1) && gdzie!='c') return 0;
	for (list<Plane>::const_iterator i = samolot.begin(); i != samolot.end(); ++i)
	{
		if (i->nazwa == nazwa)
		{
			if (gdzie == '/' && i->x - ile < 1) {
				cout << "Nie mozna przesunac sie o tyle pol w gore!"<<endl;
				return 0;
			}
			else if (gdzie == '\\' && i->x + ile > ROW - 2) {
				cout << "Samolot nie moze obniżyć się o tyle pól!" << endl;
				return 0;
			}
			else return 1;
		}
	}
	cout << "Nie ma takiego samolotu w zasięgu!" << endl;
	return 0;
}

void menu(list<Plane>& samolot, array<array<Tile, COL>, ROW>& board)
{
	string choice;
	list<Plane>::iterator wsk_plane;
	do
	{
		cout << "\n Menu";

		cout << "\n  _____________________________ \n";

		cout << "\n Komendy:";

		cout << "\n <spacja> - nastepna tura";

		cout << "\n <znak samolotu> / <liczba 1-9> - nakaz wzniesienia sie o podana liczbe pol";

		cout << "\n <znak samolotu> \\ <liczba 1-9> - nakaz opadania o podana liczbe pol";

		cout << "\n <znak samolotu> = - lot stabilny";

		cout << "\n <znak samolotu> c  anulowanie rozkazu";

		cout << "\n Debug: p wyjscie";

		cout << "\n Debug: cokolwiek k pokaz tablice";

		cout << "\n  _____________________________ \n";
		cout << "\n Enter selection: ";
		getline(cin, choice);
		if (choice[0] == ' ')
		{
			cout << "Nastepna tura" << endl;
			//i w tym momencie wszystkie samoloty powinny wykonać ruch do przodu, lub tak jak jeszcze im zostało
		}
		else if (choice[0] >= 'A' && choice[0] <= 'Z')
		{
			while (!WpisPoprawny(samolot, choice[0], choice[1], choice[2]))
			{
				cout << "Niepoprawne dane. Prosze wpisac nazwe samolotu obecnego na planszy, ktory ma mozliwosc ruszenia sie o dana liczbe ruchow" << endl;
				cin >> choice;
			}
			//if (algorytm_losujacy(0, 100) <= probability) losuj_samolot(samolot);//tu samolotowi powinna zostać przypisana wartość zmiennej [0,9] do opadania
			wsk_plane = get_itterator_of_plane(samolot, choice[0]);
			if (choice[1] == 'c') { 
				wsk_plane->command = 0;
				wsk_plane->deley = 0;
			}
			else {
				if (choice[1] == '\\') wsk_plane->command = 1;
				else if (choice[1] == '/') wsk_plane->command = 2;
				wsk_plane->deley = choice[2];
			}

		}
		else cout << "Niepoprawna instrukcja!" << endl;
		//system("cls");
		make_turn(samolot, board);
		//fill_the_board(board, samolot);
		view_board(board);
	} while (choice[0] != 112);
}
//zastosowac clean coda zeby bylo ok
//dodajemy samoloty na koncu(push_back), a usuwamy na poczatku(pop_front)
//tworzymy nieskoczona petle programu
//1 losujemy czy ma sie pojawic nowy samolot, globalna zmienna probalistyczna int (od 0 do 100) losujemy w randomie liczbe od 0 do 100 
// i jesli wylosowana jest mniejsza od prob to losujemy samolot
//2 losowanie czy ma sie samolot poruszac w lewo czy w prawo
//3 loswanie na ktorym torze ma sie pojawic i zrobic if czy nie bedzie kolizji przy pojawieniu sie nowego samolotu 
// i losowac az znajdzi sie miejsce w odleglosci 7 pol
//4 logika zderzen dziala do 2 pol odleglosci, przelatuje forem po kazdym rzedzie i sprawdzam czy istnije taka sytuacja ze 
//5 dodac do klasy atrybut oznaczajcy ile razy za wykonac dany rozkaz
//6 zrobic logike jak doleci
