extern "C"
{
	/// ���豸
	/// ����ֵ��0-�ɹ� ����-ʧ��

	int  OpenDevice();

	/// �����źŲ���
	/// pSigType:�ź����ͣ�0-�����źţ�1-�����źţ�2-���ǲ��ź�
	/// pAmp:�źŷ�ֵ
	/// pFreq:�ź�Ƶ�ʣ���λ��HZ
	/// pPhase0:�źų�ʼ��λ,��λ������

	void  SetSignalPara(int pSigType, double pAmp, double pFreq, double pPhase0);

	/// ���÷���ռ�ձ�
	/// pDuty:����ռ�ձȣ�ȡֵ��Χ0.00-1.00

    void  SetSWDuty(double pDuty);
		
	/// ���ò�������
	/// pSampFreq:����Ƶ�ʣ���λ����/��

	void  SetSampPara(int pSampFreq);

	/// �ɼ������ź�����(����)
	/// pData:���ݻ�������ַ
	/// ����ֵ��0-�ɹ� ����-ʧ��

	int ReadOneData(double *pData);

	/// �ɼ������ź�����(���)
	/// Num:���ݵ���
	/// pData:���ݻ�������ַ
	/// ����ֵ��0-�ɹ� ����-ʧ��

	int ReadData(int Num, double *pData);

	/// �ر��豸
	/// ����ֵ��0-�ɹ� ����-ʧ��

	int CloseDevice(void);
}
