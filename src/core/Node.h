#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

class Node {
public:
    virtual ~Node() = 0;
    virtual void render() = 0;
};

#endif

