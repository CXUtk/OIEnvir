//
// Created by DELL on 2018/12/24.
//

#ifndef OJONLY_INTHASHTABLE_H
#define OJONLY_INTHASHTABLE_H

#include <cstring>
#include <cstdlib>

struct Node{
	int k;
	int v;
	Node * next;
};
constexpr int MAX_ELEMENT = 200005;
class IntHashTable {
public:
	IntHashTable(){
		memset(data, 0, sizeof(data));
	}
	void Insert(int k, int v){
		int i = getHash(k);
		if(!data[i]){
			Node * n = (Node *)malloc(sizeof(Node));
			n->k = k;
			n->v = v;
			n->next = nullptr;
			data[i] = n;
		}
		else{
			Node * p = data[i];
			while(p->k != k && p->next){
				p = p->next;
			}
			if(p->k != k){
				Node * n = (Node *)malloc(sizeof(Node));
				n->k = k;
				n->v = v;
				n->next = nullptr;
				p->next = n;
			}
			else{
				p->v = v;
			}
		}
	}

	bool Contains(int k, int * v){
		int i = getHash(k);
		if(!data[i]) return false;
		Node * p = data[i];
		while(p->k != k && p->next){
			p = p->next;
		}
		if(p->k == k){
			*v = p->v;
			return true;
		}
		return false;
	}

	void Clear(){
		memset(data, 0, sizeof(data));
	}
private:
	Node * data[10000];
	int getHash(int n) const {
		return n % 10000;
	}
};


#endif //OJONLY_INTHASHTABLE_H
