#include "header.hpp"
#include "classes.hpp"

vector<string> read_from_files(string file_info, string file_key)
{
    vector<string> data(2);

    ifstream bin(file_info);
    bin >> data[0];
    bin.close();

    ifstream bin2(file_key);
    bin2 >> data[1];
    bin2.close();

    //Копирование входных данный в другой файл для недопущения случайной потери данных...
    ofstream bout("file_copy_input_info");
    bout << data[0];
    bout.close();

    return data;
}

void write_to_file(string file_info, string info)
{
    ofstream bout(file_info);
    bout << info;
}

void encr_block(string file_info, string file_key, Encryptor * encr)
{
    string info = "", key = "";
    vector<string> data = read_from_files(file_info, file_key);
    info = data[0];
    key = data[1];

    encr = new Block_Encryptor(info, key);

    encr->encript();

    write_to_file(file_info, encr->get_info());
}


void encr_stream(string file_info, string file_key, Encryptor * encr)
{
    string info = "", key = "";
    vector<string> data = read_from_files(file_info, file_key);
    info = data[0];
    key = data[1];

    encr = new Stream_Encryptor(info, key);

    //Добавить проверку на (len_key < len_info)
    //encr->make_key_sequence(); //так делать нельзя, так как make... не переопределена

    encr->encript();

    write_to_file(file_info, encr->get_info());
}