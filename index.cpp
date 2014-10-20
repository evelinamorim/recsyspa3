/*
 * =====================================================================================
 *
 *       Filename:  index.cpp
 *
 *    Description:  classe que indexa conteudo de filmes
 *
 *        Version:  1.0
 *        Created:  10/20/14 10:45:09
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  evelinamorim, 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "index.h"

using namespace std;

void Index::read_movie(string line){
    istringstream ss(line);

    string item_id,item_info;

    ss >> item_id;
    ss >> item_info;

    vector<string> keys;
    vector<string> values;

    tokenize_dict(item_info,keys,values);

    //por enquanto usar so o plot e tokenizar as palavras dele
    vector<string>::iterator it_keys = keys.begin();
    vector<string>::iterator it_keys_end = keys.end();
}

void Index::read(string file_name){
    ifstream data(file_name);

    if (data.is_open()){
	string linha;
	while(get_line(data,linha)){
	    read_movie(linha);
	    linha.clear();
	}
    }
    data.close();
}

