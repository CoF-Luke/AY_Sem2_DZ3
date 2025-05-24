#include"header.hpp"


int main(int argc, const char * argv[])
{
    try
    {
        if (argc != 4) throw invalid_argument("ERROR! Incorrect number of arguments...");
    }
    catch(const std::invalid_argument& e)
    {
        cerr << e.what() << endl;
        return 0;
    }

    string type_encr = argv[1];
    string file_info = argv[2];
    string file_key = argv[3];

    Encryptor * encr;

    try
    {
        if (type_encr == "block") encr_block(file_info, file_key, encr);
        else if (type_encr == "stream") encr_stream(file_info, file_key, encr);
        else throw invalid_argument("ERROR! Incorrect encryption type...");
    }
    catch(const std::invalid_argument& e)
    {
        cerr << e.what() << endl;
        delete encr;
        return 0;
    }

    delete encr;
    
    return 0;
}