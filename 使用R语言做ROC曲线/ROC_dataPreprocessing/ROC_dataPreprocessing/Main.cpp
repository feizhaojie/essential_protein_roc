#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

//读取对应方法蛋白质及值
void ReadPreteinFile(vector<pair<float, string> >& file,string FileName)
{
	ifstream in;
	in.open(FileName, ios::in);
	string line, word;
	pair<float, string > temp;
	while (getline(in, line))
	{
		istringstream record(line);
		record >> temp.second;
		record >> temp.first;
		file.push_back(temp);
	}
	in.close();
}
//判断是否为关键蛋白质,string为关键蛋白质txt
void Judge_protein(vector<pair<float, string> >& m,string file_name,vector<pair<float,int>> &result)
{
	ifstream in;
	in.open(file_name, ios::in);
	vector<string> essential_protein;
	string temp;
	while (getline(in,temp))
	{
		essential_protein.push_back(temp);
	}
	in.close();
	//int j = 1;
	//for (auto i : essential_protein)
	//	cout << i << (((j++) % 10) ? ' ' : '\n');
	for (auto i : m)
	{
		if ((find(essential_protein.begin(), essential_protein.end(), i.second)) != essential_protein.end())
		{
			result.push_back(make_pair(i.first, 1));
		}
		else
			result.push_back(make_pair(i.first, 0));
	}
}

void WriteFile(vector<pair<float, int>> &res,ostream &on = cout)
{
	for (auto i : res)
		on << i.first << " " << i.second << endl;
}

bool compare(const pair<float, string> &p1, const pair<float, string> &p2)
{
	return p1.first > p2.first;
}
int main()
{
	//将读入文件放入read_file中
	vector<pair<float, string> > read_file_map;
	string FileName = "C:\\Users\\Administrator\\Desktop\\使用R语言做ROC曲线\\cytoscape\\Degree(dc).txt";
	ReadPreteinFile(read_file_map, FileName);
	sort(read_file_map.begin(), read_file_map.end(), compare);
	vector<pair<float, int>> res;
	string ess_file = "C:\\Users\\Administrator\\Desktop\\使用R语言做ROC曲线\\essential.txt";
	Judge_protein(read_file_map, ess_file, res);
	/*for (auto i : res)
		cout << i.first << " " << i.second << endl;*/
	string save_f_n = "C:\\Users\\Administrator\\Desktop\\使用R语言做ROC曲线\\处理\\DC\\DC.txt";
	ofstream on;
	on.open(save_f_n);
	//将数据写回save_f_n文件
	WriteFile(res, on);
	on.close();
	
	system("pause");
	return 0;
}