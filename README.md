# physisim
Scripting Language &amp; Physics Simulator

Physisim is designed to resemble those physics problems you worked on in class, except you can actually see the result of your work play out with your own eyes! it's custom scripting language Physiscript (.psim) allows you to write out physics scenarios the same way you would on paper. 

-example.psim- (assume base units)
PARTICLE p1
p1 MASS 0.2
p1 POS (10, 5)

PARTICLE p2
P2 MASS 0.1
p2 POS (20, 6)

FORCE f1
f1 MAG (15, 0)

APPLY f1 p1 @ 3
