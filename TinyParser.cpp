#include <iostream>

#include "./include/parser/TinyParser.h"

TinyParser::TinyParser()
{
  this->_ast = TreeNode();

  TreeNode subChild1 = TreeNode();
  subChild1.type = TreeNode::Type::Assignment;

  TreeNode child1 = TreeNode();
  child1.type = TreeNode::Type::And;
  child1.children.push_back(subChild1);

  this->_ast.type = TreeNode::Type::Program;
  this->_ast.children.push_back(child1);
  this->_ast.children.push_back(child1);
}

TinyParser::~TinyParser()
{
}

TreeNode TinyParser::getAst()
{
  return this->_ast;
}

void TinyParser::parseProgram(std::queue<TinyLexicalAnalyzer::Token> tokens,
                              std::map<size_t, std::string> values)
{
  this->tokens = &tokens;
  this->values = &values;

  Tiny();
}

void TinyParser::assertNextToken(TinyLexicalAnalyzer::Token expected)
{
  TinyLexicalAnalyzer::Token currentToken = this->tokens->front();

  if (currentToken == expected)
  {
    this->tokens->pop();
    return;
  }

  char errorBuffer[115];

  sprintf(errorBuffer, "Parser failed to parse Token of type %s Expected \'%s\'",
          TinyLexicalAnalyzer::convertTokenToString(currentToken).c_str(),
          TinyLexicalAnalyzer::convertTokenToString(expected).c_str());

  throw std::invalid_argument(errorBuffer);
}

void TinyParser::Tiny()
{
  assertNextToken(TinyLexicalAnalyzer::Token::Program);
  Name();
  assertNextToken(TinyLexicalAnalyzer::Token::Colon);
  Consts();
  Types();
  Dclns();
  SubProgs();
  Body();
  Name();
  assertNextToken(TinyLexicalAnalyzer::Token::Dot);
};

void TinyParser::Consts()
{
  if (this->tokens->front() == TinyLexicalAnalyzer::Token::Constant)
  {
    do
    {
      assertNextToken(TinyLexicalAnalyzer::Token::Constant);
      Const();
    } while (this->tokens->front() == TinyLexicalAnalyzer::Token::Comma);

    assertNextToken(TinyLexicalAnalyzer::Token::Semicolon);
  }
};

void TinyParser::Const()
{
  Name();
  assertNextToken(TinyLexicalAnalyzer::Token::Assignment);
  ConstValue();
};

void TinyParser::ConstValue()
{
  switch (this->tokens->front())
  {
  case (TinyLexicalAnalyzer::Token::Number):
    assertNextToken(TinyLexicalAnalyzer::Token::Number);
    break;
  case (TinyLexicalAnalyzer::Token::Character):
    assertNextToken(TinyLexicalAnalyzer::Token::Character);
    break;
  default:
    Name();
  }
};

void TinyParser::Types()
{
  if (this->tokens->front() == TinyLexicalAnalyzer::Token::Type)
  {
    assertNextToken(TinyLexicalAnalyzer::Token::Type);

    do
    {
      TypeNode();
      assertNextToken(TinyLexicalAnalyzer::Token::Semicolon);
    } while (this->tokens->front() == TinyLexicalAnalyzer::Token::Identifier);
  }
};

void TinyParser::TypeNode()
{
  Name();
  assertNextToken(TinyLexicalAnalyzer::Token::Assignment);
  LitList();
};

void TinyParser::LitList()
{
  assertNextToken(TinyLexicalAnalyzer::Token::OpenBracket);
  Name();

  while (this->tokens->front() == TinyLexicalAnalyzer::Token::Comma)
  {
    assertNextToken(TinyLexicalAnalyzer::Token::Comma);
    Name();
  }

  assertNextToken(TinyLexicalAnalyzer::Token::CloseBracket);
};

void TinyParser::SubProgs()
{
  while (this->tokens->front() == TinyLexicalAnalyzer::Token::Function)
  {
    Fcn();
  }
};

void TinyParser::Fcn()
{
  assertNextToken(TinyLexicalAnalyzer::Token::Function);
  Name();
  assertNextToken(TinyLexicalAnalyzer::Token::OpenBracket);
  Params();
  assertNextToken(TinyLexicalAnalyzer::Token::CloseBracket);
  assertNextToken(TinyLexicalAnalyzer::Token::Colon);
  Name();
  assertNextToken(TinyLexicalAnalyzer::Token::Semicolon);
  Consts();
  Types();
  Dclns();
  Body();
  Name();
  assertNextToken(TinyLexicalAnalyzer::Token::Semicolon);
};

