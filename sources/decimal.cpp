#include "decimal.h"

Decimal::Decimal() : sign{1}, digits{0}, exponent{1}
{
}

Decimal::Decimal(std::string str) : sign{1}, digits{0}, exponent{1}
{
    MakeFromString(str);
    RemoveZeroes();
}

Decimal::Decimal(const Decimal &decimal) : sign{1}, digits{0}, exponent{1}
{
    sign = decimal.sign;
    exponent = decimal.exponent;
    digits = std::vector<int>(decimal.digits);
}

Decimal::Decimal(const int &num) : sign{1}, digits{0}, exponent{1}
{
    std::stringstream ss;
	ss << num;
	MakeFromString(ss.str());
	RemoveZeroes();
}

Decimal::Decimal(const double &num) : sign{1}, digits{0}, exponent{1}
{
    std::stringstream ss;
	ss << std::setprecision(15) << num;
	MakeFromString(ss.str());
	RemoveZeroes();
}

Decimal::~Decimal()
{

}

void Decimal::MakeFromString(const std::string &s)
{
    int index;

	if (s[0] == '-') {
		sign = -1;
		index = 1;
	} else {
		sign = 1;
		index = 0;
	}

	exponent = std::abs(static_cast<int>(s.length()) - index);

	while (index < static_cast<int>(s.length())) {
		if (s[static_cast<long unsigned int>(index)] == '.')
			exponent = sign == 1 ? index : index - 1;
		else
			digits.push_back(s[static_cast<long unsigned int>(index)] - '0');

		index++;
	}
}

void Decimal::RemoveZeroes()
{
    int n = std::max(1, static_cast<int>(exponent));
    while (static_cast<int>(digits.size()) > n && digits[digits.size() - 1] == 0)
        digits.erase(digits.end() - 1);
    while (digits.size() > 1 && digits[0] == 0) {
        digits.erase(digits.begin());
        exponent--;
    }
    while (digits.size() > 1 && digits[digits.size() - 1] == 0)
        digits.erase(digits.end() - 1);
    if (digits.size() == 1 && digits[0] == 0) {
        exponent = 1;
        sign = 1;
    }
}

Decimal Decimal::Inverse() const
{
    if (IsZero())
		throw std::string("Division by zero!");

	Decimal x(*this);
	x.sign = 1;
	Decimal d("1");
	Decimal res;
	res.sign = sign;
	res.exponent = 1;
	res.digits = std::vector<int>();
	while (x < 1) {
		x.exponent++;
		res.exponent++;
	}
	while (d < x)
		d.exponent++;

	res.exponent -= d.exponent - 1;
	int numbers = 0;
	int intPart = std::max(0, static_cast<int>(res.exponent));
	int maxNumbers = maxPrecision + intPart;
	do {
		int div = 0;
		while (d >= x) {
			div++;
			d -= x;
		}
		d.exponent++;
		d.RemoveZeroes();
		res.digits.push_back(div);
		numbers++;
	} while (!d.IsZero() && numbers < maxNumbers);
	return res;
}

bool Decimal::IsZero() const {
	return digits.size() == 1 && digits[0] == 0;
}

Decimal& Decimal::operator=(const Decimal &decimal)
{
    sign = decimal.sign;
    exponent = decimal.exponent;
    digits = std::vector<int>(decimal.digits);
    return *this;
}

Decimal Decimal::operator-() const
{
    Decimal res;
    res.sign = -sign;
    res.exponent = exponent;
    res.digits = std::vector<int>(digits);
    return res;
}

