/**
 * @file Parser.cc
 * @brief Implementation of the Parser methods
 */

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <typeinfo>
#include <cctype>

#include "Parser.hh"
#include "Brain.hh"
#include "InstructionIF.hh"
#include "InstructionDB.hh"
#include "Instruction_add.hh"
#include "Instruction_sub.hh"
#include "Instruction_brk.hh"
#include "Instruction_cln.hh"
#include "Instruction_cra.hh"
#include "Instruction_crt.hh"
#include "Instruction_del.hh"
#include "Instruction_div.hh"
#include "Instruction_DST.hh"
#include "Instruction_ebk.hh"
#include "Instruction_GAP.hh"
#include "Instruction_GTA.hh"
#include "Instruction_iee.hh"
#include "Instruction_iel.hh"
#include "Instruction_ieL.hh"
#include "Instruction_ife.hh"
#include "Instruction_ifl.hh"
#include "Instruction_ifL.hh"
#include "Instruction_add.hh"
#include "Instruction_jmp.hh"
#include "Instruction_mul.hh"
#include "Instruction_put.hh"
#include "Instruction_ret.hh"
#include "Instruction_SIM.hh"
#include "Instruction_sub.hh"
#include "Instruction_wat.hh"

using namespace std;

#define MAXCHARACTERSPERLINE 1000

static bool isSpace(char c){

    return c == '\t' || c == ' ';
}

static bool readLine(vector<string> &out,string line){

    out.clear();
    bool empty = true;


    for(unsigned int i=0;i<line.size();i++){

        if(!isSpace(line[i])){

            out.push_back(string(""));
            while(!isSpace(line[i]) && i<line.size()){
                empty = false;
                out.back().push_back(line[i]);
                i++;
            }
        }
    }

    return !empty;
}

static bool isLabel(string str){

    return str[0] == '#';
    
}


//Macro to create and add one of the different instructions with
//the given number of parameters
#define ADD_INSTRUCTION(instruction,args,vec,current,words,icount,linenr)                   \
    vector<string> vals;                                                                    \
    int res;                                                                                \
    for(unsigned int i=1;i<=args;i++){                                                      \
        if(words.size() > current + i){                                                     \
            if(isLabel(words[current+i])){                                                  \
                if (labels.find(words[current+i]) != labels.end()) {                        \
                    vals.push_back(labels[words[current+i]]);                               \
                }                                                                           \
                else {                                                                      \
                    cerr << "Parser " << linenr << " : ";                                   \
                    cerr << "Label " << words[current+i] << " is not defined!" << endl;     \
                    goto cleanup;                                                           \
                }                                                                           \
            } else{                                                                         \
                vals.push_back(words[current+i]);                                           \
            }                                                                               \
        } else {                                                                            \
            cerr << "Parser " << linenr << " : ";                                           \
            cerr << "The function " << words[current];                                      \
            cerr << " takes " << args << " arguments." << endl;                             \
            goto cleanup;                                                                   \
        }                                                                                   \
    }                                                                                       \
    InstructionIF *ni = new instruction(&res,vals);                                         \
    if (res != 0) {                                                                         \
        cerr << "Parser " << linenr << " : ";                                               \
        cerr << "The function " << words[current] << " is not well formated\n" << endl;     \
        goto cleanup;                                                                       \
    } else ;                                                                                \
    vec.push_back(ni);                                                                      \
    icount++;


