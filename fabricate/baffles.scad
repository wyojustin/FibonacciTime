inch = 25.4;
D = 185.3;
d = 166;
h = 12;

r_scale = 1.0;
translate([0, 0, 1.6])scale([r_scale, r_scale, 5])translate([-83, -83, 0])import("Fibonacci256voronoi.stl");
/*
difference(){
  cylinder(d=D, h=h, $fn=500);
  translate([0, 0, -1])cylinder(d=d, h=h+2, $fn=100);
}
*/

/*
*/

//translate([0, 0, 10])color([0, 1, .5])cylinder(h=1.6, d=166, $fn=100);
difference(){
  color([.1, .5, .6])translate([0, 0, 1.6])cylinder(h=10, d=D, $fn=300);
  translate([0, 0, -50])color([1, 1, .5])cylinder(h=100, d=160, $fn=100);
  rotate([0, 0, 54 + 90])translate([79, -5, -1])cube([30, 10, 12]);
}

//translate([0, 0, 0])color([0, 1, .5])cylinder(h=1.6, d=166, $fn=100);

difference(){
   color([.1, .5, .6])translate([0, 0, 1.6 - 2])cylinder(h=2, d=D, $fn=300);
  translate([0, 0, 1.65-30])color([1, 1, 1.6-3])cylinder(h=30, d=168, $fn=100);
  rotate([0, 0, 54 + 90])translate([79, -5, -1])cube([30, 10, 13]);
}

module screwhead(){
  cylinder(h=5, d=8, $fn=30);
}
screwhead();
