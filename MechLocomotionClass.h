//Locomotor = {55D141B8-DB94-11d1-AC98-006008055BB5}

#pragma once

#include <LocomotionClass.h>

class NOVTABLE MechLocomotionClass : public LocomotionClass, public IPiggyback
{
public:
	static constexpr reference<CLSID const, 0x7E9AA0u> const ClassGUID {};

	// TODO stub virtuals implementations

	//Destructor
	virtual ~MechLocomotionClass() RX;

	//Constructor
	MechLocomotionClass()
		: MechLocomotionClass(noinit_t())
	{ JMP_THIS(0x5AFEF0); }

protected:
	explicit __forceinline MechLocomotionClass(noinit_t)
		: LocomotionClass(noinit_t())
	{ }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	CoordStruct Destination;
	CoordStruct HeadToCoord;
	bool IsMoving;
};

