#ifndef GROUP_H_INCLUDED
#define GROUP_H_INCLUDED

#include <map>
#include <algorithm>
#include <memory>
#include <mutex>
#include <vector>

#include "Node.h"

class Group: public Node {
public:
    typedef std::shared_ptr<Node> node_t;
private:
    typedef std::lock_guard<std::mutex> lockGuard_t;
    typedef std::multimap<int, node_t, std::greater<int>> nodes_t;

    nodes_t nodes;
    std::vector<Node*> removeBuffer;
    std::vector<nodes_t::value_type> addBuffer;
    std::mutex remLock;
    std::mutex addLock;
    
    void sync();

public:
    Group();
    void add(const node_t &n, int priority = 0);
    void remove(Node *ptr);
    void render() override;
};

#endif