void TinyParser::Params()
{
  Dcln();

  while (this->tokens->front() == TinyLexicalAnalyzer::Token::Semicolon)
  {
    assertNextToken(TinyLexicalAnalyzer::Token::Semicolon);
    Dcln();
  }
};

void TinyParser::Dclns()
{
  if (this->tokens->front() == TinyLexicalAnalyzer::Token::Variable)
  {
    assertNextToken(TinyLexicalAnalyzer::Token::Variable);

    do
    {
      Dcln();
      assertNextToken(TinyLexicalAnalyzer::Token::Semicolon);
    } while (this->tokens->front() == TinyLexicalAnalyzer::Token::Identifier);
  }
};

void TinyParser::Dcln()
{
  Name();

  while (this->tokens->front() == TinyLexicalAnalyzer::Token::Comma)
  {
    assertNextToken(TinyLexicalAnalyzer::Token::Comma);
    Name();
  }

  assertNextToken(TinyLexicalAnalyzer::Token::Colon);
  Name();
};

void TinyParser::Body()
{
  assertNextToken(TinyLexicalAnalyzer::Token::Begin);
  Statement();

  while (this->tokens->front() == TinyLexicalAnalyzer::Token::Semicolon)
  {
    assertNextToken(TinyLexicalAnalyzer::Token::Semicolon);
    Statement();
  }

  assertNextToken(TinyLexicalAnalyzer::Token::End);
};

void TinyParser::Statement()
{
  switch (this->tokens->front())
  {
  case (TinyLexicalAnalyzer::Token::Identifier):
    AssignmentNode();
    break;
  case (TinyLexicalAnalyzer::Token::Output):
    assertNextToken(TinyLexicalAnalyzer::Token::Output);
    assertNextToken(TinyLexicalAnalyzer::Token::OpenBracket);

    OutExp();

    while (this->tokens->front() == TinyLexicalAnalyzer::Token::Comma)
    {
      assertNextToken(TinyLexicalAnalyzer::Token::Comma);
      OutExp();
    }

    assertNextToken(TinyLexicalAnalyzer::Token::CloseBracket);
    break;
  case (TinyLexicalAnalyzer::Token::If):
    assertNextToken(TinyLexicalAnalyzer::Token::If);
    Expression();
    assertNextToken(TinyLexicalAnalyzer::Token::Then);
    Statement();
    if (this->tokens->front() == TinyLexicalAnalyzer::Token::Else)
    {
      assertNextToken(TinyLexicalAnalyzer::Token::Else);
      Statement();
    }
    break;
  case (TinyLexicalAnalyzer::Token::While):
    assertNextToken(TinyLexicalAnalyzer::Token::While);
    Expression();
    assertNextToken(TinyLexicalAnalyzer::Token::Do);
    Statement();
    break;
  case (TinyLexicalAnalyzer::Token::Repeat):
    assertNextToken(TinyLexicalAnalyzer::Token::Repeat);
    Statement();
    while (this->tokens->front() == TinyLexicalAnalyzer::Token::Semicolon)
    {
      assertNextToken(TinyLexicalAnalyzer::Token::Semicolon);
      Statement();
    }
    assertNextToken(TinyLexicalAnalyzer::Token::Until);
    Expression();
    break;
  case (TinyLexicalAnalyzer::Token::For):
    assertNextToken(TinyLexicalAnalyzer::Token::For);
    assertNextToken(TinyLexicalAnalyzer::Token::OpenBracket);
    ForStat();
    assertNextToken(TinyLexicalAnalyzer::Token::Semicolon);
    ForExp();
    assertNextToken(TinyLexicalAnalyzer::Token::Semicolon);
    ForStat();
    assertNextToken(TinyLexicalAnalyzer::Token::CloseBracket);
    Statement();
    break;
  case (TinyLexicalAnalyzer::Token::Loop):
    assertNextToken(TinyLexicalAnalyzer::Token::Loop);
    Statement();
    while (this->tokens->front() == TinyLexicalAnalyzer::Token::Semicolon)
    {
      assertNextToken(TinyLexicalAnalyzer::Token::Semicolon);
      Statement();
    }
    assertNextToken(TinyLexicalAnalyzer::Token::Pool);
    break;
  case (TinyLexicalAnalyzer::Token::Case):
    assertNextToken(TinyLexicalAnalyzer::Token::Case);
    Expression();
    assertNextToken(TinyLexicalAnalyzer::Token::Of);
    CaseClauses();
    OtherwiseClause();
    assertNextToken(TinyLexicalAnalyzer::Token::End);
    break;
  case (TinyLexicalAnalyzer::Token::Read):
    assertNextToken(TinyLexicalAnalyzer::Token::Read);
    assertNextToken(TinyLexicalAnalyzer::Token::OpenBracket);
    Name();
    while (this->tokens->front() == TinyLexicalAnalyzer::Token::Comma)
    {
      assertNextToken(TinyLexicalAnalyzer::Token::Comma);
      Name();
    }
    assertNextToken(TinyLexicalAnalyzer::Token::CloseBracket);
    break;
  case (TinyLexicalAnalyzer::Token::Exit):
    assertNextToken(TinyLexicalAnalyzer::Token::Exit);
    break;
  case (TinyLexicalAnalyzer::Token::Return):
    assertNextToken(TinyLexicalAnalyzer::Token::Return);
    Expression();
    break;
  case (TinyLexicalAnalyzer::Token::Begin):
    Body();
    break;
  }
};

