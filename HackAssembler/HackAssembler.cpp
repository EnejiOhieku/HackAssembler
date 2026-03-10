// HackAssembler.cpp : Defines the entry point for the application.
//

#include "HackAssembler.h"
#include "Parser.h"
#include "Code.h"
#include "SymbolTable.h"

#include <string>
#include <bitset>



using namespace std;



string input_file = ".\\Add.asm", output_file;
SymbolTable symbol_table;
Parser parser;
Code code;

void initSymbolTable() {
	symbol_table.addEntry("SP", 0);
	symbol_table.addEntry("LCL", 1);
	symbol_table.addEntry("ARG", 2);
	symbol_table.addEntry("THIS", 3);
	symbol_table.addEntry("THAT", 4);
	symbol_table.addEntry("SCREEN", 0x4000);
	symbol_table.addEntry("KBD", 0x6000);
	
	for (int i = 0; i < 16; i++) symbol_table.addEntry("R" + to_string(i), i);
}

void firstPass() {
	int counter = 0;

	while (parser.hasMoreCommands()) {
		parser.advance();
		if (parser.commandType() == CommandType::L_COMMAND) {
			string label = parser.symbol();
			if (symbol_table.contains(label)) Code::syntax_error("Error: Label already declared", parser.get_line_number());

			symbol_table.addEntry(label, counter);
		}
		else counter++;
	}
}

void secondPass() {
	ofstream fs(output_file);
	static int n = 16;
	
	parser.reset();

	while (parser.hasMoreCommands()) {
		if (n == 0x4000) cout << "Warning The program exceeds 16k of ram memory" << endl;

		parser.advance();

		if (parser.commandType() == CommandType::C_COMMAND) {
			fs << "111" + code.comp(parser.comp()) + code.dest(parser.dest()) + code.jump(parser.jump()) << endl;
		}
		else if (parser.commandType() == CommandType::A_COMMAND) {
			string symbol = parser.symbol();

			bool is_digit = true;
			for (char c : symbol) is_digit &= (bool) isdigit(c);
			int value;

			if (!is_digit) {
				if (symbol_table.contains(symbol)) value = symbol_table.getAdrress(symbol);
				else {
					value = n++;
					symbol_table.addEntry(symbol, value);
				}
			}
			else value = stoi(symbol);
			bitset<16> bs(value);
			fs << bs.to_string() << endl;
		}
	}
	fs.close();
}


int main(int argc, char** argv) {
	//if (argc > 0) input_file = string(argv[0]);
	//if (argc > 1) output_file = string(argv[1]);
	//else if (input_file.size()) output_file = input_file.substr(0, input_file.find('.'))+".hack";
	output_file = input_file.substr(0, input_file.find('.')) + ".hack";

	cout << input_file << ' ' << output_file << endl;
	try {
		parser = Parser(input_file);
		initSymbolTable();
		firstPass();
		secondPass();
	}
	catch (exception e) {
		cout << "An Error Occurred!" << endl;
		cout << e.what() << endl;
	}

	cout << "Done Compiling..." << endl;
	return 0;
}
