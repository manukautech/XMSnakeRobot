//20180614 JPC  Gait01 Gait Rectilinear version 3
//As of this version 6 of the system, this is the most successful
//as well as the simplest gait
//Double inchworm rectilinear effect with 2 waves going tail to head.
//Simplified by removing code for interpolation between keyframe vertAngles
//Natural speed of servo movement seems to work just fine as a flowing movement.
        
//alert("Testing external js Gait01.js");
   

function Gait01() {
        
    var vert = [
        [-30,  40, -20,   0, -20,  20,  20, -20,   0,   0],
        [-10,   0,   0, -20,  20,  20, -20,   0, -20,  40],
        [-10,   0, -20,  20,  20, -20,   0, -20,  20,  15],
        [-10, -20,  20,  20, -20,   0, -20,  20,  20, -22],
        [-30,  20,  20, -20,   0, -20,  20,  20, -20,   0]
    ];
        
    var horiz = [
        [  0,   0,   0,   0,   0,   0,   0,   0,   0,   0],
        [  0,   0,   0,   0,   0,   0,   0,   0,   0,   0],
        [  0,   0,   0,   0,   0,   0,   0,   0,   0,   0],
        [  0,   0,   0,   0,   0,   0,   0,   0,   0,   0],
        [  0,   0,   0,   0,   0,   0,   0,   0,   0,   0]
    ];

    return [vert, horiz];
}