#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
#include <limits>
using namespace std;

// BUBBLE SORT

void bubble_sort(vector<float_t> &vec){
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

// MERGE SORT FUNCTIONS

void merge_aux(vector<float_t> &vec, vector<float_t> &aux, int start, int mid, int end){
    int leftIndex = start;
    int rightIndex = mid + 1;
    int auxIndex = start;

    while(leftIndex <= mid && rightIndex <= end){
        if(vec[leftIndex] <= vec[rightIndex]){
            aux[auxIndex] = vec[leftIndex];
            leftIndex++;
        }
        else{
            aux[auxIndex] = vec[rightIndex];
            rightIndex++;
        }
        auxIndex++;
    }

    while(leftIndex <= mid){
        aux[auxIndex] = vec[leftIndex];
        leftIndex++;
        auxIndex++;
    }

    while(rightIndex <= end){
        aux[auxIndex] = vec[rightIndex];
        rightIndex++;
        auxIndex++;
    }

    copy(aux.begin() + start, aux.begin() + end + 1, vec.begin() + start);
}

void merge_sort_recursion(vector<float_t> &vec, vector<float_t> &aux, int start, int end){
    if(start < end){
        int mid = start + (end - start)/2;
        merge_sort_recursion(vec, aux, start, mid);
        merge_sort_recursion(vec, aux, mid + 1, end);
        // merge(vec, start, mid, end);
        merge_aux(vec, aux, start, mid, end);
    }
}

void merge_sort(vector<float_t> &vec){
    vector<float_t> aux(vec.size());
    merge_sort_recursion(vec, aux, 0, vec.size()-1);
}   

// QUICK SORT FUNCTIONS

int partition (vector<float_t> &vec, int start, int end, int random_pivot){
    swap(vec[random_pivot], vec[end]);
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

void quick_sort_recursion(vector<float_t> &vec, int start, int end, mt19937& rng){
    if(start < end){
        uniform_int_distribution<int> dist(start, end);
        int p = partition(vec, start, end, dist(rng));
        quick_sort_recursion(vec, start, p - 1, rng);
        quick_sort_recursion(vec, p + 1, end, rng);
    }
}

void quick_sort(vector<float_t> &vec){
    random_device rd;
    mt19937 rng(rd());
    quick_sort_recursion(vec, 0, vec.size() - 1, rng);
}

const long max_rand = 100000;

int main(){
    chrono::steady_clock sc;
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<long> dist(-max_rand, max_rand);
    auto gen_rand = [&dist, &rng](){return (float)dist(rng)/dist(rng);};
    ofstream ofs;
    ofs.open("time_algs.txt", ios::out);
    const int samples = 8;
    vector<long> size_array(samples);
    generate_n(size_array.begin(), samples, [](){static int n = 1; n *= 10; return n;});
    ofs << fixed << setprecision(9);
    for(const long& n : size_array){
        ofs << n << "\n";
        vector<float> vec(n);
        generate(vec.begin(), vec.end(), gen_rand);
//        for(const auto& el : vec) cout << el << " ";
        vector<float> bubble_vec(vec), merge_vec(vec), quick_vec(vec);        

        auto start = sc.now();
        merge_sort(merge_vec);
        auto end = sc.now();
        auto time_span = static_cast<chrono::duration<float>>(end - start);
        // for(const auto& el : merge_vec) cout << el << " ";
        ofs << time_span.count()<<"\n";

        start = sc.now();
        quick_sort(quick_vec);
        end = sc.now();
        time_span = static_cast<chrono::duration<float>>(end - start);
        // for(const auto& el : quick_vec) cout << el << " ";
        ofs << time_span.count()<<"\n";

        if(n < 1e6 - 1){
            start = sc.now();
            bubble_sort(bubble_vec);
            end = sc.now();
            time_span = static_cast<chrono::duration<float>>(end - start);
            ofs << time_span.count() <<"\n";
        }
        else ofs << numeric_limits<float>::max() << "\n";
    }
    ofs.close();
}