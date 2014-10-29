/*
 * =====================================================================================
 *
 *       Filename:  main_recommend.cpp
 *
 *    Description:  arquivo principal para recomendacao
 *
 *        Version:  1.0
 *        Created:  10/23/14 18:58:07
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

int main(int argc,char** argv){

    if (argc != 4){
	cout<<"*** Error *** Worng Number of Arguments "<<endl;
	cout<<"Usage: ./tp3-rating <users> <items> <ratings> "<<endl;
	return -1;
    }

    string arquivoUsers = argv[1];
    string arquivoItem = argv[2];
    string arquivoRate = argv[3];

    vector<string> ftrs;
    ftrs.push_back("Plot");

    Recommend rec_obj = Recommend(ftrs);

    rec_obj.read_users(arquivoUsers);
    //TODO: Esta funcao nao esta pronta
    rec_obj.read_items(arquivoItem);
    rec_obj.read_ratings(arquivoRate);

    rec_obj.compute_user_feature();
    rec_obj.predict();
    return 0;
}

