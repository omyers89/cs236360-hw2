
#include "SymbolTable.h"

using namespace std;

Table::Table(Table* parentTable, int tableId, scopeType newScopeType):
															_tableId(tableId),
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
		throw new exception("trying to pop empty stack");
	}
	_offsetsStack.pop();
}

int& Offsets::top(){
	if (_offsetsStack.size() == 0){
		throw new exception("trying to top empty stack");
	}
	return _offsetsStack.top();
}

int Tables::TID = 0;
void Tables::push(Table t){
	cout << "in push Tables:" << endl;
	return;
}
void Tables::pop(){
	cout << "in pop Tables:" << endl;
	return;
}
Table& Tables::get(int i){
	cout << "in get Tables:" << endl;
	return Table(NULL,0);
}


bool SymbolTable::EndProg(){
	cout << "in EndProg:" << endl;
	return true;
}
AddFuncResult SymbolTable::AddFunc(string name, funcType t){
	cout << "in AddFunc:" << endl;
	return AF_SUCCESS;
}
	bool SymbolTable::OpenScope(){
		cout << "in OpenScope:" << endl;
		return true;
	}
	bool SymbolTable::AddVar(string name, varType t){
		cout << "in AddVar:" << endl;
		return true;
	}
	bool SymbolTable::GetVar(string name, VarData& outData){
		cout << "in GetVar:" << endl;
		return true;
	}
	bool SymbolTable::UpdateVar(string name, VarData newData){
		cout << "in UpdateVar:" << endl;
		return true;
	}