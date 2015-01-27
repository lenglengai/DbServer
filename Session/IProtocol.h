#pragma once

namespace std {

	class IProtocol : noncopyable
	{
	public:
		const PacketIdPtr& getPacketId(const __i32 nPacketType) const;
		void addPacketId(PacketIdPtr& nPacketId);
		
		IProtocol();
		virtual ~IProtocol();
		
	private:
		map<__i32, PacketIdPtr> mPacketIds;
	};

}
