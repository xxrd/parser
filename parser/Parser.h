#pragma once
#include "Token.h"
#include "TokenType.h"
#include <vector>
#include "Tree.h"

class Parser {
private:
	Token END_OF_FILE = Token(TokenType::END_OF_FILE, "");
	std::vector<Token> tokens;
	int pos;
	int size;

	Token get(int relativePosition) const;
	bool match(TokenType type);
	Tree::Node* node();

public:
	Parser(const std::vector<Token>& tokens);
	Tree* parse();


};