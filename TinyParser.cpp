#include <iostream>
#include <string.h>

#include "./include/parser/TinyParser.h"

TinyParser::TinyParser()
{
  this->_ast = TreeNode();
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
  this->initialQueueSize = tokens.size();

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

  sprintf(errorBuffer, "Parser failed to parse Token of type \'%s\' Expected \'%s\'",
          TinyLexicalAnalyzer::convertTokenToString(currentToken).c_str(),
          TinyLexicalAnalyzer::convertTokenToString(expected).c_str());

  throw std::invalid_argument(errorBuffer);
}

void TinyParser::Tiny()
{
  assertNextToken(TinyLexicalAnalyzer::Token::Program);
  this->_ast.children.push_back(Name());
  assertNextToken(TinyLexicalAnalyzer::Token::Colon);
  this->_ast.children.push_back(Consts());
  this->_ast.children.push_back(Types());
  this->_ast.children.push_back(Dclns());
  this->_ast.children.push_back(SubProgs());
  this->_ast.children.push_back(Body());
  this->_ast.children.push_back(Name());
  assertNextToken(TinyLexicalAnalyzer::Token::Dot);

  this->_ast.type = TreeNode::Type::Program;
};

TreeNode TinyParser::Consts()
{
  TreeNode node = TreeNode();
  node.type = TreeNode::Type::Consts;

  if (this->tokens->front() == TinyLexicalAnalyzer::Token::Constant)
  {
    assertNextToken(TinyLexicalAnalyzer::Token::Constant);
    node.children.push_back(Const());

    while (this->tokens->front() == TinyLexicalAnalyzer::Token::Comma)
    {
      assertNextToken(TinyLexicalAnalyzer::Token::Comma);
      node.children.push_back(Const());
    }

    assertNextToken(TinyLexicalAnalyzer::Token::Semicolon);
  }

  return node;
};

TreeNode TinyParser::Const()
{
  TreeNode node = TreeNode();
  node.type = TreeNode::Type::Const;

  node.children.push_back(Name());
  assertNextToken(TinyLexicalAnalyzer::Token::Assignment);
  node.children.push_back(ConstValue());

  return node;
};

TreeNode TinyParser::ConstValue()
{
  TreeNode node = TreeNode();

  switch (this->tokens->front())
  {
  case (TinyLexicalAnalyzer::Token::Number):
    node.type = TreeNode::Type::IntegerConst;
    assertNextToken(TinyLexicalAnalyzer::Token::Number);
    node.children.push_back(ValueNode());
    return node;
  case (TinyLexicalAnalyzer::Token::Character):
    node.type = TreeNode::Type::Char;
    assertNextToken(TinyLexicalAnalyzer::Token::Character);
    node.children.push_back(ValueNode());
    return node;
  default:
    break;
  }

  return Name();
};

TreeNode TinyParser::Types()
{
  TreeNode node = TreeNode();
  node.type = TreeNode::Type::Types;

  if (this->tokens->front() == TinyLexicalAnalyzer::Token::Type)
  {
    assertNextToken(TinyLexicalAnalyzer::Token::Type);

    do
    {
      node.children.push_back(TypeNode());
      assertNextToken(TinyLexicalAnalyzer::Token::Semicolon);
    } while (this->tokens->front() == TinyLexicalAnalyzer::Token::Identifier);
  }

  return node;
};

TreeNode TinyParser::TypeNode()
{
  TreeNode node = TreeNode();
  node.type = TreeNode::Type::Type;

  node.children.push_back(Name());
  assertNextToken(TinyLexicalAnalyzer::Token::Eq);
  node.children.push_back(LitList());

  return node;
};

TreeNode TinyParser::LitList()
{
  TreeNode node = TreeNode();
  node.type = TreeNode::Type::Lit;

  assertNextToken(TinyLexicalAnalyzer::Token::OpenBracket);
  node.children.push_back(Name());

  while (this->tokens->front() == TinyLexicalAnalyzer::Token::Comma)
  {
    assertNextToken(TinyLexicalAnalyzer::Token::Comma);
    node.children.push_back(Name());
  }

  assertNextToken(TinyLexicalAnalyzer::Token::CloseBracket);

  return node;
};

