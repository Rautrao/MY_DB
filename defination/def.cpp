#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<iomanip>
#include<algorithm>
#include<cstdlib>
#include<cctype>
#include "../declaration/dec.hpp"
using namespace std;
DataManager::DataManager(string& rel,string& q):relationName(rel),query(q) {
    file.open(relationName);
    isFileOpen=file.is_open();
    if (!isFileOpen) {
        cout << "File not opened" << endl;
        exit(1);
    }
    std::string line;
    getline(file,line);
    getRelation();
    headers = split(line,',');  
    qTokens = split(query,' ');
    hasSelect = qTokens[0]=="SELECT";
    hasWhere = find(qTokens.begin(),qTokens.end(),"WHERE") != qTokens.end();
    hasFrom=find(qTokens.begin(),qTokens.end(),"FROM") !=qTokens.end();
    if(hasSelect) selectPos = 0;
    if(hasWhere) wherePos = find(qTokens.begin(),qTokens.end(),"WHERE")-qTokens.begin();
    if(hasFrom) fromPos = find(qTokens.begin(),qTokens.end(),"FROM")-qTokens.begin();
    if(hasWhere) {
        whereColumn=qTokens[wherePos+1];
        whereOp=qTokens[wherePos+2];
        whereValue=qTokens[wherePos+3];
    }
}

void DataManager::getRelation() {
    std::string line;
    while(getline(file,line)) relation.push_back(split(line,','));
    return;
}

std::vector<std::string> DataManager::split(const string& s,char c){
    std::stringstream buffer(s);
    std::vector<std::string> tokens;
    std::string token;
    while(std::getline(buffer,token,c)) {
        tokens.push_back(token);
    }
    return tokens;
} 

std::string DataManager::getAttribute(){
    std::string columnPart = query.substr(7,query.find("FROM")-7);
    return columnPart;
}
std::string DataManager:: tableName(){
    std::string tn = qTokens[fromPos+1]+".csv";
    return tn;
}

bool DataManager::evaluateCondition(const vector<string>& row) {
    string op = whereOp;    
    int p = headers.size();
    int idx = find(headers.begin(), headers.end(), whereColumn) - headers.begin();
    if (idx >= headers.size()) return false;

    string cell = row[idx];
    if(isNumber(whereValue) && isNumber(cell)) {
        int a=stoi(cell);
        int b=stoi(whereValue);
        if(whereOp=="=" ) return a==b;
        if(whereOp==">") return a>b;
        if(whereOp=="<") return a<b;
    } else if(whereOp=="=") { 
        return cell==whereValue;
    }
    return false;
}

bool DataManager::isNumber(const string& s) {
    return !s.empty() && all_of(s.begin(),s.end(),::isdigit);
}

void DataManager::printTable(const vector<string> &header,const vector<vector<string>>& res) {
    int cols=header.size();
    vector<int> width(cols);
    for(int i=0;i<cols;i++) width[i]=header[i].size();
    for (const vector<string>& row: res) {
        for(int i=0;i<row.size();i++) {
            width[i]=max(width[i],(int)(row[i].size()));
        }
    }
    //printing headers
    for(int i=0;i<cols;i++) 
        cout<<"| "<<setw(width[i])<<left<<header[i]<<" ";
    cout<<"|\n";    
    for(int i=0;i<cols;i++) 
        cout<<"|-"<<string(width[i],'-')<<'-';
    cout<<"|\n";
    //printing rows
    int n=res.size();
    for(int i=0;i<n;i++) {
        for (int j=0;j<cols;j++) {
            cout<<"| "<<setw(width[j])<<left<<res[i][j]<<" ";
        }
        cout<<"|\n";
    } 
}