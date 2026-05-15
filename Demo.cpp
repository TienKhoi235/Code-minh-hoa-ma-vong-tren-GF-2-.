#include <bits/stdc++.h>

using namespace std;

class GF2
{
public:
    static int add(int a, int b) { return a ^ b; }
    static int mul(int a, int b) { return a & b; }
};

class Polynomial
{
public:
    vector<int> coeffs;

    Polynomial(string binStr = "")
    {
        for (int i = (int)binStr.length() - 1; i >= 0; --i)
        {
            coeffs.push_back(binStr[i] - '0');
        }
        trim();
    }

    void trim()
    {
        while (!coeffs.empty() && coeffs.back() == 0)
        {
            coeffs.pop_back();
        }
    }

    string toPolynomialString() const
    {
        if (coeffs.empty())
            return "0";
        string res = "";
        bool first = true;
        for (int i = (int)coeffs.size() - 1; i >= 0; --i)
        {
            if (coeffs[i] == 1)
            {
                if (!first)
                    res += " + ";
                if (i == 0)
                    res += "1";
                else if (i == 1)
                    res += "x";
                else
                    res += "x^" + to_string(i);
                first = false;
            }
        }
        return res;
    }

    string toBinaryString(int n) const
    {
        string s = "";
        for (int i = n - 1; i >= 0; --i)
        {
            s += (i < (int)coeffs.size() ? to_string(coeffs[i]) : "0");
        }
        return s;
    }
};

class CyclicCodeEngine
{
private:
    int n, k;
    Polynomial gx;

public:
    CyclicCodeEngine(int n, int k, string gStr) : n(n), k(k), gx(gStr) {}

    Polynomial encode(const vector<int> &m)
    {
        vector<int> c(n, 0);
        for (int i = 0; i < (int)m.size(); i++)
        {
            if (!m[i])
                continue;
            for (int j = 0; j < (int)gx.coeffs.size(); j++)
            {
                if (i + j < n)
                    c[i + j] ^= gx.coeffs[j];
            }
        }
        Polynomial res;
        res.coeffs = c;
        return res;
    }

    void printTuLuan()
    {
        cout << "=== Loi giai tu luan ===\n\n";
        cout << "Thong so: n = " << n << ", k = " << k << ", r = " << n - k << "\n";
        cout << "g(x) = " << gx.toPolynomialString() << "\n\n";

        cout << left << setw(5) << "STT" << setw(12) << "m(bin)" << setw(15) << "m(x)" << "c(bin)\n";
        cout << string(60, '-') << "\n";

        int d_min = n;
        for (int i = 0; i < (1 << k); i++)
        {
            vector<int> m;
            string m_str = "";
            for (int j = 0; j < k; j++)
            {
                int bit = (i >> (k - 1 - j)) & 1;
                m.push_back(bit);
                m_str += (char)('0' + bit);
            }

            Polynomial p;
            p.coeffs = m;
            p.trim();

            string c = encode(m).toBinaryString(n);

            int w = 0;
            for (char ch : c)
                if (ch == '1')
                    w++;
            if (i > 0)
                d_min = min(d_min, w);

            if (i < 8 || i == (1 << k) - 1)
                cout << left << setw(5) << i << setw(12) << m_str << setw(15) << p.toPolynomialString() << c << "\n";
            else if (i == 8)
                cout << "...\n";
        }

        cout << "\nKet qua: d_min = " << d_min << ", phat hien " << d_min - 1 << " loi, sua " << (d_min - 1) / 2 << " loi\n";
    }

    void printTracNghiem()
    {
        cout << "=== Trac nghiem nhanh ===\n\n";
        int d_min = n;
        for (int i = 1; i < (1 << k); i++)
        {
            vector<int> m;
            for (int j = 0; j < k; j++)
                m.push_back((i >> j) & 1);

            string c = encode(m).toBinaryString(n);
            int w = 0;
            for (char ch : c)
                if (ch == '1')
                    w++;
            d_min = min(d_min, w);
        }

        cout << "- Tong so tu ma: " << (1 << k) << "\n";
        cout << "- d_min: " << d_min << "\n";
        cout << "- Phat hien: " << d_min - 1 << " bit, Sua: " << (d_min - 1) / 2 << " bit\n";
        cout << "- deg(g): " << (int)gx.coeffs.size() - 1 << "\n";
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, k, opt;
    string g;
    cin >> n >> k >> g >> opt;

    CyclicCodeEngine engine(n, k, g);

    if (opt == 1)
        engine.printTuLuan();
    else
        engine.printTracNghiem();

    return 0;
}