/*
 * =====================================================================================
 *
 *       Filename:  main_index.cpp
 *
 *    Description:  classe principal para indexacao
 *
 *        Version:  1.0
 *        Created:  10/21/14 16:27:08
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>
#include "index.h"

using namespace std;

int main(int argc,char** argv){


    string arquivoItem = argv[1];

    if (argc != 2){
	cout<<"*** Error *** Wrong Number of Arguments "<<endl;
	cout<<"Usage: ./tp3-index itemfilename "<<endl;
	return -1;
    }

    vector<string> ftrs;
    ftrs.push_back("Plot");

    Index idxObj = Index(ftrs);
    //leu o arquivo de itens e colocou na memoria
    idxObj.read(arquivoItem);
    idxObj.write_voc();
    idxObj.write_idx_film();
    idxObj.write_idx_term();
    //agora escrever em arquivo os indices
    return 0;
}
