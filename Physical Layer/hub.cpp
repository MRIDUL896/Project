#include<bits/stdc++.h>
using namespace std;

class Device;

class Hub {
    static int hNo;
    int id;
    vector<Device*> devices;
    public : 
    Hub() {
        this->id = hNo++;
        this->devices = {};
        cout<<"Hub "<<id<<" created\n";
    }
    int getId(){
        return this->id;
    }
    void addDevice(Device* device);
    void broadCastData(Device* sender, Device* receiver, string data);
    void broadCastAck(Device* sender, Device* receiver,string ack);
};
int Hub :: hNo = 0;

class Device {
    static int devNo;
    int id;
    Hub* hub;
    public : 
    Device(){
        this->id = devNo++;
        this->hub = NULL;
        cout<<"Device "<<id<<" created\n";
    }
    int getId(){
        return this->id;
    }
    void setHub(Hub* hub){
        this->hub = hub;
    }
    void sendMessage(Device* reciever,string data){
        cout<<"sending message from device "<<this->id<<" to hub "<<this->hub->getId()<<endl;
        this->hub->broadCastData(this,reciever,data);
    }
    void receiveMessage(Device* sender,Device* reciever,string data){
        if(reciever->getId() != this->id){
            cout<<"Device "<<this->id<<" rejected message \n";
            return;
        }
        cout<<"Device "<<this->id<<" recieved message : "<<data<<endl;
        cout<<"Sending ack from device "<<this->id<<" to device "<<sender->getId()<<endl;
        this->sendAck(reciever,sender);
    }
    void receiveAck(Device* sender,Device* reciever,string data){
        if(reciever->getId() != this->id){
            cout<<"Device "<<this->id<<" rejected ack \n";
            return;
        }
        cout<<"Device "<<this->id<<" recieved ack : "<<data<<endl;
    }
    void sendAck(Device* sender,Device* reciever){
        this->hub->broadCastAck(sender,reciever,"Ack");
    }
};
int Device :: devNo = 0;

void Hub:: addDevice(Device* device){
    cout<<"Hub "<<this->id<<" connected to "<<" device "<<device->getId()<<endl;
    this->devices.push_back(device);
}

void Hub::broadCastData(Device* sender, Device* receiver, string data){
    cout<<"Hub "<<this->id<<" is broadcasting \n";
    for(int i = 0; i < devices.size(); i++){
        if(devices[i] != sender){
            devices[i]->receiveMessage(sender,receiver, data);
        }
    }
}

void Hub::broadCastAck(Device* sender, Device* receiver, string data){
    cout<<"Hub "<<this->id<<" is broadcasting \n";
    for(int i = 0; i < devices.size(); i++){
        if(devices[i] != sender){
            devices[i]->receiveAck(sender,receiver, data);
        }
    }
}

void testCase2() {
    Hub* hub1 = new Hub();
    vector<Device*> devices;
    for(int i=0;i<5;i++){
        Device* device = new Device();
        devices.push_back(device);
        hub1->addDevice(device);
        device->setHub(hub1);
    }
    //dev1 sends hello to dev4
    devices[1]->sendMessage(devices[4],"Hello");
}

int main() {
    testCase2();
}