#include "BigInt.hpp"
#include <iostream>
//#include <stdlib.h>
#include <vector>
class BigInt;
/*void plus_one(std::string &binary_BigInt);
void reverse_binary(std::string &binary_BigInt);
int get_ful_len(std::string &binary_BigInt);
std::string reverse(std::string const &s);
void binary_xor(const BigInt &a, const BigInt &b, BigInt &c);
void binary_or(const BigInt &a, const BigInt &b, BigInt &c);
void binary_and(const BigInt &a, const BigInt &b, BigInt &c);
void binary_invers(const BigInt &a, BigInt &c);*/
namespace
{
#define BASE 1000000000

int toInt(const std::string &str)
{
    int32_t digit = 1;
    int32_t result = 0;
    for (int32_t i = 0; i < str.size(); i++)
    {
        result += digit * (str[i] - '0');
        digit *= 10;
    }
    return result;
}

int32_t get_amount_of_numbers(int32_t val)
{
    if (val == 0)
    {
        return 1;
    }
    int32_t n = 0;
    while (val > 0)
    {
        val /= 10;
        n++;
    }
    return n;
}

void plus_one(std::string &binaryBigInt)
{
    binaryBigInt += '0';
    size_t len = binaryBigInt.size();
    int32_t i = 1;
    char a = binaryBigInt[0];
    int32_t term = 1 + (a - '0');
    int32_t tmp = term / 2;
    term = term % 2;
    binaryBigInt[0] = '0' + term;
    while (tmp != 0)
    {
        term = tmp + (binaryBigInt[i] - '0');
        tmp = term / 2;
        term = term % 2;
        binaryBigInt[i] = '0' + term;
        i++;
    }
    if (binaryBigInt[len - 1] == '0')
    {
        binaryBigInt.erase(len - 1, len);
    }
}

void reverse_binary(std::string &binaryBigInt)
{
    size_t len = binaryBigInt.size();
    for (int32_t i = 0; i < len; i++)
    {
        if (binaryBigInt[i] == '0')
        {
            binaryBigInt[i] = '1';
        }
        else
            binaryBigInt[i] = '0';
    }
}

int get_ful_len(std::string &binaryBigInt)
{
    size_t len = binaryBigInt.size();
    size_t base = 8;
    while (len > base)
    {
        base *= 2;
    }
    return base;
}

std::string reverse(std::string const &s)
{
    std::string rev(s.rbegin(), s.rend());
    return rev;
}
}

//private methods
void BigInt::del(int32_t ind)
{
    myVec.erase(myVec.begin() + ind);
}

void BigInt::del_zero()
{
    for (int32_t i = myVec.size() - 1; i > 0; i--)
    {
        if (myVec[i] != 0)
        {
            return;
        }
        del(i);
    }
}

void BigInt::full_del()
{
    myVec.clear();
    myVec.push_back(0);
}

int32_t BigInt::get_all_numbers() const
{
    int32_t sum = 0;
    for (int32_t i = myVec.size() - 1; i >= 0; i--)
    {
        if (i != myVec.size() - 1)
        {
            sum += 9;
        }
        else
        {
            sum += get_amount_of_numbers(myVec[i]);
        }
    }
    return sum;
}

void BigInt::sum_modul(const BigInt &a, const BigInt &b, BigInt &c)
{
    int32_t tmp = 0;
    int32_t firstval = 0;
    int32_t secondval = 0;
    int32_t degree = 0;
    int32_t cellA = 0;
    int32_t cellB = 0;
    int32_t  term = 0;
    size_t sizeA = a.myVec.size();
    size_t sizeB = b.myVec.size();
    size_t maxSize = std::max(sizeA, sizeB);
    for (int32_t i = 0; i < maxSize; i++)
    {
        if (c.myVec.size() < i + 1)
        {
            c.myVec.push_back(0);
        }
        else
        {
            c.myVec[i] = 0;
        }
        degree = 10;
        if (sizeA < i + 1)
        {
            cellA = 0;
        }
        else
        {
            cellA = a.myVec[i];
        }
        if (sizeB < i + 1)
        {
            cellB = 0;
        }
        else
        {
            cellB = b.myVec[i];
        }
        term = cellA + cellB + tmp;
        tmp = term / BASE;
        term = term % BASE;
        c.myVec[i] = term;
    }
    if (tmp != 0)
    {
        c.myVec.push_back(tmp);
    }
}

