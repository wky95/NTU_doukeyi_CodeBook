# Disable randomization of memory addresses
setarch `uname -m` -R ./yourProgram
setarch $(uname -m) -R