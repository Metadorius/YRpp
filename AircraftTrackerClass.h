/*
	AircraftTrackerClass
*/

#pragma once

#include <GeneralDefinitions.h>
#include <ArrayClasses.h>
#include <TechnoClass.h>
#include <CellClass.h>

/**
 * The game use this array when searching for and damaging air techno,
 * when warhead explosion or greatest threat.
 * JumpjetLoco, RocketLoco and FlyLoco will Add or Remove or Update this list.
 *
 */
class AircraftTrackerClass
{
public:
	static constexpr constant_ptr<AircraftTrackerClass, 0x887888u> const Instance{};

	//Destructor
	~AircraftTrackerClass() RX;

	void Add_Entry(TechnoClass* pAircraft)
		{ JMP_THIS(0x4134A0); }

	void Remove_Entry(TechnoClass* pAircraft)
		{ JMP_THIS(0x4135D0); }

	void Update_Entry(TechnoClass* pAircraft, CellStruct lastCell, CellStruct curretCell)
		{ JMP_THIS(0x4138C0); }

	int Search_Entry(CellClass* pCell, int cellSpread)
		{ JMP_THIS(0x412B40); }

protected:
	//Constructor
	AircraftTrackerClass() {}	//don't need this

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:
	DECLARE_PROPERTY(DynamicVectorClass<TechnoClass*>, Technos); // All Techno in air
	DECLARE_PROPERTY(DynamicVectorClass<TechnoClass*>, Current); // Searching for
};
