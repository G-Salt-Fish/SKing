#pragma once
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <thread>
#include <random>
#include <ctime>
#include <any>



namespace sk
{
	using namespace std;

	inline void __pause__() 
	{
	#ifdef __linux__
		cout << "请按任意键继续. . .";
		cin.get();
	#elif __APPLE__ 
		cout << "请按任意键继续. . .";
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	#endif
	}
	#ifdef _WIN32
		#define pause system("pause")
	#elif __linux__ 
		#define pause __pause__()
	#elif __APPLE__
		#define pause __pause__()
	#endif

	#define cls printf("\033[2J\033[H");

	#define elif else if

	template<typename T>
	constexpr auto sleep(T t) { return this_thread::sleep_for(chrono::milliseconds(t)); }

	using Uint = unsigned int;

	class Rand
	{
	private:
		int seed_;
		mt19937 rd;
		random_device r_rd;
		bool if_real_random;
	public:
		int seed(void);
		void seed(int);
		int random(int min, int max);
		Rand();
		Rand(int);
		Rand(int, bool);
		void real_random(bool);
		bool real_random(void);
	};

	class Int
	{
	private:
			string value;
			string& remove_leading_zeros(string& s) const;
			void remove_leading_zeros(void);
			string add(const string& s, const string& t) const;
			string sub(const string& s, const string& t) const;
			string simplex(const string& s, const char c) const;
			inline bool is_negative_number(const string& s) const { return s[0] == '-' ? true : false; }
			inline bool is_negative_number() const { return value[0] == '-' ? true : false; }

	public:
		Int();
		explicit Int(string);
		Int(long long);

		Int operator+(const Int& other) const;
		Int operator-(const Int& other) const;
		Int operator-(void) const;
		Int operator=(const char*) const;
		Int operator*(const Int& other) const;
		bool operator>(const Int& other) const;
		bool operator>=(const Int& other) const;
		bool operator<(const Int& other) const;
		bool operator<=(const Int& other) const;
		bool operator==(const Int& other) const;


		operator string() const;
		
		friend ostream& operator<<(ostream&, const Int&);
		friend istream& operator>>(istream&, Int&);

		string get(void);
	};

	int randomseed();
	//

}