Decimal Decimal::operator+(const Decimal &decimal) const
{
        if (sign == decimal.sign)
        {
        long exp1 = exponent;
        long exp2 = decimal.exponent;
        long exp = std::max(exp1, exp2);
        std::vector<int> d1(digits);
        std::vector<int> d2(decimal.digits);
        while (exp1 != exp)
        {
            d1.insert(d1.begin(), 0);
            exp1++;
        }
        while (exp2 != exp)
        {
            d2.insert(d2.begin(), 0);
            exp2++;
        }
        size_t size = std::max(d1.size(), d2.size());
        while (d1.size() != size)
            d1.push_back(0);
        while (d2.size() != size)
            d2.push_back(0);
        size_t len = 1 + size;
        Decimal res;
        res.sign = sign;
        res.digits = std::vector<int>(len, 0);
        for (size_t i = 0; i < size; i++)
            res.digits[i + 1] = d1[i] + d2[i];
        for (size_t i = len - 1; i > 0; i--) {
            res.digits[i - 1] += res.digits[i] / 10;
            res.digits[i] %= 10;
        }
        res.exponent = exp + 1;
        res.RemoveZeroes();
        return res;
    }

    if (sign == -1)
        return decimal - (-(*this));
    return *this - (-decimal);
}

Decimal Decimal::operator+=(const  Decimal &decimal)
{
    return (*this = *this + decimal);
}

Decimal Decimal::operator-(const Decimal &decimal) const
{
    if (sign == 1 && decimal.sign == 1)
    {
        bool cmp = *this > decimal;
        long exp1 = cmp ? exponent : decimal.exponent;
        long exp2 = cmp ? decimal.exponent : exponent;
        long exp = std::max(exp1, exp2);
        std::vector<int> d1(cmp ? digits : decimal.digits);
        std::vector<int> d2(cmp ? decimal.digits : digits);
        while (exp1 != exp)
        {
            d1.insert(d1.begin(), 0);
            exp1++;
        }
        while (exp2 != exp)
        {
            d2.insert(d2.begin(), 0);
            exp2++;
        }
        size_t size = std::max(d1.size(), d2.size());
        while (d1.size() != size)
            d1.push_back(0);
        while (d2.size() != size)
            d2.push_back(0);
        size_t len = 1 + size;
        Decimal res;
        res.sign = cmp ? 1 : -1;
        res.digits = std::vector<int>(len, 0);
        for (size_t i = 0; i < size; i++)
            res.digits[i + 1] = d1[i] - d2[i];
        for (size_t i = len - 1; i > 0; i--) {
            if (res.digits[i] < 0) {
                res.digits[i] += 10;
                res.digits[i - 1]--;
            }
        }
        res.exponent = exp + 1;
        res.RemoveZeroes();
        return res;
    }
    if (sign == -1 && decimal.sign == -1)
        return (-decimal) - (-(*this));
    return *this + (-decimal);
}

Decimal Decimal::operator-=(const Decimal &decimal)
{
    return (*this = *this - decimal);
}

Decimal Decimal::operator*(const Decimal &decimal) const
{
    size_t len = digits.size() + decimal.digits.size();
    Decimal res;
    res.sign = sign * decimal.sign;
    res.digits = std::vector<int>(len, 0);
    res.exponent = exponent + decimal.exponent;
    for (size_t i = 0; i < digits.size(); i++)
        for (size_t j = 0; j < decimal.digits.size(); j++)
            res.digits[i + j + 1] += digits[i] * decimal.digits[j];
    for (size_t i = len - 1; i > 0; i--) {
        res.digits[i - 1] += res.digits[i] / 10;
        res.digits[i] %= 10;
    }
    res.RemoveZeroes();
    return res;
}

Decimal Decimal::operator*=(const Decimal &decimal)
{
    return (*this = *this * decimal);
}

Decimal Decimal::operator/(const Decimal &decimal) const
{
    Decimal res = *this * decimal.Inverse();
    int intPart = std::max(0, static_cast<int>(exponent));
	if (intPart > static_cast<int>(res.digits.size()) - 1)
		return res;
	int i = static_cast<int>(res.digits.size()) - 1 - intPart;
	int n = std::max(0, static_cast<int>(res.exponent));
	if (i > n && res.digits[static_cast<long unsigned int>(i)] == 9) {
		while (i > n && res.digits[static_cast<long unsigned int>(i)] == 9)
			i--;
		if (res.digits[static_cast<long unsigned int>(i)] == 9) {
			res.digits.erase(res.digits.begin() + n, res.digits.end());
			res = res + res.sign;
		}
		else {
			res.digits.erase(res.digits.begin() + i + 1, res.digits.end());
			res.digits[static_cast<long unsigned int>(i)]++;
		}
	}
	return res;
}

