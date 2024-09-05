static volatile const char srcvers[] __attribute__((section(".version"))) =
#ifdef Cusomter
"VERSION/foo.c/1.01/09.04.15"
#else
""
#endif
;
