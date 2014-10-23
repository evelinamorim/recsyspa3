/*
 * =====================================================================================
 *
 *       Filename:  util.h
 *
 *    Description:  header de funcoes uteis
 *
 *        Version:  1.0
 *        Created:  10/20/14 13:09:40
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
#include <locale>

using namespace std;
#ifndef __UTIL_H_
#define __UTIL_H_

void tokenize_dict(string& d,vector<string>& keys,vector<string>& values);
void converteParaMinusculo_char(char* s);
void tokenize(string s,char sep,vector<string>& tok);
#endif
