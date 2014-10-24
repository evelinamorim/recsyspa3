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
#include "index.h"

typedef struct user_list{
    float rating;
    long unsigned int ts;
}User_List; 

class Recommend{
    vector<int> users;
    Index idx_obj;
    //matriz de utilidade
    unordered_map<int,unordered_map<int,User_List> > util_matrix;
    //matrix de user feature
    unordered_map<int,unordered_map<int,float> > user_matrix;

    private:
    Recommend(const vector<string> x);
    void read_users(string file_name);
    void read_items(string file_name);
    void read_ratings(string file_name);

    void compute_user_feature();
    
};