Decimal Decimal::operator/=(const Decimal &decimal)
{
    return (*this = *this / decimal);
}

bool Decimal::operator==(const Decimal &decimal) const
{
    if (sign != decimal.sign)
		return false;
	if (exponent != decimal.exponent)
		return false;
	if (digits.size() != decimal.digits.size())
		return false;
	for (size_t i = 0; i < digits.size(); i++)
		if (digits[i] != decimal.digits[i])
			return false;
	return true;
}
bool Decimal::operator!=(const Decimal &decimal) const
{
    return !(*this == decimal);
}
bool Decimal::operator<(const Decimal &decimal) const
{
    if (sign != decimal.sign)
        return sign < decimal.sign;
    if (exponent != decimal.exponent)
        return (exponent < decimal.exponent) ^ (sign == -1);
    std::vector<int> d1(digits);
    std::vector<int> d2(decimal.digits);
    size_t size = std::max(d1.size(), d2.size());
    while (d1.size() != size)
        d1.push_back(0);
    while (d2.size() != size)
        d2.push_back(0);
    for (size_t i = 0; i < size; i++)
        if (d1[i] != d2[i])
            return (d1[i] < d2[i]) ^ (sign == -1);
    return false;
}
bool Decimal::operator<=(const Decimal &decimal) const
{
    return *this < decimal || *this == decimal;
}
bool Decimal::operator>(const Decimal &decimal) const
{
    if (sign != decimal.sign)
        return sign > decimal.sign;
    if (exponent != decimal.exponent)
        return (exponent > decimal.exponent) ^ (sign == -1);
    std::vector<int> d1(digits);
    std::vector<int> d2(decimal.digits);
    size_t size = std::max(d1.size(), d2.size());
    while (d1.size() != size)
        d1.push_back(0);
    while (d2.size() != size)
        d2.push_back(0);
    for (size_t i = 0; i < size; i++)
        if (d1[i] != d2[i])
            return (d1[i] > d2[i]) ^ (sign == -1);
    return false;
}

bool Decimal::operator>=(const Decimal &decimal) const
{
    return *this > decimal || *this == decimal;
}


int Decimal::operator[](const int index)
{
    return digits[static_cast<long unsigned int>(index)];
}

int& Decimal::operator()(const int index)
{
    return digits[static_cast<long unsigned int>(index)];
}

std::ostream& operator<<(std::ostream &out, const Decimal &decimal)
{
    if (decimal.sign == -1)
        out << '-';
    if (decimal.exponent > 0)
    {
        int i = 0;
        int e = static_cast<int>(decimal.exponent);
        while(i < static_cast<int>(decimal.digits.size()) && i < e)
            out << decimal.digits[static_cast<long unsigned int>(i++)];
        while (i < e)
        {
            out << "0";
            i++;
        }

        if (i < static_cast<int>(decimal.digits.size()))
        {
            out << ".";
            while(i < static_cast<int>(decimal.digits.size()))
                out << decimal.digits[static_cast<long unsigned int>(i++)];
        }
    }
    else
    {
        out << "0.";
        for (long i = 0; i < - decimal.exponent; i++)
            out << "0";
        for (size_t i = 0; i < decimal.digits.size(); i++)
            out << decimal.digits[i];
    }
    return out;
}

std::istream& operator>>(std::istream &in, Decimal &decimal)
{
    std::string str;
    in >> str;
    decimal = Decimal(str);
    return in;
}

int Decimal::ToInt()
{
    std::stringstream ss;
    ss << *this;
    int res;
    ss>>res;
    return res;
}


double Decimal::ToDouble()
{
    std::stringstream ss;
    ss << *this;
    double res;
    ss>>res;
    return res;
}

