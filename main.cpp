#include <bits/stdc++.h>
using namespace std;

string convert(string binary_num){  // to convert to hex string 
                                    // I use bitset<32> 3 times and a bitset<4> -> sum of 100
    int cnt = 0;
    string hex_num, s;
    for (int i = 0; i < 4; i++){
        hex_num.clear();
        if (i == 3){
            bitset<4> bits(binary_num.substr(96, 4));
            stringstream hex_stream;
            hex_stream << hex << bits.to_ullong(); 
            hex_num += hex_stream.str();
            if (hex_num.length() == 7) hex_num.insert(0, "0");
            s += hex_num;
            break;
        }
        bitset<32> bits(binary_num.substr(cnt, 32));
        stringstream hex_stream;
        hex_stream << hex << bits.to_ullong(); 
        hex_num += hex_stream.str();
        cnt += 32;
        if (hex_num.length() == 7) hex_num.insert(0, "0");
        s += hex_num;    
    }
    return s;
}

string count(string hex){ //this to crunch hex string to string contains 0-9 numbers with lenth within 9-11
    int cnt = 1;
    string s;
    char c;    
    c = hex[0];
    if (!isdigit(c)){
        int d = char(toascii(c) - 97 + 10);
        s += to_string(d);
    }
    else s += c;
    for (int i = 0; i < 3; i++){
        int sum = 0;
        string cr = hex.substr(cnt, 8);
        for (char &c : cr) sum += toascii(c);
        cnt += 8;
        s.append(to_string(sum % 311));
    }
    return s;
}

// Checking function to count the collision case
int countRepeated(string arr[], int n) {
    int cnt = 0;
    sort(arr, arr + n);
    for(int i = 1; i < n; i++) {
        if(arr[i] == arr[i-1]) {
            cnt++;
            //cout << arr[i] << endl;
        }
    }
    return cnt;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int M; cin >> M;    //input M which is the amount of table length()
    string arr[M];
    srand(time(NULL));
    for (int t = 0; t < M; t++){
        string binary_num;
        // random binary string with length of 100
        for (int i = 0; i < 100; i++) {
            int rnd = ((int)rand() % 2);
            binary_num += to_string(rnd); 
        }
        string hx = convert(binary_num); // convert to hex string
        string dc = count(hx);   //convert to a hash number
        arr[t] = dc;
        //cout << arr[t] << endl;
    }
    cout << "Numbers of collision case: " << countRepeated(arr, M);
   
}