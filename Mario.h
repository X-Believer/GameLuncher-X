#pragma once
#include"Creature.h"

class Mario : public Creature
{
	friend class SuperMario;
public:

	//���캯��
	Mario();
	
	//��Ⱦ��ɫ
	void Render(double x, double y, const char* file = NULL);

	//���½�ɫ 0->freeze 1->idle 2->run 3->jump 4->down 5->climb 6->attack 7->squat
	void UpdateStatus(int type = 0, int damage = 0);

	//����Ƿ����µ�
	bool CheckFall();

	//������ײ
	bool ReportCollide(int direction, Creature* target = NULL, int layer=1);

	//����ɱ
	void Kill(int direction = 0);

	//��������
	~Mario();

private:
	int animationTime = 0;      //����ʱ���
	int changeTime = 0;         //�ı�ȼ�ʱ���
	int invincibleTime = 0; //�޵ж�����˸ʱ���
	int fireTime = 0; //�������ʱ��
	bool jumpKey = false;
	bool jumpSound = false;
	bool flagDirection;     //���췽��
	bool isSquat = false; //�Ƿ��¶�
	bool isDash = false; //�Ƿ��ڳ��״̬
	bool changeSize = false; //�Ƿ�ı�״̬��С

	//����
	bool MarioStand();

	//�¶�
	bool MarioSquat();

	//��Ծ
	bool MarioJump();

	//����
	bool MarioChange(int type);

};

