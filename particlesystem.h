#include "particle.h"
#include<vector>
using namespace std;
class particleSystem
{
private:
	vector<particle> particles;//�������Ӷ���
	int max_count;//������Ӹ���
	
public:
	particleSystem()//��ʼ��
	{
		max_count = 350;
		init();
	}
	void init()//��ʼ����������
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

	void display()//��ʾ������������
	{
		for(int i = 0; i < max_count; i++)
		{
				particles[i].draw();
				particles[i].update();
		}
	}
};