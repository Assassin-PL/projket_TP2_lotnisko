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
	void print_tile()
	{
		cout << tile_view;
	}
	void set_tile(char tile_new)
	{
		tile_view = tile_new;
	}
	Tile(char new_tile = ' ')
	{
		tile_view = new_tile;
	}
	~Tile()
	{
	}
private:

};
class Plane
{
public:
	int x, y, deley, command;
	bool direction;
	char nazwa;
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
	Plane(int row_value, int column_value, int plain_value_of_deley, int set_command, bool flight_direction, char name_of_plain)
	{
		set_plane(row_value, column_value, plain_value_of_deley, set_command, flight_direction, name_of_plain);
	}
	~Plane()
	{
	}
private:

};

void make_turn(list<Plane>& samolot, array<array<Tile, COL>, ROW>& board);
void losuj_samolot(list<Plane>& samolot, array<array<Tile, COL>, ROW> board);
void menu(list<Plane>& samolot, array<array<Tile, COL>, ROW>& board);
void set_board(array<array<Tile, COL>, ROW>& board);
void view_board(array<array<Tile, COL>, ROW>& board);
void fill_the_board(array<array<Tile, COL>, ROW>& board, list<Plane>& samolot);
void move_plain(list<Plane>& samolot, array<array<Tile, COL>, ROW>& board, char nazwa);
int algorytm_losujacy(int beg, int end);
int check_number(int number, list<Plane>& samolot, bool direction, int& tries);
bool check_neigbours(bool direction, int which_row, array<array<Tile, COL>, ROW> board);
bool is_collsision(list<Plane>& samolot);
bool check_priv_zone(list<Plane>::iterator j, list<Plane>::iterator i);
char check_name(char name, list<Plane>& samolot);
list<Plane>::iterator get_itterator_of_plane(list<Plane>& samolot, char nazwa);

int main()
{
	setlocale(LC_CTYPE, "Polish");
	array<array<Tile, COL>, ROW> board;
	set_board(board);
	list<Plane> samolot;
	losuj_samolot(samolot, board);
	fill_the_board(board, samolot);
	cout << endl;
	view_board(board);
	menu(samolot, board);
	return 0;
}

