/*
 * =====================================================================================
 *
 *       Filename:  evaluation.cpp
 *
 *    Description:  classe que implementa a avaliacao para este trabalho
 *
 *        Version:  1.0
 *        Created:  10/28/14 21:22:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "evaluation.h"

unordered_map<int,vector<Item_Rate> > Evaluation::read_ground_truth(string truth_file){
    ifstream truth_fd(truth_file,ios::in);
    unordered_map<int,vector<Item_Rate> >  t;

    if (truth_fd.is_open()){

	string linha;
	while(getline(truth_fd,linha)){
	}
    }

    truth_fd.close();
}

unordered_map<int,vector<Item_Rate> > Evaluation::read_prediction(string predict_file){
}

float rmse(unordered_map<int,vector<Item_Rate> > gt,unordered_map<int,vector<Item_Rate> > p){
}


