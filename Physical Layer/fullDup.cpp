#include<iostream>
#include<vector>
using namespace std;

class Device {
    static int no;
    int id;
    vector<Device*> connections;
    public : 
    Device(){
        this->id = ++no;
        cout<<"Device "<<id<<" created\n";
    }
    int getId(){
        return this->id;
    }
    void establishConnection(Device* device){
        connections.push_back(device);
    }
    void sendData(Device* reciever,string data){
        cout<<"Sending message from device "<<this->id<<" device "<<reciever->getId()<<endl;
        reciever->receieveData(data);
    }
    void receieveData(string data){
        cout<<"Message recieved at device : "<<this->id<<" "<<data<<endl;
    }
};
int Device :: no = 0;

void testCase1(){
    Device *device1 = new Device();
    Device *device2 = new Device();
    device1->establishConnection(device2);
    device2->establishConnection(device1);
    string data = "hello world";
    device1->sendData(device2,data);
}

int main(){
    testCase1();
}