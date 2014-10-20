/*
 * =====================================================================================
 *
 *       Filename:  util.cpp
 *
 *    Description:  funcoes uteis para o sistema
 *
 *        Version:  1.0
 *        Created:  10/20/14 13:08:08
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

using namespace std;

void tokenize_dict(string d,vector<string>& keys,vector<string>& values){
    //a partir de uma strinh que contem o formato de um dicionario tokeniza 
    //para um vetor de string de header e outro com os valores
   string::iterator it_d = d.begin();

   string word;
   while (true){
       //chaves
       if (*it_d == ',' || *it_d == '{'){
	   word = ""
           it_d++;
	   while (*it_d != ':' && *it_d!='}'){
	       word += *it_d;
	       it_d++;
	   }
	   keys.push_back(word);
       }
       //valores
       if (*it_d == ':'){
	   word = ""
           it_d++;
	   while (*it_d != ',' && *it_d!='}'){
	       word += *it_d;
	       it_d++;
	   }
	   values.push_back(word);
       }
       //fim
       if (*it_d == '}') break;

   }
}

