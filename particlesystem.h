#include "particle.h"
#include<vector>
using namespace std;
class particleSystem
{
private:
	int max_count;//粒子个数
	vector<particle> particles;
public:
	particleSystem()//构造函数
	{
		max_count = 300;
		init();
	}
	void init()//初始化
	{
		srand((unsigned)time(NULL));
		particle* newOne;
		for(int i = 0; i < max_count; i++)
		{
			newOne = new particle();
			newOne->init();
			particles.push_back(*newOne);
			delete newOne;
		}
	}

	void display()//显示当下所有粒子
	{
		for(int i = 0; i < max_count; i++)
		{
				particles[i].draw();
				particles[i].update();
		}
	}
};