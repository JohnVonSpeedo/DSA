#include <bits/stdc++.h>

struct HashNode{
    int value;
    std::string key;
    HashNode* next;

    HashNode(std::string k, int v){
        key = k;
        value = v;
        next = nullptr;
    }
};

class HashTable {
    private:
        static const int TABLE_SIZE = 7;
        HashNode* table[TABLE_SIZE];

        int hashFunction(const std::string& key){
            int hash = 0;
            for(char c : key)
                hash += c;
            return hash % TABLE_SIZE;
        }

        void copy(const HashTable &other){
            for(int i = 0; i < TABLE_SIZE; i++){
                if(other.table[i] == nullptr){
                    table[i] = nullptr;
                    continue;
                }

                table[i] = new HashNode(other.table[i]->key, other.table[i]->value);
                HashNode* currentNew = table[i];
                HashNode* currentOther = other.table[i]->next;

                while(currentOther != nullptr){
                    currentNew->next = new HashNode(currentOther->key, currentOther->value);
                    currentNew = currentNew->next;
                    currentOther = currentOther->next;
                }
            }
        }

        void freeMemory(){
            for(int i = 0; i < TABLE_SIZE; i++){
                HashNode* curr = table[i];
                while(curr != nullptr){
                    HashNode* nextNode = curr->next;
                    delete curr;
                    curr = nextNode;
                }
            }
        }

    public:
        HashTable(){
            for(int i = 0; i < TABLE_SIZE; i++)
                table[i] = nullptr;
        }

        HashTable(const HashTable &other){
            copy(other);
        }

        void insert(std::string key, int value){
            int index = hashFunction(key);
            HashNode* curr = table[index];
            while(curr != nullptr){
                if (curr->key == key){
                    curr->value = value;
                    return;
                }
                curr = curr->next;
            }

            HashNode* newNode = new HashNode(key, value);
            newNode->next = table[index];
            table[index] = newNode;
        }

        int search(std::string key){
            int index = hashFunction(key);
            HashNode* curr = table[index];

            while(curr != nullptr){
                if(curr->key == key)
                    return curr->value;
                curr = curr->next;
            }
            return -1;
        }

        void remove(std::string key){
            int index = hashFunction(key);
            HashNode* curr = table[index];
            HashNode* prev = nullptr;

            while(curr != nullptr && curr->key != key){
                prev = curr;
                curr = curr->next;
            }

            if(curr == nullptr)
                return;

            if(prev == nullptr)
                table[index] = curr->next;
            else
                prev->next = curr->next;

            delete curr;
        }

        void printTable(){
            for(int i = 0; i < TABLE_SIZE; i++){
                std::cout << "Bucket " << i << ": ";
                HashNode* curr = table[i];
                while(curr != nullptr){
                    std::cout << "[" << curr->key << ":" << curr->value << "] -> ";
                    curr = curr->next;
                }
                std::cout << "nullptr" << std::endl;
            }
        }

        HashTable& operator=(const HashTable &other){
            if(this != &other){
                freeMemory();
                copy(other);
            }
            return *this;
        }

        ~HashTable(){
            freeMemory();
        }
        
};

int main(){
    HashTable ht;

    // Fun fact: In this specific setup (Size 7), both "Alice" and "Bob" 
    // mathematically evaluate to bucket index 2. This proves our collision logic works!
    ht.insert("Alice", 25);
    ht.insert("Bob", 30);
    ht.insert("Charlie", 35);
    ht.insert("Diana", 40);

    ht.printTable();

    std::cout << "\nSearching for Bob: " << ht.search("Bob") << "\n";
    
    ht.remove("Bob");
    std::cout << "\nAfter removing Bob:\n";
    ht.printTable();

    return 0;
}