/*
 * =====================================================================================
 *
 *       Filename:  index.h
 *
 *    Description:  classe header para indexacao
 *
 *        Version:  1.0
 *        Created:  10/20/14 10:45:34
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstring>

#include "util.h"

using namespace std;

#ifndef __INDEX_H_
#define __INDEX_H_

#define MAIOR_PALAVRA 600
#define TAM_VOC 200000

struct  eqstr {
    inline bool operator() (char const *s1,char const *s2) const {
	// cout << "==> " << s1 << " " << " "  << s2 << " " << strcmp(s1,s2) << endl;
	 if (s1==NULL){
	     if (s2==NULL){
		 return true;
	     }else return false;
	 }

	 if (s2==NULL){
	     return false;
	 }

	 int len1 = strlen(s1);
	 int len2 = strlen(s2);

	 if (len1 == 0){
	     if (len2 == 0){
		 return true;
	     }else return false;
         }
	 if (len2 == 0)  return false;
	 int min = len1 < len2 ? len1:len2; 

	 //problema aqui: Invalid read of size 1
	 return strcmp(s1,s2)==0;
    }
}; 

struct Hash_Func{
       int operator() (char* k) const{
	   string s("");
	   stringstream ss;


	   if (k != NULL){
	      s.reserve(strlen(k)+1);
	      ss << k; //problema aqui
	      ss >> s;// assuming k is a C-string
	   }
	   static hash<string> hash_function; // standard hashing functor
           int h = hash_function(s);
	   return h;
	}
     
};

class Index{
    //cabecalho que um dado filme tem no arquivo de conteudo
    vector<string> header;

    //vocabulario construido que associa termo com um numero
    unordered_map<char*,int, Hash_Func,eqstr> vocabulario;
    unordered_map<int,char*> vocabulario_invertido;
    char** buffer_chaves;

    //indice filme->termos
    unordered_map<int,unordered_map<int,int> > idx_film_term;

    //indice term->film
    unordered_map<int,vector<int> > idx_term_film;

    //campos de features a serem considerados para o bag of words
    vector<string> ftrs_bow;

    static const string file_name_voc;
    static const string file_name_idxfilm;
    static const string file_name_idxterm;

    int contaPalavras;

    public:
        Index(const vector<string> x);
        //essa funcao recebe uma linha com info de um filme e 
	//separa esta info para poder mapear 
	void read_movie(string line,vector<int>& pos_key_bow);
	void read(string file_name);

	void write_voc();
	void write_idx_film();
	void write_idx_term();

	void read_voc();
	void read_idx_film();
	void read_idx_term();
};

#endif
