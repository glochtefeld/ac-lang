#ifndef AC_AST_TREE
#define AC_AST_TREE
#include "node.hpp"
#include <vector>
namespace AC {

class Tree {
private:
    std::vector<Node> nodes{};

public:
    Tree() = default;
};

}
#endif
