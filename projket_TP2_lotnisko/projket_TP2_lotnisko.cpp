#include <iostream>
#include <random>
#include <list>
#include <array>
#include <string>

using namespace std;

const int ROW = 10;
const int COL = 100;
const int probability = 50;

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
	int x, y, deley, command;
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
void set_board(array<array<Tile, COL>, ROW> &board);
void view_board(array<array<Tile, COL>, ROW>& board);
void fill_the_board(array<array<Tile, COL>, ROW>& board, list<Plane>& samolot);
void move_plain(list<Plane>& samolot, array<array<Tile, COL>, ROW>& board, char nazwa);
void start_flight(list<Plane>& samolot, array<array<Tile, COL>, ROW>& board, char nazwa);
int algorytm_losujacy(int beg, int end);
int check_number(int number, list<Plane>& samolot, bool direction);
bool check_neigbours(bool direction, int which_row, array<array<Tile, COL>, ROW> board);
list<Plane>::iterator get_itterator_of_plane(list<Plane>& samolot, char nazwa);

int main()
{
	array<array<Tile, COL>, ROW> board;
	set_board(board);
	view_board(board);
	list<Plane> samolot;
	losuj_samolot(samolot);
	fill_the_board(board, samolot);
	cout << endl;
	view_board(board);
	menu(samolot,board);
    return 0;
}

int algorytm_losujacy(int beg, int end)
{
	random_device rd; // obtain a random number from hardware
	mt19937 gen(rd()); // seed the generator
	uniform_int_distribution<> distr(beg, end); // define the range

	return distr(gen);
}

void set_board(array<array<Tile, COL>, ROW> &board)
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
	int a,b,c;
	Plane obj1(0, 0, 0, 0, 0, '=');
	c = algorytm_losujacy(0, 1);
	if (c == 1)
	{
		a = algorytm_losujacy(1, ROW - 2);
		a = check_number(a, samolot, 1);
		obj1.set_plane(a, 0, 0, 0, 1, 65 + samolot.size());
		samolot.push_back(obj1);
	}
	else
	{
		b = algorytm_losujacy(1, ROW - 2);
		b = check_number(b, samolot, 0);
		obj1.set_plane(b, COL - 1, 0, 0, 0, 65 + samolot.size());
		samolot.push_back(obj1);
	}
}

int check_number(int number, list<Plane>& samolot, bool direction)
{
	for (list<Plane>::const_iterator i = samolot.begin(); i != samolot.end(); ++i)
	{
		if (i->x == number && direction == 1)
		{
			number = algorytm_losujacy(1, ROW - 2);
			number = check_number(number, samolot, direction);
		}
		if (i->x == number && direction == 0)
		{
			number = algorytm_losujacy(1, ROW - 2);
			number = check_number(number, samolot, direction);
		}
	}
	return number;
}

bool check_neigbours(bool direction,int which_row, array<array<Tile, COL>, ROW> board)
{
	if (direction == 1)
	{
		for (int i = 2; i < 7; i++)
		{
			if (board[which_row  + i][COL].tile_view == ' ')
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

void move_plain(list<Plane>& samolot, array<array<Tile, COL>, ROW>& board,char nazwa)
{
	list<Plane>::iterator wsk_plane;
	wsk_plane = get_itterator_of_plane(samolot, nazwa);
	board[wsk_plane->x][wsk_plane->y] = ' ';
	if (wsk_plane->direction == 1)
	{
		switch (wsk_plane->command)
		{
		case 0:
			wsk_plane->x += 1;
			break;
		case 1:
			wsk_plane->x += 1;
			wsk_plane->y -= 1;
			break;
		case 2:
			wsk_plane->x += 1;
			wsk_plane->y += 1;
			break;
		default:
			wsk_plane->x += 1;
			break;
		}
	}
	else
	{
		switch (wsk_plane->command)
		{
		case 0:
			wsk_plane->x -= 1;
			break;
		case 1:
			wsk_plane->x -= 1;
			wsk_plane->y -= 1;
			break;
		case 2:
			wsk_plane->x -= 1;
			wsk_plane->y += 1;
			break;
		default:
			wsk_plane->x -= 1;
			break;
		}
	}
	board[wsk_plane->x][wsk_plane->y] = wsk_plane->nazwa;
}

void start_flight(list<Plane>& samolot, array<array<Tile, COL>, ROW>& board, char nazwa)
{
	list<Plane>::iterator wsk_plane;
	wsk_plane = get_itterator_of_plane(samolot, nazwa);
	board[wsk_plane->x][wsk_plane->y] = ' ';
	if (wsk_plane->direction == 1)
	{
		switch (wsk_plane->command)
		{
		case 0:
			wsk_plane->x += 1;
			break;
		case 1:
			wsk_plane->x += 1;
			wsk_plane->y -= 1;
			break;
		case 2:
			wsk_plane->x += 1;
			wsk_plane->y += 1;
			break;
		default:
			wsk_plane->x += 1;
			break;
		}
	}
	else
	{
		switch (wsk_plane->command)
		{
		case 0:
			wsk_plane->x -= 1;
			break;
		case 1:
			wsk_plane->x -= 1;
			wsk_plane->y -= 1;
			break;
		case 2:
			wsk_plane->x -= 1;
			wsk_plane->y += 1;
			break;
		default:
			wsk_plane->x -= 1;
			break;
		}
	}
	board[wsk_plane->x][wsk_plane->y] = wsk_plane->nazwa;
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
		cin >> choice;
		if (choice[0] == ' ')
		{
			cout << "Nastepna tura" << endl;
			//i w tym momencie wszystkie samoloty powinny wykonać ruch do przodu, lub tak jak jeszcze im zostało
			//break;
		}
		else
		{
			switch (choice[1])
			{
			case 'e':if(algorytm_losujacy(0,100)<=probability)losuj_samolot(samolot);
				break;
			case 'k':
				fill_the_board(board, samolot);
				view_board(board);
				break;
			case '=':; //to niepotrzebne
				break;
			case 92: cout << "dupa"; //tu samolotowi powinna zostać przypisana wartość zmiennej [0,9] do opadania
				break;
			case '/':                //tu samolotowi powinna zostać przypisana wartość zmiennej [0,9] do wznoszenia; jeżeli samolot już ma wyznaczone opadanie, powinna się blokować taka możliwość
				wsk_plane = get_itterator_of_plane(samolot, choice[0]);
				wsk_plane->command = 2;
				if (wsk_plane->y == 0 || wsk_plane->y == COL - 1)
				{
					move_plain(samolot, board, choice[0]);
				}
				else   //sam ruch samolotów powinien się odbywać chyba w jednym momencie, więc w tej planszy powinniśmy tylko dodawać samolotom wartości do wznoszenia
				{
					move_plain(samolot, board, choice[0]);
				}
				break;
			case 'c':cout << "dupa3"; //powinna być jakaś zmienna określająca ile jeszcze samolotowi zostało (może już jest). Gdy zostanie wpisane c, ta zmienna powinna być zerowana
				break;
			default: system("cls");
				break;
			}
		}
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
