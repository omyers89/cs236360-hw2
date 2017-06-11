
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
	if (_vars->size() == 0){
		return false;
	}
	return (_vars->find(name) != _vars->end());
}


void Offsets::push()
{
	int curOffset;
	if (_offsetsStack.size() == 0){
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




SymbolTableResult SymbolTable::AddFunc(string funcName, varType newRetType, varList &argNameTypes){
	//TODO:[TIO]<-[NOAM] newArgs is now a map type with <type,name>.
	IdType idt;
	if (GetFunc(funcName, idt)){
		return FAIL;
	}
	IdType newIdType;
	newIdType.retType = newRetType;
	newIdType.args = argNameTypes.argTypes;
	
	VarData newFuncData;
	newFuncData.t = newIdType;
	newFuncData.offset = 0;
		
	//Table* newFuncTable = new Table(_tables.top(), _FUNC);
	Table* newFuncVarsTable = new Table(_tables.top(), _FUNC);
	vector<string>::iterator namesIt = argNameTypes.argNames.begin();
	vector<varType>::iterator typesIt = argNameTypes.argTypes.begin();
	int noffset = 0;
	for (; namesIt != argNameTypes.argNames.end(); namesIt++, typesIt++){
		IdType nRetType;
		nRetType.retType = *typesIt;
		VarData nvarData;
		nvarData.t = nRetType;
		nvarData.offset = noffset;
		if (!newFuncVarsTable->addVar(*namesIt, nvarData)){
			return FAIL;
		}
		noffset--;
	}
	//_tables.push(newFuncTable);
	_tables.top()->addVar(funcName, newFuncData);
	_tables.push(newFuncVarsTable);
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
	return false;
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
	_offsetes.push();
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