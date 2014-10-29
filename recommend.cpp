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

using namespace std;

const string Recommend::prediction_file="pred_toy.txt";

bool compare_rates(Item_Rate a,Item_Rate b){
    return a.rate>b.rate;
}

Recommend::Recommend(const vector<string> x):idx_obj(x){
}

void Recommend::read_users(string file_name){
    ifstream user_file(file_name,ios::in);


    if (user_file.is_open()){
	string line;
	while (getline(user_file,line)){
	    vector<string> tok;
	    tokenize(line,'|',tok);
	    users.push_back(atoi(tok.front().c_str()));
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

void Recommend::compute_user_feature(){

    //computar a matriz item feature usando o modulo index
    //TODO: liberar memoria deste vocabulario
    idx_obj.read_voc();
    idx_obj.read_idx_film();

    //iterar sobre a matriz de utilidades
    unordered_map<int,unordered_map<int,User_List> >::iterator it_util = util_matrix.begin();
    unordered_map<int,unordered_map<int,User_List> >::iterator it_util_end = util_matrix.end();

    //iterando sobre cada usuario da minha matriz de utilidade
    while (it_util!=it_util_end){

	//agora iterar sobre a matriz de itens de cada filme avaliado pelo 
	//usuario em questao
	unordered_map<int,User_List>::iterator it_rate_item = it_util->second.begin();
	unordered_map<int,User_List>::iterator it_rate_item_end = it_util->second.end();
	//para cada usuario u, percorrer cada item i avaliado por ele
	while(it_rate_item!=it_rate_item_end){
	    unordered_map<int,float> term_item = idx_obj.get_term_list(it_rate_item->first);
	    unordered_map<int,float>::iterator it_term_item = term_item.begin();
	    unordered_map<int,float>::iterator it_term_item_end = term_item.end();
            
	    //para cada item i avaliado, percorrer a lista de termos 
	    //de tal item
	    while (it_term_item!=it_term_item_end){
		float nitens_rated = it_util->second.size();

		if (user_matrix[it_util->first].find((*it_term_item).first) == user_matrix[it_util->first].end()){
		    //U_{u}{t} = (nota x freq_term)/qtd_itens_avaliados
		    //onde u eh um dado usuario e t eh um dado termo
	             user_matrix[it_util->first][(*it_term_item).first] = (util_matrix[it_util->first][it_rate_item->first].rating*it_term_item->second)/nitens_rated;
		}else{
		    //nota x freq_term/qtd_itens_avaliados
	             user_matrix[it_util->first][(*it_term_item).first] += (util_matrix[it_util->first][it_rate_item->first].rating*it_term_item->second)/nitens_rated;
		}
		it_term_item++;
	    }

	    it_rate_item++;
	}
	it_util++;
    }

}

float Recommend::compute_item_score(unordered_map<int,float> user,unordered_map<int,float> item){
    float sum = 0;
    float user_mod = 0;
    float item_mod = 0;

    unordered_map<int,float>::iterator it_user = user.begin();
    unordered_map<int,float>::iterator it_user_end = user.end();

    while(it_user!=it_user_end){
	// user feature do termo atual x item feature do termo atual
	if (item.find(it_user->first)!=item.end()){
	    //...mas apenas dos termos em comum
	     sum += (it_user->second)*(item[it_user->first]);
	     //cout<<"--> "<<sum<<" "<< (it_user->second)<<" "<<(item[it_user->first])<<endl;
	     user_mod += (it_user->second)*(it_user->second);
	     item_mod += (item[it_user->first])*(item[it_user->first]);
	}
	it_user++;
    }

    if (user_mod!=0 && item_mod!=0){
         return sum/(sqrt(user_mod)*sqrt(item_mod));
    }else return 0;
}

void Recommend::predict(){
   //para cada usuario...
   vector<int>::iterator it_user = users.begin();
   vector<int>::iterator it_user_end = users.end();
   int nitems = idx_obj.get_number_items();

   unordered_map<int,vector<Item_Rate> > predict_list;

   //...calcular a nota de filmes que nao foram vistos por estes usuarios
   while(it_user!=it_user_end){
       //para cada filme na base..
       int i = 1;
       while (i<=nitems){
	   //...caso it_user nao o tenha assistido...
	   if (util_matrix[(*it_user)].find(i) == util_matrix[(*it_user)].end()){
	       //calcular a nota de i para it_user

	       //o item i deve ser pego com get_term_list
	       Item_Rate r;
	       r.item = i;
	       r.rate = MAX_RATE*compute_item_score(user_matrix[(*it_user)],idx_obj.get_term_list(i));
	       predict_list[(*it_user)].push_back(r);
	   }
	   i++;
       }
       it_user++;
   }

   //ordenar as predicoes
   unordered_map<int,vector<Item_Rate> >::iterator it_predict = predict_list.begin();
   unordered_map<int,vector<Item_Rate> >::iterator it_predict_end = predict_list.end();
   while (it_predict!=it_predict_end){
       sort(it_predict->second.begin(),it_predict->second.end(),compare_rates);
       it_predict++;
   }
   cout<<"Predicoes "<<predict_list.size()<<endl;
   print_predictions(predict_list);
   write_predictions(predict_list);

}

void Recommend::print_predictions(unordered_map<int,vector<Item_Rate> > pl){

   unordered_map<int,vector<Item_Rate> >::iterator it_predict = pl.begin();
   unordered_map<int,vector<Item_Rate> >::iterator it_predict_end = pl.end();
   while (it_predict!=it_predict_end){
       vector<Item_Rate>::iterator it_pred = it_predict->second.begin();
       vector<Item_Rate>::iterator it_pred_end = it_predict->second.end();
       cout<<"User: "<<it_predict->first<<endl;
       while(it_pred!=it_pred_end){
	   cout<<it_pred->item<<" "<<it_pred->rate<<endl;
	   it_pred++;
       }
       it_predict++;
   }
}

void Recommend::write_predictions(unordered_map<int,vector<Item_Rate> > pl){
   ofstream pred_fd(prediction_file,ios::out);

   if (pred_fd.is_open()){

       unordered_map<int,vector<Item_Rate> >::iterator it_predict = pl.begin();
       unordered_map<int,vector<Item_Rate> >::iterator it_predict_end = pl.end();

       while (it_predict!=it_predict_end){
           vector<Item_Rate>::iterator it_pred = it_predict->second.begin();
           vector<Item_Rate>::iterator it_pred_end = it_predict->second.end();
          ///`<<"User: "<<it_predict->first<<endl;
	   int i = 0;
           while(it_pred!=it_pred_end){
	       pred_fd <<it_predict->first<<" "<<it_pred->item<<" "<<round(it_pred->rate)<<endl;
	       it_pred++;
	       i++;
	       if (i==NPRED) break;
           }
           it_predict++;
        }
   }

   pred_fd.close();
}
