#include "Group.h"

Group::Group() {
}

void Group::sync() {
    {
        lockGuard_t g(addLock);
        for (auto &v : addBuffer) {
            nodes.insert(v);
        }
        addBuffer.clear();
    }
    {
        lockGuard_t g(remLock);
        for (Node *v : removeBuffer) {
            for (nodes_t::iterator it = nodes.begin(); it != nodes.end();) {
                if (it->second.get() == v) {
                    it = nodes.erase(it);
                } else {
                    ++it;
                }
            }
        }
        removeBuffer.clear();
    }
}

void Group::add(const node_t &n, int priority) {
    lockGuard_t g(addLock);
    addBuffer.emplace_back(priority, n);
}

void Group::remove(Node *ptr) {
    lockGuard_t g(remLock);
    removeBuffer.push_back(ptr);
}

void Group::render() {
    for (auto &p : nodes) {
        p.second->render();
    }
}

