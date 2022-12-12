#include <iostream>
#include <fstream>
#include <vector> 
#include <string>

using namespace std;


int n, m;

int getN(){
    int n;
    cin >> n;
    return n;
}

int getM(){
    int m;
    cin >> m;
    return m;
}

vector<int> getGrid(int n){
    int a, i;
    vector<int> c(0);
    //cin >> n >> m;
    for (i = 0; i < n; i++){
        cin >> a;
        c.push_back(a);
    }
    return c;
}

void print(vector<int> v){
    for (int i = 0; i < v.size(); i++) {
            cout << v.at(i) << " ";
        }
        cout << endl;
}

int get_upper_right_square(vector<int> v){
    int max_value = v[0];
    int max_index = 0;

    for(int i = 0; i < v.size(); i++) {
        if (v[i] > max_value) {
            max_value = v[i];
            max_index = i;
        }
    }
    return max_index;
}

int find_max_square(vector<int> &v){
    int max_size = 0;
    int index = get_upper_right_square(v);

    if (v[index] > v[index + 1]){
        max_size++;
        return max_size;
    }

    else{
        int count = 0;
        int i = 0;
        while (v[index] == v[index + i]){
            count++;
            i++;
        }
        max_size = count;
        return max_size;
    }

}

/*
int find_max_square(vector<int> &v){
    int max_size = 0;
    int index = 
    
    if (!is_sorted(v.begin(), v.end(), greater<int>())){
        if (index == v.size() - 1)
            max_size = 1;
        else {
            if (v[index] > (v.size() - index))
                max_size = v.size() - index;
            else max_size = v[index]; 
        }
    }

    else{
    }
    return max_size;
}*/

int main()
{
    int rows = getN();
    int cols = getM();
    vector<int> vec = getGrid(rows);
    print(vec);
    int max_square = find_max_square(vec);
    cout << max_square;
    cout << endl;
    return 0;
}