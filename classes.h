#pragma once
#ifndef __classes__
#define __classes__

//#include "header.hpp"
#include<string>
using namespace std;

class Encryptor //����������� �����
{
protected:
    string info;
    int len_info;
public:
    Encryptor();
    Encryptor(string info);
    virtual ~Encryptor();
    virtual void encript() = 0; //���
    string get_info();
};


class Block_Encryptor : public Encryptor //����������� �����
{
private:
    string key;
    int len_key;
public:
    Block_Encryptor();
    Block_Encryptor(string info, string key);
    ~Block_Encryptor();

    void shift_to_right();
    void encript();
};


class Stream_Encryptor : public Encryptor //����������� �����
{
private:
    string key_symbol;
    string key_sequence;
public:
    Stream_Encryptor();
    Stream_Encryptor(string info, string key_symbol);
    virtual ~Stream_Encryptor();

    void make_key_sequence();
    void encript();
};

#endif
