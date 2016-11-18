#pragma once
//==================================================================
//		## singletonBase ##
//==================================================================

template <typename T>
class CSingletonBase
{
protected:
	//�̱��� �ν��Ͻ� ����
	static T* singleton;

	CSingletonBase() {};
	~CSingletonBase() {};
public:
	//�̱��� �� ��������
	static T* getSingleton(void);
	//�̱��� �޸𸮿��� �����Ѵ�
	void releaseSingleton(void);
};

//�̱��� �ʱ�ȭ
template <typename T>
T* CSingletonBase<T>::singleton = nullptr;

//�̱��� �� ��������
template <typename T>
T* CSingletonBase<T>::getSingleton(void)
{
	//�̱����� ������ ���� �����ض�
	if (!singleton) singleton = new T;

	return singleton;
}

//�̱��� �޸𸮿��� �����Ѵ�
template <typename T>
void CSingletonBase<T>::releaseSingleton(void)
{
	//�̱����� ������ �޸𸮿��� �������ְ� �̱����� 0���� �ʱ�ȭ�ض�
	if (singleton)
	{
		delete singleton;
		singleton = nullptr;
	}
}