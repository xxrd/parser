#include <iostream>
#include <fstream>
#include "Tree.h"
#include "Lexer.h"
#include "Parser.h"

using namespace std;


int main(int argc, char *argv[]) {

	ifstream in;
	in.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	ofstream out;
	out.exceptions(std::ifstream::failbit | std::ifstream::badbit);


	try {

		if (argc != 3) throw runtime_error("The number of command line parameters is not equal to two");

		in.open(argv[1]);
		out.open(argv[2]);

		std::string inStr((std::istreambuf_iterator<char>(in)),
			std::istreambuf_iterator<char>());

		Lexer lexer(inStr);
		vector<Token> tokens = lexer.tokenize();

		Parser parser(tokens);
		shared_ptr<Tree> tree(parser.parse());
		out << *tree;
		
		in.close();
		out.close();

	}
	catch (exception& e) {
		cerr << e.what() << endl;
		in.close();
		out.close();

	}




}













