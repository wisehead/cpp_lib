/*******************************************************************************
 *      file name: calculator.cpp                                               
 *         author: Hui Chen. (c) 2019                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2019/03/23-16:19:02                              
 *  modified time: 2019/03/23-16:19:02                              
 *******************************************************************************/
#include <iostream>
using namespace std;
/* Project 2
  编写一个函数int Calculate(node *pHead, int k);在链表数字之间插入+ 、- 或者什么都不插入,使得计算结果等于
  给定的整数 K,返回所有可能性的个数。例如链表有数字 1, 2, 3, ..., 9 并且给
  定的整数为 100,那么其中的一种可能性是: 1 + 2 + 34 – 5 + 67 – 8 + 9 = 100。
  (不允许开辟额外的字符串空间,假设链表所有数字都大于 0 并且小于 10)
*/
struct node {
    int val;
    node *next;
    node(int x) : val(x), next(NULL) {}
};

void create_linklist(node **pHead, int n)
{
	*pHead = NULL;
	node *pTail = NULL;
	for (int i=1; i <= n; i++)
	{
		node *p = new node(i);
		if (!(*pHead))
		{
			*pHead = p;
			pTail = p; 
			continue;
		}
		pTail->next = p; 
		pTail = p; 
	}
	pTail->next = NULL;
}
void print_linklist(node *pHead)
{
	node *p = pHead;
	while(p)
	{
		cout<<p<<"	:p->val:"<<p->val<<endl;
		p = p->next;
	}
}
//op 1 : +
//op -1 : -
//flag true: 没有运算符号，两个数字连接
//flag false: 有运算符号
void cal(string trace, node *p, int pre, int sum, int op, int k, int& cnt)
{
	//cout<<"p:"<<p<<endl;
	if (!p) 
	{
		cout<<"[NULL] trace:"<<trace<<"	p->val:"<<p->val<<"	pre:"<<pre<<"	pre*10+p->val:"<<pre*10 + p->val<<"	k:"<<k<<"	cnt:"<<cnt<<endl;;
		return;
	}
	int sum2 = 0; 
	if (op == 1)
		sum2 = sum + pre*10 + p->val; 
	else if (op == -1)
		sum2 = sum - (pre*10 + p->val); 

	if (!p->next)
	{
		if (sum2 == k)
		{
			cout<<"got 1 result."<<endl;
			cout<<"[YES ] trace:"<<trace<<"	p->val:"<<p->val<<"	op:"<<op<<"	sum:"<<sum<<"	pre:"<<pre<<"	cnt:"<<cnt<<endl;;
			cnt = 1;
		}
		else 
			cout<<"[NO  ] trace:"<<trace<<"	p->val:"<<p->val<<"	op:"<<op<<"	sum:"<<sum<<"	pre:"<<pre<<"	cnt:"<<cnt<<endl;;
		return;
	}
	int c1 = 0, c2 = 0, c3 = 0;
	cout<<"[INFO] trace:"<<trace<<"	p->val:"<<p->val<<"	op:"<<op<<"	sum:"<<sum<<"	pre:"<<pre<<"	cnt:"<<cnt<<endl;;
	cal(trace + to_string(p->val) + "+", p->next, 0, sum2, 1, k, c1);
	cal(trace + to_string(p->val) + "-", p->next, 0, sum2, -1, k, c2);
	cal(trace + to_string(p->val), p->next, pre*10 + p->val, sum, op, k, c3);
	cnt = c1 + c2 + c3;
}
int Calculate(node *pHead, int k)
{
	int count = 0;
	string trace;
	cal(trace, pHead, 0, 0, 1, k, count);
	return count;
}

int main()
{
    // Project 2
    cout << "==========Project2=================" << endl;
	node *pHead;
    //delete_linklist(&pHead);
    create_linklist(&pHead,9);
	print_linklist(pHead);
    cout << Calculate(pHead,100) << endl;
    cout << "==========Project2=================" << endl;
    cout << endl;
}
