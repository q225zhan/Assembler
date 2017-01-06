#include "kind.h"
#include "lexer.h"
#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <map>
// Use only the neeeded aspects of each namespace
using std::string;
using std::vector;
using std::endl;
using std::cerr;
using std::cin;
using std::getline;
using ASM::Token;
using ASM::Lexer;
using namespace std;

int main(int argc, char* argv[]){
  // Nested vector representing lines of Tokens
  // Needs to be used here to cleanup in the case
  // of an exception
  vector< vector<Token*> > tokLines;
  try{
    // Create a MIPS recognizer to tokenize
    // the input lines
    Lexer lexer;
    // Tokenize each line of the input
    string line;
    while(getline(cin,line)){
      tokLines.push_back(lexer.scan(line));
    }

    // Iterate over the lines of tokens and print them
    // to standard error
    vector<vector<Token*> >::iterator it;
    int v= 0;
    int w = 0;
    map<string,int> labels;
    for(it = tokLines.begin(); it != tokLines.end(); ++it){
      string word=".word";
      vector<Token*>::iterator it2;
      for(it2 = it->begin(); it2 != it->end(); ++it2){
        if(((*it2)->getKind()==ASM::DOTWORD)){
         if(labels.count((*it2)->getLexeme())==1){
            string error="ERROR";
            throw error;
          }
          else{
            word="num";
          }
        }else if(word=="num"){
          if(((*it2)->getKind()!= ASM::INT) &&((*it2)->getKind()!= ASM::HEXINT) && ( (*it2)->getKind()!= ASM::ID )){
            string error="ERROR";
            throw error;
          }else if((it2 == it->end()-1)){
              v+=4;
          }else{
              string error="ERROR";
              throw error;
          }
        }
        else if((*it2)->getKind()== ASM::LABEL){
          if(it2!=it->begin()){
            if((*(it2-1))->getKind()!=ASM::LABEL){
              string error="ERROR";
              throw error;
            }
          }
          if(labels.count((*it2)->getLexeme())==1){
            string error="ERROR";
            throw error;
          }
          string label=(*it2)->getLexeme();
          labels[label]=v;
        }
        else if((*it2)->getKind()== ASM::ID){
          if((*it2)->getLexeme()=="jr"||(*it2)->getLexeme()=="jalr"){
            if(it->size()!=2){
              string e = "ERROR";
              throw e;
            }
            ++it2;
            if((it2 == it->end()-1)&&(*it2)->getKind()== ASM::REGISTER){
              v+=4;
            }else{
              string e = "ERROR";
              throw e;
            }
          }
          else if((*it2)->getLexeme()=="add"||(*it2)->getLexeme()=="sub"||(*it2)->getLexeme()=="slt"||(*it2)->getLexeme()=="sltu") {
            if(it->size()!=6){
              string e = "ERROR";
              throw e;
            }
            ++it2;
            if((*it2)->getKind()!=ASM::REGISTER){
              string e = "ERROR";
              throw e;
              }
            ++it2;
            if((*it2)->getKind()!=ASM::COMMA){
              string e = "ERROR";
              throw e;
            }
            ++it2;
            if((*it2)->getKind()!=ASM::REGISTER){
              string e = "ERROR";
              throw e;
            }
            ++it2;
            if((*it2)->getKind()!=ASM::COMMA){
              string e = "ERROR";
              throw e;
            }
            ++it2;
            if((*it2)->getKind()!=ASM::REGISTER){
              string e = "ERROR";
              throw e;
            }    
            v+=4;
          }
          else if((*it2)->getLexeme()=="lw"||(*it2)->getLexeme()=="sw"){
            if(it->size()!=7){
              string e = "ERROR";
              throw e;
            }
            ++it2;
            if((*it2)->getKind()!=ASM::REGISTER){
              string e = "ERROR";
              throw e;
            }
            ++it2;
            if((*it2)->getKind()!=ASM::COMMA){
              string e = "ERROR";
              throw e;
            }
            ++it2;
            if((*it2)->getKind()!=ASM::INT&&(*it2)->getKind()!=ASM::HEXINT){
              string e = "ERROR";
              throw e;
            }
            ++it2;
            if((*it2)->getKind()!=ASM::LPAREN){
              string e = "ERROR";
              throw e;
            }
            ++it2;
            if((*it2)->getKind()!=ASM::REGISTER){
              string e = "ERROR";
              throw e;
            }
            ++it2;
            if((*it2)->getKind()!=ASM::RPAREN){
              string e = "ERROR";
              throw e;
            }
            v+=4;
          }
          else if((*it2)->getLexeme()=="beq"||(*it2)->getLexeme()=="bne"){
            if(it->size()!=6){
              string e = "ERROR";
              throw e;
            }
            ++it2;
            if((*it2)->getKind()!=ASM::REGISTER){
              string e = "ERROR";
              throw e;
            }
            ++it2;
            if((*it2)->getKind()!=ASM::COMMA){
              string e = "ERROR";
              throw e;
            }
            ++it2;
            if((*it2)->getKind()!=ASM::REGISTER){
              string e = "ERROR";
              throw e;
            }
            ++it2;
            if((*it2)->getKind()!=ASM::COMMA){
              string e = "ERROR";
              throw e;
            }
            ++it2;
            if(((*it2)->getKind()!= ASM::INT &&(*it2)->getKind()!= ASM::HEXINT&&(*it2)->getKind()!= ASM::ID)){
              string e = "ERROR";
              throw e;
            }
            v+=4;
          }
          else if((*it2)->getLexeme()=="lis"||(*it2)->getLexeme()=="mflo"||(*it2)->getLexeme()=="mfhi"){
              if(it->size()!=2){
              string e = "ERROR";
              throw e;
            }
            it2++;
            if((*it2)->getKind()!=ASM::REGISTER){
              string e = "ERROR";
              throw e;
            }
          }
          else if((*it2)->getLexeme()=="mult"||(*it2)->getLexeme()=="multu"||(*it2)->getLexeme()=="div"||(*it2)->getLexeme()=="divu"){
            if(it->size()!=4){
              string e = "ERROR";
              throw e;
            }
            ++it2;
            if((*it2)->getKind()!=ASM::REGISTER){
              string e = "ERROR";
              throw e;
            }
            ++it2;
            if((*it2)->getKind()!=ASM::COMMA){
              string e = "ERROR";
              throw e;
            }
            ++it2;
            if((*it2)->getKind()!=ASM::REGISTER){
              string e = "ERROR";
              throw e;
            }
          }
          else{
              string e = "ERROR";
              throw e;
          } 
        }
        else {
          string e = "ERROR";
            throw e;
        }
        
      }
      
    }
    for(it = tokLines.begin(); it != tokLines.end(); ++it){
      vector<Token*>::iterator it2;
      for(it2 = it->begin(); it2 != it->end(); ++it2){
        if((*it2)->getKind()== ASM::DOTWORD){         
          ++it2;
          if(it2 == it->end()-1&&(*it2)->getKind()== ASM::ID ){
            string s = (*it2)->getLexeme()+":";
            if(labels.count(s)==0){
                string e = "ERROR";
                throw e;
            }
              int inst = labels[s];
              putchar((inst>>24) & 0xff);
              putchar((inst>>16) & 0xff);
              putchar((inst>>8) & 0xff);
              putchar(inst & 0xff);
          }
          w+=4;
        }
        else if((*it2)->getKind()== ASM::ID){
          if((*it2)->getLexeme()=="jr"){
            ++it2;
            int inst = ((*it2)->toInt() << 21) | 8;
            putchar((inst>>24) & 0xff);
            putchar((inst>>16) & 0xff);
            putchar((inst>>8) & 0xff);
            putchar(inst & 0xff);
          }
          else if((*it2)->getLexeme()=="jalr"){
            ++it2;
            int inst = ((*it2)->toInt() << 21) | 9;
            putchar((inst>>24) & 0xff);
            putchar((inst>>16) & 0xff);
            putchar((inst>>8) & 0xff);
            putchar(inst & 0xff);
          }
          else if((*it2)->getLexeme()=="add"){
            ++it2;
            int inst= ((*it2)->toInt() << 11) | ((*(it2+2))->toInt() << 21) | ((*(it2+4))->toInt() << 16) | 32;
            putchar((inst>>24) & 0xff);
            putchar((inst>>16) & 0xff);
            putchar((inst>>8) & 0xff);
            putchar(inst & 0xff);
            it2+=4;
          }
          else if((*it2)->getLexeme()=="sub"){
            ++it2;
            int inst= ((*it2)->toInt() << 11) | ((*(it2+2))->toInt() << 21) | ((*(it2+4))->toInt() << 16) | 34;
            putchar((inst>>24) & 0xff);
            putchar((inst>>16) & 0xff);
            putchar((inst>>8) & 0xff);
            putchar(inst & 0xff);
            it2+=4;
          }
          else if((*it2)->getLexeme()=="slt"){
            ++it2;
            int inst= ((*it2)->toInt() << 11) | ((*(it2+2))->toInt() << 21) | ((*(it2+4))->toInt() << 16) | 42;
            putchar((inst>>24) & 0xff);
            putchar((inst>>16) & 0xff);
            putchar((inst>>8) & 0xff);
            putchar(inst & 0xff);
            it2+=4;
          }
          else if((*it2)->getLexeme()=="sltu"){
            it2++;
            int inst= ((*it2)->toInt() << 11) | ((*(it2+2))->toInt() << 21) | ((*(it2+4))->toInt() << 16) | 43;
            putchar((inst>>24) & 0xff);
            putchar((inst>>16) & 0xff);
            putchar((inst>>8) & 0xff);
            putchar(inst & 0xff);
            it2+=4;
          }
          else if((*it2)->getLexeme()=="beq"){
            ++it2;
            int first = (*it2)->toInt();
            it2+=2;
            int second = (*it2)->toInt();
            it2+=2;
            if((*it2)->getKind()==ASM::ID){
              string s = (*it2)->getLexeme()+":";
              if(labels.count(s)==0){
                string e = "ERROR";
                throw e;
              }
              int third = (labels[s] - w)/4 - 1;
              if(third<0){
                third = third & 0xffff;
              }
              int inst=(4<<26) | (first << 21) | (second << 16) | third;
              putchar((inst>>24) & 0xff);
              putchar((inst>>16) & 0xff);
              putchar((inst>>8) & 0xff);
              putchar(inst & 0xff);
            }
            else{
              int third = (*it2)->toInt();
              if((!((*it2)->getKind()==ASM::INT&&third<=32767&&third >= -32768)) && (!((*it2)->getKind()==ASM::HEXINT&&third>=0&&third<=0xffff))){
                string e = "ERROR";
                throw e;
              }
              if(third<=0){
                third = third & 0xffff;
              }
              int inst=(4<<26) | (first << 21) | (second << 16) | third;
              putchar((inst>>24) & 0xff);
              putchar((inst>>16) & 0xff);
              putchar((inst>>8) & 0xff);
              putchar(inst & 0xff);
            }       
          }
          else if((*it2)->getLexeme()=="bne"){
            ++it2;
            int first = (*it2)->toInt();
            it2+=2;
            int second = (*it2)->toInt();
            it2+=2;
            if((*it2)->getKind()==ASM::ID){
              string s = (*it2)->getLexeme()+":";
              if(labels.count(s)==0){
                string e = "ERROR";
                throw e;
              }
              int third = (labels[s] - w)/4 - 1;
              if(third<0){
                third = third & 0xffff;
              }
              int inst=(5<<26) | (first << 21) | (second << 16) | third;
              putchar((inst>>24) & 0xff);
              putchar((inst>>16) & 0xff);
              putchar((inst>>8) & 0xff);
              putchar(inst & 0xff);
            }
            else{
              int third = (*it2)->toInt();
              if((!((*it2)->getKind()==ASM::INT&&third<=32767&&third >= -32768)) && (!((*it2)->getKind()==ASM::HEXINT&&third>=0&&third<=0xffff))){
                string e = "ERROR";
                throw e;
              }
              if(third<0){
                third = third & 0xffff;
              }
              int inst=(5<<26) | (first << 21) | (second << 16) | third;
              putchar((inst>>24) & 0xff);
              putchar((inst>>16) & 0xff);
              putchar((inst>>8) & 0xff);
              putchar(inst & 0xff);
            }
          }
          else if((*it2)->getLexeme()=="lis"){
            it2++;  
            int inst= ((*it2)->toInt() << 11) |20;        
            putchar((inst>>24) & 0xff);
            putchar((inst>>16) & 0xff);
            putchar((inst>>8) & 0xff);
            putchar(inst & 0xff);
          }
          else if((*it2)->getLexeme()=="mflo"){
            it2++;  
            int inst= ((*it2)->toInt() << 11) | 18;            
            putchar((inst>>24) & 0xff);
            putchar((inst>>16) & 0xff);
            putchar((inst>>8) & 0xff);
            putchar(inst & 0xff);
          }
          else if((*it2)->getLexeme()=="mfhi"){
            it2++;   
            int inst= ((*it2)->toInt() << 11) | 16; 
            putchar((inst>>24) & 0xff);
            putchar((inst>>16) & 0xff);
            putchar((inst>>8) & 0xff);
            putchar(inst & 0xff);
          }
          else if((*it2)->getLexeme()=="mult"){
            it2++;
            int inst= 24 | ((*it2)->toInt()<<21) | ((*(it2+2))->toInt()<<16);
            putchar((inst>>24) & 0xff);
            putchar((inst>>16) & 0xff);
            putchar((inst>>8) & 0xff);
            putchar(inst & 0xff);
            it2+=2;
          }
          else if((*it2)->getLexeme()=="multu"){
            ++it2;
            int inst= 25 | ((*it2)->toInt()<<21) | ((*(it2+2))->toInt()<<16);
            putchar((inst>>24) & 0xff);
            putchar((inst>>16) & 0xff);
            putchar((inst>>8) & 0xff);
            putchar(inst & 0xff);
            it2+=2;
          }
          else if((*it2)->getLexeme()=="div"){
            ++it2;
            int inst= 26 | ((*it2)->toInt()<<21) | ((*(it2+2))->toInt()<<16);
            putchar((inst>>24) & 0xff);
            putchar((inst>>16) & 0xff);
            putchar((inst>>8) & 0xff);
            putchar(inst & 0xff);
            it2+=2;
          }
          else if((*it2)->getLexeme()=="divu"){
            ++it2;
            int inst= 27 | ((*it2)->toInt()<<21) | ((*(it2+2))->toInt()<<16);
            putchar((inst>>24) & 0xff);
            putchar((inst>>16) & 0xff);
            putchar((inst>>8) & 0xff);
            putchar(inst & 0xff);
            it2+=2;
          }
          else if((*it2)->getLexeme()=="lw"){
            ++it2;
            int first = (*it2)->toInt();
            it2 += 2;
            int second = (*it2)->toInt();
            it2 += 2;
            int third = (*it2)->toInt();
            ++it2;
            if(second<0){
              second = second & 0xffff;
            }
            int inst = (35<<26) | (third<<21) | (first<<16) | second;
            putchar((inst>>24) & 0xff);
            putchar((inst>>16) & 0xff);
            putchar((inst>>8) & 0xff);
            putchar(inst & 0xff);
          }
          else if((*it2)->getLexeme()=="sw"){
            ++it2;
            int first = (*it2)->toInt();
            it2 += 2;
            int second = (*it2)->toInt();
            it2 += 2;
            int third = (*it2)->toInt();
            ++it2;
            if(second<0){
              second = second & 0xffff;
            }
            int inst = (43<<26) | (third<<21) | (first<<16) | second;
            putchar((inst>>24) & 0xff);
            putchar((inst>>16) & 0xff);
            putchar((inst>>8) & 0xff);
            putchar(inst & 0xff);
          }
          w += 4;
        }
      } 
    }
  } catch(const string& msg){
    // If an exception occurs print the message and end the program
    cerr << msg << endl;
  }
  // Delete the Tokens that have been made
  vector<vector<Token*> >::iterator it;
  for(it = tokLines.begin(); it != tokLines.end(); ++it){
    vector<Token*>::iterator it2;
    for(it2 = it->begin(); it2 != it->end(); ++it2){
      delete *it2;
    }
  }
}

