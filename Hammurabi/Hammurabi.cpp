// Hammurabi.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <iostream>
#include <cctype>
#include <Windows.h>
#include <fstream>
#include <cstdlib>
#include <random>
#include <string>
#include <format>
#include <regex>


bool TryParsePositiveInt(const std::string& in_value, int& out_value)
{
	// check if string contains any non-digit symbols
	if (!std::all_of(in_value.begin(), in_value.end(), isdigit))
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

bool TryParsePositiveDouble(const std::string& in_value, double& out_value)
{
	std::regex double_expr("(0|([1-9][0-9]*))(\\,[0-9]+)?$");
	if (!std::regex_match(in_value, double_expr))
	{
		return false;
	}

	try
	{
		out_value = std::stod(in_value);
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
	int harvested_acres_;
	int harvest_from_acre_;

	double yearly_starved_;

	int GeneratePrice()
	{
		std::mt19937 gen(time(0));
		std::uniform_int_distribution<> uid(17, 26);
		return uid(gen);
	}

	std::string ToString()
	{
		return std::to_string(population_) + "\n" + std::to_string(bushels_) + "\n" + std::to_string(acres_) + "\n" +
			std::to_string(year_) + "\n" + std::to_string(harvest_) + "\n" + std::to_string(starved_people_) + "\n" +
			std::to_string(new_people_) + "\n" + std::to_string(bushels_destroyed_) + "\n" + std::to_string(price_) + "\n" +
			std::to_string(acres_to_buy_) + "\n" + std::to_string(acres_to_sell_) + "\n" + std::to_string(bushels_to_eat_) + "\n" +
			std::to_string(acres_to_sow_) + "\n" + std::to_string(harvested_acres_) + "\n" + std::to_string(harvest_from_acre_) + "\n" +
			std::to_string(yearly_starved_) + "\n" + std::to_string(plague_);
	}
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
		price_ = GeneratePrice();
		plague_ = false;

		acres_to_buy_ = 0;
		acres_to_sell_ = 0;
		bushels_to_eat_ = 0;
		acres_to_sow_ = 0;
		harvested_acres_ = 1;
		harvest_from_acre_ = 0;
		yearly_starved_ = 0;
	}

	bool SaveState()
	{
		std::string input_string;

		//confirm the order
		std::cout << "\n����������, ������ �� �� ���������� � ���������? (y/n)";
		while (true)
		{
			std::cin >> input_string;
			if (input_string == "y" || input_string == "n")
			{
				break;
			}
			std::cout << "����������, �� ���� ����������. �������, ����������: ";
		}

		if (input_string == "y")
		{
			std::ofstream save_file("savefile.txt");
			save_file << ToString();
			save_file.close();
			return true;
		}

		return false;
	}

	void LoadState()
	{
		std::string input_string;
		std::cout << "��������� ����������� ����� ����? (y/n)";
		while (true)
		{
			std::cin >> input_string;
			if (input_string == "y" || input_string == "n")
			{
				break;
			}
			std::cout << "�������, ����������: ";
		}
		if (input_string == "n")
		{
			return;
		}

		std::ifstream save_file("savefile.txt");
		if (!save_file)
		{
			save_file.close();
			std::cout << "������ � ����������� ���� �� �������. �������� ����� ����.";
			return;
		}

		std::string tmp;
		int tmp_int_arr[15];

		double tmp_starved;
		bool tmp_plague;

		// check input file
		for (int i = 0; i < 15; i++)
		{
			std::getline(save_file, tmp);
			if (tmp.empty())
			{
				std::cout << "���� ���������� ���������. �������� ����� ����.";
				return;
			}
			if (!TryParsePositiveInt(tmp, tmp_int_arr[i]))
			{
				std::cout << "���� ���������� ���������. �������� ����� ����.";
				return;
			}
		}
		std::getline(save_file, tmp);
		if (!TryParsePositiveDouble(tmp, tmp_starved))
		{
			std::cout << "���� ���������� ���������. �������� ����� ����.";
			return;
		}
		std::getline(save_file, tmp);
		if (tmp != "0" && tmp != "1")
		{
			std::cout << "���� ���������� ���������. �������� ����� ����.";
			return;
		}
		tmp_plague = tmp == "1";

		// set savefile data

		population_ = tmp_int_arr[0];
		bushels_ = tmp_int_arr[1];
		acres_ = tmp_int_arr[2];
		year_ = tmp_int_arr[3];
		harvest_ = tmp_int_arr[4];
		starved_people_ = tmp_int_arr[5];
		new_people_ = tmp_int_arr[6];
		bushels_destroyed_ = tmp_int_arr[7];
		price_ = tmp_int_arr[8];
		acres_to_buy_ = tmp_int_arr[9];
		acres_to_sell_ = tmp_int_arr[10];
		bushels_to_eat_ = tmp_int_arr[11];
		acres_to_sow_ = tmp_int_arr[12];
		harvested_acres_ = tmp_int_arr[13];
		harvest_from_acre_ = tmp_int_arr[14];
		yearly_starved_ = tmp_starved;
		plague_ = tmp_plague;
		save_file.close();
	}

	bool CheckLoss() {
		double a = (double)starved_people_ / (starved_people_ + (plague_ ? 2 : 1) * population_ - new_people_);
		yearly_starved_ += a;
		if (population_ == 0 || a >= 0.45)
		{
			std::cout << "�� ���������� �����. �� ��������!";
			return true;
		}
		return false;
	}

	bool CheckLastYear()
	{
		if (year_ >= 11)
		{
			yearly_starved_ /= 10;
			int acres_per_human = population_ / acres_;
			if (yearly_starved_ > 0.33 && acres_per_human < 7)
			{
				std::cout << "\n��-�� ����� ���������������� � ����������, ����� ������� ����, � ������ ��� �� ������.������ �� ��������� ������� ������ ������������� � ��������";
			}
			else if (yearly_starved_ > 0.1 && acres_per_human < 9)
			{
				std::cout << "\n�� ������� �������� �����, ������� ������ � ����� ��������. ����� �������� � �����������, � ����� ������ �� ������ ������ ��� ����������";
			}
			else if (yearly_starved_ > 0.03 && acres_per_human < 10)
			{
				std::cout << "\n�� ���������� ������ �������, � ���, �������, ���� ���������������, �� ������ ������ �� ������� ��� �� ����� ������ �����";
			}
			else
			{
				std::cout << "\n����������! ���� �������, �������� � ���������� ������ �� ���������� �� �����";
			}
			return true;
		}
		return false;
	}

	void UpdateCityState()
	{

		// bushels volume after king's orders
		bushels_ = bushels_ + (acres_to_sell_ - acres_to_buy_) * price_ - bushels_to_eat_ - acres_to_sow_ * 0.5;

		// new acreage
		acres_ = acres_ + acres_to_buy_ - acres_to_sell_;

		// starved people
		if (bushels_to_eat_ / 20 < population_)
		{
			starved_people_ = population_ - bushels_to_eat_ / 20;
			population_ -= starved_people_;
		}

		// harvest by alive people
		std::mt19937 gen(time(0));
		std::uniform_int_distribution<> hid(1, 6);
		harvest_from_acre_ = hid(gen);
		int max_harvested_acres = (population_ - starved_people_) * 10;
		if (max_harvested_acres > acres_to_sow_)
		{
			harvest_ = acres_to_sow_ * harvest_from_acre_;
			harvested_acres_ = acres_to_sow_;
		}
		else
		{
			harvest_ = max_harvested_acres * harvest_from_acre_;
			harvested_acres_ = max_harvested_acres;
		}
		bushels_ += harvest_;

		// rats
		std::uniform_real_distribution<> rid(0.0, 0.07);
		bushels_destroyed_ = rid(gen) * bushels_;
		bushels_ -= bushels_destroyed_;

		// plague
		std::uniform_int_distribution<> pid(1, 100);
		if (pid(gen) <= 15)
		{
			plague_ = true;
			population_ /= 2;
		}
		else
		{
			plague_ = false;
		}

		// newcomers
		int newcomers = starved_people_ / 2 + (5 - harvest_from_acre_) * bushels_ / 600 + 1;
		if (newcomers <= 0)
		{
			new_people_ = 0;
		}
		else if (newcomers >= 50)
		{
			new_people_ = 50;
		}
		else
		{
			new_people_ = newcomers;
		}
		population_ += new_people_;

		// next year 
		price_ = GeneratePrice();
		year_++;
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
		std::cout << "\n\t�� ������� " << harvest_ << " ������� �������, �� " << harvest_from_acre_ << " ������ � ����;";
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
				if (!TryParsePositiveInt(input_string, acres_to_buy_))
				{
					std::cout << "����������, ��� ����������. �������, ����������: ";
					continue;
				}
				if (acres_to_buy_ != 0 && acres_to_buy_ * price_ > bushels_)
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
				if (!TryParsePositiveInt(input_string, acres_to_sell_))
				{
					std::cout << "����������, ��� ����������. �������, ����������: ";
					continue;
				}
				if (acres_to_sell_ != 0 && acres_to_sell_ > acres_to_buy_ + acres_)
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
				if (!TryParsePositiveInt(input_string, bushels_to_eat_))
				{
					std::cout << "����������, ��� ����������. �������, ����������: ";
					continue;
				}
				if (bushels_to_eat_ != 0 && bushels_to_eat_ > bushels_ + (acres_to_sell_ - acres_to_buy_) * price_)
				{
					std::cout << "����������, �� �� ����� ���� ����� ��������� � ������ ���������� ��������. �������, ����������:";
					continue;
				}
				break;
			}

			// bushels to sow
			std::cout << "\n������� ����� ����� ����������� �������? ";
			acres_to_sow_ = 0;
			while (true)
			{
				std::cin >> input_string;
				if (!TryParsePositiveInt(input_string, acres_to_sow_))
				{
					std::cout << "����������, ��� ����������. �������, ����������: ";
					continue;
				}
				if (acres_to_sow_ != 0 && (acres_to_sow_ > acres_ + acres_to_buy_ - acres_to_sell_ ||
					acres_to_sow_ * 0.5 > (acres_to_sell_ - acres_to_buy_) * price_ + bushels_ - bushels_to_eat_))
				{
					std::cout << "����������, �� �� ����� ���� ����� ��������� � ������ ���������� ��������. �������, ����������:";
					continue;
				}
				break;
			}

			//confirm the order
			std::cout << "����������, ������ �����������, ��������� �� �� ���? ���� ���, �� �������� �����. (y/n)";
			while (true)
			{
				std::cin >> input_string;
				if (input_string == "y" || input_string == "n")
				{
					break;
				}
				std::cout << "����������, �� ���� ����������. �������, ����������: ";
			}

			if (input_string == "y")
				break;
		}
	}
};


int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleOutputCP(1251); 
	Babylon babylon;
	babylon.LoadState();

	while (true)
	{
		babylon.PrintYearReport();
		if (babylon.CheckLastYear())
		{
			break;
		}
		if (babylon.SaveState())
		{
			break;
		}
		babylon.GetKingsOrders();
		babylon.UpdateCityState();
		if (babylon.CheckLoss())
		{
			break;
		}
	}
}
