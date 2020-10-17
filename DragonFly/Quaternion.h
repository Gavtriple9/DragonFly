#include <Arduino.h>
class Quaternion{
protected:
    float xComp;
    float yComp;
    float zComp;
    float wComp;

    float angle;
    
public:
    Quaternion();
    Quaternion( float, float, float, float );

    float operator *( Quaternion );
    Quaternion operator &( Quaternion );

    void setx(float arg){ xComp = arg; }
    void sety(float arg){ yComp = arg; }
    void setz(float arg){ zComp = arg; }
    void setw(float arg){ wComp = arg; }

    void setAngle( float arg ){ angle = arg; };
        
    float getx(void){ return xComp; }
    float gety(void){ return yComp; }
    float getz(void){ return zComp; }
    float getw(void){ return wComp; }

    float getAngle(void);

    void normalize(void);
    float getMag(void);
    void report(void);
};
