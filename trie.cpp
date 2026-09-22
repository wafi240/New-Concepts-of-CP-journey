const int ALPHABET_SIZE = 26;

class Node
{
public:
    bool isEndOfWord;
    Node *children[ALPHABET_SIZE];

    // Node(): no params — creates a node with isEndOfWord=false and all children=nullptr
    Node()
    {
        isEndOfWord = false;
        for (int i = 0; i < ALPHABET_SIZE; i++)
            children[i] = nullptr;
    }
};

class Trie
{
private:
    Node *root;

    // deleteNode(node, key, depth): inp: Node*&, string, int — goes to end of word, unmarks it, then removes empty nodes
    bool deleteNode(Node *&node, const std::string &key, int depth)
    {
        if (node == nullptr)
            return false;

        if (depth == (int)key.length())
        {
            if (!node->isEndOfWord)
                return false;
            node->isEndOfWord = false;
            return true;
        }

        int index = key[depth] - 'a';
        if (!deleteNode(node->children[index], key, depth + 1))
            return false;

        if (!node->isEndOfWord)
        {
            bool isEmpty = true;
            for (int i = 0; i < ALPHABET_SIZE; i++)
            {
                if (node->children[i])
                {
                    isEmpty = false;
                    break;
                }
            }
            if (isEmpty)
            {
                delete node;
                node = nullptr;
            }
        }
        return true;
    }

    // destroy(node): inp: Node* — frees all nodes
    void destroy(Node *node)
    {
        if (!node)
            return;
        for (int i = 0; i < ALPHABET_SIZE; i++)
            destroy(node->children[i]);
        delete node;
    }

public:
    // Trie(): no params — creates an empty trie with a root node
    Trie() { root = new Node(); }

    // ~Trie(): no params — frees all nodes to avoid memory leak
    ~Trie() { destroy(root); }

    // insert(key): inp: string — adds a word and marks its last node
    void insert(const std::string &key)
    {
        Node *current = root;
        for (char ch : key)
        {
            int index = ch - 'a';
            if (!current->children[index])
                current->children[index] = new Node();
            current = current->children[index];
        }
        current->isEndOfWord = true;
    }

    // search(key): inp: string — returns true only if the exact word exists
    bool search(const std::string &key)
    {
        Node *current = root;
        for (char ch : key)
        {
            int index = ch - 'a';
            if (!current->children[index])
                return false;
            current = current->children[index];
        }
        return current && current->isEndOfWord;
    }

    // startsWith(prefix): inp: string — returns true if any word starts with the prefix
    bool startsWith(const std::string &prefix)
    {
        Node *current = root;
        for (char ch : prefix)
        {
            int index = ch - 'a';
            if (!current->children[index])
                return false;
            current = current->children[index];
        }
        return true;
    }

    // deleteString(key): inp: string — removes a word and cleans up unused nodes
    void deleteString(const std::string &key)
    {
        deleteNode(root, key, 0);
    }
};

