//#include "header.hpp"
#include "classes.hpp"

//Определение функций абстрактного класса
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
Encryptor::~Encryptor()
{
    info = "";
    len_info = 0;
}
string Encryptor::get_info()
{
    return info;
}

//Определение функций наследуемого класса для блокового шифрования
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
Block_Encryptor::~Block_Encryptor()
{
    key = "";
    len_key = 0;
}

void Block_Encryptor::encript() //Функция кодировки
{
    string result = "";
    for (size_t i = 0; i < (len_info / len_key); ++i) //Блоки по длине ключа
    {
        for(size_t j = (i * len_key); j < ((i + 1) * len_key); ++j) //Проход внутри блока
        {
            result += (char)(info[j] ^ key[j]);
        }

        shift_to_right(); //Сдвиг ключа вправо
    }
    for(size_t j = ((len_info / len_key) * len_key); j < len_info; ++j) //Проход по остатку от блоков справа
    {
        result += (char)(info[j] ^ key[j]);
    }

    info = result;
    result = ""; //Затирка данных
}

void Block_Encryptor::shift_to_right() //Функция сдвига ключа вправо на 1 бит (исправлено)
{
    bool last_bit = (key.back() & 1); //Сохраняем последний бит
    for(size_t i = key.size() - 1; i > 0; --i) //Сдвигаем в каждом символе биты вправо
    {
        key[i] = (key[i] >> 1) | ((key[i - 1] & 1) << 7);
    }
    key[0] = (key[0] >> 1) | (last_bit << 7); //Сдвигаем в первом символе биты вправо и добавляем в начало сохранённый бит
    last_bit = 0; //Затирка данных
}

/*void Block_Encryptor::shift_to_right() //Функция сдвига ключа вправо на 1 символ
{
    char last_char = key.back();
    key.pop_back();
    key.insert(key.begin(), last_char);
}*/



//Определение функций наследуемого класса для поточного шифрования
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

void Stream_Encryptor::make_key_sequence() //Функция для создания ключевой последовательности из изначального байта ключа
{
    string result = key_symbol;
    for (size_t i = 1; i < len_info; ++i)
    {
        result += ((result[i - 1] * 13) % 256);
    }
    key_sequence = result;
    result = ""; //Затирка данных
}

void Stream_Encryptor::encript() //Функция кодировки
{
    make_key_sequence(); //Создание ключевой последовательности

    string result = "";
    for (size_t i = 0; i < len_info; ++i) //Блоки по длине ключа
    {
        result += (char)(info[i] ^ key_sequence[i]);
    }

    info = result;
    result = ""; //Затирка данных
}