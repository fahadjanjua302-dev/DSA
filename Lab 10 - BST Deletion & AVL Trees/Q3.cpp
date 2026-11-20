/*
 * Name            : Fahad Ali
 * Registration No : 554809
 * Section         : BSCS-15_   <-- (write D or E here)
 * Course          : Data Structures and Algorithms - Lab 10
 * Task            : Q3 - AVL insertion and deletion (with rebalancing at every ancestor)
 *
 * Notes: I wrote all of this code myself. I reused my insertion/rotation code
 * from Q2 and my BST deletion logic from Q1. No external help was used.
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
    int height;
};

// I log every rotation so I can print which ancestor was unbalanced and what I did.
string rotationLog;

Node* createNode(int value) {
    Node* n = new Node;
    n->data = value;
    n->left = n->right = nullptr;
    n->height = 1;
    return n;
}

int height(Node* n) { return n ? n->height : 0; }                      // height(nullptr) = 0
void updateHeight(Node* n) { if (n) n->height = 1 + max(height(n->left), height(n->right)); }
int getBalance(Node* n) { return n ? height(n->left) - height(n->right) : 0; }  // left - right

// Right rotation: left child becomes the new root. I update the OLD root's height first.
Node* rightRotate(Node* root) {
    Node* newRoot = root->left;
    Node* T2 = newRoot->right;
    newRoot->right = root;
    root->left = T2;
    updateHeight(root);
    updateHeight(newRoot);
    return newRoot;
}

// Left rotation: right child becomes the new root. Old root's height first.
Node* leftRotate(Node* root) {
    Node* newRoot = root->right;
    Node* T2 = newRoot->left;
    newRoot->left = root;
    root->right = T2;
    updateHeight(root);
    updateHeight(newRoot);
    return newRoot;
}

// One function that restores balance at a node whose height is already updated.
// I choose the rotation using the CHILD's balance factor (not the inserted/deleted
// value), so the same function works for insertion and for deletion.
Node* rebalance(Node* root) {
    int bf = getBalance(root);

    if (bf > 1) {                                   // left-heavy
        if (getBalance(root->left) >= 0) {          // child bf >= 0 -> single right rotation
            rotationLog += "node " + to_string(root->data) + " left-heavy, left child bf>=0 -> right rotate(" +
                           to_string(root->data) + "); ";
        } else {                                    // child bf < 0 -> left then right
            rotationLog += "node " + to_string(root->data) + " left-heavy, left child bf<0 -> left rotate(" +
                           to_string(root->left->data) + ") then right rotate(" + to_string(root->data) + "); ";
            root->left = leftRotate(root->left);
        }
        return rightRotate(root);
    }
    if (bf < -1) {                                  // right-heavy
        if (getBalance(root->right) <= 0) {         // child bf <= 0 -> single left rotation
            rotationLog += "node " + to_string(root->data) + " right-heavy, right child bf<=0 -> left rotate(" +
                           to_string(root->data) + "); ";
        } else {                                    // child bf > 0 -> right then left
            rotationLog += "node " + to_string(root->data) + " right-heavy, right child bf>0 -> right rotate(" +
                           to_string(root->right->data) + ") then left rotate(" + to_string(root->data) + "); ";
            root->right = rightRotate(root->right);
        }
        return leftRotate(root);
    }
    return root;                                    // balance factor is -1, 0 or 1: nothing to do
}

// AVL insertion (same logic as Q2): BST insert, update height, rebalance.
Node* insertAVL(Node* root, int value) {
    if (root == nullptr) return createNode(value);
    if (value < root->data)      root->left  = insertAVL(root->left, value);
    else if (value > root->data) root->right = insertAVL(root->right, value);
    else return root;                               // duplicate: ignored

    updateHeight(root);
    return rebalance(root);
}

// Smallest node of a subtree (inorder successor helper from Q1).
Node* minValueNode(Node* node) {
    while (node && node->left) node = node->left;
    return node;
}

// AVL deletion: BST deletion first, then update height and rebalance at every
// ancestor while the recursion returns. Always returns the new subtree root.
Node* deleteAVL(Node* root, int value) {
    // Empty tree / key not found: nothing changes.
    if (root == nullptr) return nullptr;

    if (value < root->data) {
        root->left = deleteAVL(root->left, value);
    } else if (value > root->data) {
        root->right = deleteAVL(root->right, value);
    } else {
        // Found the node to delete.
        if (root->left == nullptr || root->right == nullptr) {
            // Leaf or one child: the (possibly null) child replaces the node.
            // If it is a leaf this returns nullptr, i.e. the subtree is now empty.
            Node* child = (root->left != nullptr) ? root->left : root->right;
            delete root;
            return child;
        }
        // Two children: copy the inorder successor's key here, then delete the
        // successor from the right subtree.
        Node* successor = minValueNode(root->right);
        root->data = successor->data;
        root->right = deleteAVL(root->right, successor->data);
    }

    // On the way back up I update this ancestor's height, then check balance.
    updateHeight(root);
    return rebalance(root);
}

// ---------- traversals / display / verification ----------
void preorder(Node* r, vector<int>& out) {
    if (!r) return;
    out.push_back(r->data);
    preorder(r->left, out);
    preorder(r->right, out);
}
void inorder(Node* r, vector<int>& out) {
    if (!r) return;
    inorder(r->left, out);
    out.push_back(r->data);
    inorder(r->right, out);
}
string vecToString(const vector<int>& v) {
    if (v.empty()) return "(empty)";
    string s;
    for (size_t i = 0; i < v.size(); i++) s += to_string(v[i]) + " ";
    return s;
}

// Sideways drawing of the tree (right subtree on top).
void printTree(Node* r, int space = 0) {
    if (!r) return;
    printTree(r->right, space + 6);
    cout << string(space, ' ') << r->data << "\n";
    printTree(r->left, space + 6);
}

// I print key, height and balance factor of every node (inorder) to verify the result.
void printNodeInfo(Node* r) {
    if (!r) return;
    printNodeInfo(r->left);
    cout << "   key=" << r->data << "  height=" << r->height << "  balance=" << getBalance(r) << "\n";
    printNodeInfo(r->right);
}

// Verifies BST order, correct stored heights and every balance factor in {-1,0,1}.
bool checkAVL(Node* n, long long lo, long long hi, int& h) {
    if (!n) { h = 0; return true; }
    if (n->data <= lo || n->data >= hi) return false;
    int lh, rh;
    if (!checkAVL(n->left, lo, n->data, lh)) return false;
    if (!checkAVL(n->right, n->data, hi, rh)) return false;
    h = 1 + max(lh, rh);
    if (n->height != h) return false;
    int bf = lh - rh;
    return bf >= -1 && bf <= 1;
}
bool isAVL(Node* r) { int h; return checkAVL(r, LLONG_MIN, LLONG_MAX, h); }

// Release all nodes (postorder).
Node* freeTree(Node* r) {
    if (!r) return nullptr;
    freeTree(r->left);
    freeTree(r->right);
    delete r;
    return nullptr;
}

// Prints everything the lab asks for after an operation and compares with my hand trace.
void report(const string& title, Node* root, const vector<int>& expPre, const vector<int>& expIn) {
    cout << "\n--- " << title << " ---\n";
    cout << "Rotation(s): " << (rotationLog.empty() ? "none needed (all ancestors balanced)" : rotationLog) << "\n";
    rotationLog.clear();
    cout << "Tree:\n";
    if (!root) cout << "      (empty tree)\n"; else printTree(root);
    vector<int> pre, in;
    preorder(root, pre);
    inorder(root, in);
    cout << "Preorder: " << vecToString(pre) << "\n";
    cout << "Inorder : " << vecToString(in) << "\n";
    cout << "Node details:\n";
    if (!root) cout << "   (none)\n"; else printNodeInfo(root);
    bool ok = isAVL(root) && pre == expPre && in == expIn;
    cout << "Check (AVL valid + matches my trace): " << (ok ? "PASS" : "FAIL") << "\n";
}

int main() {
    cout << "==== Lab 10 - Q3: AVL Insertion and Deletion ====\n";
    cout << "Fahad Ali | 554809\n";

    // =========== Main scenario ===========
    // Insert 30, 20, 40, 10, 25, 50, 5 into an empty AVL tree. No rotation is needed.
    cout << "\n########## Main scenario ##########\n";
    Node* root = nullptr;
    int keys[] = {30, 20, 40, 10, 25, 50, 5};
    for (int k : keys) root = insertAVL(root, k);
    report("After inserting 30, 20, 40, 10, 25, 50, 5", root,
           {30, 20, 10, 5, 25, 40, 50}, {5, 10, 20, 25, 30, 40, 50});

    // Delete 50 (leaf). Ancestor 40 is fine, but ancestor 30 gets bf = 3 - 1 = +2.
    // Its left child 20 has bf = +1 (>= 0) -> single RIGHT rotation at 30.
    root = deleteAVL(root, 50);
    report("After deleting 50 (leaf)", root,
           {20, 10, 5, 30, 25, 40}, {5, 10, 20, 25, 30, 40});

    // Delete 40 (leaf). 30 now has only left child 25 (bf = +1) and 20 has bf = 0.
    // Every ancestor is balanced, so NO rotation is needed.
    root = deleteAVL(root, 40);
    report("After deleting 40 (leaf)", root,
           {20, 10, 5, 30, 25}, {5, 10, 20, 25, 30});

    // Extra: delete a node with two children (root 20, successor = 25).
    root = deleteAVL(root, 20);
    report("Extra: after deleting 20 (root, two children)", root,
           {25, 10, 5, 30}, {5, 10, 25, 30});

    root = freeTree(root);

    // =========== Boundary cases ===========
    cout << "\n########## Boundary cases ##########\n";

    // Missing key: tree must stay unchanged.
    Node* t = nullptr;
    for (int k : {20, 10, 30}) t = insertAVL(t, k);
    t = deleteAVL(t, 999);
    report("Missing key 999 in tree {20,10,30}", t, {20, 10, 30}, {10, 20, 30});
    t = freeTree(t);

    // Empty tree.
    Node* emptyTree = nullptr;
    emptyTree = deleteAVL(emptyTree, 10);
    cout << "\n--- Delete 10 from an EMPTY tree ---\n";
    cout << "Result: " << (emptyTree == nullptr ? "PASS (still nullptr, no crash)" : "FAIL") << "\n";

    // One-node tree: deleting its only node must return nullptr.
    Node* single = insertAVL(nullptr, 10);
    single = deleteAVL(single, 10);
    cout << "\n--- Delete the ONLY node of a one-node tree ---\n";
    cout << "Result: " << (single == nullptr ? "PASS (returned nullptr)" : "FAIL") << "\n";

    // =========== Heavy child has balance factor 0 ===========
    cout << "\n########## Heavy child with balance factor 0 ##########\n";

    // Left case: insert 20, 10, 30, 5, 15 -> 20(10(5,15),30). Delete 30:
    // node 20 becomes left-heavy (bf = +2) and its left child 10 has bf = 0.
    // A SINGLE right rotation at 20 is enough.
    Node* a = nullptr;
    for (int k : {20, 10, 30, 5, 15}) a = insertAVL(a, k);
    cout << "\nTree before deleting 30 (left child of 20 is 10 with bf = " << getBalance(a->left) << "):\n";
    printTree(a);
    a = deleteAVL(a, 30);
    report("Left case: delete 30, heavy child 10 has bf = 0 -> single right rotation", a,
           {10, 5, 20, 15}, {5, 10, 15, 20});
    a = freeTree(a);

    // Right case (mirror image): insert 20, 10, 30, 25, 35. Delete 10:
    // node 20 becomes right-heavy (bf = -2) and its right child 30 has bf = 0 -> single left rotation.
    Node* b = nullptr;
    for (int k : {20, 10, 30, 25, 35}) b = insertAVL(b, k);
    cout << "\nTree before deleting 10 (right child of 20 is 30 with bf = " << getBalance(b->right) << "):\n";
    printTree(b);
    b = deleteAVL(b, 10);
    report("Right case: delete 10, heavy child 30 has bf = 0 -> single left rotation", b,
           {30, 20, 25, 35}, {20, 25, 30, 35});
    b = freeTree(b);

    /*
     * Why a single rotation is correct when the heavy child's balance factor is 0:
     * Suppose node Y is left-heavy by 2 and its left child X has bf = 0, so both
     * of X's subtrees have the same height h (X has height h+1, Y's right side has height h).
     * After a right rotation, X becomes the root. X keeps its left subtree (height h).
     * Y becomes X's right child with left = X's old right subtree (height h) and
     * right = Y's old right subtree (height h), so Y has height h+1 and bf = 0.
     * The new root X then has bf = h - (h+1) = -1, which is allowed. So one rotation
     * already restores balance. A double rotation is only needed when X's bf is
     * negative: then the tall subtree is the inner one (X's right), a single
     * rotation would just move it to the other side and leave X with bf = -2.
     * (Note: this case can only happen after a deletion, never after an insertion.)
     */
    cout << "\nWhy one rotation is enough when the heavy child has bf = 0:\n"
         << "  Both subtrees of the heavy child have the same height h. After the single\n"
         << "  rotation the old root has two subtrees of height h (bf = 0, height h+1) and\n"
         << "  the new root has bf = h - (h+1) = -1 (or +1 in the mirror case), which is\n"
         << "  still allowed. A double rotation is only needed when the heavy child leans\n"
         << "  the opposite way, because a single rotation would then leave a bf of 2.\n";

    // =========== Double-rotation deletion cases (extra testing) ===========
    cout << "\n########## Double rotations after deletion ##########\n";

    // LR: insert 30, 10, 40, 20 -> 30(10(-,20),40). Delete 40:
    // 30 has bf = +2 and left child 10 has bf = -1 -> left rotate(10), right rotate(30).
    Node* c = nullptr;
    for (int k : {30, 10, 40, 20}) c = insertAVL(c, k);
    c = deleteAVL(c, 40);
    report("LR after deletion: delete 40", c, {20, 10, 30}, {10, 20, 30});
    c = freeTree(c);

    // RL: insert 10, 5, 30, 20 -> 10(5,30(20,-)). Delete 5:
    // 10 has bf = -2 and right child 30 has bf = +1 -> right rotate(30), left rotate(10).
    Node* d = nullptr;
    for (int k : {10, 5, 30, 20}) d = insertAVL(d, k);
    d = deleteAVL(d, 5);
    report("RL after deletion: delete 5", d, {20, 10, 30}, {10, 20, 30});
    d = freeTree(d);

    // Cascading rebalancing across several ancestors: insert 1..15 (perfect tree),
    // then delete 1..4 and check the tree stays AVL after every single deletion.
    Node* e = nullptr;
    for (int k = 1; k <= 15; k++) e = insertAVL(e, k);
    bool allOk = isAVL(e);
    for (int k = 1; k <= 4; k++) {
        e = deleteAVL(e, k);
        allOk = allOk && isAVL(e);
    }
    cout << "\n--- Stress check: insert 1..15, delete 1..4 ---\n";
    cout << "Tree stayed a valid AVL after every deletion: " << (allOk ? "PASS" : "FAIL") << "\n";
    rotationLog.clear();
    e = freeTree(e);

    // I released every tree above, so nothing is left allocated at exit.
    cout << "\nAll nodes released. Program finished.\n";
    return 0;
}
