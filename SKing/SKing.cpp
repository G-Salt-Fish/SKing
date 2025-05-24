#include "SKing.h"
namespace sk
{
#pragma warning(disable:4834)

	random_device _rd;

	mt19937 _gen(_rd());

	Uint saved_seed = static_cast<Uint>(_rd());

	void set_random_seed(Uint seed)
	{
		_gen.seed(seed);
	}

	int random(int min, int max)
	{
		uniform_int_distribution<> dis(min, max);
		return dis(_gen);
	}

	double random(double min, double max)
	{
		uniform_real_distribution<> dis(1.0 * min, 1.0 * max);
		return dis(_gen);
	}

	Int operator+(const string& s, const Int& i)
	{
		return i + s;
	}

	ostream& operator<<(ostream& os, const Int& i)
	{
		os << i.value;
		return os;
	}

	int randomseed()
	{
		return saved_seed;
	}


	//Int


	


	string& Int::remove_leading_zeros(string& s) const
	{
		if (s.empty()) return s = "0";
		if (s[0] == '-')
		{
			s = s.substr(1);
			auto pos = s.find_first_not_of('0');
			auto final_ops = s.find_last_of('0');
			if (final_ops == s.size()-1 && pos == string::npos)
			{
				return s = "0";
			}
			s = '-' + s.substr((pos < string::npos)? pos : 0);
			return (s == "-") ? s = "0" : s;
		}
		size_t pos = s.find_first_not_of('0');
		if (pos == string::npos) 
		{
			return s = "0";
		}
		return s = s.substr(pos);
	}

	void Int::remove_leading_zeros(void)
	{
		string& s = this->value;

		if (s.empty())
		{
			s = "0";
			return;
		}
		if (s[0] == '-')
		{
			s = s.substr(1);
			auto pos = s.find_first_not_of('0');
			auto final_ops = s.find_last_of('0');
			if (final_ops == s.size() - 1 && pos == string::npos)
			{
				 s = "0";
				 return;
			}
			s = '-' + s.substr((pos < string::npos) ? pos : 0);
			//(s == "-") ? s = "0" : s;
			if (s == "-")
			{
				s = "0";
				return;
			}
		}
		size_t pos = s.find_first_not_of('0');
		if (pos == string::npos)
		{
			s = "0";
			return;
		}
		s = s.substr(pos);
		return;
	}

	//需先保证两个加数均为正数
	string Int::add(const string& s, const string& t) const
	{
		size_t ss = s.size(), ts = t.size();
		string other = (ss >= ts) ? t : s;//位数更小的
		bool carry{ false };//进位
		string r = (ss >= ts) ? s : t;//位数更大的
		string& result = r;
		result.insert(0, "0");
		other.insert(0, result.size() - other.size(), '0');
		#pragma warning(disable:6295)
		for (size_t i = result.size() - 1; i >= 0; i--)
		{
			if (result[i] + other[i] - 96 >= 10)
			{
				result[i] = (result[i] + other[i] - 96) % 10 + 48;
				if (carry)
				{
					result[i]++;
					carry = false;
				}
				carry = true;
			}
			else
			{
				if (carry + result[i] - 48 >= 10)
				{
					result[i] = '0';
				}
				else if (carry)
				{
					result[i]++;
					carry = false;
				}
				if (result[i] + other[i] - 96 >= 10)
				{
					result[i] = '0';
					carry = true;
				}
				else
				{
					result[i] = (result[i] + other[i] - 96) + 48;
				}
			}
			if (i == 0) break;
		}
		this->remove_leading_zeros(result);
		this->remove_leading_zeros(other);
		return result;
	}
	//确保删去前导零
	string Int::sub(const string& s, const string& t) const
	{
		bool exchange{ false };
		if (s.size() == t.size() and s < t)
		{
			exchange = true;
		}
		elif(s.size() < t.size())
		{
			exchange = true;
		}
		string result = exchange ? t : s;
		string other = exchange ? s : t;
		other.insert(0, result.size() - other.size(), '0');
		bool borrow{ false };//借位
		for (size_t i = result.size(); i >= 0; i--)
		{
			if (result[i] - other[i] < 0)
			{
				//result[i] = (result[i] + other[i] - 96) % 10 + 48;
				result[i] = result[i] + 10 - other[i] + '0';
				if (borrow)
				{
					result[i]--;
					borrow = false;
				}
				borrow = true;
			}
			else
			{
				if (result[i] - borrow - '0' < 0)
				{
					result[i] = '9';
				}
				elif (borrow)
				{
					result[i]--;
					borrow = false;
				}

				if (result[i] - other[i] < 0)
				{
					result[i] = '9';
					borrow = true;
				}
				else
				{
					result[i] = (result[i] - other[i]) + '0';
				}
			}



			if (i == 0) break;
		}
		this->remove_leading_zeros(result);
		if (exchange)
		{
			result.insert(0, "-");
		}
		return result;
	}

	Int::Int()
	{
	}

	Int::Int(string value)
	{
		remove_leading_zeros(value);
		this->value = value;
	}

	Int::Int(long long n)
	{
		this->value = to_string(n);
	}

	Int Int::operator+(const Int& other) const
	{
		string result{};
		string t{ value }, o{ other.value };
		if (this->is_negative_number() && other.is_negative_number())
		{
			result = add(t.erase(0,1), o.erase(0,1));
			result.insert(0, "-");
		}
		elif(this->is_negative_number())
		{
			result = sub(t.erase(0,1), o);
		}
		elif(other.is_negative_number())
		{
			result = sub(t, o.erase(0,1));
		}
		else
		{
			result = add(t, o);
		}

		return result;
	}

	Int Int::operator-(const Int& other) const
	{
		string result{};
		string t{ value }, o{ other.value };
		if (this->is_negative_number() && other.is_negative_number())
		{
			result = sub(t.erase(0, 1), o.erase(0,1));
		}
		elif(this->is_negative_number() && (!other.is_negative_number()))
		{
			result = add(t.erase(0, 1), o);
			result.insert(0, "-");
		}
		elif((!this->is_negative_number()) && other.is_negative_number())
		{

			result = add(t, o.erase(0, 1));

		}
		else
		{
			result = sub(t, o);
		}
		return result;
	}

	Int Int::operator-(void) const
	{
		Int r{ *this };
		if (r.value[0] == '-')
		{

			r.value.substr(0);
		}
		else
		{
			r.value.insert(0, "-");
		}
		return Int();
	}

	Int Int::operator=(const char* c) const
	{
		string s{ c };
		return s;
	}

	Int::operator string() const
	{
		return this->value;
	}

	string Int::get()
	{
		return value;
	}

	int Rand::seed(void)
	{
		return seed_;
	}

	void Rand::seed(int s)
	{
		seed_ = s;
		rd.seed(seed_);
	}

	int Rand::random(int min, int max)
	{
		uniform_int_distribution<int> dist(min, max);
		if (!if_real_random)
		{
			return dist(rd);
		}
		else
		{
			return dist(r_rd);
		}
	}

	Rand::Rand() : seed_(r_rd()), if_real_random(false)
	{
		rd.seed(seed_);
	}

	Rand::Rand(int s) : seed_(s), if_real_random(false)
	{
		rd.seed(seed_);
	}

	Rand::Rand(int s, bool b) : seed_(s), if_real_random(b)
	{
		rd.seed(seed_);
	}

	void Rand::real_random(bool b)
	{
		if_real_random = b;
	}

	bool Rand::real_random(void)
	{
		return if_real_random;
	}

}
