extern "C"
{
	/// 打开设备
	/// 返回值：0-成功 其他-失败

	int  OpenDevice();

	/// 设置信号参数
	/// pSigType:信号类型，0-正弦信号；1-方波信号；2-三角波信号
	/// pAmp:信号幅值
	/// pFreq:信号频率，单位：HZ
	/// pPhase0:信号初始相位,单位：弧度

	void  SetSignalPara(int pSigType, double pAmp, double pFreq, double pPhase0);

	/// 设置方波占空比
	/// pDuty:方波占空比，取值范围0.00-1.00

    void  SetSWDuty(double pDuty);
		
	/// 设置采样参数
	/// pSampFreq:采样频率，单位：点/秒

	void  SetSampPara(int pSampFreq);

	/// 采集正弦信号数据(单点)
	/// pData:数据缓存区地址
	/// 返回值：0-成功 其他-失败

	int ReadOneData(double *pData);

	/// 采集正弦信号数据(多点)
	/// Num:数据点数
	/// pData:数据缓存区地址
	/// 返回值：0-成功 其他-失败

	int ReadData(int Num, double *pData);

	/// 关闭设备
	/// 返回值：0-成功 其他-失败

	int CloseDevice(void);
}
