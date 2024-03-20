include <NopSCADlib/vitamins/pcb.scad>

tol = 0.06;
width = 17.65+tol;
length = 23.7+tol;
height = 6;
wall = 1;
btn_w = 3.5;
btn_l = 2.5;
btn_tol = 8*tol;
btn_offset = [2*wall+2.3, length-10, 0];

pcb_h=2;


module box() {
	difference() {
		translate([0, 0, wall])
		cube([width + 2*wall, length + 2*wall, height+2*wall]);

		translate([wall, wall, 2*wall])
		cube([width, length, height+wall]);

		translate([(width+2*wall)/2, length, 1.4+pcb_h])
		rotate([0, 0, 90])
		usb_C(cutout=true);
	}
}

module cover() {
	difference() {
		translate([0, 0, wall])
		cube([width + 2*wall, length + 2*wall, wall]);

		translate(btn_offset)
		cube([btn_w, btn_l, 10]);
	}

	translate([0, 0, -wall])
	difference() {
		translate([wall, wall, 0])
		cube([width-tol, length-tol, 2*wall]);

		translate([2*wall, 2*wall, 0])
		cube([width-2*wall-tol, length-wall-tol, 2*wall]);
	}
}

module button() {
	cube([btn_w-btn_tol, btn_l-btn_tol, 2.1+1+1]);
		translate([-btn_tol, -btn_tol, 0])
		cube([btn_w+btn_tol, btn_l+btn_tol, 2]);
}

box();
translate([0, 0, 20]) {
	cover();

	translate(btn_offset + [0, 0, -8]) {
		button();
	}

}
