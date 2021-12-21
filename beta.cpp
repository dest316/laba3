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
				if (surname.empty())
				{
					surname = temp;
					temp = "";
				}
				else if (name.empty())
				{
					name = temp;
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
	bool operator>(const FIO& other)
	{
		if (this->surname == other.surname && this->name == other.name)
			return (this->patronymic > other.patronymic);
		else if (this->surname == other.surname)
			return (this->name > other.name);
		else return (this->surname > other.surname);
	}
	bool operator<(const FIO& other)
	{
		return (!(*this > other || *this == other));
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
	bool operator>(const Date& other)
	{
		if (this->year == other.year && this->month == other.month)
			return (this->day > other.day);
		else if (this->year == other.year)
			return (this->month > other.month);
		else return (this->year > other.year);
	}
	bool operator<(const Date& other)
	{
		return (!(*this > other || *this == other));
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
	bool operator>(const Student& other)
	{
		if (this->fio > other.fio)
			return true;
		else if (this->fio == other.fio)
			if (this->date_of_birthday > other.date_of_birthday)
				return true;
		return false;
	}
	bool operator<(const Student & other)
	{
		if (this->fio < other.fio)
			return true;
		else if (this->fio == other.fio)
			if (this->date_of_birthday < other.date_of_birthday)
				return true;
		return false;
	}
	bool operator==(const Student& other)
	{
		return (!(*this > other && *this < other));
	}
	
};


void insertion_sort(Student* stud_array, int length)
{
	for (int i = 1; i < length; i++)
		for (int j = i; j > 0 && stud_array[j - 1] > stud_array[j]; j--) // пока j>0 и элемент j-1 > j, stud_array-массив int
			swap(stud_array[j - 1], stud_array[j]);
}

int median_of_three_partition(Student* stud_array, int p, int r)
{
	Student x = stud_array[p], y = stud_array[(r - p) / 2 + p], z = stud_array[r - 1];
	int i = p - 1, j = r;
	if (y > x && y < z || y > z && y < x)
	{
		x = y;
	}
	else if (z > x && z < y || z > y && z < x)
	{
		x = z;
	}
	while (true)
	{
		do
		{
			j--;
		} while (stud_array[j] > x);
		do
		{
			i++;
		} while (stud_array[i] < x);
		if (i < j)
		{
			swap(stud_array[i], stud_array[j]);
		}
		else return j + 1;
	}

}

void quick_sort(Student* stud_array, int start, int end)
{
	int q;
	if (end - start < 2)
	{
		return;
	}
	q = median_of_three_partition(stud_array, start, end);
	quick_sort(stud_array, start, q);
	quick_sort(stud_array, q, end);
}


ostream& operator<< (std::ostream& out, const FIO& fio)
{
	out << fio.surname << " " << fio.name << " " << fio.patronymic;
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
	for (size_t i = 0; i < (record_count); i++)
	{
		getline(fout, temp);
		students[i] = Student(temp);
	}
	fout.close();
	//insertion_sort(students, record_count);
	quick_sort(students, 0, record_count);
	for (size_t i = 0; i < record_count; i++)
	{
		cout << students[i];
	}
	delete[] students;
	return 0;
}
