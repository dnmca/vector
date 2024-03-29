// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <iostream>
#include <vector>
#include <string> //! OF: MSVC, наприклад, без нього не вміє << std::string{}.
#include "my_vector.h"

using namespace std;

struct President
{
	std::string name{"None"};
	std::string country{"None"};
	int year = 0;

	President() = default;

	President(std::string p_name, std::string p_country, int p_year)
			: name(std::move(p_name)), country(std::move(p_country)), year(p_year)
	{
		std::cout << "I am being constructed.\n";
	}
	President(President&& other)
			: name(std::move(other.name)), country(std::move(other.country)), year(other.year)
	{
		//! OF: сподіваюся, Ви пам'ятаєте, що такий move constructor має сенс лише для виводу --
		//! OF: по замовчуванню було б так само.
		//! OF: те ж стосується конструктора копіювання вище!
		std::cout << "I am being moved.\n";
	}
	President& operator=(const President& other) = default;
};

int main() {

	my_vector<int> vec {1,2,3,4};
	my_vector<int> vec1(vec.end(), vec.end());
    for (auto x : vec){
        cout << x << '+';
    }
    cout << endl;
    for (auto x : vec1){
        cout << x << '+';
    }

    cout << "Here we go"<<endl;
    my_vector<int> v{1,2,3};
//    cout << *v.rcend() << endl;
    cout << *v.rbegin() << endl;


	my_vector<President> elections;
	std::cout << "emplace_back:\n";
	elections.emplace_back("Nelson Mandela", "South Africa", 1994);
	my_vector<President> reElections;
	std::cout << "\npush_back:\n";
	reElections.push_back(President("Franklin Delano Roosevelt", "the USA", 1936));

	std::cout << "\nContents:\n";
	for (President const& president: elections) {
		std::cout << president.name << " was elected president of "
				  << president.country << " in " << president.year << ".\n";
	}
	for (President const& president: reElections) {
		std::cout << president.name << " was re-elected president of "
				  << president.country << " in " << president.year << ".\n";
	}
	return 0;
}