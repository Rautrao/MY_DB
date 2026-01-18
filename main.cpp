#include<iostream>
#include<algorithm>
#include<utility>
#include<cstdlib>
#include<fstream>
#include<iomanip>
#include<sstream>
#include<cctype>
#include"./declaration/dec.hpp"
using namespace std;

int main(int argc,char* argv[]) {
    string path = "data/student.csv";
    if(argc!=2) {
        cout<<"Invalid argc"<<"\n";
        exit(0);
    }
    string query = argv[1];
    DataManager d(path,query);
    vector<string> selectedHeaders;
    vector<int> selectedIdx;
    if (d.getAttribute().find('*')!=std::string::npos) {
        selectedHeaders=d.headers;
        for(int i=0;i<d.headers.size();i++) {
            selectedIdx.push_back(i);
        } 
    }  else {
        vector<string> cols = d.split(d.getAttribute(), ',');
        for (auto& c : cols) {
            c.erase(remove(c.begin(), c.end(), ' '), c.end());
            selectedHeaders.push_back(c);
            selectedIdx.push_back(find(d.headers.begin(), d.headers.end(), c) - d.headers.begin());
        }
    }

    vector<vector<string>> result;
    for(vector<string> row:d.relation) {
        if(!d.hasWhere || d.evaluateCondition(row)) {
            vector<string> temp;
            for(int a:selectedIdx) {
                temp.push_back(row[a]);
            }
            result.push_back(temp);
        }
    } 
    d.printTable(selectedHeaders,result);
    return 0;
}