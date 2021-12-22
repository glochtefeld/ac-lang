#ifndef AC_AST_NODE
#define AC_AST_NODE
namespace AC {
class Node {
private:
    int num_children;
    Node* children[];
public:
    Node(int n): num_children(n) {}
    virtual void visit();

};

class AssignNode : Node {
    void visit() override;
};
}
#endif
