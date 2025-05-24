#include "header.hpp"
#include "classes.hpp"

vector<string> read_from_files(string file_info, string file_key)
{
    vector<string> data(2);

    //Открытие info файла
    ifstream bin(file_info, ios::binary);

    if (!bin) throw invalid_argument("Error: File dont exist...");

    bin.seekg(0, ios::end);
    streampos file_size = bin.tellg();
    bin.seekg(0, ios::beg);
    
    if (file_size == 0) throw invalid_argument("Error: File is empty...");
    if (file_size > 1024) throw invalid_argument("Error: The file size is more than 1024...");

    data[0].resize(file_size);

    bin.read(&data[0][0], file_size);

    bin.close();

    cout << data[0] << endl;

    //Открытие key файла
    ifstream bin2(file_key, ios::binary);

    if (!bin2) throw invalid_argument("Error: File dont exist...");

    bin2.seekg(0, ios::end);
    file_size = bin2.tellg();
    bin2.seekg(0, ios::beg);
    
    if (file_size == 0) throw invalid_argument("Error: File is empty...");
    if (file_size > 1024) throw invalid_argument("Error: The file size is more than 1024...");

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
    
    bout << info;

    bout.close();

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