void BigInt::def_modul(const BigInt &a, const BigInt &b, BigInt &c)
{
    c.full_del();
    int32_t tmp = 0;
    int32_t firstval = 0;
    int32_t secondval = 0;
    int32_t degree = 0;
    int32_t cellA = 0;
    int32_t cellB = 0;
    int32_t term = 0;
    size_t sizeA = a.myVec.size();
    size_t sizeB = b.myVec.size();
    for (int32_t i = 0; i < sizeA; i++)
    {
        if (c.myVec.size() < i + 1)
        {
            c.myVec.push_back(0);
        }
        else
        {
            c.myVec[i] = 0;
        }
        cellA = a.myVec[i];
        if (sizeB < i + 1)
        {
            cellB = 0;
        }
        else
        {
            cellB = b.myVec[i];
        }
        term = cellA - cellB - tmp;
        if (term < 0)
        {
            tmp = 1;
            term += BASE;
        }
        else
        {
            tmp = 0;
        }
        c.myVec[i] = term;
    }
}

int BigInt::cmp_modul(const BigInt &a, const BigInt &b) const
{
    int32_t cellA = 0;
    int32_t cellB = 0;
    size_t sizeA = a.myVec.size();
    size_t sizeB = b.myVec.size();
    if (sizeA > sizeB)
    {
        return 1;
    }
    if (sizeA < sizeB)
    {
        return 2;
    }
    for (int32_t i = sizeA - 1; i >= 0; i--)
    {
        cellA = a.myVec[i];
        cellB = b.myVec[i];
        if (cellA > cellB)
        {
            return 1;
        }
        if (cellB > cellA)
        {
            return 2;
        }
    }
    return 0;
}

void BigInt::mul_modul(const BigInt &a, const BigInt &b, BigInt &c)
{
    BigInt zero = 0;
    c = zero;
    int64_t term = 0;
    int64_t firstval = 0;
    int64_t secondval = 0;
    int64_t degree = 0;
    int64_t degree2 = 0;
    int64_t cellA = 0;
    int64_t cellB = 0;
    int64_t tmp = 0;
    int64_t tmp_plus = 0;
    int64_t term_plus = 0;
    size_t sizeA = a.myVec.size();
    size_t sizeB = b.myVec.size();
    for (int32_t i = 0; i < sizeA + sizeB; i++)
    {
        c.myVec.push_back(0);
    }
    for (int32_t i = 0; i < sizeA; i++)
    {
        cellA = a.myVec[i];
        tmp = 0;
        for (int32_t j = 0; j < sizeB; j++)
        {
            cellB = b.myVec[j];
            term = cellA * cellB + tmp;
            tmp = term / BASE;
            term = term % BASE;
            tmp_plus = 0;
            term_plus = term + c.myVec[i + j] + tmp_plus;
            tmp_plus = term_plus / BASE;
            term_plus = term_plus % BASE;
            c.myVec[i + j] = term_plus;
            int32_t counter = 1;
            while (tmp_plus != 0)
            {
                term_plus = c.myVec[i + j + counter] + tmp_plus;
                tmp_plus = term_plus / BASE;
                term_plus = term_plus % BASE;
                c.myVec[i + j + counter] = term_plus;
                counter++;
            }
        }
        if (tmp != 0)
        {
            tmp_plus = 0;
            term_plus = tmp + c.myVec[i + sizeB] + tmp_plus;
            tmp_plus = term_plus / BASE;
            term_plus = term_plus % BASE;
            c.myVec[i + sizeB] = term_plus;
        }
    }
    c.del_zero();
}