TreeNode TinyParser::SubProgs()
{
  TreeNode node = TreeNode();
  node.type = TreeNode::Type::Subprogs;

  while (this->tokens->front() == TinyLexicalAnalyzer::Token::Function)
  {
    node.children.push_back(Fcn());
  }

  return node;
};

TreeNode TinyParser::Fcn()
{
  TreeNode node = TreeNode();
  node.type = TreeNode::Type::Fcn;

  assertNextToken(TinyLexicalAnalyzer::Token::Function);
  node.children.push_back(Name());
  assertNextToken(TinyLexicalAnalyzer::Token::OpenBracket);
  node.children.push_back(Params());
  assertNextToken(TinyLexicalAnalyzer::Token::CloseBracket);
  assertNextToken(TinyLexicalAnalyzer::Token::Colon);
  node.children.push_back(Name());
  assertNextToken(TinyLexicalAnalyzer::Token::Semicolon);
  node.children.push_back(Consts());
  node.children.push_back(Types());
  node.children.push_back(Dclns());
  node.children.push_back(Body());
  node.children.push_back(Name());
  assertNextToken(TinyLexicalAnalyzer::Token::Semicolon);

  return node;
};

TreeNode TinyParser::Params()
{
  TreeNode node = TreeNode();
  node.type = TreeNode::Type::Params;

  node.children.push_back(Dcln());

  while (this->tokens->front() == TinyLexicalAnalyzer::Token::Semicolon)
  {
    assertNextToken(TinyLexicalAnalyzer::Token::Semicolon);
    node.children.push_back(Dcln());
  }

  return node;
};

TreeNode TinyParser::Dclns()
{
  TreeNode node = TreeNode();
  node.type = TreeNode::Type::Dclns;

  if (this->tokens->front() == TinyLexicalAnalyzer::Token::Variable)
  {
    assertNextToken(TinyLexicalAnalyzer::Token::Variable);

    do
    {
      node.children.push_back(Dcln());
      assertNextToken(TinyLexicalAnalyzer::Token::Semicolon);
    } while (this->tokens->front() == TinyLexicalAnalyzer::Token::Identifier);
  }

  return node;
};

TreeNode TinyParser::Dcln()
{
  TreeNode node = TreeNode();
  node.type = TreeNode::Type::Var;

  node.children.push_back(Name());

  while (this->tokens->front() == TinyLexicalAnalyzer::Token::Comma)
  {
    assertNextToken(TinyLexicalAnalyzer::Token::Comma);
    node.children.push_back(Name());
  }

  assertNextToken(TinyLexicalAnalyzer::Token::Colon);
  node.children.push_back(Name());

  return node;
};

TreeNode TinyParser::Body()
{
  TreeNode node = TreeNode();
  node.type = TreeNode::Type::Block;

  assertNextToken(TinyLexicalAnalyzer::Token::Begin);
  node.children.push_back(Statement());

  while (this->tokens->front() == TinyLexicalAnalyzer::Token::Semicolon)
  {
    assertNextToken(TinyLexicalAnalyzer::Token::Semicolon);
    node.children.push_back(Statement());
  }

  assertNextToken(TinyLexicalAnalyzer::Token::End);

  return node;
};

