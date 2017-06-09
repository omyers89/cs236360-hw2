
#include "SymbolTable.h"


Table::Table(Table* parentTable, scopeType newScopeType) :_parentTable(parentTable), _scopeType(newScopeType){}
	
//VarData Table::get(string varName){
//	
//	if (_vars.find(varName) == _vars.end()){
//		std::cout << "var name not found" << std::endl;
//		return null;
//	}
//};
bool Table::addVar(string name, VarData d)
{
	cout << "in addVar:" << endl;
	return true;
}
//{
//	if (contains(name))
//	{
//		return false;
//	}
//	
//}

bool Table::contains(string name)
{
	cout << "in contains:" << endl;
	return true;
}
//{
//	return (_vars.find(name) != _vars.end());
//}


void Offsets::push(bool isFunc){
		cout << "in push Offset:" << endl;
		return;
	}
void Offsets::pop(){
	cout << "in pop Offset:" << endl;
	return;
}
int& Offsets::top(){
	cout << "in top Offset:" << endl;
	int i = 1;
	return i;
}

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
	Table table;
	return table;
}


bool SymbolTable::EndProg(){
	cout << "in EndProg:" << endl;
	return true;
}
bool SymbolTable::AddFunc(string name, varType t){
	cout << "in AddFunc:" << endl;
	return true;
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