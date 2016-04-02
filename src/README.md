Changelist:
===========

+ Added a ApproximatePi.h class to take care of approximation, and compute the partial amplitudes.
+ Fixed approximation math. Need to multiply 4 with the fractions
+ Added Function to compute amplitudes of all the partials. 



Bugs:
====
* Crashes upon quit. Suspect it has something to do with the mulitiple windows' threads not being terminated properly.