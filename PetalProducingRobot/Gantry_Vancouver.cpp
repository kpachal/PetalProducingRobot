#include "Gantry_Vancouver.h"



Gantry_Vancouver::Gantry_Vancouver()
{
	gantry = NULL;

	xaxis = (AXISMASK)AXISMASK_02;
	xindex = (AXISINDEX)AXISINDEX_02;

	yaxis = (AXISMASK)AXISMASK_00; // AXISMASK_01 is YY, the one coupled to Y without independent movement
	yindex = AXISINDEX_00;

	zaxis = (AXISMASK)AXISMASK_03;
	zindex = AXISINDEX_03;

	uaxis = (AXISMASK)AXISMASK_04;
	uindex = AXISINDEX_04;

	allAxes = (AXISMASK)(AXISMASK_02 | AXISMASK_00 | AXISMASK_03 | AXISMASK_04);
	xyAxes = (AXISMASK)(AXISMASK_02 | AXISMASK_00);

	default_xspeed = 20;
	default_yspeed = 20;
	default_zspeed = 5;
	default_uspeed = 5;
}


Gantry_Vancouver::~Gantry_Vancouver()
{
	if (gantry != NULL) {
		if (!A3200MotionDisable(gantry, TASKID_Library, allAxes)) msg.Error("oh no");
		if (!A3200Disconnect(gantry)) msg.Error("oh no");
	}
}

void Gantry_Vancouver::ActivateGantry()
{

	A3200Connect(&gantry);
	msg.Info("Gantry activated!");
	return;
}

void Gantry_Vancouver::ActivateAllAxes()
{
	A3200MotionEnable(gantry, TASKID_Library, allAxes);
	msg.Info("Axes activated");
	return;
}

void Gantry_Vancouver::Home() {

	A3200MotionHome(gantry, TASKID_Library, allAxes);
	msg.Info("Homed all axes.");
	return;
}

void Gantry_Vancouver::HomeX() {

	A3200MotionHome(gantry, TASKID_Library, xaxis);
	msg.Info("Homed X axis.");
	return;
}

void Gantry_Vancouver::HomeY() {
	
	A3200MotionHome(gantry, TASKID_Library, yaxis);
	msg.Info("Homed Y axis.");
	return;
}
void Gantry_Vancouver::HomeZ() {

	A3200MotionHome(gantry, TASKID_Library, zaxis);
	msg.Info("Homed Z axis.");
	return;
}
void Gantry_Vancouver::HomeU() {

	A3200MotionHome(gantry, TASKID_Library, uaxis);
	msg.Info("Homed U axis.");
	return;
}

void Gantry_Vancouver::MoveTo(double x, double y, double z, double speed)
{
	if (!(isnan(speed))) {
		A3200MotionMoveAbs(gantry, TASKID_Library, xindex, x, speed);
		A3200MotionMoveAbs(gantry, TASKID_Library, yindex, y, speed);
		A3200MotionMoveAbs(gantry, TASKID_Library, zindex, z, speed / 4.0);
	}
	else {
		A3200MotionMoveAbs(gantry, TASKID_Library, xindex, x, default_xspeed);
		A3200MotionMoveAbs(gantry, TASKID_Library, yindex, y, default_yspeed);
		A3200MotionMoveAbs(gantry, TASKID_Library, zindex, z, default_zspeed);
	}
	A3200MotionWaitForMotionDone(gantry, allAxes, WAITOPTION_InPosition, -1, NULL);

	msg.Info("Moved axes to", x, y, z);
	return;
}

// Move relative to current location by an amount x, y, z
// Note default unit is mm
void Gantry_Vancouver::MoveBy(double x, double y, double z, double speed)
{

	if (!(isnan(speed))) {
		A3200MotionMoveInc(gantry, TASKID_Library, xindex, x, speed);
		A3200MotionMoveInc(gantry, TASKID_Library, yindex, y, speed);
		A3200MotionMoveInc(gantry, TASKID_Library, zindex, z, speed / 4.0);
	}
	else {
		A3200MotionMoveInc(gantry, TASKID_Library, xindex, x, default_xspeed);
		A3200MotionMoveInc(gantry, TASKID_Library, yindex, y, default_yspeed);
		A3200MotionMoveInc(gantry, TASKID_Library, zindex, z, default_zspeed);
	}
	A3200MotionWaitForMotionDone(gantry, allAxes, WAITOPTION_InPosition, -1, NULL);

	msg.Info("Moved axes by", x, y, z);
	return;
}

// Begin free running (x direction)
void Gantry_Vancouver::RunX()
{
	msg.Info("Free running in X...");
	A3200MotionFreeRun(gantry, TASKID_Library, xindex, default_xspeed);
	return;
}

