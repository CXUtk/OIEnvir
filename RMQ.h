//
// Created by DELL on 2018/11/22.
//

#ifndef OJONLY_RMQ_H
#define OJONLY_RMQ_H

#include <algorithm>

constexpr int lgN = 17;
constexpr int N = 100005;

int arr[N];
int minn[N][lgN];
int maxx[N][lgN];

void init(){
	for(int i = 0; i < N; i++){
		minn[i][0] = maxx[i][0] = arr[i];
	}
	for (int j = 1; (1 << j) <= N; j++) {
		for (int i = 0; i + (1 << j) - 1 < N; i++) {
			minn[i][j] = std::min(minn[i][j - 1], minn[i + (1 << (j - 1))][j - 1]);
			maxx[i][j] = std::max(maxx[i][j - 1], maxx[i + (1 << (j - 1))][j - 1]);
		}
	}
}

int getMin(int l, int r){
	int c = 2;
	int z = 0;
	while(c <= r - l + 1) { c <<= 1; z++; }
	return std::min(minn[l][z], minn[r - (1 << z) + 1][z]);
}

int getMax(int l, int r){
	int c = 2;
	int z = 0;
	while(c <= r - l + 1) { c <<= 1; z++; }
	return std::max(maxx[l][z], maxx[r - (1 << z) + 1][z]);
}

#endif //OJONLY_RMQ_H
