#ifndef _TABLES_H_
#define _TABLES_H_

#include <map>
#include <list>
#include <stack>
#include <iostream>
#include "Contracts.hpp"
using namespace std;

typedef enum{ SUCCESS,FAIL, NOT_DEFINED, PROTOTYPE_MISMATCH} SymbolTableResult;


struct IdType{
	varType retType;
	vector<varType> args;
};



typedef struct {
	varType t;
	int offset;
} VarData;

class Table {
private:
	map<string, VarData>* _vars;
	Table* _parentTable;
	list<scopeType>* scopeList;
public: 
	Table(Table* parentTable, scopeType newScopeType = _IF);
	VarData get(string varName);
	bool addVar(string name, VarData d);
	bool contains(string name);
	~Table();
};

class Offsets{
private:
	stack<int> _offsetsStack;
public:
	void push(bool isFunc);
	bool pop();
	int& top();

};

class Tables{
private:
	list<Table> _tableStack;
public:
	void push(Table t);
	bool pop();
	Table& get(int i);
};


class SymbolTable{
private:
	Tables _tables;
	Offsets _offsetes;
	bool findVarByName(string name);
public:
	bool EndProg(); //just pop tables and offsets
	SymbolTableResult AddFunc(string name, varType retType, vector<varType> &args);
	SymbolTableResult CallFunc(string name, vector<varType> callArgs, varType &retType, vector<varType> &expected);
	bool OpenScope();//make new table, add to tables and update offsets
	bool AddVar(string name, varType t); //insert at top table (name, tyoe, offset), and update offset
	bool GetVar(string name, varType& outVarType); //return a reference to the object, or null and false otherwise
	bool UpdateVar(string name, VarData newData);
};

#endif //_TABLES_H_
