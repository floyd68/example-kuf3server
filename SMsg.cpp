#include "SMsg.h"
#include <assert.h>




SMsgRecv::SMsgRecv(SNetBuf* pBuf)
	: m_pBuf(pBuf), m_usRead( 4 )
{
	m_pBuf->read_at(0, &m_usSize, sizeof(unsigned short));
	m_pBuf->read_at(2, &m_usID, sizeof(unsigned short));
	
}
