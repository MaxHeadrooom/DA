#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>
#include <set>
#include <map>
#include <sstream>
#include <fstream>
#include <chrono>

using ll = long long;

using std::cin;
using std::cout;

class Node
{
public:
    std::pair<std::string, unsigned long long> data;
    Node* left;
    Node* right;
    Node* parent;
    char color;

    Node(const std::pair<std::string, unsigned long long>& s)
    {
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        data = s;
        color = 'r';
    }
};

class RB_tree
{
private:
    void rotateLeft(Node* node)
    {
        Node* child = node->right;

        node->right = child->left;

        if (child->left != nullptr)
        {
            child->left->parent = node;
        }

        child->parent = node->parent;

        if (node->parent == nullptr)
        {
            root = child;
        }

        else if (node == node->parent->left)
        {
            node->parent->left = child;
        }
        else
        {
            node->parent->right = child;
        }

        child->left = node;

        node->parent = child;
    }

    void rotateRight(Node* node)
    {
        Node* child = node->left;

        node->left = child->right;

        if (child->right != nullptr)
        {
            child->right->parent = node;
        }

        child->parent = node->parent;

        if (node->parent == nullptr)
        {
            root = child;
        }

        else if (node == node->parent->right)
        {
            node->parent->right = child;
        }
        else
        {
            node->parent->left = child;
        }

        child->right = node;

        node->parent = child;
    }

    Node* seek(const std::pair<std::string, unsigned long long>& str, Node* root)
    {
        if (root == nullptr)
        {
            return nullptr;
        }

        if (str.first < root->data.first)
        {
            if (root->left != nullptr)
                return seek(str, root->left);
        }
        else
        {
            if (str.first > root->data.first)
            {
                if (root->right != nullptr)
                    return seek(str, root->right);
            }
            else
                return root;
        }

        return nullptr;
    }

    void fix(Node* node)
    {
        if (node->parent == nullptr)
        {
            node->color = 'b';
            return;
        }

        Node* parent = node->parent;

        if (parent->color == 'b')
        {
            return;
        }

        Node* grandparent = parent->parent;

        if (grandparent == nullptr)
        {
            return;
        }

        if (parent == grandparent->left)
        {
            Node* dyadya_bili = grandparent->right;

            if (dyadya_bili != nullptr and dyadya_bili->color == 'r')
            {
                parent->color = 'b';
                dyadya_bili->color = 'b';
                grandparent->color = 'r';

                fix(grandparent);
            }
            else
            {
                if (node == parent->right)
                {
                    node = parent;
                    rotateLeft(node);
                    parent = node->parent;
                }

                parent->color = 'b';
                grandparent->color = 'r';
                rotateRight(grandparent);
            }
        }
        else
        {
            Node* dyadya_bili = grandparent->left;

            if (dyadya_bili != nullptr and dyadya_bili->color == 'r')
            {
                parent->color = 'b';
                dyadya_bili->color = 'b';
                grandparent->color = 'r';
                fix(grandparent);
            }
            else
            {
                if (node == parent->left)
                {
                    node = parent;
                    rotateRight(node);
                    parent = node->parent;
                }

                parent->color = 'b';
                grandparent->color = 'r';
                rotateLeft(grandparent);
            }
        }
    }

    void fix_delete(Node* target)
    {
        while (target != root and target->color == 'b')
        {
            Node* parent = target->parent;
            if (parent->left == target)
            {
                Node* brother = parent->right;
                if (brother and brother->color == 'r')
                {
                    brother->color = 'b';
                    parent->color = 'r';
                    rotateLeft(parent);
                    brother = parent->right;
                }
                if ((!brother->left or brother->left->color == 'b') and (!brother->right or brother->right->color == 'b'))
                {
                    brother->color = 'r';
                    target = parent;
                }
                else
                {
                    if (!brother->right or brother->right->color == 'b')
                    {
                        brother->left->color = 'b';
                        brother->color = 'r';
                        rotateRight(brother);
                        brother = parent->right;
                    }
                    brother->color = parent->color;
                    parent->color = 'b';
                    brother->right->color = 'b';
                    rotateLeft(parent);
                    target = root;
                }
            }
            else
            {
                Node* brother = parent->left;
                if (brother and brother->color == 'r')
                {
                    brother->color = 'b';
                    parent->color = 'r';
                    rotateRight(parent);
                    brother = parent->left;
                }
                if ((!brother->right or brother->right->color == 'b') and (!brother->left or brother->left->color == 'b'))
                {
                    brother->color = 'r';
                    target = parent;
                }
                else {
                    if (!brother->left or brother->left->color == 'b')
                    {
                        brother->right->color = 'b';
                        brother->color = 'r';
                        rotateLeft(brother);
                        brother = parent->left;
                    }
                    brother->color = parent->color;
                    parent->color = 'b';
                    brother->left->color = 'b';
                    rotateRight(parent);
                    target = root;
                }
            }
        }
        target->color = 'b';
    }


public:

    void insert(const std::pair<std::string, unsigned long long>& str)
    {
        Node* node = new Node(str);
        Node* parent = nullptr;
        Node* cur = root;

        if (root == nullptr)
        {
            root = node;
            fix(node);
            return;
        }

        while (cur != nullptr)
        {
            parent = cur;
            if (str.first < cur->data.first)
            {
                cur = cur->left;
            }
            else
            {
                cur = cur->right;
            }
        }

        node->parent = parent;

        if (parent == nullptr)
        {
            root = cur;
        }
        else
        {
            if (parent->data > str)
                parent->left = node;
            else
                parent->right = node;
        }

        fix(node);
    }

