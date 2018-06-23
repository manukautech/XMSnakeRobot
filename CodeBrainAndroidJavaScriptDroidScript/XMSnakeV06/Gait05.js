//20180623 JPC single wave rectilinear inchworm gait
//Rewrite in array format of the gait from end of 2017 
//Kept here because it demos the inchworm idea more slowly and clearly than 
//the later faster version Gait01 with smaller faster twin ripple waves

function Gait05() {
        
    var vert = [
        [  0,   0,   0,   0,   0,   0, -40,  40,  40, -40],
        [  0,   0,   0,   0,   0, -20,   0,  40,   0, -20],
        [  0,   0,   0,   0,   0, -40,  40,  40, -40,   0],
        [  0,   0,   0,   0, -20,   0,  40,   0, -20,   0],
        [  0,   0,   0,   0  -40,  40,  40, -40,   0,   0],
        [  0,   0,   0, -20,   0,  40,   0, -20,   0,   0],
        [  0,   0,   0, -40,  40,  40, -40,   0,   0,   0],
        [  0,   0, -20,   0,  40,   0, -20,   0,   0,   0],
        [  0,   0, -40,  40,  40, -40,   0,   0,   0,   0],
        [  0, -20,   0,  40,   0, -20,   0,   0,   0,   0],
        [  0, -40,  40,  40, -40,   0,   0,   0,   0,   0],
        [-20,   0,  40,   0, -20,   0,   0,   0,   0,   0],
        [-40,  40,  40, -40,   0,   0,   0,   0,   0,   0],
        [-30,  40,  30, -20,   0,   0,   0,   0,   0,   0],
        [-20,  40,  20,   0,   0,   0,   0,   0,   0,   0],
        [-10,  20,  10,   0,   0,   0,   0, -10,  20, -10],
        [  0,   0,   0,   0,   0,   0,   0, -20,  40, -20]
    ];
        
    var horiz = [
        [  0,   0,   0,   0,   0,   0,   0,   0,   0,   0]
    ];

    return [vert, horiz];
}