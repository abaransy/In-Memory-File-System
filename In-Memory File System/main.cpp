//
//  main.cpp
//  In-Memory File System
//
//  Created by Aatef Baransy on 9/18/20.
//  Copyright © 2020 Aatef Baransy. All rights reserved.
//

#include <iostream>
#include <map>
#include <vector>
#include <sstream>

using namespace std;

class FileSystem {
    class TrieNode {
        public:
        map<string, TrieNode*> names;
        bool isFile = false;
        string content = "";
    };
private:
    TrieNode* root = new TrieNode;
public:
    FileSystem() {
        
    }
    
    void createNode(string path, bool isFile, string content) {
        TrieNode* temp = root;
        vector<string> paths;
        string curr;
        stringstream ss(path);
        
        while(getline(ss, curr, '/')) paths.push_back(curr);
        
        for(auto p : paths) {
            if (temp->names[p]) {
                temp = temp->names[p];
            } else {
                temp->names[p] = new TrieNode;
                temp = temp->names[p];
            }
        }
        
        if (isFile) {
            temp->isFile = 1;
            temp->content += content;
        }
    }
    
    vector<string> ls(string path) {
        if (!root->names.size()) return {};
        TrieNode* temp = root;
        vector<string> paths;
        vector<string> answer;
        string curr;
        stringstream ss(path);
        
        while(getline(ss, curr, '/')) paths.push_back(curr);
        
        for(auto p : paths) {
            temp = temp->names[p];
        }
        
        if (temp->isFile) {
            return { paths[paths.size() - 1] };
        } else {
            for(auto entry : temp->names) answer.push_back(entry.first);
        }
        
        return answer;
    }
    
    void mkdir(string path) {
        createNode(path, false, "");
    }
    
    void addContentToFile(string filePath, string content) {
        createNode(filePath, true, content);
    }
    
    string readContentFromFile(string filePath) {
         TrieNode* temp = root;
        vector<string> paths;
        vector<string> answer;
        string curr;
        stringstream ss(filePath);
        
        while(getline(ss, curr, '/')) paths.push_back(curr);
        
        for(auto p : paths) {
            temp = temp->names[p];
        }
        
        return temp->content;
    }
};

int main(int argc, const char * argv[]) {
    return 0;
}
