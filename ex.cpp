// #include <iostream>
// #include <fstream>
// #include <vector>

// struct Packet {
//     double arrival_time;
//     double size;
// };

// void simulateNetwork(const std::vector<Packet>& packets, int B, double wlan_capacity) {
//     int buffer_occupancy = 0;
//     int incoming_packets = 0;
//     int delivered_packets = 0;
//     int lost_packets = 0;
//     double total_queuing_delay = 0.0;

//     double current_time = 0.0;

//     for (const Packet& packet : packets) {
//         // Handle packet arrival
//         if (packet.arrival_time <= current_time) {
//             ++incoming_packets;

//             // Check buffer occupancy
//             if (buffer_occupancy < B) {
//                 // Packet is delivered
//                 total_queuing_delay += current_time - packet.arrival_time;
//                 buffer_occupancy++;
//                 ++delivered_packets;
//             } else {
//                 // Packet loss
//                 ++lost_packets;
//             }
//         }

//         // Handle packet departure
//         if (buffer_occupancy > 0) {
//             double transmission_time = packet.size / wlan_capacity;
//             current_time += transmission_time;
//             buffer_occupancy--;
//         }
//     }

//     // Calculate and print metrics
//     double packet_loss_percentage = (static_cast<double>(lost_packets) / incoming_packets) * 100.0;
//     double average_queuing_delay = total_queuing_delay / delivered_packets;

//     std::cout << "Buffer Size (B): " << B << std::endl;
//     std::cout << "WLAN Capacity: " << wlan_capacity << " Mbps" << std::endl;
//     std::cout << "Incoming Packets: " << incoming_packets << std::endl;
//     std::cout << "Delivered Packets: " << delivered_packets << std::endl;
//     std::cout << "Lost Packets: " << lost_packets << std::endl;
//     std::cout << "Packet Loss Percentage: " << packet_loss_percentage << "%" << std::endl;
//     std::cout << "Average Queuing Delay: " << average_queuing_delay << " seconds" << std::endl;
// }

// int main() {
//     // Read packet trace from file
//     std::ifstream traceFile("./sample.txt");
//     if (!traceFile.is_open()) {
//         std::cerr << "Error opening trace file." << std::endl;
//         return 1;
//     }

//     std::vector<Packet> packets;
//     double arrival_time, size;

//     while (traceFile >> arrival_time >> size) {
//         packets.push_back(Packet(arrival_time, size));
//     }

//     // Simulate the network for various parameters
//     simulateNetwork(packets, 100, 5.0);  // Example with B=100, WLAN Capacity=5 Mbps

//     return 0;
// }







// // CPSC 441 Assignment 4
// // Eugene Lee - 30137489
// // Traffic Analysis

// #include <iostream>
// #include <fstream>
// #include <sstream>
// #include <string>
// #include <queue>

// #define BUF_SIZE 2 //100
// #define WLAN_CAP 5 //5

// using namespace std;

// struct packet {
//     double arrivalTime;
//     double size;
//     double delay;
//     double processTime;
// }

// int main() {
//     //open the input file
//     ifstream inputFile("./sample.txt");

//     //check if the input file is opened successfully
//     if (!inputFile) {
//         cerr << "Error opening file." << endl;
//         return 1;
//     }

//     //open the output file
//     std::ofstream outputFile("./output.txt");

//     //check if the output file is opened successfully
//     if (!outputFile) {
//         std::cerr << "Error opening output file." << std::endl;
//         inputFile.close(); //close the input file before exiting
//         return 1;
//     }

//     string line;
//     double count = 0;
//     deque<packet> buffer;
//     double front = 0;
//     int received = 0;
//     int dropped = 0;
//     double prevArrivalTime = 0;
//     double time = 0;
//     double amount = 0;

//     //process each line in the file
//     while (getline(inputFile, line)) {
//         count++; //count the packet
//         //find the position of the space character
//         size_t spacePos = line.find(' ');

//         //check if the space character is found
//         if (spacePos != string::npos) {
//             //extract substrings before and after the space
//             string arrivalTimeStr = line.substr(0, spacePos);
//             string packetSizeStr = line.substr(spacePos + 1);

//             //convert the substrings to double values
//             double arrivalTime = stod(arrivalTimeStr);
//             double packetSize = stod(packetSizeStr);

