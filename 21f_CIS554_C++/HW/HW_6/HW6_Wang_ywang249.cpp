// CIS554 HW6. Due: 11:59pm, Saturday, Dec. 11.
//hw6 by yuchen wang
//su net id: ywang249  suid: 905508464

//hw6 due: 11:59pm, friday october 29

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>
#include <string>

using namespace std;

class Circuit
{ // Truth Table
public:
    int input_length;
    int output_length;
    // vector<pair<vector<int>, vector<int>> *> data;
    vector<shared_ptr<pair<vector<int>, vector<int>>>> data;

    Circuit()
    {
        input_length = 0;
        output_length = 0;
        // data = vector<pair<vector<int>, vector<int>> *>();
        data = vector<shared_ptr<pair<vector<int>, vector<int>>>>();
    }

    Circuit(vector<string> &L, int input_l, int output_l) : Circuit()
    {
        input_length = input_l;
        output_length = output_l;

        for (string &i : L)
        {
            vector<int> input_digit;
            vector<int> output_digit;

            int index = 0;
            while (i[index] != ' ')
                input_digit.push_back(i[index++] - '0');

            index++;

            while (index < i.size() && i[index] != ' ')
                output_digit.push_back(i[index++] - '0');
            shared_ptr<pair<vector<int>, vector<int>>> p = make_shared<pair<vector<int>, vector<int>>>(input_digit, output_digit);
            // data.push_back(new pair<vector<int>, vector<int>>{input_digit, output_digit});
            data.push_back(p);
        }

        return;
    }

    bool operator==(const Circuit &M2) const;
};

bool Circuit::operator==(const Circuit &M2) const
{
    if ((input_length != M2.input_length) || (output_length != M2.output_length))
        return false;

    unordered_map<int, int> output_row_check;
    // check output rows
    for (shared_ptr<pair<vector<int>, vector<int>>> i : data)
    {
        int row_sum = 0;

        for (int j : i->second)
            row_sum += j;

        output_row_check[row_sum]++;
    }

    for (shared_ptr<pair<vector<int>, vector<int>>> i : (M2.data))
    {
        int row_sum = 0;

        for (int j : i->second)
            row_sum += j;

        output_row_check[row_sum]--;
    }

    for (auto i = output_row_check.begin(); i != output_row_check.end(); i++)
    {
        if (i->second != 0)
            return false;
    }

    // check output columns
    unordered_map<int, int> output_col_check;
    vector<int> output_columns_M1(output_length, 0);
    vector<int> output_columns_M2(output_length, 0);

    for (shared_ptr<pair<vector<int>, vector<int>>> i : data)
    {
        vector<int> &output_column = i->second;

        for (int j = 0; j < i->second.size(); j++)
        {
            output_columns_M1[j] += output_column[j];
        }
    }

    for (shared_ptr<pair<vector<int>, vector<int>>> i : (M2.data))
    {
        vector<int> &output_column = i->second;

        for (int j = 0; j < i->second.size(); j++)
        {
            output_columns_M2[j] += output_column[j];
        }
    }

    for (int i : output_columns_M1)
        output_col_check[i]++;
    for (int i : output_columns_M2)
        output_col_check[i]--;

    for (auto i = output_col_check.begin(); i != output_col_check.end(); i++)
    {
        if (i->second != 0)
            return false;
    }

    // check rows of input combining output
    unordered_map<int, int> overall_row_check;
    for (shared_ptr<pair<vector<int>, vector<int>>> i : (data))
    {
        int row_sum = 0;

        for (int j : i->first)
            row_sum += j;

        for (int j : i->second)
            row_sum += j;

        overall_row_check[row_sum]++;
    }

    for (shared_ptr<pair<vector<int>, vector<int>>> i : (M2.data))
    {
        int row_sum = 0;

        for (int j : i->first)
            row_sum += j;

        for (int j : i->second)
            row_sum += j;

        overall_row_check[row_sum]--;
    }

    for (auto i = overall_row_check.begin(); i != overall_row_check.end(); i++)
    {
        if (i->second != 0)
            return false;
    }

    return true;
}

class myHashEqualClass
{
public:
    size_t operator()(const Circuit &M1) const;
    bool operator()(const Circuit &M1, const Circuit &M2) const;
};

size_t myHashEqualClass::operator()(const Circuit &M1) const
{
    int sum_one = 0;
    hash<int> h;

    for (shared_ptr<pair<vector<int>, vector<int>>> i : (M1.data))
    {
        for (int j : i->second)
            sum_one += j;
    }

    return h(sum_one);
}