int Parser::parseFile(Brain **brainptr, string brainfile, int arguments) {

    vector<InstructionIF*> vec;
    vector<string> args;
    vector<string> words;
    map<string,string> labels;
    vector<string> lineContent;
    ifstream stream (brainfile.c_str(),std::ifstream::in);
    char line[MAXCHARACTERSPERLINE];
    int icount = 0;
    int current = 0;
    vector< vector<string> > file;
    int brk,ebk;
    brk = ebk = -1;

    if (!stream.is_open()) {
        cerr << "Parser: Could not open brain file " << brainfile << endl;
        return 1;
    }

    while((stream.getline(line,MAXCHARACTERSPERLINE).rdstate() & std::ifstream::failbit) == 0){

        if(readLine(lineContent,string(line))){

            current = 0;
            if(isLabel(lineContent[current])){

                stringstream s;
                s << file.size();
                labels[lineContent[current]] = s.str();
                current++;
            }

            file.push_back(vector<string>());

            for(int i=current;(unsigned int) i<lineContent.size();i++){

                file.back().push_back(lineContent[i]);
            }

        }
    }
    stream.close();

    for(int linenr=0;(unsigned int)linenr<file.size();linenr++){

        words = file[linenr];

        if(words[current].compare("add") == 0){
            ADD_INSTRUCTION(Instruction_add,3,vec,current,words,icount,linenr+1);
        }else if(words[current].compare("sub") == 0){
            ADD_INSTRUCTION(Instruction_sub,3,vec,current,words,icount,linenr+1);
        }else if(words[current].compare("mul") == 0){
            ADD_INSTRUCTION(Instruction_mul,3,vec,current,words,icount,linenr+1);
        }else if(words[current].compare("div") == 0){
            ADD_INSTRUCTION(Instruction_div,3,vec,current,words,icount,linenr+1);
        }else if(words[current].compare("ifL") == 0){
            ADD_INSTRUCTION(Instruction_ifL,3,vec,current,words,icount,linenr+1);
        }else if(words[current].compare("ifl") == 0){
            ADD_INSTRUCTION(Instruction_ifl,3,vec,current,words,icount,linenr+1);
        }else if(words[current].compare("ife") == 0){
            ADD_INSTRUCTION(Instruction_ife,3,vec,current,words,icount,linenr+1);
        }else if(words[current].compare("ieL") == 0){
            ADD_INSTRUCTION(Instruction_ieL,4,vec,current,words,icount,linenr+1);
        }else if(words[current].compare("iel") == 0){
            ADD_INSTRUCTION(Instruction_iel,4,vec,current,words,icount,linenr+1);
        }else if(words[current].compare("iee") == 0){
            ADD_INSTRUCTION(Instruction_iee,4,vec,current,words,icount,linenr+1);
        }else if(words[current].compare("jmp") == 0){
            ADD_INSTRUCTION(Instruction_jmp,1,vec,current,words,icount,linenr+1);
        }else if(words[current].compare("put") == 0){
            ADD_INSTRUCTION(Instruction_put,2,vec,current,words,icount,linenr+1);
        }else if(words[current].compare("crt") == 0){
            ADD_INSTRUCTION(Instruction_crt,2,vec,current,words,icount,linenr+1);
        }else if(words[current].compare("cra") == 0){
            ADD_INSTRUCTION(Instruction_cra,3,vec,current,words,icount,linenr+1);
        }else if(words[current].compare("del") == 0){
            ADD_INSTRUCTION(Instruction_del,1,vec,current,words,icount,linenr+1);
        }else if(words[current].compare("ret") == 0){
            ADD_INSTRUCTION(Instruction_ret,1,vec,current,words,icount,linenr+1);
        }else if(words[current].compare("wat") == 0){
            ADD_INSTRUCTION(Instruction_wat,0,vec,current,words,icount,linenr+1);
        }else if(words[current].compare("brk") == 0){
            ADD_INSTRUCTION(Instruction_brk,0,vec,current,words,icount,linenr+1);
            if (brk != -1)
                goto cleanup;
            brk = linenr;
        }else if(words[current].compare("ebk") == 0){
            ADD_INSTRUCTION(Instruction_ebk,0,vec,current,words,icount,linenr+1);
            if (ebk != -1)
                goto cleanup;
            ebk = linenr;
        }else if(words[current].compare("cln") == 0){
            ADD_INSTRUCTION(Instruction_cln,0,vec,current,words,icount,linenr+1);
        }else if(words[current].compare("DST") == 0){
            ADD_INSTRUCTION(Instruction_DST,3,vec,current,words,icount,linenr+1);
        }else if(words[current].compare("SIM") == 0){
            ADD_INSTRUCTION(Instruction_SIM,3,vec,current,words,icount,linenr+1);
        }else if(words[current].compare("GTA") == 0){
            ADD_INSTRUCTION(Instruction_GTA,2,vec,current,words,icount,linenr+1);
        }else if(words[current].compare("GAP") == 0){
            ADD_INSTRUCTION(Instruction_GAP,3,vec,current,words,icount,linenr+1);
        }else{
            cerr << "The instruction " << words[current] << " is not valid." << endl;
            goto cleanup;
        }
    }

    *brainptr = new Brain( vec );
    if (brk != -1) 
        (*brainptr)->setInstructionBreakPointer(brk);
    if (ebk != -1) 
        (*brainptr)->setInstructionErrorBreakPointer(ebk);

    return 0;

cleanup:
    for(int i=0;(unsigned int)i<vec.size();++i) {
        delete vec[i];
    }
    return 1;
}


