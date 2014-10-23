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
#include <iostream>
#include "util.h"

void tokenize_dict(string& d,vector<string>& keys,vector<string>& values){
    //a partir de uma strinh que contem o formato de um dicionario tokeniza 
    //para um vetor de string de header e outro com os valores
   string::iterator it_d = d.begin();

   string word;
   int i = 1;
   while (true){
       
	word = "";
	if ((*it_d) == '{')  it_d++;//pulando a chave {
        if ((*it_d) == '"'){  
	    it_d++;//pulando as aspas que abrem o campo
	    if ((*it_d) == ',' || (*it_d) == ':'){
		//pulando a pontuacao e a aspas que abre o proximo campo
		it_d+=2;
	    }
	}
	while (*it_d != '"' && *it_d!='}'){
	    word += *it_d;
	    it_d++;
	}
	
	if (i%2 == 0){
	    //cout<<"Value: "<< word<< endl;
             values.push_back(word);
	} 	
	else{ 
	    //cout<<"Chave: "<< word<< endl;
	    keys.push_back(word);}
       //fim
       if (*it_d == '}') break;
       i++;
   }
}
void converteParaMinusculo_char(char* s){
    locale loc;
    if (s!=NULL){
	int n= strlen(s);
        for(int i=0;i<n;i++){
	     s[i] = use_facet<ctype<char> >(loc).tolower(s[i]);
	}
    }
}

void tokenize(string s,char sep,vector<string>& tok){
    string::iterator it_s = s.begin();
    string::iterator it_s_end = s.end();

    string word = "";

    while(it_s!=it_s_end){
	if ((*it_s) == sep){
	    if (word.size()>0) tok.push_back(word);
	    word = "";
	}else{
	    word += (*it_s);
	}
	it_s++;
    }

    if (word.size()>0) tok.push_back(word);
}