void BigInt::div_modul(const BigInt &a, const BigInt &b, BigInt &c)
{
    BigInt a1 = a;
    BigInt b1 = b;
    //BigInt c1 = 10;
    BigInt ten = 10;
    BigInt zero = 0;
    BigInt MulResult;
    c = zero;
    if (b == zero)
    {
        throw std::invalid_argument("wtf man, delenie na nol?");
    }
    a1.sign = 0;
    b1.sign = 0;
    int32_t dif;
    while (cmp_modul(a1, b1) < 2)
    {
        b1.sign = 0;
        BigInt c2 = 1;
        dif = a1.get_all_numbers() - b1.get_all_numbers();
        for (int i = 0; i < dif - 1; i++)
        {
            b1 *= ten;
            c2 *= ten;
        }
        for (int i = 99; i > 0; i--)
        {
            BigInt tmp = i;
            //c1 = tmp;
            MulResult = b1;
            MulResult *= tmp;
            if (cmp_modul(a1, MulResult) != 2)
            {
                BigInt tmp2 = i;
                tmp = tmp2;
                b1 *= tmp;
                c2 *= tmp;
                break;
            }
        }
        c += c2;
        a1 -= b1;
        b1 = b;
    }
}

void BigInt::rem_modul(const BigInt &a, const BigInt &b, BigInt &c)
{
    BigInt a1 = a;
    BigInt b1 = b;
    //BigInt c1 = 10;
    BigInt ten = 10;
    BigInt zero = 0;
    BigInt MulResult;
    c = zero;
    if (b == zero)
    {
        throw std::invalid_argument("wtf man, delenie na nol?");
    }
    a1.sign = 0;
    b1.sign = 0;
    int32_t dif;
    while (cmp_modul(a1, b1) < 2)
    {
        b1.sign = 0;
        BigInt c2 = 1;
        dif = a1.get_all_numbers() - b1.get_all_numbers();
        for (int i = 0; i < dif - 1; i++)
        {
            b1 *= ten;
            c2 *= ten;
        }
        for (int i = 99; i > 0; i--)
        {
            BigInt tmp = i;
            //c1 = tmp;
            MulResult = b1;
            MulResult *= tmp;
            if (cmp_modul(a1, MulResult) != 2)
            {
                BigInt tmp2 = i;
                tmp = tmp2;
                b1 *= tmp;
                c2 *= tmp;
                break;
            }
        }
        c += c2;
        a1 -= b1;
        b1 = b;
    }
    c = a1;
}

void BigInt::to_binary(const BigInt &a, std::string &binaryBigInt) const
{
    binaryBigInt = "";
    BigInt tmp = a;
    BigInt term;
    BigInt base = 2;
    BigInt zero = 0;
    int32_t val_of_term = 0;
    char num;
    tmp.sign = 0;
    while (tmp > zero)
    {
        term = tmp;
        term %= base;
        val_of_term = term.myVec[0];
        num = val_of_term + '0';
        binaryBigInt += num;
        tmp /= base;
    }
    int32_t ful_len = get_ful_len(binaryBigInt);
    size_t len_now = binaryBigInt.size();
    for (int32_t i = len_now; i < ful_len; i++)
    {
        binaryBigInt += '0';
    }
    if (a.sign == 1)
    {
        reverse_binary(binaryBigInt);
        binaryBigInt[ful_len - 1] = '1';
        plus_one(binaryBigInt);
    }
}

void BigInt::to_BigInt(BigInt &c, std::string &binaryBigInt) const
{
    c.full_del();
    // c.myVec.push_back(0);
    BigInt base = 2;
    BigInt term;
    BigInt degree = 1;
    int32_t  val = 0;
    int32_t flag = 1;
    size_t str_size = binaryBigInt.size();
    if (binaryBigInt[str_size - 1] == '1')
    {
        reverse_binary(binaryBigInt);
        plus_one(binaryBigInt);
        flag = 0;
    }
    for (int32_t i = 0; i < str_size; i++)
    {
        val = binaryBigInt[i] - '0';
        BigInt tmp = val;
        term = tmp;
        term *= degree;
        degree *= base;
        c += term;
    }
    if (flag == 0)
    {
        c.sign = 1;
    }
}

void BigInt::binary_and(const BigInt &a, const BigInt &b, BigInt &c)
{
    std::string first_number;
    std::string second_number;
    std::string result = "";
    to_binary(a, first_number);
    to_binary(b, second_number);
    size_t size1 = first_number.size();
    size_t size2 = second_number.size();
    char index1 = first_number[size1 - 1];
    char index2 = second_number[size2 - 1];
    size_t max_size = std::max(size1, size2);
    char val1;
    char val2;
    char val_result;
    for (int32_t i = 0; i < max_size; i++)
    {
        if (size1 < i + 1)
        {
            val1 = index1;
        }
        else
        {
            val1 = first_number[i];
        }
        if (size2 < i + 1)
        {
            val2 = index2;
        }
        else
        {
            val2 = second_number[i];
        }
        val_result = '0' + ((val1 - '0') * (val2 - '0'));
        result += val_result;
    }
    to_BigInt(c, result);
}