void TinyParser::OutExp()
{
  if (this->tokens->front() == TinyLexicalAnalyzer::Token::String)
  {
    StringNode();
  }
  else
  {
    Expression();
  }
};

void TinyParser::StringNode()
{
  assertNextToken(TinyLexicalAnalyzer::Token::String);
};

void TinyParser::CaseClauses()
{
  do
  {
    CaseClause();
    assertNextToken(TinyLexicalAnalyzer::Token::Semicolon);
  } while (this->tokens->front() != TinyLexicalAnalyzer::Token::Otherwise);
};

void TinyParser::CaseClause()
{
  CaseExpression();

  while (this->tokens->front() == TinyLexicalAnalyzer::Token::Comma)
  {
    assertNextToken(TinyLexicalAnalyzer::Token::Comma);
    CaseExpression();
  }
  assertNextToken(TinyLexicalAnalyzer::Token::Colon);
  Statement();
};

void TinyParser::CaseExpression()
{
  ConstValue();

  if (this->tokens->front() == TinyLexicalAnalyzer::Token::Elipses)
  {
    assertNextToken(TinyLexicalAnalyzer::Token::Elipses);
    ConstValue();
  }
};

void TinyParser::OtherwiseClause()
{
  if (this->tokens->front() == TinyLexicalAnalyzer::Token::Otherwise)
  {
    assertNextToken(TinyLexicalAnalyzer::Token::Otherwise);
    Statement();
  }
};

void TinyParser::AssignmentNode()
{
  Name();

  switch (this->tokens->front())
  {
  case (TinyLexicalAnalyzer::Token::Assignment):
    assertNextToken(TinyLexicalAnalyzer::Token::Assignment);
    Expression();
    break;
  case (TinyLexicalAnalyzer::Token::Swap):
    assertNextToken(TinyLexicalAnalyzer::Token::Swap);
    Name();
    break;
  }
};

void TinyParser::ForStat()
{
  if (this->tokens->front() == TinyLexicalAnalyzer::Token::Identifier)
  {
    AssignmentNode();
  }
};

void TinyParser::ForExp()
{
  if (this->tokens->front() != TinyLexicalAnalyzer::Token::Semicolon)
  {
    Expression();
  }
};

void TinyParser::Expression()
{
  Term();

  switch (this->tokens->front())
  {
  case (TinyLexicalAnalyzer::Token::LE):
    assertNextToken(TinyLexicalAnalyzer::Token::LE);
    Term();
    break;
  case (TinyLexicalAnalyzer::Token::LT):
    assertNextToken(TinyLexicalAnalyzer::Token::LT);
    Term();
    break;
  case (TinyLexicalAnalyzer::Token::GE):
    assertNextToken(TinyLexicalAnalyzer::Token::GE);
    Term();
    break;
  case (TinyLexicalAnalyzer::Token::GT):
    assertNextToken(TinyLexicalAnalyzer::Token::GT);
    Term();
    break;
  case (TinyLexicalAnalyzer::Token::Eq):
    assertNextToken(TinyLexicalAnalyzer::Token::Eq);
    Term();
    break;
  case (TinyLexicalAnalyzer::Token::NE):
    assertNextToken(TinyLexicalAnalyzer::Token::NE);
    Term();
    break;
  }
};

