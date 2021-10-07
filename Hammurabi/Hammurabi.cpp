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
	int harvested_acres_;
	int harvest_from_acre;

	double yearly_starved_;
	void GeneratePrice()
	{
		std::mt19937 gen(time(0));
		std::uniform_int_distribution<> uid(17, 26);
		price_ = uid(gen);
	}
public:

	Babylon()
	{
		population_ = 100;
		bushels_ = 2800;
		acres_ = 1000;
		year_ = 1;

		harvest_ = 0;
		harvested_acres_ = 1;
		starved_people_ = 0;
		new_people_ = 0;
		bushels_destroyed_ = 0;
		harvest_from_acre = 0;
		plague_ = false;
		yearly_starved_ = 0;
		GeneratePrice();
	}

	bool CheckLoss() {
		double a = (double)starved_people_ / (starved_people_ + (plague_ ? 2 : 1) * population_ - new_people_);
		yearly_starved_ += a;
		if (population_ == 0 || a >= 0.45)
		{
			std::cout << "Вы уничтожили город. До свидания!";
			return true;
		}
		return false;
	}

	bool CheckLastYear()
	{
		if (year_ == 11)
		{
			yearly_starved_ /= 10;
			int acres_per_human = population_ / acres_;
			if (yearly_starved_ > 0.33 && acres_per_human < 7)
			{
				std::cout << "\nИз-за вашей некомпетентности в управлении, народ устроил бунт, и изгнал вас их города.Теперь вы вынуждены влачить жалкое существование в изгнании";
			}
			else if (yearly_starved_ > 0.1 && acres_per_human < 9)
			{
				std::cout << "\nВы правили железной рукой, подобно Нерону и Ивану Грозному. Народ вздохнул с облегчением, и никто больше не желает видеть вас правителем";
			}
			else if (yearly_starved_ > 0.03 && acres_per_human < 10)
			{
				std::cout << "\nВы справились вполне неплохо, у вас, конечно, есть недоброжелатели, но многие хотели бы увидеть вас во главе города снова";
			}
			else
			{
				std::cout << "\nФантастика! Карл Великий, Дизраэли и Джефферсон вместе не справились бы лучше";
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
		harvest_from_acre = hid(gen);
		int max_harvested_acres = (population_ - starved_people_) * 10;
		if (max_harvested_acres > acres_to_sow_)
		{
			harvest_ = acres_to_sow_ * harvest_from_acre;
			harvested_acres_ = acres_to_sow_;
		}
		else
		{
			harvest_ = max_harvested_acres * harvest_from_acre;
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
		int newcomers = starved_people_ / 2 + (5 - harvest_from_acre) * bushels_ / 600 + 1;
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
		GeneratePrice();
		year_++;
	}

	void PrintYearReport()
	{
		std::cout << "Мой повелитель, соизволь поведать тебе:";
		std::cout << "\n\tв году " << year_ << " твоего высочайшего правления";
		if (starved_people_ != 0)
		{
			std::cout << "\n\t" << starved_people_ << " человек умерли из-за голода;";
		}
		if (new_people_ != 0)
		{
			std::cout << "\n\t" << new_people_ << " человек прибыли в наш город;";
		}
		if (plague_)
		{
			std::cout << "\n\t" << "Чума уничтожила половину населения;";
		}
		else
		{
			std::cout << "\n\t" << "Чума обошла наш город стороной;";
		}
		std::cout << "\n\tНаселение города составляет " << population_ << " человек;";
		std::cout << "\n\tМы собрали " << harvest_ << " бушелей пшеницы, по " << harvest_from_acre << " бушеля с акра;";
		std::cout << "\n\tКрысы истребили " << bushels_destroyed_ << " бушелей пшеницы, оставив " << bushels_ << " бушеля в амбарах; ";
		std::cout << "\n\tГород сейчас занимает " << acres_ << " акров;";
		std::cout << "\n\tЦена одного акра составляет " << price_ << " бушелей.";
	}

	void GetKingsOrders()
	{
		std::string input_string;
		while (true)
		{
			// acres to buy
			std::cout << "\nСколько акров земли повелеваешь купить? ";
			acres_to_buy_ = 0;
			while (true)
			{
				std::cin >> input_string;
				if (!TryParseInt(input_string, acres_to_buy_))
				{
					std::cout << "Повелитель, это невозможно. Повтори, пожалуйста: ";
					continue;
				}
				if (acres_to_buy_ != 0 && acres_to_buy_ * price_ > bushels_)
				{
					std::cout << "Повелитель, мы не можем себе этого позволить. Повтори, пожалуйста:";
					continue;
				}
				break;
			}

			// acres to sell
			std::cout << "\nСколько акров земли повелеваешь продать? ";
			acres_to_sell_ = 0;
			while (true)
			{
				std::cin >> input_string;
				if (!TryParseInt(input_string, acres_to_sell_))
				{
					std::cout << "Повелитель, это невозможно. Повтори, пожалуйста: ";
					continue;
				}
				if (acres_to_sell_ != 0 && acres_to_sell_ > acres_to_buy_ + acres_)
				{
					std::cout << "Повелитель, мы не можем себе этого позволить с учетом предыдущих действий. Повтори, пожалуйста:";
					continue;
				}
				break;
			}

			// bushels to eat
			std::cout << "\nСколько бушелей повелеваешь отдать гражданам для еды? ";
			bushels_to_eat_ = 0;
			while (true)
			{
				std::cin >> input_string;
				if (!TryParseInt(input_string, bushels_to_eat_))
				{
					std::cout << "Повелитель, это невозможно. Повтори, пожалуйста: ";
					continue;
				}
				if (bushels_to_eat_ != 0 && bushels_to_eat_ > bushels_ + (acres_to_sell_ - acres_to_buy_) * price_)
				{
					std::cout << "Повелитель, мы не можем себе этого позволить с учетом предыдущих действий. Повтори, пожалуйста:";
					continue;
				}
				break;
			}

			// bushels to sow
			std::cout << "\nСколько акров земли повелеваешь засеять? ";
			acres_to_sow_ = 0;
			while (true)
			{
				std::cin >> input_string;
				if (!TryParseInt(input_string, acres_to_sow_))
				{
					std::cout << "Повелитель, это невозможно. Повтори, пожалуйста: ";
					continue;
				}
				if (acres_to_sow_ != 0 && (acres_to_sow_ > acres_ + acres_to_buy_ - acres_to_sell_ ||
					acres_to_sow_ * 0.5 > (acres_to_sell_ - acres_to_buy_) * price_ + bushels_ - bushels_to_eat_))
				{
					std::cout << "Повелитель, мы не можем себе этого позволить с учетом предыдущих действий. Повтори, пожалуйста:";
					continue;
				}
				break;
			}

			//confirm the order
			std::cout << "Повелитель, приказ сформирован, подпишешь ли ты его? Если нет, то создадим новый. (y/n)";
			while (true)
			{
				std::cin >> input_string;
				if (input_string == "y" || input_string == "n")
				{
					break;
				}
				std::cout << "Повелитель, это невозможно. Повтори, пожалуйста: ";
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
	std::string input = "2147483647";
	int input_int = 0;

	Babylon babylon;

	while (true)
	{
		babylon.PrintYearReport();
		if (babylon.CheckLastYear())
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
