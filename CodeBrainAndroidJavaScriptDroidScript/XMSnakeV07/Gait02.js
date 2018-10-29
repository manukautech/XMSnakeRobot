//20180623 JPC  Gait02 Gait Rectilinear version 3 Reverse
//This is only Gait01 with vert array elements reversed
        
//alert("Testing external js Gait02.js");
   

function Gait02() {
        
    var vert = [
        [-30,  20,  20, -20,   0, -20,  20,  20, -20,   0],
        [-10, -20,  20,  20, -20,   0, -20,  20,  20, -22],
        [-10,   0, -20,  20,  20, -20,   0, -20,  20,  15],
        [-10,   0,   0, -20,  20,  20, -20,   0, -20,  40],            
        [-30,  40, -20,   0, -20,  20,  20, -20,   0,   0]
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
