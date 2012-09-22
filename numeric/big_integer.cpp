#include "big_integer.h"

#include <cmath>
#include <cstdio>
#include <cstring>
#include <cassert>

#include <iomanip>
#include <iostream>
#include <algorithm>

const int big_integer::MAX_ELEMENT_VALUE = (int)pow(10.0, ELEMENT_DIGIT);

big_integer::big_integer()
{
	*this = 0;
}

big_integer::big_integer(int a)
{
	*this = a;
}

big_integer::big_integer(long long a)
{
	*this = a;
}

big_integer::big_integer(const char* s)
{
	*this = s;
}

big_integer::big_integer(const std::string& s)
{
	*this = s;
}

big_integer::big_integer(const big_integer& a)
{
	if (this != &a) {
		*this = a;
	}
}

big_integer& big_integer::operator=(int a)
{
	*this = (long long)a;
	return *this;
}

big_integer& big_integer::operator=(long long a)
{
	memset(data_, 0, sizeof(data_));
	if (a < 0) {
		is_negative_ = true;
		a *= -1;
	} else {
		is_negative_ = false;
	}
	first_index_ = MAX_ELEMENT_NUM;
	do {
		data_[--first_index_] = a % MAX_ELEMENT_VALUE;
		a /= MAX_ELEMENT_VALUE;
	} while (a);
	return *this;
}

big_integer& big_integer::operator=(const char* s)
{
	if (s == NULL) return *this;
	int len = strlen(s), ten = 1, i = 0, k = 0;
	if (s[0] == '+' || s[0] == '-') ++i;
	for (; i < len; ++i)
		if (s[i] < '0' || s[i] > '9') break;
	if (i != len) return *this;
	// check passed.
	first_index_ = MAX_ELEMENT_NUM - 1;
	memset(data_, 0, sizeof(data_));
	if (s[0] == '+' || s[0] == '-') k = 1;
	for (int i = len - 1; i >= k; --i) {
		data_[first_index_] += (s[i] - '0') * ten;
		ten *= 10;
		if (ten >= MAX_ELEMENT_VALUE) {
			--first_index_;
			ten = 1;
		}
	}
	if (s[0] == '-')
		is_negative_ = true;
	else
		is_negative_ = false;
	// skip precursor zero
	for (; first_index_ < MAX_ELEMENT_NUM - 1; ++first_index_)
		if (data_[first_index_] != 0) break;
	return *this;
}

big_integer& big_integer::operator=(const std::string& a)
{
	*this = a.c_str();
	return *this;
}

big_integer& big_integer::operator=(const big_integer& a)
{
	is_negative_ = a.is_negative_;
	first_index_ = a.first_index_;
	memcpy(data_, a.data_, sizeof(data_));
	return *this;
}

bool big_integer::operator>(const big_integer& a) const
{
	if (*this < a || *this == a) return false;
	return true;
}

bool big_integer::operator<(const big_integer& a) const
{
	if (is_negative_ && !a.is_negative_) return true;
	if (!is_negative_ && a.is_negative_) return false;
	if (first_index_ > a.first_index_) return true;
	if (first_index_ < a.first_index_) return false;
	for (int i = first_index_; i < MAX_ELEMENT_NUM; ++i) {
		if (data_[i] < a.data_[i]) 
			return true;
		else if (data_[i] > a.data_[i]) 
			return false;
	}
	return false;
}

bool big_integer::operator==(const big_integer& a) const
{
	if (is_negative_ != a.is_negative_) return false;
	if (first_index_ != a.first_index_) return false;
	for (int i = first_index_; i < MAX_ELEMENT_NUM; ++i)
		if (data_[i] != a.data_[i]) return false;
	return true;
}

bool big_integer::operator!=(const big_integer& a) const
{
	return !(*this == a);
}


bool big_integer::operator<=(const big_integer& a) const
{
	return !(*this > a);
}

bool big_integer::operator>=(const big_integer& a) const
{
	return !(*this < a);
}

big_integer big_integer::operator+(const big_integer& a) const
{
	big_integer ret;
	if (is_negative_ && !a.is_negative_) {
		ret = a.Minus(*this);
		ret.is_negative_ = (a < *this);
	} else if (!is_negative_ && a.is_negative_) {
		ret = Minus(a);
		ret.is_negative_ = (*this < a);
	} else {
		ret = Add(a);
		ret.is_negative_ = is_negative_;
	}
	return ret;
}

big_integer big_integer::operator-(const big_integer& a) const
{
	big_integer ret;
	if (is_negative_ != a.is_negative_) {
		ret = Add(a);
		ret.is_negative_ = is_negative_;
	} else {
		ret = Minus(a);
		ret.is_negative_ = (*this < a);
	}
	return ret;
}

big_integer big_integer::operator*(const big_integer& a) const
{
	if (a == 0 || *this == 0) return 0;
	int i = 0, j = 0, k = MAX_ELEMENT_NUM - 1;
	big_integer ret;
	for (i = MAX_ELEMENT_NUM - 1; i >= first_index_; --i) {
		for (j = MAX_ELEMENT_NUM - 1; j >= a.first_index_; --j) {
			k = i + j - MAX_ELEMENT_NUM + 1;
			ret.data_[k] += data_[i] * a.data_[j];
			if (ret.data_[k] >= MAX_ELEMENT_VALUE) {
				ret.data_[k - 1] += (ret.data_[k] / MAX_ELEMENT_VALUE);
				ret.data_[k] %= MAX_ELEMENT_VALUE;
			}
		}
	}
	if (ret.data_[k - 1] != 0) --k;
	ret.first_index_ = k;
	ret.is_negative_ = is_negative_ ^ a.is_negative_;
	return ret;
}