// Begin free running (negative x direction)
void Gantry_Vancouver::RunXNeg()
{
	msg.Info("Free running in negative X...");
	A3200MotionFreeRun(gantry, TASKID_Library, xindex, -1.0*default_xspeed);
	return;
}

// Stop free running (x direction)
void Gantry_Vancouver::EndRunX()
{
	A3200MotionFreeRunStop(gantry, TASKID_Library, xindex);
	msg.Info("Stopped free running in X");
	return;
}

// Begin free running (y direction)
void Gantry_Vancouver::RunY()
{
	msg.Info("Free running in Y...");
	A3200MotionFreeRun(gantry, TASKID_Library, yindex, default_yspeed);
	return;
}

// Begin free running (negative y direction)
void Gantry_Vancouver::RunYNeg()
{
	msg.Info("Free running in negative Y...");
	A3200MotionFreeRun(gantry, TASKID_Library, yindex, -1.0*default_yspeed);
	return;
}

// Stop free running (y direction)
void Gantry_Vancouver::EndRunY()
{
	A3200MotionFreeRunStop(gantry, TASKID_Library, yindex);
	msg.Info("Stopped free running in Y");
	return;
}

// Begin free running (z direction)
void Gantry_Vancouver::RunZ()
{
	A3200MotionFreeRun(gantry, TASKID_Library, zindex, default_zspeed);
	msg.Info("Free running in Z...");
	return;
}

// Begin free running (negative z direction)
void Gantry_Vancouver::RunZNeg()
{
	A3200MotionFreeRun(gantry, TASKID_Library, zindex, -1.0*default_zspeed);
	msg.Info("Free running in negative Z...");
	return;
}

// Stop free running (z direction)
void Gantry_Vancouver::EndRunZ()
{
	A3200MotionFreeRunStop(gantry, TASKID_Library, zindex);
	msg.Info("Stopped free running in Z");
	return;
}

// Begin free running (rotational direction)
void Gantry_Vancouver::RunU()
{
	A3200MotionFreeRun(gantry, TASKID_Library, uindex, default_uspeed);
	msg.Info("Free running rotationally...");
	return;
}

// Begin free running (negative u direction)
void Gantry_Vancouver::RunUNeg()
{
	A3200MotionFreeRun(gantry, TASKID_Library, uindex, -1.0*default_uspeed);
	msg.Info("Free running rotationally (backwards) ...");
	return;
}

// Stop free running (rotational direction)
void Gantry_Vancouver::EndRunU()
{
	A3200MotionFreeRunStop(gantry, TASKID_Library, uindex);
	msg.Info("Stopped free running rotationally");
	return;
}

void Gantry_Vancouver::SetSpeedDefaults(double speedX, double speedY, double speedZ, double speedU)
{
	msg.Info("Setting speed defaults to:");
	msg.Info("\nx axis:", speedX);
	msg.Info("\ny axis:", speedY);
	msg.Info("\nz axis:", speedZ);
	msg.Info("\nrotational axis:", speedU);

	default_xspeed = speedX;
	default_yspeed = speedY;
	default_zspeed = speedZ;
	default_uspeed = speedU;

	return;
}

void Gantry_Vancouver::SetSpeedX(double speed)
{
	msg.Info("Setting x axis speed to", speed);
	default_xspeed = speed;
	return;
}

void Gantry_Vancouver::SetSpeedY(double speed)
{
	msg.Info("Setting y axis speed to", speed);
	default_yspeed = speed;
	return;
}

void Gantry_Vancouver::SetSpeedZ(double speed)
{
	msg.Info("Setting z axis speed to", speed);
	default_zspeed = speed;
	return;
}

void Gantry_Vancouver::SetSpeedU(double speed)
{
	msg.Info("Setting rotational speed to", speed);
	default_uspeed = speed;
	return;
}

std::vector<double> Gantry_Vancouver::WhereAmI() {
	double posX, posY, posZ, posU;
	A3200StatusGetItem(gantry, xindex, STATUSITEM_PositionFeedback, 0, &posX);
	A3200StatusGetItem(gantry, yindex, STATUSITEM_PositionFeedback, 0, &posY);
	A3200StatusGetItem(gantry, zindex, STATUSITEM_PositionFeedback, 0, &posZ);
	A3200StatusGetItem(gantry, uindex, STATUSITEM_PositionFeedback, 0, &posU);
	std::vector<double> returnVec = {posX, posY, posZ, posU};
	msg.Info("Gantry is at position",posX,posY,posZ,posU);

	return returnVec;
}