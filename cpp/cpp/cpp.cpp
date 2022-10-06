#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class result
{
public :
    string m_comb;
    int m_count;

    result(string comb, int count)
    {
        this->m_comb = comb;
        this->m_count = count;
    }

    ~result() {}
};

vector<result> res;

void showRes()
{
    for (result& result : res)
    {
        cout << result.m_comb << " " << result.m_count << "\n";
    }
}

void find_largest(vector<string>& answer)
{
    //��Ų �մ� ��
    int temp_count = 0;

    for (result& result : res)
    {
        if (temp_count < result.m_count)
            temp_count = result.m_count;
    }

    for (result& result : res)
    {
        //�θ� �̻� ��Ų ��쿡, �ִ��� ���� ��쵵 ����
        if (temp_count == result.m_count && temp_count > 1)
        {
            answer.push_back(result.m_comb);
            cout << "\n" << result.m_comb << "\n";
        }
    }

    cout << "\n";

    res.clear();
}

//order ������ num���� ���Ҹ� ���� ������ ���Ѵ�
void find_Combination(string order, int num)
{
    //������ ���� permutation(����) ���ǵ�, �̿� �̿� (���Ұ� 1�� �ε����� ������ �װ� �����̴�)
    vector<int> temp;
    vector<string> combs;

    sort(order.begin(), order.end());

    if (order.size() < num)
        return;

    for (int i = 0; i < order.size(); i++)
    {
        //n���� ���ҿ��� 1�� �ְ� �������� 0�� �ִ´�
        if (i < num)
            temp.push_back(1);
        else
            temp.push_back(0);
    }

    //1�� ������ ���� ����
    sort(temp.begin(), temp.end());

    do
    {
        string str;

        for (int i = 0; i < temp.size(); i++)
        {
            //1�� ģ���� �ش��ϴ� �ε����� order���� ������ ǥ���ϸ� ������ �ȴ�
            if (temp[i] == 1)
            {
                //��������� string �ױ�
                str.push_back(order[i]);
                //cout << order[i] << " ";
            }
        }

        //���� string �� ����
        combs.push_back(str);
        //cout << "\n";

    } while (next_permutation(temp.begin(), temp.end()));

    //cout << "----------------\n";

    sort(combs.begin(), combs.end());

    //for (string& str : combs)
    //    cout << str << "\n";

    //res�� ��������� �ߺ����� Ȯ��
	if (res.size() > 0)
	{
		for (string& str : combs)
		{
            bool found = false;

			for (result& result : res)
			{
                if (!str.compare(result.m_comb))
                {
                    found = true;
                    result.m_count++;
                }
			}

            if(!found)
                res.push_back(result(str, 1));
		}
	}
    //�ƹ��͵� ������(ó�� ����) �켱 �״´�
    else
    {
        for (string& str : combs)
            res.push_back(result(str, 1));
    }

    //showRes();
}

vector<string> solution(vector<string> orders, vector<int> course)
{
    // A~Z
    vector<string> answer;

    //course �� ���� order �ȿ� ����ִ� �ֹ��� ���̽��� ����� ���� ��� ã�´�. 
	for (int& num : course)
	{
		for (string& str : orders)
		{
			find_Combination(str, num);
		}

        showRes();
        find_largest(answer);
	}

    sort(answer.begin(), answer.end());
    for (string& str : answer)
    {
        cout << "[" << str << "] ";
    }

    return answer;
}

int main()
{
    vector<string> orders = { "XYZ", "XWY", "WXA" };
    vector<int> course = {2, 3, 4};

    solution(orders, course);
    //find_Combination("ABCFG", 3);

    showRes();
}