void BigInt::binary_or(const BigInt &a, const BigInt &b, BigInt &c)
{
    std::string first_number;
    std::string second_number;
    std::string result = "";
    to_binary(a, first_number);
    to_binary(b, second_number);
    size_t size1 = first_number.size();
    size_t size2 = second_number.size();
    char index1 = first_number[size1 - 1];
    char index2 = second_number[size2 - 1];
    size_t max_size = std::max(size1, size2);
    char val1 = 0;
    char val2 = 0;
    char val_result = 0;
    for (int32_t i = 0; i < max_size; i++)
    {
        if (size1 < i + 1)
        {
            val1 = index1;
        }
        else
        {
            val1 = first_number[i];
        }
        if (size2 < i + 1)
        {
            val2 = index2;
        }
        else
        {
            val2 = second_number[i];
        }
        if ((val1 - '0') == 1 || (val2 - '0') == 1)
        {
            val_result = '1';
        }
        else
        {
            val_result = '0';
        }
        result += val_result;
    }
    to_BigInt(c, result);
}

void BigInt::binary_xor(const BigInt &a, const BigInt &b, BigInt &c)
{
    std::string first_number;
    std::string second_number;
    std::string result = "";
    to_binary(a, first_number);
    to_binary(b, second_number);
    size_t size1 = first_number.size();
    size_t size2 = second_number.size();
    char index1 = first_number[size1 - 1];
    char index2 = second_number[size2 - 1];
    size_t max_size = std::max(size1, size2);
    char val1 = 0;
    char val2 = 0;
    char val_result = 0;
    for (int32_t i = 0; i < max_size; i++)
    {
        if (size1 < i + 1)
        {
            val1 = index1;
        }
        else
        {
            val1 = first_number[i];
        }
        if (size2 < i + 1)
        {
            val2 = index2;
        }
        else
        {
            val2 = second_number[i];
        }
        if ((val1 - '0') != (val2 - '0'))
        {
            val_result = '1';
        }
        else
        {
            val_result = '0';
        }
        result += val_result;
    }
    to_BigInt(c, result);
}

void BigInt::binary_invers(const BigInt &a, BigInt &c) const
{
    std::string first_number;
    to_binary(a, first_number);
    reverse_binary(first_number);
    to_BigInt(c, first_number);
}

//public methods and operators
BigInt::BigInt(int32_t val)
{
    if (val >= 0)
    {
        sign = 0;
    }
    else
    {
        sign = 1;
        val = -val;
    }
    int first_number = val % BASE;
    int secon_number = val / BASE;
    myVec.push_back(first_number);
    if (secon_number != 0)
    {
        myVec.push_back(secon_number);
    }
}

BigInt::BigInt()
{
    sign = 0;
    myVec.push_back(0);
}

BigInt::BigInt(std::string MyBigint)
{
    int32_t flag = 0;
    if (MyBigint[0] == '-')
    {
        sign = 1;
        flag = 1;
    }
    else if (MyBigint[0] == '+')
    {
        sign = 0;
        flag = 1;
    }
    else
    {
        sign = 0;
    }
    std::string buffer = "";
    int32_t counter = 0;
    int32_t res;
    for (int32_t i = MyBigint.size() - 1; i >= flag; i--)
    {
        char val = MyBigint[i];
        if (!(val >= '0' && val <= '9'))
        {
            throw std::invalid_argument("Invalid syntax.");
        }
        counter++;
        if (counter == 9)
        {
            buffer = MyBigint.substr(i, 9);
            buffer = reverse(buffer);
            res = toInt(buffer);
            counter = 0;
            myVec.push_back(res);
        }
    }
    if (counter != 0)
    {
        buffer = MyBigint.substr(flag, counter);
        buffer = reverse(buffer);
        res = toInt(buffer);
        myVec.push_back(res);
    }
    for (int32_t i = myVec.size() - 1; i > 0; i--)
    {
        if (myVec[i] != 0)
        {
            return;
        }
        myVec.erase(myVec.begin() + i);
        //this->del(i);
    }
    if (myVec.size() == 1 && myVec[0] == 0)
    {
        sign = 0;
    }
}

