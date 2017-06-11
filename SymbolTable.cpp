
#include "SymbolTable.h"
#include <exception>

using namespace std;

Table::Table(Table* parentTable, scopeType newScopeType) : _parentTable(parentTable)
{
	_vars = new(map<string, VarData>);
	scopeList = new (list<scopeType>);
}

Table::~Table()
{
	delete(_vars);
	delete(scopeList);
}

bool Table::get(string varName, VarData& dat){
	if (!contains(varName)){
		return false;
	}
	VarData vd = _vars->find(varName)->second;
	dat.t = vd.t;
	dat.offset = vd.offset;
	return true;
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
	int curOffset;
	if (_offsetsStack.size() == 0 || isFunc){
		curOffset = 0;
	}
	else { curOffset = _offsetsStack.top(); }
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

void Tables::push(Table* t){
	_tableStack.push_back(t);
}

bool Tables::pop(){
	if (_tableStack.size() == 0){
		//throw new exception("trying to pop empty stack- Tables");
		return false;
	}
	_tableStack.pop_back();
	return true;
}

Table* Tables::top(){
	if (_tableStack.size() == 0){ return NULL; }
	return _tableStack.back();
}

Table* Tables::get(int i){
	if ((unsigned)i >= _tableStack.size()){
		return NULL;
	}
	vector<Table*>::iterator it = _tableStack.begin();
	advance(it, i);
	return *it;
}


bool SymbolTable::EndProg(){
	return _tables.pop() && _offsetes.pop();
}



//bool SymbolTable::findVarByName(string name){
//
//	return true;
//}

SymbolTableResult SymbolTable::AddFunc(string name, varType newRetType, map<string,varType> &newArgs){
	//TODO:[TIO]<-[NOAM] newArgs is now a map type with <type,name>.
	IdType idt;
	if (GetFunc(name, idt)){
		return FAIL;
	}
	IdType newIdType;
	newIdType.retType = newRetType;
	newIdType.args = newArgs;
	
	VarData newVarData;
	newVarData.t = newIdType;
	newVarData.offset = 0;
	
	Table* newTable = new Table(_tables.top(), _FUNC);

	newTable->addVar(name, newVarData);
	_tables.push(newTable);
	return SUCCESS;
}

bool CompareVecs(vector<varType> &callArgs, vector<varType> &expectedArgs){
	vector<varType>::iterator it_c = callArgs.begin();
	vector<varType>::iterator it_e = expectedArgs.begin();
	while (it_c != callArgs.end() && it_e != expectedArgs.end())
	{
		if (*it_c != *it_e){ return false; }
		it_c++;
		it_e++;
	}
	if (it_c == callArgs.end() && it_e == expectedArgs.end()){
		return true;
	}
	
}

SymbolTableResult SymbolTable::CallFunc(string name, vector<varType> &callArgs, vector<varType> &expectedArgs, varType &ret){

	IdType funkyType;
	bool exist = GetFunc(name, funkyType);
	if (exist){
		expectedArgs = funkyType.args;
		ret = funkyType.retType;
		if (CompareVecs(callArgs,expectedArgs)){
			return SUCCESS;
		}
		else
		{
			return PROTOTYPE_MISMATCH;
		}
	}
	return NOT_DEFINED;
}

bool SymbolTable::GetFunc(string name, IdType &funType){
	Table* curTable = _tables.top();
	while (curTable != NULL){
		VarData vd;
		if (curTable->get(name, vd)){
			funType = vd.t;
			return true;
		}
		curTable = curTable->_parentTable;
	}
	return false;

}


bool SymbolTable::OpenScope(){
	Table* nt = new Table(_tables.top());
	_tables.push(nt);
	_offsetes.push(false);
	return true;
}

bool SymbolTable::AddVar(string name, varType t){
	IdType idt;
	if (GetFunc(name, idt)){
		return FAIL;
	}
	VarData vd;
	IdType it;
	it.retType = t;
	vd.t = it;
	vd.offset = _offsetes.top();
	_tables.top()->addVar(name, vd);
	_offsetes.top()++;
	return true;
}
bool SymbolTable::GetVar(string name, varType& outVarType){
	IdType idt;
	bool ex = GetFunc(name, idt);
	outVarType = idt.retType;
	return ex;
}


//bool SymbolTable::UpdateVar(string name, VarData newData){
//	cout << "in UpdateVar:" << endl;
//	return true;
//}