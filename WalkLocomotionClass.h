//Locomotor = {4A582744-9839-11d1-B709-00A024DDAFD1}

#pragma once

#include <LocomotionClass.h>

class NOVTABLE WalkLocomotionClass : public LocomotionClass, public IPiggyback
{
public:
	static constexpr reference<CLSID const, 0x7E9A60u> const ClassGUID {};

	// TODO stub virtuals implementations

	//Destructor
	virtual ~WalkLocomotionClass() RX;

	//Constructor
	WalkLocomotionClass()
		: WalkLocomotionClass(noinit_t())
	{ JMP_THIS(0x75AA90); }

protected:
	explicit __forceinline WalkLocomotionClass(noinit_t)
		: LocomotionClass(noinit_t())
	{ }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	CoordStruct Destination;
	CoordStruct HeadToCoord;
	bool IsMoving;
	bool Bool_35;
	bool  IsReallyMoving;
};

