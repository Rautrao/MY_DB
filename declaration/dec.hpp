#include<vector>
#include<string>
#include<fstream>
#include<sstream>

#ifndef DEC_HPP
#define DEC_HPP

class DataManager{
    public:
        std::string query;  //query string
        std::vector<std::string> qTokens; // tokens form query
        std::string relationName;  //table name
        std::ifstream file; //file 
        std::vector<std::vector<std::string>> relation; //store table data
        std::vector<std::string> headers; // attributes names
        bool isFileOpen; // is file open 

        bool hasSelect;  // check if select is present in query 
        bool hasWhere;  // heck if where is present in query
        bool hasFrom;  //check if Form is presen in query
        int selectPos; // Position of select
        int fromPos;   // position of string "FROM"
        int wherePos;  // position of strin "WHERE"
        void getRelation();  //member function
        std::string getAttribute();  // string between SELECT AND FORM
        std::string tableName(); //string after Form and before where(if exist)
        std::string whereColumn, whereOp, whereValue; // condition 
        void isValidQuery();  // check if query is valid
        std::vector<std::string> split(const std::string&,char);  //splits the given string wherever encountered a delimeter
        bool isNumber(const std::string&);  //checks if given string is number  
        DataManager(std::string& ,std::string&);
        bool evaluateCondition(const std::vector<std::string>& row); //evaluates condition
        void printTable (const std::vector<std::string>&,const std::vector<std::vector<std::string>>&); //prints table
};
#endif //DEC_HPP