#include "Lexer.h";
#include <stdexcept>

using namespace std;


char Lexer::peek(int relativePosition) const {
	const int position = pos + relativePosition;
	if (position >= length) return '\0';
	return input.at(position);
}

char Lexer::next() {
	pos++;
	return peek(0);
}

void Lexer::addToken(TokenType type) {
	addToken(type, "");
}

void Lexer::addToken(TokenType type, const std::string& text) {
	tokens.push_back(Token(type, text));

}

void Lexer::tokenizeName() {
	string buffer;
	char current = peek(0);


	while (true) {
		if (!isalpha(current) && !isdigit(current) && (current != '_')) {
			break;
		}
		buffer.push_back(current);
		current = next();
	}
	addToken(TokenType::NODE_NAME, buffer);
	next();

}

void Lexer::tokenizeValue() {
	string buffer;
	char current = next();


	while (true) {
		if (current == '"') {
			break;
		}
		if (current == '\n') {
			throw runtime_error("Lexer error: unexpected end of line at position " + to_string(pos) + "of input");
		}
		buffer.push_back(current);
		current = next();
	}
	addToken(TokenType::NODE_VALUE, buffer);
	next();

}

void Lexer::tokenizeEqual() {
	char current = peek(0);
	addToken(TokenType::EQUAL);
	next();
}

void Lexer::tokenizeLBracket() {
	char current = peek(0);
	addToken(TokenType::LBRACKET);
	next();
}

void Lexer::tokenizeRBracket() {
	char current = peek(0);
	addToken(TokenType::RBRACKET);
	next();
}


Lexer::Lexer(const std::string& input) : input(input), length(input.size()), pos(0) {}

vector<Token> Lexer::tokenize() {
	while (pos < length) {
		char current = peek(0);
		if (isalpha(current) || current == '_')
			tokenizeName();
		else if (current == '=') {
			tokenizeEqual();
		}
		else if (current == '"') {
			tokenizeValue();
		}
		else if (current == '{') {
			tokenizeLBracket();
		}
		else if (current == '}') {
			tokenizeRBracket();
		}
		else if (isspace(current)) {
			next();
		}
		else {
			throw runtime_error("Lexer error: unknown sybmol at position: " + to_string(pos) + "of input");
		}

	}

	return tokens;
}

