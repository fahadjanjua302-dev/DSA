/*
 * Name            : Fahad Ali
 * Registration No : 554809
 * Section         : BSCS-15_   <-- (write D or E here)
 * Course          : Data Structures and Algorithms - Lab 10
 * Task            : Q1 - BST deletion (leaf, one child, two children)
 *
 * Notes: I wrote all of this code myself using the concept review in the lab
 * handout. No external help was used.
 */
#include <iostream>
#include <string>
#include <vector>
#include <climits>
using namespace std;

// Node as given in the lab. I keep the height field but ignore it in Task 1.
struct Node {
    int data;
    Node *left, *right;
    int height;
};

// I create a new node with null children and height 1.
Node* createNode(int value) {
    Node* n = new Node;
    n->data = value;
    n->left = n->right = nullptr;
    n->height = 1;
    return n;
}

// Standard BST insertion. I ignore duplicates and return the (possibly new) subtree root.
Node* insertBST(Node* root, int value) {
    if (root == nullptr) return createNode(value);
    if (value < root->data)      root->left  = insertBST(root->left, value);
    else if (value > root->data) root->right = insertBST(root->right, value);
    // equal key: duplicate, so I do nothing
    return root;
}

// Helper: I keep going left to find the smallest key of a subtree
// (this is the inorder successor when I call it on the right subtree).
Node* minValueNode(Node* node) {
    while (node != nullptr && node->left != nullptr) node = node->left;
    return node;
}

// Recursive BST deletion. I always return the updated subtree root so that the
// parent (or main) can reconnect it.
Node* deleteBST(Node* root, int value) {
    // Empty tree or key not found: nothing to delete, tree stays unchanged.
    if (root == nullptr) return nullptr;

    if (value < root->data) {
        root->left = deleteBST(root->left, value);      // key is in the left subtree
    } else if (value > root->data) {
        root->right = deleteBST(root->right, value);    // key is in the right subtree
    } else {
        // I found the node to delete.
        if (root->left == nullptr && root->right == nullptr) {
            // Case 1: leaf. I just free it and return nullptr to the parent.
            delete root;
            return nullptr;
        }
        if (root->left == nullptr) {
            // Case 2a: only a right child. The child takes the node's place.
            Node* child = root->right;
            delete root;
            return child;
        }
        if (root->right == nullptr) {
            // Case 2b: only a left child. The child takes the node's place.
            Node* child = root->left;
            delete root;
            return child;
        }
        // Case 3: two children. I copy the smallest key of the right subtree
        // (inorder successor) into this node, then delete that successor
        // key from the right subtree (it has at most one child, so it is easy).
        Node* successor = minValueNode(root->right);
        root->data = successor->data;
        root->right = deleteBST(root->right, successor->data);
    }
    return root;
}

// ---------- traversal / display helpers ----------
void inorder(Node* root, vector<int>& out) {
    if (!root) return;
    inorder(root->left, out);
    out.push_back(root->data);
    inorder(root->right, out);
}

string vecToString(const vector<int>& v) {
    if (v.empty()) return "(empty)";
    string s;
    for (size_t i = 0; i < v.size(); i++) s += to_string(v[i]) + " ";
    return s;
}

// I print the tree sideways (right subtree on top, root on the left) so I can
// "draw" it in the console and compare with my notebook drawing.
void printTree(Node* root, int space = 0) {
    if (!root) return;
    printTree(root->right, space + 6);
    cout << string(space, ' ') << root->data << "\n";
    printTree(root->left, space + 6);
}

void showTree(Node* root) {
    if (!root) { cout << "      (empty tree)\n"; return; }
    printTree(root);
}

// I check that the BST ordering property holds everywhere.
bool isBST(Node* n, long long lo, long long hi) {
    if (!n) return true;
    if (n->data <= lo || n->data >= hi) return false;
    return isBST(n->left, lo, n->data) && isBST(n->right, n->data, hi);
}

// I release every node (postorder) so there are no leaks when the program ends.
Node* freeTree(Node* root) {
    if (!root) return nullptr;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
    return nullptr;
}

