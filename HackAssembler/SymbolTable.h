#ifndef SymbolTable_H
#define SymbolTable_H

#include <string>
#include <unordered_map>

using namespace std;



struct SymbolTable {
	unordered_map<string, int> table;

	void addEntry(string symbol, int address) {
		table[symbol] = address;
	}

	bool contains(string symbol) {
		return table.count(symbol);
	}

	int getAdrress(string symbol) {
		return table[symbol];
	}
};
#endif // !SymbolTable_H
