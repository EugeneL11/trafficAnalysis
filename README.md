# trafficAnalysis
Eugene Lee - 30137489 / CPSC 441 Assignment 4 / December 4th, 2023

Summary: 
This is a traffic analyzer program that can estimate the QoS of incoming video streaming traffic on a network. It measures both average queueing delay for packets and also the packet loss percentage. 

User Manual: 
1. Compile the program: Go to the working directory of the code on your device's terminal, and run the following command. 
    "g++ -o run trafficAnalysis.cpp"
2. Run the program: Run the following command to execute the program. 
    "./run"

Testing Description:
- I tested a alot both at school and at home, using my laptop. Since my laptop is Unix, it was not too challenging to make it also work on Linux devices. There seemed to be no difference between testing at home and at the university. I mainly wrote out to the terminal using cout to test my code. By printing out everything, I was able to see which parts are working and which parts aren't. It was a lot of debugging done this way. Being able to locate all the issues helped me understand all the different moving parts of the proxy, and handle all malfunctionalities appropriately.

What Works: 
- Everything in the trafficAnalyzer works as expected. It has all the required functionalities of the assignment

What Doesn't Work:
- There shouldn't be anything that doesn't work. I followed all the instructions.

Notes:
- The input file name, output file name, buffer size, and WLAN capacity are all defined at the top of the program, so that you can change with ease when testing. I did not incorporate any command line arguments as it was not part of the assignment description or requirements. I also did not round any decimal places to preserve the highest accuracy possible. Since we are dealing with such small values at times, I thought that it would be best to keep all of the digits at all times.