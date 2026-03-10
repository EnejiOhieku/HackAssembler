#ifndef Parser_H
#define Parser_H

#include <string>
#include <vector>
#include <fstream>
#include "CommandType.h"

using namespace std;




struct Parser {
	vector<string> commands;
	vector<int> line_number;

	int instruction_ptr = -1;

	Parser() {}

	Parser(string filePath) {
		ifstream fs(filePath);
		if (!fs.is_open()) {
			cerr << "Failed to open file: " << filePath << endl;
			exit(1);
		}

		int i = 1;
		string line;
		while (getline(fs, line)) {
			// Remove comments and whitespace
			size_t commentPos = line.find("//");
			if (commentPos != string::npos) {
				line = line.substr(0, commentPos);
			}
			line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
			if (!line.empty()) {
				commands.push_back(line);
				line_number.push_back(i);
			}
			i++;
		}
	}

	bool hasMoreCommands() {
		return instruction_ptr < (int)commands.size()-1;
	}

	void advance() {
		instruction_ptr++;
	}
	
	CommandType commandType() {
		string command = commands[instruction_ptr];
		if (command[0] == '@') return CommandType::A_COMMAND;
		if (command[0] == '(' && command.back() == ')') return CommandType::L_COMMAND;
		return CommandType::C_COMMAND;
	}
	
	string symbol() {
		string command = commands[instruction_ptr];
		CommandType command_type = commandType();

		if (command_type == CommandType::A_COMMAND) return command.substr(1, command.size() - 1);
		if (command_type == CommandType::L_COMMAND) return command.substr(1, command.size() - 2);

		throw runtime_error("Parser: Using Symbol() on a C-instruction.");
	}


	string dest() {
		if (commandType() != CommandType::C_COMMAND) throw runtime_error("Parser: Dest Operation Invalid on non C-instruction");

		string command = commands[instruction_ptr];
		size_t eq_pos = command.find('=');
		if (eq_pos == string::npos) return "null";
		return command.substr(0, eq_pos);
	}

	string comp() {
		if (commandType() != CommandType::C_COMMAND) throw runtime_error("Parser: Comp Operation Invalid on non C-instruction");

		string command = commands[instruction_ptr];

		size_t eq_pos = command.find("=");
		size_t  colon_pos = command.find(";");
		if (colon_pos == string::npos) colon_pos = command.size();

		return command.substr(eq_pos + 1, colon_pos - eq_pos - 1);
	}


	string jump() {
		if (commandType() != CommandType::C_COMMAND) throw runtime_error("Parser: Dest Operation Invalid on non C-instruction");

		string command = commands[instruction_ptr];
		size_t colon_pos = command.find(';');
		if (colon_pos == string::npos) return "null";
		return command.substr(colon_pos+1, command.size() - colon_pos - 1);
	}

	void reset() {
		instruction_ptr = -1;
	}

	int get_line_number() {
		return line_number[instruction_ptr];
	}

	void InvalidSyntaxError() {
		throw runtime_error("Parser: Invalid Syntax at line " + to_string(get_line_number()));
	}
};


#endif // !Parser_H
