// laba3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;



struct FIO
{
	string name;
	string surname;
	string patronymic;
	FIO(string name, string surname, string patronymic)
	{
		this->name = name;
		this->surname = surname;
		this->patronymic = patronymic;
	}
	FIO()
	{
		name = surname = patronymic = "";
	}
	FIO(string data)
	{
		string temp = "";
		for (size_t i = 0; i < data.size(); i++)
		{
			if (data[i] == '_')
			{
				if (name.empty())
				{
					name = temp;
					temp = "";
				}
				else if (surname.empty())
				{
					surname = temp;
					temp = "";
				}				
			}
			else
			{
				temp += data[i];
			}
		}
		patronymic = temp;
	}
	bool operator==(const FIO& other)
	{
		return (this->name == other.name && this->surname == other.surname && this->patronymic == other.patronymic);
	}
};


struct Date
{
	int day = 0;
	int month = 0;
	int year = 0;
	Date()
	{
		day = 0; month = 0; year = 0;
	}
	Date(string data)
	{
		string temp = "";
		for (size_t i = 0; i < data.size(); i++)
		{
			if (data[i] == '/')
			{
				if (day == 0)
				{
					day = stoi(temp);
					temp = "";
				}
				else if (month == 0)
				{
					month = stoi(temp);
					temp = "";
				}
			}
			else
			{
				temp += data[i];
			}
		}
		year = stoi(temp);
	}
	bool operator==(const Date& other)
	{
		return (this->day == other.day && this->month == other.month && this->year == other.year);
	}
};

struct Student
{
	FIO fio;
	string major;
	string group_number;
	Date date_of_birthday;
	string phone_number;
	Student()
	{
		fio = FIO();
		major = group_number = phone_number = "";
		date_of_birthday = Date();
	}
	Student(string data)
	{
		string temp = "";
		for (size_t i = 0; i < data.size(); i++)
		{
			if (data[i] == ' ')
			{
				if (fio == FIO())
				{
					fio = FIO(temp);
					temp = "";
				}
				else if (major == "")
				{
					major = temp;
					temp = "";
				}
				else if (group_number == "")
				{
					group_number = temp;
					temp = "";
				}
				else if (date_of_birthday == Date())
				{
					date_of_birthday = Date(temp);
					temp = "";
				}
			}
			else
				temp += data[i];
			
		}
		phone_number = temp;
	}
	
};


ostream& operator<< (std::ostream& out, const FIO& fio)
{
	out << fio.name << " " << fio.surname << " " << fio.patronymic;
	return out;
}

ostream& operator<< (std::ostream& out, const Date& date)
{
	out << date.day << "." << date.month << "." << date.year;
	return out;
}

ostream& operator<< (std::ostream& out, const Student& student)
{
	out << student.fio << " " << student.major << " " << student.group_number << " " <<	student.date_of_birthday << " " << student.phone_number << endl;
	return out;
}


int main()
{
	fstream fout;
	fout.open("input.txt", ios::in);
	if (!fout.is_open())
	{
		cout << "Ошибка: не удалось открыть файл" << endl;
		return -1;
	}
	string temp;	
	getline(fout, temp);
	int record_count = stoi(temp);
	Student* students = new Student[record_count];
	for (size_t i = 0; i < (record_count - 1); i++)
	{
		getline(fout, temp);
		students[i] = Student(temp);
	}
	cout << students[2].date_of_birthday;
	fout.close();
	delete[] students;
	return 0;
}
