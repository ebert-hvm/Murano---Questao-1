#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
using namespace std;

void bubble_sort(vector<float> &vec){
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

void merge(vector<float> &vec, int start, int mid, int end){
    vector<float> left, right;
    for(int i=start;i<=end;i++){
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

void merge_sort(vector<float> &vec, int start, int end){
    if(start < end){
        int mid = start + (end - start)/2;
        merge_sort(vec, start, mid);
        merge_sort(vec, mid + 1, end);
        merge(vec, start, mid, end);
    }
}

int partition (vector<float> &vec, int start, int end){
    // last element pivoting
    int i = start-1;
    for (int j = start; j < end; j++){
        if (vec[j] < vec[end]){
            i++;
            swap(vec[i], vec[j]);
        }
    }
    swap(vec[i + 1], vec[end]);
    return i+1;
}

void quick_sort(vector<float> &vec, int start, int end){
    if(start < end){
        int p = partition(vec, start, end);
        quick_sort(vec, start, p - 1);
        quick_sort(vec, p + 1, end);
    }
}

const long max_rand = 100000;

int main(){
    chrono::steady_clock sc;
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<long> dist(-max_rand, max_rand);
    auto gen_rand = [&dist, &rng](){return (float)dist(rng)/dist(rng);};
    vector<long> size_array = {(long)1e7};
    for(const long& n : size_array){
        vector<float> vec(n);
        generate(vec.begin(), vec.end(), gen_rand);
        // for(const auto& el : vec) cout << el << " ";
        vector<float> bubble_vec(vec), merge_vec(vec), quick_vec(vec);        

        auto start = sc.now();
        merge_sort(merge_vec, 0, merge_vec.size()-1);
        auto end = sc.now();
        auto time_span = static_cast<chrono::duration<float>>(end - start);
        cout<<"merge sort: "<<time_span.count()<<"\n";

        start = sc.now();
        quick_sort(quick_vec, 0, quick_vec.size() - 1);
        end = sc.now();
        time_span = static_cast<chrono::duration<float>>(end - start);
        cout<<"quick sort: "<<time_span.count()<<"\n";

        start = sc.now();
        //bubble_sort(bubble_vec);
        end = sc.now();
        time_span = static_cast<chrono::duration<float>>(end - start);
        cout<<"bubble sort: "<<time_span.count()<<"\n";
    }
}