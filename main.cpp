#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#define MAX_RAND 1e5
#define N 5
using namespace std;

void bubble_sort(vector<double> &vec){
    int swap_count;
    for(int i = 0; i < vec.size() - 1; i++){
        swap_count = 0;
        for(int j = 0; j < vec.size() - i - 1; j++){
            if(vec[j] > vec[j+1]) swap(vec[j], vec[j+1]);
            swap_count++;
        }
        if(swap_count == 0) break;
    }
}

void merge(vector<double> &vec, int start, int mid, int end){
    vector<double> left, right;
    for(int i=0;i<=end;i++){
        if(i <= mid) left.push_back(vec[i]);
        else right.push_back(vec[i]);
    }
    int l = 0, r = 0, j = start;
    while(l < left.size() && r < right.size()){
        if(left[l] < right[r]){
            vec[j] = left[l];
            l++;
        }
        else{
            vec[j] = right[r];
            r++;
        }
        j++;
    }
    while(l < left.size()){
        vec[j] = left[l];
        j++;
        l++;
    }
    while(r < right.size()){
        vec[j] = right[r];
        j++;
        r++;
    }
}

void merge_sort(vector<double> &vec, int start, int end){
    if(start < end){
        int mid = start + (end - start)/2;
        merge_sort(vec, start, mid);
        merge_sort(vec, mid + 1, end);
        merge(vec, start, mid, end);
    }
}

int main(){
    vector<double> vec(N);
    random_device rd;
    mt19937 rng(rd());
    uniform_real_distribution<double> dist(-MAX_RAND, MAX_RAND);
    auto gen_rand = [&dist, &rng](){return dist(rng);};
    generate(vec.begin(), vec.end(), gen_rand);
    //sort(vec.rbegin(), vec.rend());
    vector<double> bubble_vec(vec), merge_vec(vec);;

    bubble_sort(bubble_vec);
    for(double val : bubble_vec) cout << val << " ";
    cout << "\n";

    merge_sort(merge_vec, 0, merge_vec.size()-1);
    for(double val : merge_vec) cout << val << " ";
    cout << "\n";
}