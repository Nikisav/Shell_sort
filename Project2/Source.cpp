#include<iostream>
#include <windows.h>
#include <thread>
#include <chrono>
#include<vector>

using namespace std;

void shell(int* mas, int id, int step, int how_meny_cores, int size);			// ������� ����������

bool pff(int answer, int page);													// pff - Protection from fools, �������� �� ������������ ������� ��������

bool menu(int& size_mm);														//����.___.

void fill_and_limit(int* mas, int size_mm);										// ��������� ������ � ������������ ������ �����

void start_work(int* mas, int size);											//"����" ���������

void print(int* mas, int size, chrono::time_point<chrono::high_resolution_clock> start, chrono::time_point<chrono::high_resolution_clock> end); // ����� �����������

//////////////////////////////////////////////////////////////////////

int main()
{
	setlocale(LC_ALL, "RUS");

	srand(static_cast<int>(time(0)));

	int size_mm;							//����������� �������

	bool wtd = menu(size_mm);				//wtd - what to do, ����������, ��� ��������� ����� ������ ������

	if (wtd == 0)							//� ���� ������ ����� ������ �� ���������
		return 0;

	int* mas = new int[size_mm];			//������� ������

	fill_and_limit(mas, size_mm);

	start_work(mas, size_mm);

	system("pause");

	return 0;
}

//////////////////////////////////////////////////////////////////////
	
void shell(int* mas, int id, int step, int how_meny_cores, int size)
{
	if (id * how_meny_cores >= step)return;

	int temp;

	for (int j = id * how_meny_cores; j < (id + 1) * how_meny_cores && j < step; j++)
	{
		int k;
		for (int i = j; i < size; i += step)
		{
			temp = mas[i];
			for ( k = i; k >= step; k -= step)
			{
				if (temp < mas[k - step])
					mas[k] = mas[k - step];
				else
					break;
			}
			mas[k] = temp;
		}
	}
}

bool menu(int& size_mm)												//����.___.
{
	int choice, page;
	cout << "��������� ��� ���������� ������� ������� �����";
	this_thread::sleep_for(chrono::milliseconds(1500));
	system("cls");

	page = 1;
	while (1)
	{
		cout << "==================����==================" << endl;
		cout << "1. ������ ������" << endl;
		cout << "2. ����� �� ���������" << endl;
		cin >> choice;
		system("cls");
		if (pff(choice, page) == true)
			break;
	}
	if (choice == 2)
		return false;

	cout << "������ �� ��������� ������� (���� ���������)\n " << endl;
	this_thread::sleep_for(chrono::milliseconds(1000));
	system("cls");
	cout << "������� �������� �����������" << endl;
	cin >> size_mm;
	system("cls");
	return true;

}

void fill_and_limit(int* mas, int size_mm)	// ��������� ������ � ������������ ������ �����
{
	for (int i = 0; i < size_mm; ++i)
	{
		mas[i] = rand() % 1000;
		cout << mas[i] << " ";
	}
}

void start_work(int* mas, int size)				//"����" ���������
{
	chrono::time_point<chrono::high_resolution_clock> start, end;

	start = chrono::high_resolution_clock::now();

	int Threads = thread::hardware_concurrency();

	for (int step = size / 2; step > 0; step /= 2)
	{
		vector<thread>threads;

		int how_meny_cores = ceil(double(step) / double(Threads));

		for (int id = 0; id < Threads; id++)
			threads.push_back(thread(shell, mas, id, step, how_meny_cores, size));

		for (int id = 0; id < Threads; id++)
			threads[id].join();
	}

	end = chrono::high_resolution_clock::now();

	print(mas, size, start, end);
}

void print(int* mas, int size, chrono::time_point<chrono::high_resolution_clock> start, chrono::time_point<chrono::high_resolution_clock> end) // ����� �����������
{
	cout << endl;

	for (int i = 0; i < size; ++i)
	{
		cout << mas[i] << " ";
	}

	cout << endl;

	double elapsed_seconds = chrono::duration_cast<chrono::milliseconds> (end - start).count();
	cout << "����������� ����� : " << elapsed_seconds << endl;
}

bool pff(int answer, int page)							// pff - Protection from fools, �������� �� ������������ ������� ��������
{
	if (page == 1)
		if (answer == 1 || answer == 2)
			return true;

	return false;
}