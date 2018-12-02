#ifndef TINY_TREENODE_H
#define TINY_TREENODE_H

#include <vector>
#include <string>
#include <map>

class TreeNode
{
public:
  TreeNode();
  ~TreeNode();

  enum class Type
  {
    Program,
    Consts,
    Const,
    Types,
    Type,
    Lit,
    Subprogs,
    Fcn,
    Params,
    Dclns,
    Var,
    Block,
    Output,
    If,
    While,
    Repeat,
    For,
    Loop,
    Case,
    Read,
    Exit,
    Return,
    Null,
    Integer,
    IntegerConst,
    Identifier,
    IdentifierValue,
    String,
    Char,
    CaseClause,
    Ellipses,
    Otherwise,
    Assign,
    Swap,
    True,
    LE,
    LT,
    GE,
    GT,
    EQ,
    NE,
    Plus,
    Minus,
    Or,
    Multiply,
    Divide,
    And,
    Mod,
    Not,
    Eof,
    Call,
    Succ,
    Pred,
    Chr,
    Ord
  };

  std::vector<TreeNode> children;
  Type type;
  void *data;

  void print();
  std::string toString();

private:
  static std::map<Type, std::string> _tokenRepresentationMap;
  static bool isInitialized;

  void printLayer(std::string prefix);
};

#endif