bool myHashEqualClass::operator()(const Circuit &M1, const Circuit &M2) const
{
    if ((M1.input_length != M2.input_length) || (M1.output_length != M2.output_length))
        return false;

    unordered_map<int, int> output_row_check;
    // check output rows
    for (shared_ptr<pair<vector<int>, vector<int>>> i : M1.data)
    {
        int row_sum = 0;
        for (int j : i->second)
            row_sum += j;

        output_row_check[row_sum]++;
    }

    for (shared_ptr<pair<vector<int>, vector<int>>> i : (M2.data))
    {
        int row_sum = 0;

        for (int j : i->second)
            row_sum += j;

        output_row_check[row_sum]--;
    }

    for (auto i = output_row_check.begin(); i != output_row_check.end(); i++)
    {
        if (i->second != 0)
            return false;
    }

    // check output columns
    unordered_map<int, int> output_col_check;
    vector<int> output_columns_M1(M1.output_length, 0);
    vector<int> output_columns_M2(M1.output_length, 0);

    for (shared_ptr<pair<vector<int>, vector<int>>> i : M1.data)
    {
        vector<int> &output_column = i->second;

        for (int j = 0; j < i->second.size(); j++)
        {
            output_columns_M1[j] += output_column[j];
        }
    }

    for (shared_ptr<pair<vector<int>, vector<int>>> i : (M2.data))
    {
        vector<int> &output_column = i->second;

        for (int j = 0; j < i->second.size(); j++)
        {
            output_columns_M2[j] += output_column[j];
        }
    }

    for (int i : output_columns_M1)
        output_col_check[i]++;
    for (int i : output_columns_M2)
        output_col_check[i]--;

    for (auto i = output_col_check.begin(); i != output_col_check.end(); i++)
    {
        if (i->second != 0)
            return false;
    }

    // check rows of input combining output
    unordered_map<int, int> overall_row_check;
    for (shared_ptr<pair<vector<int>, vector<int>>> i : (M1.data))
    {
        int row_sum = 0;

        for (int j : i->first)
            row_sum += j;

        for (int j : i->second)
            row_sum += j;

        overall_row_check[row_sum]++;
    }

    for (shared_ptr<pair<vector<int>, vector<int>>> i : (M2.data))
    {
        int row_sum = 0;

        for (int j : i->first)
            row_sum += j;

        for (int j : i->second)
            row_sum += j;

        overall_row_check[row_sum]--;
    }

    for (auto i = overall_row_check.begin(); i != overall_row_check.end(); i++)
    {
        if (i->second != 0)
            return false;
    }

    return true;
}

ostream &operator<<(ostream &str, const Circuit &c)
{
    str << c.input_length << "\n";
    str << c.output_length << "\n";

    for (shared_ptr<pair<vector<int>, vector<int>>> i : c.data)
    {
        for (int j : i->first)
            str << j;

        str << " ";

        for (int j : i->second)
            str << j;

        str << "\n";
    }

    return str;
}

ostream &operator<<(ostream &str, const unordered_map<Circuit, vector<string>, myHashEqualClass, myHashEqualClass> &DB)
{
    for (auto i = DB.begin(); i != DB.end(); i++)
    {
        str << (i->first) << "\n";
    }

    str << endl;

    return str;
}

bool myFind(const Circuit &c, unordered_map<Circuit, vector<string>, myHashEqualClass, myHashEqualClass> &DB)
{
    for (auto &i : DB)
    {
        if (i.first == c)
            return true;
    }

    return false;
}

int main()
{
    // Declare you DB of type unordered_map< â€¦,â€¦> DB;
    unordered_map<Circuit, vector<string>, myHashEqualClass, myHashEqualClass> DB;

    string line;
    ifstream myfile("circuits.txt");
    if (!myfile.is_open())
    {
        cout << "Input File ERROR!!!" << endl;
    }

    getline(myfile, line);
    int num_of_circuit = stoi(line);

    while (num_of_circuit-- > 0 && getline(myfile, line))
    {
        int input_length = stoi(line), num_of_row = pow(2, input_length);

        getline(myfile, line);
        int output_length = stoi(line);

        // circuit data
        vector<string> curr_circuit;

        while (num_of_row-- > 0 && getline(myfile, line))
        {
            curr_circuit.push_back(line);
        }

        Circuit curr(curr_circuit, input_length, output_length);

        // if (!myFind(curr, DB))
        if (DB.find(curr) == DB.end())
        {
            DB[curr] = curr_circuit;
        }
        else
        {
            cout << "The circuit is already in DB." << endl;
        }
    }

    cout << DB << endl;

    // cout << "DB size is : " << DB.size() << endl;

    myfile.close();

    return 0;
}