TreeNode TinyParser::Statement()
{
  TreeNode node = TreeNode();
  TreeNode tmp = TreeNode();

  switch (this->tokens->front())
  {
  case (TinyLexicalAnalyzer::Token::Identifier):
    return AssignmentNode();
    break;
  case (TinyLexicalAnalyzer::Token::Output):
    node.type = TreeNode::Type::Output;
    assertNextToken(TinyLexicalAnalyzer::Token::Output);
    assertNextToken(TinyLexicalAnalyzer::Token::OpenBracket);

    node.children.push_back(OutExp());

    while (this->tokens->front() == TinyLexicalAnalyzer::Token::Comma)
    {
      assertNextToken(TinyLexicalAnalyzer::Token::Comma);
      node.children.push_back(OutExp());
    }

    assertNextToken(TinyLexicalAnalyzer::Token::CloseBracket);
    break;
  case (TinyLexicalAnalyzer::Token::If):
    node.type = TreeNode::Type::If;
    assertNextToken(TinyLexicalAnalyzer::Token::If);
    node.children.push_back(Expression());
    assertNextToken(TinyLexicalAnalyzer::Token::Then);
    node.children.push_back(Statement());
    if (this->tokens->front() == TinyLexicalAnalyzer::Token::Else)
    {
      assertNextToken(TinyLexicalAnalyzer::Token::Else);
      node.children.push_back(Statement());
    }
    break;
  case (TinyLexicalAnalyzer::Token::While):
    node.type = TreeNode::Type::While;
    assertNextToken(TinyLexicalAnalyzer::Token::While);
    node.children.push_back(Expression());
    assertNextToken(TinyLexicalAnalyzer::Token::Do);
    node.children.push_back(Statement());
    break;
  case (TinyLexicalAnalyzer::Token::Repeat):
    node.type = TreeNode::Type::Repeat;
    assertNextToken(TinyLexicalAnalyzer::Token::Repeat);
    node.children.push_back(Statement());
    while (this->tokens->front() == TinyLexicalAnalyzer::Token::Semicolon)
    {
      assertNextToken(TinyLexicalAnalyzer::Token::Semicolon);
      node.children.push_back(Statement());
    }
    assertNextToken(TinyLexicalAnalyzer::Token::Until);
    node.children.push_back(Expression());
    break;
  case (TinyLexicalAnalyzer::Token::For):
    node.type = TreeNode::Type::For;
    assertNextToken(TinyLexicalAnalyzer::Token::For);
    assertNextToken(TinyLexicalAnalyzer::Token::OpenBracket);
    node.children.push_back(ForStat());
    assertNextToken(TinyLexicalAnalyzer::Token::Semicolon);
    node.children.push_back(ForExp());
    assertNextToken(TinyLexicalAnalyzer::Token::Semicolon);
    node.children.push_back(ForStat());
    assertNextToken(TinyLexicalAnalyzer::Token::CloseBracket);
    node.children.push_back(Statement());
    break;
  case (TinyLexicalAnalyzer::Token::Loop):
    node.type = TreeNode::Type::Loop;
    assertNextToken(TinyLexicalAnalyzer::Token::Loop);
    node.children.push_back(Statement());
    while (this->tokens->front() == TinyLexicalAnalyzer::Token::Semicolon)
    {
      assertNextToken(TinyLexicalAnalyzer::Token::Semicolon);
      node.children.push_back(Statement());
    }
    assertNextToken(TinyLexicalAnalyzer::Token::Pool);
    break;
  case (TinyLexicalAnalyzer::Token::Case):
    node.type = TreeNode::Type::Case;
    assertNextToken(TinyLexicalAnalyzer::Token::Case);
    node.children.push_back(Expression());
    assertNextToken(TinyLexicalAnalyzer::Token::Of);

    tmp = CaseClauses();

    for (auto child : tmp.children)
    {
      node.children.push_back(child);
    }

    if (this->tokens->front() == TinyLexicalAnalyzer::Token::Otherwise)
    {
      node.children.push_back(OtherwiseClause());
    }
    assertNextToken(TinyLexicalAnalyzer::Token::End);
    break;
  case (TinyLexicalAnalyzer::Token::Read):
    node.type = TreeNode::Type::Read;
    assertNextToken(TinyLexicalAnalyzer::Token::Read);
    assertNextToken(TinyLexicalAnalyzer::Token::OpenBracket);
    node.children.push_back(Name());
    while (this->tokens->front() == TinyLexicalAnalyzer::Token::Comma)
    {
      assertNextToken(TinyLexicalAnalyzer::Token::Comma);
      node.children.push_back(Name());
    }
    assertNextToken(TinyLexicalAnalyzer::Token::CloseBracket);
    break;
  case (TinyLexicalAnalyzer::Token::Exit):
    node.type = TreeNode::Type::Exit;
    assertNextToken(TinyLexicalAnalyzer::Token::Exit);
    break;
  case (TinyLexicalAnalyzer::Token::Return):
    node.type = TreeNode::Type::Return;
    assertNextToken(TinyLexicalAnalyzer::Token::Return);
    node.children.push_back(Expression());
    break;
  case (TinyLexicalAnalyzer::Token::Begin):
    return Body();
    break;
  default:
    node.type = TreeNode::Type::Null;
    break;
  }

  return node;
};

