#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
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

void merge_sort(vector<double> &vec, int start, int end){
    if(start < end){
        int mid = start + (end - start)/2;
        merge_sort(vec, start, mid);
        merge_sort(vec, mid + 1, end);
        merge(vec, start, mid, end);
    }
}

int partition (vector<double> &vec, int start, int end){
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

void quick_sort(vector<double> &vec, int start, int end){
    if(start < end){
        int p = partition(vec, start, end);
        quick_sort(vec, start, p - 1);
        quick_sort(vec, p + 1, end);
    }
}

const int n = 1e1;
const int max_rand = 1e5;

int main(){
    vector<double> vec(n);
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<long> dist(-max_rand, max_rand);
    auto gen_rand = [&dist, &rng](){return (double)dist(rng)/dist(rng);};
    generate(vec.begin(), vec.end(), gen_rand);

    vector<double> bubble_vec(vec), merge_vec(vec), quick_vec(vec);
    quick_sort(quick_vec, 0, quick_vec.size() - 1);
    for(double val :quick_vec) cout << val << " ";
    cout << "\n";

    bubble_sort(bubble_vec);
    for(double val : bubble_vec) cout << val << " ";
    cout << "\n";

    merge_sort(merge_vec, 0, merge_vec.size()-1);
    for(double val : merge_vec) cout << val << " ";
    cout << "\n";
}