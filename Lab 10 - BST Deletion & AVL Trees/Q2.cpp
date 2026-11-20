/*
 * Name            : Fahad Ali
 * Registration No : 554809
 * Section         : BSCS-15_   <-- (write D or E here)
 * Course          : Data Structures and Algorithms - Lab 10
 * Task            : Q2 - AVL insertion and rotations (LL, RR, LR, RL)
 *
 * Notes: I wrote all of this code myself using the concept review in the lab
 * handout and the rotation logic discussed in class. No external help was used.
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

// I record which rotations happen during an insertion so I can print them
// and compare them with my hand trace.
string rotationLog;

// New node: null children, height 1.
Node* createNode(int value) {
    Node* n = new Node;
    n->data = value;
    n->left = n->right = nullptr;
    n->height = 1;
    return n;
}

// height(nullptr) = 0, a leaf has height 1.
int height(Node* n) { return n ? n->height : 0; }

// height = 1 + max(left height, right height)
void updateHeight(Node* n) {
    if (n) n->height = 1 + max(height(n->left), height(n->right));
}

// balance factor = left height - right height
int getBalance(Node* n) { return n ? height(n->left) - height(n->right) : 0; }

// Right rotation (fixes a left-heavy LL case). Returns the new subtree root.
/*
         y                x
        / \              / \
       x   T3    -->   T1   y
      / \                  / \
    T1   T2              T2   T3
*/
Node* rightRotate(Node* root) {
    Node* newRoot = root->left;
    Node* T2 = newRoot->right;
    newRoot->right = root;      // old root goes down to the right
    root->left = T2;            // the middle subtree changes parent
    updateHeight(root);         // old root first (it is now lower) ...
    updateHeight(newRoot);      // ... then the new root
    return newRoot;
}

// Left rotation (fixes a right-heavy RR case). Returns the new subtree root.
Node* leftRotate(Node* root) {
    Node* newRoot = root->right;
    Node* T2 = newRoot->left;
    newRoot->left = root;       // old root goes down to the left
    root->right = T2;
    updateHeight(root);         // old root first
    updateHeight(newRoot);      // then new root
    return newRoot;
}

