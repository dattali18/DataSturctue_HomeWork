#include "Trie.h"


#include <iostream>
#include <list>
#include <queue>
#include <tuple>


TrieNode* getNode(void)
{
    // init the new node and returning it
    TrieNode* newNode = new TrieNode;
    for (size_t i = 0; i < ALPHABET_SIZE; i++)
    {
        newNode->children[i] = nullptr;
    }
    newNode->isWordEnd = false;
    return newNode;
}

bool isEmpty(TrieNode* root)
{
    for (size_t i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i])
            return false;
    }
    return true;
}

bool isLastNode(TrieNode* root)
{
    return root->children == nullptr;
}

bool insertT(TrieNode* root, string key)
{
    // if the world is already in the trie there is no need to insert it so we return false
    if (searchT(root, key))
        return false;
    TrieNode* current = root;
    // we loop over each letter in the key and we either add a new node or if a node with the letter allready exist just pass on
    for (size_t i = 0; i < key.length(); i++)
    {
        // if the current letter is not in the children of the current level
        // we create a new TrieNode 
        if (current->children[CHAR_TO_INDEX(key[i])] == nullptr) {
            TrieNode* newNode = getNode();
            current->children[CHAR_TO_INDEX(key[i])] = newNode;
            current = newNode;
        }
        // if the current letter is in the children of the current level so we don't need to add the letter and we just go on to the next level
        else {
            current = current->children[CHAR_TO_INDEX(key[i])];
        }
    }
    // when finnish lopping the world is in and we need to update the last node to be isWordEnd = true
    current->isWordEnd = true;
    return true;
}

bool delT(TrieNode* root, string key)
{
    if (searchT(root, key) == false)
        return false;
    return delR(root, key, 0) != nullptr;
}

TrieNode* delR(TrieNode* root, string key, int lvl)
{
    // if tree is empty
    if(!root)
        return nullptr;
    // if the last char of the key is beeing processed
    if (lvl == key.length()) {
        // This node is no more end of word after
        // removal of given key
        if (root->isWordEnd)
            root->isWordEnd = false;
        // If given is not prefix of any other word
        if (isEmpty(root)) {
            delete root;
            root = nullptr;
        } 
        return root;
    }
    // if it's not the last char
    root->children[CHAR_TO_INDEX(key[lvl])] = delR(root->children[CHAR_TO_INDEX(key[lvl])], key, lvl + 1);

    // If root does not have any child (its only child got
    // deleted), and it is not end of another word.
    if (isEmpty(root) && root->isWordEnd == false) {
        delete root;
        root = nullptr;
    }
    return root;
}

bool searchT(TrieNode* root, string key)
{
    TrieNode* current = root;
    // we loop over every char in the key and find our way in the trie struct
    for (size_t i = 0; i < key.length(); i++)
    {
        // if the current node doesn't have a child for the current char the word is not in the trie struct
        if (current->children[CHAR_TO_INDEX(key[i])] == nullptr) {
            return false;
        }
        else {
            current = current->children[CHAR_TO_INDEX(key[i])];
        }
    }
    // now that we are at the end of the word we need to check is the isWordEnd flag is true
    // is current->isWordEnd is true the word is in else return false
    return (current != nullptr && current->isWordEnd);
}

void suggestionsRec(TrieNode* root, string currPrefix)
{
}

int printAutoSuggestionsT(TrieNode* root, string query)
{
    std::list<std::string> list;
    std::string pre = query;
    TrieNode* current = root;

    for (size_t i = 0; i < query.length(); i++)
    {
        // if one of the link is null the query is not in the trie
        if (current->children[CHAR_TO_INDEX(query[i])] == nullptr)
            return 0;
        current = current->children[CHAR_TO_INDEX(query[i])];
    }
    TrieNode* start = current;
    // now we will go through every child of the string node and add the word in it
    std::queue<std::tuple<TrieNode*, std::string>> queue;
    queue.push(std::make_tuple(start, pre));
    while (!queue.empty()) {
        std::tuple<TrieNode*, std::string> currentItem = queue.front();
        current = std::get<0>(currentItem);
        queue.pop();

        if (current->isWordEnd) {
            list.emplace_front(std::get<1>(currentItem));
        }

        for (size_t i = 0; i < ALPHABET_SIZE; i++)
        {
            if (current->children[i] != nullptr) {
                queue.push(std::make_tuple(current->children[i],std::string( std::get<1>(currentItem) + (char)('a' + i))));
            }
        }
    }
    if (list.empty())
        return 0;
    for(auto itr = list.begin(); itr != list.end(); ++itr)
    {
        std::cout << *itr << std::endl;
    }
    return 1;
}

void printT(TrieNode* t, int level)
{
    if (t == nullptr)
        return;
    for (size_t i = 0; i < ALPHABET_SIZE; i++)
    {
        if (t->children[i] != nullptr) {

            for (size_t j = 0; j < level; j++)
            {
                std::cout << "  ";
            }
            std::cout << (char)('a' + i) << ": " << std::endl;;
            printT(t->children[i], level + 1);
            
        }
    }
    
}
