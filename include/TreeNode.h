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
    Variable,
    Constant,
    Type,
    Function,
    Return,
    Begin,
    End,
    Swap,
    Assignment,
    Integer,
    Output,
    If,
    Then,
    Else,
    While,
    Do,
    Case,
    Of,
    Elipses,
    Otherwise,
    Repeat,
    For,
    Until,
    Loop,
    Pool,
    Exit,
    LE,
    NE,
    LT,
    GE,
    GT,
    Eq,
    Mod,
    And,
    Or,
    Not,
    Read,
    Successor,
    Predecessor,
    CharFun,
    OrdFun,
    Eof,
    Colon,
    Semicolon,
    Dot,
    Comma,
    OpenBracket,
    CloseBracket,
    Plus,
    Minus,
    Multiply,
    Divide,
    Identifier,
    Number,
    Character,
    String
  };

  std::vector<TreeNode> children;
  Type type;

  void print();
  std::string toString();

private:
  static std::map<Type, std::string> _tokenRepresentationMap;
  static bool isInitialized;

  void printLayer(std::string prefix);
};

#endif