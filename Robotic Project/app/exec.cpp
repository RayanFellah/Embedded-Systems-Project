/*
Configuration (digital):    
    A0: LED (Green to -)
    A1: LED (Red to +)
    A4: Distance Captor
    A6: Right Photoresistance
    A7: Left Photoresistance
    AVCC-AGND: Distance Captor (for power)

    B2-B3: Left motor (B2: Top | B3: Bottom)
    B4-B5: Right motor (B4: Top | B5: Bottom)
    CVCC-CGND: Breadboard aliementation

    D2: Interruption Button
    D3: White Button
*/

#define F_CPU 8000000
#include <Robot.h>

int main() {
    Robot robot;
    robot.executeParkour();
    //robot.testDistanceCaptor();
    // while (true) {
    //     robot.testPhotoResistance();
    // }
    return 0;
}