//             //check the size of the buffer
//             if (buffer.size() <= BUF_SIZE) { //if not full yet
//                 buffer.push_back(packetSize); //add packet to buffer
//                 front = buffer.front(); //get the front of the buffer
//                 received++; //count the received packet

//                 time = arrivalTime - prevArrivalTime;
//                 amount = time * WLAN_CAP;
//                 while (amount > front) {
//                     amount -= front;
//                     buffer.pop_front();
//                     front = buffer.front();
//                     cout << ">" << endl;
//                 }
//                 if (amount == front) {
//                     buffer.pop_front();
//                     cout << "=" << endl;
//                 } else {
//                     front -= amount;
//                     buffer.at(0) = front;
//                     cout << "<" << endl;
//                 }

//                 cout << "buffer size: " << buffer.size() << endl;
//                 cout << "Buffer: ";
//                 for(double num : buffer) {
//                     cout << num << " ";
//                 }
//                 cout << endl;

//                 prevArrivalTime = arrivalTime; //now becomes the previous time for the next iteration
//             } else { //if it is full
//                 dropped++; //count the dropped packet
//             }

//             //print the result
//             outputFile << "Retrieved: " << arrivalTime << " & " << packetSize << endl;
//         } else {
//             cerr << "Error reading line: " << line << endl;
//         }
//     }
//     outputFile << "\nStats\nTotal number of incoming packets: " << count << "\nTotal number of delivered packets: " << received << "\nTotal number of lost packets: " << dropped << "\nPacket loss percentage: " << dropped/count << endl << endl;
//     cout << "\nStats\nTotal number of incoming packets: " << count << "\nTotal number of delivered packets: " << received << "\nTotal number of lost packets: " << dropped << "\nPacket loss percentage: " << dropped/count << endl << endl;

//     //close the files
//     inputFile.close();
//     outputFile.close();
//     return 0;
// }






// // CPSC 441 Assignment 4
// // Eugene Lee - 30137489
// // Traffic Analysis

// #include <iostream>
// #include <fstream>
// #include <sstream>
// #include <string>
// #include <queue>

// #define BUF_SIZE 100 //2
// #define WLAN_CAP 5 //5

// using namespace std;

// struct packet {
//     double arrivalTime;
//     double size;
//     double delay;
//     double processTime;
// };

// int main() {
//     //open the input file
//     ifstream inputFile("./zoom.txt");

//     //check if the input file is opened successfully
//     if (!inputFile) {
//         cerr << "Error opening file." << endl;
//         return 1;
//     }

//     //open the output file
//     std::ofstream outputFile("./output.txt");

//     //check if the output file is opened successfully
//     if (!outputFile) {
//         std::cerr << "Error opening output file." << std::endl;
//         inputFile.close(); //close the input file before exiting
//         return 1;
//     }

//     string line;
//     double count = 0;
//     deque<double> buffer;
//     double front = 0;
//     int received = 0;
//     int dropped = 0;
//     double prevArrivalTime = 0;
//     double time = 0;
//     double amount = 0;
//     double wLanBytes = 125000 * WLAN_CAP;
// //    double wLanBytes = WLAN_CAP;

//     //process each line in the file
//     while (getline(inputFile, line)) {
//         count++; //count the packet
//         //find the position of the space character
//         size_t spacePos = line.find(' ');

//         //check if the space character is found
//         if (spacePos != string::npos) {

//             packet myPacket;

//             //extract substrings before and after the space
//             string arrivalTimeStr = line.substr(0, spacePos);
//             string packetSizeStr = line.substr(spacePos + 1);

//             //convert the substrings to double values
//             double arrivalTime = stod(arrivalTimeStr);
//             double packetSize = stod(packetSizeStr);

//             if (!buffer.empty()) {
//                 front = buffer.front(); //get the front of the buffer
//                 time = arrivalTime - prevArrivalTime;
//                 amount = time * wLanBytes;
//                 while (amount > front) {
//                     amount -= front;
//                     buffer.pop_front();
//                     if (!buffer.empty()) {
//                         front = buffer.front();
//                     } else {
//                         break;
//                     }
                