TreeNode TinyParser::OutExp()
{
  TreeNode node = TreeNode();

  if (this->tokens->front() == TinyLexicalAnalyzer::Token::String)
  {
    node.type = TreeNode::Type::String;
    node.children.push_back(StringNode());
  }
  else
  {
    node.type = TreeNode::Type::Integer;
    node.children.push_back(Expression());
  }

  return node;
};

TreeNode TinyParser::StringNode()
{
  TreeNode node = TreeNode();
  node.type = TreeNode::Type::String;

  assertNextToken(TinyLexicalAnalyzer::Token::String);

  return node;
};

TreeNode TinyParser::CaseClauses()
{
  TreeNode node = TreeNode();

  do
  {
    node.children.push_back(CaseClause());
    assertNextToken(TinyLexicalAnalyzer::Token::Semicolon);
  } while (this->tokens->front() != TinyLexicalAnalyzer::Token::Otherwise &&
           this->tokens->front() != TinyLexicalAnalyzer::Token::End);

  return node;
};

TreeNode TinyParser::CaseClause()
{
  TreeNode node = TreeNode();
  node.type = TreeNode::Type::CaseClause;

  node.children.push_back(CaseExpression());

  while (this->tokens->front() == TinyLexicalAnalyzer::Token::Comma)
  {
    assertNextToken(TinyLexicalAnalyzer::Token::Comma);
    node.children.push_back(CaseExpression());
  }
  assertNextToken(TinyLexicalAnalyzer::Token::Colon);
  node.children.push_back(Statement());

  return node;
};

TreeNode TinyParser::CaseExpression()
{
  TreeNode node = TreeNode();
  TreeNode tmp = ConstValue();

  if (this->tokens->front() == TinyLexicalAnalyzer::Token::Elipses)
  {
    node.children.push_back(tmp);
    node.type = TreeNode::Type::Ellipses;
    assertNextToken(TinyLexicalAnalyzer::Token::Elipses);
    node.children.push_back(ConstValue());
  }
  else
  {
    return tmp;
  }

  return node;
};

TreeNode TinyParser::OtherwiseClause()
{
  TreeNode node = TreeNode();

  node.type = TreeNode::Type::Otherwise;
  assertNextToken(TinyLexicalAnalyzer::Token::Otherwise);
  node.children.push_back(Statement());

  return node;
};

TreeNode TinyParser::AssignmentNode()
{
  TreeNode node = TreeNode();

  node.children.push_back(Name());

  switch (this->tokens->front())
  {
  case (TinyLexicalAnalyzer::Token::Assignment):
    node.type = TreeNode::Type::Assign;
    assertNextToken(TinyLexicalAnalyzer::Token::Assignment);
    node.children.push_back(Expression());
    break;
  case (TinyLexicalAnalyzer::Token::Swap):
    node.type = TreeNode::Type::Swap;
    assertNextToken(TinyLexicalAnalyzer::Token::Swap);
    node.children.push_back(Name());
    break;
  default:
    break;
  }

  return node;
};

TreeNode TinyParser::ForStat()
{
  TreeNode node = TreeNode();
  node.type = TreeNode::Type::Null;

  if (this->tokens->front() == TinyLexicalAnalyzer::Token::Identifier)
  {
    return AssignmentNode();
  }

  return node;
};

TreeNode TinyParser::ForExp()
{
  TreeNode node = TreeNode();
  node.type = TreeNode::Type::True;

  if (this->tokens->front() != TinyLexicalAnalyzer::Token::Semicolon)
  {
    return Expression();
  }

  return node;
};

