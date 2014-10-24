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

//const vector<string> Index::ftrs_bow = {"Plot"};
const string Index::file_name_voc="voc.txt";
const string Index::file_name_idxfilm="idx_film.txt";
const string Index::file_name_idxterm="idx_term.txt";

Index::Index(const vector<string> x):ftrs_bow(x){
    buffer_chaves = new char*[TAM_VOC];
    contaPalavras = 1;
}

void Index::read_movie(string line,vector<int>& pos_key_bow){

    string item_id,item_info;
    char* palavra = new char[MAIOR_PALAVRA+2];
    vector<string> tok_line;

    tokenize(line,'{',tok_line);
   // cout<<"-->"<<tok_line.size()<<endl;

    item_id = tok_line.front();
    int item_id_int = atoi(item_id.c_str());
    vector<string> keys;
    vector<string> values;
    string dict = "{" + tok_line.back();

    tokenize_dict(dict,keys,values);
    //nenhum valor...nada a mapear
    if (values.size() == 0){
	return;
    }

    //descobrir qual eh a posicao dos campos desejados para bag-of-words
    //caso ainda nao tenha sido feito ainda
    if (pos_key_bow.size() == 0){
         vector<string>::iterator it_keys = keys.begin();
         vector<string>::iterator it_keys_end = keys.end();

         vector<string>::iterator it_ftrs_bow_end = ftrs_bow.end();
         ///cout<<"==> "<<pos_key_bow.size()<<" "<<keys.size()<<endl;
         for(int i=0;it_keys!=it_keys_end;it_keys++,i++){
             vector<string>::iterator it_ftrs_bow = ftrs_bow.begin();

	     while(it_ftrs_bow!=it_ftrs_bow_end){
                  //if (item_id_int == 1)
		  //   cout<<">>>"<<(*it_keys)<<" "<<(*it_ftrs_bow)<<endl;
	         if (*it_keys == *it_ftrs_bow){
		    pos_key_bow.push_back(i);
		    break;
	         }
	         it_ftrs_bow++;
	    }
         }
    }

    //apos descobrir a posicao das chaves a serem usadas no bow,
    //vamos tokenizar estes campos (values) e colocar nos indices
    vector<int>::iterator it_pos_key_bow = pos_key_bow.begin();
    vector<int>::iterator it_pos_key_bow_end = pos_key_bow.end();
    //cout<<"Comecou loop das chaves"<<endl;
    while (it_pos_key_bow!=it_pos_key_bow_end){
	vector<string> tokens;

	//cout<<"Comecou a tokenizar valores "<<(*it_pos_key_bow)<<" "<<values.size()<<endl;
	tokenize(values.at(*it_pos_key_bow),' ',tokens);
	//cout<<"Terminou de tokenizar valores"<<endl;
	//cout<<"==>"<<tokens.size()<<endl;
	vector<string>::iterator it_tokens = tokens.begin();
	vector<string>::iterator it_tokens_end = tokens.end();

	while (it_tokens!=it_tokens_end){
	    memset(palavra,'\0',MAIOR_PALAVRA+2);
	    copy((*it_tokens).begin(),(*it_tokens).end(),palavra);

	    int tamanho_palavra = strlen(palavra);

	    if (palavra!=NULL && tamanho_palavra!=0){
		char* tmp = strdup(palavra);
		converteParaMinusculo_char(tmp);
		strcpy(palavra,tmp);
		if (tmp!=NULL) free(tmp);

		//a palavra ainda nao esta no vocabulario
		if (vocabulario.find(palavra) == vocabulario.end()){
		    buffer_chaves[contaPalavras] = new char[tamanho_palavra+1];
		    memset(buffer_chaves[contaPalavras],'\0',tamanho_palavra+1);
		    strncpy(buffer_chaves[contaPalavras],palavra,tamanho_palavra);

		    vocabulario[buffer_chaves[contaPalavras]] = contaPalavras;
		    vocabulario_invertido[contaPalavras] = buffer_chaves[contaPalavras];
		    //cout<<"-->"<<buffer_chaves[contaPalavras]<<" "<<vocabulario[buffer_chaves[contaPalavras]]<<endl;

		    //indexando por filme e por termo
		    //cout<<"--> "<<item_id<<" "<<item_id_int<<endl;
		    if (idx_film_term[item_id_int].find(contaPalavras) == idx_film_term[item_id_int].end()){ 
		           idx_film_term[item_id_int][contaPalavras] = 1;
		    }else{
		           idx_film_term[item_id_int][contaPalavras] += 1;
		    }
		    idx_term_film[contaPalavras].push_back(item_id_int);
		    contaPalavras++;
		}else{
		    //palavra ja esta no vocabulario
		     int idpalavra = vocabulario[palavra];
		     if (idx_film_term[item_id_int].find(idpalavra) == idx_film_term[item_id_int].end()){ 
		          idx_film_term[item_id_int][idpalavra] = 1;
		     }else{
		          idx_film_term[item_id_int][idpalavra] += 1;
		     }
		     idx_term_film[idpalavra].push_back(item_id_int);
		}
	    }
	    it_tokens++;
	    //passando nos tokens do campo dado das features do item
	}
	//passando pelos campos desejados do item
	it_pos_key_bow++;
	//cout<<"Terminou loop das chaves"<<endl;
    }

    if (palavra!=NULL) delete[] palavra;
    //cout<<"Terminou read_movie"<<endl;
}