BigInt::BigInt(const BigInt &val)
{
    sign = val.sign;
    myVec = val.myVec;
}

bool BigInt::operator==(const BigInt &a) const
{
    return (cmp_modul(*(this), a) == 0 && a.sign == sign);
}

bool BigInt::operator!=(const BigInt &a) const
{
    if (!(*(this) == a))
    {
        return 1;
    }
    return 0;
}

bool BigInt::operator>(const BigInt &a) const
{
    int32_t res_cmp = cmp_modul(*(this), a), sign1 = sign, sign2 = a.sign;
    if (sign2 == sign1)
    {
        if (sign1 == 0)
        {
            if (res_cmp == 1)
            {
                return 1;
            }
        }
        else
        {
            if (res_cmp == 2)
            {
                return 1;
            }
        }
    }
    else
    {
        if (sign1 == 0)
        {
            return 1;
        }
    }
    return 0;
}

BigInt &BigInt::operator=(const BigInt &other)
{
    sign = other.sign;
    myVec = other.myVec;
    return *(this);
}

bool BigInt::operator<(const BigInt &a) const
{
    if (!(*(this) > a) && (*(this) != a))
    {
        return 1;
    }
    return 0;
}

bool BigInt::operator<=(const BigInt &a) const
{
    if ((*(this) < a) || (*(this) == a))
    {
        return 1;
    }
    return 0;
}

bool BigInt::operator>=(const BigInt &a) const
{
    if ((*(this) > a) || (*(this) == a))
    {
        return 1;
    }
    return 0;
}

BigInt BigInt::operator+() const
{
    BigInt tmp = *(this);
    return tmp;
}

BigInt BigInt::operator-() const
{
    BigInt tmp = *(this);
    tmp.sign = !(tmp.sign);
    return tmp;
}

BigInt &BigInt::operator+=(const BigInt &b)
{
    BigInt c = *(this);
    if (c.sign == b.sign)
    {
        sum_modul(c, b, *(this));
        sign = c.sign;
    }
    else
    {
        if (cmp_modul(c, b) == 1)
        {
            def_modul(c, b, *(this));
            this->del_zero();
            sign = c.sign;
        }
        else if (cmp_modul(c, b) == 2)
        {
            def_modul(b, c, *(this));
            this->del_zero();
            sign = b.sign;
        }
        else
        {
            full_del();
            // myVec.push_back(0);
            sign = 0;
        }
    }
    return *(this);
}

BigInt &BigInt::operator-=(const BigInt &b)
{
    BigInt c = *(this);
    if (c.sign == b.sign)
    {
        if (cmp_modul(c, b) == 1)
        {
            def_modul(c, b, *(this));
            this->del_zero();
            sign = c.sign;
        }
        else if (cmp_modul(c, b) == 2)
        {
            def_modul(b, c, *(this));
            this->del_zero();
            sign = !(b.sign);
        }
        else
        {
            full_del();
            // myVec.push_back(0);
            sign = 0;
        }
    }
    else
    {
        sign = c.sign;
        sum_modul(c, b, *(this));
    }
    return *(this);
}

BigInt &BigInt::operator++()
{
    BigInt tmp = 1;
    *(this) += tmp;
    return *(this);
}

const BigInt BigInt::operator++(int32_t tmp)
{
    BigInt a = *this;
    //a = *this;
    ++(*this);
    return a;
}

BigInt &BigInt::operator--()
{
    BigInt tmp = -1;
    *(this) += tmp;
    return *(this);
}

const BigInt BigInt::operator--(int32_t tmp)
{
    BigInt a = *this;
    //a = *this;
    --(*this);
    return a;
}

BigInt &BigInt::operator*=(const BigInt &b)
{
    BigInt c = *(this);
    mul_modul(c, b, *(this));
    BigInt cheker = 0;
    if (cheker == *(this))
    {
        sign = 0;
    }
    else
    {
        if (c.sign == b.sign)
        {
            sign = 0;
        }
        else
        {
            sign = 1;
        }
    }
    return *(this);
}

