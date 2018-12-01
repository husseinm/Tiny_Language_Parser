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
    this->_tokenRepresentationMap[TreeNode::Type::Consts] = "consts";
    this->_tokenRepresentationMap[TreeNode::Type::Const] = "const";
    this->_tokenRepresentationMap[TreeNode::Type::Types] = "types";
    this->_tokenRepresentationMap[TreeNode::Type::Type] = "type";
    this->_tokenRepresentationMap[TreeNode::Type::Lit] = "lit";
    this->_tokenRepresentationMap[TreeNode::Type::Subprogs] = "subprogs";
    this->_tokenRepresentationMap[TreeNode::Type::Fcn] = "fcn";
    this->_tokenRepresentationMap[TreeNode::Type::Params] = "params";
    this->_tokenRepresentationMap[TreeNode::Type::Dclns] = "dclns";
    this->_tokenRepresentationMap[TreeNode::Type::Var] = "var";
    this->_tokenRepresentationMap[TreeNode::Type::Block] = "block";
    this->_tokenRepresentationMap[TreeNode::Type::Output] = "output";
    this->_tokenRepresentationMap[TreeNode::Type::If] = "if";
    this->_tokenRepresentationMap[TreeNode::Type::While] = "while";
    this->_tokenRepresentationMap[TreeNode::Type::Repeat] = "repeat";
    this->_tokenRepresentationMap[TreeNode::Type::For] = "for";
    this->_tokenRepresentationMap[TreeNode::Type::Loop] = "loop";
    this->_tokenRepresentationMap[TreeNode::Type::Case] = "case";
    this->_tokenRepresentationMap[TreeNode::Type::Read] = "read";
    this->_tokenRepresentationMap[TreeNode::Type::Exit] = "exit";
    this->_tokenRepresentationMap[TreeNode::Type::Return] = "return";
    this->_tokenRepresentationMap[TreeNode::Type::Null] = "<null>";
    this->_tokenRepresentationMap[TreeNode::Type::Integer] = "integer";
    this->_tokenRepresentationMap[TreeNode::Type::IntegerConst] = "<integer>";
    this->_tokenRepresentationMap[TreeNode::Type::Identifier] = "<identifier>";
    this->_tokenRepresentationMap[TreeNode::Type::String] = "<string>";
    this->_tokenRepresentationMap[TreeNode::Type::CaseClause] = "case_clause";
    this->_tokenRepresentationMap[TreeNode::Type::Ellipses] = "..";
    this->_tokenRepresentationMap[TreeNode::Type::Otherwise] = "otherwise";
    this->_tokenRepresentationMap[TreeNode::Type::Assign] = "assign";
    this->_tokenRepresentationMap[TreeNode::Type::Swap] = "swap";
    this->_tokenRepresentationMap[TreeNode::Type::True] = "true";
    this->_tokenRepresentationMap[TreeNode::Type::LE] = "<=";
    this->_tokenRepresentationMap[TreeNode::Type::LT] = "<";
    this->_tokenRepresentationMap[TreeNode::Type::GE] = ">=";
    this->_tokenRepresentationMap[TreeNode::Type::GT] = ">";
    this->_tokenRepresentationMap[TreeNode::Type::EQ] = "=";
    this->_tokenRepresentationMap[TreeNode::Type::NE] = "<>";
    this->_tokenRepresentationMap[TreeNode::Type::Plus] = "+";
    this->_tokenRepresentationMap[TreeNode::Type::Minus] = "-";
    this->_tokenRepresentationMap[TreeNode::Type::Or] = "or";
    this->_tokenRepresentationMap[TreeNode::Type::Multiply] = "*";
    this->_tokenRepresentationMap[TreeNode::Type::Divide] = "/";
    this->_tokenRepresentationMap[TreeNode::Type::And] = "and";
    this->_tokenRepresentationMap[TreeNode::Type::Mod] = "mod";
    this->_tokenRepresentationMap[TreeNode::Type::Not] = "not";
    this->_tokenRepresentationMap[TreeNode::Type::Eof] = "eof";
    this->_tokenRepresentationMap[TreeNode::Type::Call] = "call";
    this->_tokenRepresentationMap[TreeNode::Type::Succ] = "succ";
    this->_tokenRepresentationMap[TreeNode::Type::Pred] = "pred";
    this->_tokenRepresentationMap[TreeNode::Type::Chr] = "chr";
    this->_tokenRepresentationMap[TreeNode::Type::Or] = "or";

    isInitialized = true;
  }
}

TreeNode::~TreeNode()
{
}

std::string TreeNode::toString()
{
  std::string nodeName;

  try
  {
    nodeName = this->_tokenRepresentationMap.at(this->type);
  }
  catch (std::out_of_range e)
  {
    if (this->type == Type::IdentifierValue)
    {
      nodeName = (char *)this->data;
    }
    else
    {
      nodeName = "UNDEFINED";
    }
  }

  return nodeName + "(" + std::to_string(this->children.size()) + ")";
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