// Runs one deletion test: prints the tree before, the case and my prediction,
// does root = deleteBST(root, value), prints the result and compares with my prediction.
Node* testDelete(Node* root, int value, const string& caseName, const vector<int>& predicted) {
    cout << "\n>>> Delete " << value << "  | Case: " << caseName << "\n";
    cout << "    Tree before:\n";
    showTree(root);
    cout << "    Predicted inorder: " << vecToString(predicted) << "\n";

    root = deleteBST(root, value);          // root must be reassigned

    vector<int> actual;
    inorder(root, actual);
    cout << "    Tree after:\n";
    showTree(root);
    cout << "    Actual inorder   : " << vecToString(actual) << "\n";
    bool ok = (actual == predicted) && isBST(root, LLONG_MIN, LLONG_MAX);
    cout << "    Result: " << (ok ? "PASS (matches prediction, BST valid)" : "FAIL") << "\n";
    return root;
}

int main() {
    cout << "==== Lab 10 - Q1: BST Deletion ====\n";
    cout << "Fahad Ali | 554809\n";

    // ---------------- Main scenario ----------------
    // Insert 50, 30, 70, 20, 40, 60, 80, 65. Resulting tree (my drawing):
    /*
                 50
               /    \
             30      70
            /  \    /  \
          20   40  60   80
                     \
                      65
    */
    Node* root = nullptr;
    int keys[] = {50, 30, 70, 20, 40, 60, 80, 65};
    for (int k : keys) root = insertBST(root, k);

    cout << "\nInitial tree:\n";
    showTree(root);
    vector<int> init;
    inorder(root, init);
    cout << "Initial inorder: " << vecToString(init) << "\n";

    // 1) 20 is a leaf (Case 1)          -> 30 40 50 60 65 70 80
    root = testDelete(root, 20, "Leaf node (zero children)",
                      vector<int>{30, 40, 50, 60, 65, 70, 80});

    // 2) 60 has only a right child 65 (Case 2) -> 65 replaces 60
    root = testDelete(root, 60, "One child (60 has only right child 65)",
                      vector<int>{30, 40, 50, 65, 70, 80});

    // 3) 50 is the root with two children (Case 3). Inorder successor = 65
    //    (smallest key in right subtree). Root becomes 65, then old 65 leaf is removed.
    root = testDelete(root, 50, "Two children (root, successor = 65)",
                      vector<int>{30, 40, 65, 70, 80});

    // ---------------- Boundary cases ----------------
    cout << "\n---------- Boundary cases ----------\n";

    // Missing key: the tree must stay unchanged.
    root = testDelete(root, 999, "Missing key (tree must stay unchanged)",
                      vector<int>{30, 40, 65, 70, 80});

    // Deletion from an empty tree.
    Node* emptyTree = nullptr;
    cout << "\n>>> Delete 10 from an EMPTY tree\n";
    emptyTree = deleteBST(emptyTree, 10);
    cout << "    Result: " << (emptyTree == nullptr ? "PASS (still nullptr, no crash)" : "FAIL") << "\n";

    // Deletion of the only node: must return nullptr.
    Node* single = createNode(10);
    cout << "\n>>> Delete the ONLY node (10) of a one-node tree\n";
    single = deleteBST(single, 10);
    cout << "    Result: " << (single == nullptr ? "PASS (returned nullptr)" : "FAIL") << "\n";

    // Extra: root with only one child, and a two-child node that is not the root.
    Node* extra = nullptr;
    int ek[] = {10, 5, 3};
    for (int k : ek) extra = insertBST(extra, k);          // 10 -> 5 -> 3 (left chain)
    extra = testDelete(extra, 10, "Root with one child (left only)", vector<int>{3, 5});
    extra = freeTree(extra);

    // Extra: delete a non-root node with two children (70 in the main tree).
    root = testDelete(root, 70, "Two children, non-root node (successor = 80)",
                      vector<int>{30, 40, 65, 80});

    // ---------------- Cleanup ----------------
    // I release all remaining nodes before the program exits.
    root = freeTree(root);
    cout << "\nAll remaining nodes released. root == nullptr: "
         << (root == nullptr ? "yes" : "no") << "\n";
    return 0;
}
