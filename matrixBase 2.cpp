#include<iostream>
#include<vector>
#include<string>

using namespace std;

struct data{
    int x, y;
    int value;
};

struct link{
    int x, y;
    int r;
};

using matrix = vector<data>;
using vect0 = vector<double>;
using graph = vector<link>;
using list = vector<vector<int>>;

vector<int> zero;

vect0 operator * (matrix a, vect0 b) {
    vect0 ans;
    for(auto it: a) {
        while(ans.size() < it.y + 1) ans.push_back(0);
        while(b.size() < it.x + 1) b.push_back(0);
        ans[it.y] += it.value*b[it.x];
    }
    return ans;
}

vect0 operator / (matrix a, vect0 b) {
    vect0 ans;
    for(auto it: a) {
        while(ans.size() < it.x + 1) ans.push_back(0);
        while(b.size() < it.y + 1) b.push_back(0);
        ans[it.x] += it.value*b[it.y];
    }
    return ans;
}

vect0 operator * (double x, vect0 a) {
    for(int i = 0; i < a.size(); i++) {
        a[i] *= x;
    }
    return a;
}

double operator * (vect0 a, vect0 b) {
    double ans = 0;
    for(int i = 0; i < a.size() && i < b.size(); i++) {
        ans += a[i]*b[i];
    }
    return ans;
}
/*
matrix invert(matrix a) {
    matrix ans;
    for(auto it:a) {
        coords c;
        c.x = it.first.y;
        c.y = it.first.x;
        ans.find(c)->second = a.find(it.first)->second;
    }
    return ans;
}
*/
vect0 operator - (vect0 a, vect0 b) {
    vect0 ans = a;
    for(int i = 0; i < b.size(); i++) {
        if(ans.size() < i) ans.push_back(0);
        ans[i] -= b[i];
    }
    return ans;
}

vect0 operator + (vect0 a, vect0 b) {
    vect0 ans = b;
    for(int i = 0; i < a.size(); i++) {
        if(ans.size() < i) ans.push_back(0);
        ans[i] += a[i];
    }
    return ans;
}

matrix doA() {
    matrix ans;
    data xar;
    xar.x = 0;
    xar.y = 0;
    xar.value = 1;
    ans.push_back(xar);
    xar.x = 0;
    xar.y = 1;
    xar.value = 3;
    ans.push_back(xar);
    xar.x = 1;
    xar.y = 0;
    xar.value = 2;
    ans.push_back(xar);
    xar.x = 1;
    xar.y = 1;
    xar.value = 4;
    ans.push_back(xar);
    return ans;
}

vect0 doa() {
    vect0 ans;
    ans.push_back(5);
    ans.push_back(11);
    return ans;
}

vect0 dox(int a) {
    vect0 ans;
    for(int i = 0; i < a; i++) {
        ans.push_back(0.001);
    }
    return ans;
}

void print(vect0 x) {
    cout << "---------------" << endl;
    for(int i = 0; i < x.size(); i++) {
        cout << x[i] << " " << endl;
    }
    cout << "---------------" << endl;
}

void print(list x) {
    for(int i = 0; i < x.size(); i++) {
        cout << i << endl;
        for(int j = 0; j < x[i].size(); j++) {
            cout << x[i][j] << " ";
        }
        cout << endl;
    }
}

vect0 solve(matrix A1, vect0 a1, int size) {
    matrix A = A1;
    vect0 b = a1;
    vect0 x = dox(size);
    double k = 30; // kol-vo iteratsii
    for(int i = 0; i < k; i++) {
        vect0 r = A*x - b;
        vect0 Ar = A/r;
        vect0 AAr = A*Ar;
        double m = (r*AAr)/(AAr*AAr);
        x = x - m*(Ar);
    }
    return x;
}

double solveGraph(graph x) {
    list l;
    for(int i = 0; i < x.size(); i++) {
        while(x[i].x + 1 > l.size() || x[i].y + 1 > l.size()) l.push_back(zero);
        l[x[i].x].push_back(i);
        l[x[i].y].push_back((-1)-i);
    }
    print(l);
    cout << endl;
    matrix A;
    vect0 b;
    
    for(int i = 0; i < x.size() + l.size() - 2; i++) {
        b.push_back(0);
    }
    for(int i = 0; i < l[l.size()-1].size(); i++) {
        if(l[l.size()-1][i] < 0) b[(-1) - l[l.size()-1][i] ] = -1; else b[l[l.size()-1][i]] = 1;
    }
//    cout << x.size() << " xsize" << endl;
    for(int i = 0; i < x.size(); i++) {
        data xar;
        xar.y = i;
        xar.x = x.size() - 1 + x[i].x;
        xar.value = -1;
        if(xar.x != x.size() - 1 && xar.x != x.size() - 1 + x.size()) A.push_back(xar);
        xar.x = x.size() - 1 + x[i].y;
        xar.value = 1;
        if(xar.x != x.size() - 1 && xar.x != x.size() - 1 + x.size()) A.push_back(xar);
        xar.x = i;
        xar.value = -1/x[i].r;
        A.push_back(xar);
    }
    for(int i = 1; i < l.size() - 1; i++) {
        data xar;
        xar.y = i + x.size() - 1;
        for(int j = 0; j < l[i].size(); j++) {
            int a;
            int plus;
            if(l[i][j] < 0) {a = -1 - l[i][j]; plus = -1;}
            else {a = l[i][j]; plus = 1;}
            xar.x = a;
            xar.value = plus;
            A.push_back(xar);
        }
    }
    for(int i = 0; i < A.size(); i++) {
        cout << A[i].x << " " << A[i].y << " " << A[i].value << " " << endl;
    }
    print(b);
    vect0 preAns = solve(A,b, x.size() + l.size() - 2);
    double summ = 0;
    print(preAns);
    for(int j = 0; j < l[0].size(); j++) {
        int a;
        int plus;
        if(l[0][j] < 0) {a = -1 - l[0][j]; plus = -1;}
        else {a = l[0][j]; plus = 1;}
        summ += preAns[a]*plus;
    }
    return 1./summ;
}




int main() { 
    graph G;
    link l;
    l.x = 0;
    l.y = 1;
    l.r = 1;
    G.push_back(l);
    l.x = 0;
    l.y = 1;
    l.r = 1;
    G.push_back(l);
    cout << solveGraph(G) << endl;
}
