#ifndef Code_H
#define Code_H

#include <string>
#include <unordered_map>

using namespace std;


struct Code {
	unordered_map<string, string> dest_map, comp_map, jump_map;

	Code() {
		dest_map = {
			{"null", "000"},
			{"A", "100"},
			{"D", "010"},
			{"M", "001"},
			{"AD", "110"},
			{"AM", "101"},
			{"MD", "011"},
			{"AMD", "111"}
		};

		comp_map = {
			{"0", "0101010"},
			{"1", "0111111"},
			{"-1", "0111010"},
			{"D", "0001100"},
			{"A", "0110000"},
			{"M", "1110000"},
			{"!D", "0001101"},
			{"!A", "0110001"},
			{"!M", "1110001"},
			{"-D", "0001111"},
			{"-A", "0110011"},
			{"-M", "1110011"},
			{"D+1", "0011111"},
			{"A+1", "0110111"},
			{"M+1", "1110111"},
			{"D-1", "0001110"},
			{"A-1", "0110010"},
			{"M-1", "1110010"},
			{"D+A", "0000010"},
			{"D+M", "1000010"},
			{"D-A", "0010011"},
			{"D-M", "1010011"},
			{"A-D", "0000111"},
			{"M-D", "1000111"},
			{"D&A", "0000000"},
			{"D&M", "1000000"},
			{"D|A", "0010101"},
			{"D|M", "1010101"},
		};

		jump_map = {
			{"null", "000"},
			{"JGT", "001"},
			{"JEQ", "010"},
			{"JGE", "011"},
			{"JLT", "100"},
			{"JNE", "101"},
			{"JLE", "110"},
			{"JMP", "111"},
		};
	}

	string dest(string mnemonic, int ln = 0) {
		if (dest_map.count(mnemonic)) return dest_map[mnemonic];
		syntax_error("Code: Invalid dest", ln);
	}

	string comp(string mnemonic, int ln = 0) {
		if (comp_map.count(mnemonic)) return comp_map[mnemonic];
		syntax_error("Code: Invalid comp", ln);
	}

	string jump(string mnemonic, int ln = 0) {
		if (jump_map.count(mnemonic)) return jump_map[mnemonic];
		syntax_error("Code: Invalid jump", ln);
	}

	static void syntax_error(string msg, int ln = 0) {
		if (ln) {
			msg += " At line " + to_string(ln);
		}

		throw runtime_error(msg);
	}
};
#endif //Code_H