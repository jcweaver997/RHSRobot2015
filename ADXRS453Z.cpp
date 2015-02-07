/*
* ADXRS453Z.cpp
*
* Created on: Jan 18, 2015
* Author: ratpack
*/

#include "ADXRS453Z.h"
#include <cstdarg>

int ADXRS453ZUpdateFunction(int pointer_val) {
	ADXRS453Z * gyro = (ADXRS453Z *) pointer_val;
	Timer * timer = new Timer(); //don't update too often
	timer->Start();

	while (true) {
		gyro->Update();
		//SmartDashboard::PutNumber("task loop time", timer->Get());
		timer->Reset();
	}
	return 0;
}

ADXRS453Z::ADXRS453Z() {
	spi = new SPI(SPI::kOnboardCS0);
	spi->SetClockRate(4000000); //4 MHz (rRIO max, gyro can go high)
	spi->SetClockActiveHigh();
	spi->SetChipSelectActiveLow();
	spi->SetMSBFirst();

	command[0] = READ_COMMAND;
	command[1] = 0;
	command[2] = 0;
	command[3] = 0;
	data[0] = 0;
	data[1] = 0;
	data[2] = 0;
	data[3] = 0;
	iLoop = 0;

	accumulated_angle = 0.0;
	current_rate = 0.0;
	accumulated_offset = 0.0;
	rate_offset = 0.0;
	update_timer = new Timer();
	update_timer->Start();
	calibration_timer = new Timer();
	calibration_timer->Start();

	update_task = new Task("tADSRX543Z", (FUNCPTR) &ADXRS453ZUpdateFunction); //TODO: this should give a unique name for each gyro object
	task_started = false;
}

void ADXRS453Z::Start() {
	if (task_started) {
		update_task->Resume();
	} else {
		update_task->Start((int) this);
		task_started = true;
	}
}

void ADXRS453Z::Stop() {
	if (task_started) {
		update_task->Suspend();
	}
}

void ADXRS453Z::Update() {
	//calibration_timer->Start();
	check_parity(command);
	spi->Transaction(command, data, DATA_SIZE); //perform transaction, get error code

	if (calibration_timer->Get() < WARM_UP_PERIOD){
		lastTime = thisTime = update_timer->Get();
		return;
	} else if (calibration_timer->Get() < CALIBRATE_PERIOD) {
		Calibrate();
	} else {
		UpdateData();
	}
}

void ADXRS453Z::UpdateData() {
	int sensor_data = assemble_sensor_data(data);
	float rate = ((float) sensor_data) / 80.0;

	current_rate = rate;
	current_rate -= rate_offset;
	thisTime = update_timer->Get();

	accumulated_offset += rate * (thisTime - lastTime);
	accumulated_angle  +=  current_rate * (thisTime - lastTime);
	lastTime = thisTime;
	iLoop++;
}

void ADXRS453Z::Calibrate() {
	int sensor_data = assemble_sensor_data(data);
	float rate = ((float) sensor_data) / 80.0;

	thisTime = update_timer->Get();
	accumulated_offset += rate * (thisTime - lastTime);
	lastTime = thisTime;
	rate_offset = accumulated_offset / (calibration_timer->Get() - WARM_UP_PERIOD);
	iLoop++;
}

float ADXRS453Z::GetRate() {
	return current_rate;
}

float ADXRS453Z::GetAngle() {
	return accumulated_angle;
}

float ADXRS453Z::Offset() {
	return rate_offset;
}

void ADXRS453Z::Reset() {
	data[0] = 0;
	data[1] = 0;
	data[2] = 0;
	data[3] = 0;
	current_rate = 0.0;
	accumulated_angle = 0.0;
	rate_offset = 0.0;
	accumulated_offset = 0.0;

	//calibration_timer->Stop();
	calibration_timer->Reset();

	//update_timer->Stop();
	update_timer->Reset();
}

short ADXRS453Z::assemble_sensor_data(unsigned char * data){
	//cast to short to make space for shifts
	//the 16 bits from the gyro are a 2's complement short
	//so we just cast it too a C++ short
	//the data is split across the output like this (MSB first): (D = data bit, X = not data)
	// X X X X X X D D | D D D D D D D D | D D D D D D X X | X X X X X X X X X
	return ((short) (data[0] & FIRST_BYTE_DATA)) << 14	|
			((short) data[1]) << 6 | ((short) (data[2] & THIRD_BYTE_DATA)) >> 2;
}

void ADXRS453Z::check_parity(unsigned char * command) {
	int num_bits = bits(command[0]) + bits(command[1]) + bits(command[2]) + bits(command[3]);

	if (num_bits % 2 == 0) {
		command[3] |= PARITY_BIT;
	}
}

int ADXRS453Z::bits(unsigned char val) {
	int n = 0;

	while (val) {
		val &= val-1;
		n += 1;
	}

	return n;
}
