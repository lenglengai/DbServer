#pragma once

namespace std {

	class IBlock : noncopyable
	{
	public:
		virtual bool runBool(bool& nValue) = 0;

		virtual bool runInt8(__i8& nValue) = 0;
		virtual bool runInt8s(list<__i8>& nValue) = 0;

		virtual bool runInt16(__i16& nValue) = 0;
		virtual bool runInt16s(list<__i16>& nValue) = 0;

		virtual bool runInt32(__i32& nValue) = 0;
		virtual bool runInt32s(list<__i32>& nValue) = 0;

		virtual bool runInt64(__i64& nValue) = 0;
		virtual bool runInt64s(list<__i64>& nValue) = 0;

		virtual bool runString(string& nValue) = 0;
		virtual bool runStrings(list<string>& nValue) = 0;

		virtual bool runFloat(float& nValue) = 0;
		virtual bool runFloats(list<float>& nValue) = 0;

		virtual bool runDouble(double& nValue) = 0;
		virtual bool runDoubles(list<double>& nValue) = 0;
		
		virtual bool isReader() const = 0;
	};
	typedef shared_ptr<IBlock> BlockPtr;

}
