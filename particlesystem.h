#include "particle.h"
#include<vector>
using namespace std;
class particleSystem
{
private:
	int max_count;//���Ӹ���
	vector<particle> particles;
public:
	particleSystem()//���캯��
	{
		max_count = 300;
		init();
	}
	void init()//��ʼ��
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