#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<algorithm>
#include<cctype>
using namespace std;
DataManager::DataManager(const string& rel):relation(rel),query(q) {
    file(relation);
    std::string line;
    isFIleOpen=file.is_open();
    getline(file,line);
    headers = split(line,',');  
    qTokens = split(query,' ');
    hasSelect = qTokens[0]=="SELECT";
    hasWhere = find(qTokens.being(),qTokens.end(),"WHERE") != qTokens.end();
    hasFrom=find(qTokens.begin(),qTokens.end(),"FROM") !=qTokens.end();
    if(hasSelect) selectPos = 0;
    if(hasWhere) wherePos = find(qTokens.begin(),qTokens.end(),"WHERE")-qTokens.begin();
    if(hasForm) formPos = find(qTokens.begin(),qTokens.end(),"FROM")-qTokens.begin();
    if(hasWhere) {
        whereColumn=qTokens[wherePos+1];
        whereOp=qTokens[wherePos+2];
        whereValue=qTokens[wherePos+3];
    }
}

void DataManager::getRelation() {
    std::string line;
    if(isFIleOpen) {
        while(getline(file,line)){
            relation.push_back(split(line,','));
        }
    } else {
        cout<<"File not opened"<<endl;
        exit(1);
    }
    return;
}

std::vector<std::string> split(const string& s,char c){
    std::stringstream buffer(s);
    std::vector<std::string> tokens;
    std::string token;
    while(std::getline(buffer,token,c)) {
        tokens.push_back(token);
    }
    return tokens;
} 

std::string Solution::getAttribute(){
    std::string columnPart = query.substr(7,query.find("FORM")-7);
    return columnPart;
}
std::string tableName(){
    std::string tn = qTokens[formPos+1]+".csv";
    return tn;
}

bool Solution::evaluateCondition(vector<string>& row) {
    string op = whereOp;    
    int p = headers.size();
    int idx = find(headers.begin(), headers.end(), column) - headers.begin();
    string cell = row[idx];
    if(isNumber(whereValue) && isNumber(cell)) {
        int a=stoi(cell);
        int b=stoi(whereValue);
        if(whereOp=="=" ) return a==b;
        if(whereOp==">") return a>b;
        if(whereOp=="<") return a<b;
    } else if(whereOp=="=") { 
        return cell==value;
    }
    return false;
}

bool DataManager::isNumber(const string& s) {
    return !s.empty() && std::all_for(s.begin(),s.end(),::isdigit);
}

void DataManager::printTable(const vector<vector<string>>& res) {


}