void TinyParser::Term()
{
  Factor();

  switch (this->tokens->front())
  {
  case (TinyLexicalAnalyzer::Token::Plus):
    assertNextToken(TinyLexicalAnalyzer::Token::Plus);
    Factor();
    break;
  case (TinyLexicalAnalyzer::Token::Minus):
    assertNextToken(TinyLexicalAnalyzer::Token::Minus);
    Factor();
    break;
  case (TinyLexicalAnalyzer::Token::Or):
    assertNextToken(TinyLexicalAnalyzer::Token::Or);
    Factor();
    break;
  }
};

void TinyParser::Factor()
{
  Primary();

  switch (this->tokens->front())
  {
  case (TinyLexicalAnalyzer::Token::Multiply):
    assertNextToken(TinyLexicalAnalyzer::Token::Multiply);
    Primary();
    break;
  case (TinyLexicalAnalyzer::Token::Divide):
    assertNextToken(TinyLexicalAnalyzer::Token::Divide);
    Primary();
    break;
  case (TinyLexicalAnalyzer::Token::And):
    assertNextToken(TinyLexicalAnalyzer::Token::And);
    Primary();
    break;
  case (TinyLexicalAnalyzer::Token::Mod):
    assertNextToken(TinyLexicalAnalyzer::Token::Mod);
    Primary();
    break;
  }
};

void TinyParser::Primary()
{
  switch (this->tokens->front())
  {
  case (TinyLexicalAnalyzer::Token::Minus):
    assertNextToken(TinyLexicalAnalyzer::Token::Minus);
    Primary();
    break;
  case (TinyLexicalAnalyzer::Token::Plus):
    assertNextToken(TinyLexicalAnalyzer::Token::Plus);
    Primary();
    break;
  case (TinyLexicalAnalyzer::Token::Not):
    assertNextToken(TinyLexicalAnalyzer::Token::Not);
    Primary();
    break;
  case (TinyLexicalAnalyzer::Token::Eof):
    assertNextToken(TinyLexicalAnalyzer::Token::Eof);
    break;
  case (TinyLexicalAnalyzer::Token::Identifier):
    assertNextToken(TinyLexicalAnalyzer::Token::Identifier);
    if (this->tokens->front() == TinyLexicalAnalyzer::Token::OpenBracket)
    {
      assertNextToken(TinyLexicalAnalyzer::Token::OpenBracket);
      Expression();
      while (this->tokens->front() == TinyLexicalAnalyzer::Token::Comma)
      {
        assertNextToken(TinyLexicalAnalyzer::Token::Comma);
        Expression();
      }
      assertNextToken(TinyLexicalAnalyzer::Token::CloseBracket);
    }
    break;
  case (TinyLexicalAnalyzer::Token::Number):
    assertNextToken(TinyLexicalAnalyzer::Token::Number);
    break;
  case (TinyLexicalAnalyzer::Token::Character):
    assertNextToken(TinyLexicalAnalyzer::Token::Character);
    break;
  case (TinyLexicalAnalyzer::Token::OpenBracket):
    assertNextToken(TinyLexicalAnalyzer::Token::OpenBracket);
    Expression();
    assertNextToken(TinyLexicalAnalyzer::Token::CloseBracket);
    break;
  case (TinyLexicalAnalyzer::Token::Successor):
    assertNextToken(TinyLexicalAnalyzer::Token::Successor);
    assertNextToken(TinyLexicalAnalyzer::Token::OpenBracket);
    Expression();
    assertNextToken(TinyLexicalAnalyzer::Token::CloseBracket);
    break;
  case (TinyLexicalAnalyzer::Token::Predecessor):
    assertNextToken(TinyLexicalAnalyzer::Token::Predecessor);
    assertNextToken(TinyLexicalAnalyzer::Token::OpenBracket);
    Expression();
    assertNextToken(TinyLexicalAnalyzer::Token::CloseBracket);
    break;
  case (TinyLexicalAnalyzer::Token::CharFun):
    assertNextToken(TinyLexicalAnalyzer::Token::CharFun);
    assertNextToken(TinyLexicalAnalyzer::Token::OpenBracket);
    Expression();
    assertNextToken(TinyLexicalAnalyzer::Token::CloseBracket);
    break;
  case (TinyLexicalAnalyzer::Token::OrdFun):
    assertNextToken(TinyLexicalAnalyzer::Token::OrdFun);
    assertNextToken(TinyLexicalAnalyzer::Token::OpenBracket);
    Expression();
    assertNextToken(TinyLexicalAnalyzer::Token::CloseBracket);
    break;
  }
};

void TinyParser::Name()
{
  assertNextToken(TinyLexicalAnalyzer::Token::Identifier);
};
