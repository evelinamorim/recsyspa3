/*
 * =====================================================================================
 *
 *       Filename:  evaluation.h
 *
 *    Description:  header da classe de avaliacao
 *
 *        Version:  1.0
 *        Created:  10/28/14 21:22:53
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <fstream>
#include <unordered_map>

#include "util.h"

using namespace std;

#ifndef __EVALUATION_H_
#define __EVALUATION_H_

typedef struct item_rate{
    int item;
    int rate;
}Item_Rate;

class Evaluation{
    public:
    unordered_map<int,vector<Item_Rate> >  read_ground_truth(string truth_file);
    unordered_map<int,vector<Item_Rate> > read_prediction(string predict_file);
    float rmse(unordered_map<int,vector<Item_Rate> > gt,unordered_map<int,vector<Item_Rate> > p);
};

#endif