big_integer big_integer::operator/(const big_integer& a) const
{
	if (a == 0) {
		assert(false && "divide by zero!");
		abort();
		//UNDONE: may throw exception.
	}
	//HACK: may very slow...
	big_integer ret;
	big_integer tmp(*this);
	while (tmp >= a) {
		tmp -= a;
		ret++;
	}
	ret.is_negative_ = is_negative_ ^ a.is_negative_;
	return ret;
}

big_integer big_integer::operator%(const big_integer& a) const
{
	return *this - (*this / a) * a;
}

big_integer big_integer::operator^(big_integer a) const
{
	big_integer tmp = *this;
	big_integer ret = 1;
	// binary method
	while (a != 0) {
		if (a % 2 == 1)
			ret = ret * tmp;
		a /= 2;
		tmp = tmp * tmp;
	}
	if (is_negative_ && a != 0) {
		ret.is_negative_ = (a % 2 == 1);
	}
	return ret;
}

big_integer& big_integer::operator+=(const big_integer& a)
{
	return *this = *this + a;
}

big_integer& big_integer::operator-=(const big_integer& a)
{
	return *this = *this - a;
}

big_integer& big_integer::operator*=(const big_integer& a)
{
	return *this = *this * a;
}

big_integer& big_integer::operator/=(const big_integer& a)
{
	return *this = *this / a;
}

big_integer& big_integer::operator%=(const big_integer& a)
{
	return *this = *this % a;
}

big_integer& big_integer::operator++()
{
	return *this = *this + 1;
}

big_integer big_integer::operator++(int)
{
	big_integer tmp(*this);
	*this = *this + 1;
	return tmp;
}

big_integer& big_integer::operator--()
{
	return *this = *this - 1;
}

big_integer big_integer::operator--(int)
{
	big_integer tmp(*this);
	*this = *this - 1;
	return tmp;
}

void big_integer::print()
{
	// set output format
	char str[6] = "%0xd";
	// set x which in above str.
	str[2] = ELEMENT_DIGIT + '0';
	// negative integer
	if (is_negative_) printf("-");
	printf("%d", data_[first_index_]);
	for (int i = first_index_ + 1; i < MAX_ELEMENT_NUM; ++i)
		printf(str, data_[i]);
	//puts("");
}

big_integer big_integer::Add(const big_integer& a) const
{
	int i = 0, low = std::min(first_index_, a.first_index_);
	big_integer sum;
	for (i = MAX_ELEMENT_NUM - 1; i >= low; --i) {
		sum.data_[i] += data_[i] + a.data_[i];
		if (sum.data_[i] >= MAX_ELEMENT_VALUE) {
			sum.data_[i - 1] = 1;
			sum.data_[i] -= MAX_ELEMENT_VALUE;
		}
	}
	if (sum.data_[i] == 0)
		sum.first_index_ = low;
	else 
		sum.first_index_ = low - 1;
	return sum;
}

big_integer big_integer::Minus(const big_integer& a) const
{
	int i;
	big_integer ret;
	// bigger of absolute value 
	const big_integer& bigger = (first_index_ < a.first_index_ || 
		data_[first_index_] > a.data_[a.first_index_]) ? *this : a;
	const big_integer& smaller = (&bigger == this) ? a : *this;
	for (i = MAX_ELEMENT_NUM - 1; i >= bigger.first_index_; --i) {
		ret.data_[i] += bigger.data_[i] - smaller.data_[i];
		// borrow
		if (ret.data_[i] < 0) {
			ret.data_[i - 1] = -1;
			ret.data_[i] += MAX_ELEMENT_VALUE;
		}
	}
	// skip precursor zero, set right first index
	for (; i < MAX_ELEMENT_NUM - 1; ++i)
		if (ret.data_[i] != 0) break;
	ret.first_index_ = i;
	return ret;
}

big_integer big_integer::operator-() const
{
	big_integer ret = *this;
	ret.is_negative_ = !is_negative_;
	return ret;
}

std::ostream& operator<<(std::ostream& o_stream, const big_integer& a)
{
	if (a.is_negative_ == 1) {
		o_stream << '-';
	}
	for (int i = a.first_index_; i < a.MAX_ELEMENT_NUM; ++i) {
		if (i != a.first_index_) {
			// format output
			o_stream << std::setw(big_integer::ELEMENT_DIGIT) << std::setfill('0');
		}
		o_stream << a.data_[i];
	}
	return o_stream;
}

std::istream& operator>>(std::istream& i_stream, big_integer& a)
{
	char ch;
	std::string tmp;
	// skip: single space, tab, vertical tab, 
	// form feed, carriage return, or newline.
	i_stream.get(ch);
	while (isspace(ch)) {
		i_stream.get(ch);
	}
	if (ch == '-') {
		tmp += ch;
		i_stream.get(ch);
	}
	while (ch >= '0' && ch <= '9')
	{
		tmp += ch;
		i_stream.get(ch);
	}
	i_stream.unget();
	a = tmp;
	return i_stream;
}

