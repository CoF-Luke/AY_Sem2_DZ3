#include"header.h"


int main(int argc, const char* argv[])
{
    /*if (argc != 4)
    {
        cout << "ERROR! Incorrect number of arguments..." << endl;
        return 1;
    }
    string type_encr = argv[1];
    string file_info = argv[2];
    string file_key = argv[3];*/

    string type_encr = "block";
    string file_info = "file_info.txt";
    string file_key = "file_key.txt";

    Encryptor* encr = nullptr;

    //cout << "Hello\n";//Для отладки
    if (type_encr == "block") encr_block(file_info, file_key, encr);
    else if (type_encr == "stream") encr_stream(file_info, file_key, encr);
    else cout << "ERROR! Incorrtct encryption type..." << endl << type_encr << endl;


    return 0;
}