TreeNode TinyParser::Expression()
{
  TreeNode node = TreeNode();
  TreeNode tmp = Term();

  node.children.push_back(tmp);

  switch (this->tokens->front())
  {
  case (TinyLexicalAnalyzer::Token::LE):
    node.type = TreeNode::Type::LE;
    assertNextToken(TinyLexicalAnalyzer::Token::LE);
    node.children.push_back(Term());
    return node;
  case (TinyLexicalAnalyzer::Token::LT):
    node.type = TreeNode::Type::LT;
    assertNextToken(TinyLexicalAnalyzer::Token::LT);
    node.children.push_back(Term());
    return node;
  case (TinyLexicalAnalyzer::Token::GE):
    node.type = TreeNode::Type::GE;
    assertNextToken(TinyLexicalAnalyzer::Token::GE);
    node.children.push_back(Term());
    return node;
  case (TinyLexicalAnalyzer::Token::GT):
    node.type = TreeNode::Type::GT;
    assertNextToken(TinyLexicalAnalyzer::Token::GT);
    node.children.push_back(Term());
    return node;
  case (TinyLexicalAnalyzer::Token::Eq):
    node.type = TreeNode::Type::EQ;
    assertNextToken(TinyLexicalAnalyzer::Token::Eq);
    node.children.push_back(Term());
    return node;
  case (TinyLexicalAnalyzer::Token::NE):
    node.type = TreeNode::Type::NE;
    assertNextToken(TinyLexicalAnalyzer::Token::NE);
    node.children.push_back(Term());
    return node;
  default:
    break;
  }

  return tmp;
};

TreeNode TinyParser::Term()
{
  TreeNode node = TreeNode();
  TreeNode tmp = Factor();

  node.children.push_back(tmp);

  switch (this->tokens->front())
  {
  case (TinyLexicalAnalyzer::Token::Plus):
    node.type = TreeNode::Type::Plus;
    assertNextToken(TinyLexicalAnalyzer::Token::Plus);
    node.children.push_back(Factor());
    return node;
  case (TinyLexicalAnalyzer::Token::Minus):
    node.type = TreeNode::Type::Minus;
    assertNextToken(TinyLexicalAnalyzer::Token::Minus);
    node.children.push_back(Factor());
    return node;
  case (TinyLexicalAnalyzer::Token::Or):
    node.type = TreeNode::Type::Or;
    assertNextToken(TinyLexicalAnalyzer::Token::Or);
    node.children.push_back(Factor());
    return node;
  default:
    break;
  }

  return tmp;
};

TreeNode TinyParser::Factor()
{
  TreeNode node = TreeNode();
  TreeNode tmp = Primary();

  node.children.push_back(tmp);

  switch (this->tokens->front())
  {
  case (TinyLexicalAnalyzer::Token::Multiply):
    node.type = TreeNode::Type::Multiply;
    assertNextToken(TinyLexicalAnalyzer::Token::Multiply);
    node.children.push_back(Primary());
    return node;
  case (TinyLexicalAnalyzer::Token::Divide):
    node.type = TreeNode::Type::Divide;
    assertNextToken(TinyLexicalAnalyzer::Token::Divide);
    node.children.push_back(Primary());
    return node;
  case (TinyLexicalAnalyzer::Token::And):
    node.type = TreeNode::Type::And;
    assertNextToken(TinyLexicalAnalyzer::Token::And);
    node.children.push_back(Primary());
    return node;
  case (TinyLexicalAnalyzer::Token::Mod):
    node.type = TreeNode::Type::Mod;
    assertNextToken(TinyLexicalAnalyzer::Token::Mod);
    node.children.push_back(Primary());
    return node;
  default:
    break;
  }

  return tmp;
};