int algorytm_losujacy(int beg, int end)
{
	random_device rd; 
	mt19937 gen(rd()); 
	uniform_int_distribution<> distr(beg, end); 

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

void losuj_samolot(list<Plane>& samolot, array<array<Tile, COL>, ROW> board)
{
	int a, b, c, d;
	d = 0;
	Plane obj1(0, 0, 0, 0, 0, '=');
	c = algorytm_losujacy(0, 1);
	if (c == 1)
	{
		a = algorytm_losujacy(1, ROW - 2);
		a = check_number(a, samolot, 1, d);
		if (a > 0 && a < ROW - 2 && check_neigbours(c, a, board))
		{
			obj1.set_plane(a, 0, 0, 0, 1, check_name('A', samolot));
			samolot.push_back(obj1);
		}
	}
	else
	{
		b = algorytm_losujacy(1, ROW - 2);
		b = check_number(b, samolot, 0, d);
		if (b > 0 && b < ROW - 2 && check_neigbours(c, b, board))
		{
			obj1.set_plane(b, COL - 1, 0, 0, 0, check_name('A', samolot));
			samolot.push_back(obj1);
		}
	}
}

int check_number(int number, list<Plane>& samolot, bool direction, int& tries)
{
	if (tries < 10000)
	{
		for (list<Plane>::const_iterator i = samolot.begin(); i != samolot.end(); ++i)
		{
			if (i->x == number && direction == 1 && i->y == 0)
			{
				number = algorytm_losujacy(1, ROW - 2);
				tries++;
				number = check_number(number, samolot, direction, tries);
			}
			if (i->x == number && direction == 0 && i->y == COL - 1)
			{
				number = algorytm_losujacy(1, ROW - 2);
				tries++;
				number = check_number(number, samolot, direction, tries);
			}
		}
		return number;
	}
	else 
	{
		return 0;
	}
}

char check_name(char name, list<Plane>& samolot)
{
	for (list<Plane>::iterator i = samolot.begin(); i != samolot.end(); ++i)
	{
		if (i->nazwa == name)
		{
			name += 1;
		}
	}
	return name;
}
bool check_neigbours(bool direction, int which_row, array<array<Tile, COL>, ROW> board)
{
	if (direction == 1)
	{
		for (int i = 2; i < 7; i++)
		{
			if (board[which_row][0 + i].tile_view != ' ' || board[which_row + 1][0 + i].tile_view != ' ' || board[which_row - 1][0 + i].tile_view != ' ')
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		for (int i = 2; i < 7; i++)
		{
			if (board[which_row][COL - 1 - i].tile_view != ' ' || board[which_row + 1][COL - 1 - i].tile_view != ' ' || board[which_row - 1][COL - 1 - i].tile_view != ' ')
			{
				return false;
			}
		}
		return true;
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
		board[wsk_plane->x][wsk_plane->y + 1] = char(wsk_plane->deley + '0');
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
	for (list<Plane>::iterator i = samolot.begin(); i != samolot.end(); ++i)
	{

		if (i->direction == 1)
		{
			if (i->y + 8 == COL)
			{
				board[i->x][i->y] = ' ';
				board[i->x][i->y - 1] = ' ';
				board[i->x][i->y + 1] = ' ';
				board[i->x][i->y + 2] = ' ';
				board[i->x][i->y - 2] = ' ';
				i = samolot.erase(i);
			}
			else
			{
				if (i->deley > 0 && i->deley < 10)
				{
					i->deley--;
				}
				else
				{
					i->command = 0;
				}
				move_plain(samolot, board, i->nazwa);
			}
		}
		else
		{
			if (i->y - 8 == 0)
			{
				board[i->x][i->y] = ' ';
				board[i->x][i->y - 1] = ' ';
				board[i->x][i->y + 1] = ' ';
				board[i->x][i->y + 2] = ' ';
				board[i->x][i->y + 3] = ' ';
				i = samolot.erase(i);
			}
			else
			{
				if (i->deley > 0 && i->deley < 10)
				{
					i->deley--;
				}
				else
				{
					i->command = 0;
				}
				move_plain(samolot, board, i->nazwa);
			}
		}
	}
	if (algorytm_losujacy(0, 100) <= probability)losuj_samolot(samolot, board);
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
	if ((ile > 9 || ile < 1) && gdzie != 'c') return 0;
	for (list<Plane>::const_iterator i = samolot.begin(); i != samolot.end(); ++i)
	{
		if (i->nazwa == nazwa)
		{
			if (gdzie == '/' && i->x - ile < 1) {
				cout << "Nie mozna przesunac sie o tyle pol w gore!" << endl;
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

bool is_collsision(list<Plane>& samolot)
{
	list<Plane>::iterator k;
	for (list<Plane>::iterator j = samolot.begin(); j != samolot.end(); ++j)
	{
		j++;
		k = j;
		j--;
		for (list<Plane>::iterator i = k; i != samolot.end(); ++i)
		{
			if (check_priv_zone(i, j))
			{
				return true;
			}
		}
	}
	return false;
}

bool check_priv_zone(list<Plane>::iterator plain1, list<Plane>::iterator plain2)
{
	for (int j = 0; j < 6; j++)
		for (int i = -1; i < 2; i++)
		{
			if (plain2->direction == 1) {
				if ((plain1->x == (plain2->x + i) && plain1->y == (plain2->y + j)) || (plain2->x == (plain1->x + i) && plain2->y == (plain1->y + j)))
				{
					return true;
				}
			}
			else {
				if ((plain1->x == (plain2->x + i) && plain1->y == (plain2->y - j)) || (plain2->x == (plain1->x + i) && plain2->y == (plain1->y - j)))
				{
					return true;
				}
			}
		}
	return false;
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

		cout << "\n <znak samolotu> c  anulowanie rozkazu";

		cout << "\n  _____________________________ \n";
		cout << "\n Proszę wpisać komendę: ";
		getline(cin, choice);
		while ((choice[0] < 'A' || choice[0] > 'Z') && choice[0] != ' ') {
			cout << "Niepoprawna instrukcja! Proszę wpisać instrukcję taką jak na liście." << endl;
			getline(cin, choice);
		}
		system("cls");
		make_turn(samolot, board);
		if (choice[0] == ' ')
		{
			cout << "Nastepna tura..." << endl;
		}
		else if (choice[0] >= 'A' && choice[0] <= 'Z')
		{
			while (!WpisPoprawny(samolot, choice[0], choice[1], choice[2]))
			{
				cout << "Niepoprawne dane. Proszę wpisać nazwę samolotu obecnego na planszy, który ma mozliwość ruszenia się o daną liczbę ruchów" << endl;
				cin >> choice;
			}
			wsk_plane = get_itterator_of_plane(samolot, choice[0]);
			if (choice[1] == 'c') {
				wsk_plane->command = 0;
				wsk_plane->deley = 0;
			}
			else {
				wsk_plane->deley = choice[2] - '0';
				if (choice[1] == '\\') {
					wsk_plane->command = 1;
					if (wsk_plane->direction == 1) {
						board[wsk_plane->x][wsk_plane->y + 1] = char(wsk_plane->deley + '0');
						board[wsk_plane->x][wsk_plane->y + 3] = '\\';
					}
					else {
						board[wsk_plane->x][wsk_plane->y + 1] = char(wsk_plane->deley + '0');
						board[wsk_plane->x][wsk_plane->y - 2] = '/';
					}
				}
				else if (choice[1] == '/') {
					wsk_plane->command = 2;
					if (wsk_plane->direction == 1) {
						board[wsk_plane->x][wsk_plane->y + 1] = char(wsk_plane->deley + '0');
						board[wsk_plane->x][wsk_plane->y + 3] = '/';
					}
					else {
						board[wsk_plane->x][wsk_plane->y + 1] = char(wsk_plane->deley + '0');
						board[wsk_plane->x][wsk_plane->y - 2] = '\\';
					}
				}

			}
		}
		fill_the_board(board, samolot);
		view_board(board);
	} while (!is_collsision(samolot));

	cout << "Uwaga! Wystąpiła kolizja!" << endl;
}
