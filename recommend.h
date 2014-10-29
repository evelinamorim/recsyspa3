/*
 * =====================================================================================
 *
 *       Filename:  recommend.h
 *
 *    Description:  header para as funcoes de recomendacao
 *
 *        Version:  1.0
 *        Created:  10/23/14 13:12:03
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <unordered_map>
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <string>
#include "index.h"

#ifndef __RECOMMEND_H_
#define __RECOMMEND_H_

//numero de itens preditos a serem escritos no 
//arquivo de predicoes por usuario
#define NPRED 100
//nota maxima que um item pode ter
#define MAX_RATE 5

typedef struct user_list{
    float rating;
    long unsigned int ts;
}User_List; 


typedef struct item_rate{
    int item;
    float rate;
}Item_Rate;

class Recommend{
    vector<int> users;
    Index idx_obj;
    //matriz de utilidade: usuario x itens
    unordered_map<int,unordered_map<int,User_List> > util_matrix;
    //matrix de user feature
    unordered_map<int,unordered_map<int,float> > user_matrix;
    static const string prediction_file;

    public:
    Recommend(const vector<string> x);
    void read_users(string file_name);
    void read_items(string file_name);
    void read_ratings(string file_name);

    void compute_user_feature();
    float compute_item_score(unordered_map<int,float> user,unordered_map<int,float> item);
    void predict();

    void print_predictions(unordered_map<int,vector<Item_Rate> > pl);
    void write_predictions(unordered_map<int,vector<Item_Rate> > pl);
};

#endif