TreeNode TinyParser::Primary()
{
  TreeNode node = TreeNode();
  TreeNode tmp = TreeNode();

  switch (this->tokens->front())
  {
  case (TinyLexicalAnalyzer::Token::Minus):
    node.type = TreeNode::Type::Minus;
    assertNextToken(TinyLexicalAnalyzer::Token::Minus);
    node.children.push_back(Primary());
    return node;
  case (TinyLexicalAnalyzer::Token::Plus):
    assertNextToken(TinyLexicalAnalyzer::Token::Plus);
    return Primary();
  case (TinyLexicalAnalyzer::Token::Not):
    node.type = TreeNode::Type::Not;
    assertNextToken(TinyLexicalAnalyzer::Token::Not);
    node.children.push_back(Primary());
    return node;
  case (TinyLexicalAnalyzer::Token::Eof):
    node.type = TreeNode::Type::Eof;
    assertNextToken(TinyLexicalAnalyzer::Token::Eof);
    return node;
  case (TinyLexicalAnalyzer::Token::Identifier):
    tmp = Name();

    if (this->tokens->front() == TinyLexicalAnalyzer::Token::OpenBracket)
    {
      node.type = TreeNode::Type::Call;
      node.children.push_back(tmp);
      assertNextToken(TinyLexicalAnalyzer::Token::OpenBracket);
      node.children.push_back(Expression());
      while (this->tokens->front() == TinyLexicalAnalyzer::Token::Comma)
      {
        assertNextToken(TinyLexicalAnalyzer::Token::Comma);
        node.children.push_back(Expression());
      }
      assertNextToken(TinyLexicalAnalyzer::Token::CloseBracket);

      return node;
    }

    return tmp;
  case (TinyLexicalAnalyzer::Token::Number):
    node.type = TreeNode::Type::IntegerConst;

    assertNextToken(TinyLexicalAnalyzer::Token::Number);
    node.children.push_back(ValueNode());

    return node;
  case (TinyLexicalAnalyzer::Token::Character):
    node.type = TreeNode::Type::Char;

    assertNextToken(TinyLexicalAnalyzer::Token::Character);
    node.children.push_back(ValueNode());
    break;
  case (TinyLexicalAnalyzer::Token::OpenBracket):
    assertNextToken(TinyLexicalAnalyzer::Token::OpenBracket);
    node = Expression();
    assertNextToken(TinyLexicalAnalyzer::Token::CloseBracket);
    return node;
  case (TinyLexicalAnalyzer::Token::Successor):
    node.type = TreeNode::Type::Succ;
    assertNextToken(TinyLexicalAnalyzer::Token::Successor);
    assertNextToken(TinyLexicalAnalyzer::Token::OpenBracket);
    node.children.push_back(Expression());
    assertNextToken(TinyLexicalAnalyzer::Token::CloseBracket);
    return node;
  case (TinyLexicalAnalyzer::Token::Predecessor):
    node.type = TreeNode::Type::Pred;
    assertNextToken(TinyLexicalAnalyzer::Token::Predecessor);
    assertNextToken(TinyLexicalAnalyzer::Token::OpenBracket);
    node.children.push_back(Expression());
    assertNextToken(TinyLexicalAnalyzer::Token::CloseBracket);
    return node;
  case (TinyLexicalAnalyzer::Token::CharFun):
    node.type = TreeNode::Type::Chr;
    assertNextToken(TinyLexicalAnalyzer::Token::CharFun);
    assertNextToken(TinyLexicalAnalyzer::Token::OpenBracket);
    node.children.push_back(Expression());
    assertNextToken(TinyLexicalAnalyzer::Token::CloseBracket);
    return node;
  case (TinyLexicalAnalyzer::Token::OrdFun):
    node.type = TreeNode::Type::Ord;
    assertNextToken(TinyLexicalAnalyzer::Token::OrdFun);
    assertNextToken(TinyLexicalAnalyzer::Token::OpenBracket);
    node.children.push_back(Expression());
    assertNextToken(TinyLexicalAnalyzer::Token::CloseBracket);
    return node;
  default:
    break;
  }

  return node;
};

TreeNode TinyParser::Name()
{
  TreeNode node = TreeNode();
  node.type = TreeNode::Type::Identifier;

  assertNextToken(TinyLexicalAnalyzer::Token::Identifier);
  node.children.push_back(ValueNode());

  return node;
};

TreeNode TinyParser::ValueNode()
{
  TreeNode valueNode = TreeNode();

  const size_t index = this->initialQueueSize - this->tokens->size() - 1;
  const char *stackValue = this->values->at(index).c_str();
  char *heapValue = new char[sizeof(stackValue)];
  strcpy(heapValue, stackValue);

  valueNode.type = TreeNode::Type::IdentifierValue;
  valueNode.data = (void *)heapValue;

  return valueNode;
}