void Index::read(string file_name){
    ifstream data(file_name);
    //posicao das features desejadas e definidas como constantes
    vector<int> pos_key;

    if (data.is_open()){
	string linha;
	while(getline(data,linha)){
	    //cout<<linha<<endl;
	    read_movie(linha,pos_key);
	    linha.clear();
	}
    }
    data.close();
    //cout<<"Terminou read"<<endl;
}

void Index::write_voc(){
    ofstream fd_voc(file_name_voc,ios::out);

    if (fd_voc.is_open()){
	int i = 1;
	int nterms = vocabulario_invertido.size();
	while (i<nterms){
	    fd_voc << vocabulario_invertido[i] << " " << vocabulario[vocabulario_invertido[i]]<<endl;
	    i++;
	}
    }
    int n = vocabulario.size();
    if (buffer_chaves !=NULL){
         for(int i=0;i<n;i++){
	     if (buffer_chaves[i] !=NULL) 
		delete[] buffer_chaves[i];
	 }
         delete[] buffer_chaves;
    }
         
     

    fd_voc.close();
}

void Index::write_idx_film(){
    ofstream fd_idx_film(file_name_idxfilm,ios::out);

    if (fd_idx_film.is_open()){
         unordered_map<int,unordered_map<int,int> >::iterator it_idx_film = idx_film_term.begin();
         unordered_map<int,unordered_map<int,int> >::iterator it_idx_film_end = idx_film_term.end();
	// cout<<"-->"<<idx_film_term.size()<<endl;
	 while (it_idx_film!=it_idx_film_end){
	     fd_idx_film << it_idx_film->first;

	     unordered_map<int,int>::iterator it_terms = it_idx_film->second.begin();
	     unordered_map<int,int>::iterator it_terms_end = it_idx_film->second.end();
	     
	     while (it_terms!=it_terms_end){
		 fd_idx_film << " "<< (*it_terms).first << " " <<  (*it_terms).second;
		 it_terms++;
	     }
	     fd_idx_film << endl;
	     it_idx_film++;
	 }
    }

    fd_idx_film.close();
}

void Index::write_idx_term(){
    ofstream fd_idx_term(file_name_idxterm,ios::out);

    if (fd_idx_term.is_open()){
         unordered_map<int,vector<int> >::iterator it_idx_term = idx_term_film.begin();
         unordered_map<int,vector<int> >::iterator it_idx_term_end = idx_term_film.end();
	 while (it_idx_term!=it_idx_term_end){
	     fd_idx_term << it_idx_term->first;

	     vector<int>::iterator it_film = it_idx_term->second.begin();
	     vector<int>::iterator it_film_end = it_idx_term->second.end();
	     
	     while (it_film!=it_film_end){
		 fd_idx_term << " "<< (*it_film);
		 it_film++;
	     }
	     fd_idx_term << endl;
	     it_idx_term++;
	 }
    }

    fd_idx_term.close();
}

void Index::read_voc(){
    ifstream fd_voc(file_name_voc,ios::in);

    if (fd_voc.is_open()){

	char* palavra = new char[MAIOR_PALAVRA+2]();
	string linha;
	vector<string> toks;
	int i = 1;

	while(getline(fd_voc,linha)){
	    tokenize(linha,' ',toks);
	    string term,num;

	    num = toks.back();
	    toks.pop_back();

	    term = toks.back();
	    toks.pop_back();


	    memset(palavra,'\0',MAIOR_PALAVRA+2);
	    copy(term.begin(),term.end(),palavra);

	    if (palavra!=NULL){
		int tamanho_palavra = strlen(palavra)+1;
		memset(buffer_chaves[i],'\0',tamanho_palavra+1);
		strncpy(buffer_chaves[i],palavra,tamanho_palavra);
		vocabulario[buffer_chaves[i]] = i;
		vocabulario_invertido[i] = buffer_chaves[i];
	    }
	    toks.clear();
	}
    }

    fd_voc.close();
}

void Index::read_idx_film(){
    ifstream fd_film(file_name_idxfilm,ios::in);

    if (fd_film.is_open()){
	string linha;
	vector<string> toks;
	while (getline(fd_film,linha)){
	    unordered_map<int,int> lst_terms;
	    tokenize(linha,' ',toks);

	    //lendo a lista de termos associado ao item, que eh o 
	    //primeiro elemento ds lidys toks
	    string t;
	    while (toks.size()!=1){

		t = toks.back();
		toks.pop_back();
		int freq = atoi(t.c_str());

		t = toks.back();
		toks.pop_back();
		int term = atoi(t.c_str());

		lst_terms[term] = freq;
	    }
	    t = toks.back();
            toks.pop_back();

	    int item = atoi(t.c_str());

	    idx_film_term[item] = lst_terms;
	}
    }
    fd_film.close();
}

void Index::read_idx_term(){
    ifstream fd_term(file_name_idxterm,ios::in);

    if (fd_term.is_open()){
	string linha;
	vector<string> toks;
	while (getline(fd_term,linha)){
	    vector<int> lst_items;
	    tokenize(linha,' ',toks);

	    //lendo a lista de termos associado ao item, que eh o 
	    //primeiro elemento ds lidys toks
	    string t;
	    while (toks.size()!=1){

		t = toks.back();
		toks.pop_back();

		lst_items.push_back(atoi(t.c_str()));
	    }
	    t = toks.back();
            toks.pop_back();

	    int term = atoi(t.c_str());

	    idx_term_film[term] = lst_items;
	}
    }
    fd_term.close();
}

unordered_map<int,int> Index::get_term_list(int item){
    return idx_film_term[item];
}
