#include "./include/TreeNode.h"
#include <iostream>

std::map<TreeNode::Type, std::string> TreeNode::_tokenRepresentationMap =
    std::map<TreeNode::Type, std::string>();
bool TreeNode::isInitialized = false;

TreeNode::TreeNode()
{
  this->children = std::vector<TreeNode>();

  if (!isInitialized)
  {
    this->_tokenRepresentationMap[TreeNode::Type::Program] = "program";
    this->_tokenRepresentationMap[TreeNode::Type::Variable] = "var";
    this->_tokenRepresentationMap[TreeNode::Type::Constant] = "const";
    this->_tokenRepresentationMap[TreeNode::Type::Type] = "type";
    this->_tokenRepresentationMap[TreeNode::Type::Function] = "function";
    this->_tokenRepresentationMap[TreeNode::Type::Return] = "return";
    this->_tokenRepresentationMap[TreeNode::Type::Begin] = "begin";
    this->_tokenRepresentationMap[TreeNode::Type::End] = "end";
    this->_tokenRepresentationMap[TreeNode::Type::Swap] = ":=:";
    this->_tokenRepresentationMap[TreeNode::Type::Assignment] = ":=";
    this->_tokenRepresentationMap[TreeNode::Type::Integer] = "integer";
    this->_tokenRepresentationMap[TreeNode::Type::Output] = "output";
    this->_tokenRepresentationMap[TreeNode::Type::If] = "if";
    this->_tokenRepresentationMap[TreeNode::Type::Then] = "then";
    this->_tokenRepresentationMap[TreeNode::Type::Else] = "else";
    this->_tokenRepresentationMap[TreeNode::Type::While] = "while";
    this->_tokenRepresentationMap[TreeNode::Type::Do] = "do";
    this->_tokenRepresentationMap[TreeNode::Type::Case] = "case";
    this->_tokenRepresentationMap[TreeNode::Type::Of] = "of";
    this->_tokenRepresentationMap[TreeNode::Type::Elipses] = "..";
    this->_tokenRepresentationMap[TreeNode::Type::Otherwise] = "otherwise";
    this->_tokenRepresentationMap[TreeNode::Type::Repeat] = "repeat";
    this->_tokenRepresentationMap[TreeNode::Type::For] = "for";
    this->_tokenRepresentationMap[TreeNode::Type::Until] = "until";
    this->_tokenRepresentationMap[TreeNode::Type::Loop] = "loop";
    this->_tokenRepresentationMap[TreeNode::Type::Pool] = "pool";
    this->_tokenRepresentationMap[TreeNode::Type::Exit] = "exit";
    this->_tokenRepresentationMap[TreeNode::Type::LE] = "<=";
    this->_tokenRepresentationMap[TreeNode::Type::NE] = "<>";
    this->_tokenRepresentationMap[TreeNode::Type::LT] = "<";
    this->_tokenRepresentationMap[TreeNode::Type::GE] = ">=";
    this->_tokenRepresentationMap[TreeNode::Type::GT] = ">";
    this->_tokenRepresentationMap[TreeNode::Type::Eq] = "=";
    this->_tokenRepresentationMap[TreeNode::Type::Mod] = "mod";
    this->_tokenRepresentationMap[TreeNode::Type::And] = "and";
    this->_tokenRepresentationMap[TreeNode::Type::Or] = "or";
    this->_tokenRepresentationMap[TreeNode::Type::Not] = "not";
    this->_tokenRepresentationMap[TreeNode::Type::Read] = "read";
    this->_tokenRepresentationMap[TreeNode::Type::Successor] = "succ";
    this->_tokenRepresentationMap[TreeNode::Type::Predecessor] = "pred";
    this->_tokenRepresentationMap[TreeNode::Type::CharFun] = "chr";
    this->_tokenRepresentationMap[TreeNode::Type::OrdFun] = "ord";
    this->_tokenRepresentationMap[TreeNode::Type::Eof] = "eof";
    this->_tokenRepresentationMap[TreeNode::Type::Colon] = ":";
    this->_tokenRepresentationMap[TreeNode::Type::Semicolon] = ";";
    this->_tokenRepresentationMap[TreeNode::Type::Dot] = ".";
    this->_tokenRepresentationMap[TreeNode::Type::Comma] = ",";
    this->_tokenRepresentationMap[TreeNode::Type::OpenBracket] = "(";
    this->_tokenRepresentationMap[TreeNode::Type::CloseBracket] = ")";
    this->_tokenRepresentationMap[TreeNode::Type::Plus] = "+";
    this->_tokenRepresentationMap[TreeNode::Type::Minus] = "-";
    this->_tokenRepresentationMap[TreeNode::Type::Multiply] = "*";
    this->_tokenRepresentationMap[TreeNode::Type::Divide] = "/";

    isInitialized = true;
  }
}

TreeNode::~TreeNode()
{
}

std::string TreeNode::toString()
{
  return this->_tokenRepresentationMap.at(this->type) +
         "(" + std::to_string(this->children.size()) + ")";
}

void TreeNode::print()
{
  printLayer("");
}

void TreeNode::printLayer(std::string prefix)
{
  std::cout << prefix << this->toString() << std::endl;

  for (TreeNode child : this->children)
  {
    child.printLayer(prefix + ". ");
  }
}
