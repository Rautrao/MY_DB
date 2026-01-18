#include<vector>
#include<string>
#include<fstream>
#ifndef DEC_HPP
#define DEC_HPP

class DataManager{
    private:

        std::relationName;  //table name
        std::string query;  //query string
        std::ifstream file; //file 
        std::vector<std::vector<std::string>> relation; //store table data
        std::vector<std::string> qTokens; // tokens form query
        std::vector<std::string> headers; // attributes names
        bool isFIleOpen; // is file open 
        bool hasSelect;  // check if select is present in query 
        bool hasWhere;  // heck if where is present in query
        bool hasForm;  //check if Form is presen in query
        int selectPos; // Position of select
        int formPos;   // position of string "FROM"
        int wherePos;  // position of strin "WHERE"
        void getRelation();  //member function
        std::string getAttribute();  // string between SELECT AND FORM
        std::string tableName(); //string after Form and before where(if exist)
        std::string whereColumn, whereOp, whereValue; // condition 
        void isValidQuery();  // check if query is valid
        void evaluateCondition(); //evaluates condition
        std::vector<std::string> split(const string&,char);  //splits the given string wherever encountered a delimeter
        bool isNumber(const string&);  //checks if given string is number  
    public:
        DataManager(const string& rel,const string& q);
        void printTable(const vector<vector<string>>&);
}
#endif //DEC_HPP