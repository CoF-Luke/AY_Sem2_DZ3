#ifndef __classes__
#define __classes__

//#include "header.hpp"
#include<string>
using namespace std;

class Encryptor //Абстрактный класс
{
protected:
    string info;
    int len_info;
public:
    Encryptor();
    Encryptor(string info);
    virtual ~Encryptor();
    virtual void encript()=0; //ЧВФ
    string get_info();
};


class Block_Encryptor : public Encryptor //Наследуемый класс
{
private:
    string key;
    int len_key;
public:
    Block_Encryptor();
    Block_Encryptor(string info, string key);
    virtual ~Block_Encryptor();//Должна быть виратульной пример 3 лаба

    void shift_to_right();
    void encript();
};


class Stream_Encryptor : public Encryptor //Наследуемый класс
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