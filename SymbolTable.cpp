
#include "SymbolTable.h"
#include <exception>

using namespace std;

Table::Table(Table* parentTable, scopeType newScopeType): _parentTable(parentTable)
{
	_vars = new(map<string, VarData>);
	scopeList = new (list<scopeType>);
}

Table::~Table()
{
	delete(_vars);
	delete(scopeList);
}

bool Table::addVar(string name, VarData d)
{
	if (contains(name))
	{
		return false;
	}
	(*_vars)[name] = d;
	return true;
	
}

bool Table::contains(string name)
{
	return (_vars->find(name) != _vars->end());
}


void Offsets::push(bool isFunc)
{
	int curOffset = _offsetsStack.top();
	if (isFunc) {
		curOffset = 0; //note: functions does not have offset.
	}
	_offsetsStack.push(curOffset);
}

bool Offsets::pop(){
	if (_offsetsStack.size() == 0){
		//throw new exception("trying to pop empty stack Offsets");
		return false;
	}
	_offsetsStack.pop();
	return true;
}

int& Offsets::top(){
	if (_offsetsStack.size() == 0){
		throw exception::exception();
	}
	return _offsetsStack.top();
}

void Tables::push(Table t){
	_tableStack.push_front(t);
}

bool Tables::pop(){
	if (_tableStack.size() == 0){
		//throw new exception("trying to pop empty stack- Tables");
		return false;
	}
	_tableStack.pop_front();
	return true;
}

Table& Tables::get(int i){
	if (_tableStack.size() >= (unsigned)i){
		throw exception::exception();
	}
	list<Table>::iterator it;
	advance(it, i);
	return *it;
}


bool SymbolTable::EndProg(){
	return _tables.pop() && _offsetes.pop();
}



bool SymbolTable::findVarByName(string name){

	return true;
}

SymbolTableResult SymbolTable::AddFunc(string name, varType retType, vector<varType> &args){
	if (! findVarByName(name)){
		return FAIL;
	}


}

SymbolTableResult SymbolTable::CallFunc(string name, varType retType, vector<varType> &args){
	cout << "in CallFunc:" << endl;
	return SUCCESS;
}



	bool SymbolTable::OpenScope(){
		cout << "in OpenScope:" << endl;
		return true;
	}

	bool SymbolTable::AddVar(string name, varType t){
		cout << "in AddVar:" << endl;
		return true;
	}
	bool SymbolTable::GetVar(string name, varType& outVarType){
		cout << "in GetVar:" << endl;
		return true;
	}
	bool SymbolTable::UpdateVar(string name, VarData newData){
		cout << "in UpdateVar:" << endl;
		return true;
	}