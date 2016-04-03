TODO:
=====

* Unable to load the 8-channel wav file using ofSoundFilePlayer. 
* Make the `drawdigits()` function into `drawdigits(float number)` so that it doesn't depend on shared data (avoiding errors). Then, use this function in the draw function. 

Bugs:
====
* [liveAudio] Crashes upon quit. Suspect it has something to do with the mulitiple windows' threads not being terminated properly.
* [Approximator_dev] Crashes upon failed file load.