#include <iostream>
#include <random>
#include <list>
#include <array>
#include <string>

using namespace std;

const int ROW = 10;
const int COL = 12;

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
	int x, y, deley, command;//czy dodac stringa nazwe?
	bool direction;
	char nazwa;
	Plane(int a, int b, int c, int d, bool e, char f);
	~Plane();

private:

};

Plane::Plane(int a, int b, int c, int d, bool e, char f)
{
	x = a;
	y = b;
	deley = c;
	command = d;
	direction = e;
	nazwa = f;
}

Plane::~Plane()
{
}

void set_board(array<array<Tile, COL>, ROW> &board);
void view_board(array<array<Tile, COL>, ROW>& board);

int main()
{
	array<array<Tile, COL>, ROW> board;
    cout << "Hello World!\n";
	set_board(board);
	view_board(board);
	list<Plane> samolot;
	Plane obj1(1,2,3,3,0,'A');
	samolot.push_back(obj1);
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
	}
}
//zastosowac clean coda zeby bylo ok
//dodajemy samoloty na koncu(push_back), a usuwamy na poczatku(pop_front)
//tworzymy nieskoczona petle programu
//1 losujemy czy ma sie pojawic nowy samolot, globalna zmienna probalistyczna int (od 0 do 100) losujemy w randomie liczbe od 0 do 100 i jesli wylosowana jest mniejsza od prob to losujemy samolot
//2 losowanie czy ma sie samolot poruszac w lewo czy w prawo
//3 loswanie na ktorym torze ma sie pojawic i zrobic if czy nie bedzie kolizji przy pojawieniu sie nowego samolotu i losowac az znajdzi sie miejsce w odleglosci 7 pol
//4 logika zderzen dziala do 2 pol odleglosci, przelatuje forem po kazdym rzedzie i sprawdzam czy istnije taka sytuacja ze 
//5 dodac do klasy atrybut oznaczajcy ile razy za wykonac dany rozkaz
//6zrobic logike jak doleci