//                     // cout << ">" << endl;
//                 }
//                 if ((amount == front) && (!buffer.empty())) {
//                     buffer.pop_front();
//                     // cout << "=" << endl;
//                 } else if ((amount < front) && (!buffer.empty())) {
//                     front -= amount;
//                     buffer.at(0) = front;
//                     // cout << "<" << endl;
//                 }
//             }


//             //check the size of the buffer
//             if (buffer.size() < BUF_SIZE) { //if not full yet
//                 buffer.push_back(packetSize); //add packet to buffer
//                 received++; //count the received packet

//                 prevArrivalTime = arrivalTime; //now becomes the previous time for the next iteration
//             } else { //if it is full
//                 dropped++; //count the dropped packet
//             }

//             // cout << "buffer size: " << buffer.size() << endl;
//             // cout << "Buffer: ";
//             // for(double num : buffer) {
//             //     cout << num << " ";
//             // }
//             // cout << endl;

//             //print the result
// //            outputFile << "Retrieved: " << arrivalTime << " & " << packetSize << endl;
//         } else {
//             cerr << "Error reading line: " << line << endl;
//         }
//     }
//     outputFile << "\nStats\nTotal number of incoming packets: " << count << "\nTotal number of delivered packets: " << received << "\nTotal number of lost packets: " << dropped << "\nPacket loss percentage: " << dropped/count << endl << endl;
//     cout << "\nStats\nTotal number of incoming packets: " << count << "\nTotal number of delivered packets: " << received << "\nTotal number of lost packets: " << dropped << "\nPacket loss percentage: " << dropped/count * 100 << "%" << endl << endl;

//     //close the files
//     inputFile.close();
//     outputFile.close();
//     return 0;
// }

















#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <sstream>


#define PACKET_ARRIVED 0
#define PACKET_DEPARTURE 1
#define PACKET_DROPPED 2
#define SPACE_DELIMITER " "
#define MEGA_BITS_TO_BITS 1000000

// structure to hold event data
struct Event
{
  int id;
  int type;
  double time;
  long packet_size;
};

typedef Event* EventRef; // type definition for pointer to Event structure

struct scmp { // structure to compare event values stored in a multiset
  bool operator()(const EventRef & a, const EventRef & b) const {
    if(a -> time == b -> time) {
      return a -> type < b -> type;
    } else {
      return a -> time < b -> time;
    }
   }
 };

int global_id = 0; // global variable to give an id to each packet
std::multiset<EventRef,scmp> all_events; // multiset to store events in ascending order with respect to time


EventRef get_event(const std::string in) {
  std::string line(in); // create a new string from the input string
  std::vector<std::string> words; // vector to store line after spliting

  size_t idx = 0;

  // loop through line while it has white spaces
  while((idx = line.find(SPACE_DELIMITER)) != std::string::npos) {
    words.push_back(line.substr(0, idx)); // add the word to the vector
    line.erase(0, idx + 1); // remove the word from the input string
  }

  if(line.length() != 0) { // if line still has words, add it to the end of the vector
    words.push_back(line);
  }

  if(words.size() != 2) { // if input data is invalid
    return nullptr; // return null
  }

  for(auto str : words) { // remove spaces in all words in the vector
    str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
  }

  struct Event* result = (Event*)malloc(sizeof(Event)); // allocate memory to event

  result -> type = PACKET_ARRIVED; //set event type in struct
  result -> time = std::stod(words[0]); // change arrival time to double and set it in struct
  result -> packet_size = std::stol(words[1]); // chnage packet size to long and set it in struct
  result -> id = global_id; // give an id to the packet

  global_id++; // increment id for next packet

  return result;
}


void load_data_from_file(std::string file_name) {
  std::ifstream input; // create an ifstream
  input.open(file_name); // open the input file name

  std::string current_line;

  while(std::getline(input, current_line)) { // read the file line by line
    struct Event* current_event = get_event(current_line); // get event struct from read line
    if(current_event != nullptr) { // if event is valid
      all_events.insert(current_event); // add event to multiset
    }

  }
}


// function to print event for debugging purposes
void print_event(const EventRef e) {
  std::cout << "\n----------------------------------" << std::endl;
  std::cout << "Event id: " << e -> id << std::endl;
  std::cout << "Event Type: " << e -> type << std::endl;
  std::cout << "Event Time: " << e -> time << std::endl;
  std::cout << "Event Packet Size: " << e -> packet_size << std::endl;
  std::cout << "\n----------------------------------" << std::endl;
}

