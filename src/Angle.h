#ifndef ANGLE_HEADER_GUARD
#define ANGLE_HEADER_GUARD

struct Angle{
	float angle;

	Angle(float angle){
		set(angle);
	}

	Angle operator = (Angle angle){
		Angle::set(angle.angle);
		return this;
	}

	Angle operator = (float angle){
		Angle::set(angle);
		return this;
	}

	operator float(){
		return Angle::angle;
	}

	void set(float angle){
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
	}
};

#endif
