// Hammurabi.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <iostream>
#include <cctype>
#include <Windows.h>

#include <cstdlib>
#include <random>
#include <string>


bool TryParseInt(const std::string& in_value, int& out_value)
{
	// check if string contains any non-digit symbols
	if (!std::all_of(in_value.begin(), in_value.end(), ::isdigit))
	{
		return false;
	}

	try
	{
		out_value = std::stoi(in_value);
		return true;
	}
	catch (std::out_of_range) // if input value doesn't fit in integer
	{
		return false;
	}
}

class Babylon
{
private:
	int population_;
	int bushels_;
	int acres_;
	int year_;

	int harvest_;
	int starved_people_;
	int new_people_;
	int bushels_destroyed_;
	int price_;
	bool plague_;

	int acres_to_buy_;
	int acres_to_sell_;
	int bushels_to_eat_;
	int acres_to_sow_;
public:
	Babylon()
	{
		population_ = 100;
		bushels_ = 2800;
		acres_ = 1000;
		year_ = 1;

		harvest_ = 0;
		starved_people_ = 0;
		new_people_ = 0;
		bushels_destroyed_ = 0;
		plague_ = false;
		GeneratePrice();
	}

	void GeneratePrice()
	{
		std::mt19937 gen(time(0));
		std::uniform_int_distribution<> uid(17, 26);
		price_ = uid(gen);
	}

	int CountStarved()
	{
		return 1;

	}

	void UpdateCityState()
	{

	}

	void PrintYearReport()
	{
		std::cout << "��� ����������, �������� �������� ����:";
		std::cout << "\n\t� ���� " << year_ << " ������ ����������� ���������";
		if (starved_people_ != 0)
		{
			std::cout << "\n\t" << starved_people_ << " ������� ������ ��-�� ������;";
		}
		if (new_people_ != 0)
		{
			std::cout << "\n\t" << new_people_ << " ������� ������� � ��� �����;";
		}
		if (plague_)
		{
			std::cout << "\n\t" << "���� ���������� �������� ���������;";
		}
		else
		{
			std::cout << "\n\t" << "���� ������ ��� ����� ��������;";
		}
		std::cout << "\n\t��������� ������ ���������� " << population_ << " �������;";
		std::cout << "\n\t�� ������� " << harvest_ << " ������� �������, �� " << harvest_ / acres_ << " ������ � ����;";
		std::cout << "\n\t����� ��������� " << bushels_destroyed_ << " ������� �������, ������� " << bushels_ << " ������ � �������; ";
		std::cout << "\n\t����� ������ �������� " << acres_ << " �����;";
		std::cout << "\n\t���� ������ ���� ���������� " << price_ << " �������.";
	}

	void GetKingsOrders()
	{
		std::string input_string;
		while (true)
		{
			// acres to buy
			std::cout << "\n������� ����� ����� ����������� ������? ";
			acres_to_buy_ = 0;
			while (true)
			{
				std::cin >> input_string;
				if (!TryParseInt(input_string, acres_to_buy_))
				{
					std::cout << "����������, ��� ����������. �������, ����������: ";
					continue;
				}
				if (acres_to_buy_ * price_ > bushels_)
				{
					std::cout << "����������, �� �� ����� ���� ����� ���������. �������, ����������:";
					continue;
				}
				break;
			}

			// acres to sell
			std::cout << "\n������� ����� ����� ����������� �������? ";
			acres_to_sell_ = 0;
			while (true)
			{
				std::cin >> input_string;
				if (!TryParseInt(input_string, acres_to_sell_))
				{
					std::cout << "����������, ��� ����������. �������, ����������: ";
					continue;
				}
				if (acres_to_sell_ > acres_to_buy_ + acres_)
				{
					std::cout << "����������, �� �� ����� ���� ����� ��������� � ������ ���������� ��������. �������, ����������:";
					continue;
				}
				break;
			}

			// bushels to eat
			std::cout << "\n������� ������� ����������� ������ ��������� ��� ���? ";
			bushels_to_eat_ = 0;
			while (true)
			{
				std::cin >> input_string;
				if (!TryParseInt(input_string, bushels_to_eat_))
				{
					std::cout << "����������, ��� ����������. �������, ����������: ";
					continue;
				}
				if (bushels_to_eat_ > bushels_ + (acres_to_sell_ - acres_to_buy_) * price_)
				{
					std::cout << "����������, �� �� ����� ���� ����� ��������� � ������ ���������� ��������. �������, ����������:";
					continue;
				}
				break;
			}

			// bushels to sow
			std::cout << "\n������� ������� ����������� ������ �� �����? ";
			acres_to_sow_ = 0;
			while (true)
			{
				std::cin >> input_string;
				if (!TryParseInt(input_string, acres_to_sow_))
				{
					std::cout << "����������, ��� ����������. �������, ����������: ";
					continue;
				}
				if (acres_to_sow_ > acres_ + acres_to_buy_ - acres_to_sell_ ||
					acres_to_sow_ * 0.5 > (acres_to_sell_ - acres_to_buy_) * price_ + bushels_ - bushels_to_eat_)
				{
					std::cout << "����������, �� �� ����� ���� ����� ��������� � ������ ���������� ��������. �������, ����������:";
					continue;
				}
				break;
			}

			//confirm the order
			std::cout << "����������, ������ �����������, ��������� �� �� ���? ���� ���, �� �������� �����. (yes/no)";
			while (true)
			{
				std::cin >> input_string;
				if (input_string == "yes" || input_string == "no")
				{
					break;
				}
				std::cout << "����������, ��� ����������. �������, ����������: ";
			}

			if (input_string == "yes")
				break;
		}

	}
};



int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleOutputCP(1251);
	std::string input = "2147483647";
	int input_int = 0;

	Babylon babylon;

	while (true)
	{
		babylon.PrintYearReport();
		babylon.GetKingsOrders();
	}


	std::cout << "�������!\n";

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
