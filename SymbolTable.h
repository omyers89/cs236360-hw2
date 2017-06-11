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
	IdType t;
	int offset;
} VarData;

class Table {
private:
	map<string, VarData>* _vars;
	
	list<scopeType>* scopeList;
public: 
	Table* _parentTable;
	Table(Table* parentTable, scopeType newScopeType = _IF);
	bool get(string varName, VarData& dat);
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
	vector<Table*> _tableStack;
public:
	void push(Table* t);
	bool pop();
	Table* top();
	Table* get(int i);
};


class SymbolTable{
private:
	Tables _tables;
	Offsets _offsetes;
	
	bool GetFunc(string name, IdType &funType);
public:
	//bool findVarByName(string name);

	bool EndProg(); //just pop tables and offsets
	SymbolTableResult AddFunc(string name, varType retType, map<varType,string> &args);
	SymbolTableResult CallFunc(string name, vector<varType> &callArgs, vector<varType> &expectedArgs, varType &ret);

	bool OpenScope();//make new table, add to tables and update offsets
	bool AddVar(string name, varType t); //insert at top table (name, tyoe, offset), and update offset
	bool GetVar(string name, varType& outVarType); //return a reference to the object, or null and false otherwise
	//bool UpdateVar(string name, VarData newData);
};

#endif //_TABLES_H_
