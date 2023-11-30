// CPSC 441 Assignment 4
// Eugene Lee - 30137489
// Traffic Analysis

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>

#define BUF_SIZE 100 //the buffer size
#define WLAN_CAP 5 //the bandwidth, in Mbps
#define inputF "./stream.txt" //the input file, change to either 'zoom.txt' or 'stream.txt' here
#define outputF "./output.txt" //the file the output will write to (will also write to the terminal everytime still)

using namespace std;

struct packet {
    double arrivalTime;
    double size;
    double delay;
    double processTime;
};

int main() {
    //open the input file
    ifstream inputFile(inputF);
    //check if the input file is opened successfully
    if (!inputFile) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    //open the output file
    ofstream outputFile(outputF);
    //check if the output file is opened successfully
    if (!outputFile) {
        std::cerr << "Error opening output file." << std::endl;
        inputFile.close(); //close the input file before exiting
        return 1;
    }

    //initialize variables
    string line;
    deque<packet> buffer;
    double incoming = 0;
    int delivered = 0;
    int dropped = 0;
    double totalDelay = 0;
    double wLanBytes = 125000 * WLAN_CAP; //converting from Mb to B

    //process each line in the file
    while (getline(inputFile, line)) {
        incoming++; //count the packet
        //find the position of the space character
        size_t spacePos = line.find(' ');

        //check if the space character is found
        if (spacePos != string::npos) {
            packet currentPacket; //create the current packet

            //extract substrings before and after the space
            string arrivalTimeStr = line.substr(0, spacePos);
            string packetSizeStr = line.substr(spacePos + 1);

            //assign packet values
            currentPacket.arrivalTime = stod(arrivalTimeStr);
            currentPacket.size = stod(packetSizeStr);
            currentPacket.processTime = currentPacket.size / wLanBytes;

            //processing packets
            while (!buffer.empty()) { //as long as the buffer isn't empty
                double deliveryTime = buffer.front().arrivalTime + buffer.front().processTime + buffer.front().delay; //time the packet at front of buffer finishes processing
                //check if any packets finished processing before the current arrival time
                if (deliveryTime <= currentPacket.arrivalTime) { //if it hasn't, pop the front of buffer
                    buffer.pop_front();
                } else { //if it has been reached, stop the loop
                    break;
                }
            }

            //check if the buffer is empty or not
            if (!buffer.empty()) {
                //the current packet's delay can be calculated by subtracting the current packet's arrival time from the time it will actually start processing
                currentPacket.delay = buffer.back().arrivalTime + buffer.back().processTime + buffer.back().delay - currentPacket.arrivalTime;
            } else {
                currentPacket.delay = 0; //there is no delay if the buffer is empty
            }

            //check the size of the buffer
            if (buffer.size() < BUF_SIZE) { //if not full yet
                buffer.push_back(currentPacket); //add packet to buffer
                delivered++; //count the delivered packet
                totalDelay += currentPacket.delay; //accumulate the total delay
            } else { //if it is full
                dropped++; //count the dropped packet
            }
        } else {
            cerr << "Error reading line: " << line << endl;
        }
    }

    //Print the statistics
    cout << "\nStats\nTotal number of incoming packets: " << incoming << endl;
    cout << "Total number of delivered packets: " << delivered << endl;
    cout << "Total number of lost packets: " << dropped << endl;
    cout << "Packet loss percentage: " << dropped/incoming * 100 << "%" << endl;
    cout << "Total Delay: " << totalDelay << endl;
    cout << "Average Delay: " << totalDelay / delivered << endl;

    outputFile << "\nStats\nTotal number of incoming packets: " << incoming << endl;
    outputFile << "Total number of delivered packets: " << delivered << endl;
    outputFile << "Total number of lost packets: " << dropped << endl;
    outputFile << "Packet loss percentage: " << dropped/incoming * 100 << "%" << endl;
    outputFile << "Total Delay: " << totalDelay << endl;
    outputFile << "Average Delay: " << totalDelay / delivered << endl;

    //close the files
    inputFile.close();
    outputFile.close();
    return 0;
}