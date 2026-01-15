#pragma once

#include <bit>

enum class DirType : unsigned char;

// North -> 0x0000
// South -> 0x8000
// ...
// Just a very simple BAM
struct DirStruct
{
public:
	explicit DirStruct() noexcept : Raw{ 0 } { }
	explicit DirStruct(int raw) noexcept : Raw{ static_cast<unsigned short>(raw) } { }
	explicit DirStruct(double rad) noexcept { SetRadian<65536>(rad); }
	explicit DirStruct(const DirType dir) noexcept { SetDir(dir); }
	explicit DirStruct(const noinit_t&) noexcept { }

	bool operator==(const DirStruct& another) const
	{
		return Raw == another.Raw;
	}

	bool operator!=(const DirStruct& another) const
	{
		return Raw != another.Raw;
	}

	void SetDir(DirType dir)
	{
		Raw = static_cast<unsigned short>(static_cast<unsigned char>(dir) * 256);
	}

	DirType GetDir() const
	{
		return static_cast<DirType>(Raw / 256);
	}

	// If you want to divide it into 32 facings, as 32 has 5 bits
	// then you should type <5> here.
	// So does the others.
	template<size_t Bits>
	constexpr size_t GetValue(size_t offset = 0) const
	{
		return TranslateFixedPoint<16, Bits>(Raw, offset);
	}

	template<size_t Bits>
	constexpr void SetValue(size_t value, size_t offset = 0)
	{
		Raw = static_cast<unsigned short>(TranslateFixedPoint<Bits, 16>(value, offset));
	}

	// untemplate
	short GetValue(const size_t Bits = 16)
	{
		if (Bits > 0 && Bits <= 16)
		{
			return (short)(TranslateFixedPoint(16, Bits, (size_t)(this->Raw), 0));
		}
		return 0;
	}

	// untemplate
	void SetValue(short value, size_t Bits = 16, size_t offset = 0)
	{
		if (Bits > 0 && Bits <= 16)
		{
			Raw = static_cast<unsigned short>(TranslateFixedPoint(16, Bits, (size_t)value, offset));
		}
	}

	template<size_t Count>
	constexpr size_t GetFacing(size_t offset = 0) const
	{
		static_assert(std::has_single_bit(Count));

		constexpr size_t Bits = std::bit_width(Count - 1);
		return GetValue<Bits>(offset);
	}

	template<size_t Count>
	constexpr void SetFacing(size_t value, size_t offset = 0)
	{
		static_assert(std::has_single_bit(Count));

		constexpr size_t Bits = std::bit_width(Count - 1);
		SetValue<Bits>(value, offset);
	}

	template<size_t FacingCount>
	double GetRadian()
	{
		static_assert(std::has_single_bit(FacingCount));

		constexpr size_t Bits = std::bit_width(FacingCount - 1);

		size_t value = GetValue<Bits>();
		int dir = static_cast<int>(value) - FacingCount / 4; // LRotate 90 degrees
		return dir * (-Math::TwoPi / FacingCount);
	}

	template<size_t FacingCount>
	void SetRadian(double rad)
	{
		static_assert(std::has_single_bit(FacingCount));

		constexpr size_t Bits = std::bit_width(FacingCount - 1);
		constexpr size_t Max = (1 << Bits) - 1;

		int dir = static_cast<int>(rad / (-Math::TwoPi / FacingCount));
		size_t value = dir + FacingCount / 4; // RRotate 90 degrees
		SetValue<Bits>(value & Max);
	}

	// untemplate
	double GetRadian(size_t Bits = 16)
	{
		if (Bits > 0 && Bits <= 16)
		{
			int Max = (1 << (int)Bits) - 1;

			int value = Max / 4 - this->GetValue(Bits);
			return -value * -(Math::TwoPi / Max);
		}
		return 0;
	}

	// untemplate
	void SetRadian(double rad, size_t Bits = 16)
	{
		if (Bits > 0 && Bits <= 16)
		{
			int Max = (1 << (int)Bits) - 1;

			int value = (int)(rad * (Max / Math::TwoPi));
			this->SetValue((short)(Max / 4 - value), Bits);
		}
	}

private:
	template<size_t BitsFrom, size_t BitsTo>
	constexpr static size_t TranslateFixedPoint(size_t value, size_t offset = 0)
	{
		constexpr size_t MaskIn = ((1u << BitsFrom) - 1);
		constexpr size_t MaskOut = ((1u << BitsTo) - 1);

		if constexpr (BitsFrom > BitsTo)
			return (((((value & MaskIn) >> (BitsFrom - BitsTo - 1)) + 1) >> 1) + offset) & MaskOut;
		else if constexpr (BitsFrom < BitsTo)
			return (((value - offset) & MaskIn) << (BitsTo - BitsFrom)) & MaskOut;
		else
			return value & MaskOut;
	}

	// untemplate
	constexpr static size_t TranslateFixedPoint(size_t bitsFrom, size_t bitsTo, size_t value, size_t offset = 0)
	{
		size_t MaskIn = (1u << (int)bitsFrom) - 1;
		size_t MaskOut = (1u << (int)bitsTo) - 1;

		if (bitsFrom > bitsTo)
		{
			// converting down
			return (((((value & MaskIn) >> (int)(bitsFrom - bitsTo - 1)) + 1) >> 1) + offset) & MaskOut;
		}
		else if (bitsFrom < bitsTo)
		{
			// converting up
			return (((value - offset) & MaskIn) << (int)(bitsTo - bitsFrom)) & MaskOut;
		}
		else
		{
			return value & MaskOut;
		}
	}
public:
	unsigned short Raw;
private:
	unsigned short Padding;
};

static_assert(sizeof(DirStruct) == 4);
