# In-Memory File System
A trie-based commaned-line file system, implemented in C++

## Some Key Features
* Allows users to make a directory
* Allows users to add contents to a file
* Allows users to list directory names and files contained within a particular parent directory

### Trie 
A trie node containes a map of the directory's name to the directory's children. Additionally, an isFile variable indicates whether or not the Node belongs to a file. The content variable stores the content of the file. 

```C++
class TrieNode {
        public:
        map<string, TrieNode*> names;
        bool isFile = false;
        string content = "";
    };  
```


## Creating a Node
The following algorithm elegantly handles the functionality for both adding a directory and adding a file. 

```C++  
void createNode(string path, bool isFile, string content) {
    //First, we split the given path on a '/'
        TrieNode* temp = root;
        vector<string> paths;
        string curr;
        stringstream ss(path);
        
        while(getline(ss, curr, '/')) paths.push_back(curr);
    //We use the parsed path name to navigate down the trie, until we reach the desired directory or file
        for(auto p : paths) {
            if (temp->names[p]) {
                temp = temp->names[p];
            } else {
                temp->names[p] = new TrieNode;
                temp = temp->names[p];
            }
        }
    //if the destinaton is a file, add the provided content to the file
        if (isFile) {
            temp->isFile = 1;
            temp->content += content;
        }
    }
```
