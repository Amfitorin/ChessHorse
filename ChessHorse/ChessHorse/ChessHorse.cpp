// ChessHorse.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

bool CanBeDone(int& u, int& v, int& i);
void tryNextMove(int& x, int& y, int& i, bool& done);
void KnightsTour(int x0, int y0, bool done);
void Clear(void);
void Next(int& k, int&x, int&y, bool& eos, int& u, int& v);
void First(int& k, int&x, int&y, bool& eos, int& u, int& v);
void Print();
const int height = 7;
const int width = 6;
int h[height][width];
int drop=0;
int dx[8] = { 2, 1, -1, -2, -2,-1,1,2 };
int dy[8] = { 1,2,2,1,-1,-2,-2,-1 };

int main()
{

	KnightsTour(1, 2, false);
	Print();
	int c;
	cin >> c;
	return 0;
}

bool CanBeDone(int & u, int & v, int & i)
{
	bool done;
	h[u][v] = i;
	tryNextMove(u, v, i, done);
	if (!done)
		h[u][v] = 0;
	return done;
}

void tryNextMove(int & x, int & y, int & i, bool & done)
{
	bool eos;
	int u, v, k;
	if (i < width * height - drop)
	{
		int temp = i + 1;
		First(k, x, y, eos, u, v);
		while (!eos && !CanBeDone(u, v, temp))
		{
			Next(k, x, y, eos, u, v);
		}
		done = !eos;
	}
	else
		done = true;
}

void Next(int& k, int&x, int&y, bool& eos, int& u, int& v) {
	do
	{
		k++;
		if (k < 8)
		{
			u = x + dx[k];
			v = y + dy[k];
		}
	} while (k < 8 && !(u >= 0 && u < height && v >= 0 && v < width && h[u][v] == 0));
	eos = k == 8;
}

void First(int& k, int&x, int&y, bool & eos, int & u, int & v)
{
	eos = false;
	k = -1;
	Next(k, x, y, eos, u, v);
}

void Print()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
			cout <<cout.width(6)<< h[i][j];
		cout << endl<<endl;
	}
}

void KnightsTour(int x0, int y0, bool done)
{
	for (int x = 0; x < height; x++)
	{
		for (int y = 1; y < width; y++)
			if (h[x][y] == 0)
			{
				Clear();
				int index = 1;
				h[x][y] = 1;
				tryNextMove(x, y, index, done);
				if (done)
					break;
			}
		if (done)
			break;
	}
}

void Clear(void)
{

	ifstream f("input.txt");
	if (!f.is_open()) cout << "Error!" << endl;
	else
	{
		drop = 0;
		int n;
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				f >> n;
				if (n == -1)
					drop++;
				h[i][j] = n;
			}
		}
		f.close();
	}			
}