// AVL insertion: normal BST insert, then fix heights/balance on the way back up.
// I assign the returned root to the parent's pointer (or main's root).
Node* insertAVL(Node* root, int value) {
    // 1) ordinary BST insertion (duplicates are ignored)
    if (root == nullptr) return createNode(value);
    if (value < root->data)      root->left  = insertAVL(root->left, value);
    else if (value > root->data) root->right = insertAVL(root->right, value);
    else return root;

    // 2) update this node's height BEFORE checking its balance
    updateHeight(root);

    // 3) check balance and apply the right rotation(s)
    int bf = getBalance(root);

    if (bf > 1 && value < root->left->data) {            // Left-Left
        rotationLog += "LL case at " + to_string(root->data) + " -> right rotate(" + to_string(root->data) + "); ";
        return rightRotate(root);
    }
    if (bf < -1 && value > root->right->data) {          // Right-Right
        rotationLog += "RR case at " + to_string(root->data) + " -> left rotate(" + to_string(root->data) + "); ";
        return leftRotate(root);
    }
    if (bf > 1 && value > root->left->data) {            // Left-Right
        rotationLog += "LR case at " + to_string(root->data) + " -> left rotate(" + to_string(root->left->data) +
                       ") then right rotate(" + to_string(root->data) + "); ";
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (bf < -1 && value < root->right->data) {          // Right-Left
        rotationLog += "RL case at " + to_string(root->data) + " -> right rotate(" + to_string(root->right->data) +
                       ") then left rotate(" + to_string(root->data) + "); ";
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;   // already balanced
}

// ---------- traversals and display ----------
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

// Sideways tree drawing: right subtree on top, root at the left.
void printTree(Node* r, int space = 0) {
    if (!r) return;
    printTree(r->right, space + 6);
    cout << string(space, ' ') << r->data << " (h=" << r->height << ", bf=" << getBalance(r) << ")\n";
    printTree(r->left, space + 6);
}

// I verify: BST order, stored height is correct, and every balance factor is -1, 0 or 1.
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

// Release every node (postorder).
Node* freeTree(Node* r) {
    if (!r) return nullptr;
    freeTree(r->left);
    freeTree(r->right);
    delete r;
    return nullptr;
}

// Runs one insertion sequence on its own empty AVL tree and prints everything
// that the lab asks for: imbalance + rotation, final tree, traversals, verification.
void runSequence(const string& label, const vector<int>& seq, const string& myExpectedImbalance,
                 const vector<int>& expPre, const vector<int>& expIn) {
    cout << "\n=========== Sequence " << label << " ===========\n";
    Node* root = nullptr;                       // separate empty tree for each sequence
    rotationLog.clear();
    cout << "Insert order: " << vecToString(seq) << "\n";
    for (size_t i = 0; i < seq.size(); i++) root = insertAVL(root, seq[i]);

    cout << "My expected imbalance : " << myExpectedImbalance << "\n";
    cout << "Rotation(s) performed : " << (rotationLog.empty() ? "none" : rotationLog) << "\n";
    cout << "Final tree:\n";
    printTree(root);

    vector<int> pre, in;
    preorder(root, pre);
    inorder(root, in);
    cout << "Preorder : " << vecToString(pre) << "\n";
    cout << "Inorder  : " << vecToString(in) << "\n";

    bool ok = isAVL(root) && pre == expPre && in == expIn;
    cout << "Every node balanced & BST valid & matches my trace: " << (ok ? "PASS" : "FAIL") << "\n";

    root = freeTree(root);                      // no leaks
}

int main() {
    cout << "==== Lab 10 - Q2: AVL Insertion and Rotations ====\n";
    cout << "Fahad Ali | 554809\n";

    // (a) 30, 20, 10 : 30 becomes left-heavy (bf = 2) and its left child 20 is
    //     also left-heavy -> Left-Left -> one right rotation at 30.
    runSequence("(a) 30, 20, 10", {30, 20, 10},
                "Node 30 has bf=+2, new key in left-left -> LL, single right rotation",
                {20, 10, 30}, {10, 20, 30});

    // (b) 10, 20, 30 : 10 becomes right-heavy (bf = -2), right child 20 is right-heavy
    //     -> Right-Right -> one left rotation at 10.
    runSequence("(b) 10, 20, 30", {10, 20, 30},
                "Node 10 has bf=-2, new key in right-right -> RR, single left rotation",
                {20, 10, 30}, {10, 20, 30});

    // (c) 30, 10, 20 : 30 has bf = +2 but its left child 10 is right-heavy
    //     -> Left-Right -> left rotate at 10, then right rotate at 30.
    runSequence("(c) 30, 10, 20", {30, 10, 20},
                "Node 30 has bf=+2, new key in left-right -> LR, left rotate 10 then right rotate 30",
                {20, 10, 30}, {10, 20, 30});

    // (d) 10, 30, 20 : 10 has bf = -2 but its right child 30 is left-heavy
    //     -> Right-Left -> right rotate at 30, then left rotate at 10.
    runSequence("(d) 10, 30, 20", {10, 30, 20},
                "Node 10 has bf=-2, new key in right-left -> RL, right rotate 30 then left rotate 10",
                {20, 10, 30}, {10, 20, 30});

    // Extra tests: a longer sequence, and duplicates being ignored.
    // 10,20,30,40,50,25 : RR at 10, RR at 30, then RL at 20 (checks rotations deeper in the tree).
    runSequence("(extra) 10, 20, 30, 40, 50, 25", {10, 20, 30, 40, 50, 25},
                "Several rotations deeper in the tree",
                {30, 20, 10, 25, 40, 50}, {10, 20, 25, 30, 40, 50});
    runSequence("(extra) duplicates 20, 10, 20, 30, 10", {20, 10, 20, 30, 10},
                "No imbalance; duplicates must be ignored",
                {20, 10, 30}, {10, 20, 30});

    cout << "\nAll trees released.\n";
    return 0;
}
