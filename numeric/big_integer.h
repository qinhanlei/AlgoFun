#ifndef _ALGOFUN_BIG_INTEGER_H
#define _ALGOFUN_BIG_INTEGER_H

#include <string>


class big_integer {
public:
	// constructors, use assignment operator indrect
	big_integer();
	big_integer(int);
	big_integer(long long);
	big_integer(const char*); //TODO: unnecessary, string is well enough
	big_integer(const std::string&);
	big_integer(const big_integer&);
	
	// assignment operator overload
	big_integer& operator=(int);
	big_integer& operator=(long long);
	big_integer& operator=(const char*); //TODO: use string instead
	big_integer& operator=(const std::string&);
	big_integer& operator=(const big_integer&);
	
	// logic operator overload
	bool operator<(const big_integer&) const;
	bool operator>(const big_integer&) const;
	bool operator==(const big_integer&) const;
	bool operator!=(const big_integer&) const;
	bool operator<=(const big_integer&) const;
	bool operator>=(const big_integer&) const;
	
	//HACK: all calculate need more boundary judge
	// arithmetic operator overload
	big_integer operator+(const big_integer&) const;
	big_integer operator-(const big_integer&) const;
	big_integer operator*(const big_integer&) const;
	big_integer operator/(const big_integer&) const; //TODO: improve this
	big_integer operator%(const big_integer&) const;
	// exponentiate
	big_integer operator^(big_integer) const;
	
	big_integer& operator+=(const big_integer&);
	big_integer& operator-=(const big_integer&);
	big_integer& operator*=(const big_integer&);
	big_integer& operator/=(const big_integer&);
	big_integer& operator%=(const big_integer&);
	
	big_integer& operator++();
	big_integer operator++(int);
	big_integer& operator--();
	big_integer operator--(int);
	// negative
	big_integer operator-() const;
	
	void print();
	// limit digits of one biginteger
	static int limit_digits() {
		return ELEMENT_DIGIT * MAX_ELEMENT_NUM;
	}
	
	friend std::ostream& operator<<(std::ostream&, const big_integer&);
	friend std::ostream& operator>>(std::ostream&, big_integer&);
	
private:
	// add someone ignore sign
	big_integer Add(const big_integer&) const;
	// minus someone ignore sign
	big_integer Minus(const big_integer&) const;
	
	// single element(here is data_[i]) stored digits.
	// as a 32-bit int, to multiplication must less than or equal 4.
	static const int ELEMENT_DIGIT = 4;
	// maximum quantity of a big integer
	static const int MAX_ELEMENT_NUM = 10000; //TODO: not flexible enough
	// maximum value of individual element
	static const int MAX_ELEMENT_VALUE;
	
	// first valid number index
	int first_index_;
	// signed
	bool is_negative_;
	
	// substructure, all number in serise as a big integer.
	// the lowest digit is at data_[MAX_ELEMENT_NUM - 1]
	int data_[MAX_ELEMENT_NUM]; //TODO: use STL deque may more convenient.
};

std::ostream& operator<<(std::ostream&, const big_integer&);
std::istream& operator>>(std::istream&, big_integer&);


#endif //_ALGOFUN_BIG_INTEGER_H
