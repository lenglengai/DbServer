#include "../Common.h"

namespace std {
	
	bool IPacket::handleRun(SessionPtr& nSession)
	{
		return true;
	}
		
	void IPacket::setHeader(const __i32 nProtocol, const __i32 nPacketId)
	{
		mProtocol = nProtocol;
		mPacketId = nPacketId;
	}
	
	bool IPacket::runHeader(BlockPtr& nBlock)
	{
		nBlock->runInt16(mVersion);
		nBlock->runInt32(mProtocol);
		nBlock->runInt32(mPacketId);
		return true;
	}

	__i32 IPacket::getProtocolId() const
	{
		return mProtocol;
	}
	
	__i32 IPacket::getPacketId() const
	{
		return mPacketId;
	}
	
	bool IPacket::isError() const
	{
		return false;
	}

	IPacket::IPacket()
		: mProtocol(0)
		, mPacketId(0)
	{
		mVersion = __versionid();
	}

	IPacket::~IPacket()
	{
		mProtocol = 0;
		mPacketId = 0;
	}

}
