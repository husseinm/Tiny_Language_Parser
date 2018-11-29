#include "./include/TinyParser.h"

TinyParser::TinyParser()
{
  this->_ast = TreeNode();
}

TinyParser::~TinyParser()
{
}

void TinyParser::parseProgram(std::vector<TinyLexicalAnalyzer::Token> tokens,
                              std::map<size_t, std::string> values)
{
}

TinyParser::TreeNode TinyParser::getAst()
{
  return this->_ast;
}

void TinyParser::printAst()
{
  printAstLayer(0);
}

void TinyParser::printAstLayer(int layer)
{
}

void TinyParser::Tiny(){};

void TinyParser::Consts(){};

void TinyParser::Const(){};

void TinyParser::ConstValue(){};

void TinyParser::Types(){};

void TinyParser::Type(){};

void TinyParser::LitList(){};

void TinyParser::SubProgs(){};

void TinyParser::Fcn(){};

void TinyParser::Params(){};

void TinyParser::Dclns(){};

void TinyParser::Dcln(){};

void TinyParser::Body(){};

void TinyParser::Statement(){};

void TinyParser::OutExp(){};

void TinyParser::StringNode(){};

void TinyParser::CaseClauses(){};

void TinyParser::CaseClause(){};

void TinyParser::CaseExpression(){};

void TinyParser::OtherwiseClause(){};

void TinyParser::Assignment(){};

void TinyParser::ForStat(){};

void TinyParser::ForExp(){};

void TinyParser::Expression(){};

void TinyParser::Term(){};

void TinyParser::Factor(){};

void TinyParser::Primary(){};

void TinyParser::Name(){};
