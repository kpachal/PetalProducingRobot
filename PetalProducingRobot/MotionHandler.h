#pragma once
#include "MessageHandler.h"
#include <vector>

class MotionHandler
{
public:

	MotionHandler();
	~MotionHandler();

	///////////////////////////////
	// Starting and finishing

	// Turn the gantry on
	virtual void ActivateGantry();

	// Need to activate axes before machine can be used
	virtual void ActivateAllAxes();

	///////////////////////////////
	// Motion commands

	// Home all axes
	virtual void Home();

	// Home individual axis (X)
	virtual void HomeX();

	// Home individual axis (Y)
	virtual void HomeY();

	// Home individual axis (Z)
	virtual void HomeZ();

	// Home individual axis (U)
	virtual void HomeU();

	// Move to absolute location specified by x, y, z
	// Note default unit is mm
	virtual void MoveTo(double x, double y, double z, double speed = 10);

	// Move relative to current location by an amount x, y, z
	// Note default unit is mm
	virtual void MoveBy(double x, double y, double z, double speed = 10);

	// Begin free running (x direction)
	virtual void RunX();

	// Begin free running (negative x direction)
	virtual void RunXNeg();

	// Stop free running (x direction)
	virtual void EndRunX();

	// Begin free running (y direction)
	virtual void RunY();

	// Begin free running (negative y direction)
	virtual void RunYNeg();

	// Stop free running (y direction)
	virtual void EndRunY();

	// Begin free running (z direction)
	virtual void RunZ();

	// Begin free running (negative z direction)
	virtual void RunZNeg();

	// Stop free running (z direction)
	virtual void EndRunZ();

	// Begin free running (rotational direction)
	virtual void RunU();

	// Begin free running (rotate the other way)
	virtual void RunUNeg();

	// Stop free running (rotational direction)
	virtual void EndRunU();

	///////////////////////////////
	// Configuration commands

	// Set default speed for each axis
	virtual void SetSpeedDefaults(double speedX, double speedY, double speedZ, double speedU);

	// Set speed for x axis
	virtual void SetSpeedX(double speed);

	// Set speed for y axis
	virtual void SetSpeedY(double speed);

	// Set speed for z axis
	virtual void SetSpeedZ(double speed);

	// Set speed for u axis
	virtual void SetSpeedU(double speed);

	///////////////////////////////
	// Status commands

	// Returns current location as vector in x, y, z, u
	virtual std::vector<double> WhereAmI();

protected :

	// For delivering messages.
	MessageHandler msg;

};

