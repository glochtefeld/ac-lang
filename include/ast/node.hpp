#ifndef AC_AST_NODE
#define AC_AST_NODE
#include "scanner/token.hpp"
#include <vector>
#include <memory>
/*
 *namespace AC {
 *
 *enum class NodeType {
 *    null_node,
 *    float_node,
 *    int_node,
 *};
 *
 *class Node {
 *private:
 *    std::vector<Node*> children;
 *public:
 *    NodeType type;
 *    virtual void visit();
 *    auto get_node(int) -> Node*;
 *    void enter_symbol(char id, TokenType type);
 *};
 *
 *class ComputeNode : Node {
 *    void visit() override;
 *};
 *
 *class AssignNode : Node {
 *    void visit() override;
 *};
 *
 *
 *class SymbolReferenceNode : Node {
 *    char id;
 *    void visit() override;
 *    SymbolReferenceNode(char i): id(i) {}
 *};
 *
 *class IntConstNode : Node {
 *    void visit() override;
 *};
 *
 *class FloatConstNode : Node {
 *    void visit() override;
 *};
 *
 *auto consistent(Node*,Node*)->NodeType;
 *auto generalize(NodeType,NodeType)->NodeType;
 *void convert(Node*, NodeType);
 *
 *}
 */
#endif
