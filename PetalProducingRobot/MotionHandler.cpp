#include "MotionHandler.h"

MotionHandler::MotionHandler() :
	msg(INFO)
{

}


MotionHandler::~MotionHandler()
{
}

void MotionHandler::ActivateGantry() 
{
	msg.Info("Gantry activated!");
	return;
}

void MotionHandler::ActivateAllAxes() 
{
	msg.Info("Axes activated");
	return;
}

void MotionHandler::Home() { 
	
	msg.Info("Homed all axes.");
	return; 
}

void MotionHandler::HomeX() {

	msg.Info("Homed X axis.");
	return;
}
void MotionHandler::HomeY() {

	msg.Info("Homed Y axis.");
	return;
}
void MotionHandler::HomeZ() {

	msg.Info("Homed Z axis.");
	return;
}
void MotionHandler::HomeU() {

	msg.Info("Homed U axis.");
	return;
}
void MotionHandler::MoveTo(double x, double y, double z, double speed)
{
	msg.Info("Moved axes to", x, y, z, "at speed",speed);
	return;
}

// Move relative to current location by an amount x, y, z
// Note default unit is mm
void MotionHandler::MoveBy(double x, double y, double z, double speed)
{
	msg.Info("Moved axes by", x, y, z, "at speed", speed);
	return;
}

// Begin free running (x direction)
void MotionHandler::RunX()
{
	msg.Info("Free running in X...");
	return;
}

// Begin free running (negative x direction)
void MotionHandler::RunXNeg()
{
	msg.Info("Free running in negative X...");
	return;
}

// Stop free running (x direction)
void MotionHandler::EndRunX()
{
	msg.Info("Stopped free running in X");
	return;
}

// Begin free running (y direction)
void MotionHandler::RunY()
{
	msg.Info("Free running in Y...");
	return;
}

// Begin free running (negative y direction)
void MotionHandler::RunYNeg()
{
	msg.Info("Free running in negative Y...");
	return;
}

// Stop free running (y direction)
void MotionHandler::EndRunY()
{
	msg.Info("Stopped free running in Y");
	return;
}

// Begin free running (z direction)
void MotionHandler::RunZ()
{
	msg.Info("Free running in Z...");
	return;
}

// Begin free running (negative z direction)
void MotionHandler::RunZNeg()
{
	msg.Info("Free running in negative Z...");
	return;
}

// Stop free running (z direction)
void MotionHandler::EndRunZ()
{
	msg.Info("Stopped free running in Z");
	return;
}

// Begin free running (rotational direction)
void MotionHandler::RunU()
{
	msg.Info("Free running rotationally...");
	return;
}

// Begin free running (rotate the other way)
void MotionHandler::RunUNeg()
{
	msg.Info("Free running rotationally (backwards) ...");
	return;
}

// Stop free running (rotational direction)
void MotionHandler::EndRunU()
{
	msg.Info("Stopped free running rotationally");
	return;
}

void MotionHandler::SetSpeedDefaults(double speedX, double speedY, double speedZ, double speedU)
{
	msg.Info("Setting speed defaults to:");
	msg.Info("\nx axis:", speedX);
	msg.Info("\ny axis:", speedY);
	msg.Info("\nz axis:", speedZ);
	msg.Info("\nrotational axis:", speedU);
	return;
}

void MotionHandler::SetSpeedX(double speed)
{
	msg.Info("Setting x axis speed to", std::to_string(speed));
	return;
}

void MotionHandler::SetSpeedY(double speed)
{
	msg.Info("Setting y axis speed to", std::to_string(speed));
	return;
}

void MotionHandler::SetSpeedZ(double speed)
{
	msg.Info("Setting z axis speed to", std::to_string(speed));
	return;
}

void MotionHandler::SetSpeedU(double speed)
{
	msg.Info("Setting rotational speed to", std::to_string(speed));
	return;
}