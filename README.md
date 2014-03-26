 Introduction and Project Overview

Basic Overview and Project Description

This overview is prepared to serve the goal of making an appropriate software design for the Mars Rovers project. 
It involves setting up the frameworks that should be followed in order to properly execute instructions later in time, 
which also includes stating the specification of the language that is going to be used.

In the Mars Rover project, the Rover is placed in a fixed 2-D map, assumed to be the terrain of planet Mars, and
the control software is expected to safely guide it to its home base located at the center of the map in time.
Throughout the run, the rover may encounter craters, boulders and Martians, which it must avoid. The
simulation starts with the user providing, to the client, the Brain file which is composed of different
implementations of algorithms and schemes that are written in a language described in this document, and are
geared towards leading the rover back to the home base.
Afterwards the client will independently continue to operate the rover by communicating with the server, until
the end of the run. The server will send out different messages during the simulation and in the end when the
round is over, it will issue the score achieved which depends upon the time spent, the condition of the rover
and the penalties that have been received.

In general, our design possesses a Connection class, that acts as a mediator between the different components
and classes. It listens for any type of messages from the server and parses them and passes it on to the specific
component that is required, sends back the commands given by the respective component to the server and
also maintains the interaction of the different classes.

The language used for this project is based on the assembler language but has more high-level functions and features 
that are crafted to make the user experience better. It was designed such that it doesn't have restrictions to a 
particular strategy but rather a very flexible interface that one can use to try out different algorithms and plan
of actions, such as future simulations and others.


The language was designed to provide simple operations of assembler type equipped with some very useful
high level functions. Each line of the Brain File contains a single instruction. 
The variable types used in the assembler are: Int, Double, Position, Label and Immediate, or Boulders, Craters,
Martians or Homebase. The Brain Programmer can create some variables types and their respective arrays. To
see how this works check the relevant section.
When the brain receives telemetry data from the server the received data is put in its respective registers. The
data is stored in its respective registers until the server receives another telemetry data that replaces the old
one. It is up to the programmer to keep information from past messages, which is easily done with the
VariableRegister.

There are preset variables to access the information related to the Rover, Boulders, Craters, Martians,
Homebase and Map.The Brain Programmer can edit some of the values of the preset registers for easier usage of 
some high-level functions. This provides more flexibility and it does not corrupt memory because the modifiable 
data is updated with every telemetry message received.

Brain Requirements
The Brain code must meet the following requirements:
1) Each line of the Brain file must contain an instruction starting with one or zero labels.
2) A instruction is specified by the instruction name (3-letter word) and a number of arguments.
3) The arguments are separated by a space and does not contain spaces inside them.
4) The brain file must only contain lowercase characters, uppercase characters, numbers or one
of the following {'.', '#', '*', '[', ']'}
5) The brain file must contain either one or no call of the function: 'brk'. The same is the case for
function: 'ebk'.
6) There must be no two labels declared with the same name.



An argument must meet the following requirements:
1) An argument that starts with a lowercase or uppercase character is a Variable that relates to
the memory and is handled by the MemoryHandler. In this case the argument must either be
a Preset Variable or be created before the execution of this instruction.
2) An argument that starts with a number is an Immediate constant which can be an Int or a
Double. If the argument contains a '.' character then the argument represents a Double
3) An argument that starts with the character '*' represents an Immediate constant that is a
String. The part of the argument after the '*' is the represented String.
4) An argument that starts with the character '#' represents a Label variable.
5) The argument which is a variable and contains the '[' ']' characters must either be a preset
variable, where the information inside the brackets must be an Int or an Immediate Constant,
or part of an array.