int main(int argc, char *argv[]) {
  std::cout << "*********************************************" << std::endl;
  std::cout << "Note 1: test files should be in the same driectory as the program." << std::endl;
  std::cout << "Note 2: For the bonus, enter -2- for the number of test files when prompted, then enter the file names of the text files having the two traces." <<
  "For regular testing, enter -1- for the number of test files when prompted, then enter the name of the text file having the trace." << std::endl;
  std::cout << "*********************************************\n" << std::endl;

  std::string temp_num_files; // variable to store string representation of the number of files
  std::string temp_buffer_size; // variable to store string representation of the buffer size
  std::string temp_capacity; // variable to store string representation of the link capacity
  int input_num_files; // number of files to read
  int  MAX_BUFFER_LENGTH; // buffer size
  int unconverted_capacity; // capacity in Mbps
  long OUTPUT_LINK_CAPACITY; // capacity in bps


  while(true) { // keep asking user to enter the size of the buffer while it is invalid
    std::cout << "Enter desired AP buffer size: ";
    std::cin >> temp_buffer_size;
    std::stringstream input_stream(temp_buffer_size);
    input_stream >> MAX_BUFFER_LENGTH; // change buffer size to integer
    if(!input_stream) { // if conversion failed, display error message and re-prompt user
      std::cout << "Please enter an integer number for the buffer size\n" << std::endl;
      continue;
    }
    break;
  }

  while(true) { // keep asking user to enter the capacity while it is invalid
    std::cout << "Enter desired WLAN capacity (Mbps): ";
    std::cin >> temp_capacity;
    std::stringstream input_stream(temp_capacity);
    input_stream >> unconverted_capacity; // change capacity to integer
    if(!input_stream) { // if conversion failed, display error message and and re-prompt user
      std::cout << "Please enter an integer number for the WLAN capacity (Mbps)\n" << std::endl;
      continue;
    }
    OUTPUT_LINK_CAPACITY = unconverted_capacity * MEGA_BITS_TO_BITS; // convert capacity from Mbps to bps
    break;
  }

  while(true) { // keep asking user to enter the number of files while it is invalid
    std::cout << "Enter number of files input to the simulator: ";
    std::cin >> temp_num_files;
    std::stringstream input_stream(temp_num_files);
    input_stream >> input_num_files; // change number of files to integer
    if(!input_stream) { // if conversion failed, display error message and re-prompt user
      std::cout << "Please enter an integer number of files\n" << std::endl;
      continue;
    }
    break;
  }

  std::vector<std::string> input_file_names(input_num_files); // vector to store file names input by user

  for(int i = 0; i < input_num_files; i++) { // keep asking user for the file names to read
    std::cout << "\nEnter the name for file number " << i + 1 << " including extension. E.g soccer.txt" << std::endl;
    std::cout << "File name: ";

    std::cin >> input_file_names[i];
  }

  std::cout << "\nSimulation running. Result will be displayed soon ......\n" << std::endl;

  for(std::string file_name : input_file_names) { // load data from files into memory
    load_data_from_file(file_name);
  }


  std::cout << "---------------------Results------------------------------" << std::endl;

  std::vector<EventRef> buffer_events; // vector to store events in the buffer
  std::set<int> packets_sent_to_buffer; // set to keep track of ids of packets alread sent to buffer

  int remaining_buffer = MAX_BUFFER_LENGTH; // integer to keep track of remaining buffer
  long double current_time = 0; // variable to track current time
  long lost_packets = 0; // long to keep track of number of lost packets
  long discarded_bytes = 0; // keep track of number of lost bytes
  long incoming_packets = 0; // keep track of number of incoming packets
  long incoming_bytes = 0; // keep track of number of incoming bytes
  long outgoing_packets = 0; // keep track of number of sent packets
  long outgoing_bytes = 0; // keep track of number of sent bytes
  long peak_occupancy = 0; // keep track of max number of packets in the buffer at any point in time
  long current_buffered_bytes = 0; // keep track of number of bytes currently in the buffer
  long current_buffered_packets = 0; // keep track of number of packets currently in the buffer
  long total_buffered_bytes = 0; // keep track total number of bytes that got buffered
  long total_buffered_packets = 0; // keep track of total number of packets that got buffered
  long peak_buffered_bytes = 0; // keep track of max number of bytes buffere at any point in time
  long double total_queuing_delay = 0; // keep track of total queuing delay for all transmitted packets

  Event* last_event = nullptr;
  if(!all_events.empty()) {
    last_event = *(--all_events.end()); // keep last event for future use
  }


  while(!all_events.empty()) { // loop through all events while events are still in the queue
    if(current_buffered_packets > peak_occupancy) { // if current occupancy is greater than peak occupancy
      peak_occupancy = current_buffered_packets; // update peak occupancy
    }

    if(current_buffered_bytes > peak_buffered_bytes) { // if buffered bytes is greater than peak bytes
      peak_buffered_bytes = current_buffered_bytes; // udpate peak bytes
    }

    Event* event = *(all_events.begin()); // get event with smallest time

    all_events.erase(all_events.begin()); // remove event from queue
    switch(event -> type) {
      case PACKET_ARRIVED: // case 1: packet arrived
        incoming_packets++; // increment incoming packets
        incoming_bytes += event -> packet_size; // add packet size to incoming bytes
        if(remaining_buffer == 0) { // if no more buffer space is left
          struct Event* arrived_drop_event = (Event*)malloc(sizeof(Event)); // allocate memory for a new event

          arrived_drop_event -> id = event -> id; // set event if to packet id
          arrived_drop_event -> type = PACKET_DROPPED; // set event type to PACKET_DROPPED
          arrived_drop_event -> time = current_time; // set drop time to current time
          arrived_drop_event -> packet_size = event -> packet_size; // set event packet size

          all_events.insert(arrived_drop_event); // add event to queue
        } else { // if buffer space exists
          remaining_buffer--; // decrement available buffer
          current_buffered_bytes += event -> packet_size; // add packet size to current buffered bytes
          current_buffered_packets++; // increment number of packets currently buffered
          total_buffered_bytes += event -> packet_size; // add packet size to total buffered bytes
          total_buffered_packets++; // increment total buffered packets
          buffer_events.push_back(event); // add event to buffer
        }
        break;
      case PACKET_DROPPED: // case 2: packet dropped
        discarded_bytes += event -> packet_size; // add size of packet to number of discarded bytes
        lost_packets++; // increment number of lost packets
        break;

      case PACKET_DEPARTURE: // case 3: packet began being transmitted
      {
        outgoing_packets++; // increment number of outgoing packets
        outgoing_bytes += event -> packet_size; // add packet size to total outgoing bytes

        // calculate packet queuing delay as: current time - packet arrival time
        long double packet_queuing_delay = current_time - ((*(buffer_events.begin()))  -> time);

        total_queuing_delay += packet_queuing_delay; // add packet queuing delay to total queuing delay

        // calculate transmission delay as L/R where L is the packet size and R is the link capacity
        long double transmission_delay = ((long double)((event -> packet_size) * 8) / (long double)OUTPUT_LINK_CAPACITY);
        current_time += transmission_delay; // forward current time by the transmission delay

        // process all events that happened while the packet was being transmitted
        while(!all_events.empty()) {
          if(current_buffered_packets > peak_occupancy) { // if current occupancy is greater than peak occupancy
            peak_occupancy = current_buffered_packets; // update peak occupancy
          }

          if(current_buffered_bytes > peak_buffered_bytes) { // if buffered bytes is greater than peak bytes
            peak_buffered_bytes = current_buffered_bytes; // udpate peak bytes
          }

          Event* previous_event = *(all_events.begin()); // get event with lowest time stamp

          // if event is not PACKET_DROPPED or PACKET_ARRIVED, break out of loop
          if(previous_event -> time > current_time || previous_event -> type == PACKET_DEPARTURE) {
            break;
          }

          all_events.erase(all_events.begin()); // if still in loop, remove event currently being processed

          if(previous_event -> type == PACKET_DROPPED) { // if event type is packet dropped
            discarded_bytes += previous_event -> packet_size; // add packet size to discarded bytes
            lost_packets++; // increment number of lost packets
          } else { // if event type is packet arrival
            incoming_packets++; // increment number of incoming packets
            incoming_bytes += previous_event -> packet_size; // add packet size to number of incoming bytes
            if(remaining_buffer == 0) { // if no more buffer space is left
              struct Event* drop_event = (Event*)malloc(sizeof(Event)); // allocate memory for a new event

              drop_event -> id = previous_event -> id; // set event if to packet id
              drop_event -> type = PACKET_DROPPED; // set event type to PACKET_DROPPED
              drop_event -> time = current_time; // set drop time to current time
              drop_event -> packet_size = previous_event -> packet_size;  // set event packet size

              all_events.insert(drop_event); // add event to queue
            } else { // if buffer space exists
              remaining_buffer--; // decrement available buffer
              current_buffered_bytes += previous_event -> packet_size; // add packet size to current buffered bytes
              current_buffered_packets++; // increment number of packets currently buffered
              total_buffered_bytes += previous_event -> packet_size; // increment total buffered packets
              buffer_events.push_back(previous_event); // add event to buffer
            }
          }
        }

        buffer_events.erase(buffer_events.begin()); // remove departure event from buffer
        remaining_buffer++; // increment amount of remaining buffer
        current_buffered_bytes -= event -> packet_size; // remove pack size from current buffered bytes
        current_buffered_packets--; // decerement number of current buffered packets

        break;
      }
    }

    // if no more event to process in the current time, advance current time to next departure time
    if(!buffer_events.empty() > 0 && !all_events.empty() && current_time < ((*(buffer_events.begin())) -> time)
      && (*(all_events.begin())) -> time >= (*(buffer_events.begin())) -> time) {
      current_time = (*(buffer_events.begin())) -> time;
    }

    // create a departure events if it doesn't exist for packets in the buffer
    if(buffer_events.size() > 0 && current_time >= (*(buffer_events.begin())) -> time
      && packets_sent_to_buffer.find((*(buffer_events.begin())) -> id) == packets_sent_to_buffer.end()) {

      struct Event* departure_event = (Event*)malloc(sizeof(Event)); // allocate memory for a new event

      departure_event -> type = PACKET_DEPARTURE; // set event type as a departure event
      departure_event -> time = current_time; // set event time to current time
      departure_event -> packet_size = (*(buffer_events.begin())) -> packet_size; // set packet size
      departure_event -> id = (*(buffer_events.begin())) -> id; // set event id to packet id

      packets_sent_to_buffer.insert((*(buffer_events.begin())) -> id); // add packet id to set that tracks ids

      all_events.insert(departure_event); // add departure event to queue
    }

  }

  if(current_time == 0 && last_event != nullptr) { // if simulation didn't proceed, ie buffer = 0
    current_time = last_event -> time;
  }

  long double average_queuing_delay = total_queuing_delay / (long double)outgoing_packets; // calculate average queuing delay

  std::cout.precision(10); // set the precision of standard output


  // Dispaly results
  std::cout << "AP Buffer Size: " << MAX_BUFFER_LENGTH << " pkts" << std::endl;
  std::cout << "Wireless Link Speed: " << OUTPUT_LINK_CAPACITY << " bps" << std::endl;
  std::cout << "End time: " << current_time << std::endl;
  std::cout << "Incoming traffic: " << incoming_packets << " pkts\t" << incoming_bytes << " bytes" << std::endl;
  std::cout << "Outgoing traffic: " << outgoing_packets << " pkts\t" << outgoing_bytes << " bytes" << std::endl;
  std::cout << "Buffered traffic: " << total_buffered_packets << " pkts\t" << total_buffered_bytes << " bytes" << std::endl;
  std::cout << "Discarded traffic: " << lost_packets << " pkts\t" << discarded_bytes << " bytes" << std::endl;
  std::cout << "Peak occupancy: " << peak_occupancy << " pkts\t" << peak_buffered_bytes << " bytes" << std::endl;
  std::cout << "Lost traffic: " << ((double)lost_packets / (double)incoming_packets) * 100.0 << "% pkts\t" << ((double)discarded_bytes / (double)incoming_bytes) * 100.0 << "% bytes" << std::endl;
  std::cout << "Average queuing delay: " << average_queuing_delay << std::endl;

  std::cout << "----------------------------------------------------------\n\n" << std::endl;


  return 0;
}