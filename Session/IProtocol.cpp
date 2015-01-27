#include "../Common.h"

namespace std {

	const PacketIdPtr& IProtocol::getPacketId(const __i32 nPacketType) const
	{
		auto it = mPacketIds.find(nPacketType);
		if (it == mPacketIds.end()) {
			LogService& logService_ = Singleton<LogService>::instance();
			logService_.logError(log_1(nPacketType));
			return __defaultptr<IPacketId>();
		}
		return it->second;
	}

	void IProtocol::addPacketId(PacketIdPtr& nPacketId)
	{
		__i32 packetId_ = nPacketId->getPacketId();
		auto it = mPacketIds.find(packetId_);
		if (it != mPacketIds.end()) {
			LogService& logService_ = Singleton<LogService>::instance();
			logService_.logError(log_1(packetId_));
			return;
		}
		mPacketIds[packetId_] = nPacketId;
	}

	IProtocol::IProtocol()
	{
		mPacketIds.clear();
	}

	IProtocol::~IProtocol()
	{
		mPacketIds.clear();
	}

}
