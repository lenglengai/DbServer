#include "../Common.h"

namespace std {

	bool ProtocolService::runReadBlock(ReadBlockPtr& nReadBlock, SessionPtr& nSession)
	{
		__i16 version_ = 0; nReadBlock->runInt16(version_);
		if (Error_::mMustUpdate_ == __vercheck(version_)) {
			return false;
		}
		
		__i32 protocolId_ = 0; nReadBlock->runInt32(protocolId_);
		auto it = mProtocols.find(protocolId_);
		if (it == mProtocols.end()) {
			return false;
		}
		IProtocol * protocol_ = it->second;
		
		__i32 packetType_ = 0; nReadBlock->runInt32(packetType_);
		const PacketIdPtr& packetId_ = protocol_->getPacketId(packetType_);
		if (!packetId_) {
			return false;
		}
		
		PacketPtr packet_ = packetId_->createPacket();
		BlockPtr block_ = nReadBlock;
		packet_->runBlock(block_);
		if (packet_->isError()) {
			return false;
		}
		return packet_->handleRun(nSession);
	}

	void ProtocolService::runClear()
	{
	}

	ProtocolService::ProtocolService()
	{
	}

	ProtocolService::~ProtocolService()
	{
	}
	
}
