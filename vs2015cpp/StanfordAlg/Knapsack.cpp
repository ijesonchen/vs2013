void TestKnapsack(void);


/*
0-1���� ��̬�滮
����: n����Ʒ����ֵvi,����wi��������СW��
Ҫ�󣺱�������װ��Ʒ���ܼ�ֵV���
�����Ӽ�S��ʹsigma(wi) <= W ʱ��sigma(vi)���

˼·����֪S�����Ž⣬�������һ��Ԫ��n
1����ѡn����s    ��ǰn-1 ����W    ��ֵV    �����Ž�
2��ѡȡn����s-{n}��ǰn-1 ����W-wi ��ֵV-vi �����Ž�

�����ӽṹ
��A[i,x]��ʾ ǰi��Ԫ�أ�����x�µļ�ֵ
��A[i,x] = max{ A[i-1, x],    // ����n
		   vi + A[i-1, x-wi]} // ������n 
*/
namespace nsKnapsack01 {


	void main(void)
	{

	}
}







void TestKnapsack(void)
{
	nsKnapsack01::main();
}