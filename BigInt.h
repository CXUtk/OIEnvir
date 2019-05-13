//
// Created by DELL on 2018/10/20.
//

#ifndef OJONLY_BIGINT_H
#define OJONLY_BIGINT_H

#include <cstdio>
#include <cstring>
#include <algorithm>

class BigInt {
public:
    static constexpr int N = 10005;

	BigInt() : BigInt(0);

    explicit BigInt(unsigned int n, int base = 10) {
        this->base = base;
        memset(data, 0, sizeof(data));
        if (n == 0) {
            digits = 1;
            return;
        }
        int k = 0;
        while (n != 0) {
            data[k++] = n % this->base;
            n /= this->base;
        }
        digits = k;
    }

    explicit BigInt(const char *num, int len, int base = 10);

    BigInt(const BigInt &other);

    BigInt &operator=(const BigInt &other);

    BigInt add(const BigInt &other) const;

    BigInt minus(const BigInt &other) const;

    BigInt multiply(const BigInt &other) const;

	BigInt divide(const BigInt& other) const;

    BigInt modular(const BigInt& other) const;

    void trimZero();

    void print(FILE *file) const;

    bool operator>(const BigInt &b) const;

    bool operator<(const BigInt &b) const { return b > *this; }

    bool operator<=(const BigInt &b) const { return !(*this > b); }

    bool operator>=(const BigInt &b) const { return !(*this < b); }

    bool operator!=(const BigInt &b) const { return b < *this || *this < b; }

    bool operator==(const BigInt &b) const { return !(b < *this) && !(b > *this); }

    ~BigInt() {}

private:
    int data[N];
    int digits = 1;
    int base = 10;
    char sign = 0;
};


BigInt &BigInt::operator=(const BigInt &other) {
    this->sign = other.sign;
    this->digits = other.digits;
    memset(data, 0, sizeof(data));
    memcpy(this->data, other.data, other.digits * sizeof(int));
    return *this;
}

BigInt::BigInt(const BigInt &other) {
    this->sign = other.sign;
    this->digits = other.digits;
    memset(data, 0, sizeof(data));
    memcpy(this->data, other.data, other.digits * sizeof(int));
}

BigInt::BigInt(const char *num, int len, int base) {
    this->base = base;
    memset(data, 0, sizeof(data));
    if (num[0] == '-') {
        sign = 1;
        len--;
        num++;
    }
    digits = len;
    int k = 0;
    for (int i = digits - 1; i >= 0; i--) {
        if(num[i] >= 'A')
            data[k++] = num[i] - 'A' + 10;
        else
            data[k++] = num[i] - '0';
    }
    trimZero();
}

BigInt BigInt::add(const BigInt &other) const {
    if (other.sign) {
        BigInt tmp(other);
        tmp.sign = 0;
        return this->minus(tmp);
    }
    if (this->sign) {
        BigInt tmp(*this);
        tmp.sign = 0;
        return other.minus(tmp);
    }
    BigInt res(0);
    int maxx = std::min(this->digits, other.digits);
    int k = 0;
    int carry = 0;
    for (; k < maxx; k++) {
        int sum = this->data[k] + other.data[k] + carry;
        res.data[k] = sum % this->base;
        carry = sum / this->base;
    }
    while (k < this->digits) {
        int sum = this->data[k] + carry;
        res.data[k++] = sum % this->base;
        carry = sum / this->base;
    }
    while (k < other.digits) {
        int sum = other.data[k] + carry;
        res.data[k++] = sum % this->base;
        carry = sum / this->base;
    }
    if (carry > 0) {
        res.data[k++] = carry;
    }
    res.digits = k;
    return res;
}

void BigInt::print(FILE *file) const {
    if (sign) {
        fputc('-', file);
    }
    for (int i = this->digits - 1; i >= 0; i--) {
        if(this->data[i] >= 10)
            fputc(this->data[i] - 10 + 'A', file);
        else
            fputc(this->data[i] + '0', file);
    }
    fprintf(file, "\n");
}

BigInt BigInt::minus(const BigInt &other) const {
    if (*this == other)
        return BigInt(0);
    if (other.sign) {
        BigInt tmp(other);
        tmp.sign = 0;
        return this->add(tmp);
    }
    if (this->sign) {
        BigInt tmp(*this);
        tmp.sign = 0;
        auto r = other.add(tmp);
        r.sign = 1;
        return r;
    }
    BigInt a(*this);
    BigInt b(other);
    if (*this < other) {
        a = other;
        b = *this;
        a.sign = 1;
    }
    int maxx = std::min(this->digits, other.digits);
    int i = 0;
    for (; i < maxx; i++) {
        int diff = a.data[i] - b.data[i];
        if (diff < 0) {
            diff += this->base;
            a.data[i + 1]--;
        }
        a.data[i] = diff;
    }
    while (a.data[i] < 0) {
        a.data[i] += this->base;
        a.data[i + 1]--;
        i++;
    }
    a.digits = std::max(i, a.digits);
    a.trimZero();
    return a;
}

void BigInt::trimZero() {
    for (int i = digits - 1; i >= 0; i--) {
        if (data[i] != 0) {
            digits = i + 1;
            return;
        }
    }
    digits = 1;
}

bool BigInt::operator>(const BigInt &b) const {
    if (!sign && b.sign) {
        return true;
    } else if (sign && !b.sign) {
        return false;
    }
    if (this->digits == b.digits) {
        for (int i = this->digits - 1; i >= 0; i--) {
            if (this->data[i] != b.data[i]) {
                if (sign)
                    return this->data[i] < b.data[i];
                else
                    return this->data[i] > b.data[i];
            }
        }
    }
    if (sign) {
        return this->digits < b.digits;
    } else {
        return this->digits > b.digits;
    }
}

BigInt BigInt::multiply(const BigInt &other) const {
    BigInt res(0);
    if(this->sign ^ other.sign){
        res.sign = 1;
    }
    int size = this->digits + other.digits;
    auto * multiArray = new int[size]();
    for(int i = 0; i < this->digits; i++) {
        for (int j = 0; j < other.digits; j++) {
            multiArray[i + j] += this->data[i] * other.data[j];
        }
    }
    int i = 0;
    int carry = 0;
    for(; i < size; i++){
        int sum = (multiArray[i] + carry);
        res.data[i] = sum % this->base;
        carry = sum / this->base;
    }
    while(carry > 0){
        res.data[i++] = carry % this->base;
        carry /= this->base;
    }
    res.digits = i;
    res.trimZero();
    delete multiArray;
    return res;
}

BigInt BigInt::divide(const BigInt &other) const {
	BigInt res(0);
	res.sign = this->sign ^ other.sign;
	if(other > *this)
		return res;
}

BigInt BigInt::modular(const BigInt &) const {
	return BigInt(0);
}


#endif //OJONLY_BIGINT_H
