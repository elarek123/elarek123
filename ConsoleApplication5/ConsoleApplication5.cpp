#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <deque>
#include <set>
#include <string>
#include <bitset>
#include <iomanip>
#include <map>
#include <stack> 
#include <typeinfo>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <optional>
#define all(x) sort(x.begin(), x.end())
#define rall(x) sort(x.rbegin(), x.rend())
#define rev(x) reverse(x.begin(), x.end())
#define ll long long
#define ull unsigned long long
#define uint unsigned int
#define x first
#define y second
#define check(x,y) (x<y&x>=0) ? true : false
#define show(x) for(auto i:x) cout<<i<<"";
#define getm(x) for(auto&i :x) cin>>i;

using namespace std;

struct Person {
protected:
    string name, surname;
    optional<string> secondname;
public:
    Person(string surname, string name, optional<string> secondname = nullopt) : name(name), surname(surname), secondname(secondname) {}
    string GetSecName() const;

    bool operator<(const Person& person) {
        return tie(surname, name, *secondname) < tie(surname, name, *secondname);
    }
    bool operator==(const Person& person) {
        return tie(surname, name, *secondname) == tie(surname, name, *secondname);
    }
};

struct PhoneNumber {
protected:
    int c_c, t_c;
    string n;
    optional<int>ex_n;
public:
    PhoneNumber(int countrycode, int towncode, string number, optional<int> exnumber = nullopt) : c_c(countrycode), t_c(towncode), n(number), ex_n(exnumber) {}
    bool operator<(const PhoneNumber& number) {
        return tie(c_c, t_c, n, *ex_n) < tie(c_c, t_c, n, *ex_n);
    }
    bool operator==(const PhoneNumber& number) {
        return tie(c_c, t_c, n, *ex_n) == tie(c_c, t_c, n, *ex_n);
    }
    friend  ostream& operator <<(ostream& out, const PhoneNumber& number);
};
ostream& operator <<(ostream& out, const PhoneNumber& number) {
    out << '+' << number.c_c << '(' << number.t_c << ')' << number.n << (number.ex_n == nullopt) ? "" : to_string(*number.ex_n);
    return out;
}

class PhoneBook {
protected:
    vector<pair<Person, PhoneNumber>>Q;
public:
    PhoneBook(ifstream& in) {
        string s;
        while (getline(in, s)) {
            stringstream s1;
            s1 << s.substr(0, s.find('+'));
            vector<string>Q1(3);
            string s2;
            int k = 0;
            while (s1 >> s2) {
                Q1[k++] = s2;
            }
            s = s.substr(s.find('+') + 1, s.size() - s.find("+"));
            s.replace(s.find(")"), 1, " ");
            s.replace(s.find("("), 1, " ");
            int countrycode, towncode, exnumber;
            string number;
            s1 << s;
            s1 >> countrycode >> towncode >> number;
            if (s1.gcount() != 0)
                s1 >> exnumber;
            Q.emplace_back(Person(Q1[0], Q1[1], Q1[2]), PhoneNumber(countrycode, towncode, number, exnumber));
        }

    }
    void SortByName() {
        sort(Q.begin(), Q.end(), [](pair<Person, PhoneNumber> pr1,
            pair<Person, PhoneNumber> pr2) {
                return pr1.first < pr2.first; });
    }

    void SortByPhone() {
        sort(Q.begin(), Q.end(), [](pair<Person, PhoneNumber> pr1,
            pair<Person, PhoneNumber> pr2) {
                return pr1.second < pr2.second; });
    }
    tuple<string, PhoneNumber> GetPhoneNumber(string sec_name) const {
        string str;
        PhoneNumber pn(0, 0, "");
        int cnt = 0;
        for_each(Q.begin(), Q.end(), [&pn, &cnt, &sec_name](pair<Person, PhoneNumber> pr) {
            cnt += ((pr.first.GetSecName() == sec_name) ? 1 : 0);
            if (cnt == 1) {
                pn = pr.second;
            }
            });
        switch (cnt) {
        case 0:
            str = "not found";
            break;
        case 1:
            str = "";
            break;
        default:
            str = "found more than 1";
            break;
        }
        return tie(str, pn);
    }
    void ChangePhoneNumber(Person pers, PhoneNumber pn) {
        auto found = find_if(Q.begin(), Q.end(), [&pers](pair<Person, PhoneNumber> pr)
            { return pr.first == pers; });
        if (found != Q.end()) {
            (*found).second = pn;
        }
    }
};

int main()
{

}

