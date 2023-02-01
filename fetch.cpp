#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

int main(int argc,char** argv) {
    int total = atoi(argv[1]);
    ifstream inputF;
    inputF.open("transactions.csv");

    string line = "";
    getline(inputF, line); //romove title line
    line = "";
    map<string, vector<pair<string, int>>>mp;
    map<string, int>pay;
    while (getline(inputF, line)) {
        if (line == "")break;
        string Payer;
        int num;
        string timeStamp;
        string temp;

        stringstream inputString(line);
        getline(inputString, Payer, ',');
        getline(inputString, temp, ',');
        num = stoi(temp);
        getline(inputString, timeStamp);


        pay[Payer] += num;

        if (mp.count(timeStamp) > 0)mp[timeStamp].push_back({ Payer,num });
        else mp[timeStamp] = { { Payer,num } };
        line = "";
    }

    for (auto it : mp) {
        if (total == 0)break;
        int n = it.second.size();
        for (int i = 0; i < n; i++) {
            string payer = it.second[i].first;
            int num= it.second[i].second;
            if (num < 0) {
                pay[payer] += abs(num);
                total -= num;
            }
            else {
                if (num < total) {
                    if (pay[payer] < num) {
                        total -= pay[payer];
                        pay[payer] = 0;
                    }
                    else {
                        pay[payer] -= num;
                        total -= num;
                    }
                }
                else {
                    if (pay[payer] < total) {
                        total -= pay[payer];
                        pay[payer] = 0;
                    }
                    else {
                        pay[payer] -= total;
                        total=0;
                    }
                }
            }
        }

    }

    string delim = "";
    for (auto it : pay) {
        cout << delim << it.first << ": " << it.second;
        delim = ",\n";
    }
    return 0;
}