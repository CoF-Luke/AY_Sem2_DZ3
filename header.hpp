#ifndef __header__
#define __header__

#include<iostream>
#include<fstream>
#include<string>
#include<vector>

#include "classes.hpp"

using namespace std;

vector<string> read_from_files(string file_info, string file_key);
void write_to_file(string file_info, string info);

void encr_block(string file_info, string file_key, Encryptor * encr);
void encr_stream(string file_info, string file_key, Encryptor * encr);


#endif