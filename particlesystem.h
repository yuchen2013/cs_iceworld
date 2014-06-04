#include "particle.h"
#include<vector>
using namespace std;
class particleSystem
{
private:
	vector<particle> particles;//所有粒子对象
	int max_count;//最多粒子个数
	
public:
	particleSystem()//初始化
	{
		max_count = 350;
		init();
	}
	void init()//初始化所有粒子
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