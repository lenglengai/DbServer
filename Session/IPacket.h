#pragma once

#include "IBlock.h"

namespace std {

	class Session;
	typedef weak_ptr<Session> SessionWtr;
	typedef shared_ptr<Session> SessionPtr;
	class IPacket : noncopyable
	{
	public:
		virtual bool handleRun(SessionPtr& nSession);
		virtual bool runBlock(BlockPtr& nBlock) = 0;
		void setHeader(const __i32 nProtocol, const __i32 nPacketId);
		bool runHeader(BlockPtr& nBlock);
		__i32 getProtocolId() const;
		__i32 getPacketId() const;
		virtual bool isError() const;
		virtual void runInit() = 0;
		
		IPacket();
		virtual ~IPacket();
		
	protected:
		__i16 mVersion;
		__i32 mProtocol;
		__i32 mPacketId;
	};
	typedef shared_ptr<IPacket> PacketPtr;
	
	template<class __t0, class __t1>
	class Packet : public IPacket
	{
	public:
		void runInit()
		{
			mProtocol = __classid<__t1>();
			mPacketId = __classid<__t0>();
		}
	};
	
	class IPacketId
	{
	public:
		virtual __i32 getPacketId() const = 0;
		virtual PacketPtr createPacket() const = 0;
	};
	typedef weak_ptr<IPacketId> PacketIdWtr;
	typedef shared_ptr<IPacketId> PacketIdPtr;

	template<class __t>
	class PacketId : public IPacketId
	{
	public:
		__i32 getPacketId() const
		{
			return this->getClassId();
		}

		static __i32 getClassId()
		{
			if (0 == mPacketId) {
				mPacketId = __classid<__t>();
			}
			return mPacketId;
		}

		PacketPtr createPacket() const
		{
			return PacketPtr(new __t());
		}

		PacketId()
		{
		}

		~PacketId()
		{
		}
	private:
		static __i32 mPacketId;;
	};
	template<class __t>
	__i32 PacketId<__t>::mPacketId = 0;

}
