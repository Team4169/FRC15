#ifndef FRC15_ANGLE_H
#define FRC15_ANGLE_H

#include <math.h>

struct Angle{
	float angle;

	Angle(float angle){
		Set(angle);
	}

	void Set(float angle){
		if(angle < 0){
			while(angle < 0){
				angle += 360;
			}
			Angle::angle = angle;
		} else if(angle > 360){
			while(angle > 360){
				angle -= 360;
			}
			Angle::angle = angle;
		} else{
			Angle::angle = angle;
		}

		Angle::angle = round(Angle::angle);
	}
};

#endif
