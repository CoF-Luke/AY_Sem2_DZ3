//#include "header.hpp"
#include "classes.h"

//����������� ������� ������������ ������
Encryptor::Encryptor()
{
    info = "";
    len_info = 0;
}
Encryptor::Encryptor(string info)
{
    this->info = info;
    len_info = info.length();
}
Encryptor::~Encryptor()//�����?
{
    info = "";
    len_info = 0;
}
string Encryptor::get_info()
{
    return info;
}

//����������� ������� ������������ ������ ��� ��������� ����������
Block_Encryptor::Block_Encryptor() : Encryptor()
{
    key = "";
    len_key = 0;
}
Block_Encryptor::Block_Encryptor(string info, string key) : Encryptor(info)
{
    this->key = key;
    len_key = key.length();
}
Block_Encryptor::~Block_Encryptor()//������ ������� ���������� ��� ������, �������� ������ ���� �������� ��� virtual
{
    key = "";
    len_key = 0;
}

void Block_Encryptor::encript() //������� ���������
{
    string result = "";
    for (size_t i = 0; i < (len_info / len_key); ++i) //����� �� ����� �����
    {
        for (size_t j = (i * len_key); j < ((i + 1) * len_key); ++j) //������ ������ �����
        {
            result += (char)(info[j] ^ key[j-(i*len_key)]);
        }

        shift_to_right(); //����� ����� ������
    }
    for (size_t j = ((len_info / len_key) * len_key), z = 0; j < len_info; ++j, ++z) //������ �� ������� �� ������ ������
    {
        result += (char)(info[j] ^ key[z]);
    }


    info = result;
    result = ""; //������� ������
}

void Block_Encryptor::shift_to_right() //������� ������ ����� ������ �� 1 ��� (����������)
{
    bool last_bit = (key.back() & 1); //��������� ��������� ���
    for (size_t i = key.size() - 1; i > 0; --i) //�������� � ������ ������� ���� ������
    {
        key[i] = (key[i] >> 1) | ((key[i - 1] & 1) << 7);
    }
    key[0] = (key[0] >> 1) | (last_bit << 7); //�������� � ������ ������� ���� ������ � ��������� � ������ ���������� ���
    last_bit = 0; //������� ������
}

/*void Block_Encryptor::shift_to_right() //������� ������ ����� ������ �� 1 ������
{
    char last_char = key.back();
    key.pop_back();
    key.insert(key.begin(), last_char);
}*/



//����������� ������� ������������ ������ ��� ��������� ����������
Stream_Encryptor::Stream_Encryptor() : Encryptor()
{
    key_symbol = "";
    key_sequence = "";
}
Stream_Encryptor::Stream_Encryptor(string info, string key_symbol) : Encryptor(info)
{
    this->key_symbol = key_symbol;
    key_sequence = "";
}
Stream_Encryptor::~Stream_Encryptor()
{
    key_symbol = "";
    key_sequence = "";
}

void Stream_Encryptor::make_key_sequence() //������� ��� �������� �������� ������������������ �� ������������ ����� �����
{
    string result = key_symbol;
    for (size_t i = 1; i < len_info; ++i)
    {
        result += ((result[i - 1] * 13) % 256);
    }
    key_sequence = result;
    result = ""; //������� ������
}

void Stream_Encryptor::encript() //������� ���������
{
    make_key_sequence(); //�������� �������� ������������������

    string result = "";
    for (size_t i = 0; i < len_info; ++i) //����� �� ����� �����
    {
        result += (char)(info[i] ^ key_sequence[i]);
    }

    info = result;
    result = ""; //������� ������
}