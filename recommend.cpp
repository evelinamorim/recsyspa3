/*
 * =====================================================================================
 *
 *       Filename:  recommend.cpp
 *
 *    Description:  funcoes que recomendam e auxiliam a recomendacao de itens 
 *    a usuarios
 *
 *        Version:  1.0
 *        Created:  10/23/14 13:11:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "recommend.h"

Recommend::Recommend(const vector<string> x):idx_obj(x){
}

void Recommend::read_users(string file_name){
    ifstream user_file(file_name,ios::in);

    if (user_file.is_open()){
	string line;
	while (getline(user_file,line)){
	    vector<string> tok;
	    tokenize(line,'|',tok);
	    users.push_back(atoi(line.front().c_str()));
	}
    }

    user_file.close();
}

void Recommend::read_items(string file_name){
    return;
}

void Recommend::read_ratings(string file_name){
    ifstream rate_file(file_name,ios::in);

    if (rate_file.is_open()){
	string line;
	while (getline(rate_file,line)){
	    vector<string> tok;
	    tokenize(line,'\t',tok);

	    User_List u;
	    int user_id,item_id;

	    u.ts = strtoul(tok.back().c_str(),NULL,0);
	    tok.pop_back();

	    u.rating = atof(tok.back().c_str());
	    tok.pop_back();

	    item_id = atoi(tok.back().c_str());
	    tok.pop_back();

	    user_id = atoi(tok.back().c_str());
	    tok.pop_back();

	    util_matrix[user_id][item_id] = u;
	}
    }

    rate_file.close();
}

void compute_user_feature(){

    //computar a matriz item feature usando o modulo index
    idx_obj.read_voc();
    idx_obj.read_idx_film();

    //iterar sobre a matriz de utilidades
    unordered_map<int,vector<User_List> >::iterator it_util = util_matrix.begin();
    unordered_map<int,vector<User_List> >::iterator it_util_end = util_matrix.end();

    //iterando sobre cada usuario da minha matriz de utilidade
    while (it_util!=it_util_end){

	//agora iterar sobre a matriz de itens de cada filme avaliado pelo 
	//usuario em questao
	unordered_map<int,User_List>::iterator it_rate_item = it_util->second.begin();
	unordered_map<int,User_List>::iterator it_rate_item_end = it_util->second.end();
	//para cada usuario u, percorrer cada item i avaliado por ele
	while(it_rate_item!=it_rate_item_end){
	    unordered_map<int,int> term_item = idx_obj.get_term_list(it_rate_item->first);
	    unordered_map<int,int>::iterator it_term_item = term_item.begin();
	    unordered_map<int,int>::iterator it_term_item_end = term_item.end();
            
	    //para cada item i avaliado, percorrer a lista de termos 
	    //de tal item
	    while (it_term_item!=it_term_item_end){

		if (user_matrix[it_util->first].find((*it_term_item).first) == user_matrix[it_util->first].end()){
		    //U_{u}{t} = nota x freq_term
		    //onde u eh um dado usuario e t eh um dado termo
	             user_matrix[it_util->first][(*it_term_item).first] = util_matrix[it_util->first][it_rate_item->first].rating*it_term_item->second;
		}else{
		    //nota x freq_term
	             user_matrix[it_util->first][(*it_term_item).first] += util_matrix[it_util->first][it_rate_item->first].rating*it_term_item->second;
		}
	    }

	    it_rate_item->rating*
	    it_rate_item++;
	}
	it_util++;
    }

}