BigInt &BigInt::operator/=(const BigInt &b)
{
    BigInt c = *(this);
    div_modul(c, b, *(this));
    if (c.sign == b.sign)
    {
        sign = 0;
    }
    else
    {
        sign = 1;
    }
    return *(this);
}

BigInt &BigInt::operator%=(const BigInt &b)
{
    BigInt c = *(this);
    BigInt zero=0;
    int32_t sign1 = c.sign;
    int32_t sign2 = b.sign;
    rem_modul(c, b, *(this));
    if (sign1 == 1 && *(this)!=zero)
    {
        c = -(*(this));
        if (sign2 == 0)
        {
            c += b;
        }
        else
        {
            c -= b;
        }
        *(this) = c;
    }
    return *(this);
}

BigInt &BigInt::operator^=(const BigInt &b)
{
    BigInt c = *(this);
    binary_xor(c, b, *(this));
    return *(this);
}

BigInt &BigInt::operator&=(const BigInt &b)
{
    BigInt c = *(this);
    binary_and(c, b, *(this));
    return *(this);
}

BigInt &BigInt::operator|=(const BigInt &b)
{
    BigInt c = *(this);
    binary_or(c, b, *(this));
    return *(this);
}

BigInt BigInt::operator~() const
{
    BigInt c = 0;
    binary_invers(*(this), c);
    return c;
}

size_t BigInt::size() const
{
    return size_t(myVec.size());
}

BigInt::operator int() const
{
    long long res = myVec[0];
    if (myVec.size() >= 2 && (myVec[1] % 10) <= 2)
    {
        res += (myVec[1] % 10) * BASE;
        if (sign == 1)
        {
            res = -res;
        }
        if (res > 2147483647 || res < (-2147483648))
        {
            res = myVec[0];
            if (sign == 1)
            {
                res = -res;
            }
        }
    }
    else
    {
        if (sign == 1)
        {
            res = -res;
        }
    }
    res = int(res);
    return res;
}

BigInt::operator std::string() const
{
    size_t size_of_vec = myVec.size();
    int32_t full_len = get_all_numbers();
    int32_t counter = 0;
    if (sign == 1 && !(size_of_vec == 1 && myVec[0] == 0))
    {
        full_len++;
    }
    std::string result(full_len, '0');
    if (sign == 1 && !(size_of_vec == 1 && myVec[0] == 0))
    {
        result[counter] = '-';
        counter++;
        // result+='-';
    }
    for (int32_t i = size_of_vec - 1; i >= 0; i--)
    {
        if (i != size_of_vec - 1)
        {
            int32_t amount_of_numbers = get_amount_of_numbers(myVec[i]);
            if (myVec[i] == 0)
            {
                amount_of_numbers = 0;
            }
            for (int32_t j = 0; j < 9 - amount_of_numbers; j++)
            {
                result[counter] = '0';
                counter++;
                // result+='0';
            }
        }
        if (myVec[i] != 0 || i == size_of_vec - 1)
        {
            std::string tmp = std::to_string(myVec[i]);
            for (int j = 0; j < tmp.size(); j++)
            {
                result[counter] = tmp[j];
                counter++;
            }
        }
    }
    return result;
}

//BigInt::~BigInt() {}

//free public operators
BigInt operator+(const BigInt &a, const BigInt &b)
{
    BigInt c=a;
    c += b;
    return c;
}

BigInt operator-(const BigInt &a, const BigInt &b)
{
    BigInt c=a;
    c -= b;
    return c;
}

BigInt operator*(const BigInt &a, const BigInt &b)
{
    BigInt c=a;
    c *= b;
    return c;
}

BigInt operator/(const BigInt &a, const BigInt &b)
{
    BigInt c=a;
    c /= b;
    return c;
}

BigInt operator%(const BigInt &a, const BigInt &b)
{
    BigInt c=a;
    c %= b;
    return c;
}

BigInt operator^(const BigInt &a, const BigInt &b)
{
    BigInt c=a;
    c ^= b;
    return c;
}

BigInt operator&(const BigInt &a, const BigInt &b)
{
    BigInt c=a;
    c &= b;
    return c;
}

BigInt operator|(const BigInt &a, const BigInt &b)
{
    BigInt c=a;
    c |= b;
    return c;
}

std::ostream &operator<<(std::ostream &o, const BigInt &i)
{
    o << std::string(i);
    return o;
}
