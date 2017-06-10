
#include "SymbolTable.h"
#include <exception>

using namespace std;
using namespace std::exception;

Table::Table(Table* parentTable, scopeType newScopeType):
															_parentTable(parentTable)
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

void Offsets::pop(){
	if (_offsetsStack.size() == 0){
		throw new exception("trying to pop empty stack Offsets");
	}
	_offsetsStack.pop();
}

int& Offsets::top(){
	if (_offsetsStack.size() == 0){
		throw new exception("trying to top empty stack");
	}
	return _offsetsStack.top();
}

void Tables::push(Table t){
	_tableStack.push_front(t);
}

void Tables::pop(){
	if (_tableStack.size() == 0){
		throw new exception("trying to pop empty stack- Tables");
	}
	_tableStack.pop_front();

}

Table& Tables::get(int i){
	if (_tableStack.size() >= (unsigned)i){
		throw new exception("invalid index- get tables");
	}
	list<Table>::iterator it;
	advance(it, i);
	return *it;
}


bool SymbolTable::EndProg(){
	cout << "in EndProg:" << endl;
	return true;
}
SymbolTableResult SymbolTable::AddFunc(string name, funcType t){
	cout << "in AddFunc:" << endl;
	return SUCCESS;
}

SymbolTableResult SymbolTable::CallFunc(string name, funcType ftStruct){
	cout << "in CallFunc:" << endl;
	return SUCCESS;
}



	bool SymbolTable::OpenScope(){
		cout << "in OpenScope:" << endl;
		return SUCCESS;
	}

	bool SymbolTable::AddVar(string name, varType t){
		cout << "in AddVar:" << endl;
		return true;
	}
	bool SymbolTable::GetVar(string name){
		cout << "in GetVar:" << endl;
		return true;
	}
	bool SymbolTable::UpdateVar(string name, VarData newData){
		cout << "in UpdateVar:" << endl;
		return true;
	}