    Node* seeker(const std::pair<std::string, unsigned long long>& str)
    {
        Node* node = seek(str, root);

        return node;
    }

    void del(const std::pair<std::string, unsigned long long>& str)
    {
        Node* node = seeker(str);

        return erase(node);
    }

    void erase(Node* node)
    {
        if (node->left and node->right)
        {
            Node* sin = node->right;
            while (sin->left)
            {
                sin = sin->left;
            }
            node->data = sin->data;
            erase(sin);
            return;
        }
        Node* parent = node->parent;
        Node*& target_edge = (!parent) ? root : (parent->left == node) ? parent->left : parent->right;
        fix_delete(node);
        if (node->right)
        {
            target_edge = node->right;
            node->right->parent = parent;
        }
        else if (node->left)
        {
            target_edge = node->left;
            node->left->parent = parent;
        }
        else
        {
            if (!parent)
            {
                root = nullptr;
            }
            else
            {
                target_edge = nullptr;
            }
        }
        node->left = node->right = nullptr;
        delete node;
    }

    void Save(std::ostream& file, Node* node)
    {
        if (node == nullptr)
        {
            return;
        }
        int keySize = (node->data.first).size();
        file.write((char*)&keySize, sizeof(int));
        file.write((char*)node->data.first.c_str(), keySize);
        file.write((char*)&(node->data.second), sizeof(unsigned long long));
        file.write((char*)&node->color, sizeof(char));

        bool hasLeft = (node->left != nullptr);
        bool hasRight = (node->right != nullptr);

        file.write((char*)&hasLeft, sizeof(bool));
        file.write((char*)&hasRight, sizeof(bool));

        if (hasLeft)
        {
            Save(file, node->left);
        }
        if (hasRight)
        {
            Save(file, node->right);
        }
    }

    Node* Load(std::istream& file)
    {
        int keysize;
        file.read((char*)&keysize, sizeof(int));

        if (file.gcount() == 0 or keysize == 0)
        {
            return nullptr;
        }

        char* key = new char[keysize + 1];
        key[keysize] = '\0';
        file.read(key, keysize);
        std::string keyString(key);
        delete[] key;

        unsigned long long value;
        file.read((char*)&value, sizeof(unsigned long long));

        char color;
        file.read((char*)&color, sizeof(char));

        bool hasLeft = false;
        bool hasRight = false;
        file.read((char*)&hasLeft, sizeof(bool));
        file.read((char*)&hasRight, sizeof(bool));

        Node* node = new Node(std::make_pair(keyString, value));
        node->color = color;

        if (hasLeft)
        {
            node->left = Load(file);
            if (node->left)
                node->left->parent = node;
        }
        if (hasRight)
        {
            node->right = Load(file);
            if (node->right)
                node->right->parent = node;
        }

        return node;
    }

    void clearHelper(Node* node)
    {
        if (node != nullptr)
        {
            clearHelper(node->left);
            clearHelper(node->right);
            delete node;
        }
    }

    void clear()
    {
        clearHelper(root);
        root = nullptr;
    }

    Node* root = nullptr;

};

void lower(std::string& str)
{
    for (char& c : str)
    {
        c = tolower(c);
    }
}

int main()
{

    cin.tie(NULL);
    cout.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    auto start = std::chrono::high_resolution_clock::now();

    RB_tree tree;

    std::string s, s1;
    unsigned long long s2;

    std::pair<std::string, unsigned long long> m;

    std::ofstream ofstr;
    std::ifstream ifstr;

    std::ifstream f("1e5.txt");

    while (cin >> s)
    {
        lower(s);
        if (s[0] != '+' and s[0] != '-' and s[0] != '!')
        {
            Node* nod = tree.seeker(std::make_pair(s, 0ULL));
            if (nod != nullptr)
            {
                cout << "OK: " << nod->data.second << '\n';
            }
            else
            {
                cout << "NoSuchWord" << '\n';
            }
        }
        else
        {
            if (s == "!")
            {
                cin >> s1;

                std::string file;

                cin >> file;

                if (s1 == "Save")
                {
                    ofstr.open(file, std::ios::out | std::ios::binary);
                    tree.Save(ofstr, tree.root);
                    cout << "OK" << '\n';
                }
                else
                {
                    tree.clear();
                    ifstr.open(file, std::ios::in | std::ios::binary);
                    tree.root = tree.Load(ifstr);
                    cout << "OK" << '\n';
                }
            }
            else
            {
                cin >> s1;
                lower(s1);

                if (s[0] == '+')
                {
                    cin >> s2;

                    std::pair<std::string, unsigned long long> pa;
                    pa = std::make_pair(s1, s2);

                    if (tree.seeker(pa) == nullptr)
                    {
                        tree.insert(pa);
                        cout << "OK" << '\n';
                    }
                    else
                    {
                        cout << "Exist" << '\n';
                    }
                }
                else
                {
                    if (s[0] == '-')
                    {
                        if (tree.seeker(std::make_pair(s1, 0ULL)) != nullptr)
                        {
                            tree.del(std::make_pair(s1, 0ULL));
                            cout << "OK" << '\n';
                        }
                        else
                        {
                            cout << "NoSuchWord" << '\n';
                        }
                    }
                }
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    //cout << duration.count() << '\n';
}