int Parser::parseImmediate(void* value, string imed) {

    // Types of input available:
    // 1) Integer: numerical digits with or without a minus
    // 2) Double: numerical digits with or without a minus including a '.' character
    // 3) String: numbers or alphanumeric characters starting with a '*' character

    if (value == NULL) {
        return 1;
    }

    if (imed == "") {
        return 1;
    }

    int dot = -1;
    int int_val;
    double double_val;
    string string_val;
    istringstream converter(imed);

    if (imed[0] == '*') { // resolve string

        string_val = imed.substr(1);
        for(int i=0;(unsigned int) i<string_val.size();i++) {
            if (!(isdigit(string_val[i]) || isupper(string_val[i]) || islower(string_val[i])))
                return 1;
        }

        *(string*)value = string_val;
        return 0;
    }

    // check if there are only numerical values
    for(int i=0;(unsigned int) i<imed.size();i++) {
        if (imed[i] >= '0' && imed[i] <= '9') {
            // continue
        } else if (imed[i] == '.' && dot < 0 ) {
            dot = i;
        } else if (imed[i] == '-' && i == 0) {
            // continue
        } else
            return 1;
    }

    if (dot >= 0) { // resolve double

        if ( !(converter >> double_val) && converter.tellg() != (int) imed.size()) {
            return 1; // Cannot convert double
        }

        *(double*) value = double_val;
        return 0;
    }

    // resolve integer (remaining)

    if ( !(converter >> int_val) && converter.tellg() != (int) imed.size()) {
        return 1; // Cannot convert int
    }
    *(int*) value = int_val;
    return 0;
}

int Parser::parseGetTypeImmediate(ArgumentType *type, string imed) {

    if (type == NULL) {
        return 1;
    }

    if (imed == "") {
        return 1;
    }

    *type = NOTYPE;

    int dot = -1;
    int int_val;
    double double_val;
    string string_val;
    istringstream converter(imed);

    if (imed[0] == '*') { // resolve string
        string_val = imed.substr(1);
        for(int i=0;(unsigned int) i<string_val.size();i++) {
            if (!(isdigit(string_val[i]) || isupper(string_val[i]) || islower(string_val[i])))
                return 1;
        }

        *type = STRING;
        return 0;
    }


    for(int i=0;(unsigned int) i<imed.size();i++) {
        if (imed[i] >= '0' && imed[i] <= '9') {
            // continue
        } else if (imed[i] == '.' && dot < 0 ) {
            dot = i;
        } else if (imed[i] == '-' && i == 0) {
            // continue
        } else {
            return 1;
        }
    }

    if (dot >= 0) { // resolve double
        if ( !(converter >> double_val) && converter.tellg() != (int) imed.size()) {
            return 1; // Cannot convert double
        }

        *type = DOUBLE;
        return 0;
    }

    // resolve integer (remaining)
    if ( !(converter >> int_val) && converter.tellg() != (int) imed.size()) {
        return 1; // Cannot convert int
    }

    *type = INT;
    return 0;
}
