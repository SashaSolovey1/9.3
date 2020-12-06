#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h> // забезпечення відображення кирилиці
using namespace std;
enum Magazin { Zina, Gastronom, Blizenko };
string magazinStr[] = { "Зіна", "Гастроном", "Близенько" };
struct Price
{
	string nazva;
	Magazin magazin;
	union
	{
		double $;
	};
};
void Create(Price* p, const int N);
void Print(Price* p, const int N);
void Sort(Price* p, const int N);
int main()
{ // забезпечення відображення кирилиці:
	SetConsoleCP(1251); // встановлення сторінки win-cp1251 в потік вводу
	SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу
		int N;
	cout << "Введіть кількість товарів N: "; cin >> N;

	Price* p = new Price[N];
	double proc;
	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [3] - фізичне впорядкування даних" << endl << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			Create(p, N);
			break;
		case 2:
			Print(p, N);
			break;
		case 3:
			Sort(p, N);
			break;
		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
	} while (menuItem != 0);
	return 0;
}
void Create(Price* p, const int N)
{
	int magazin;
	for (int i = 0; i < N; i++)
	{
		cout << "Товар № " << i + 1 << ":" << endl;
		cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
		cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок

		cout << " назва: "; getline(cin, p[i].nazva);
		cout << " магазин (0 - Зіна, 1 - Гастроном, 2 - Близенько): ";
		cin >> magazin;
		p[i].magazin = (Magazin)magazin;
		switch (p[i].magazin)
		{
		case Zina:
		case Gastronom:
		case Blizenko:
			cout << " Ціна : "; cin >> p[i].$;
			break;
		}
		cout << endl;
	}
}
void Print(Price* p, const int N)
{
	cout << "========================================================================="
		<< endl;
	cout << "| №   | Назва        | Магазин    | Ціна      |"
		<< endl;
	cout << "-------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(3) << right << i + 1 << " ";
		cout << "| " << setw(13) << left << p[i].nazva
		<< "| " << setw(11) << left << magazinStr[p[i].magazin];
		switch (p[i].magazin)
		{
		case Zina:
		case Gastronom:
		case Blizenko:
		cout << "| " << setw(9) << setprecision(2) << fixed << right
			<< p[i].$ << " |" << setw(13) << right << endl;
			break;
		}
	}
	cout << "========================================================================="
		<< endl;
	cout << endl;
}
void Sort(Price* p, const int N)
{
	Price tmp;
	for (int i0 = 0; i0 < N - 1; i0++) // метод "бульбашки"
		for (int i1 = 0; i1 < N - i0 - 1; i1++)
			if ((p[i1].magazin > p[i1 + 1].magazin)
				||
				(p[i1].magazin == p[i1 + 1].magazin &&
					p[i1].nazva > p[i1 + 1].nazva))
			{
				tmp = p[i1];
				p[i1] = p[i1 + 1];
				p[i1 + 1] = tmp;
			}
}
