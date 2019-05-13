template <typename vt>
class fib_heap {
    class fib_node {
       public:
        fib_node(const vt &v, const int &n)
            : parent(NULL), child(NULL), degree(0), marked(false), value(v) {}
        fib_node *parent;
        fib_node *prev;
        fib_node *next;
        fib_node *child;
        size_t degree;
        bool marked;
        vt value;
    };

   public:
    class iterator {
       public:
        iterator() : p(NULL) {}

        iterator(fib_node *p_) : p(p_) {}

        vt &operator*() { return p->value; }
        vt *operator->() { return &p->value; }
        bool operator==(iterator &other) { return p == other.p; }
        bool operator!=(iterator &other) { return p != other.p; }
        bool empty() { return !p; }

       private:
        friend class fib_heap;
        fib_node *p;
    };

    fib_heap() : minRoot(NULL), combineVec(16) {}

    ~fib_heap() { clear(); }

    iterator insert(const vt &v, const int &n) {
        fib_node *newNode = new fib_node(v, n);
        if (!minRoot) {
            minRoot = newNode->next = newNode->prev = newNode;
        } else {
            newNode->prev = minRoot;
            newNode->next = minRoot->next;
            minRoot->next->prev = newNode;
            minRoot->next = newNode;
            if (newNode->value < minRoot->value) minRoot = newNode;
        }
        return iterator(newNode);
    }

    bool empty() { return minRoot == NULL; }

    vt &minR() { return minRoot->value; }

    // heap must not be empty
    void deleteMin() {
        // make minRoot's children roots
        fib_node *child = minRoot->child;
        if (child) {
            fib_node *curchild = child;
            do {
                curchild->parent = NULL;
                curchild->marked = false;
                curchild = curchild->next;
            } while (child != curchild);
            child->prev->next = minRoot->next;
            minRoot->next->prev = child->prev;
            child->prev = minRoot;
            minRoot->next = child;
        }

        // combine root with equal degree
        fib_node *curNode = minRoot->next;
        fib_node *nextNode;
        while (curNode != minRoot) {
            nextNode = curNode->next;
            size_t degree = curNode->degree;
            fib_node *target = combineVec[degree];
            while (target) {
                if (target->value < curNode->value) {
                    fib_node *tmp = curNode;
                    curNode = target;
                    target = tmp;
                }
                // combine target to curNode
                target->next->prev = target->prev;
                target->prev->next = target->next;
                if (!curNode->child) {
                    curNode->child = target->next = target->prev = target;
                } else {
                    fib_node *child = curNode->child;
                    target->prev = child;
                    target->next = child->next;
                    child->next->prev = target;
                    child->next = target;
                }
                target->parent = curNode;
                combineVec[degree] = NULL;
                degree = ++curNode->degree;
                if (degree > combineVec.size()) combineVec.resize(degree);
                target = combineVec[degree];
            }
            combineVec[degree] = curNode;
            curNode = nextNode;
        }

        // find new min and clear combineVec
        curNode = minRoot->next;
        fib_node *curMin = NULL;
        while (curNode != minRoot) {
            combineVec[curNode->degree] = NULL;
            if (!curMin || curNode->value < curMin->value) curMin = curNode;
            curNode = curNode->next;
        }
        minRoot->next->prev = minRoot->prev;
        minRoot->prev->next = minRoot->next;
        delete minRoot;
        minRoot = curMin;
    }

    void decrease(iterator it) {
        fib_node *node = it.p;
        fib_node *parent = node->parent;
        if (parent) {
            if (!(node->value < parent->value)) return;
            cut(node);
        }
        if (node->value < minRoot->value) minRoot = node;
    }

    void erase(iterator it) {
        fib_node *node = it.p;
        if (node->parent) {
            cut(node);
        } else if (node == minRoot) {
            deleteMin();
            return;
        }
        fib_node *child = node->child;
        if (child) {
            fib_node *curchild = child;
            do {
                curchild->parent = NULL;
                curchild->marked = false;
                curchild = curchild->next;
            } while (child != curchild);
            child->prev->next = node->next;
            node->next->prev = child->prev;
            child->prev = node->prev;
            node->prev->next = child;
        } else {
            node->next->prev = node->prev;
            node->prev->next = node->next;
        }
        delete node;
    }

    void clear() {
        clearDescendants(minRoot);
        minRoot = NULL;
    }

   private:
    // node must not be root
    void cut(fib_node *node) {
        do {
            fib_node *parent = node->parent;
            if (--parent->degree == 0) {
                parent->child = NULL;
            } else {
                node->next->prev = node->prev;
                node->prev->next = node->next;
                parent->child = node->next;
            }
            node->parent = NULL;
            node->marked = false;
            node->next = minRoot->next;
            node->prev = minRoot;
            minRoot->next->prev = node;
            minRoot->next = node;
            node = parent;
        } while (node->marked);
        if (node->parent) node->marked = true;
    }

    void clearDescendants(fib_node *child) {
        if (!child) return;
        fib_node *curchild = child;
        do {
            clearDescendants(curchild->child);
            fib_node *tmp = curchild;
            curchild = curchild->next;
            delete tmp;
        } while (curchild != child);
    }

   public:
    fib_node *minRoot;
    std::vector<fib_node *> combineVec;
};