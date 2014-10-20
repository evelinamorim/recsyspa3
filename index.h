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

#include "util.h"

using namespace std;

#ifndef __INDEX_H_
#define __INDEX_H_

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

    //indice filme->termos
    unordered_map<int,vector<int> > idx_film_term;

    //indice term->film
    unordered_map<int,vector<int> > idx_term_film;

    public:
        //essa funcao recebe uma linha com info de um filme e 
	//separa esta info para poder mapear 
	void read_movie(string line);
	void read(string file_name);
};

#endif
