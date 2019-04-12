/***********************************************************************
�ļ����ƣ�TCP_SERVER.C
��    �ܣ����TCP�������շ�
��дʱ�䣺2013.4.25
�� д �ˣ���
ע    �⣺
***********************************************************************/
#include "stm32_eth.h"
#include "lwip/tcp.h"
#include "TCP_SERVER.h"

/***********************************************************************
�������ƣ�tcp_server_recv(void *arg, struct tcp_pcb *pcb,struct pbuf *p,err_t err)
��    �ܣ�TCP���ݽ��պͷ���
���������
���������
��дʱ�䣺2013.4.25
�� д �ˣ�
ע    �⣺����һ���ص���������һ��TCP�ε����������ʱ�ᱻ����
***********************************************************************/
static err_t tcp_server_recv(void *arg, struct tcp_pcb *pcb,struct pbuf *p,err_t err)
{
	char *data;
	char *data_temp;

	if(p != NULL)
	{
		tcp_recved(pcb, p->tot_len);				//��ȡ���ݳ��� tot_len��tcp���ݿ�ĳ���
		/******������ԭ������*******************/
		tcp_write(pcb,p->payload,p->tot_len,0); 	// payloadΪTCP���ݿ����ʼλ��       
		pbuf_free(p); 											/* �ͷŸ�TCP�� */
	}
	else
	{
		tcp_close(pcb); 											/* ��ΪTCP��������Ӧ�����ر�������ӣ� */
	}
	err = ERR_OK;
	return err;
}


/***********************************************************************
�������ƣ�tcp_server_accept(void *arg, struct tcp_pcb *pcb,struct pbuf *p,err_t err)
��    �ܣ��ص�����
���������
���������
��дʱ�䣺2013.4.25
�� д �ˣ�
ע    �⣺����һ���ص���������һ�������Ѿ�����ʱ�ᱻ����
***********************************************************************/
static err_t tcp_server_accept(void *arg,struct tcp_pcb *pcb,err_t err)
{
	tcp_setprio(pcb, TCP_PRIO_MIN); 		/* ���ûص��������ȼ��������ڼ�������ʱ�ر���Ҫ,�˺����������*/
	tcp_recv(pcb,tcp_server_recv); 				/* ����TCP�ε�ʱ�Ļص����� */
	err = ERR_OK;
	return err;
}


/***********************************************************************
�������ƣ�TCP_server_init(void)
��    �ܣ����TCP�������ĳ�ʼ������Ҫ��ʹ��TCPͨѶ��������״̬
���������
���������
��дʱ�䣺2013.4.25
�� д �ˣ�
ע    �⣺
***********************************************************************/
void TCP_server_init(void)
{
	struct tcp_pcb *pcb;

	/*****************************************************/
	pcb = tcp_new(); 								/* ����ͨ�ŵ�TCP���ƿ�(pcb) */
	tcp_bind(pcb,IP_ADDR_ANY,TCP_LOCAL_PORT); 	    /* �󶨱���IP��ַ�Ͷ˿ںţ���Ϊtcp�������� */
	pcb = tcp_listen(pcb); 							/* �������״̬ */
	tcp_accept(pcb,tcp_server_accept); 			    /* ��������������ʱ�Ļص����� */

}