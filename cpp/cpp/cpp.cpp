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
    //시킨 손님 수
    int temp_count = 0;

    for (result& result : res)
    {
        if (temp_count < result.m_count)
            temp_count = result.m_count;
    }

    for (result& result : res)
    {
        //두명 이상 시킨 경우에, 최댓값이 같은 경우도 포함
        if (temp_count == result.m_count && temp_count > 1)
        {
            answer.push_back(result.m_comb);
            cout << "\n" << result.m_comb << "\n";
        }
    }

    cout << "\n";

    res.clear();
}

//order 내에서 num개의 원소를 갖는 조합을 구한다
void find_Combination(string order, int num)
{
    //조합을 위해 permutation(순열) 쓸건데, 이에 이용 (원소가 1인 인덱스만 읽으면 그게 조합이다)
    vector<int> temp;
    vector<string> combs;

    sort(order.begin(), order.end());

    if (order.size() < num)
        return;

    for (int i = 0; i < order.size(); i++)
    {
        //n개의 원소에만 1을 넣고 나머지는 0을 넣는다
        if (i < num)
            temp.push_back(1);
        else
            temp.push_back(0);
    }

    //1이 앞으로 가게 정렬
    sort(temp.begin(), temp.end());

    do
    {
        string str;

        for (int i = 0; i < temp.size(); i++)
        {
            //1인 친구에 해당하는 인덱스를 order에서 꺼내서 표현하면 조합이 된다
            if (temp[i] == 1)
            {
                //저장용으로 string 쌓기
                str.push_back(order[i]);
                //cout << order[i] << " ";
            }
        }

        //쌓은 string 를 넣음
        combs.push_back(str);
        //cout << "\n";

    } while (next_permutation(temp.begin(), temp.end()));

    //cout << "----------------\n";

    sort(combs.begin(), combs.end());

    //for (string& str : combs)
    //    cout << str << "\n";

    //res에 들어있으면 중복인지 확인
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
    //아무것도 없으면(처음 실행) 우선 쌓는다
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

    //course 를 돌며 order 안에 들어있는 주문을 베이스로 경우의 수를 모두 찾는다. 
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