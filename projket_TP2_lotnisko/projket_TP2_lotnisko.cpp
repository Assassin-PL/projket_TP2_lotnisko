#include <iostream>
#include <random>
#include <vector>

using namespace std;

class plansza
{
public:
	bool is_visited = 0;
	int x, y;
	plansza();
	~plansza();
	void visit_point()
	{
		is_visited = 1;
	}
private:

};

plansza::plansza()
{
	x = 0;
	y = 0;
	is_visited = 0;
}

plansza::~plansza()
{
}

int main()
{
    cout << "Hello World!\n";
	plansza* ptr_plansza = new plansza[1];
	cout << ptr_plansza->is_visited<<endl;
	ptr_plansza->visit_point();
	cout << ptr_plansza->is_visited;
	delete[] ptr_plansza;
    return 0;
}

int algorytm_losujacy(int beg, int end)
{
	random_device rd; // obtain a random number from hardware
	mt19937 gen(rd()); // seed the generator
	uniform_int_distribution<> distr(beg, end); // define the range

	return distr(gen);
}
