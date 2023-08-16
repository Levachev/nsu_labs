#pragma once
#include <iostream>
#include <vector>
class BigInt
{
private:
    std::vector<int32_t> myVec;
    int32_t sign;
public:
    BigInt();
    BigInt(int);
    BigInt(std::string); // бросать исключение std::invalid_argument при ошибке
    BigInt(const BigInt&);
    ~BigInt()=default;
private:
    void  del(int32_t ind);
    void  del_zero();
    void  full_del();
    int32_t  get_all_numbers()const;
    void  sum_modul(const BigInt &a, const BigInt &b, BigInt &c);
    void  def_modul(const BigInt &a, const BigInt &b, BigInt &c);
    int  cmp_modul(const BigInt& a, const BigInt& b) const;
    void  mul_modul(const BigInt &a, const BigInt &b, BigInt &c);
    void  div_modul(const BigInt &a, const BigInt &b, BigInt &c);
    void  rem_modul(const BigInt &a, const BigInt &b, BigInt &c);
    void  to_binary(const BigInt &a, std::string &binary_BigInt) const;
    void  to_BigInt(BigInt &c, std::string &binary_BigInt)const;
    void  binary_and(const BigInt &a, const BigInt &b, BigInt &c);
    void  binary_or(const BigInt &a, const BigInt &b, BigInt &c);
    void  binary_xor(const BigInt &a, const BigInt &b, BigInt &c);
    void  binary_invers(const BigInt &a, BigInt &c) const;
public:
    BigInt& operator=(const BigInt&);  //возможно присваивание самому себе!

    BigInt operator~() const;

    BigInt& operator++();
    const BigInt operator++(int);
    BigInt& operator--();
    const BigInt operator--(int);

    BigInt& operator+=(const BigInt&);
    BigInt& operator*=(const BigInt&);
    BigInt& operator-=(const BigInt&);
    BigInt& operator/=(const BigInt&);
    BigInt& operator^=(const BigInt&);
    BigInt& operator%=(const BigInt&);
    BigInt& operator&=(const BigInt&);
    BigInt& operator|=(const BigInt&);

    BigInt operator+() const;  // unary +
    BigInt operator-() const;  // unary -

    bool operator==(const BigInt&) const;
    bool operator!=(const BigInt&) const;
    bool operator<(const BigInt&) const;
    bool operator>(const BigInt&) const;
    bool operator<=(const BigInt&) const;
    bool operator>=(const BigInt&) const;

    operator int() const;
    operator std::string() const;

    size_t size() const;  // size in bytes
};

BigInt operator+(const BigInt&, const BigInt&);
BigInt operator-(const BigInt&, const BigInt&);
BigInt operator*(const BigInt&, const BigInt&);
BigInt operator/(const BigInt&, const BigInt&);
BigInt operator^(const BigInt&, const BigInt&);
BigInt operator%(const BigInt&, const BigInt&);
BigInt operator&(const BigInt&, const BigInt&);
BigInt operator|(const BigInt&, const BigInt&);


std::ostream& operator<<(std::ostream& o, const BigInt& i);

/*void plus_one(std::string &binary_BigInt);
void reverse_binary(std::string &binary_BigInt);
int get_ful_len(std::string &binary_BigInt);
std::string reverse(std::string const &s);
void binary_xor(const BigInt &a, const BigInt &b, BigInt &c);
void binary_or(const BigInt &a, const BigInt &b, BigInt &c);
void binary_and(const BigInt &a, const BigInt &b, BigInt &c);
void binary_invers(const BigInt &a, BigInt &c);
int toInt(const std::string &str);
int32_t get_amount_of_numbers(int32_t val);*/
