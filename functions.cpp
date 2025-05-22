#include "header.hpp"
#include "classes.hpp"

vector<string> read_from_files(string file_info, string file_key)
{
    vector<string> data(2);
    /*char sign;

    ifstream bin(file_info);
    while (bin.peek() != EOF)
    {
        bin.read((char*)&sign, sizeof(sign));
        data[0] += sign;
    }
    bin.close();*/
    ifstream bin(file_info, ios::binary);

    bin.seekg(0, ios::end);
    streampos file_size = bin.tellg();
    bin.seekg(0, ios::beg);
    
    data[0].resize(file_size);

    bin.read(&data[0][0], file_size);

    bin.close();

    cout << data[0] << endl;
    /*ifstream bin2(file_key);
    while (bin2.peek() != EOF)
    {
        bin2.read((char*)&sign, sizeof(sign));
        data[1] += sign;
    }
    bin2.close();*/

    ifstream bin2(file_info, ios::binary);

    bin2.seekg(0, ios::end);
    file_size = bin2.tellg();
    bin2.seekg(0, ios::beg);
    
    data[1].resize(file_size);

    bin2.read(&data[1][0], file_size);

    bin2.close();

    //Копирование входных данный в другой файл для недопущения случайной потери данных...
    ofstream bout(file_info, ios::binary);
    
    bout.write(data[0].data(), data[0].size());

    bout.close();

    return data;
}

void write_to_file(string file_info, string info)
{
    cout << info << endl;
    ofstream bout(file_info, ios::binary);
    
    //bout.write(info.data(), info.size());
    bout << info;

    bout.close();
    /*for (size_t i = 0; i < info.length(); ++i)
    {
        bout.write((char*)&info[i], sizeof(info[i]));
    }
    bout.close();*/
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